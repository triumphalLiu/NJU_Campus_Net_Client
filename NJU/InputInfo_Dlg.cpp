// InputInfo_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NJU.h"
#include "InputInfo_Dlg.h"
#include "NJUDlg.h"
#include "afxdialogex.h"
#include "Wait.h"

extern char new_username[MAX_ID_LENGTH];
extern char new_password[MAX_PASSWORD_LENGTH];
extern int now_status; 
extern status *new_status;
extern char *info_file_loc;
extern char *user_file_loc;
extern char *pw_file_loc;
extern char *serv1;
extern char *serv2;
// InputInfo_Dlg �Ի���

IMPLEMENT_DYNAMIC(InputInfo_Dlg, CDialogEx)

InputInfo_Dlg::InputInfo_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

InputInfo_Dlg::~InputInfo_Dlg()
{
}

void InputInfo_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputInfo_Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputInfo_Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &InputInfo_Dlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// InputInfo_Dlg ��Ϣ�������

//��ȡ�༭�����ݣ�����¼
void InputInfo_Dlg::OnBnClickedOk()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT1, strTemp);
	char szTemp[128];
	memset(szTemp, 0, sizeof(szTemp));
	strcpy(szTemp, (char *)(strTemp.GetBuffer(strTemp.GetLength())));
	CString strTemp2;
	GetDlgItemText(IDC_EDIT2, strTemp2);
	char szTemp2[128];
	memset(szTemp2, 0, sizeof(szTemp2));
	strcpy(szTemp2, (char *)(strTemp2.GetBuffer(strTemp2.GetLength())));

	if (strTemp.IsEmpty() || strTemp2.IsEmpty())
	{
		AfxMessageBox(_T("�û���������Ϊ�գ�"));
		return;
	}

	Wait* Msgdlg = new Wait;
	Msgdlg->Create(IDD_DIALOG2, this);
	Msgdlg->UpdateData(FALSE);
	Msgdlg->ShowWindow(SW_SHOW);
	Msgdlg->RedrawWindow();

	now_status = 0;
	char *old_username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
	char *old_password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
	read_info(old_username, old_password);
	strcpy(new_username, "\0");
	strcpy(new_password, "\0");
	strcpy(new_username, szTemp);
	strcpy(new_password, szTemp2);
	save_user();
	login();	
	Msgdlg->DestroyWindow();
	clean_status();
	read_status();
	if (!(new_status->successful == 1 || new_status->successful == 6))
	{
		now_status = 0;
		if (new_status->successful == 3)
		{
			CString s_fail(_T("��¼ʧ�ܣ��û������������"));
			CEdit *p_fail = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT3);
			p_fail->SetWindowText((LPCTSTR)s_fail);
			AfxMessageBox(_T("��¼ʧ�ܣ��û������������"));
		}
		else
		{
			CString s_fail(_T("��¼ʧ�ܣ�δ֪���������ԣ�"));
			CEdit *p_fail = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT3);
			p_fail->SetWindowText((LPCTSTR)s_fail);
			AfxMessageBox(_T("��¼ʧ�ܣ�δ֪���������ԣ�"));
		}
		GetParent()->GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT8)->SetWindowText(_T(""));
		strcpy(new_username, old_username);
		strcpy(new_password, old_password);
		save_password(old_password, pw_file_loc);
		save_password(old_username, user_file_loc);
		return;
	}
	else
	{
		now_status = 1;
		//AfxMessageBox(_T("123"));
		CString s_succ(_T("��¼�ɹ���"));
		CEdit *p_succ = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT3);
		p_succ->SetWindowText((LPCTSTR)s_succ);
		CString s_username(new_status->username);
		CEdit *p_name = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT4);
		p_name->SetWindowText((LPCTSTR)s_username);
		CString s_num;
		s_num.Format(_T("%d"), new_status->device_amounts);
		CEdit *p_num = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT7);
		p_num->SetWindowText((LPCTSTR)s_num);
		CString s_rest;
		s_rest.Format(_T("%.2fԪ"), new_status->account_balance);
		CEdit *p_rest = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT5);
		p_rest->SetWindowText((LPCTSTR)s_rest);
		CString s_time;
		s_time.Format(_T("%dСʱ%d����"), new_status->hours, new_status->mins);
		CEdit *p_time = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT6);
		p_time->SetWindowText((LPCTSTR)s_time);
		if (strcmp(serv1, new_status->service) == 0)
		{
			//LLMARK��ѧ���˷������δ��ȡ��
			CString s_serv;
			s_serv.Format(_T("ѧ����׼��ʱ����/1�ն�"), new_status->hours, new_status->mins);
			CEdit *p_serv = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT8);
			p_serv->SetWindowText((LPCTSTR)s_serv);
		}
		else if(strcmp(serv2, new_status->service) == 0)
		{
			CString s_serv;
			s_serv.Format(_T("ѧ��2�ն˼�ʱ����/2�ն�"), new_status->hours, new_status->mins);
			CEdit *p_serv = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT8);
			p_serv->SetWindowText((LPCTSTR)s_serv);
		}
	}
	CString s_butt;
	if (now_status == 0)
	{
		s_butt.Format(_T("���µ�¼"));
	}
	else
		s_butt.Format(_T("�ǳ�"));
	CEdit *p_butt = (CEdit*)GetParent()->GetDlgItem(IDC_BUTTON3);
	p_butt->SetWindowText((LPCTSTR)s_butt);

	EndDialog(0);
}


void InputInfo_Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}