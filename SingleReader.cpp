#include "SingleReader.h"
#include <mutex>
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
//-------- [ CSingleReader ] -----------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
CSingleReader::CSingleReader()
{
	c_empty_statement;
}
//--------------------------------------------------------------------------------------------------
CSingleReader::CSingleReader(const CSingleReader &source)
{
	(*this) = source;
}
//--------------------------------------------------------------------------------------------------
CSingleReader& CSingleReader::operator = (const CSingleReader &source)
{
	c_unused(source);
	return (*this);
}
//--------------------------------------------------------------------------------------------------
bool CSingleReader::OpenRead(ifstream &file, const filesystem::path &path)
{
  unique_lock< mutex > sync(m_DiskSync);
  return CMultiReader::OpenRead(file, path);
}
//--------------------------------------------------------------------------------------------------
const streamsize CSingleReader::Read(ifstream &file, string &data, const streamsize count)
{
  unique_lock< mutex > sync(m_DiskSync);
  return CMultiReader::Read(file, data, count);
}
//--------------------------------------------------------------------------------------------------
void CSingleReader::Close(ifstream &file)
{
  unique_lock< mutex > sync(m_DiskSync);
  return CMultiReader::Close(file);
}
//--------------------------------------------------------------------------------------------------