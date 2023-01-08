#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<cstdlib>
#include<WinUser.h>

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

int main() {
	string $EAddCode = "null.set.Environment";
	string $EGUI_SHOWMODE = "null.set.Environment";

	system("echo=%AddCode%>>tmpadcode.data");
	system("echo=%switchGUI%>>tmpgset.data");

	ifstream taskreadACode;
	taskreadACode.open("tmpadcode.data");
	taskreadACode >> $EAddCode;
	taskreadACode.close();

	ifstream taskreaGSM;
	taskreaGSM.open("tmpgset.data");
	taskreaGSM >> $EGUI_SHOWMODE;
	taskreaGSM.close();

	remove("tmpadcode.data");
	remove("tmpgset.data");

	system("echo=null>>adcode.data");
	system("echo=null>>gset.data");
	string $XAddCode;
	string $XGUI_SHOWMODE;

	ifstream XtaskreadACode;
	XtaskreadACode.open("adcode.data");
	XtaskreadACode >> $XAddCode;
	XtaskreadACode.close();

	ifstream XtaskreadGSM;
	XtaskreadGSM.open("gset.data");
	XtaskreadGSM >> $XGUI_SHOWMODE;
	XtaskreadGSM.close();

	remove("adcode.data");
	remove("gset.data");

		string CallCloseService = "FXRuntime.lock";
		string $AddCode = $XAddCode;
		string $GUI_SHOWMODE = $XGUI_SHOWMODE;

	ReCommand:

		if ($GUI_SHOWMODE == "hide") {
			ShowWindow(GetForegroundWindow(), SW_HIDE);
		}

		if ($GUI_SHOWMODE == "show") {
			ShowWindow(GetForegroundWindow(), SW_SHOW);
		}

		LPCWSTR EXCOMMAND = stringToLPCWSTR($AddCode);
		if ($XAddCode == "null") {
			if ($EAddCode == "%AddCode%") {
			MessageBox(0, L"Error Unknown Command", EXCOMMAND, MB_OK);
			return 0;
		}
		}
		
		if ($XAddCode == "null") {
			goto NotUseXMode;
		}
		// Command
		if ($AddCode == "update.auto") {
			Sleep(5000);

			string autoupdatelogfile = "Root\\AU.log";
			bool aufcheck = isFileExists_ifstream(autoupdatelogfile);
			if (aufcheck) {
				system("del Root\\au.log");
			}
			system("echo=Auto Update Service Run Start >>Root\\AU.log");
			system("echo=Start Time %date% %time% >>Root\\AU.log");

			system("echo=Get Info... >>Root\\AU.log");

			string VNPV = "Root\\CoreVersion.cfg";
			bool vnpvdt = isFileExists_ifstream(VNPV);
			if (vnpvdt) {}
			else
			{
				system("echo=Get Info Failed : Core Version >>Root\\AU.log");
				system("echo=Service Exit >>Root\\AU.log");
				return 0;
			}
			string CoreVersionCode = "nul";
			ifstream taskreadcvc;
			taskreadcvc.open("Root\\CoreVersion.cfg");
			taskreadcvc >> CoreVersionCode;
			taskreadcvc.close();

			system("set LCode=report &Root\\Plugin\\Kernel.exe");
			string taskFileKNC = "Root\\Temp\\KernelReport-Version.data";
			bool rdfknc = isFileExists_ifstream(taskFileKNC);
			if (rdfknc) {}
			else
			{
				system("echo=Get Info Failed: Kernel Info >>Root\\AU.log");
				system("echo=Service Exit >>Root\\AU.log");
				return 0;
			}

			string KernelVersionCode = "nul";
			ifstream taskreadKVerC;
			taskreadKVerC.open("Root\\Temp\\KernelReport-Version.data");
			taskreadKVerC >> KernelVersionCode;
			taskreadKVerC.close();
			system("del Root\\Temp\\KernelReport-Version.data");
			system("del Root\\Temp\\KernelReport-BuildDate.data");
			system("del Root\\Temp\\KernelReport-CodeName.data");

			system("echo=Connect Server >>Root\\AU.log");

		UpdateReturn:
			system("echo=Check Version Info >>Root\\AU.log");
			system("echo=Sync Time Info:  %date% %time% >>Root\\AU.log");
			system("echo=https://foxaxudecvin.github.io/vercheck/krnlver.data >>durl.data &echo=Root\\Temp\\KrnlVer.data >>dsp.data &set AddCode=longlink &Root\\Plugin\\FXDS.exe >>Root\\AU.log");
			system("echo=https://foxaxudecvin.github.io/vercheck/corever.data >>durl.data &echo=Root\\Temp\\VerCore.data >>dsp.data &set AddCode=longlink &Root\\Plugin\\FXDS.exe >>Root\\AU.log");
			string IFEKV = "Root\\Temp\\KrnlVer.data";
			string IFECV = "Root\\Temp\\VerCore.data";
			bool ckvdata = isFileExists_ifstream(IFEKV);
			if (ckvdata) {
				system("echo=Get Kernel Version Message Succsed >>Root\\AU.log");
			}
			else
			{
				system("echo=Get Message FAILED : Kernel Version>>Root\\AU.log");
				system("echo=some time later will check update again >>Root\\AU.log");
				Sleep(6000);
				system("del FXRuntime.lock");
				bool checkupA = isFileExists_ifstream(CallCloseService);
				if (checkupA) {}
				else
				{
					return 0;
				}
				goto UpdateReturn;
			}

			bool ccoredata = isFileExists_ifstream(IFECV);
			if (ccoredata) {
				system("echo=Get Core Version Message Succsed >>Root\\AU.log");
			}
			else
			{
				system("echo=Get Message FAILED :Core Version >>Root\\AU.log");
				system("echo=some time later will check update again >>Root\\AU.log");
				Sleep(6000);
				system("del FXRuntime.lock");
				bool checkupB = isFileExists_ifstream(CallCloseService);
				if (checkupB) {}
				else
				{
					return 0;
				}
				goto UpdateReturn;
			}

			string SVRNEWCore = "nul";
			string SVRNEWKernel = "nul";

			ifstream RDSNC;
			RDSNC.open("Root\\Temp\\VerCore.data");
			RDSNC >> SVRNEWCore;
			RDSNC.close();

			ifstream RDSNK;
			RDSNK.open("Root\\Temp\\KrnlVer.data");
			RDSNK >> SVRNEWKernel;
			RDSNK.close();

			system("del Root\\Temp\\KrnlVer.data");
			system("del Root\\Temp\\VerCore.data");

			if (SVRNEWCore == CoreVersionCode) {
				system("echo=Core No Update >>Root\\AU.log");
			}
			else
			{
				system("echo=New Update For Core >>Root\\AU.log");
				system("echo=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/FoxaXu.exe >>durl.data &echo=Root\\Temp\\NewCore.exe >>dsp.data &set AddCode=longlink &Root\\Plugin\\FXDS.exe >>Root\\AU.log");
				MessageBox(0, L"新版本已经准备就绪，在你准备好后关闭主程序以进行更新", L"FX Update Service", MB_OK);
			}

			if (SVRNEWKernel == KernelVersionCode) {
				system("echo=Kernel No Update >>Root\\AU.log");
			}
			else
			{
				system("echo=New Update For Kernel >>Root\\AU.log");
				system("echo=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/Kernel.exe >>durl.data &echo=Root\\Temp\\NewKernel.exe >>dsp.data &set AddCode=longlink &Root\\Plugin\\FXDS.exe >>Root\\AU.log");
			}

			string CSUCK = "adcode.data";
		WAITAGAIN:
			bool checkservicepartSSC = isFileExists_ifstream(CSUCK);
			if (checkservicepartSSC) {
				Sleep(1000);
				goto WAITAGAIN;
			}

			ofstream twadcodea;
			twadcodea.open("adcode.data$TmpWtA");
			twadcodea << "update.installer" << endl;
			twadcodea.close();
			rename("adcode.data$TmpWtA", "adcode.data");

			ofstream twgsetA;
			twgsetA.open("gset.data$TmpWtA");
			twgsetA << "random" << endl;
			twgsetA.close();
			rename("gset.data$TmpWtA", "gset.data");
			ShellExecute(0, L"open", L"Root\\Plugin\\FXCoreService.exe", 0, 0, SW_HIDE);
			return 0;
		}
		if ($AddCode == "update.installer") {
			Sleep(1200);
			string xtaskupdatecore = "Root\\Temp\\NewCore.exe";
			string xtaskupdatekern = "Root\\Temp\\NewKernel.exe";

			bool xtuccore = isFileExists_ifstream(xtaskupdatecore);
			if (xtuccore) {
			xDelBackTUCCORE:
				string xCorePath = "nul";
				ifstream xTaskReadCorePath;
				xTaskReadCorePath.open("Root\\ProcessPath.cfg");
				xTaskReadCorePath >> xCorePath;
				xTaskReadCorePath.close();

				ofstream xTaskCreatDelScript;
				xTaskCreatDelScript.open("Root\\Temp\\DelCoreSCR.bat");
				xTaskCreatDelScript << "del ";
				xTaskCreatDelScript << xCorePath;
				xTaskCreatDelScript.close();

				ShellExecute(0, L"open", L"Root\\Temp\\DelCoreSCR.bat", 0, 0, SW_HIDE);

				bool xcdscore = isFileExists_ifstream(xCorePath);
				if (xcdscore) {
					Sleep(3000);
					goto xDelBackTUCCORE;
				}
				ofstream xTaskCopyNewCoreSC;
				xTaskCopyNewCoreSC.open("Root\\Temp\\CopyNewCoreSCR.bat");
				xTaskCopyNewCoreSC << "copy Root\\Temp\\NewCore.exe " << xCorePath;
				xTaskCopyNewCoreSC.close();

				ShellExecute(0, L"open", L"Root\\Temp\\CopyNewCoreSCR.bat", 0, 0, SW_HIDE);

				remove("del Root\\Temp\\DelCoreSCR.bat");
				remove("del Root\\Temp\\NewCore.exe");
				remove("del Root\\Temp\\CopyNewCoreSCR.bat");
			}
			bool xtuckrnl = isFileExists_ifstream(xtaskupdatekern);
			if (xtuckrnl) {
			xDelBackTUCKRNL:
				string xKernelPath = "Root\\Plugin\\Kernel.exe";

				remove("del Root\\Plugin\\Kernel.exe");

				bool xcdscore = isFileExists_ifstream(xKernelPath);
				if (xcdscore) {
					Sleep(3000);
					goto xDelBackTUCKRNL;
				}
				WinExec("cmd /c copy Root\\Temp\\NewKernel.exe Root\\Plugin\\Kernel.exe", SW_HIDE);

				cout << "正在清理安装临时文件" << endl;
				remove("del Root\\Temp\\NewKernel.exe");
			}
			return 0;
		}
		if ($AddCode == "lockroot") {
			Sleep(1000);
			ofstream LockRootSession;
			LockRootSession.open("Root\\Session.Lock");
			LockRootSession << "LockMode" << endl;

		CheckReturnSESSION:
			Sleep(3000);
			remove("FXRuntime.lock");
			bool UnLockRootTest = isFileExists_ifstream(CallCloseService);
			if (UnLockRootTest) {
				goto NOTNOWENDCRS;
			}
			else
			{
				LockRootSession.close();
				remove("Root\\Session.Lock");
				return 0;
			}
		NOTNOWENDCRS:
			goto CheckReturnSESSION;
		}
		if ($AddCode == "crash_check") {
			Sleep(2000);
		recheckpoint:
			Sleep(3000);
			remove("FXRuntime.lock");
			string CKF = "FXRuntime.lock";
			bool CheckCrash = isFileExists_ifstream(CKF);
			if (CheckCrash) {
				goto recheckpoint;
			}
			else
			{
				Sleep(1500);
				string ReportLinkFile = "FXExitReport.data";
				bool CheckExit = isFileExists_ifstream(ReportLinkFile);
				if (CheckExit) {
					remove("FXExitReport.data");
					return 0;
				}
				else
				{
					string CheckRealCrash = "$FXProcessMark";
					bool ccreal = isFileExists_ifstream(CheckRealCrash);
					if (ccreal) {
						remove("$FXProcessMark");
						MessageBox(0, L"程序异常退出，我们无法确定原因，如果是你在执行命令时主动关闭，则可以忽略本信息，非正常退出可能会导致已执行的操作与未执行的操作产生冲突，如果软件发生了崩溃，请向我们报告，详情请看数字签名页的邮箱，如果你没有看到数字签名，则你可能正在使用非正版或者内测版，建议您重新下载与安装", L"FX Crash Report MessageBox", MB_OK);
						return 0;
					}
					else
					{
						return 0;
					}
				}
			}

		}

	NotUseXMode:
		$AddCode = $EAddCode;
		$GUI_SHOWMODE = $EGUI_SHOWMODE;
		$XAddCode = "Disabled";
		EXCOMMAND = stringToLPCWSTR($AddCode);
		goto ReCommand;
		// Copyright FoxaXu 2023 FXCoreService
}