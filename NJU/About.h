#pragma once


// About �Ի���

class About : public CDialogEx
{
	DECLARE_DYNAMIC(About)

public:
	About(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~About();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
