
// calendarDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <map>
#include "afxdtctl.h"


// CcalendarDlg �Ի���
class CcalendarDlg : public CDialog
{
// ����
public:
	CcalendarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL GetStatus();
	BOOL TimeChange;
	bool CreateMatterDir();
	void ShowMatter(CString SelectDay);
	CListBox MatterList;
	std::map<CString, CString> AllMatter;
	CEdit MatterContext;
//	afx_msg void OnLbnSelchangeList1();
	CString SelectDay;
	CMonthCalCtrl DateControl;
	BOOL DeleteFromMatterFile(CString MatterTitle);
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedModifyButton();
};
