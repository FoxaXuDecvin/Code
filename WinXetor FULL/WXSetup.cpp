//WXSetup

#include"D:\CppHeader\winapicore.h"
#include<Windows.h>

using namespace std;

int main() {
	cout << "Select a Path:  " << endl;
	string Line;
BackLine:
	URLDown("https://developer.foxaxu.com/download/cppcore/dl.exe", "dl.exe");
	cout << "Path  $";
	getline(cin, Line);
	clearfolder(Line);
	cout << "Download File " << endl;
	URLDown("https://developer.foxaxu.com/WinXetor/download/WinXetor.exe", Line + "\\WinXetor.exe");
	URLDown("https://developer.foxaxu.com/WinXetor/download/wxcore.exe", Line + "\\wxcore.exe");
	URLDown("https://developer.foxaxu.com/WinXetor/download/config.ini", Line + "\\config.ini");

	string ABC = "https://developer.foxaxu.com/WinXetor/download/WinXetor.exe " + Line + "\\WinXetor.exe";
	ShellExecute(0, "open", "dl.exe", ABC.c_str(),0,SW_SHOW);
	ABC = "https://developer.foxaxu.com/WinXetor/download/wxcore.exe " + Line + "\\wxcore.exe";
	ShellExecute(0, "open", "dl.exe", ABC.c_str(), 0, SW_SHOW);
	ABC = "https://developer.foxaxu.com/WinXetor/download/config.ini " + Line + "\\config.ini";
	ShellExecute(0, "open", "dl.exe", ABC.c_str(), 0, SW_SHOW);

	cout << "Watiting Download..." << endl;

	string WXFileCheck = Line + "\\wxcore.exe";
waitwxcoreexe:
	Sleep(500);
	bool retWXMainB = existcheck(WXFileCheck);
	if (retWXMainB) {}
	else {
		goto waitwxcoreexe;
	}

	WXFileCheck = Line + "\\config.ini";
waitcfgini:
	Sleep(500);
	bool retWXMainC = existcheck(WXFileCheck);
	if (retWXMainC) {}
	else {
		goto waitcfgini;
	}

	cmdshell("start wxcore.exe refreshlang", Line, "setup");
	cout << "Setup is Complete. Run WinXetor.exe" << endl;
	getchar();
	return 0;
}