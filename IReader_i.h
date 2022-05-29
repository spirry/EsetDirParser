#ifndef I_READER_H
#define I_READER_H
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <filesystem>
#include <fstream>
//--------------------------------------------------------------------------------------------------
//-------- [ IReader ] -----------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class IReader
{
    
protected:

  IReader();
  IReader(const IReader &source);
  IReader& operator = (const IReader &source);

public:

  virtual bool OpenRead(std::ifstream &file, const std::filesystem::path &path)               = 0;
  virtual std::streamsize Read(std::ifstream &file, std::string &data, std::streamsize count) = 0;
  virtual void Close(std::ifstream &file)                                                     = 0;
  virtual ~IReader();

};
//--------------------------------------------------------------------------------------------------
#endif // I_READER_H
//--------------------------------------------------------------------------------------------------