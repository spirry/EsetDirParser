#ifndef MULTIREADER_H
#define MULTIREADER_H
//--------------------------------------------------------------------------------------------------
#include "IReader_i.h"
#include "compile.h"
//--------------------------------------------------------------------------------------------------
//-------- [ CMultiReader ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CMultiReader : public IReader
{

public:

  CMultiReader();
  CMultiReader(const CMultiReader &source);
  CMultiReader& operator = (const CMultiReader &source);

public:

  bool OpenRead(std::ifstream &file, const std::filesystem::path &path) override;
  const std::streamsize Read(std::ifstream &file, std::string &data, const std::streamsize count) override;
  void Close(std::ifstream &file) override;

};
//--------------------------------------------------------------------------------------------------
#endif // !MULTIREADER_H
//--------------------------------------------------------------------------------------------------
