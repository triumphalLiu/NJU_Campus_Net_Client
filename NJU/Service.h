#pragma once


// Service �Ի���

class Service : public CDialogEx
{
	DECLARE_DYNAMIC(Service)

public:
	Service(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Service();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
