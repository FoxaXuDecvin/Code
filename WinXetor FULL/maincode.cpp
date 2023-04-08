// WinXetor
// Copyright FoxaXu

#include<Windows.h>
#include"D:\CppHeader\winapicore.h"
#include"D:\CppHeader\7zipAPI.h"
#include <winternl.h>

using namespace std;

string DialogMSG(string MSGINFO) {
	MessageBox(0, MSGINFO.c_str(), "notice", MB_OK);
	return 0;
}

int main(int argc, char* argv[]) {

	string $String;
	string PFName = getselfinfo("processfullname");
	int PPIDx = getpid();
	string PPID = to_string(PPIDx);

	bool AdminTestRT = testAdmin("C:");
	if (AdminTestRT) {
		cmarkfile("runinfo.bin", "Administrator");
	}
	else {
		cmarkfile("runinfo.bin", "Local User");
	}

	string RunAdminInfo = ReadText("runinfo.bin", 1);
	remove("runinfo.bin");

	ofstream logs;
	ofstream runlock;
	logs.open("winxetor.log");
	string SSLockName = "wx~" + PPID + "~session.lock";
	runlock.open(SSLockName);

	string $ReloadPoint;
	$ReloadPoint = "off";
	reloadmark:
	SetConsoleTitle("WinXetor Loading");

	logs << "Start Load WinXetor" << endl;

	bool retlang = existfolder("Lang");
	if (retlang){}
	else {
		logs << "ERROR: Lang Folder is missing" << endl;
		MessageBox(0, "Language file is missing. WinXetor Cannot Launch", "Launch Error", MB_OK);
		return 1;
	}
	bool retconfig = existfile("config.ini");
	if (retconfig) {}
	else
	{
		logs << "ERROR: CONFIG.INI is missing" << endl;
		MessageBox(0, "Configure file is missing in .\\config.ini", "Launch Error", MB_OK);
		return 1;
	}
	string langname = readini(".\\config.ini", "Settings", "DefaultLanguage");
	string DevFun = readini(".\\config.ini", "Settings", "DeveloperFunction");
	string langformat = readini(".\\config.ini", "ConfigHeader", "LangFormat");
	string wxversion = readini(".\\config.ini", "ConfigHeader", "Version");
	
	string n7zfile = "7z\\7z.exe";
	logs << "Language File: " + langname << endl;
	logs << "WinXetor Version: " + wxversion << endl;

	cout << "Developer Function switch mode :  " << DevFun << endl;

	string $Langfile = "Lang\\" + langname;
	bool retlangfile = existcheck($Langfile);
	if (retlangfile) {}
	else {
		$String = "Cannot read language file  " + $Langfile;
		logs << "ERROR: " + $String << endl;
		MessageBox(0, $String.c_str(), "Launch Error", MB_OK);
		writeini(".\\config.ini", "Settings", "DefaultLanguage", "en-us.lang");
		goto reloadmark;
	}
	
	string langfileformat = readini($Langfile, "Head", "LangFormat");
	if (langfileformat == langformat) {}
	else {
		int a = 0;
		string langmob = "This Language maybe cannot running in this WinXetor Version. Lang Ver:  " + langfileformat + "  Your WinXetor Version:  " + langformat + "  Do you want load this language?";
		a = MessageBox(0, langmob.c_str(), "Support Warning", MB_YESNO);
		if (a == 6) {}
		else {
			writeini(".\\config.ini", "Settings", "DefaultLanguage","en-us.lang");
			goto reloadmark;
		}
	}

	// Start Load
	string langtitlebar = readini($Langfile, "LangUI", "titlebar");
	SetConsoleTitle(langtitlebar.c_str());
	logs << "Loading Files ..." << endl;

	string langmsg = readini($Langfile, "LangUI", "langmsg");
	string wxmsg = readini($Langfile, "LangUI", "wxmsg");
	string langerror = readini($Langfile, "LangUI", "langerror");
	string langgetnotice = readini($Langfile, "LangUI", "langgetnotice");

	//out version info
	cout << langmsg << endl;
	cout << wxmsg << " " << wxversion << endl;

	bool retwxcore = existfile("wxcore.exe");
	if (retwxcore) {}
	else {
		logs << "ERROR: Core file missing.  wxcore.exe" << endl;
		cout << langerror << "CORE_FILE_MISSING";
		MessageBox(0, "Core file is missing .\\wxcore.exe", "Launch Error", MB_OK);
		return 0;
	}

	bool retdlcore = existfile("dl.exe");
	if (retdlcore) {
		logs << "dl.exe is ready" << endl;
	}
	else {
		logs << "Download File : DL.exe" << endl;
		logs << "URL: https://developer.foxaxu.com/download/cppcore/dl.exe" << endl;
		URLDown("https://developer.foxaxu.com/download/cppcore/dl.exe", "dl.exe");
	}

	bool retace = existfile("anticrash.exe");
	if (retace) {
		logs << "anticrash.exe is ready" << endl;
	}
	else {
		logs << "Download File : DL.exe" << endl;
		logs << "URL: https://developer.foxaxu.com/WinXetor/download/anticrash.exe" << endl;
		URLDown("https://developer.foxaxu.com/WinXetor/download/anticrash.exe", "anticrash.exe");
	}

	bool retwxscr = existfile("wxscript.exe");
	if (retace) {
		logs << "wxscript is ready" << endl;
	}
	else {
		logs << "Download File : WXScript.exe" << endl;
		logs << "URL: https://developer.foxaxu.com/WinXetor/download/wxscript.exe" << endl;
		URLDown("https://developer.foxaxu.com/WinXetor/download/wxscript.exe", "wxscript.exe");
	}

	string apireadcharU = readini(".\\config.ini", "Settings", "AutoUpdate");
	if (apireadcharU == "open") {
		ShellExecute(0, "open", "wxcore.exe", "autoupdate", 0, SW_HIDE);
	}

	if ($ReloadPoint == "open") {
		goto SkipLoadANTICRASH;
	}
	ShellExecute(0, "open", "anticrash.exe", SSLockName.c_str(), 0, SW_HIDE);
	

	SkipLoadANTICRASH:

	cout << langgetnotice << endl;

	bool retnotice = URLDown("https://api.foxaxu.com/public/notice.txt", "notice.txt");
	if (retnotice) {}
	else {
		ofstream write;
		write.open("notice.txt");
		write << "Connect Server Failed" << endl;
		write.close();
	}

	system("cls");
	system("type notice.txt");

	string ShellTitle = readini($Langfile, "ShellUI", "Title");
	string ShellTitleHelps = readini($Langfile, "ShellUI", "ShellHelp");

	string WinXetorShellTitle = readini($Langfile, "ProcessTitle", "WinXetor");
	SetConsoleTitle(WinXetorShellTitle.c_str());

	//Print Shell
	cout << endl;
	cout << ShellTitle << endl;
	cout << ShellTitleHelps << endl;

	string shellkey;
	string markfile = ".\\workcheck.mark";
BackShell:
	remove(markfile.c_str());
	cout << endl;
	cout << "WinXetor " + wxversion + " Shell  $";
	getline(cin, shellkey);
	logs << "Enter command :  " + shellkey << endl;

	cmarkfile(markfile, "markrun");

	if (shellkey == "update") {
		ShellExecute(0, "open", "wxcore.exe", "update", 0, SW_SHOW);
		goto BackShell;
	}
	if (shellkey == "version") {
		string LINFO = readini($Langfile, "Head", "LangINFO");
		string AUSwitch = readini(".\\config.ini", "Settings", "AutoUpdate");
		cout << "WinXetor Windows Tool" << endl;
		cout << "Version  : " + wxversion << endl;
		cout << "Language :  " + LINFO << endl;
		cout << "Auto Update:  " + AUSwitch << endl;
		cout << "Authority:  " + RunAdminInfo << endl;

		if (DevFun == "enabled") {
			cout << "Process Full Name :  " + PFName << endl;
			cout << "Process PID :  " + PPID << endl;
			cout << "Developer Function is Enabled" << endl;
			cout << "use offdebugmode command off" << endl;
		}

		cout << "Thanks your visit" << endl;
		goto BackShell;
	}
	if (shellkey == "reload") {
		$ReloadPoint = "open";
		goto reloadmark;
	}
	if (shellkey == "help") {
		cout << "WinXetor Windows Tool" << endl;
		cout << "    update   -Check update" << endl;
		cout << "    refreshlang   -refresh language" << endl;
		cout << "    version   -List version" << endl;
		cout << "    help   -list help" << endl;
		cout << "    reload   -Reload WinXetor" << endl;
		cout << "    setlang   -Set New Language for WinXetor from Lang Folder" << endl;
		cout << "    <open/off>-autoupdate  - Set Enabled or Disabled Auto Update" << endl;
		cout << endl << "Copyright FoxaXu" << endl;
		goto BackShell;
	}
	if (shellkey == "web") {
		ShellExecute(0, "open", "https://developer.foxaxu.com/WinXetor", 0, 0, SW_SHOW);
		goto BackShell;
	}

	//ToolBox

	//Settings
	if (shellkey == "refreshlang") {
		ShellExecute(0, "open", "wxcore.exe", "refreshlang", 0, SW_SHOW);
		goto BackShell;
	}
	if (shellkey == "setlang") {
		cout << "select your language" << endl;
		cout << "Do not add:  .lang" << endl;
		string langselect;
	BackSLang:
		cout << endl;
		cout << "Lang\\File.lang   $";
		getline(cin, langselect);
		string charccc = "Lang\\" + langselect + ".lang";
		bool retslang = existcheck(charccc);
		if (retslang) {
			string LINFO = readini(charccc, "Head", "LangINFO");
			cout << "Do you want use this language:  " + LINFO + "  ?" << endl;
			cout << "If you select this language we will reload WinXetor Now" << endl;
			cout << "<y/n>   $";
			string xlangselect;
			getline(cin, xlangselect);
			if (xlangselect == "y") {
				string SETLANGINI = langselect + ".lang";
				writeini(".\\config.ini", "Settings", "DefaultLanguage", SETLANGINI);
				goto reloadmark;
			}
			goto BackShell;
		}
		else {
			cout << "This language " + langselect + " is not exist on Lang Folder" << endl;
			cout << "Maybe this language WinXetor unsupport.  You can try to DIY lang file" << endl;
			goto BackSLang;
		}
	}
	if (shellkey == "off-autoupdate") {
		cout << "OK" << endl;
		writeini(".\\config.ini", "Settings", "AutoUpdate","off");
		goto BackShell;
	}
	if (shellkey == "open-autoupdate") {
		cout << "OK" << endl;
		writeini(".\\config.ini", "Settings", "AutoUpdate", "open");
		goto BackShell;
	}

	//OpenOffDebug
	if (shellkey == "opendebugmode") {
		writeini(".\\config.ini", "Settings", "DeveloperFunction", "enabled");
		cout << "complete" << endl;
		goto BackShell;
	}
	if (shellkey == "offdebugmode") {
		writeini(".\\config.ini", "Settings", "DeveloperFunction", "disabled");
		cout << "complete" << endl;
		goto BackShell;
	}

	//Hide CMD
	if (DevFun == "enabled") {
        if (shellkey == "testcrash") {
		return 0;
	}
		if (shellkey == "debuglang") {
			writeini(".\\config.ini", "Settings", "DefaultLanguage", "test.lang");
			goto reloadmark;
		}
	}

	string UCMD = readini($Langfile, "ShellUI", "UnknownCMD");
	string UCMDHelp = readini($Langfile, "ShellUI", "UnknownCMDHelp");
	cout << UCMD << shellkey << endl;
	cout << UCMDHelp << endl;
	goto BackShell;
}