#include "MultiReader.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
//-------- [ CMultiReader ] ------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
CMultiReader::CMultiReader()
{
	c_empty_statement;
}
//--------------------------------------------------------------------------------------------------
CMultiReader::CMultiReader(const CMultiReader &source)
{
	(*this) = source;
}
//--------------------------------------------------------------------------------------------------
CMultiReader& CMultiReader::operator = (const CMultiReader &source)
{
	c_unused(source);
	return (*this);
}
//--------------------------------------------------------------------------------------------------
bool CMultiReader::OpenRead(ifstream &file, const filesystem::path &path)
{
  file.open(path.string(), ios::in | ios::binary);
  return file.is_open();
}
//--------------------------------------------------------------------------------------------------
streamsize CMultiReader::Read(ifstream &file, string &data, streamsize count)
{
  data.resize(count);

  file.read(data.data(), count);

  if (file.bad())
    return 0;

  return file.gcount();
}
//--------------------------------------------------------------------------------------------------
void CMultiReader::Close(ifstream &file)
{
  file.close();
}
//--------------------------------------------------------------------------------------------------