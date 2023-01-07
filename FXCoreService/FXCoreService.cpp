#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<WinUser.h>
#include<cstdlib>

using namespace std;

bool isFileExists_ifstream(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

int main() {
	ShowWindow(GetForegroundWindow(), SW_HIDE);
	Sleep(2000);

	system("echo=%addcode% >>adcode.data"); 
	string $AddCode = "adcode.data";
	ifstream taskReadACD;
	taskReadACD.open("adcode.data");
	taskReadACD >> $AddCode;
	taskReadACD.close();
	system("del adcode.data");

	system("echo=%GuiSet% >>gset.data");
	string $GUI_SHOWMODE = "gset.data";
	ifstream taskReadGUISET;
	taskReadGUISET.open("gset.data");
	taskReadGUISET >> $GUI_SHOWMODE;
	taskReadGUISET.close();

	system("del gset.data");

	string CallCloseService = "FXRuntime.lock";

	if ($AddCode == "%addcode%") {
		MessageBox(0, L"FX Main Core Service. Service For FXTools File Update.", L"FXCoreService", MB_OK);
		return 0;
	}
	if ($AddCode == "update.auto") {
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
			MessageBox(0, L"新版本已经准备就绪，请关闭主程序以进行更新",L"FX Update Service",MB_OK);
		}

		if (SVRNEWKernel == KernelVersionCode) {
			system("echo=Kernel No Update >>Root\\AU.log");
		}
		else
		{
			system("echo=New Update For Kernel >>Root\\AU.log");
			system("echo=https://gitcode.net/PerhapsCanFly/quicklink/-/raw/master/QuickServer/Kernel.exe >>durl.data &echo=Root\\Temp\\NewKernel.exe >>dsp.data &set AddCode=longlink &Root\\Plugin\\FXDS.exe >>Root\\AU.log");
		}

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

			system("Root\\Temp\\DelCoreSCR.bat");

			bool xcdscore = isFileExists_ifstream(xCorePath);
			if (xcdscore) {
				Sleep(3000);
				goto xDelBackTUCCORE;
			}
			ofstream xTaskCopyNewCoreSC;
			xTaskCopyNewCoreSC.open("Root\\Temp\\CopyNewCoreSCR.bat");
			xTaskCopyNewCoreSC << "copy Root\\Temp\\NewCore.exe " << xCorePath;
			xTaskCopyNewCoreSC.close();
			system("Root\\Temp\\CopyNewCoreSCR.bat");

			cout << "正在清理安装临时文件" << endl;
			system("del Root\\Temp\\DelCoreSCR.bat");
			system("del Root\\Temp\\NewCore.exe");
			system("del Root\\Temp\\CopyNewCoreSCR.bat");

		}
		bool xtuckrnl = isFileExists_ifstream(xtaskupdatekern);
		if (xtuckrnl) {
			cout << "正在更新Kernel操作" << endl;
		xDelBackTUCKRNL:
			string xKernelPath = "Root\\Plugin\\Kernel.exe";

			system("del Root\\Plugin\\Kernel.exe");

			bool xcdscore = isFileExists_ifstream(xKernelPath);
			if (xcdscore) {
				Sleep(3000);
				goto xDelBackTUCKRNL;
			}
			system("copy Root\\Temp\\NewKernel.exe Root\\Plugin\\Kernel.exe");

			cout << "正在清理安装临时文件" << endl;
			system("del Root\\Temp\\NewKernel.exe");
		}
		system("echo=Update Check Successfully.  Service Stop >>Root\\AU.log");
		return 0;
	}
}
