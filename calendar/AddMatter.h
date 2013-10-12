#pragma once
#include "afxwin.h"


// CAddMatter �Ի���

class CAddMatter : public CDialog
{
	DECLARE_DYNAMIC(CAddMatter)

public:
	CAddMatter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddMatter();

// �Ի�������
	enum { IDD = IDD_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit MatterTitle;
	CEdit MatterContent;
	CString title;
	CString context;
	CString today;
	BOOL mod;
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CButton SaveButton;
	afx_msg void OnPaint();
	BOOL IsMatterExists(CString Matter);
};
