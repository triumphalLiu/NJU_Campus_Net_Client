// ChangePW.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NJU.h"
#include "ChangePW.h"
#include "afxdialogex.h"
#include "Wait.h"
extern char *pw_file_loc;
extern char *old_file_loc;
extern char new_password[MAX_PASSWORD_LENGTH];
// ChangePW �Ի���

IMPLEMENT_DYNAMIC(ChangePW, CDialogEx)

ChangePW::ChangePW(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

ChangePW::~ChangePW()
{
}

void ChangePW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangePW, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChangePW::OnBnClickedButton1)
END_MESSAGE_MAP()


// ChangePW ��Ϣ�������


void ChangePW::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����ԭ����
	char *username = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
	char *password = (char *)malloc(MAX_PASSWORD_LENGTH * sizeof(char));
	read_info(username, password);
	save_password(password, old_file_loc);
	//��ȡ��������ݲ����浽pw.nju
	CString strTemp;
	GetDlgItemText(IDC_EDIT1, strTemp);
	char szTemp[128];
	memset(szTemp, 0, sizeof(szTemp));
	strcpy(szTemp, (char *)(strTemp.GetBuffer(strTemp.GetLength())));
	if (strTemp.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ�գ�"));
		return;
	}

	char *save = (char *)malloc(sizeof(szTemp));
	strcpy(save, strTemp);
	save_password(save, pw_file_loc);

	//AfxMessageBox(strTemp);

	//�򿪵ȴ���
	Wait* Msgdlg = new Wait;
	Msgdlg->Create(IDD_DIALOG2, this);
	Msgdlg->UpdateData(FALSE);
	Msgdlg->ShowWindow(SW_SHOW);
	Msgdlg->RedrawWindow();
	//�޸�����
	WinExec("data\\changepw.exe", SW_HIDE);
	//�Ƿ�ɹ�
	int change_succ = change_check();
	
	if (change_succ == 1)
	{
		strcpy(new_password, szTemp); 
		CString str;
		str.Format(_T("�޸ĳɹ�!�����Ϊ%s"),szTemp);
		AfxMessageBox(str);
	}
	else
	{
		save_password(password, pw_file_loc);//ԭ����д��
		CString str;
		str.Format(_T("�޸�ʧ��!��ǰ����Ϊ%s"), password);
		AfxMessageBox(str);
	}
	
	Msgdlg->DestroyWindow();//���ٵȴ���
	EndDialog(0);//����������
}