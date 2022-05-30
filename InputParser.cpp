#include "InputParser.h"
#include "compile.h"
#include <string>
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
const int CInputParser::s_DEFAULT_PARAM_COUNT = 3;
//--------------------------------------------------------------------------------------------------
//-------- [ CInputParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
CInputParser::CInputParser()
{
  m_Argc = -1;
  m_Argv = NULL;
}
//--------------------------------------------------------------------------------------------------
void CInputParser::SetArguments(int &argc, char **argv)
{
  m_Argc = argc;
  m_Argv = argv;
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::Build()
{
  bool 

  ok =       BuildTokens();
  ok = ok && CheckInput();
  ok = ok && CheckOutput();

  return ok;
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::BuildTokens()
{
  m_Tokens.clear();
  for (int i = 1; i < m_Argc; ++i)
    m_Tokens.push_back(string(m_Argv[i]));

  return true;
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::CheckInput()
{
  cout << endl;
  cout << "INFO: Check input " << endl;
  cout << "INFO: total number of arguments: " << m_Argc;
  for (int i = 0; i < m_Argc; i++)
    cout << endl << "[ " << i << " ]"<< "[ argument ] : " << m_Argv[i];

  //verify argc count
  if (m_Argc < s_DEFAULT_PARAM_COUNT)
  {
    if (GetPath().empty())
    {
      cout << endl;
      cout << "ERROR: No path selected, EXIT... " << endl;
      return false;
    }

    if (GetWord().empty())
    {
      cout << endl;
      cout << "ERROR: No word selected, EXIT... " << endl;
      return false;
    }

    return false;
  }

  string testPath = "";
  string testWord = "";
  if ((m_Argc <= 1) || (m_Argv[m_Argc - 1] == NULL) || (m_Argv[m_Argc - 1][0] == '-') || (m_Argv[m_Argc - 1][0] == ' '))
  {
    // there is NO input...
    cout << endl;
    cerr << "ERROR: No argument provided, EXIT..." << endl;
    return false;
  }
  else
  {  // there is an input...
    testPath = m_Argv[m_Argc - 2];
    testWord = m_Argv[m_Argc - 1];
  }

  //found a space in PATH
  const size_t foundSpace = testPath.find(" ");
  if (foundSpace != string::npos)
  {
    cout << endl;
    cout << "ERROR : Found a space in location path at  " << foundSpace << " position!!" << endl;
    cout << "INFO  : Please provide a valid path and try again " << endl;
    return false;
  }

  // Debug
  cout << endl;
  cout << endl;
  cout << "TEST: file path = " << testPath << endl;
  cout << "TEST: word      = " << testWord << endl;
  cout << endl;

  return true;
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::CheckOutput()
{
  cout << "INFO: Check Output " << endl;
  
  bool ok = (!GetPath().empty() || !GetWord().empty());
  const string outStr = C_CHOICE(ok, string("OK"), string("FAILED"));
  cout << "INFO: Output is " << outStr << endl;
  
  return ok;
}
//--------------------------------------------------------------------------------------------------