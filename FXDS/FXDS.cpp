#include<Windows.h>
#include<stdio.h>
#include<direct.h>
#include<string>
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")

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

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}


int main()
{
	string SetDownloadCout = "SetDownload.data";
	bool returnSDLC = isFileExists_ifstream(SetDownloadCout);
	if (returnSDLC)
	{
		system("del SetDownload.data");
	}

	string SetDownloadURL = "SetSavePath.data";
	bool returnSDURL = isFileExists_ifstream(SetDownloadURL);
	if (returnSDURL)
	{
		system("del SetSavePath.data");
	}

	system("echo=%setURL% >>SetDownload.data");
	system("echo=%setSP% >>SetSavePath.data");

	string durl = "nul";
	string dsp = "nul";

	ifstream ReadDURL;
	ReadDURL.open("SetDownload.data");
	ReadDURL >> durl;
	ReadDURL.close();

	ifstream ReadDSP;
	ReadDSP.open("SetSavePath.data");
	ReadDSP >> dsp;
	ReadDSP.close();

	bool CFEXIST = isFileExists_ifstream(dsp);
	if (CFEXIST) {
		system("del %setSP%");
	}

	system("del SetSavePath.data");
	system("del SetDownload.data");
	if (durl == "%setURL%")
	{
		MessageBox(0, L"请添加 %setSP%与%setURL%下载链接两个参数，请不要直接打开本程序，操作无效", L"Download Service", MB_OK);
		MessageBox(0, L"例： set setURL=www.baidu.com&set setSP=%userprofile%\\Desktop\\a.exe&FXDS.exe", L"Download Service", MB_OK);
		return 0;
	}
	if (dsp == "%setSP%")
	{
		cout << "参数错误，请补全 %setSP% 变量" << endl;
		cout << "Error Data Error: VAR_CODE_ERROR" << endl;
		return 0;
	}

	LPCWSTR LcDsp = stringToLPCWSTR(dsp);
	LPCWSTR LcDURL = stringToLPCWSTR(durl);

	cout << "下载开始 - 下载链接:" << durl << "保存地址: " << dsp << endl;

	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcDURL,
		LcDsp,
		0,
		nullptr
	);

	bool CDSP = isFileExists_ifstream(dsp);
	if (CDSP) {
		cout << "下载成功，目录" << dsp << endl;

		system("echo=TRUE >>%temp%\\DownloadReport.dat");

		return 0;
	}
	else
	{
		cout << "下载失败, URL错误: " << durl << endl;

		system("echo=FALSE >>%temp%\\DownloadReport.dat");

		return 0;
	}
}