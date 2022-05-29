#ifndef SINGLEREADER_H
#define SINGLEREADER_H
//--------------------------------------------------------------------------------------------------
#include <mutex>
#include "MultiReader.h"
//--------------------------------------------------------------------------------------------------
//-------- [ CSingleReader ] -----------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CSingleReader : public CMultiReader
{
  
public:

  CSingleReader();
  CSingleReader(const CSingleReader &source);
  CSingleReader& operator = (const CSingleReader &source);

public:

  bool OpenRead(std::ifstream &file, const std::filesystem::path &path) override;
  std::streamsize Read(std::ifstream &file, std::string &data, std::streamsize count) override;
  void Close(std::ifstream &file) override;

private:

  std::mutex m_DiskSync;

};
//--------------------------------------------------------------------------------------------------
#endif // SINGLEREADER_H
//--------------------------------------------------------------------------------------------------

