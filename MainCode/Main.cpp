#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<urlmon.h>
#include<Psapi.h>
#include<TlHelp32.h>
#include<io.h>
#pragma comment(lib,"URlmon.lib")

using namespace std;

bool g_ProcessRun = false;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

//wchar_t 转 string;
void Wchar_tToString(string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}

//判断是否进程运行
// STRING process_name
bool isProcessRun(string process_name)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
		wchar_t* process_str = pe.szExeFile;
		string current_process_name;
		Wchar_tToString(current_process_name, process_str);
		if (current_process_name == process_name) {
			g_ProcessRun = true;
			break;
		}
	}
	CloseHandle(hSnapshot);
	return g_ProcessRun;
}

//代码来源 https://blog.csdn.net/Giser_D/article/details/89763987

int main(int argc, char** argv) {
RELOAD:
	remove("$FXProcessMark");
	remove("FXRuntime.lock");
	remove("FXExitReport.data");
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	char version[] = "Build_1021";
	char pubdate[] = "20230108";

	ofstream OutVersionINFO;
	OutVersionINFO.open("Root\\CoreVersion.cfg");
	OutVersionINFO << version;
	OutVersionINFO.close();

	ofstream OutPDINFO;
	OutPDINFO.open("Root\\CoreReleaseTime.cfg");
	OutPDINFO << pubdate;
	OutPDINFO.close();

	string filename = "Root\\SettingInfo.txt";
	bool ret = isFileExists_ifstream(filename);
	if (ret)
	{	
		system("attrib Root -s -a -h");
		goto SkipLoadConfig;
	}
	else
	{
		system("md Root");
		system("md Root\\Config");
		system("md Root\\Logs");
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

		ofstream autoupdate;
		autoupdate.open("Root\\Config\\AutoUpdate.cfg");
		autoupdate << "open" << endl;
		autoupdate.close();

		ofstream settinginfo;
		settinginfo.open("Root\\SettingInfo.txt");
		settinginfo << "Release Version: ";
		settinginfo << version << endl;
		settinginfo << "Public Date: ";
		settinginfo << pubdate << endl;
		settinginfo << "如果你在使用中发现了问题，可以尝试删除这个目录以重置所有选项" << endl;
		settinginfo << "此文件仅用于判断配置文件是否正常" << endl;
		settinginfo.close();

		ofstream showrootset;
		showrootset.open("Root\\Config\\ShowRoot.cfg");
		showrootset << "off" << endl;
		showrootset.close();

		//Download File
		cout << "正在下载FXDS" << endl;
		HRESULT PrepFXDS = URLDownloadToFileW(
			nullptr,
			L"https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/FXDS.exe",
			L"Root\\Plugin\\FXDS.exe",
			0,
			nullptr
		);
		goto SkipLoadConfig;
}

CLOSE_PART:
	system("echo=ExitNormal>>FXExitReport.data");
	system("del FXRuntime.lock");
	return 0;

SkipLoadConfig:

	//获取进程地址
	errno_t	err = 0;
	char	fileName[100] = { 0 };
	char    processFullName[_MAX_PATH] = { 0 };
	char    processName[0x40] = { 0 };
	DWORD   dwpid = 0;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	dwpid = GetCurrentProcessId();
	GetModuleFileNameA(NULL, processFullName, _MAX_PATH); 

	tmp1 = strrchr((char*)processFullName, '\\');
	tmp2 = strrchr((char*)processFullName, '.');
	memcpy(processName, tmp1 + 1, min(tmp2 - tmp1 - 1, 0x40)); 

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

	string showrootdata = "Null";
	ifstream tasksrd;
	tasksrd.open("Root\\Config\\ShowRoot.cfg");
	tasksrd >> showrootdata;
	tasksrd.close();

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
	kerneldata << "Copyright FoxaXu 2023" << endl;
	kerneldata.close();
		ofstream eula;
		eula.open("Root\\EULA.txt");
		eula << "   软件使用条款" << endl;
		eula << " 更新日期   2023 年 1 月 3 日。修改: FoxaXu" << endl;
		eula << "更多信息请访问 https://foxaxudecvin.github.io. 邮箱 foxaxudecvin@outlook.com" << endl;
		eula << " " << endl;
		eula << "感谢你打开这款软件，测试阶段，部分信息可以在 Root\\KernelData.txt找到" << endl;
		eula << "如果你在使用中发现有漏洞，可以向我们报告，联系方式可以打开上面的网站。也可以通过邮箱" << endl;
		eula << "此软件处于开发测试阶段，此条款可能会随时更新,未经许可不允许修改发布" << endl;
		eula << " " << endl;
		eula << "FoxaXu 2023.1.3      Github https://github.com/foxaxudecvin" << endl;
		eula << "关于开源信息请访问: https://github.com/foxaxudecvin/Code" << endl;
		eula << "下载加速链接： https://gitcode.net/PerhapsCanFly/quicklink" << endl;
		eula << "阅读完成请点击确定同意" << endl;
		eula << " " << endl;
		eula << "Version: ";
		eula << version << endl;
		eula << "PubDate: ";
		eula << pubdate << endl;
		eula.close();

		ofstream ProcessNameOut;
		ProcessNameOut.open("Root\\ProcessName.cfg");
		ProcessNameOut << processName << ".exe" << endl;
		ProcessNameOut.close();

		ofstream ProcessPathOut;
		ProcessPathOut.open("Root\\ProcessPath.cfg");
		ProcessPathOut << processFullName << endl;
		ProcessPathOut.close();


		//初始化与下载
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
				goto CLOSE_PART;
			}

		CDFDService_PASS:
			Sleep(1500);
			cout << " " << endl;
			cout << "正在启动下载服务" << endl;
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/7zip/7z.exe&set setsp=Root\\Plugin\\7z.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/Kernel.exe&set setsp=Root\\Plugin\\Kernel.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/FXCoreService.exe&set setsp=Root\\Plugin\\FXCoreService.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/7zip/7z.dll&set setsp=Root\\Plugin\\7z.dll&Root\\Plugin\\FXDS.exe");
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
				goto CLOSE_PART;
			}
		CDFK_PASS:
			cout << "正在进行下一步安装,请稍等" << endl;
			system("set LCode=setup &Root\\Plugin\\Kernel.exe");
			goto CLOSE_PART;
		}
		system("cls");
	SkipPrepareDownload:

		string servicecore = "Root\\Plugin\\FXCoreService.exe";
		bool sctest = isFileExists_ifstream(servicecore);
		if (sctest) {}
		else
		{
			MessageBox(0, L"FXCoreService 无法运行，请尝试删除Root重新安装",L"MainService",MB_OK);
			goto CLOSE_PART;
		}

		string autoupdateswitch = "off";
		ifstream taskaus;
		taskaus.open("Root\\Config\\AutoUpdate.cfg");
		taskaus >> autoupdateswitch;
		taskaus.close();

		string CSUCK = "adcode.data";

		if (settingSde == "offskip") {
			goto SkipLoadService;
		}
		if (autoupdateswitch == "open") {
			system("set AddCode=update.auto &set switchGUI=show &start /b Root\\Plugin\\FXCoreService.exe >nul 2>nul");
			Sleep(1500);
		}
		system("set AddCode=lockroot&set switchGUI=show&start /b Root\\Plugin\\FXCoreService.exe >nul 2>nul");
		Sleep(1500);
		system("set AddCode=crash_check&set switchGUI=hide&start Root\\Plugin\\FXCoreService.exe >nul 2>nul");
		Sleep(1500);

		SkipLoadService:

		ofstream OpenLockRumtime;
		OpenLockRumtime.open("FXRuntime.lock");
		OpenLockRumtime << "a";

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
			goto CLOSE_PART;
		}

		MessageBox(0, L"由于程序特殊性，执行部分操作可能会被系统安全软件所拦截，如果你遇到了这种错误，我们推荐你安装数字签名以解决问题，在控制台输入setup-sign即可安装",L"MainService",MB_OK);

	SkipDisplayE:

		system("set LCode=report &Root\\Plugin\\Kernel.exe");

		string KRVersion = "Root\\Temp\\KernelReport-Version.data";
		bool KRVer = isFileExists_ifstream(KRVersion);
		if (KRVer) {
			goto RKMsg;
		}
		else
		{
			MessageBox(0, L"内核没有回复主程序的指令，请尝试重新运行或者删除Root目录重新安装本程序",L"MainService", MB_OK);
			goto CLOSE_PART;
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

		if (showrootdata == "open") {
			system("attrib Root -s -a -h");
		}
		else
		{
			system("attrib Root +s +a +h");
		}

	system("cls");

	system("start /b Root\\Config\\DisplayColor.bat");
	Sleep(1000);
	cout << "Type Command or Program" << endl;
	cout << "Kernel Version: ";
	cout << version << endl;
RETURN_BOX:
	remove("$FXProcessMark");
	system("title FoxaXu Dialogue");
	string Dialog = "Null.noanytype";
	cout << "Command\\";
	getline(cin, Dialog);
	system("echo=Mark For Command>>$FXProcessMark");
	if (Dialog == "") {
		cout << " " << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "exit") {
		OpenLockRumtime.close();
		remove("$FXProcessMark");
		goto CLOSE_PART;
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
		cout << "Process Path: ";
		cout << processFullName << "   " << "PID: " << dwpid << endl;
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
		cout << "crash       -Debug For Crash Test" << endl;
		cout << "openwork   -Open Root Folder" << endl;
		cout << "admin      -Run To Administrator" << endl;
		cout << "download    -Download File" << endl;
		cout << "setup-package  -Install Package" << endl;
		cout << "setup-sign         -setup our Application Digital Signature" << endl;
		cout << "setroot-show/hide           -Set Root Folder Show or Hide" << endl;
		cout << "update-open/off          -Auto Update Manager" << endl;
		cout << "remove     -Uninstall Package" << endl;
		cout << "list-tool    -List All Tools" << endl;
		cout << "repair       -Repair Tools" << endl;
		cout << endl;
		cout << "FXTools Copyright FoxaXu 2022" << endl << endl;
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
		OpenLockRumtime.close();
		goto RELOAD;
	}
	if (Dialog == "crash") {
		string realcrash;
		cout << "输入crash再次确认";
		getline(cin, realcrash);
		if (realcrash == "crash") {
			return 0;
		}
		goto RETURN_BOX;
	}
	if (Dialog == "openwork") {
		system("explorer %cd%\\Root");
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
		goto CLOSE_PART;
	}
	if (Dialog == "download") {
		string DialogURL = "Null.noanytype";
		cout << "URL>";
		getline(cin, DialogURL);
		if (DialogURL == "exit") {
			cout << endl;
			goto RETURN_BOX;
		}
		if (DialogURL == "") {
			cout << endl;
			goto RETURN_BOX;
		}
		string DialogSavePath = "nul";
		RETURN_TYPE_SAVEPATH:
		cout << "Save Path>";
		getline(cin,DialogSavePath);

		if (DialogSavePath == "") {
			cout << "请输入一个有效的保存目录或者exit返回" << endl;
			cout << endl;
			goto RETURN_TYPE_SAVEPATH;
		}
		if (DialogSavePath == "exit") {
			cout << endl;
			goto RETURN_BOX;
		}

		ofstream OutDownloadTaskURL;
		OutDownloadTaskURL.open("durl.data");
		OutDownloadTaskURL << DialogURL;
		OutDownloadTaskURL.close();

		ofstream OutDownloadTaskSP;
		OutDownloadTaskSP.open("dsp.data");
		OutDownloadTaskSP << DialogSavePath;
		OutDownloadTaskSP.close();
		cout << "下载开始" << endl;
		cout << "如果下载期间任务管理器长期显示 0 Mpbs 速度请手动使用任务管理器结束 FXDS.exe 以终止下载" << endl;

		system("set AddCode=longlink &Root\\Plugin\\FXDS.exe");
		cout << "任务执行完成" << endl;
		cout << endl;
		goto RETURN_BOX;
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
		system("echo=cancel>>Root\\Temp\\OpenReport.data");
		taskreadsf.open("Root\\Temp\\OpenReport.data");
		taskreadsf >> SelectPackFile;
		taskreadsf.close();
		if (SelectPackFile == "cancel") {
			cout << endl;
			goto RETURN_BOX;
		}
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
	if (Dialog == "setup-sign") {
		int b;
		b = MessageBox(0, L"确定要安装数字证书吗", L"MainService", MB_YESNO);
		if (b == 6) {
			system("set LCode=setup-sign-fxtool&Root\\Plugin\\Kernel.exe");
			cout << endl;
			goto RETURN_BOX;
		}
		else
		{
			cout << "Cancel" << endl << endl;
			goto RETURN_BOX;
		}
	}
	if (Dialog == "setroot-show") {
		system("attrib Root -s -a -h");
		ofstream showrootsetopen;
		showrootsetopen.open("Root\\Config\\ShowRoot.cfg");
		showrootsetopen << "open" << endl;
		showrootsetopen.close();
		cout << "Set Root Show Mode Successfully" << endl << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "setroot-hide") {
		ofstream showrootsetoff;
		showrootsetoff.open("Root\\Config\\ShowRoot.cfg");
		showrootsetoff << "off" << endl;
		showrootsetoff.close();
		system("attrib Root +s +a +h");
		cout << "Set Root Show Mode Successfully" << endl << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "update") {
		string autoupdatemode = "unknown";
		ifstream taskausc;
		taskausc.open("Root\\Config\\AutoUpdate.cfg");
		taskausc >> autoupdatemode;
		taskausc.close();
		cout << "当前自动更新模式为:  " << autoupdatemode << endl;
		cout << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "update-off") {
		ofstream autoupdatesetoff;
		autoupdatesetoff.open("Root\\Config\\AutoUpdate.cfg");
		autoupdatesetoff << "off" << endl;
		autoupdatesetoff.close();
		cout << "自动更新已经关闭" << endl;
		cout << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "update-open") {
		ofstream autoupdatesetopen;
		autoupdatesetopen.open("Root\\Config\\AutoUpdate.cfg");
		autoupdatesetopen << "open" << endl;
		autoupdatesetopen.close();
		cout << "自动更新已经启用" << endl;
		cout << endl;
		goto RETURN_BOX;
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