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
  cout << "INFO: Open for read operation " << endl;
  file.open(path.string(), ios::in | ios::binary);
  return file.is_open();
}
//--------------------------------------------------------------------------------------------------
streamsize CMultiReader::Read(ifstream &file, string &data, streamsize count)
{
  cout << "INFO: Read from file with buffer = " << count << endl;
  data.resize(static_cast<const unsigned int>(count));

  file.read(data.data(), count);

  if (file.bad())
    return 0;

  return file.gcount();
}
//--------------------------------------------------------------------------------------------------
void CMultiReader::Close(ifstream &file)
{
  cout << "INFO: Close file " << endl;
  file.close();
}
//--------------------------------------------------------------------------------------------------