#pragma once
#include "NJU.h"

// ChangePW �Ի���

class ChangePW : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePW)

public:
	ChangePW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangePW();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
