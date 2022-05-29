#ifndef PARSER_H
#define PARSER_H
//--------------------------------------------------------------------------------------------------
#include <mutex>
#include <queue>
#include "IReader_i.h"
#include "FileParser.h"
//--------------------------------------------------------------------------------------------------
//--------- [ CFileParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CParser
{

public:

  CParser(const std::string path, const std::string word, IReader &reader) : m_Path(path), m_Word(word), m_Reader(reader) {}

public:

  void WorkerFunction(unsigned id);
  void SpawnWorkers(unsigned workerCount);
  bool Parse(unsigned workerCount);

private:

  IReader&                                     m_Reader;
  std::mutex                                   m_QueueSync;
  std::queue< std::shared_ptr< CFileParser > > m_Files;
  std::filesystem::path                        m_Path;
  std::string                                  m_Word;

};
//--------------------------------------------------------------------------------------------------
#endif // PARSER_H
//--------------------------------------------------------------------------------------------------
