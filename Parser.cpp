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
//--------- [ CParser ] ----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void CParser::WorkerFunction(const unsigned id)
{
  cout << "INFO: Start worker function for thread ID = " << (id + 1) << endl;
  while (true)
  {
    shared_ptr< CFileParser > fileParser;

    // Mandatory scope
    {
      cout << "INFO: Locking MUTEX..." << endl;
      unique_lock< mutex > lock(m_QueueSync);
      if (!m_Files.empty())
      {        
        cout << "INFO: Attach current file to be processed " << endl;
        fileParser = m_Files.front();
        cout << "INFO: And removing current file from queue " << endl;
        m_Files.pop();
      }
      else
      {
        cout << "INFO: No files to be processed, EXIT..." << endl;
        return;
      }
    }

    if (fileParser)
    {
      //start parse the word
      fileParser->Parse(m_Word);
    }
    else
    {
      // no more files
      cout << "INFO: No more files to be processed, EXIT" << endl;
      return;
    }
  }

  cout << "INFO: Stop worker function..." << endl;
}
//--------------------------------------------------------------------------------------------------
void CParser::SpawnWorkers(unsigned workerCount)
{
  cout << "INFO: Start spawning workers..." << endl;

  if (workerCount > (unsigned)m_Files.size())
    workerCount = (unsigned)m_Files.size();

  cout << "INFO: spawning " << workerCount << " workers, total files count: " << m_Files.size() << endl;

  vector< thread > workers;
  for (unsigned i = 0; i < workerCount; i++)  
    workers.push_back(thread(&CParser::WorkerFunction, this, i));  

  for (unsigned i = 0; i < workerCount; i++)
    if (workers[i].joinable())
      workers[i].join();

  cout << "INFO: Stop spawning workers..." << endl;
}
//--------------------------------------------------------------------------------------------------
bool CParser::Parse(const unsigned workerCount)
{
  cout << "INFO: Start parsing..." << endl;

  if (fs::is_directory(m_Path))
  {
    cout << "INFO: Path is directory..." << endl;
    for (const auto& dirEntry : fs::recursive_directory_iterator(m_Path))
    {
      if (fs::is_regular_file(dirEntry))
      {
        cout << "INFO: Adding file to queue"  << dirEntry << endl;
        shared_ptr< CFileParser > parser(new CFileParser(dirEntry.path(), m_Reader));
        m_Files.push(parser);
      }
    }
  }
  else if (fs::is_regular_file(m_Path))
  {
    cout << "INFO: Path is file..." << endl;
    cout << "INFO: Adding file to queue"  << m_Path.filename() << endl;
    shared_ptr< CFileParser > parser(new CFileParser(m_Path, m_Reader));
    m_Files.push(parser);
  }
  else
  {
    cerr << "ERROR: invalid path: " << m_Path;
    cout << "INFO: Stop parsing..." << endl;
    return false;
  }

  SpawnWorkers(workerCount);

  cout << "INFO: Stop parsing..." << endl;
  return true;
}
//--------------------------------------------------------------------------------------------------