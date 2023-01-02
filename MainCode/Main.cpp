#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char** argv) {
	RELOAD:
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	char version[] = "Build_1011";
	char pubdate[] = "20230102";

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
		cout << "正在下载FXDS" << endl;
		HRESULT PrepFXDS = URLDownloadToFileW(
			nullptr,
			L"https://foxaxudecvin.github.io/warehouse/FXDS.exe",
			L"Root\\Plugin\\FXDS.exe",
			0,
			nullptr
		);
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
		eula << "关于开源信息请访问: https://github.com/foxaxudecvin/Code" << endl;
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

		string KernelFile = "Root\\Plugin\\Kernel.exe";
		bool returndata = isFileExists_ifstream(KernelFile);
		if (returndata) {
			goto SkipPrepareDownload;
		}
		else
		{
			system("cls");
			cout << "正在完成安装，请稍等" << endl;

			string CDFDService = "Root\\Plugin\\FXDS.exe";
			bool CDFDS = isFileExists_ifstream(CDFDService);
			if (CDFDS) {
				goto CDFDService_PASS;
			}
			else
			{
				MessageBox(0, L"初始化失败，请检查你的网络是否正常，如果你正在使用Windows7系统请启用TLS服务和安装KB3140245更新, 下载服务可能会触发 Windows Defender警报，请自行处理", L"MainService", MB_OK);
				return 0;
			}

		CDFDService_PASS:
			Sleep(1500);
			cout << " " << endl;
			cout << "正在启动下载服务" << endl;
			system("set setURL=https://foxaxudecvin.github.io/warehouse/7z.exe&set setsp=Root\\Plugin\\7z.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://foxxaaservice.github.io/Kernel.exe&set setsp=Root\\Plugin\\Kernel.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://foxaxudecvin.github.io/warehouse/7z.dll&set setsp=Root\\Plugin\\7z.dll&Root\\Plugin\\FXDS.exe");
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
		cout << "Help Center" << endl << endl;
		cout << "exit  - Close" << endl;
		cout << "version  -show version info" << endl;
		cout << "help        -get help information" << endl;
		cout << "clear       -clear screen" << endl;
		cout << "time       -debug for show time" << endl;
		cout << "reload    -Reload All Settings" << endl;
		cout << "openwork   -Open Root Folder" << endl;
		cout << "admin      -Run To Administrator" << endl;
		cout << "setup-package  -Install Package" << endl;
		cout << "remove     -Uninstall Package" << endl;
		cout << "list-tool    -List All Tools" << endl;
		cout << "repair       -Repair Tools" << endl;
		cout << "Copyright FoxaXu 2022" << endl << endl;
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
	if (Dialog == "setup-package") {
		string SFServc = "Root\\Extend\\SelectFileService.vbs";
		bool SFS = isFileExists_ifstream(SFServc);
		if (SFS) {
			goto SVRNORMAL;
		}
		else
		{
			MessageBox(0, L"SelectFileService 服务异常，无法进行下一步操作", L"MainService", MB_OK);
			cout << " " << endl;
			goto RETURN_BOX;
		}

	SVRNORMAL:
		ShellExecute(0, L"open", L"Root\\Extend\\SelectFileService.vbs", 0, 0, SW_SHOW);

	WaitSelectFile:

		Sleep(200);
		string CheckSLOR = "Root\\Temp\\OpenReport.data";
		bool CLSOR = isFileExists_ifstream(CheckSLOR);
		if (CLSOR)
		{
			goto applysetuppackage;
		}
		else
		{
			goto WaitSelectFile;
		}

		applysetuppackage:
		string SelectPackFile = "Null";
		ifstream taskreadsf;
		taskreadsf.open("Root\\Temp\\OpenReport.data");
		taskreadsf >> SelectPackFile;
		taskreadsf.close();
		cout << "正在验证安装包" << endl;
		string CFKRS = "Root\\Temp\\kernel-report-setpk.data";
		bool CFRS = isFileExists_ifstream(CFKRS);
		if (CFRS) {
			system("del /q Root\\Temp\\kernel-report-setpk.data");
		}
		system("set LCode=getpack &set/p FilePath=<Root\\Temp\\OpenReport.data &Root\\Plugin\\Kernel.exe");
		system("del Root\\Temp\\OpenReport.data");

	WAITRETURN_REPORT_SP:
		
		Sleep(1000);

		string WaitReturnKernelSP = "Root\\Temp\\kernel-report-setpk.data";
		bool WRKSP = isFileExists_ifstream(WaitReturnKernelSP);
		if (WRKSP) {
			goto CheckReturnKernelSP;
		}
		else
		{
			goto WAITRETURN_REPORT_SP;
		}

		CheckReturnKernelSP:
		
		string ApplyExtend = "False";
		ifstream taskcrksp;
		taskcrksp.open("Root\\Temp\\kernel-report-setpk.data");
		taskcrksp >> ApplyExtend;
		taskcrksp.close();

		system("del Root\\Temp\\kernel-report-setpk.data");

		if (ApplyExtend == "True") {
			MessageBox(0, L"安装完成，使用 list-tool 指令即可打开工具目录", L"MainService", MB_OK);
			cout << " " << endl;
			system("del Root\\Temp\\KR-PackCertData.data");
			system("del Root\\Temp\\GetFileSha256.data");
			system("del Root\\Temp\\GetURLCertCode.data");
			system("rd /s /q Root\\Temp\\PackInstallerTemp");
			system("cls");
			goto RETURN_BOX;
		}
		else
		{
			MessageBox(0, L"安装已被取消， 安装程序已撤销你所做的所有更改", L"MainService", MB_OK);
			cout << " " << endl;
			system("del Root\\Temp\\KR-PackCertData.data");
			system("del Root\\Temp\\GetFileSha256.data");
			system("del Root\\Temp\\GetURLCertCode.data");
			system("rd /s /q Root\\Temp\\PackInstallerTemp");
			system("cls");
			goto RETURN_BOX;
		}
		cout << " " << endl;
	}
	if (Dialog == "remove") {

		string CheckSVRFXI = "Root\\Extend\\PackTool-FXInstaller.Bat";
		bool CSVRFXI = isFileExists_ifstream(CheckSVRFXI);
		if (CSVRFXI) {
			goto PassCSVRFXI;
		}
		else
		{
			MessageBox(0, L"PackTool-FXInstaller 服务异常，无法执行相关命令", L"MainService", MB_OK);
			cout << " " << endl;
			goto RETURN_BOX;
		}

	PassCSVRFXI:
		cout << endl;
		system("dir Root\\PackTool");
		cout << "输入安装包PackDir路径" << endl;
		string PackDirDL = "Null.noanytype";
		cout << "Root\\PackTool\\>";
		getline(cin, PackDirDL);

		ofstream PackDirDialog;
		PackDirDialog.open("Root\\Temp\\PDDialog.data");
		PackDirDialog << PackDirDL << endl;
		PackDirDialog.close();

		system("set WorkMode=remove &set/p PackDir=<Root\\Temp\\PDDialog.data &start Root\\Extend\\PackTool-FXInstaller.Bat");
		system("del Root\\Temp\\PDDialog.data");
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "repair") {
		system("dir Root\\PackTool");
		cout << endl;
		string SelectRepair = "Null.Repair";
		cout << "Repair>";
		getline(cin, SelectRepair);
		ofstream RepairSelOut;
		RepairSelOut.open("Root\\Temp\\SROut.data");
		RepairSelOut << SelectRepair;
		RepairSelOut.close();

		system("set WorkMode=repair &set/p packdir=<Root\\Temp\\SROut.data &start Root\\Extend\\PackTool-FXInstaller.Bat");
		system("del Root\\Temp\\SROut.data");

		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "list-tool") {
		string OpenToolNameCK = "Null.noanytype";
		system("dir Root\\Reg");
		cout << "直接输入名称打开工具: 末尾不加 .fxlink " << endl ;
		cout << endl;
		goto RETURN_BOX;

	}

	ofstream RunExtendDialogDialog;
	RunExtendDialogDialog.open("Root\\Temp\\RunExtendDialog.data");
	RunExtendDialogDialog << "Root\\Reg\\";
	RunExtendDialogDialog << Dialog;
	RunExtendDialogDialog << ".fxlink" << endl;
	RunExtendDialogDialog.close();

	string RunExtendCode = "nul";
	ifstream REDExistCheck;
	REDExistCheck.open("Root\\Temp\\RunExtendDialog.data");
	REDExistCheck >> RunExtendCode;
	REDExistCheck.close();

	bool CheckRECD = isFileExists_ifstream(RunExtendCode);
	if (CheckRECD)
	{
		string CHECKRES = "Root\\Extend\\RunExtendService.Bat";
		bool CSRES = isFileExists_ifstream(CHECKRES);
		if (CSRES) {
			goto PassCheckSVRPFX;
		}
		else
		{
			MessageBox(0, L"RunExtendService 服务异常，无法运行工具", L"MainService", MB_OK);
			cout << " " << endl;
			goto RETURN_BOX;
		}
	    PassCheckSVRPFX:
		system("set/p OpenLink=<Root\\Temp\\RunExtendDialog.data &start Root\\Extend\\RunExtendService.Bat");
		system("del Root\\Temp\\RunExtendDialog.data");
		cout << " " << endl;
		goto RETURN_BOX;
	}
	else
	{
		cout << "Code: ";
		cout << Dialog;
		cout << " is not a command and tool" << endl;
		cout << "Check your type is Correct" << endl;
		cout << " " << endl;
		goto RETURN_BOX;
	}
}