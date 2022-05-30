#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include "compile.h"
//--------------------------------------------------------------------------------------------------
//-------- [ CInputParser ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CInputParser
{

public:

  CInputParser();
  void SetArguments(int &argc, char **argv);

  bool Build();

public:

  const std::string& GetPath() const;
  const std::string& GetWord() const;
  
private:

  bool BuildTokens();
  bool CheckInput();
  bool CheckOutput();

private:

  int                       m_Argc;
  char**                    m_Argv;
  std::vector <std::string> m_Tokens;

private:

  static const int s_DEFAULT_PARAM_COUNT;

};
//--------------------------------------------------------------------------------------------------
cpp_inline const std::string& CInputParser::GetPath() const
{
  if (m_Tokens.size() > 0)
    return m_Tokens[0];

  static const std::string empty_string("");
  return empty_string;
}
//--------------------------------------------------------------------------------------------------
cpp_inline const std::string& CInputParser::GetWord() const
{
  if (m_Tokens.size() > 1)
    return m_Tokens[1]; 

  static const std::string empty_string("");
  return empty_string;
}  
//--------------------------------------------------------------------------------------------------
#endif // INPUT_PARSER_H
//--------------------------------------------------------------------------------------------------

