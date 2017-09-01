// uart_testDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_UART_TESTDLG_H__B5F17D25_B336_4F4C_AC93_86A9F28E4358__INCLUDED_)
#define AFX_UART_TESTDLG_H__B5F17D25_B336_4F4C_AC93_86A9F28E4358__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUart_testDlg dialog

class CUart_testDlg : public CDialog
{
// Construction
public:
	CUart_testDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUart_testDlg)
	enum { IDD = IDD_UART_TEST_DIALOG };
	CButton	m_BUTsend;
	CButton	m_BUTON;
	CString	m_EDITTX;
	CMSComm	m_COMM1;
	CString	m_RX;
	CString	m_ID;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUart_testDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUart_testDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Ontest();
	afx_msg void Onsendtest();
	afx_msg void OnButon();
	afx_msg void OnBUTsend();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnclearRX();
	afx_msg void OnReadId();
	afx_msg void OnWriteID();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UART_TESTDLG_H__B5F17D25_B336_4F4C_AC93_86A9F28E4358__INCLUDED_)
