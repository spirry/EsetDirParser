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
#define __DEFAULT_THREADS_COUNT 10
//--------------------------------------------------------------------------------------------------
//---------------- [ MAIN ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int main()
{
  string path;
  string wordToFind;

  //const string location = "D:\\TRY\\EsetDirParserTEST1";
  //const string word     = "void";

  cout << "---------- [ PATH PARSER ] ----------" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Please enter the path : ";
  cin  >> path;

  if (path.empty())
  {
    cout << "Path not entered, EXIT... ";
    return -1;
  }    

  cout << endl;
  cout << "Please enter the word : ";
  cin  >> wordToFind;

  if (wordToFind.empty())
  {
    cout << "Searched workd not entered, EXIT... ";
    return -1;
  }    
  cout << "-------------------------------------" << endl;

  unique_ptr< IReader > reader(new CSingleReader());
  CParser parser(path, wordToFind, *reader);
  parser.Parse(__DEFAULT_THREADS_COUNT);

  return 0;
}
//--------------------------------------------------------------------------------------------------