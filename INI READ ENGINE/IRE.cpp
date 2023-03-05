// IRE Tool
// Format:  
//              ire <read/write/delete> <select file> <head> <reg> <info>
//   Copyright FoxaXu 2023

#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<conio.h>

using namespace std;

#undef UNICODE
#undef _UNICODE

bool existcheck(string& name) {
	ifstream f(name.c_str());
	return f.good();
}

string ReadINI(string SFx,string Headx,string Regx) {
	LPTSTR lpPath = new char[MAX_PATH];
	strcpy(lpPath, SFx.c_str());
	LPTSTR ReadPointWM = new char[99];
	bool exist = existcheck(SFx);
	if (exist) {
		GetPrivateProfileString(Headx.c_str(), Regx.c_str(), NULL, ReadPointWM, 99, lpPath);
		return ReadPointWM;
	}
	else
	{
		string Text = "file.not.exist";
		return Text;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 5) {
		cout << " IRE Tool " << endl;
		cout << " Format:  " << endl;
		cout << "ire <read/write> <select file> <head> <reg> <info>" << endl;
		cout << "Copyright FoxaXu 2023" << endl;
		return 0;
	}
	if (argc > 6) {
		cout << " IRE Tool " << endl;
		cout << " Format:  " << endl;
		cout << "ire <read/write> <select file> <head> <reg> <info>" << endl;
		cout << "Copyright FoxaXu 2023" << endl;
		return 0;
	}
		int argvlang = 0;
		argvlang < argc;

		argvlang++;
		string WM = argv[argvlang];
		argvlang++;
		string SF = argv[argvlang];
		argvlang++;
		string Head = argv[argvlang];

		if (WM == "read") {
			argvlang++;
			string Reg = argv[argvlang];
			string ReadCode;
			ReadCode = ReadINI(SF, Head, Reg);
			if (ReadCode == "") {
				cout << "read.failed" << endl;
				return 0;
			}
			  cout << ReadCode << endl;
			  return 0;
		}

		if (WM == "write") {
			if (argc < 6) {
				cout << "Missing Parameter" << endl;
				return 0;
			}
			argvlang++;
			string Reg = argv[argvlang];
			argvlang++;
			string Info = argv[argvlang];
			LPTSTR lpPath = new char[MAX_PATH];
			strcpy(lpPath, SF.c_str());
			WritePrivateProfileString(Head.c_str(), Reg.c_str(), Info.c_str(), lpPath);
			cout << "Write Succ  " << lpPath << " " << Head << " " << Reg << " " << Info << endl;
			return 0;
		}

		string MBMsg = "Configuration Code Error. Code :  " + WM + "  is not support.";
		MessageBox(0, MBMsg.c_str(), "INI Read Engine    ~ Error", MB_OK);
		return 0;
}