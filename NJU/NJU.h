
// NJU.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNJUApp: 
// �йش����ʵ�֣������ NJU.cpp
//

class CNJUApp : public CWinApp
{
public:
	CNJUApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNJUApp theApp;

#include <cstring>
#include <cstdlib>
#include <direct.h>  
#include <Windows.h>  
#include <cstdio>  
#include <fstream>
#include <string>
#define MAX_FILE_PATH 100
#define MAX_ID_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_SERV_LENGTH 20
#pragma warning (disable:4996)

struct status {
	int successful;
	int device_amounts;
	float account_balance;
	char service[MAX_SERV_LENGTH];
	char username[MAX_ID_LENGTH];
	int hours;
	int mins;
};
void read_info(char *&, char *&);
void login();
void logout();
void read_status();
bool file_is_empty(char *);
void save_user();
void clean_status();
int change_check();
void save_password(char *&,char *);