//Copyright FoxaXu
// API For 7zip Tools https://www.7-zip.org/

#include<Windows.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;

//7z Core

string n7zNewZIP(string n7zcore, string selectoption, string outfile, string password) {
	if (password == "0") {
		string n7zParameter = "a " + outfile + " " + selectoption;
		ShellExecute(0, "open", n7zcore.c_str(), n7zParameter.c_str(), 0, SW_HIDE);
		return 0;
	}
	else {
		string n7zParameter = "a " + outfile + " " + selectoption + " -p" + password;
		ShellExecute(0, "open", n7zcore.c_str(), n7zParameter.c_str(), 0, SW_HIDE);
		return 0;
	}
}

string n7zUNZIP(string n7zcore, string selectoption, string outpath, string password) {
	if (password == "0") {
		string n7zParameter = "x -o" + outpath + " " + selectoption;
		ShellExecute(0, "open", n7zcore.c_str(), n7zParameter.c_str(), 0, SW_HIDE);
		return 0;
	}
	else {
		string n7zParameter = "x -o" + outpath + " " + selectoption + " -p" + password;
		ShellExecute(0, "open", n7zcore.c_str(), n7zParameter.c_str(), 0, SW_HIDE);
		return 0;
	}
}

string n7zGetSHA256(string n7zcore, string file) {
	bool ret7zrfile = existfile("report~7z.txt");
	if (ret7zrfile) {
		remove("report~7z.txt");
	}

	ofstream WritePoint;
	WritePoint.open("calc~7zsha256.bat");
	WritePoint << "@echo off" << endl;
	WritePoint << n7zcore + " h - scrcsha256 " + file + " >>report~7z.txt" << endl;
	WritePoint << "del calc~7zsha256.bat" << endl;
	WritePoint << "exit" << endl;
	WritePoint.close();

	ShellExecute(0, "open", "calc~7zsha256.bat", 0, 0, SW_HIDE);

BackWaitCalcSHA:
	Sleep(500);
	bool retR7S = existfile("report~7z.txt");
	if (retR7S) {
		string SHACode = ReadText("report~7z.txt",10);
		remove("report~7z.txt");
		ofstream CleanLong;
		CleanLong.open("temp~cleankey");
		CleanLong << SHACode << endl;
		CleanLong.close();

		string RealReturn;
		ifstream ReadShort;
		ReadShort.open("temp~cleankey");
		ReadShort >> RealReturn;
		ReadShort.close();

		remove("temp~cleankey");

		return RealReturn;
	}
	else {
		goto BackWaitCalcSHA;
	}
}