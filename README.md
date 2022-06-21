# EsetDirParser

Input: Application will receive two command line parameter. First is path, either to file or folder. Second is string to be
searched for (maximum length 128).

Output: Print to stdout lines in format “<file>(<position>): <prefix>…<suffix>”. Where <file> is the name of file containing the
string, <position> is offset in that file where string started (zero based), <prefix> is three characters in front of the match,
similarly <suffix> is three characters after the match. When there are not enough characters for whole prefix or suffix (at
beginning or end of the file) use as many as there are available. In prefix and suffix tabs should be printed as “\t” and newlines
as “\n”.
  
You may assume that path points either to single text file or folder with just another folders and text files (your application
must recursively traverse and process all subfolders). The application must not crash for any reason (error handling). So, if
there are not enough command line arguments you should print something sensible and exit. The same is true when the input
path cannot be opened, etc.
  
The solution must be multithreaded in processing the data.
