#include <iostream>
#include <filesystem>
#include <queue>
#include <thread>
#include <mutex>
#include <fstream>
#include "IReader_i.h"
#include "SingleReader.h"
#include "Parser.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
//---------------- [ MAIN ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int main()
{
  const string location = "D:\\TRY\\EsetDirParserTEST1";
  const string word     = "void";

  unique_ptr< IReader > reader(new CSingleReader());

  CParser parser(location, word, *reader);

  parser.Parse(10);

  return 0;
}
//--------------------------------------------------------------------------------------------------