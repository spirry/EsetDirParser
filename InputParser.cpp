#include "InputParser.h"
#include <string>
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
//-------- [ CInputParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
CInputParser::CInputParser(int &argc, char **argv)
{
  bool ok = CheckInput(argc, argv);
  if (ok)
  {
    m_Tokens.clear();
    for (int i = 1; i < argc; ++i)
      m_Tokens.push_back(string(argv[i]));
  }
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::CheckInput(int &argc, char **argv)
{
  cout << endl;
  cout << "INFO: total number of arguments: " << argc;
  for (int i = 0; i < argc; i++)
    cout << endl << i << "argument: " << argv[i];

  cout << endl;
  if (GetPath().empty())
  {
    cout << "ERROR: no path selected " << endl;
    return false;
  }

  cout << endl;
  if (GetWord().empty())
  {
    cout << "ERROR: no word selected " << endl;
    return false;
  }

  if (argc < 3)
  {
    cout << endl << "ERROR: not enough parametrs, EXIT... " << endl;
    return false;
  }

  string testPath = "";
  string testWord = "";
  // Retrieve the (non-option) argument:
  if ((argc <= 1) || (argv[argc - 1] == NULL) || (argv[argc - 1][0] == '-'))
  {
    // there is NO input...
    cout << endl;
    cerr << "ERROR: no argument provided, EXIT..." << endl;
    return false;
  }
  else
  {  // there is an input...
    testPath = argv[argc - 2];
    testWord = argv[argc - 1];
  }

  // Debug:
  cout << endl;
  cout << endl;
  cout << "TEST: file path = " << testPath << endl;
  cout << "TEST: word      = " << testWord << endl;

  return true;
}
//--------------------------------------------------------------------------------------------------
const string& CInputParser::GetCmdOption(const std::string &option) const
{
  vector< string >::const_iterator itr;
  itr = find(m_Tokens.begin(), m_Tokens.end(), option);
  if (itr != m_Tokens.end() && ++itr != m_Tokens.end())
    return *itr;

  static const string empty_string("");
  return empty_string;
}
//--------------------------------------------------------------------------------------------------
bool CInputParser::CmdOptionExists(const string &option) const
{
  if (option.empty())
    return false;

  return (find(m_Tokens.begin(), m_Tokens.end(), option) != m_Tokens.end());
}
//--------------------------------------------------------------------------------------------------