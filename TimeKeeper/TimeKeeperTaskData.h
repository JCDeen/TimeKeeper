#pragma once

class CTimeKeeperTaskData
{
public:
	CTimeKeeperTaskData(void);
	~CTimeKeeperTaskData(void);

	// All this is per task specific.

	CString m_csStartDateTime;		// Both Date and Time ( MM/DD/YY HH:MM AM/PM)
	CString m_csStopDateTime;		// Both Date and Time ( MM/DD/YY HH:MM AM/PM)
	CString m_csPayRateDollars;		// Dollars charged per work unit ($$/minutes or $$/hours or $$/day)
	CString m_csPayRateUnits;		// minutes or hours or day
	CString m_csTotalTime_Worked;	// Total time worked on this task in minutes.
	CString m_csTotalCost_Worked;	// Total cost with no discounts.
	CString m_csTotalCost_Billed;	// Total cost minus discounts.
	CString m_csTaskDescription;	// Notes to be displayed to client ...
	CString m_csTaskNotes_Internal;		// Private notes for internal use only; not for the client !
	CString m_csTask_DiscountDollars;	// Amount to be subtracted from Total CostWorked
	DWORD	m_dwTotalSeconds;			// 1 year = 31 556 926 seconds; DWORD can hold max value of about 36 years.
};
