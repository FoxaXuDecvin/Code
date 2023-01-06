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
	system("echo=%addcode% >>TestDialog.data");
	string AddCode = "null";
	ifstream OpenReadAddCode;
	OpenReadAddCode.open("TestDialog.data");
	OpenReadAddCode >> AddCode;
	OpenReadAddCode.close();
	system("del TestDialog.data");

	string dsp = "nul";
	string durl = "nul";

	if (AddCode == "%addcode%") {
		//����ģʽ
		system("echo=%setURL% >>surl.data");
		system("echo=%setSP% >>ssp.data");

		ifstream OSURL;
		OSURL.open("surl.data");
		OSURL >> durl;
		OSURL.close();

		ifstream OSSP;
		OSSP.open("ssp.data");
		OSSP >> dsp;
		OSSP.close();

		system("del surl.data");
		system("del ssp.data");
		
		if (durl == "%setURL%") {
			goto NullTask;
		}
		if (dsp == "%setSP%") {
			goto NullTask;
		}
		goto StartDownload;

	NullTask:
		MessageBox(0, L"������Ч������ %setURL%�� %serSP% ����ֵ�Ƿ���ȷ", L"Download Task", MB_OK);
		return 0;
	}
	if (AddCode == "longlink") {
		string CodeMode = "Long Link";
		ifstream OpenFileDURL;
		OpenFileDURL.open("durl.data");
		OpenFileDURL >> durl;
		OpenFileDURL.close();

		ifstream OpenFileDSP;
		OpenFileDSP.open("dsp.data");
		OpenFileDSP >> dsp;
		OpenFileDSP.close();
		system("del durl.data");
		system("del dsp.data");
		goto StartDownload;
	}

	StartDownload:
	LPCWSTR LcDsp = stringToLPCWSTR(dsp);
	LPCWSTR LcDURL = stringToLPCWSTR(durl);

	cout << "���ؿ�ʼ  " << AddCode << "  - ��������:" << durl << "�����ַ : " << dsp << endl;

	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcDURL,
		LcDsp,
		0,
		nullptr
	);

	bool CDSP = isFileExists_ifstream(dsp);
	if (CDSP) {
		cout << "���سɹ���Ŀ¼" << dsp << endl;

		system("echo=TRUE >>%temp%\\DownloadReport.dat");

		return 0;
	}
	else
	{
		cout << "����ʧ��, URL����: " << durl << endl;

		system("echo=FALSE >>%temp%\\DownloadReport.dat");

		return 0;
	}
}