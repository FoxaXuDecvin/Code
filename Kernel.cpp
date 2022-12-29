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
	ReadFile.open(filename.c_str());//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	if (ReadFile.fail())//�ļ���ʧ��:����0
	{
		return 0;
	}
	else//�ļ�����
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

	char CoreVersion[] = "Alpha-Core1.10.4";
	char CodeName[] = "PaperCore";
	char CoreCompileDate[] = "20221229_1";

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
		system("set A-URL=https://foxaxudecvin.github.io/DownloadLink/AutoSetupKernel.data &set A-SavePath=Root\\Temp\\ASK.data &set tasknum=1 &set EngineMode=auto &%cd%\\Root\\Plugin\\Foxa-DService.bat");

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

		system("set/p A-URL=<Root\\Temp\\ASK.data &set A-SavePath=Root\\Temp\\ASPack.zip &set tasknum=1 &set EngineMode=auto &Root\\Plugin\\Foxa-DService.bat");

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
		cout << "���ڽ�ѹ��װ��" << endl;
		system("Root\\Plugin\\7z.exe x -oRoot\\Extend Root\\Temp\\ASPack.zip");
		cout << "������֤��İ�װ" << endl;
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
			MessageBox(0,L"��װʧ�ܣ��޷���ѹExtend�ļ��У��볢��ɾ��rootĿ¼������", L"Kernel Prepare Setup", MB_OK);
			return 0;
		}
	PassSetupExtend:
		system("cls");
		MessageBox(0, L"��װ��ɣ���������Զ�����", L"Kernel Prepare Setup", MB_OK);
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
			MessageBox(0, L"7z����쳣���޷���ɽ�ѹ�ж�, ��֤��װ��ʧ��", L"Kernel Process MessageBox", MB_OK);
			ofstream AKRSetPack;
			AKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			AKRSetPack << "false" << endl;
			AKRSetPack.close();
			return 0;
		}

		PASS7zCheck:
		//��ѹ���� Root\\Temp\\PackInstallerTemp

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
				MessageBox(0, L"��װ��δ����֤��ģʽ(CertMode), �޷���ɰ�װ����֤", L"Kernel Process MessageBox", MB_OK);
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
			MessageBox(0, L"�ð�װ��ʹ�õ�ǩ����ʽδ֪�������ݵ�ǰ�汾���޷���ɰ�װ����֤", L"Kernel Process MessageBox", MB_OK);
			ofstream CKRSetPack;
			CKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			CKRSetPack << "false" << endl;
			CKRSetPack.close();
			return 0;

		}
		else
		{
			MessageBox(0, L"�ļ��ṹ������FXPack��ʽ, ��֤��װ��ʧ��", L"Kernel Process MessageBox", MB_OK);
			ofstream DKRSetPack;
			DKRSetPack.open("Root\\Temp\\kernel-report-setpk.data");
			DKRSetPack << "false" << endl;
			DKRSetPack.close();
			return 0;
		}
	}

	// �����װģ��

	//   ��ǩ��ȷ��
	if (UserDialogue == "NoCertCheck"){
	cout << "�˰�װ��û��ǩ����֤����Դδ֪" << endl;
	cout << "�˰�װ���������κ�������Ϣ" << endl;
	cout << "�������װ" << endl;

	int AppMessageBox = 0;

	AppMessageBox = MessageBox(0, L"ȷ��Ҫ��װ�ð���", L"Kernel Process MessageBox", MB_YESNO);
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

	//   ����ǩ����֤
	if (UserDialogue == "CertSelfCheckMode") {

	//��ȡ��װ����Ϣ

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

	cout << "�˰�װ��ʹ���������������ǩ�����޷���֤����Ϣ�Ƿ��޸�" << endl;
	cout << "�����޷�����Ϣ������֤�������޷�ȷ���Ƿ����Թٷ�, �������װ" << endl;
	cout << "��Դ: ";
	cout << PackAuth << endl;
	cout << "��ϸ��Ϣ: ";
	cout << PackMsg << endl;
	cout << " " << endl;

	int BppMessageBox = 0;

	BppMessageBox = MessageBox(0, L"ȷ��Ҫ��װ�ð���", L"Kernel Process MessageBox", MB_YESNO);
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

	//   ����֤�� SHA256 ǩ����֤
	if (UserDialogue == "CertSHA256CheckMode") {
	// ��֤Sha256ǩ��
		cout << "������֤��װ��ǩ��" << endl;
	system("Root\\Plugin\\7z.exe h -scrcsha256 %FilePath% >>Root\\Temp\\GetFileSha256.data");
	///////////////////////////////////////////////////////////////// Copy /////////////////////////////////////////////////////////

	//ԭ�����ַ :https://blog.csdn.net/qq_44747572/article/details/121436815
	string filename = "Root\\Temp\\GetFileSha256.data";
	int line = 11;
	string SHA256Code = ReadLine(filename, line);

	///////////////////////////////////////////////////////////////// Copy /////////////////////////////////////////////////////////

	system("del Root\\Temp\\GetFileSha256.data");

	ofstream OutCertCodeData;
	OutCertCodeData.open("Root\\Temp\\KR-PackCertData.data");
	OutCertCodeData << SHA256Code << endl;
	OutCertCodeData.close();

	system("set tasknum=1 &set EngineMode=auto &set/p A-URL=<Root\\Temp\\PackInstallerTemp\\Security\\CertURL.cfg &set A-SavePath=Root\\Temp\\GetURLCertCode.data &start /b Root\\Plugin\\Foxa-DService.bat");

	Sleep(6000);

	int a = 0;
	
	string ScanDFGUCC = "Root\\Temp\\GetURLCertCode.data";
	bool SDFGUCC = isFileExists_ifstream(ScanDFGUCC);
	if (SDFGUCC) {
		goto StartVerifyCert;
	}
	else
	{	
		a = MessageBox(0, L"���ӷ�������ʱ���޷����ǩ����֤���Ƿ�����", L"Kernel Process MessageBox", MB_YESNO);
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

		system("set tasknum=1 &set EngineMode=auto &set/p A-URL=<Root\\Temp\\PackInstallerTemp\\Security\\CertURL.cfg &set A-SavePath=Root\\Temp\\GetURLCertCode.data &start /b Root\\Plugin\\Foxa-DService.bat");

		Sleep(12000);

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
		MessageBox(0, L"�޷����ӵ�����������֤ǩ��ʧ�ܣ�������밲װ�볢�Խ� Security\\CertMode.cfg ���ݸ�Ϊoff", L"Kernel Process MessageBox", MB_OK);
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
		MessageBox(0, L"VerifyCode �����쳣���޷���������װʧ��", L"Kernel Process MessageBox", MB_OK);
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
		MessageBox(0, L"��װʧ�ܣ��ð�װ���������ѱ����ģ���ǩ��ʱ��һ�£�ǩ����Ч", L"Kernel Process MessageBox", MB_OK);
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

	cout << "��װ����ͨ��ǩ�����" << endl;
	cout << "�����Ѿ��������ȷ�ϣ��ð�װ��δ���޸ģ���ǩ��ʱ����һ�£�����Ҫ��ȷ�Ϸ�����URL��֤�����Ƿ���ȷ" << endl;
	cout << "��Դ: ";
	cout << XPackAuth << endl;
	cout << "ǩ����Դ: ";
	cout << PackCA << endl;
	cout << "ǩ����֤����: ";
	cout << PackCURL << endl;
	cout << "��ϸ��Ϣ: ";
	cout << XPackMsg << endl;

	int CppMessageBox = 0;

	CppMessageBox = MessageBox(0, L"ȷ��Ҫ��װ�ð���", L"Kernel Process MessageBox", MB_YESNO);
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

	//  ��ʼ��װ���
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
			MessageBox(0, L"PackTool-FXInstaller �����쳣���޷���������װʧ��", L"Kernel Process MessageBox", MB_OK);
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