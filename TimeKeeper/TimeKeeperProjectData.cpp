#include "StdAfx.h"
#include "TimeKeeperProjectData.h"

CTimeKeeperProjectData::CTimeKeeperProjectData(void)
{
}

CTimeKeeperProjectData::~CTimeKeeperProjectData(void)
{
}
/***
  // Open file "foo.dat"
  CFile* pFile = new CFile();
  ASSERT (pFile != NULL);
  if (!pFile->Open ("foo.dat", CFile::modeReadWrite | CFile::shareExclusive)) {
      // Handle error
      return;
  }

  // ------------------
  // Create archive ...
  bool bReading = false;  // ... for writing
  CArchive* pArchive = NULL;
  try
  {
    pFile->SeekToBegin();
    UINT uMode = (bReading ? CArchive::load : CArchive::store);
    pArchive = new CArchive (pFile, uMode);
    ASSERT (pArchive != NULL);
  }
  catch (CException* pException)
  {
    // Handle error
    return;
  }
  // ------------------
  // Assume CFoo represents an employee record that 
  // contains a couple of data members
    class CFoo
  {
    // Construction/destruction
    public:
      CFoo::CFoo();
      virtual CFoo::~CFoo();

    // Methods
    public:
      int serialize (CArchive* pArchive);

    // Data members
    public:
      CString  m_strName;  // employee name
      int      m_nId;      // employee id
  };
  // ------------------
  // We use CArchive's streaming operators << and >> to read/write the data 
  // members from/to the archive. CArchive knows how to serialize simple 
  // data types like int, float, DWORD, and objects like CString. The 
  // archive also knows whether it's in read or write mode. You can query 
  // its mode by calling CArchive::IsStoring(). CFoo's serialization 
  // method can then be written as: 

  int CFoo::serialize
    (CArchive* pArchive)
  {
    int nStatus = SUCCESS;

    // Serialize the object ...
    ASSERT (pArchive != NULL);
    try
    {
      if (pArchive->IsStoring()) {
         // Write employee name and id
         (*pArchive) << m_strName;
         (*pArchive) << m_nId;
      }
      else {
         // Read employee name and id
         (*pArchive) >> m_strName;
         (*pArchive) >> m_nId;
      }
    }
    catch (CException* pException)
    {
      nStatus = ERROR;
    }
    return (nStatus);
  }
  // ------------------
  // When you've finished serializing, you should clean up by closing the archive and datafile. 
  pArchive->Close();
  delete pArchive;
  pFile->Close();
  delete pFile();
***/

