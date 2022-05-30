#include "FileParser.h"
#include "IReader_i.h"
#include "compile.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_3 = 3;
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_2 = 2;
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_1 = 1;
const streamsize        CFileParser::s_DEFAULT_CHUNK_SIZE   = 1024;
const string            CFileParser::s_EMPTY_STRING         = string("-");
//--------------------------------------------------------------------------------------------------
#define EMPTY_STR                                  
//--------------------------------------------------------------------------------------------------
//--------- [ CFileParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void CFileParser::Parse(const string &word)
{
  cout << "INFO: Start parse function..." << endl;

  if (word.empty())
  {
    cerr << "ERROR: word to be searched is empty, exit... " << endl;
    return;
  }

  if (!m_Reader.OpenRead(m_File, m_Path))
  {
    cerr << "ERROR: could not open file: " << m_Path << endl;
    return;
  }

  cout << "INFO: parsing " << m_Path.filename() << endl;

  string data;
  while (true)
  {
    //read 1024 bytes of data
    streamsize totalRead = m_Reader.Read(m_File, data, s_DEFAULT_CHUNK_SIZE);

    cout << "INFO: Default chunk size  " << s_DEFAULT_CHUNK_SIZE << endl;
    cout << "INFO: Total read chars " << totalRead << endl;
    
    vector< string::size_type > foundPositions;
    string::size_type           startPos   = 0;
    while (string::npos != (startPos = data.find(word, startPos)))
    {
      foundPositions.push_back(startPos);      
      ++startPos;
    }

    cout << endl;
    cout << "----------- [ RESULTS ] -------------------" << endl;

    string prefix, suffix;
    for (int j = 0; j != foundPositions.size(); ++j)
    {
      prefix.clear();
      suffix.clear();

      const string::size_type foundPosValue = foundPositions[j];
      if (foundPosValue == 0)
        prefix = s_EMPTY_STRING;
      else if (foundPosValue == (totalRead - word.length()))
        suffix = s_EMPTY_STRING;       
      
      int prefixSub = (foundPosValue - s_DEFAULT_SEARCH_VAL_3);
      if (prefix.empty())
      {
        switch (prefixSub)
        {
          case -2: prefix = data.substr(0,         s_DEFAULT_SEARCH_VAL_1); break;
          case -1: prefix = data.substr(0,         s_DEFAULT_SEARCH_VAL_2); break;
          default: prefix = data.substr(prefixSub, s_DEFAULT_SEARCH_VAL_3); break;
        }          
      }        

      if (suffix.empty())
        suffix = data.substr((foundPosValue + word.length()), s_DEFAULT_SEARCH_VAL_3);

      if (suffix.empty())
        suffix = s_EMPTY_STRING;

      if (prefix.empty())
        prefix = s_EMPTY_STRING;
  
      string newSuffix;
      ComputePrefixSuffix(newSuffix, suffix);
      suffix = newSuffix;

      string newPrefix;
      ComputePrefixSuffix(newPrefix, prefix);
      prefix = newPrefix;
      
      cout << "-------------------------------------------" << endl;
      cout << "FILE: " << m_Path.filename() << "( " << foundPositions[j] << " ) : <" << prefix << ">" << word << "<" << suffix << ">" << endl;     
    }    

    cout << "-------------------------------------------" << endl;
    cout << "----------- [ END RESULTS ] ---------------" << endl;
    cout << endl;

    if (totalRead < s_DEFAULT_CHUNK_SIZE)
    {
      cout << "INFO: Finished parse function..." << endl;
      break;
    }      
  }

  m_Reader.Close(m_File);
  cout << "INFO: Stop parse function..." << endl;
}
//--------------------------------------------------------------------------------------------------
bool CFileParser::ComputePrefixSuffix(string &output, const string &input)
{
  output.clear();

  if (input.empty())
    return false;

  const int suffixLength = input.length();
  for (int i = 0; i < suffixLength; ++i)
  {
    const bool hasTabs     = (input[i] == '\t');
    const bool hasNewLines = (input[i] == '\n');
    if (hasTabs || hasNewLines)
    {
      output.push_back('\\');

      if (hasTabs)
        output.push_back('t');
      else if (hasNewLines)
        output.push_back('n');
    }
    else
    {
      output.push_back(input[i]);
    }
  }

  return true;
}
//--------------------------------------------------------------------------------------------------

