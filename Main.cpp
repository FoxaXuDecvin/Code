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
		settinginfo << "如果你在使用中发现了问题，可以尝试删除这个目录以重置所有选项" << endl;
		settinginfo << "此文件仅用于判断配置文件是否正常" << endl;
		settinginfo.close();

		//Download File
		system("start bitsadmin /transfer 安装基础脚本,请勿关闭本窗口 /download /priority normal https://foxaxudecvin.github.io/warehouse/Foxa-DService.bat  %cd%\\Root\\Plugin\\Foxa-DService.bat");
	}

SkipLoadConfig:

	//获取进程地址
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
		eula << "   软件使用条款" << endl;
		eula << " 更新日期   2022 年 12 月 26 日。修改: FoxaXu" << endl;
		eula << "更多信息请访问 https://foxaxudecvin.github.io. 邮箱 foxaxudecvin@outlook.com" << endl;
		eula << " " << endl;
		eula << "感谢你打开这款软件，测试阶段，部分信息可以在 Root\\KernelData.txt找到" << endl;
		eula << "如果你在使用中发现有漏洞，可以向我们报告，联系方式可以打开上面的网站。也可以通过邮箱" << endl;
		eula << "此软件处于开发测试阶段，此条款可能会随时更新,未经许可不允许修改发布" << endl;
		eula << " " << endl;
		eula << "FoxaXu 2022.12.26      Github https://github.com/foxaxudecvin" << endl;
		eula << "阅读完成请点击确定同意" << endl;
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
		a = MessageBox(0, L"请阅读注意事项后继续", L"MainService", MB_YESNO);
		if (a == 6)
		{
			MessageBox(0, L"按下确定代表同意此条款", L"MainService", MB_OK);
		}
		else
		{
			MessageBox(0, L"你已取消操作", L"MainService", MB_OK);
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
			cout << "正在完成安装，请稍等" << endl;

			string CDFDService = "Root\\Plugin\\Foxa-DService.bat";
			bool CDFDS = isFileExists_ifstream(CDFDService);
			if (CDFDS) {
				goto CDFDService_PASS;
			}
			else
			{
				MessageBox(0, L"安装失败，文件下载异常，请尝试删除Root目录后重新安装，安装过程中请不要随意关闭弹出的窗口", L"MainService", MB_OK);
				return 0;
			}

			CDFDService_PASS:
			cout << "安装过程中请不要关闭弹出的窗口，否则可能导致文件下载不完整" << endl;
			Sleep(1500);
			cout << " " << endl;
			cout << "下载 7z.exe 到 Root\\Plugin" << endl;
			system("set URL=https://foxaxudecvin.github.io/warehouse/7z.exe &set SavePath=Root\\Plugin\\7z.exe &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "下载 7z.dll 到 Root\\Plugin" << endl;
			system("set URL=https://foxaxudecvin.github.io/warehouse/7z.dll &set SavePath=Root\\Plugin\\7z.dll &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "下载 Kernel.exe 到 Root\\Plugin" << endl;
			system("set URL=https://FoxxaaService.github.io/Kernel.exe &set SavePath=Root\\Plugin\\Kernel.exe &set EngineMode=auto &start %cd%\\Root\\Plugin\\Foxa-DService.bat");
			cout << "在所有窗口自动关闭后按任意键继续" << endl;
			system("pause");
			system("cls");
			cout << "正在验证你的下载是否完整" << endl;

			string CDFKernel = "Root\\Plugin\\Kernel.exe";
			bool CDFK = isFileExists_ifstream(CDFKernel);
			if (CDFK) {
				goto CDFK_PASS;
			}
			else
			{
				MessageBox(0, L"安装失败，文件下载异常，请尝试删除Root目录后重新安装，安装过程中请不要随意关闭弹出的窗口", L"MainService", MB_OK);
				return 0;
			}
			CDFK_PASS:
			cout << "正在进行下一步安装,请稍等" << endl;
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
			MessageBox(0, L"内核没有回复主程序的指令，请尝试重新运行或者删除Root目录重新安装本程序",L"MainService", MB_OK);
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
			MessageBox(0, L"AdminProcess 服务异常，无法进行下一步操作", L"MainService", MB_OK);
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