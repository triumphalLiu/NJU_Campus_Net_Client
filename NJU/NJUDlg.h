
// NJUDlg.h : ͷ�ļ�
//

#pragma once


// CNJUDlg �Ի���
class CNJUDlg : public CDialogEx
{
// ����
public:
	CNJUDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NJU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void On32784();
	afx_msg void On32785();
	afx_msg void On32787();
	afx_msg void On32788();
	afx_msg void On32789();
	afx_msg void On32790();
	afx_msg void On32791();
};
