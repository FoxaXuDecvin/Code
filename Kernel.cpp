#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<iomanip>

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	char CoreVersion[] = "Alpha-Core1.10.2";
	char CodeName[] = "PaperCore";
	char CoreCompileDate[] = "20221227_1";

	//MainService

	string TempLCFile = "LaunchCode.data";
	bool ret = isFileExists_ifstream(TempLCFile);
	if (ret)
	{
		system("del /q LaunchCode.data");
	}
	system("echo=%LCode% >>LaunchCode.data");

	string UserDialogue = "null";
	ifstream GetLaunchCode;
	GetLaunchCode.open("LaunchCode.data");
	GetLaunchCode >> UserDialogue;
	GetLaunchCode.close();

	system("del LaunchCode.data");

	//Process LaunchCode

	if (UserDialogue == "version") {
		cout << "FoxaCore - Copyright FoxaXu 2022." << endl;
		cout << "FXInfo  -Core Version: ";
		cout << CoreVersion << endl;
		cout << "FXInfo  -Developer Code Name: ";
		cout << CodeName << endl;
		cout << "FXInfo  -Compile Date:";
		cout << CoreCompileDate << endl;
		cout << "Made By FoxaXu. All rights reserved" << endl;
		return 0;
	}
	
	if (UserDialogue == "setup") {
		int SECode = 0;
		cout << "Setup Preparing: " << endl;;
		Sleep(2000);
		cout << "������֤�����ļ��Ƿ�����" << endl;
		string ScanRootFile7z = "Root\\Plugin\\7z.exe";
		bool SRFo7z = isFileExists_ifstream(ScanRootFile7z);
		if (SRFo7z)
		{
			goto SRFoNEXToA;
		}
		else
		{
			MessageBox(0, L"�ں˳�ʼ��ʧ��,�����ļ� 7z.exe ��������ʧ���볢��ɾ�� RootĿ¼������", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	SRFoNEXToA:

		string ScanRootFileDService = "Root\\Plugin\\Foxa-DService.bat";
		bool SRFoDS = isFileExists_ifstream(ScanRootFileDService);
		if (SRFoDS)
		{
			goto SRFoNEXToB;
		}
		else
		{
			MessageBox(0, L"�ں˳�ʼ��ʧ��,�����ļ� Foxa-DService.bat ��������ʧ���볢��ɾ�� RootĿ¼������", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
		SRFoNEXToB:
		cout << "��֤���,���ڻ�ȡ��������" << endl;

		string ScanDeleteTempASK = "Root\\Temp\\ASK.data";
		bool SASK = isFileExists_ifstream(ScanDeleteTempASK);
		if (SASK)
		{
			system("del Root\\Temp\\ASK.data");
		}
		system("set URL=https://foxaxudecvin.github.io/DownloadLink/AutoSetupKernel.data &set SavePath=Root\\Temp\\ASK.data &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");

		ScanDownloadCompleteASK:

		string CheckDownloadOKASK= "Root\\Temp\\ASK.data";
		bool CDASK = isFileExists_ifstream(CheckDownloadOKASK);
		if (CDASK)
		{
			goto DownloadOKASK;
		}
		else
		{
			goto ScanDownloadCompleteASK;
		}
	DownloadOKASK:

		cout << "�������ذ�װ��" << endl;

		system("set/p URL=<Root\\Temp\\ASK.data &set SavePath=Root\\Temp\\ASPack.zip &set EngineMode=auto &Root\\Plugin\\Foxa-DService.bat");

	ScanDownloadCompleteASPack:

		string CheckDownloadOKASPack = "Root\\Temp\\ASPack.zip";
		bool CDASPack = isFileExists_ifstream(CheckDownloadOKASPack);
		if (CDASPack)
		{
			goto DownloadOKASPack;
		}
		else
		{
			goto ScanDownloadCompleteASPack;
		}
	DownloadOKASPack:
		cout << "�������д����Զ��رպ������������������Ҫȷ������ļ��������" << endl;
		system("pause");
		cout << "���ڽ�ѹ��װ��,�ڴ��ڹرպ����������" << endl;
		ShellExecute(0, L"open", L"Root\\Plugin\\7z.exe", L"x -oRoot\\Extend Root\\Temp\\ASPack.zip",0,SW_SHOW);
		system("pause");
		system("cls");
		cout << "������֤��İ�װ" << endl;
		Sleep(1600);
		string CheckExtendPack = "Root\\Extend\\Pack.data";
		bool CExtend = isFileExists_ifstream(CheckExtendPack);
		if (CExtend)
		{
			goto PassSetupExtend;
		}
		else
		{
			system("cls");
			MessageBox(0,L"��װʧ�ܣ��޷���ѹExtend�ļ��У��볢��ɾ��rootĿ¼������", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	PassSetupExtend:
		system("cls");
		MessageBox(0, L"��װ��ɣ����������и����", L"Kernel Prepare Setup", MB_OK);
		cout << "��������رմ˴���" << endl;
		system("pause");
		return 0;
	}
	
	if (UserDialogue == "report") {
		ofstream KernelVersionReport;
		KernelVersionReport.open("Root\\Temp\\KernelReport-Version.data");
		KernelVersionReport << CoreVersion << endl;
		KernelVersionReport.close();

		ofstream KernelBuildDateReport;
		KernelBuildDateReport.open("Root\\Temp\\KernelReport-BuildDate.data");
		KernelBuildDateReport << CoreCompileDate << endl;
		KernelBuildDateReport.close();

		ofstream KernelCNReport;
		KernelCNReport.open("Root\\Temp\\KernelReport-CodeName.data");
		KernelCNReport << CodeName << endl;
		KernelCNReport.close();
		return 0;
	}

	cout << "Unknown Command: ";
	cout << UserDialogue << endl;
	return 0;
}