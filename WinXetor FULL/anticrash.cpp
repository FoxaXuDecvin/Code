// anticrash
// WinXetor

#include"D:\CppHeader\winapicore.h"
#include<Windows.h>

using namespace std;

int main(int argc,char* argv[]) {

	if (argc == 1) {
		return 0;
	}
	int alang = 0;
	alang < argc;

	alang++;
	string sessmark = argv[alang];

	string langname = readini(".\\config.ini", "Settings", "DefaultLanguage");
	string $Langfile = "Lang\\" + langname;

	string WinXetorShellTitle = readini($Langfile, "ProcessTitle", "AntiCrash");
	SetConsoleTitle(WinXetorShellTitle.c_str());

	string markfile = "workcheck.mark";

BackCheck:
	Sleep(2000);
	remove(sessmark.c_str());
	bool retSSMK = existcheck(sessmark);
	if (retSSMK) {
		goto BackCheck;
	}

	bool retMFtest = existcheck(markfile);
	if (retMFtest) {
		remove(markfile.c_str());
		string TitleHead = readini($Langfile, "ShellUI", "CrashHead");
		string TitleINFO = readini($Langfile, "ShellUI", "CrashInfo");
		string MessageCrash = TitleHead + "     " + TitleINFO;

		MessageBox(0, MessageCrash.c_str(), TitleHead.c_str(), MB_OK);
		return 0;
	}
	else {
		return 0;
	}
}