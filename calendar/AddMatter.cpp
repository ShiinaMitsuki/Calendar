// AddMatter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "calendar.h"
#include "AddMatter.h"
#include "calendarDlg.h"


// CAddMatter �Ի���

IMPLEMENT_DYNAMIC(CAddMatter, CDialog)

CAddMatter::CAddMatter(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMatter::IDD, pParent)
{

}

CAddMatter::~CAddMatter()
{
}

void CAddMatter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_TITLE, MatterTitle);
	DDX_Control(pDX, IDC_INPUT_CONTENT, MatterContent);
	DDX_Control(pDX, IDOK, SaveButton);
}


BEGIN_MESSAGE_MAP(CAddMatter, CDialog)
	ON_BN_CLICKED(IDOK, &CAddMatter::OnBnClickedOk)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAddMatter ��Ϣ�������

void CAddMatter::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(mod)
	{
		CStdioFile temp(_T("matter\\")+today+_T(".txt"), CFile::typeBinary|CFile::modeRead);
		CStdioFile MatterFile(_T("matter\\")+today+_T(".txt.temp"), CFile::typeBinary|CFile::modeCreate|CFile::modeWrite);
		WORD unicodeFlag = 0xFEFF;
		MatterFile.Write((void*)&unicodeFlag, sizeof(WORD));
		CString buf;
		CString NewTitle;
		MatterTitle.GetWindowText(NewTitle);

		while(temp.ReadString(buf))
		{
			CString ti;
			TCHAR sign[] = (_T("\t"));
			AfxExtractSubString(ti, buf, 0, *sign);
			if(!StrCmp(NewTitle, ti))
			{
				CString con;
				MatterContent.GetWindowText(con);
				buf = NewTitle+_T("\t")+con;
			}
			MatterFile.WriteString(buf+_T("\n")); 
		}
		temp.Close();
		MatterFile.Close();
		DeleteFile(_T("matter\\")+today+_T(".txt"));
		MoveFile(_T("matter\\")+today+_T(".txt.temp"), _T("matter\\")+today+_T(".txt"));
		AfxMessageBox(_T("�޸ĳɹ�"));

		return;
	}

	CString content, title;
	MatterContent.GetWindowText(content);
	MatterTitle.GetWindowText(title);

	//�жϽ����Ƿ���ͬ����ʱ�����
	if(IsMatterExists(title))
		return;

	CString buf;
	CFileStatus status;
	
	if (CFile::GetStatus(_T("temp"),status))
	{

		CStdioFile temp(_T("temp"), CFile::modeRead);
		temp.ReadString(buf);
		temp.Close();
		DeleteFile(_T("temp"));
	}
	else
	{
		CTime cur = CTime::GetCurrentTime();
		buf = cur.Format(_T("%Y-%m-%d"));
	}
	
	CStdioFile matter(_T("matter\\")+buf+_T(".txt"), CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate|CFile::typeBinary);
	matter.SeekToEnd();
	WORD unicodeFlag = 0xFEFF;
	CString a = title + _T("\t") + content + _T("\n");
	matter.Write((void*)&unicodeFlag, sizeof(WORD));
	matter.WriteString(a);  
	matter.Close();
	AfxMessageBox(_T("����ɹ�"));
}


int CAddMatter::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CAddMatter::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	MatterTitle.SetWindowText(title);
	MatterContent.SetWindowText(context);
	if(mod)
	{

		MatterTitle.SetReadOnly(TRUE);
		SaveButton.SetWindowText(_T("�޸�"));
	}
	else
		SaveButton.SetWindowText(_T("����"));
}

BOOL CAddMatter::IsMatterExists(CString Matter)
{
	CStdioFile tmp(_T("matter\\")+today+_T(".txt"), CFile::typeBinary|CFile::modeRead);
	CString buf;

	while(tmp.ReadString(buf))
	{
		CString temp_title;
		TCHAR sign[] = (_T("\t"));
		AfxExtractSubString(temp_title, buf, 0, *sign);
		if(!StrCmp(temp_title, Matter))
		{
			AfxMessageBox(_T("������¼��Ѿ����ڣ�����Ե���༭�����޸�"));
			return TRUE;
		}
	}
	return FALSE;
}