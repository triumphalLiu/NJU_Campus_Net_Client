// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NJU.h"
#include "About.h"
#include "afxdialogex.h"


// About �Ի���

IMPLEMENT_DYNAMIC(About, CDialogEx)

About::About(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

About::~About()
{
}

void About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(About, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &About::OnBnClickedCancel)
END_MESSAGE_MAP()


// About ��Ϣ�������


void About::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
