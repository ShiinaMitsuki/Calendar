
// calendarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "calendar.h"
#include "calendarDlg.h"
#include "AddMatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcalendarDlg �Ի���




CcalendarDlg::CcalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CcalendarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	TimeChange = FALSE;
}

void CcalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, MatterList);
	DDX_Control(pDX, IDC_MATTER_CONTEXT, MatterContext);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, DateControl);
}

BEGIN_MESSAGE_MAP(CcalendarDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CcalendarDlg::OnBnClickedOk)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CcalendarDlg::OnMcnSelchangeMonthcalendar1)
//	ON_LBN_SELCHANGE(IDC_LIST1, &CcalendarDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CcalendarDlg::OnBnClickedDeleteButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &CcalendarDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, &CcalendarDlg::OnBnClickedModifyButton)
END_MESSAGE_MAP()


// CcalendarDlg ��Ϣ�������

BOOL CcalendarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(!CreateMatterDir())
	{
		OnOK();
	}

	CTime cur = CTime::GetCurrentTime();
	SelectDay = cur.Format(_T("%Y-%m-%d"));
	ShowMatter(SelectDay);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcalendarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcalendarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CcalendarDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddMatter *add = new CAddMatter;
	add->mod = FALSE;
	add->today = SelectDay;
	add->DoModal();

	ShowMatter(SelectDay);
}

void CcalendarDlg::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);

	CMonthCalCtrl* mcc = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR1);

	CTime time;
	TimeChange = TRUE;

	mcc->GetCurSel( time );
	CStdioFile temp(_T("temp"), CFile::modeCreate|CFile::modeWrite);
	SelectDay = time.Format("%Y-%m-%d");
	temp.WriteString(SelectDay);
	temp.Close();

	ShowMatter(SelectDay);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

BOOL CcalendarDlg::GetStatus()
{
	return TimeChange;
}

bool CcalendarDlg::CreateMatterDir()
{
	CString tempdir(_T("matter"));
	if(!PathIsDirectory(tempdir))
	{
		if(!CreateDirectory(tempdir, NULL))
		{
			CString temp1("create directory ");
			CString temp2("failed, now exists");
			AfxMessageBox(temp1+tempdir+temp2);
			return false;
		}
	}
	return true;
}

void CcalendarDlg::ShowMatter(CString Day)
{
	int times = 0;

	MatterList.ResetContent();
	MatterContext.SetWindowText(_T(""));

	CFileStatus status;
	CString sFile=_T("matter\\")+Day+_T(".txt");
	if (!CFile::GetStatus(sFile,status))
		return;
	
	CStdioFile MatterFile(_T("matter\\")+Day+_T(".txt"), CFile::typeBinary|CFile::modeRead);
	CString Line;
	while(MatterFile.ReadString(Line))
	{
		if(Line.GetLength() == 0)
			break;

		CString title, detail;
		TCHAR sign[] = (_T("\t"));
		AfxExtractSubString(title, Line, 0, *sign);
		AfxExtractSubString(detail, Line, 1,*sign);
		AllMatter[title] = detail;
		
		if(times == 0)
			MatterContext.SetWindowText(detail);
		MatterList.AddString(title);
		times++;
	}
}
//void CcalendarDlg::OnLbnSelchangeList1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString buf;
//	MatterList.GetText(MatterList.GetCurSel(), buf);
//	DeleteFromMatterFile(buf);
//}

void CcalendarDlg::OnBnClickedDeleteButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Cursel;
	int site = MatterList.GetCurSel();
	if(site < 0)
	{
		AfxMessageBox(_T("��ѡ��һ��Ҫɾ��������"));
		return;
	}
	MatterList.GetText(site, Cursel);
	DeleteFromMatterFile(Cursel);
}

BOOL CcalendarDlg::DeleteFromMatterFile(CString MatterTitle)
{
	CStdioFile temp(_T("matter\\")+SelectDay+_T(".txt"), CFile::typeBinary|CFile::modeRead);
	CStdioFile MatterFile(_T("matter\\")+SelectDay+_T(".txt.temp"), CFile::typeBinary|CFile::modeCreate|CFile::modeWrite);
	WORD unicodeFlag = 0xFEFF;
	MatterFile.Write((void*)&unicodeFlag, sizeof(WORD));
	CString buf;

	while(temp.ReadString(buf))
	{
		CString title;
		TCHAR sign[] = (_T("\t"));
		AfxExtractSubString(title, buf, 0, *sign);
		if(!StrCmp(MatterTitle, title))
			continue;
		MatterFile.WriteString(buf+_T("\n")); 
	}
	temp.Close();
	MatterFile.Close();
	DeleteFile(_T("matter\\")+SelectDay+_T(".txt"));
	MoveFile(_T("matter\\")+SelectDay+_T(".txt.temp"), _T("matter\\")+SelectDay+_T(".txt"));
	ShowMatter(SelectDay);
	
	typedef std::map<CString,CString>::iterator ITER;

	ITER iter=AllMatter.find(MatterTitle);
	AllMatter.erase(iter);

	return TRUE;
}
void CcalendarDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buf;
	MatterList.GetText(MatterList.GetCurSel(), buf);
	MatterContext.SetWindowText(AllMatter[buf]);
}
void CcalendarDlg::OnBnClickedModifyButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddMatter *modify = new CAddMatter;
	CString buf;
	int site = MatterList.GetCurSel();
	if(site < 0)
	{
		AfxMessageBox(_T("��ѡ��һ��Ҫ�޸ĵ�����"));
		return;
	}
	MatterList.GetText(site, buf);
	
	modify->title = buf;
	modify->context = AllMatter[buf];
	modify->today = SelectDay;
	modify->mod = TRUE;

	modify->DoModal();
	ShowMatter(SelectDay);
}
