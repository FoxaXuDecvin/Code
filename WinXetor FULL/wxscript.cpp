// WXSCRIPT
// COPYRIGHT FOXAXU 2023
// WXCORE

#include<Windows.h>
#include"D:\CppHeader\winapicore.h";
#include"D:\CppHeader\7zipAPI.h";

using namespace std;

int addkeynum() {
	int INTProcessPID = getpid();
	string PPID = to_string(INTProcessPID);
	string keyfile = "wxs~" + PPID + "~keynum.bin";

	bool retfile = existfile(keyfile);
	if (retfile) {}
	else {
		MessageBox(0, "WXScript Error: Key Num is Destroy. Command is Reset", "WXScript Error", MB_OK);
		cmarkfile(keyfile, "0");
	}

	string Readkey = ReadText(keyfile, 1);

	int keySize = atoi(Readkey.c_str());

	keySize++;

	string keyoutput = to_string(keySize);

	cmarkfile(keyfile, keyoutput);
	return 0;
}

int readkeynum() {
	int INTProcessPID = getpid();
	string PPID = to_string(INTProcessPID);
	string keyfile = "wxs~" + PPID + "~keynum.bin";

	string Readkey = ReadText(keyfile, 1);

	int keyoutput = atoi(Readkey.c_str());
	return keyoutput;
}

int main(int argc, char* argv[]) {
	SetConsoleTitle("WinXetor Script Core");

	string Version = "1.02";
	int VerCode = 2;

	int INTProcessPID = getpid();
	string PPID = to_string(INTProcessPID);

	string keyfile = "wxs~" + PPID + "~keynum.bin";

	int alang = 0;
	alang < argc;

	if (argc == 1) {
		cout << "WinXetor Script Core" << endl;
		cout << "Command Format: " << endl;
		cout << "      wxscript.exe <file>" << endl;
		cout << "      wxscript.exe help" << endl;
		cout << " if not _off.echo.console. Default is Show" << endl;
		cout << " Max Support Empty Line is 8" << endl;
		cout << " Copyright FoxaXu 2023  WinXetor Script Core" << endl;
		cout << "Version:  " + Version + "  Version Code: " << VerCode << endl;
		return 0;
	}

	string echoset = "wxstemp~" + PPID + "~para.bin";

	if (argc == 2) {
		cmarkfile(echoset, "off");
		goto startload;
	}

	if (argc > 2) {
		MessageBox(0, "WXScript Error: Parameter is Error", "WXScript Error", MB_OK);
		return 0;
	}

startload:
	alang++;
	string $ParaScript = argv[alang];

	if ($ParaScript == "help") {
		OpenWebsite("https://developer.foxaxu.com/WinXetor/HelpScript.html");
		return 0;
	}

	bool retPSFile = existfile($ParaScript);
	if (retPSFile){}
	else {
		string MINFO = "WXScript Error: Cannot Load file : " + $ParaScript;
		MessageBox(0, MINFO.c_str(), "WXScript Error", MB_OK);
		return 0;
	}

	string fcmds = ReadText($ParaScript, 1);
	if (fcmds == "_off.echo.console") {
		cmarkfile(echoset, "off");
	}
	else {
		cmarkfile(echoset, "on");
	}

	//LOAD
	string echoswitch = ReadText(echoset, 1);
	remove(echoset.c_str());

	if (echoswitch == "on") {
		cout << "WXScript MainService    -Version :  " + Version << endl;
		cout << "Copyright FoxaXu 2023" << endl;
		cout << "Echo Mode:  " + echoswitch << endl;
		cout << endl;
		cout << "Script :  " + $ParaScript << endl;
	}

	cmarkfile(keyfile, "0");
	
	int scriptLang;
	string scmd;
	int emptyspace = 0;

BackMain:
	//back main switch
	addkeynum();
BackMainNoAdd:
	scriptLang = readkeynum();
	scmd = ReadText($ParaScript, scriptLang);

	//API

	if (scmd == "_api.cout") {
		COUTCMDAPI:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "_return.backmain") {
			goto BackMain;
		}
		if (scmd == "_cout.endl") {
			cout << endl;
			goto COUTCMDAPI;
		}
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}

		cout << scmd << endl;
		goto COUTCMDAPI;
	}

	if (scmd == "_api.goto") {
	GOTOBACKPOINT:

		addkeynum();
		scriptLang = readkeynum();
		string GotoSET;
		GotoSET = ReadText($ParaScript, scriptLang);

	BACKPOINTGO:
		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == GotoSET) {
			goto BackMain;
		}
		else {
			goto BACKPOINTGO;
		}
	}

	if (scmd == "_api.win.md") {
	WINMDAPI:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}
		if (scmd == "_return.backmain") {
			goto BackMain;
		}

		mdfolder(scmd);
		goto WINMDAPI;
	}

	if (scmd == "_api.win.rd") {
	WINRDAPI:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}
		if (scmd == "_return.backmain") {
			goto BackMain;
		}

		rmfolder(scmd);
		goto WINRDAPI;
	}

	if (scmd == "_api.win.runas.local") {
	WINRUNAPIS:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "_return.backmain") {
			goto BackMain;
		}
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}

		ShellExecute(0, "open", scmd.c_str(), 0, 0, SW_SHOW);
		goto WINRUNAPIS;
	}

	if (scmd == "_api.win.runas.admin") {
	WINRUNAPISA:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "_return.backmain") {
			goto BackMain;
		}
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}

		ShellExecute(0, "runas", scmd.c_str(), 0, 0, SW_SHOW);
		goto WINRUNAPISA;
	}

	if (scmd == "_api.win.system") {
	WINCMDKEY:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "_return.backmain") {
			goto BackMain;
		}
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}

		system(scmd.c_str());
		goto WINCMDKEY;
	}

	if (scmd == "_api.win.URLDown") {
	WINUDAPI:

		addkeynum();
		scriptLang = readkeynum();

		string URLD;
		URLD = ReadText($ParaScript, scriptLang);
		if (URLD == "_return.backmain") {
			goto BackMain;
		}
		if (URLD == "") {
			cout << endl;
			cout << "WXScript.Error-URLDOWNAPI.NoParameterA" << endl;
			goto BackMain;
		}

		addkeynum();
		scriptLang = readkeynum();

		string SavePath;
		SavePath = ReadText($ParaScript, scriptLang);
		if (SavePath == "") {
			cout << endl;
			cout << "WXScript.Error-URLDOWNAPI.NoParameterB" << endl;
			goto BackMain;
		}

		URLDown(URLD, SavePath);

		bool retDLFile = existfile(SavePath);
		if (retDLFile) {
			if (echoswitch == "on") {
				cout << "Download SUCCEEDED" << endl;
			}
		}
		else {
			cout << "WXScript.Error-InternetDown.Failed" << endl;
		}


		goto WINUDAPI;
	}

	// User Dialogue
	
	if (scmd == "_wxscript.pause") {
		cout << "Press Enter to Next";
		getchar();
		goto BackMain;
	}

	if (scmd == "_wxscript.clear") {
		system("cls");
		goto BackMain;
	}

	if (scmd == "_print.TXT") {
	BACKPRINT:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);
		if (scmd == "_return.backmain") {
			goto BackMain;
		}
		if (scmd == "_cout.endl") {
			cout << endl;
			goto COUTCMDAPI;
		}
		if (scmd == "") {
			cout << endl;
			cout << "WXScript.Warning_ Please Add command:  _return.backmain  to return" << endl;
			goto BackMain;
		}

		string IFNO = "type " + scmd;

		system(IFNO.c_str());
		goto COUTCMDAPI;
	}

	// Settings

	if (scmd == "_set.min.version") {
	ANTILOWVER:

		addkeynum();
		scriptLang = readkeynum();
		scmd = ReadText($ParaScript, scriptLang);

		int needver = atoi(scmd.c_str());
		if (VerCode < needver) {
			string VCodeStr = to_string(VerCode);

			string TMPCD = "WXScript.Error: Version not support. Current WXScript Version : " + VCodeStr + ". The required version must be greater than : " + scmd;
			
			if (echoswitch == "on") {
				cout << endl;
				cout << "Command End" << endl;
				cout << "Process Exit.  PID: " + PPID << endl;
			}
			remove(keyfile.c_str());
			cout << endl;
			MessageBox(0, TMPCD.c_str(), "WXScript Error", MB_OK);
			return 0;
		}
		goto BackMain;
	}

	if (scmd == "_wxscript.close") {
		if (echoswitch == "on") {
			cout << endl;
			cout << "Command End" << endl;
			cout << "Process Exit.  PID: " + PPID << endl;
		}
		remove(keyfile.c_str());
		cout << endl;
		return 0;
	}

	if (scmd == "_skip") {
		addkeynum();
		goto BackMain;
	}

	if (scmd == "_off.echo.console") {
		goto BackMain;
	}

	if (scmd == "_use.admin.run") {
		string processname = getselfinfo("processfullname");
		
		bool retTSAM = testAdmin("C:");
		if (retTSAM) {
			goto BackMain;
		}
		else
		{
			ShellExecute(0, "runas", processname.c_str(), $ParaScript.c_str(), 0, SW_SHOW);
			return 0;
		}
	}

	if (scmd == "") {
		emptyspace++;
		if (emptyspace == 8) {
			cout << endl;
			cout << "WXScript.Error: Empty Space over allow size.Please check this script" << endl;
			remove(keyfile.c_str());
			return 0;
		}
		goto BackMain;
	}

	//NULL COMMAND

	string sLangKey = to_string(scriptLang);
	string MINFO = "WXScript Error:  Command Error_ type:  " + scmd + "  Line :  " + sLangKey;
	MessageBox(0, MINFO.c_str(), "WXScript Error: Command Error", MB_OK);
	goto BackMain;
}