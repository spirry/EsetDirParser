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
int main(int argc, char** argv)
{
  CInputParser inputParser(argc, argv);

  const std::string& path = inputParser.GetPath();
  const std::string& word = inputParser.GetWord();

  //if (inputParser.CmdOptionExists(path) && inputParser.CmdOptionExists(word))
  {
    unique_ptr< IReader > reader(new CSingleReader());
    CParser parser(path, word, *reader);
    parser.Parse(__DEFAULT_THREADS_COUNT);
  }

  //const std::string& filename = input.getCmdOption("void");
  //if (!filename.empty())
  //{
  //  cout << "HERE" << endl;
  //}
  return 0;
}


  //string path;
  //string wordToFind;

  //const string location = "D:\\TRY\\TEST";
  //const string word     = "void";

  //cout << "---------- [ PATH PARSER ] ----------" << endl;
  //cout << "-------------------------------------" << endl;
  //cout << "Please enter the path : ";
  //cin  >> path;

  //if (path.empty())
  //{
  //  cout << "Path not entered, EXIT... ";
  //  return -1;
  //}    

  //cout << endl;
  //cout << "Please enter the word : ";
  //cin  >> wordToFind;

  //if (wordToFind.empty())
  //{
  //  cout << "Searched workd not entered, EXIT... ";
  //  return -1;
  //}    
  //cout << "-------------------------------------" << endl;

  //unique_ptr< IReader > reader(new CSingleReader());
  //CParser parser(location, word, *reader);
  //parser.Parse(__DEFAULT_THREADS_COUNT);

  //return 0;
//}
//--------------------------------------------------------------------------------------------------