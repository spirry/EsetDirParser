#include "FileParser.h"
#include "IReader_i.h"
#include "compile.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_3 = 3;
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_2 = 2;
const string::size_type CFileParser::s_DEFAULT_SEARCH_VAL_1 = 1;
//--------------------------------------------------------------------------------------------------
#define EMPTY_STR                                  string("-")
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

  streamsize chunkSize = 1024;
  string     data;

  cout << endl;
  cout << "----------- [ RESULTS ] -------------------" << endl;
  while (true)
  {
    streamsize totalRead = m_Reader.Read(m_File, data, chunkSize);
    
    vector< string::size_type > foundPositions;
    string::size_type           startPos   = 0;
    while (string::npos != (startPos = data.find(word, startPos)))
    {
      foundPositions.push_back(startPos);      
      ++startPos;
    }

    string prefix, suffix;
    for (int j = 0; j != foundPositions.size(); ++j)
    {
      prefix.clear();
      suffix.clear();

      const string::size_type foundPosValue = foundPositions[j];
      if (foundPosValue == 0)
        prefix = EMPTY_STR;
      else if (foundPosValue == (totalRead - word.length()))
        suffix = EMPTY_STR;       
      
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
        suffix = EMPTY_STR;

      if (prefix.empty())
        prefix = EMPTY_STR;

      //---------------------------------------------------------------------------------
      vector< string::size_type > tabsNewLinePositions;
      startPos = 0;
      string::size_type startTabsSufix = 0;
      while (string::npos != (startPos = suffix.find('\t', startTabsSufix)))
      {
        tabsNewLinePositions.push_back(startPos);
        ++startTabsSufix;
      }
        
      for (int h = 0; h != tabsNewLinePositions.size(); ++h)
        suffix.replace(tabsNewLinePositions[h], 1, string("//t"));
      //---------------------------------------------------------------------------------
      tabsNewLinePositions.clear();
      startPos = 0;
      string::size_type startNewLinesSufix = 0;
      while (string::npos != (startPos = suffix.find('\n', startNewLinesSufix)))
      {
        tabsNewLinePositions.push_back(startPos);
        ++startNewLinesSufix;
      }

      for (int h = 0; h != tabsNewLinePositions.size(); ++h)
        suffix.replace(tabsNewLinePositions[h], 1, string("n"));
      //---------------------------------------------------------------------------------
      tabsNewLinePositions.clear();
      startPos = 0;
      string::size_type startTabsPrefix = 0;
      while (string::npos != (startPos = prefix.find('\t', startTabsPrefix)))
      {
        tabsNewLinePositions.push_back(startPos);
        ++startTabsPrefix;
      }        

      for (int h = 0; h != tabsNewLinePositions.size(); ++h)
        prefix.replace(tabsNewLinePositions[h], 2, "\t");
      //---------------------------------------------------------------------------------
      tabsNewLinePositions.clear();
      startPos = 0;
      string::size_type startNewLinesPrefix = 0;
      while (string::npos != (startPos = prefix.find('\n', startNewLinesPrefix)))
      {
        tabsNewLinePositions.push_back(startPos);
        ++startNewLinesPrefix;
      }
        
      for (int h = 0; h != tabsNewLinePositions.size(); ++h)
        prefix.replace(tabsNewLinePositions[h], 1, string("n"));
      //---------------------------------------------------------------------------------
      
      cout << "-------------------------------------------" << endl;
      cout << "FILE: " << m_Path.filename() << "( " << foundPositions[j] << " ) : <" << prefix << ">" << word << "<" << suffix << ">" << endl;     
    }    

    cout << "-------------------------------------------" << endl;
    // Finish
    if (totalRead < chunkSize)
      break;
  }

  m_Reader.Close(m_File);
  cout << "INFO: stop parse function..." << endl;
}
//--------------------------------------------------------------------------------------------------

