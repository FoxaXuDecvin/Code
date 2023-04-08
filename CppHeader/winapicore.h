// Windows API Loader
// Copyright FoxaXu
// Add _CRT_SECURE_NO_WARNINGS in Setting

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<Windows.h>
#include<string>
#include<iostream>
#include<fstream>
#include<tchar.h>
#pragma comment(lib,"URlmon.lib")

#undef UNICODE
#undef _UNICODE

using namespace std;

LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

bool existcheck(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

bool existfile(string file) {
	bool retEF = existcheck(file);
	return retEF;
}

bool existfolder(string name) {
	string A = name + "\\existfoldertest.bin";
	
	ofstream opentest;
	opentest.open(A);
	opentest << "writeTest" << endl;
	opentest.close();

	bool retb = existcheck(A);
	remove(A.c_str());

	return retb;
}

bool URLDown(string URL, string SavePath) {
	bool retDLA = existcheck(SavePath);
	if (retDLA) {
		remove(SavePath.c_str());
	}

	LPCWSTR LcDsp = stringToLPCWSTR(SavePath);
	LPCWSTR LcURL = stringToLPCWSTR(URL);
	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcURL,
		LcDsp,
		0,
		nullptr
	);
	bool retDLB = existcheck(SavePath);
	ifstream ReturnCode(SavePath.c_str());
	return ReturnCode.good();
}

string readengine(string file, string head, string title) {
	LPTSTR lpPath = new char[MAX_PATH];

	strcpy(lpPath, file.c_str());
	LPTSTR ReadPointWM = new char[99];

	bool existf = existcheck(file);
	if (existf) {
		GetPrivateProfileString(head.c_str(), title.c_str(), NULL, ReadPointWM, 99, lpPath);
		return ReadPointWM;
	}
	else
	{
		string Text = "read.data.error:file not found";
		return Text;
	}
}

string readini(string file, string head, string title) {
	string returncheck = readengine(file, head, title);
	if (returncheck == "") {
		string charcode = "read.data.error:title not found";
		return charcode;
	}
	return returncheck;
}

string writeini(string file, string head, string title,string info) {
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, file.c_str());
	WritePrivateProfileString(head.c_str(), title.c_str(), info.c_str(), lpPath);
	string n = "succ";
	return n;
}

string cmdshell(string command,string runpath,string taskcode) {
	ofstream ShellOutput;
	string code = "$temp" + taskcode + "CMD.bat";
	ShellOutput.open(code);
	ShellOutput << "set oldcd=%cd%" << endl;
	ShellOutput << "cd /d " << runpath << endl;
	ShellOutput << command << endl;
	ShellOutput << "cd /d %oldcd%" << endl;
	ShellOutput << "del /q " + code << endl;
	ShellOutput << "exit" << endl;
	ShellOutput.close();

	ShellExecute(0, "open", code.c_str(), 0, 0, SW_HIDE);
	return code;
}

string cmdshelladmin(string command, string runpath, string taskcode) {
	ofstream ShellOutput;
	string code = "$temp" + taskcode + "CMD.bat";
	ShellOutput.open(code);
	ShellOutput << "set oldcd=%cd%" << endl;
	ShellOutput << "cd /d " << runpath << endl;
	ShellOutput << command << endl;
	ShellOutput << "cd /d %oldcd%" << endl;
	ShellOutput << "del /q " + code << endl;
	ShellOutput << "exit" << endl;
	ShellOutput.close();

	ShellExecute(0, "runas", code.c_str(), 0, 0, SW_HIDE);
	return code;
}

string rmfolder(string foldername) {
	ofstream RMTask;
	string filename = "$task~rmfolder~" + foldername + ".bat";
	RMTask.open(filename);
	RMTask << "@echo off" << endl;
	RMTask << "rd /s /q " + foldername << endl;
	RMTask << "del " + filename << endl;
	RMTask << "exit" << endl;
	RMTask.close();

	ShellExecute(0, "open", filename.c_str(), 0, 0, SW_HIDE);
	return filename;
}

string mdfolder(string foldername) {
	string name = foldername;
	CreateDirectory(foldername.c_str(), 0);
	return name;
}

string clearfolder(string foldername) {
	ofstream RMTask;
	string filename = "$task~rmfolder~" + foldername + ".bat";
	RMTask.open(filename);
	RMTask << "@echo off" << endl;
	RMTask << "rd /s /q " + foldername << endl;
	RMTask << "md " + foldername << endl;
	RMTask << "del " + filename << endl;
	RMTask << "exit" << endl;
	RMTask.close();

	ShellExecute(0, "open", filename.c_str(), 0, 0, SW_HIDE);
	return filename;
}

string geturlcode(string url) {
	URLDown(url, "guc~temp.txt");
	string charr = "guc~temp.txt";
	bool retGUC = existcheck(charr);
	if (retGUC) {
		string backchar;
		ifstream ReadPoint;
		ReadPoint.open(charr);
		ReadPoint >> backchar;
		ReadPoint.close();
		remove(charr.c_str());

		return backchar;
	}
	else {
		string rechar = "geturlfailed";
		return rechar;
	}
}

string getselfinfo(string api ) {
	errno_t	err = 0;
	char	fileName[100] = { 0 };
	char    ProcessFullName[_MAX_PATH] = { 0 };
	char    ProcessName[0x40] = { 0 };
	DWORD   ProcessPID = 0;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	ProcessPID = GetCurrentProcessId();
	GetModuleFileNameA(NULL, ProcessFullName, _MAX_PATH);

	tmp1 = strrchr((char*)ProcessFullName, '\\');
	tmp2 = strrchr((char*)ProcessFullName, '.');
	memcpy(ProcessName, tmp1 + 1, min(tmp2 - tmp1 - 1, 0x40));
	if (api == "processfullname") {
		return ProcessFullName;
	}
	if (api == "processname") {
		return ProcessName;
	}
	string backmsg = "select error";
	return backmsg;
}
//command format
// processfullname
// processname

int getpid() {
		errno_t	err = 0;
		char	fileName[100] = { 0 };
		char    ProcessFullName[_MAX_PATH] = { 0 };
		char    ProcessName[0x40] = { 0 };
		DWORD   ProcessPID = 0;
		char* tmp1 = NULL;
		char* tmp2 = NULL;

		ProcessPID = GetCurrentProcessId();
		GetModuleFileNameA(NULL, ProcessFullName, _MAX_PATH);

		tmp1 = strrchr((char*)ProcessFullName, '\\');
		tmp2 = strrchr((char*)ProcessFullName, '.');
		memcpy(ProcessName, tmp1 + 1, min(tmp2 - tmp1 - 1, 0x40));
		return ProcessPID;
}

string cmarkfile(string filename, string info) {
	ofstream tempwrite;
	tempwrite.open(filename);
	tempwrite << info << endl;
	tempwrite.close();
	return info;
}

//COUT

string OpenWebsite(string URL) {
	ShellExecute(0, "open", URL.c_str(), 0, 0, SW_SHOW);
	return 0;
}

// OS API

bool testAdmin(string TestDir) {
	string testfile = TestDir + "\\testadmin~winapicore.bin";

	cmarkfile(testfile, "testAdmin");

	bool retINFO = existfile(testfile);

	remove(testfile.c_str());

	return retINFO;
}

//Read info

string ReadText(string filename, int line)
{
	ifstream fin;
	fin.open(filename, ios::in);
	string strVec[6400]; 
	int i = 0;
	while (!fin.eof())
	{
		string inbuf;
		getline(fin, inbuf, '\n');
		strVec[i] = inbuf;
		i = i + 1;
	}
	return strVec[line - 1];
}