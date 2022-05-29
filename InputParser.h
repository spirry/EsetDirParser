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

  CInputParser(int &argc, char **argv);

public:

  const std::string& GetPath() const;
  const std::string& GetWord() const;

  const std::string& GetCmdOption(const std::string& option) const;
  bool CmdOptionExists(const std::string& option) const;
  
private:

  bool CheckInput(int &argc, char **argv);

private:

  std::vector <std::string> m_Tokens;

};
//--------------------------------------------------------------------------------------------------
cpp_inline const std::string& CInputParser::GetPath() const
{
  if (m_Tokens.size() > 1)
    return m_Tokens[0];

  static const std::string empty_string("");
  return empty_string;
}
//--------------------------------------------------------------------------------------------------
cpp_inline const std::string& CInputParser::GetWord() const
{
  if (m_Tokens.size() > 2)
    return m_Tokens[1]; 

  static const std::string empty_string("");
  return empty_string;
}  
//--------------------------------------------------------------------------------------------------
#endif // INPUT_PARSER_H
//--------------------------------------------------------------------------------------------------

