
// NJUDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NJU.h"
#include "NJUDlg.h"
#include "afxdialogex.h"
#include "InputInfo_Dlg.h"
#include "Wait.h"
#include "ChangePW.h"
#include "About.h"
#include "Service.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int now_status = 0; //δ��¼
char new_username[MAX_ID_LENGTH];
char new_password[MAX_PASSWORD_LENGTH];
extern char *info_file_loc;
extern char *user_file_loc;
extern char *pw_file_loc;
extern char *serv1;
extern char *serv2;
status *new_status = new status;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CNJUDlg �Ի���

CNJUDlg::CNJUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NJU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNJUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNJUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CNJUDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNJUDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CNJUDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNJUDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT3, &CNJUDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON3, &CNJUDlg::OnBnClickedButton3)
	ON_COMMAND(ID_32784, &CNJUDlg::On32784)
	ON_COMMAND(ID_32785, &CNJUDlg::On32785)
	ON_COMMAND(ID_32787, &CNJUDlg::On32787)
	ON_COMMAND(ID_32788, &CNJUDlg::On32788)
	ON_COMMAND(ID_32789, &CNJUDlg::On32789)
	ON_COMMAND(ID_32790, &CNJUDlg::On32790)
	ON_COMMAND(ID_32791, &CNJUDlg::On32791)
END_MESSAGE_MAP()


// CNJUDlg ��Ϣ�������

BOOL CNJUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetWindowSkin(m_hWnd, "Dialog");  //�����ص㣬m_hWnd ��������Ի���Ĵ��ھ��
	SetDialogSkin("Dialog");  //��Ϊ�˸����Ժ�ĶԻ������Ƥ����!
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	FILE *fp1 = fopen(info_file_loc, "a");
	FILE *fp2 = fopen(user_file_loc, "a");
	FILE *fp3 = fopen(pw_file_loc, "a");
	fclose(fp1); fclose(fp2); fclose(fp3);

	if (!file_is_empty("data\\user.nju"))
	{
		char *username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
		char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
		read_info(username, password);
		CString s1(username);
		CString s2(password);
		/*
		CEdit *p = (CEdit*)GetDlgItem(IDC_EDIT1);
		p->SetWindowText((LPCTSTR)s1);
		CEdit *p2 = (CEdit*)GetDlgItem(IDC_EDIT2);
		p2->SetWindowText((LPCTSTR)s2);
		*/
		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		login();
		Msgdlg->DestroyWindow();

		read_status();
		if (!(new_status->successful == 1 || new_status->successful == 6))
		{
			now_status = 0;
			if (new_status->successful == 3)
			{
				CString s_fail(_T("��¼ʧ�ܣ��û������������"));
				CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_fail->SetWindowText((LPCTSTR)s_fail);
			}
			else
			{
				CString s_fail(_T("��¼ʧ�ܣ�δ֪���������ԣ�"));
				CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_fail->SetWindowText((LPCTSTR)s_fail);
			}
			GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
			GetDlgItem(IDC_EDIT8)->SetWindowText(_T(""));
		}
		else
		{
			//AfxMessageBox(_T("123"));
			now_status = 1;
			if (new_status->successful == 6)
			{
				CString s_succ(_T("��¼�ɹ���֮ǰ�ѵ�¼����"));
				CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_succ->SetWindowText((LPCTSTR)s_succ);
			}
			else {
				CString s_succ(_T("��¼�ɹ���"));
				CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_succ->SetWindowText((LPCTSTR)s_succ);
				strcpy(new_username, username);
				strcpy(new_password, password);
			}
			CString s_username(new_status->username);
			CEdit *p_name = (CEdit*)GetDlgItem(IDC_EDIT4);
			p_name->SetWindowText((LPCTSTR)s_username);
			CString s_num;
			s_num.Format(_T("%d"), new_status->device_amounts);
			CEdit *p_num = (CEdit*)GetDlgItem(IDC_EDIT7);
			p_num->SetWindowText((LPCTSTR)s_num);
			CString s_rest;
			s_rest.Format(_T("%.2fԪ"), new_status->account_balance);
			CEdit *p_rest = (CEdit*)GetDlgItem(IDC_EDIT5);
			p_rest->SetWindowText((LPCTSTR)s_rest);
			CString s_time;
			s_time.Format(_T("%dСʱ%d����"), new_status->hours, new_status->mins);
			CEdit *p_time = (CEdit*)GetDlgItem(IDC_EDIT6);
			p_time->SetWindowText((LPCTSTR)s_time);
			if (strcmp(serv1, new_status->service) == 0)
			{
				//LLMARK��ѧ���˷������δ��ȡ��
				CString s_serv;
				s_serv.Format(_T("ѧ����׼��ʱ����/1�ն�"), new_status->hours, new_status->mins);
				CEdit *p_serv = (CEdit*)GetDlgItem(IDC_EDIT8);
				p_serv->SetWindowText((LPCTSTR)s_serv);
			}
			else if (strcmp(serv2, new_status->service) == 0)
			{
				CString s_serv;
				s_serv.Format(_T("ѧ��2�ն˼�ʱ����/2�ն�"), new_status->hours, new_status->mins);
				CEdit *p_serv = (CEdit*)GetDlgItem(IDC_EDIT8);
				p_serv->SetWindowText((LPCTSTR)s_serv);
			}
		}
		CString s_butt;
		if (now_status == 0)
			s_butt.Format(_T("���µ�¼"));
		else
			s_butt.Format(_T("�ǳ�"));
		CEdit *p_butt = (CEdit*)GetDlgItem(IDC_BUTTON3);
		p_butt->SetWindowText((LPCTSTR)s_butt);
		free(username);
		free(password);
	}
	else
	{
		InputInfo_Dlg *p = new InputInfo_Dlg;
		p->Create(IDD_DIALOG1, this);
		p->ShowWindow(SW_SHOW);
	}
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNJUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNJUDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNJUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNJUDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CNJUDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CNJUDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CNJUDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CNJUDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CNJUDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (now_status == 1) {
		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		logout();
		Msgdlg->DestroyWindow();
		clean_status();
		CString s_fail(_T("���˳���¼��"));
		CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
		p_fail->SetWindowText((LPCTSTR)s_fail);
		GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT8)->SetWindowText(_T(""));
	}
	else
	{
		Wait* Msgdlg = new Wait;
		Msgdlg->Create(IDD_DIALOG2, this);
		Msgdlg->UpdateData(FALSE);
		Msgdlg->ShowWindow(SW_SHOW);
		Msgdlg->RedrawWindow();
		login();
		Msgdlg->DestroyWindow();

		read_status();
		if (new_status->successful == 1 || new_status->successful == 6) {
			if (new_status->successful == 6)
			{
				CString s_succ(_T("��¼�ɹ���֮ǰ�ѵ�¼����"));
				CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_succ->SetWindowText((LPCTSTR)s_succ);
			}
			else {
				CString s_succ(_T("��¼�ɹ���"));
				CEdit *p_succ = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_succ->SetWindowText((LPCTSTR)s_succ);
			}
			CString s_username(new_status->username);
			CEdit *p_name = (CEdit*)GetDlgItem(IDC_EDIT4);
			p_name->SetWindowText((LPCTSTR)s_username);
			CString s_num;
			s_num.Format(_T("%d"), new_status->device_amounts);
			CEdit *p_num = (CEdit*)GetDlgItem(IDC_EDIT7);
			p_num->SetWindowText((LPCTSTR)s_num);
			CString s_rest;
			s_rest.Format(_T("%.2fԪ"), new_status->account_balance);
			CEdit *p_rest = (CEdit*)GetDlgItem(IDC_EDIT5);
			p_rest->SetWindowText((LPCTSTR)s_rest);
			CString s_time;
			s_time.Format(_T("%dСʱ%d����"), new_status->hours, new_status->mins);
			CEdit *p_time = (CEdit*)GetDlgItem(IDC_EDIT6);
			p_time->SetWindowText((LPCTSTR)s_time);
			if (strcmp(serv1, new_status->service) == 0)
			{
				//LLMARK��ѧ���˷������δ��ȡ��
				CString s_serv;
				s_serv.Format(_T("ѧ����׼��ʱ����/1�ն�"), new_status->hours, new_status->mins);
				CEdit *p_serv = (CEdit*)GetDlgItem(IDC_EDIT8);
				p_serv->SetWindowText((LPCTSTR)s_serv);
			}
			else if (strcmp(serv2, new_status->service) == 0)
			{
				CString s_serv;
				s_serv.Format(_T("ѧ��2�ն˼�ʱ����/2�ն�"), new_status->hours, new_status->mins);
				CEdit *p_serv = (CEdit*)GetDlgItem(IDC_EDIT8);
				p_serv->SetWindowText((LPCTSTR)s_serv);
			}
		}
		else
		{
			if (new_status->successful == 3)
			{
				CString s_fail(_T("��¼ʧ�ܣ��û������������"));
				CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_fail->SetWindowText((LPCTSTR)s_fail);
			}
			else
			{
				CString s_fail(_T("��¼ʧ�ܣ�δ֪���������ԣ�"));
				CEdit *p_fail = (CEdit*)GetDlgItem(IDC_EDIT3);
				p_fail->SetWindowText((LPCTSTR)s_fail);
			}
		}
	}
	now_status = (new_status->successful == 1) ? 1 : 0;
	CString s_butt;
	if (now_status == 0)
		s_butt.Format(_T("���µ�¼"));
	else
		s_butt.Format(_T("�ǳ�"));
	CEdit *p_butt = (CEdit*)GetDlgItem(IDC_BUTTON3);
	p_butt->SetWindowText((LPCTSTR)s_butt);
}

void CNJUDlg::On32784()
{
	// TODO: �ڴ���������������
	if (now_status == 1) {
		AfxMessageBox(_T("�����˳���¼��"));
	}
	else {
		InputInfo_Dlg *p = new InputInfo_Dlg;
		p->Create(IDD_DIALOG1, this);
		p->ShowWindow(SW_SHOW);
	}
}


void CNJUDlg::On32785()
{
	// TODO: �ڴ���������������
	AfxMessageBox(_T("���ڿ�����..."));
}


void CNJUDlg::On32787()
{
	// TODO: �ڴ���������������
	if (now_status == 1) {
		ChangePW *p = new ChangePW;
		p->Create(IDD_DIALOG3, this);
		p->ShowWindow(SW_SHOW);
	}
	else
	{
		AfxMessageBox(_T("���ȵ�¼��"));	
		InputInfo_Dlg *p = new InputInfo_Dlg;
		p->Create(IDD_DIALOG1, this);
		p->ShowWindow(SW_SHOW);
	}
}


void CNJUDlg::On32788()
{
	// TODO: �ڴ���������������
	if (now_status == 0) {
		AfxMessageBox(_T("���ȵ�¼��"));
		InputInfo_Dlg *p = new InputInfo_Dlg;
		p->Create(IDD_DIALOG1, this);
		p->ShowWindow(SW_SHOW);
	}
	else {
		Service *p = new Service;
		p->Create(IDD_DIALOG5, this);
		p->ShowWindow(SW_SHOW);
	}
}


void CNJUDlg::On32789()
{
	// TODO: �ڴ���������������
	char *github_url = "https://github.com/triumphalLiu/NJU_Campus_Net_Client_v2";
	AfxMessageBox(_T("������ת��Ŀ����վ"));
	ShellExecute(NULL, "open", github_url, NULL, NULL, SW_MINIMIZE);
}


void CNJUDlg::On32790()
{
	// TODO: �ڴ���������������
	AfxMessageBox(_T("���������°汾������վ"));
}


void CNJUDlg::On32791()
{
	// TODO: �ڴ���������������
	About *p = new About;
	p->Create(IDD_DIALOG4, this);
	p->ShowWindow(SW_SHOW);
}
