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

//wchar_t ת string;
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

//�ж��Ƿ��������
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

//������Դ https://blog.csdn.net/Giser_D/article/details/89763987

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
		settinginfo << "�������ʹ���з��������⣬���Գ���ɾ�����Ŀ¼����������ѡ��" << endl;
		settinginfo << "���ļ��������ж������ļ��Ƿ�����" << endl;
		settinginfo.close();

		ofstream showrootset;
		showrootset.open("Root\\Config\\ShowRoot.cfg");
		showrootset << "off" << endl;
		showrootset.close();

		//Download File
		cout << "��������FXDS" << endl;
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

	//��ȡ���̵�ַ
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
		eula << "   ���ʹ������" << endl;
		eula << " ��������   2023 �� 1 �� 3 �ա��޸�: FoxaXu" << endl;
		eula << "������Ϣ����� https://foxaxudecvin.github.io. ���� foxaxudecvin@outlook.com" << endl;
		eula << " " << endl;
		eula << "��л��������������Խ׶Σ�������Ϣ������ Root\\KernelData.txt�ҵ�" << endl;
		eula << "�������ʹ���з�����©�������������Ǳ��棬��ϵ��ʽ���Դ��������վ��Ҳ����ͨ������" << endl;
		eula << "��������ڿ������Խ׶Σ���������ܻ���ʱ����,δ����ɲ������޸ķ���" << endl;
		eula << " " << endl;
		eula << "FoxaXu 2023.1.3      Github https://github.com/foxaxudecvin" << endl;
		eula << "���ڿ�Դ��Ϣ�����: https://github.com/foxaxudecvin/Code" << endl;
		eula << "���ؼ������ӣ� https://gitcode.net/PerhapsCanFly/quicklink" << endl;
		eula << "�Ķ��������ȷ��ͬ��" << endl;
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


		//��ʼ��������
		string KernelFile = "Root\\Plugin\\Kernel.exe";
		bool returndata = isFileExists_ifstream(KernelFile);
		if (returndata) {
			goto SkipPrepareDownload;
		}
		else
		{
			system("cls");
			cout << "������ɰ�װ�����Ե�" << endl;

			string CDFDService = "Root\\Plugin\\FXDS.exe";
			bool CDFDS = isFileExists_ifstream(CDFDService);
			if (CDFDS) {
				goto CDFDService_PASS;
			}
			else
			{
				MessageBox(0, L"��ʼ��ʧ�ܣ�������������Ƿ����������������ʹ��Windows7ϵͳ������TLS����Ͱ�װKB3140245����, ���ط�����ܻᴥ�� Windows Defender�����������д���", L"MainService", MB_OK);
				goto CLOSE_PART;
			}

		CDFDService_PASS:
			Sleep(1500);
			cout << " " << endl;
			cout << "�����������ط���" << endl;
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/7zip/7z.exe&set setsp=Root\\Plugin\\7z.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/Kernel.exe&set setsp=Root\\Plugin\\Kernel.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/FXCoreService.exe&set setsp=Root\\Plugin\\FXCoreService.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/7zip/7z.dll&set setsp=Root\\Plugin\\7z.dll&Root\\Plugin\\FXDS.exe");
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
				goto CLOSE_PART;
			}
		CDFK_PASS:
			cout << "���ڽ�����һ����װ,���Ե�" << endl;
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
			MessageBox(0, L"FXCoreService �޷����У��볢��ɾ��Root���°�װ",L"MainService",MB_OK);
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
		a = MessageBox(0, L"���Ķ�ע����������", L"MainService", MB_YESNO);
		if (a == 6)
		{
			MessageBox(0, L"����ȷ������ͬ�������", L"MainService", MB_OK);
		}
		else
		{
			MessageBox(0, L"����ȡ������", L"MainService", MB_OK);
			goto CLOSE_PART;
		}

		MessageBox(0, L"���ڳ��������ԣ�ִ�в��ֲ������ܻᱻϵͳ��ȫ��������أ���������������ִ��������Ƽ��㰲װ����ǩ���Խ�����⣬�ڿ���̨����setup-sign���ɰ�װ",L"MainService",MB_OK);

	SkipDisplayE:

		system("set LCode=report &Root\\Plugin\\Kernel.exe");

		string KRVersion = "Root\\Temp\\KernelReport-Version.data";
		bool KRVer = isFileExists_ifstream(KRVersion);
		if (KRVer) {
			goto RKMsg;
		}
		else
		{
			MessageBox(0, L"�ں�û�лظ��������ָ��볢���������л���ɾ��RootĿ¼���°�װ������",L"MainService", MB_OK);
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
		cout << "����crash�ٴ�ȷ��";
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
			MessageBox(0, L"AdminProcess �����쳣���޷�������һ������", L"MainService", MB_OK);
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
			cout << "������һ����Ч�ı���Ŀ¼����exit����" << endl;
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
		cout << "���ؿ�ʼ" << endl;
		cout << "��������ڼ����������������ʾ 0 Mpbs �ٶ����ֶ�ʹ��������������� FXDS.exe ����ֹ����" << endl;

		system("set AddCode=longlink &Root\\Plugin\\FXDS.exe");
		cout << "����ִ�����" << endl;
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
			MessageBox(0, L"SelectFileService �����쳣���޷�������һ������", L"MainService", MB_OK);
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
		cout << "������֤��װ��" << endl;
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
			MessageBox(0, L"��װ��ɣ�ʹ�� list-tool ָ��ɴ򿪹���Ŀ¼", L"MainService", MB_OK);
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
			MessageBox(0, L"��װ�ѱ�ȡ���� ��װ�����ѳ��������������и���", L"MainService", MB_OK);
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
		b = MessageBox(0, L"ȷ��Ҫ��װ����֤����", L"MainService", MB_YESNO);
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
		cout << "��ǰ�Զ�����ģʽΪ:  " << autoupdatemode << endl;
		cout << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "update-off") {
		ofstream autoupdatesetoff;
		autoupdatesetoff.open("Root\\Config\\AutoUpdate.cfg");
		autoupdatesetoff << "off" << endl;
		autoupdatesetoff.close();
		cout << "�Զ������Ѿ��ر�" << endl;
		cout << endl;
		goto RETURN_BOX;
	}
	if (Dialog == "update-open") {
		ofstream autoupdatesetopen;
		autoupdatesetopen.open("Root\\Config\\AutoUpdate.cfg");
		autoupdatesetopen << "open" << endl;
		autoupdatesetopen.close();
		cout << "�Զ������Ѿ�����" << endl;
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
			MessageBox(0, L"PackTool-FXInstaller �����쳣���޷�ִ���������", L"MainService", MB_OK);
			cout << " " << endl;
			goto RETURN_BOX;
		}

	PassCSVRFXI:
		cout << endl;
		system("dir Root\\PackTool");
		cout << "���밲װ��PackDir·��" << endl;
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
		cout << "ֱ���������ƴ򿪹���: ĩβ���� .fxlink " << endl ;
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
			MessageBox(0, L"RunExtendService �����쳣���޷����й���", L"MainService", MB_OK);
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