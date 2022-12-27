#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char** argv) {
	RELOAD:
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	char version[] = "Build_0003";
	char pubdate[] = "20221227";

	string filename = "Root\\SettingInfo.txt";
	bool ret = isFileExists_ifstream(filename);
	if (ret)
	{
		system("echo=Report_Config_is_Exist>>Root\\LoadReport.log");
		goto SkipLoadConfig;
	}
	else
	{
		system("md Root");
		system("md Root\\Config");
		system("md Root\\Plugin");
		system("md Root\\Reg");

		ofstream SettingSkipDisplayEula;
		SettingSkipDisplayEula.open("Root\\Config\\SkipDisplayEula.cfg");
		SettingSkipDisplayEula << "offskip" << endl;
		SettingSkipDisplayEula.close();

		ofstream profilename;
		profilename.open("Root\\ProfileName.cfg");
		profilename << "Default" << endl;
		profilename.close();

		ofstream displaycolor;
		displaycolor.open("Root\\Config\\DisplayColor.bat");
		displaycolor << "@echo off" << endl;
		displaycolor << "color 07" << endl;
		displaycolor << "exit" << endl;
		displaycolor.close();

		ofstream settinginfo;
		settinginfo.open("Root\\SettingInfo.txt");
		settinginfo << "Release Version: ";
		settinginfo << version << endl;
		settinginfo << "Public Date: ";
		settinginfo << pubdate << endl;
		settinginfo << "�������ʹ���з��������⣬���Գ���ɾ�����Ŀ¼����������ѡ��" << endl;
		settinginfo << "���ļ��������ж������ļ��Ƿ�����" << endl;
		settinginfo.close();

		//Download File
		system("start bitsadmin /transfer ��װ�����ű�,����رձ����� /download /priority normal https://foxaxudecvin.github.io/warehouse/Foxa-DService.bat  %cd%\\Root\\Plugin\\Foxa-DService.bat");
	}

SkipLoadConfig:

	//��ȡ���̵�ַ
	string ProcessName = argv[0], PN2;
	int flag = 0;
	for (int PNData = ProcessName.length() - 1; PNData >= 0; PNData--)
	{
		if (ProcessName[PNData] == '\\')
		{
			flag = PNData + 1;
			break;
		}
	}
	PN2 = ProcessName.substr(flag);

	system("rd /s /q Root\\Temp");

	system("md Root\\Temp");

	string profilename = "Null";
	ifstream taskreadprofile;
	taskreadprofile.open("Root\\ProfileName.cfg");
	taskreadprofile >> profilename;
	taskreadprofile.close();

	string settingSde = "Null";
	ifstream taskcheckSde;
	taskcheckSde.open("Root\\Config\\SkipDisplayEula.cfg");
	taskcheckSde >> settingSde;
	taskcheckSde.close();

	system("echo=%cd%\\Root>>Root\\Temp\\GetPathInfo.data");
	string WorkFolder = "Null";
	ifstream GWorkFolder;
	GWorkFolder.open("Root\\Temp\\GetPathInfo.data");
	GWorkFolder >> WorkFolder;
	GWorkFolder.close();
	system("del Root\\Temp\\GetPathInfo.data");

	system("rd /s /q %temp%\\FoxaXuTemp");
	system("md %temp%\\FoxaXuTemp");

	system("echo=%UserName%>>%temp%\\FoxaXuTemp\\UserName.data");

	ofstream kerneldata;
	kerneldata.open("Root\\KernelData.txt");
	kerneldata << "Kernel Version: ";
	kerneldata << version << endl;
	kerneldata << "Version Release Date: ";
	kerneldata << pubdate << endl;
	kerneldata << "More Info Please Visit https://foxaxudecvin.github.io" << endl;
	kerneldata << "Copyright FoxaXu 2022" << endl;
	kerneldata.close();
		ofstream eula;
		eula.open("Root\\EULA.txt");
		eula << "   ���ʹ������" << endl;
		eula << " ��������   2022 �� 12 �� 26 �ա��޸�: FoxaXu" << endl;
		eula << "������Ϣ����� https://foxaxudecvin.github.io. ���� foxaxudecvin@outlook.com" << endl;
		eula << " " << endl;
		eula << "��л��������������Խ׶Σ�������Ϣ������ Root\\KernelData.txt�ҵ�" << endl;
		eula << "�������ʹ���з�����©�������������Ǳ��棬��ϵ��ʽ���Դ��������վ��Ҳ����ͨ������" << endl;
		eula << "��������ڿ������Խ׶Σ���������ܻ���ʱ����,δ����ɲ������޸ķ���" << endl;
		eula << " " << endl;
		eula << "FoxaXu 2022.12.26      Github https://github.com/foxaxudecvin" << endl;
		eula << "�Ķ��������ȷ��ͬ��" << endl;
		eula << " " << endl;
		eula << "Version: ";
		eula << version << endl;
		eula << "PubDate: ";
		eula << pubdate << endl;
		eula.close();

		ofstream ProcessPathOut;
		ProcessPathOut.open("Root\\ProcessName.cfg");
		ProcessPathOut << ProcessName << endl;
		ProcessPathOut.close();

		int a;

		if (settingSde == "offskip")
		{
			cout << "Skip switch is disabled" << endl;
		}
		else
		{
			goto SkipDisplayE;
		}

		system("cls");

		system("type Root\\EULA.txt");
		a = MessageBox(0, L"���Ķ�ע����������", L"MainService", MB_YESNO);
		if (a == 6)
		{
			MessageBox(0, L"����ȷ������ͬ�������", L"MainService", MB_OK);
		}
		else
		{
			MessageBox(0, L"����ȡ������", L"MainService", MB_OK);
			return 0;
		}

	SkipDisplayE:

		string KernelFile = "Root\\Plugin\\Kernel.exe";
		bool returndata = isFileExists_ifstream(KernelFile);
		if (returndata) {
			goto SkipPrepareDownload;
		}
		else
		{
			system("cls");
			cout << "������ɰ�װ�����Ե�" << endl;

			string CDFDService = "Root\\Plugin\\Foxa-DService.bat";
			bool CDFDS = isFileExists_ifstream(CDFDService);
			if (CDFDS) {
				goto CDFDService_PASS;
			}
			else
			{
				MessageBox(0, L"��װʧ�ܣ��ļ������쳣���볢��ɾ��RootĿ¼�����°�װ����װ�������벻Ҫ����رյ����Ĵ���", L"MainService", MB_OK);
				return 0;
			}

			CDFDService_PASS:
			cout << "��װ�������벻Ҫ�رյ����Ĵ��ڣ�������ܵ����ļ����ز�����" << endl;
			Sleep(1500);
			cout << " " << endl;
			cout << "���� 7z.exe �� Root\\Plugin" << endl;
			system("set URL=https://foxaxudecvin.github.io/warehouse/7z.exe &set SavePath=Root\\Plugin\\7z.exe &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "���� 7z.dll �� Root\\Plugin" << endl;
			system("set URL=https://foxaxudecvin.github.io/warehouse/7z.dll &set SavePath=Root\\Plugin\\7z.dll &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "���� Kernel.exe �� Root\\Plugin" << endl;
			system("set URL=https://FoxxaaService.github.io/Kernel.exe &set SavePath=Root\\Plugin\\Kernel.exe &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "�����д����Զ��رպ����������" << endl;
			system("pause");
			system("cls");
			cout << "������֤��������Ƿ�����" << endl;

			string CDFKernel = "Root\\Plugin\\Kernel.exe";
			bool CDFK = isFileExists_ifstream(CDFKernel);
			if (CDFK) {
				goto CDFK_PASS;
			}
			else
			{
				MessageBox(0, L"��װʧ�ܣ��ļ������쳣���볢��ɾ��RootĿ¼�����°�װ����װ�������벻Ҫ����رյ����Ĵ���", L"MainService", MB_OK);
				return 0;
			}
			CDFK_PASS:
			cout << "���ڽ�����һ����װ,���Ե�" << endl;
			system("set LCode=setup &Root\\Plugin\\Kernel.exe");
			return 0;
		}
		system("cls");
		SkipPrepareDownload:

		system("set LCode=report &Root\\Plugin\\Kernel.exe");

		Sleep(50);

		string KRVersion = "Root\\Temp\\KernelReport-Version.data";
		bool KRVer = isFileExists_ifstream(KRVersion);
		if (KRVer) {
			goto RKMsg;
		}
		else
		{
			MessageBox(0, L"�ں�û�лظ��������ָ��볢���������л���ɾ��RootĿ¼���°�װ������",L"MainService", MB_OK);
			return 0;
		}

	RKMsg:

		string KernelVersion = "Null";
		ifstream KernelVersionRead;
		KernelVersionRead.open("Root\\Temp\\KernelReport-Version.data");
		KernelVersionRead >> KernelVersion;
		KernelVersionRead.close();

		string KernelBuildDate = "Null";
		ifstream KernelBuildDateRead;
		KernelBuildDateRead.open("Root\\Temp\\KernelReport-BuildDate.data");
		KernelBuildDateRead >> KernelBuildDate;
		KernelBuildDateRead.close();

		string KernelCN = "Null";
		ifstream KernelCNRead;
		KernelCNRead.open("Root\\Temp\\KernelReport-CodeName.data");
		KernelCNRead >> KernelCN;
		KernelCNRead.close();

		ofstream SettingEnabledSkipDisplayEula;
		SettingEnabledSkipDisplayEula.open("Root\\Config\\SkipDisplayEula.cfg");
		SettingEnabledSkipDisplayEula << "openskip" << endl;
		SettingEnabledSkipDisplayEula.close();

		system("del Root\\Temp\\KernelReport-Version.data");
		system("del Root\\Temp\\KernelReport-BuildDate.data");
		system("del Root\\Temp\\KernelReport-CodeName.data");

	system("cls");

	system("start /b Root\\Config\\DisplayColor.bat");
	Sleep(1000);
	cout << "Type Command or Program" << endl;
	cout << "Kernel Version: ";
	cout << version << endl;
RETURN_BOX:
	system("title FoxaXu Dialogue");
	string Dialog = "Null.noanytype";
	cout << "Command\>";
	getline(cin, Dialog);
	if (Dialog == "") {
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "exit") {
		return 0;
	};
	if (Dialog == "version") {
		cout << " " << endl;
		cout << "Version DATA: ";
		cout << version << endl;
		cout << "ReleaseTime: ";
		cout << pubdate << endl;
		cout << "Profile Name: ";
		cout << profilename << endl;
		cout << "Kernel Version: ";
		cout << KernelVersion;
		cout << " Code Name: ";
		cout << KernelCN << endl;
		cout << "Kernel Release Time: ";
		cout << KernelBuildDate << endl;
		cout << "Process Path and Name: ";
		cout << ProcessName << endl;
		cout << "Work Root Folder: ";
		cout << WorkFolder << endl;
		cout << " " << endl << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "help") {
		cout << "No Thing to here" << endl;
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "clear") {
		system("cls");
		goto RETURN_BOX;
	}
	if (Dialog == "time") {
		system("echo=%date% %time%");
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "reload") {
		goto RELOAD;
	}
	if (Dialog == "openwork") {
		system("explorer %cd%");
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "notepad") {
		ShellExecute(NULL, L"open", L"Notepad.exe", 0, 0, SW_SHOWNORMAL);
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "admin") {

		string APServiceCheck = "Root\\Extend\\AdminProcess.bat";
		bool APServiceCK = isFileExists_ifstream(APServiceCheck);
		if (APServiceCK) {
			system("set/p RunProcess=<Root\\ProcessName.cfg &Root\\Extend\\AdminProcess.bat");
		}
		else
		{
			MessageBox(0, L"AdminProcess �����쳣���޷�������һ������", L"MainService", MB_OK);
			cout << " " << endl;
			goto RETURN_BOX;
		}
		return 0;
	}
	cout << "Code: ";
	cout << Dialog ;
	cout << " is not a command and program" << endl;
	cout << "Check your type is Correct" << endl;
	cout << " " << endl;
	goto RETURN_BOX;
}