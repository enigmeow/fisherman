// kb.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "kb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// www.windows-spy.com

// The one and only application object

CWinApp theApp;

using namespace std;

#if 0
BOOL CALLBACK chldProc(HWND hwnd,
    LPARAM lParam) {
  const char *cls = "Edit";
  HWND chld = FindWindowEx(hwnd, NULL, cls, NULL);
  printf("%x\n", chld);
  return FALSE;
}
#endif

#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#endif

static HKL keyBHandle = NULL;

static unsigned char getScanCode(unsigned int keycode) {
  if (keyBHandle == NULL) 
    keyBHandle = LoadKeyboardLayout("00000409",0);
  unsigned int ret = MapVirtualKeyEx(keycode,MAPVK_VK_TO_VSC,keyBHandle);
  return ret;
}

//Making a set of keydata
static unsigned int mkKeyData(
  short repCnt,/*How many times the key have been repeated so far*/
    unsigned char ScanCode,/*The scancode of the keyboard*/
    bool hAlt,/*Is the key pressed with ALT?*/
    bool inRep,/*Is the key part of a repetive sequence?*/
    bool isRel/*Is the key beeing released?*/ ) {
  int ret = 0;
  int irepCnt = repCnt;
  int iScanCode = ScanCode;
  int ihAlt = hAlt ? 1 : 0;
  int iinRep = inRep ? 1 : 0;
  int iisRel = isRel ? 1 : 0;
  //Rotate the data to their bitwise positions
  irepCnt <<= 0;
  iScanCode <<= 16;
  ihAlt <<= 29;
  iinRep <<= 30;
  iisRel <<= 31;
  //OR them all together
  ret = irepCnt | iScanCode | ihAlt | iinRep | iisRel;
  //Return it, packed and ready
  return ret;
}

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
static void sendKey(HWND hWnd, int kc) {
  int virKeyCode = kc;
  if (kc >= 'a' && kc <= 'z')
    virKeyCode += 'A' - 'a';
  SendMessage(hWnd, WM_KEYDOWN, virKeyCode, 0);
  int kd = mkKeyData(1,getScanCode(virKeyCode),false,false,false);
  SendMessage(hWnd, WM_CHAR, kc, kd);
  SendMessage(hWnd, WM_KEYUP, virKeyCode, 0);
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
  int nRetCode = 0;

  // initialize MFC and print and error on failure
  if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0)) {
    // TODO: change error code to suit your needs
    _tprintf(_T("Fatal Error: MFC initialization failed\n"));
    nRetCode = 1;
  } else {
    const char *title = "Untitled - Notepad";
    HWND hndl = FindWindow(NULL, title);

    const char *cls = "Edit";
    HWND chld = FindWindowEx(hndl, NULL, cls, NULL);

    SendMessage(chld, WM_KEYDOWN, VK_RIGHT, 0);
    SendMessage(chld, WM_KEYUP, VK_RIGHT, 0);

    sendKey(chld, 'H');
    sendKey(chld, 'e');
    sendKey(chld, 'l');
    sendKey(chld, 'l');
    sendKey(chld, 'o');

#if 0
    if (hndl != NULL) 
      EnumChildWindows (hndl, chldProc, NULL);
#endif
  }

  return nRetCode;
}


