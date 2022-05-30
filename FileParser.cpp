#include <string>
#include "FileParser.h"
#include "IReader_i.h"
#include "compile.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
using std::to_string;
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
    cerr << "ERROR: could not open file = " << m_Path << endl;
    return;
  }

  cout << "INFO: parsing " << m_Path.filename() << endl;

  //Check the file size
  m_File.seekg(0, m_File.end);
  int butesTotalToRead = static_cast<int>(m_File.tellg());
  int bytesLeftToRead  = butesTotalToRead;
  m_File.seekg(0, m_File.beg);

  if (0 == butesTotalToRead) 
  {
    cout << "ERROR: Input file is empty " << endl;
    return;
  }

  int totalProcessedBulks = (butesTotalToRead / s_DEFAULT_CHUNK_SIZE);
  cout << "INFO: Total bulks to be processed = " << totalProcessedBulks << endl;

  string commonBufferData;
  size_t processedBulks = 0;
  m_Results.clear();
  vector < string > entities;
  string data;
  while (true)
  {
    ++processedBulks;
    //read 1024 bytes of data
    const streamsize currentRead = m_Reader.Read(m_File, data, s_DEFAULT_CHUNK_SIZE);
    bytesLeftToRead -= static_cast<int>(currentRead);

    entities.push_back(data);
    commonBufferData += data;

    cout << "INFO: Default chunk size  "   << s_DEFAULT_CHUNK_SIZE << endl;
    cout << "INFO: Total read chars "      << currentRead          << endl;
    cout << "INFO: Raw data to pe parsed " << data                 << endl;
    
    vector< string::size_type > foundPositions;
    string::size_type           startPos   = 0;
    while (string::npos != (startPos = data.find(word, startPos)))
    {
      foundPositions.push_back(startPos);
      ++startPos;
    }

    ComputeResults(currentRead, data, foundPositions, word);

    if (bytesLeftToRead <= 0 )
    {
      cout << "INFO: Finished parse buffers..." << endl;
      break;
    }      
  }

  //there is a problem when word is split between buffers
  cout << "INFO: Continue parsing between buffers..." << endl;
  size_t count = 0;
  string nameBetweenBuffers;
  for (auto it = entities.cbegin(); it != entities.cend(); ++it)
  {
    ++count;
    const string currEntity       = *it;
    const size_t currEntityLength = currEntity.size();

    if (count % 2 == 0)
      nameBetweenBuffers += currEntity.substr((0), word.length());
    else
      nameBetweenBuffers += currEntity.substr((currEntityLength - word.length()), word.length());      
  }

  cout << "INFO: Buffers concatenated = " << nameBetweenBuffers << endl;

  vector< string::size_type > foundNewPositions;
  string::size_type           startNewPos = 0;
  while (string::npos != (startNewPos = nameBetweenBuffers.find(word, startNewPos)))
  {
    foundNewPositions.push_back(startNewPos);
    ++startNewPos;
  }

  ComputeResults(0, nameBetweenBuffers, foundNewPositions, word);

  PrintSolution(); 
  cout << endl;

  m_Reader.Close(m_File);
  cout << "INFO: Stop parse function..." << endl;
}
//--------------------------------------------------------------------------------------------------
void CFileParser::ComputeResults(const streamsize currentRead, const string &data, 
                                 const vector< string::size_type > &foundPositions, 
                                 const string &word)
{
  string suffix, prefix;
  for (unsigned j = 0; j != foundPositions.size(); ++j)
  {
    prefix.clear();
    suffix.clear();

    const string::size_type foundPosValue = foundPositions[j];
    if (foundPosValue == 0)
      prefix = s_EMPTY_STRING;
    else if (foundPosValue == (currentRead - word.length()))
      suffix = s_EMPTY_STRING;

    int prefixSub = (foundPosValue - s_DEFAULT_SEARCH_VAL_3);
    if (prefix.empty())
    {
      switch (prefixSub)
      {
        case -2: prefix = data.substr(0, s_DEFAULT_SEARCH_VAL_1);         break;
        case -1: prefix = data.substr(0, s_DEFAULT_SEARCH_VAL_2);         break;
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

    string result;
    result.append(string("FILE: "));
    result.append(m_Path.filename().string());
    result.append(string("( "));
    result.append(to_string(foundPositions[j]));
    result.append(string(" ) : <"));
    result.append(prefix);
    result.append(string(">"));
    result.append(word);
    result.append(string("<"));
    result.append(suffix);
    result.append(string(">"));

    m_Results.push_back(result);
  }
}
//--------------------------------------------------------------------------------------------------
bool CFileParser::ComputePrefixSuffix(string &output, const string &input)
{
  output.clear();

  if (input.empty())
    return false;

  const unsigned suffixLength = input.length();
  for (unsigned i = 0; i < suffixLength; ++i)
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
void CFileParser::PrintSolution()
{
  cout << endl;
  for (const auto& it : m_Results)
    if (!it.empty())
      cout << it << endl;
}
//--------------------------------------------------------------------------------------------------

