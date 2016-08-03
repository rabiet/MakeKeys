#include <iostream>
#include "Windows.h"
#include <string>
#include "shlobj.h"
#include "Lmcons.h"


using namespace std;

HWND hwnd;
bool hidden = false;

template<typename T> 
 T fromStr(const string &str) 
{ 
     std::istringstream is(str); 
     T t = T(); 
     is >> t; 
     return t; 
}


void startUp()
{
	system("mkdir \"%appdata%\\MakeKeys\\");
	system("copy MakeKeys.exe \"%appdata%\\MakeKeys\\MakeKeys.exe");
	HKEY hkey;
	char username[UNLEN+1];
	DWORD username_len = UNLEN+1;
	GetUserName(username, &username_len);
	string path = "\"C:\\Users\\";
	path += username;
	path += "\\AppData\\Roaming\\MakeKeys\\MakeKeys.exe\"";
	unsigned char pat[256];

	int TempNumOne = path.length();
	for (int a=0; a<=TempNumOne; a++)
    {
        pat[a]=path[a];
    }
	
	cout << pat;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, 0);
	RegSetValueEx(hkey, "MakeKeys", 0, REG_SZ, pat, path.length());
	RegCloseKey(hkey);
}

toggleStealth()
{
	if (hidden) { ShowWindow(hwnd,5); hidden = false; }
	else { ShowWindow(hwnd,0); hidden = true; }
}

bool progbackground()
{
	//if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x24)) 
	if (RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT, VK_END))
	if (RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_ALT, VK_PRIOR))
	if (RegisterHotKey(NULL, 4, MOD_CONTROL | MOD_ALT, VK_NEXT))
	if (RegisterHotKey(NULL, 5, MOD_CONTROL | MOD_ALT, VK_ESCAPE))
	if (RegisterHotKey(NULL, 6, MOD_CONTROL | MOD_ALT, VK_BACK))
	{
		cout << "Registered!" << endl;
	}else{ cout << "Hotkey not registered!";
	return true;
	}
	
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			string called = "%no_event%";
			switch (msg.wParam)
			{
				/*case 1:
					keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);
  					keybd_event(VK_MEDIA_PLAY_PAUSE, 0, KEYEVENTF_KEYUP, 0);
  					called = "VK_MEDIA_PLAY_PAUSE";  					
  					break;*/
  				case 2:
  					keybd_event(VK_MEDIA_STOP, 0, 0, 0);
  					keybd_event(VK_MEDIA_STOP, 0, KEYEVENTF_KEYUP, 0);
  					called = "VK_MEDIA_STOP";
					break;
  				case 3:
  					keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
  					keybd_event(VK_MEDIA_PREV_TRACK, 0, KEYEVENTF_KEYUP, 0);
  					called = "VK_MEDIA_PREV_TRACK";
  					break;
  				case 4:
  					keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
  					keybd_event(VK_MEDIA_NEXT_TRACK, 0, KEYEVENTF_KEYUP, 0);
  					called = "VK_MEDIA_NEXT_TRACK";
  					break;
  				case 5:
  					called = "taskkill /IM MakeKeys.exe /F";
					system("taskkill /IM MakeKeys.exe /F");
  					break;
  				case 6:
  					called = "AntiStealth();";
  					toggleStealth();
  					break;
  						
			}			
			cout << called << " Called" << endl;
		}
	}
	return false;
}

int main(int argc, char** argv)
{
	
	AllocConsole();
 	hwnd = GetForegroundWindow();
	toggleStealth();
	startUp();
	while(!progbackground());
	
	return 0;
}