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

int CountLines(string filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename.c_str());//ios::in 表示以只读的方式读取文件
	if (ReadFile.fail())//文件打开失败:返回0
	{
		return 0;
	}
	else//文件存在
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}

string ReadLine(string filename, int line)
{
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(filename.c_str());
	lines = CountLines(filename);

	if (line <= 0)
	{
		return "Open Failed : Line";
	}
	if (file.fail())
	{
		return "Open Failed : File";
	}
	if (line > lines)
	{
		return "Open Failed : File Over Line";
	}
	while (getline(file, temp) && i < line - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	char CoreVersion[] = "Alpha-Core1.12.2";
	char CodeName[] = "PaperCore";
	char CoreCompileDate[] = "20230103";

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

	if (UserDialogue == "%LCode%") {
		MessageBox(0, L"FXTools Kernel内核，版本信息请使用 set lcode=version&kernel.exe 打开，开源信息请访问：https://github.com/foxaxudecvin/Code", L"Kernel Service", MB_OK);
		return 0;
	}

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
		cout << "正在准备安装: " << endl;;
		Sleep(2000);
		cout << "正在验证配置文件是否完整" << endl;
		string ScanRootFile7z = "Root\\Plugin\\7z.exe";
		bool SRFo7z = isFileExists_ifstream(ScanRootFile7z);
		if (SRFo7z)
		{
			goto SRFoNEXToA;
		}
		else
		{
			MessageBox(0, L"内核初始化失败,内置文件 7z.exe 不完整或丢失，请尝试删除 Root目录后重试", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	SRFoNEXToA:

		string ScanRootFileDService = "Root\\Plugin\\FXDS.exe";
		bool SRFoDS = isFileExists_ifstream(ScanRootFileDService);
		if (SRFoDS)
		{
			goto SRFoNEXToB;
		}
		else
		{
			MessageBox(0, L"内核初始化失败,内置文件 FXDS.exe 不完整或丢失，请尝试删除 Root目录后重试", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	SRFoNEXToB:
		system("cls");
		cout << "正在获取下载链接" << endl;

		string ScanDeleteTempASK = "Root\\Temp\\ASK.data";
		bool SASK = isFileExists_ifstream(ScanDeleteTempASK);
		if (SASK)
		{
			system("del Root\\Temp\\ASK.data");
		}
		system("set setURL=https://foxaxudecvin.github.io/DownloadLink/AutoSetupKernel.data &set setSP=Root\\Temp\\ASK.data &Root\\Plugin\\FXDS.exe");

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

		cout << "正在下载安装包" << endl;

		system("set/p setURL=<Root\\Temp\\ASK.data &set setSP=Root\\Temp\\ASPack.zip &Root\\Plugin\\FXDS.exe");

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
		cout << "正在解压安装包" << endl;
		system("Root\\Plugin\\7z.exe x -oRoot\\Extend Root\\Temp\\ASPack.zip");
		system("cls");
		cout << "正在验证你的安装" << endl;
		Sleep(600);
		string CheckExtendPack = "Root\\Extend\\Pack.data";
		bool CExtend = isFileExists_ifstream(CheckExtendPack);
		if (CExtend)
		{
			goto PassSetupExtend;
		}
		else
		{
			system("cls");
			MessageBox(0,L"安装失败，无法解压Extend文件夹，请尝试删除root目录以重试", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	PassSetupExtend:
		system("cls");
		cout << "正在安装附加插件" << endl;
		system("set setURL=https://foxxaaservice.github.io/PackStore/Download/PackStore-Release.zip &set setSP=Root\\Temp\\TempStoreSetup.zip &Root\\Plugin\\FXDS.exe");
		system("Root\\Plugin\\7z.exe x -oRoot\\Temp\\PackStoreSetup Root\\Temp\\TempStoreSetup.zip >nul");

		system("set WorkMode=auto &set InstallPack=Root\\Temp\\PackStoreSetup&Root\\Extend\\PackTool-FXInstaller.Bat");
		system("rd /s /q Root\\Temp\\PackStoreSetup");
		system("del /q Root\\Temp\\TempStoreSetup.zip");

		system("cls");
		system("set/p startprocess=<Root\\ProcessName.cfg &start cmd /c %startprocess%");
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

	if (UserDialogue == "getpack") {
		string ScanToolsFile7z = "Root\\Plugin\\7z.exe";
		bool STFo7z = isFileExists_ifstream(ScanToolsFile7z);
		if (STFo7z) {
			goto PASS7zCheck;
		}
		else
		{
			MessageBox(0, L"7z插件异常，无法完成解压行动, 验证安装包失败", L"Kernel Process MessageBox", MB_OK);
			ofstream AKRSetPack;
			AKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			AKRSetPack << "false" << endl;
			AKRSetPack.close();
			return 0;
		}

		PASS7zCheck:
		//解压包到 Root\\Temp\\PackInstallerTemp

		system("Root\\Plugin\\7z.exe x -oRoot\\Temp\\PackInstallerTemp %FilePath%");
		system("cls");

		string CheckPackNormal = "Root\\Temp\\PackInstallerTemp\\Installtag.txt";
		bool CheckPN = isFileExists_ifstream(CheckPackNormal);
		if (CheckPN) {

			string CheckPackCert = "Root\\Temp\\PackInstallerTemp\\Installtag.txt";
			bool CheckPC = isFileExists_ifstream(CheckPackCert);
			if (CheckPC) {
				goto PassCheckCertMode;
			}
			else
			{
				MessageBox(0, L"安装包未声明证书模式(CertMode), 无法完成安装包验证", L"Kernel Process MessageBox", MB_OK);
				ofstream BKRSetPack;
				BKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
				BKRSetPack << "false" << endl;
				BKRSetPack.close();
				return 0;
			}

		PassCheckCertMode:

			string PackCert = "null";
			ifstream PackCertCheck;
			PackCertCheck.open("Root\\Temp\\PackInstallerTemp\\Security\\CertMode.cfg");
			PackCertCheck >> PackCert;
			PackCertCheck.close();

			if (PackCert == "off") {
				system("set LCode=NoCertCheck &start /b Root\\Plugin\\Kernel.exe");
				return 0;
			}
			if (PackCert == "open-self") {
				system("set LCode=CertSelfCheckMode &start /b Root\\Plugin\\Kernel.exe");
				return 0;
			}
			if (PackCert == "open-sha256") {
				system("set LCode=CertSHA256CheckMode &start /b Root\\Plugin\\Kernel.exe");
				return 0;
			}
			MessageBox(0, L"该安装包使用的签名方式未知，不兼容当前版本，无法完成安装包验证", L"Kernel Process MessageBox", MB_OK);
			ofstream CKRSetPack;
			CKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			CKRSetPack << "false" << endl;
			CKRSetPack.close();
			return 0;

		}
		else
		{
			MessageBox(0, L"文件结构不符合FXPack格式, 验证安装包失败", L"Kernel Process MessageBox", MB_OK);
			ofstream DKRSetPack;
			DKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			DKRSetPack << "false" << endl;
			DKRSetPack.close();
			return 0;
		}
	}

	// 安装数字签名
	if (UserDialogue == "setup-sign-fxtool") {

		string WRITEADMINCheck = "%HOMEDRIVE%\\TEST";
		bool WATC = isFileExists_ifstream(WRITEADMINCheck);
		if (WATC) {
			system("del %HOMEDRIVE%\\TEST");
		}
		system("echo=%HOMEDRIVE%\\TEST>>Root\\Temp\\TryCode.data");

		string CKC = "nul";
		ifstream CheckCode;
		CheckCode.open("Root\\Temp\\TryCode.data");
		CheckCode >> CKC;
		CheckCode.close();

		system("echo=A >>%HOMEDRIVE%\\TEST");
		system("del Root\\Temp\\TryCode.data");

		string WRITEADMINTest = CKC;
		bool WAT = isFileExists_ifstream(WRITEADMINTest);

		if (WAT){
			system("del %HOMEDRIVE%\\TEST");
		cout << "正在下载证书" << endl;
		system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/FoxaXu.cer&set setSP=%temp%\\PubhicCert.cer&Root\\Plugin\\FXDS.exe");
		cout << "正在下载安装工具" << endl;
		system("set setURL=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/certmgr.exe&set setSP=Root\\Temp\\CertMgr.exe&Root\\Plugin\\FXDS.exe");
		system("cls");
		cout << "正在安装证书" << endl << endl;
		Sleep(2000);
		system("Root\\Temp\\CertMgr.exe -add %temp%\\PubhicCert.cer -s -r localMachine AuthRoot");
		MessageBox(0, L"执行完成，请打开文件属性，点击数字签名一栏查看数字签名是否有效, 安装目录：当前用户\\第三方根证书颁发机构\\证书\\FoxaXu",L"Kernel Service",MB_OK);
		cout << "正在清理文件" << endl;
		system("del %temp%\\PubhicCert.cer");
		system("del Root\\Temp\\CertMgr.exe");
		return 0;
		}
		else
		{
			cout << "请提升权限以完成操作" << endl;
			return 0;
		}
	}

	// 插件安装模块

	//   无签名确认
	if (UserDialogue == "NoCertCheck"){
	cout << "此安装包没有签名认证，来源未知" << endl;
	cout << "此安装包不包含任何作者信息" << endl;
	cout << "请谨慎安装" << endl;

	int AppMessageBox = 0;

	AppMessageBox = MessageBox(0, L"确定要安装该包吗", L"Kernel Process MessageBox", MB_YESNO);
	if (AppMessageBox == 6)
	{
		system("set LCode=ApplySetupStart &start /b Root\\Plugin\\Kernel.exe");
		return 0;
	}
	else
	{
		ofstream EKRSetPack;
		EKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		EKRSetPack << "false" << endl;
		EKRSetPack.close();
		return 0;
	}
	}

	//   自身签名验证
	if (UserDialogue == "CertSelfCheckMode") {

	//获取安装包信息

	string PackAuth = "null";
	ifstream GetPackAuth;
	GetPackAuth.open("Root\\Temp\\PackInstallerTemp\\Author.cfg");
	GetPackAuth >> PackAuth;
	GetPackAuth.close();

	string PackMsg = "null";
	ifstream GetPackMsg;
	GetPackMsg.open("Root\\Temp\\PackInstallerTemp\\Message.txt");
	GetPackMsg >> PackMsg;
	GetPackMsg.close();

	cout << "此安装包使用来自作者自身的签名，无法验证其信息是否被修改" << endl;
	cout << "由于无法对信息进行验证，我们无法确定是否来自官方, 请谨慎安装" << endl;
	cout << "来源: ";
	cout << PackAuth << endl;
	cout << "详细信息: ";
	cout << PackMsg << endl;
	cout << " " << endl;

	int BppMessageBox = 0;

	BppMessageBox = MessageBox(0, L"确定要安装该包吗", L"Kernel Process MessageBox", MB_YESNO);
	if (BppMessageBox == 6)
	{
		system("set LCode=ApplySetupStart &start /b Root\\Plugin\\Kernel.exe");
		return 0;
	}
	else
	{
		ofstream EKRSetPack;
		EKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		EKRSetPack << "false" << endl;
		EKRSetPack.close();
		return 0;
	}
	}

	//   带验证的 SHA256 签名验证
	if (UserDialogue == "CertSHA256CheckMode") {
	// 验证Sha256签名
		cout << "正在验证安装包签名" << endl;
	system("Root\\Plugin\\7z.exe h -scrcsha256 %FilePath% >>Root\\Temp\\GetFileSha256.data");
	///////////////////////////////////////////////////////////////// Copy /////////////////////////////////////////////////////////

	//原代码地址 :https://blog.csdn.net/qq_44747572/article/details/121436815
	string filename = "Root\\Temp\\GetFileSha256.data";
	int line = 11;
	string SHA256Code = ReadLine(filename, line);

	///////////////////////////////////////////////////////////////// Copy /////////////////////////////////////////////////////////

	system("del Root\\Temp\\GetFileSha256.data");

	ofstream OutCertCodeData;
	OutCertCodeData.open("Root\\Temp\\KR-PackCertData.data");
	OutCertCodeData << SHA256Code << endl;
	OutCertCodeData.close();

	system("set/p setURL=<Root\\Temp\\PackInstallerTemp\\Security\\CertURL.cfg &set setSP=Root\\Temp\\GetURLCertCode.data &Root\\Plugin\\FXDS.exe");

	int a = 0;
	
	string ScanDFGUCC = "Root\\Temp\\GetURLCertCode.data";
	bool SDFGUCC = isFileExists_ifstream(ScanDFGUCC);
	if (SDFGUCC) {
		goto StartVerifyCert;
	}
	else
	{	
		a = MessageBox(0, L"获取签名信息失败，无法验证该包签名是否有效，是否重试", L"Kernel Process MessageBox", MB_YESNO);
		if (a == 6)
		{
			goto Try_again_VCert;
		}
		else
		{
			ofstream XXXAKRSetPack;
			XXXAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			XXXAKRSetPack << "false" << endl;
			XXXAKRSetPack.close();
			return 0;
		}

	Try_again_VCert:

		system("set/p setURL=<Root\\Temp\\PackInstallerTemp\\Security\\CertURL.cfg &set setSP=Root\\Temp\\GetURLCertCode.data &Root\\Plugin\\FXDS.exe");

		int a = 0;

		string AgainScanDFGUCC = "Root\\Temp\\GetURLCertCode.data";
		bool ASDFGUCC = isFileExists_ifstream(AgainScanDFGUCC);
		if (ASDFGUCC) {
			goto StartVerifyCert;
		}
		else 
		{
			ofstream XXXAKRSetPack;
			XXXAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			XXXAKRSetPack << "false" << endl;
			XXXAKRSetPack.close();
			return 0;
		}
		MessageBox(0, L"无法连接到服务器，验证签名失败，如果你想安装请尝试将 Security\\CertMode.cfg 内容改为off", L"Kernel Process MessageBox", MB_OK);
		ofstream SSSAKRSetPack;
		SSSAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		SSSAKRSetPack << "false" << endl;
		SSSAKRSetPack.close();
		return 0;
	}
StartVerifyCert:

	string VCServiceCK = "Root\\Extend\\VerifyCode.Bat";
	bool VCSCK = isFileExists_ifstream(VCServiceCK);
	if (VCSCK)
	{
		goto VCSCKPass;
	}
	else
	{
		MessageBox(0, L"VerifyCode 服务异常，无法启动，安装失败", L"Kernel Process MessageBox", MB_OK);
		ofstream BXASSSAKRSetPack;
		BXASSSAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		BXASSSAKRSetPack << "false" << endl;
		BXASSSAKRSetPack.close();
		return 0;
	}
	VCSCKPass:

	system("set/p CodeA=<Root\\Temp\\KR-PackCertData.data &set/p CodeB=<Root\\Temp\\GetURLCertCode.data &Root\\Extend\\VerifyCode.bat");

	string VerifyReport = "null";
	ifstream GetVerifyReport;
	GetVerifyReport.open("Root\\Temp\\VerifyReport.data");
	GetVerifyReport >> VerifyReport;
	GetVerifyReport.close();

	system("del Root\\Temp\\VerifyReport.data");

	if (VerifyReport == "PASS") {
		goto CertPass;
	}
	else
	{
		MessageBox(0, L"安装失败，该安装包的内容已被更改，与签名时不一致，签名无效", L"Kernel Process MessageBox", MB_OK);
		ofstream ASSSAKRSetPack;
		ASSSAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		ASSSAKRSetPack << "false" << endl;
		ASSSAKRSetPack.close();
		return 0;
	}
CertPass:

	string XPackAuth = "null";
	ifstream GetXPackAuth;
	GetXPackAuth.open("Root\\Temp\\PackInstallerTemp\\Author.cfg");
	GetXPackAuth >> XPackAuth;
	GetXPackAuth.close();

	string XPackMsg = "null";
	ifstream GetXPackMsg;
	GetXPackMsg.open("Root\\Temp\\PackInstallerTemp\\Message.txt");
	GetXPackMsg >> XPackMsg;
	GetXPackMsg.close();

	string PackCURL = "null";
	ifstream GetPackCURL;
	GetPackCURL.open("Root\\Temp\\PackInstallerTemp\\Security\\CertURL.cfg");
	GetPackCURL >> PackCURL;
	GetPackCURL.close();

	string PackCA = "null";
	ifstream GetPackCA;
	GetPackCA.open("Root\\Temp\\PackInstallerTemp\\Security\\CertAuthor.cfg");
	GetPackCA >> PackCA;
	GetPackCA.close();

	system("cls");

	cout << "安装包已通过签名检查" << endl;
	cout << "我们已经与服务器确认，该安装包未经修改，与签名时内容一致，但需要你确认服务器URL验证链接是否正确" << endl;
	cout << "来源: ";
	cout << XPackAuth << endl;
	cout << "签名来源: ";
	cout << PackCA << endl;
	cout << "签名验证链接: ";
	cout << PackCURL << endl;
	cout << "详细信息: ";
	cout << XPackMsg << endl;

	int CppMessageBox = 0;

	CppMessageBox = MessageBox(0, L"确定要安装该包吗", L"Kernel Process MessageBox", MB_YESNO);
	if (CppMessageBox == 6)
	{
		system("set LCode=ApplySetupStart &start /b Root\\Plugin\\Kernel.exe");
		return 0;
	}
	else
	{
		ofstream EKRSetPack;
		EKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
		EKRSetPack << "false" << endl;
		EKRSetPack.close();
		return 0;
	}
}

	//  开始安装插件
	if (UserDialogue == "ApplySetupStart") {

		string SetupFXInstallFileCheck = "Root\\Extend\\PackTool-FXInstaller.Bat";
		bool SFXIF = isFileExists_ifstream(SetupFXInstallFileCheck);
		if (SFXIF)
		{
			system("set WorkMode=auto &set InstallPack=Root\\Temp\\PackInstallerTemp&Root\\Extend\\PackTool-FXInstaller.Bat");
			return 0;
		}
		else
		{
			MessageBox(0, L"PackTool-FXInstaller 服务异常，无法启动，安装失败", L"Kernel Process MessageBox", MB_OK);
			ofstream XASSSAKRSetPack;
			XASSSAKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			XASSSAKRSetPack << "false" << endl;
			XASSSAKRSetPack.close();
			return 0;
		}
	}

	cout << "Unknown Command: ";
	cout << UserDialogue << endl;
	return 0;
}