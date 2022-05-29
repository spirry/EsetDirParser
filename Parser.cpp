#include <iostream>
#include <filesystem>
#include <queue>
#include <thread>
#include <mutex>
#include <fstream>
#include "Parser.h"
#include "FileParser.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
namespace fs = std::filesystem;
//--------------------------------------------------------------------------------------------------
//--------- [ CParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void CParser::WorkerFunction(unsigned id)
{
  while (true)
  {
    shared_ptr< CFileParser > fileParser;

    // Mandatory scope
    {
      unique_lock< mutex > lock(m_QueueSync);
      if (!m_Files.empty())
      {
        fileParser = m_Files.front();
        m_Files.pop();

        cout << "INFO: Thread ID:  " << (id + 1) << endl;
      }
    }

    if (fileParser)
    {
      fileParser->Parse(m_Word);
    }
    else
    {
      // no more files
      return;
    }
  }
}
//--------------------------------------------------------------------------------------------------
void CParser::SpawnWorkers(unsigned workerCount)
{
  if (workerCount > (unsigned)m_Files.size())
    workerCount = (unsigned)m_Files.size();

  cout << "INFO: spawning " << workerCount << " workers, total files: " << m_Files.size() << endl;

  vector< thread > workers;
  for (unsigned i = 0; i < workerCount; i++)  
    workers.push_back(thread(&CParser::WorkerFunction, this, i));  

  for (unsigned i = 0; i < workerCount; i++)
    if (workers[i].joinable())
      workers[i].join();
}
//--------------------------------------------------------------------------------------------------
bool CParser::Parse(unsigned workerCount)
{
  cout << "INFO: Start parsing..." << endl;

  if (fs::is_directory(m_Path))
  {
    for (const auto& dirEntry : fs::recursive_directory_iterator(m_Path))
    {
      if (fs::is_regular_file(dirEntry))
      {
        cout << "INFO: dir entry "  << dirEntry << endl;
        shared_ptr< CFileParser > parser(new CFileParser(dirEntry.path(), m_Reader));
        m_Files.push(parser);
      }
    }
  }
  else if (fs::is_regular_file(m_Path))
  {
    shared_ptr< CFileParser > parser(new CFileParser(m_Path, m_Reader));
    m_Files.push(parser);
  }
  else
  {
    cerr << "ERROR: invalid path: " << m_Path;
    return false;
  }

  SpawnWorkers(workerCount);

  return true;
}
//--------------------------------------------------------------------------------------------------