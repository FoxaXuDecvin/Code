// file name :  wxcore.exe
// MainService
// Copyright FoxaXu

#include<Windows.h>
#include"D:\CppHeader\winapicore.h"

int main(int argc, char* argv[]) {
	string langname = readini(".\\config.ini", "Settings", "DefaultLanguage");
	string $Langfile = "Lang\\" + langname;

	string WXCoreTitle = readini($Langfile, "ProcessTitle", "WXCore");
	SetConsoleTitle(WXCoreTitle.c_str());
	if (argc == 1) {
		cout << "WinXetor Service" << endl;
		cout << "this program should not running in this mode" << endl;
		return 0;
	}
	if (argc == 2) {
		int alang = 0;
		alang < argc;

		alang++;
		string paraA = argv[alang];
		if (paraA == "lockfolder") {
			MessageBox(0, "Service Start failed:  Parameter not full", "MainService Program", MB_OK);
			return 0;
		}

		if (paraA == "lockfile") {
			MessageBox(0, "Service Start failed:  Parameter not full", "MainService Program", MB_OK);
			return 0;
		}

		if (paraA == "update") {
			string a = ".\\config.ini";
			bool retCFG = existcheck(a);
			if (retCFG) {}
			else {
				MessageBox(0, "WinXetor Update Failed: ERROR. Path no config file", "WinXetor Service", MB_OK);
				return 0;
			}
			string wxver = readini(".\\config.ini", "ConfigHeader", "Version");
			string wxupAPI = readini(".\\config.ini", "ConfigHeader", "updateAPI");
			string SvCode = readini(".\\config.ini", "ConfigHeader", "ServerVerifyCode");
			string SvAPI = readini(".\\config.ini", "ConfigHeader", "serverVURL");

			string BackINFO = geturlcode(wxupAPI);
			string VerifyCode = geturlcode(SvAPI);
			if (BackINFO == wxver) {
				if (VerifyCode == SvCode) {
					string LangUpdateNO = readini($Langfile, "UpdateUI", "NoUpdate");
					cout << LangUpdateNO << endl;
					getchar();
					return 0;
				}
				goto ServerCheckUnPass;
			}
			else {
				if (VerifyCode == SvCode) {
					string LangUpdateNew = readini($Langfile, "UpdateUI", "NewUpdate");
					string LangUDWT = readini($Langfile, "UpdateUI", "AskUpdate");
					cout << LangUpdateNew<< endl;
					cout << "Version :  " + BackINFO << endl;
					cout << LangUDWT << endl;
					string getkey;
					cout << endl;
					cout << "Select <y/n> $";
					getline(cin, getkey);
					system("cls");
					if (getkey == "y") {
						string LangCSVR = readini($Langfile, "UpdateUI", "ConnectSVR");
						cout << LangCSVR << endl;
						string UAPIDown = readini(".\\config.ini", "Update", "UpdateProfile");
						
						clearfolder("temp~update");
						string retTUUfile = "temp~update\\update.ini";

						ReCONSVR:
						URLDown(UAPIDown, retTUUfile);
						Sleep(3000);
						bool retTUCHK = existcheck(retTUUfile);
						if (retTUCHK) {}
						else {
							cout << "Download Profile failed" << endl;
							cout << "Reconnecting server" << endl;
							goto ReCONSVR;
						}

						string UHeadINFO = readini(retTUUfile, "title", "headinfo");
						string UMainINFO = readini(retTUUfile, "title", "updateinfo");

						system("cls");
						cout << "Installing New Update" << endl;
						cout << UHeadINFO << endl;
						cout << UMainINFO << endl;
						cout << "Please wait ... downloading new file" << endl;

						string NewWX = readini(retTUUfile, "GetURL", "WinXetor");
						string NewWXCore = readini(retTUUfile, "GetURL", "wxcore");
						string NewConfig = readini(retTUUfile, "GetURL", "config");
						
						string NewWXF = "temp~update\\WinXetor.exe";
						string NewWXCoreF = "temp~update\\wxcore.exe";
						string NewConfigF = "temp~update\\config.ini";
						ReDownloadWX:
						URLDown(NewWX, NewWXF);
						bool retWX = existcheck(NewWXF);
						if (retWX) {}
						else {
							goto ReDownloadWX;
						}

						ReDownloadWXCore:
						URLDown(NewWXCore, NewWXCoreF); 
						bool retWXCore = existcheck(NewWXCoreF);
						if (retWXCore) {}
						else {
							goto ReDownloadWXCore;
						}

					    ReDownloadConfig:
						URLDown(NewConfig, NewConfigF);
						bool retWXConfig = existcheck(NewConfigF);
						if (retWXConfig) {}
						else {
							goto ReDownloadConfig;
						}
						system("cls");
						cout << "Start Install..." << endl;

						ReInstallNU:
						remove(".\\WinXetor.exe");
						string rmfile = ".\\WinXetor.exe";
						bool retWXNowFile = existcheck(rmfile);
						if (retWXNowFile) {
							cout << "Close WinXetor to install New Update" << endl;
							cout << "Press Enter key to try again" << endl;
							getchar();
							goto ReInstallNU;
						}

						string $nameself = getselfinfo("processfullname");
						rename($nameself.c_str(), "wxcore.old.exe");

						string backuplangname = readini(".\\config.ini", "Settings", "DefaultLanguage");
						string autoupdatename = readini(".\\config.ini", "Settings", "AutoUpdate");
						remove(".\\config.ini");
						CopyFile(NewConfigF.c_str(), ".\\config.ini",0);
						writeini(".\\config.ini", "Settings", "DefaultLanguage", backuplangname);
						writeini(".\\config.ini", "Settings", "AutoUpdate", autoupdatename);

						CopyFile(NewWXF.c_str(), ".\\WinXetor.exe", 0);
						CopyFile(NewWXCoreF.c_str(), ".\\wxcore.exe", 0);

						ofstream UpdateRemoveOld;
						UpdateRemoveOld.open(".\\updatescript.bat");
						UpdateRemoveOld << "@echo off" << endl;
						UpdateRemoveOld << "echo=Install New Update" << endl;
						UpdateRemoveOld << "echo=Please wait" << endl;
						UpdateRemoveOld << "start wxcore.exe refreshlang" << endl;
						UpdateRemoveOld << "ping 127.0.0.1 -n 3 2>nul >nul" << endl;
						UpdateRemoveOld << "del wxcore.old.exe" << endl;
						UpdateRemoveOld << "del anticrash.exe" << endl;
						UpdateRemoveOld << "rd /s /q temp~update" << endl;
						UpdateRemoveOld << "start WinXetor.exe" << endl;
						UpdateRemoveOld << "del updatescript.bat" << endl;
						UpdateRemoveOld << "exit" << endl;
						UpdateRemoveOld.close();

						ShellExecute(0, "open", ".\\updatescript.bat", 0, 0, SW_SHOW);
						return 0;
					}
					if (getkey == "n") {
						cout << "User Cancel" << endl;
						getchar();
						return 0;
					}
				}
				goto ServerCheckUnPass;
			}
		ServerCheckUnPass:
			string MsgSCUP = readini($Langfile, "ServiceUI", "ServerVUnPass");
			MessageBox(0, MsgSCUP.c_str(), "Update Failed", MB_OK);
			return 0;
		}

		if (paraA == "autoupdate") {

			string a = ".\\config.ini";
			bool retCFG = existcheck(a);
			if (retCFG) {}
			else {
				MessageBox(0, "WinXetor Update Failed: ERROR. Path no config file", "WinXetor Service", MB_OK);
				return 0;
			}
			string wxver = readini(".\\config.ini", "ConfigHeader", "Version");
			string wxupAPI = readini(".\\config.ini", "ConfigHeader", "updateAPI");
			string SvCode = readini(".\\config.ini", "ConfigHeader", "ServerVerifyCode");
			string SvAPI = readini(".\\config.ini", "ConfigHeader", "serverVURL");

			string BackINFO = geturlcode(wxupAPI);
			string VerifyCode = geturlcode(SvAPI);
			if (BackINFO == wxver) {
				if (VerifyCode == SvCode) {
					return 0;
				}
				else {
					return 1;
				}
			}
			if (VerifyCode == SvCode) {}
			else {
				return 0;
			}

			string LangCSVR = readini($Langfile, "UpdateUI", "ConnectSVR");
			cout << LangCSVR << endl;
			string UAPIDown = readini(".\\config.ini", "Update", "UpdateProfile");

			clearfolder("temp~update");
			string retTUUfile = "temp~update\\update.ini";

		xReCONSVR:
			URLDown(UAPIDown, retTUUfile);
			Sleep(3000);
			bool retTUCHK = existcheck(retTUUfile);
			if (retTUCHK) {}
			else {
				goto xReCONSVR;
			}

			string UHeadINFO = readini(retTUUfile, "title", "headinfo");
			string UMainINFO = readini(retTUUfile, "title", "updateinfo");

			system("cls");
			cout << UHeadINFO << endl;
			cout << UMainINFO << endl;

			string NewWX = readini(retTUUfile, "GetURL", "WinXetor");
			string NewWXCore = readini(retTUUfile, "GetURL", "wxcore");
			string NewConfig = readini(retTUUfile, "GetURL", "config");

			string NewWXF = "temp~update\\WinXetor.exe";
			string NewWXCoreF = "temp~update\\wxcore.exe";
			string NewConfigF = "temp~update\\config.ini";
		xReDownloadWX:
			URLDown(NewWX, NewWXF);
			bool retWX = existcheck(NewWXF);
			if (retWX) {}
			else {
				goto xReDownloadWX;
			}

		xReDownloadWXCore:
			URLDown(NewWXCore, NewWXCoreF);
			bool retWXCore = existcheck(NewWXCoreF);
			if (retWXCore) {}
			else {
				goto xReDownloadWXCore;
			}

		xReDownloadConfig:
			URLDown(NewConfig, NewConfigF);
			bool retWXConfig = existcheck(NewConfigF);
			if (retWXConfig) {}
			else {
				goto xReDownloadConfig;
			}
			system("cls");
			cout << "Start Install..." << endl;

		xReInstallNU:
			remove(".\\WinXetor.exe");
			string rmfile = ".\\WinXetor.exe";
			bool retWXNowFile = existcheck(rmfile);
			if (retWXNowFile) {
				Sleep(3000);
				goto xReInstallNU;
			}

			string $nameself = getselfinfo("processfullname");
			rename($nameself.c_str(), "wxcore.old.exe");

			string backuplangname = readini(".\\config.ini", "Settings", "DefaultLanguage");
			string autoupdatename = readini(".\\config.ini", "Settings", "AutoUpdate");
			remove(".\\config.ini");
			CopyFile(NewConfigF.c_str(), ".\\config.ini", 0);
			writeini(".\\config.ini", "Settings", "DefaultLanguage", backuplangname);
			writeini(".\\config.ini", "Settings", "AutoUpdate", autoupdatename);

			CopyFile(NewWXF.c_str(), ".\\WinXetor.exe", 0);
			CopyFile(NewWXCoreF.c_str(), ".\\wxcore.exe", 0);

			ofstream UpdateRemoveOld;
			UpdateRemoveOld.open(".\\updatescript.bat");
			UpdateRemoveOld << "@echo off" << endl;
			UpdateRemoveOld << "start wxcore.exe refreshlang" << endl;
			UpdateRemoveOld << "ping 127.0.0.1 -n 3 2>nul >nul" << endl;
			UpdateRemoveOld << "del wxcore.old.exe" << endl;
			UpdateRemoveOld << "del anticrash.exe" << endl;
			UpdateRemoveOld << "rd /s /q temp~update" << endl;
			UpdateRemoveOld << "start WinXetor.exe" << endl;
			UpdateRemoveOld << "del updatescript.bat" << endl;
			UpdateRemoveOld << "exit" << endl;
			UpdateRemoveOld.close();

			ShellExecute(0, "open", ".\\updatescript.bat", 0, 0, SW_HIDE);
			return 0;
		}

		if (paraA == "refreshlang") {
			string fname = "7z";
			bool ret7zfolder = existfolder(fname);
			if (ret7zfolder) {}
			else {
				mdfolder("7z");
				URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.exe", "7z\\7z.exe");
				URLDown("https://gitcode.net/FoxaXu1/download/-/raw/master/7z/7z.dll", "7z\\7z.dll");
			}
			cout << "Update Language Please wait..." << endl;
			cout << "This update maybe need very long time" << endl;
			URLDown("https://developer.foxaxu.com/WinXetor/download/lang.7z", "lang.7z");
			clearfolder("Lang");
			ShellExecute(0, "open", "7z\\7z.exe", "x -oLang lang.7z",0,SW_HIDE);
			Sleep(3000);
			remove("lang.7z");
			return 0;
		}

		string charcode = "Service Start failed: Unknown Parameter: " + paraA;
			MessageBox(0, charcode.c_str(), "MainService Program", MB_OK);
			return 0;
	}
	if (argc == 3) {
		int alang = 0;
		alang < argc;

		alang++;
		string paraA = argv[alang];
		alang++;
		string paraB = argv[alang];

		if (paraA == "lockfolder") {
			ofstream LockFolder;
			LockFolder.open(paraB + "\\session.lock");
			LockFolder << "A" << endl;

			ofstream lockswitch;
			lockswitch.open("lockmark~" + paraB + "~switch.mark");
			lockswitch << "lockswitch" << endl;
			lockswitch.close();
			bool retSWITCH;
			string Abc = "lockmark~" + paraB + "~switch.mark";

		waitswitch:
			Sleep(2000);
			retSWITCH = existcheck(Abc);
			if (retSWITCH) {
				goto waitswitch;
			}
			LockFolder.close();

			string PRME = paraB + "\\session.lock";
			remove(PRME.c_str());
			return 0;
		}

		if (paraA == "lockfile") {
			ifstream LockFolder;
			LockFolder.open(paraB);

			ofstream lockswitch;
			lockswitch.open("lockfile~" + paraB + "~switch.mark");
			lockswitch << "lockswitch" << endl;
			lockswitch.close();
			bool retSWITCH;
			string Abc = "lockfile~" + paraB + "~switch.mark";

		waitswitchfile:
			Sleep(2000);
			retSWITCH = existcheck(Abc);
			if (retSWITCH) {
				goto waitswitchfile;
			}
			LockFolder.close();
			return 0;
		}
		string charcode = "Service Start failed: Unknown Parameter: " + paraA;
		MessageBox(0, charcode.c_str(), "MainService Program", MB_OK);
		return 0;
	}
}