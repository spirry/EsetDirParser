#include <iostream>
#include <filesystem>
#include <queue>
#include <thread>
#include <mutex>
#include <fstream>
#include <conio.h>
#include "IReader_i.h"
#include "SingleReader.h"
#include "Parser.h"
#include "InputParser.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
#define __DEFAULT_THREADS_COUNT 10
//--------------------------------------------------------------------------------------------------
//---------------- [ MAIN ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
  CInputParser inputParser;
  inputParser.SetArguments(argc, argv);
  bool ok = inputParser.Build();
  if (ok)
  {
    const std::string& path = inputParser.GetPath();
    const std::string& word = inputParser.GetWord();

    //TEST
    //const std::string path = "D:\\TRY\\TEST";
    //const std::string word = "void";

    unique_ptr< IReader > reader(new CSingleReader());
    CParser parser(path, word, *reader);
    parser.Parse(__DEFAULT_THREADS_COUNT);

    return 0;
  }

  return -1;
}
//--------------------------------------------------------------------------------------------------