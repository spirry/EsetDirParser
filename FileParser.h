#ifndef FILE_PARSER_H
#define FILE_PARSER_H
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "IReader_i.h"
//--------------------------------------------------------------------------------------------------
//--------- [ CFileParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CFileParser
{

public:
  
  CFileParser(const std::filesystem::path &path, IReader &reader) : m_Path(path), m_Reader(reader) {}

public:

  void Parse(const std::string &word);

private:

  bool ComputePrefixSuffix(std::string &output, const std::string &input);
  void ComputeResults(const std::streamsize currentRead, const std::string &data, 
                      const std::vector< std::string::size_type > &foundPositions, 
                      const std::string &word);

  void PrintSolution();

private:

  IReader&                  m_Reader;
  std::filesystem::path     m_Path;
  std::ifstream             m_File;
  std::vector< std::string> m_Results;
  std::vector< std::string> m_Entities;

private:

  static const std::string::size_type s_DEFAULT_SEARCH_VAL_3;
  static const std::string::size_type s_DEFAULT_SEARCH_VAL_2;
  static const std::string::size_type s_DEFAULT_SEARCH_VAL_1;
  static const std::streamsize        s_DEFAULT_CHUNK_SIZE;
  static const std::string            s_EMPTY_STRING;

};
//--------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------