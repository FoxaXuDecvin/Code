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
		settinginfo << "�������ʹ���з��������⣬���Գ���ɾ�����Ŀ¼����������ѡ��" << endl;
		settinginfo << "���ļ��������ж������ļ��Ƿ�����" << endl;
		settinginfo.close();

		//Download File
		cout << "��������FXDS" << endl;
		HRESULT PrepFXDS = URLDownloadToFileW(
			nullptr,
			L"https://foxaxudecvin.github.io/warehouse/FXDS.exe",
			L"Root\\Plugin\\FXDS.exe",
			0,
			nullptr
		);
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
		eula << "���ڿ�Դ��Ϣ�����: https://github.com/foxaxudecvin/Code" << endl;
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
				return 0;
			}

		CDFDService_PASS:
			Sleep(1500);
			cout << " " << endl;
			cout << "�����������ط���" << endl;
			system("set setURL=https://foxaxudecvin.github.io/warehouse/7z.exe&set setsp=Root\\Plugin\\7z.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://foxxaaservice.github.io/Kernel.exe&set setsp=Root\\Plugin\\Kernel.exe&Root\\Plugin\\FXDS.exe");
			system("set setURL=https://foxaxudecvin.github.io/warehouse/7z.dll&set setsp=Root\\Plugin\\7z.dll&Root\\Plugin\\FXDS.exe");
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
			MessageBox(0, L"AdminProcess �����쳣���޷�������һ������", L"MainService", MB_OK);
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
		taskreadsf.open("Root\\Temp\\OpenReport.data");
		taskreadsf >> SelectPackFile;
		taskreadsf.close();
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