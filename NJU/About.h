#pragma once


// About 对话框

class About : public CDialogEx
{
	DECLARE_DYNAMIC(About)

public:
	About(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~About();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
