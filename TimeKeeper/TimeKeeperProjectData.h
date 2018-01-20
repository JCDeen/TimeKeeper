#pragma once

// this data structure is for file or Project specific data.
class CTimeKeeperProjectData
{
public:
	CTimeKeeperProjectData(void);
	~CTimeKeeperProjectData(void);

	CString m_csCustomerName;
	CString m_csCustomerAddress; // Street Address, City, State & Zip
	CString m_csCustomerPhone;
	CString m_csCustomerEmail;
	CString m_csProjectName;
	CString m_csProjectDescription;
	int m_nTotalElapsedSeconds;
	float M_fTotalProjectCredits;
	float m_fTotalInvoiceAmount;
};
