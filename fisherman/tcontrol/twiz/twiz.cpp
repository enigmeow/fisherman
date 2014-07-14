// twiz.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace twiz;
using namespace System::Threading;


#ifndef MAPVK_VK_TO_VSC
#define MAPVK_VK_TO_VSC 0
#endif

HKL keyBHandle = NULL;
int awake = 0;

double angleTo(double mx, double my, double dx, double dy) {
  return fmod(270 + (atan2(dy - my, dx - mx) * (180.0 / 3.1415926)), 360.0);
}

double distTo(double mx, double my, double dx, double dy) {
  return sqrt(((dx - mx) * (dx - mx)) + 
              ((dy - my) * (dy - my)));
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION MAKEWORD(2,2)
#endif

  /* Start up the windows networking */
  WSADATA wsaData;
  if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
    return -1;
    // printf("Initialization of windows networking failed\n");
  }

  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false); 

  // Create the main window and run it
  Application::Run(gcnew Form1());
  return 0;
}


struct ToonPos {
  float _x;
  float _y;
  float _z;
  float _h;
};

 public ref class ProcessItem {
 public:
   String^ toonName;
   String^ myShortName;
   String^ myLongName;
   DWORD dwThreadId_;
   DWORD dwProcessId_;
   DWORD windowId_;
   void* base_;
   HANDLE process_;
   HWND hWnd_;
   bool leader;
   float x;
   float y;
   float z;
   float h;
   bool changed_;
   static ProcessItem ^leader_;
   float dh;
   bool turning_;
   bool moving_;

 public:
   ProcessItem( String^ strLongName, String^ strShortName, DWORD dwThreadId, DWORD dwProcessId, HWND hWnd  ) {
     this->myShortName = strShortName;
     this->myLongName = strLongName;
     this->dwThreadId_ = dwThreadId;
     this->dwProcessId_ = dwProcessId;
     this->base_ = 0;
     this->process_ = 0;
     this->toonName = "Unknown";
     this->hWnd_ = hWnd;
     this->leader = FALSE;
     this->dh = 0;
     this->moving_ = false;
     this->turning_ = false;
   }

   property String^ ShortName {
     String^ get() {
       return myShortName;
     }
   }

   property String^ LongName {
     String^ get() {
       return myLongName;
     }
   }
   virtual String^ ToString() override {
     return String::Concat( this->toonName, " (", this->dwProcessId_  + ")");
   }

   float mmod(float x) {
     while ( x < -180)
       x += 360.0;
     while ( x >= 180.0)
       x -= 360.0;
     return x;
   }
   

   void update(Form1 ^f, bool selected) {
     if (base_ == NULL)
       return;

     char buf[255];
     SIZE_T lpRead;
     if (ReadProcessMemory( process_, base_, buf, sizeof(struct ToonPos), &lpRead)) {
       struct ToonPos *tp = (struct ToonPos *) &buf[0];
       if ((this->x != tp->_x) || (this->y != tp->_y) || (this->z != tp->_z)) 
         this->changed_ = true;
       else
         this->changed_ = false;
       this->x = tp->_x;
       this->y = tp->_y;
       this->z = tp->_z;
       this->h = tp->_h;
     }

     if (this->leader) 
       this->leader_ = this;
     else if (this->leader_ != nullptr) {
       dh = (float) angleTo(this->x, this->y, this->leader_->x, this->leader_->y);
     }

     if (selected) {
       f->XBox->Text = x+"";
       f->YBox->Text = y+"";
       f->ZBox->Text = z+"";
       f->HBox->Text = h+"";
       if (this->leader) 
         f->DHBox->Text = h+"";
       else
         f->DHBox->Text = dh+"";
     }
     if (!this->leader && f->toonFollow->Checked) {
       dh = mmod(dh);
       float mh = mmod(this->h);
       float delta = mmod(dh - mh);
       double dist = distTo(this->x, this->y, this->leader_->x, this->leader_->y);
       double window = 10;
       if (dist < 2.0)
         window = 75;
       else if (dist < 4.0)
         window = 20;
       if ((delta < window) || (delta > (360.0 - window))) {
         if (turning_) {
           ::SendMessage(this->hWnd_, WM_KEYUP, VK_RIGHT, 0);
           ::SendMessage(this->hWnd_, WM_KEYUP, VK_LEFT, 0);
           turning_ = false;
         }
       } else if (delta < 180.0) {
         turning_ = true;
         ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
       } else {
         turning_ = true;
         ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
       }
       if (dist > 3)  {
         if ((turning_ == false) || ((delta < 10.0) || (delta > (350.0)))) {
           ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_UP, 0);
           moving_ = true;
         }
       } else {
         if (moving_) {
           ::SendMessage(this->hWnd_, WM_KEYUP, VK_UP, 0);
           moving_ = false;
         }
       }
     }
   }
   bool updateGolf(float x, float y);
 };

unsigned char getScanCode(unsigned int keycode) {
  if (keyBHandle == NULL) 
    keyBHandle = LoadKeyboardLayout("00000409",0);
  unsigned int ret = MapVirtualKeyEx(keycode,MAPVK_VK_TO_VSC,keyBHandle);
  return ret;
}

//Making a set of keydata
unsigned int mkKeyData(
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
void sendKey(HWND hWnd, int kc) {
  int virKeyCode = kc;
  if (kc >= 'a' && kc <= 'z')
    virKeyCode += 'A' - 'a';
  ::SendMessage(hWnd, WM_KEYDOWN, virKeyCode, 0);
  int kd = mkKeyData(1,getScanCode(virKeyCode),false,false,false);
  ::SendMessage(hWnd, WM_CHAR, kc, kd);
  ::SendMessage(hWnd, WM_KEYUP, virKeyCode, 0);
}

System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e) {
  const char *title = "Toontown";
  HWND chld = FindWindow(NULL, title);

  ::SendMessage(chld, WM_KEYDOWN, VK_RIGHT, 0);
  Sleep(5000);
  ::SendMessage(chld, WM_KEYUP, VK_RIGHT, 0);
  Sleep(5000);
  sendKey(chld, 'H');
  sendKey(chld, 'e');
  sendKey(chld, 'l');
  sendKey(chld, 'l');
  sendKey(chld, 'o');
}


int openPort(unsigned int addr, unsigned short port, int sender) {
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd == -1) {
    //    perror("socket");
    return -1;
  }

  struct sockaddr_in inad;
  unsigned int interface;

  char hostname[255];
  gethostname(hostname, sizeof(hostname));
  struct hostent* hent = gethostbyname(hostname);
  char** a = hent->h_addr_list;
  interface = *(unsigned int *) a[0];

  inad.sin_family      = AF_INET;
  if (sender) {
    inad.sin_addr.s_addr = interface;
    inad.sin_port        = 0;
  } else {
    inad.sin_addr.s_addr = htonl(INADDR_ANY);
    inad.sin_port        = htons(port);
  }

  if (bind(fd, (struct sockaddr*)&inad, sizeof(inad)) < 0) {
    //    perror("bind");
    return -1;
  } 

  if (!sender) {
    struct ip_mreq mr;
    mr.imr_multiaddr.s_addr = htonl(addr);
    mr.imr_interface.s_addr = interface;
    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mr,
                   sizeof(mr)) == -1)
      return -1;
  }

  return fd;
}

DWORD Form1::LoadControllerStatus(XINPUT_STATE &state)
{
  memset(&state, 0, sizeof(state));
  DWORD ret = XInputGetState( 0, &state );

  if( (state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
       state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
      (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
       state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ) {     
    state.Gamepad.sThumbLX = 0;
    state.Gamepad.sThumbLY = 0;
  }

  if( (state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
       state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
      (state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && 
       state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ) {
    state.Gamepad.sThumbRX = 0;
    state.Gamepad.sThumbRY = 0;
  }
  return ret;
}

void Form1::YButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_END;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void Form1::AButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;
  input[0].mi.mouseData = 0;
  if (newv)
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  else
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  input[0].mi.time = 0;
  SendInput(1, input, sizeof(INPUT));
}

void Form1::BButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_HOME;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void Form1::XButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    if (newv == false) 
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_CONTROL, 0);
    else
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
  }
}

void Form1::RightThumbButton(bool oldv, bool newv, XINPUT_STATE &state) { 
}
void Form1::LeftThumbButton(bool oldv, bool newv, XINPUT_STATE &state) { 
}
void Form1::BackButton(bool oldv, bool newv, XINPUT_STATE &state) {
  awake = 0;
}
void Form1::StartButton(bool oldv, bool newv, XINPUT_STATE &state) {
  awake = 1;
}

void Form1::RightButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_RIGHT;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void Form1::LeftButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_LEFT;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void Form1::DownButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_DOWN;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void Form1::UpButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_UP;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void Form1::RightThumbXY(int newx, int newy, XINPUT_STATE &state) { 
  double  scalex = pow(1.25, fabs(newx / 2500.0)) * ((newx < 0) ? -1 : 1);
  double  scaley = pow(1.25, fabs(newy / 2500.0)) * ((newy < 0) ? 1 : -1);

  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;
  input[0].mi.dx = (int) scalex;
  input[0].mi.dy = (int) scaley;
  input[0].mi.mouseData = 0;
  input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
  input[0].mi.time = 0;
  SendInput(1, input, sizeof(INPUT));
}

void Form1::LeftThumbXY(int newx, int newy, XINPUT_STATE &state) {
}

void Form1::RightTrigger(int oldv, int newv, XINPUT_STATE &state) {
}

void Form1::LeftTrigger(int oldv, int newv, XINPUT_STATE &state) {
}

void Form1::RightShoulderButton(bool oldv, bool newv, XINPUT_STATE &state) {
	/*
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_DELETE, 0);
    ::SendMessage(primary->hWnd_, WM_KEYUP, VK_DELETE, 0);
  }
  */
}

void Form1::LeftShoulderButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_DELETE, 0);
    //Sleep(state.Gamepad.bLeftTrigger);
    ::SendMessage(primary->hWnd_, WM_KEYUP, VK_DELETE, 0);
  }
}

void Form1::CheckControllerStatus(XINPUT_STATE &old, XINPUT_STATE &state)
{
  if (state.Gamepad.sThumbLX != 0 || state.Gamepad.sThumbLY)
    LeftThumbXY(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, state);

  if (state.Gamepad.sThumbRX != 0 || state.Gamepad.sThumbRY)
    RightThumbXY(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, state);

  if (old.Gamepad.bLeftTrigger != state.Gamepad.bLeftTrigger)
    LeftTrigger(state.Gamepad.bLeftTrigger, state.Gamepad.bLeftTrigger, state);

  if (old.Gamepad.bRightTrigger != state.Gamepad.bRightTrigger)
    LeftTrigger(state.Gamepad.bRightTrigger, state.Gamepad.bRightTrigger, state);

#define CheckPad(_flag, _fun)                                           \
  if (state.Gamepad.wButtons != old.Gamepad.wButtons) {                 \
    if ((state.Gamepad.wButtons & _flag) != (old.Gamepad.wButtons & _flag)) \
      _fun((old.Gamepad.wButtons & _flag) != 0, (state.Gamepad.wButtons & _flag) != 0, state); \
  }

  CheckPad(XINPUT_GAMEPAD_DPAD_UP, UpButton);
  CheckPad(XINPUT_GAMEPAD_DPAD_DOWN, DownButton);
  CheckPad(XINPUT_GAMEPAD_DPAD_LEFT, LeftButton);
  CheckPad(XINPUT_GAMEPAD_DPAD_RIGHT, RightButton);
  CheckPad(XINPUT_GAMEPAD_START, StartButton);
  CheckPad(XINPUT_GAMEPAD_BACK, BackButton);
  CheckPad(XINPUT_GAMEPAD_LEFT_THUMB, LeftThumbButton);
  CheckPad(XINPUT_GAMEPAD_RIGHT_THUMB, RightThumbButton);
  CheckPad(XINPUT_GAMEPAD_LEFT_SHOULDER, LeftShoulderButton);
  CheckPad(XINPUT_GAMEPAD_RIGHT_SHOULDER, RightShoulderButton);
  CheckPad(XINPUT_GAMEPAD_A, AButton);
  CheckPad(XINPUT_GAMEPAD_B, BButton);
  CheckPad(XINPUT_GAMEPAD_X, XButton);
  CheckPad(XINPUT_GAMEPAD_Y, YButton);
}

int StringToInt(String ^s) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  int r = atoi((char *) p.ToPointer());
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
  return r;
}

double StringToFloat(String ^s) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  double r = atof((char *) p.ToPointer());
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
  return r;
}

void StringToBuf(String ^s, char *buf, int slen) {
  IntPtr p = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s);
  strncpy(buf, (char *) p.ToPointer(), slen);
  System::Runtime::InteropServices::Marshal::FreeHGlobal(p);
}

System::Void Form1::Golf_Click(System::Object^  sender, System::EventArgs^  e) {
   int t = StringToInt(this->PercentTime->Text) * StringToInt(this->TimeMultiple->Text);
   this->GolfTimer->Interval = t;
   this->GolfTimer->Enabled = true;

   ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
   if (pi == nullptr)
     return;
   ::SendMessage(pi->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
 }

System::Void Form1::GolfTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
   this->GolfTimer->Enabled = false;
   ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
   if (pi == nullptr)
     return;
   ::SendMessage(pi->hWnd_, WM_KEYUP, VK_CONTROL, 0);
 }

void Form1::ThreadProc() {
  while (1) {
    int n;
    if ((n = recvfrom(fd_, (char *) stateA_, sizeof(*stateA_), 0, NULL, NULL)) < 0)  
      return;

    CheckControllerStatus(*stateB_, *stateA_);
    XINPUT_STATE   *t = stateB_;
    stateB_ = stateA_;
    stateA_ = t;
  }
}

System::Void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e) {
  serv_ = this->radioButton2->Checked ? 1 : 0;
  char buf[255];
  StringToBuf(this->addressBox->Text, buf, sizeof(buf));

  port_ = StringToInt(this->portBox->Text);
  addr_ = htonl(inet_addr(buf));

  fd_ = openPort(addr_,  port_, serv_);

  stateA_ = new XINPUT_STATE();
  stateB_ = new XINPUT_STATE();

  LoadControllerStatus(*stateB_);

  if (serv_) {
    si_other_ = new struct sockaddr_in();
    memset((char *) si_other_, 0, sizeof(*si_other_));
    si_other_->sin_family = AF_INET;
    int slen = sizeof(*si_other_);
    si_other_->sin_addr.s_addr = htonl(addr_);
    si_other_->sin_port = htons(port_);

    timer1->Enabled = TRUE;
    timer1->Interval = 10;
  } else {
    Thread^ oThread = gcnew Thread( gcnew ThreadStart( this, &Form1::ThreadProc ) );
    oThread->Start();
  }
}

extern "C" {
  BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
};


BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
  DWORD dwThreadId, dwProcessId;
  HINSTANCE hInstance;
  char Str[255];
  // HANDLE hProcess;
  if (!hWnd)
    return TRUE;		// Not a window
  if (!::IsWindowVisible(hWnd))
    return TRUE;		// Not visible
  if (!SendMessage(hWnd, WM_GETTEXT, sizeof(Str), (LPARAM)Str))
    return TRUE;		// No window title
  if (strcmp(Str, "Toontown"))
    return TRUE;
  hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
  dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
  // hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

  Form1::listBox1_->Items->Add(gcnew ProcessItem(gcnew String(Str), gcnew String(Str), dwThreadId, dwProcessId, hWnd));

  return TRUE;
}

class MemBuffer {
public:
  MemBuffer() {
    ptr_ = 0;
    next_ = 0;
    addr_ = 0;
    size_ = 0;
  }
  ~MemBuffer() {
    if (ptr_ != 0)
      free(ptr_);
  }
  void * addr_;
  int size_;
  char *ptr_;
  MemBuffer *next_;
};

class CompObj {
public:
  virtual int size() = 0;
  virtual int cmp(const char *val) = 0;
};

class IntObj : public CompObj {
public:
  int v_;
  IntObj(int v) :v_(v) {}
  int size() { 
    return sizeof(int);
  }
  int cmp(const char *val) { 
    return *((int *) val) == v_; 
  }
};

class FloatObj : public CompObj {
public:
  float v_;
  int vi_;
  FloatObj(float v) :v_(v) {
    vi_ = (int) (v * 100.0);
  }
  int size() {  
    return sizeof(float); 
  }
  int cmp(const char *val) { 
    return ((int) (100.0 * *((float *) val))) == vi_; 
  }
};

class FloatSetObj : public CompObj {
public:
  int xi_;
  int yi_;
  int zi_;
  int hi_;
  FloatSetObj(double x, double y, double z, double h)  {
    xi_ = (int) (x * 100.0);
    yi_ = (int) (y * 100.0);
    zi_ = (int) (z * 100.0);
    hi_ = (int) (h * 100.0);
  }
  int size() {  
    return sizeof(float) * 4; 
  }
  int cmp(const char *val) { 
    struct ToonPos *tp = (struct ToonPos *) val;
    return ((int) (100.0 * tp->_x) == xi_) && 
      (((int) (100.0 * tp->_y)) == yi_) && 
      (((int) (100.0 * tp->_z))== zi_) && 
      (((int) (100.0 * tp->_h)) == hi_);
  }
};

class SnapShot {
public:
  MemBuffer *data_;
  DWORD hProcess_;
  int elements_;

  SnapShot(DWORD hProcess) :  hProcess_(hProcess) { 
    data_ = NULL;
    elements_ = 0;
  }

  ~SnapShot() { 
    clear();
  }

  void clear() { 
    while (data_ != NULL) {
      MemBuffer *n = data_;
      data_ = data_->next_;
      delete n;
    }
  }

  static BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) {
    TOKEN_PRIVILEGES tp;
    LUID luid;

    HANDLE hToken;

    if (!OpenProcessToken (GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return FALSE;

    if ( !LookupPrivilegeValue(NULL, lpszPrivilege, &luid ) )
      return FALSE; 

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    if (bEnablePrivilege)
      tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    else
      tp.Privileges[0].Attributes = 0;

    if ( !AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES) NULL, (PDWORD) NULL) ) 
      return FALSE; 

    if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      return FALSE;

    CloseHandle(hToken);

    return TRUE;
  }

  static void reportError() {
    int err = WSAGetLastError();

    char message[256];
    sprintf(&message[0], "Windows error %d", err);
    ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL, err, 0, (LPTSTR)&message[0], sizeof(message), NULL);
  }

  int trim(BOOL changed) {
    MemBuffer **prev = &data_;
    MemBuffer *cur = data_;
    char buf[255];
    int elements = 0;
    SIZE_T lpRead;

    HANDLE process=OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);

    while (cur != NULL) {
      ReadProcessMemory( process, cur->addr_, buf, cur->size_, &lpRead);
      if (changed ? (memcmp(buf, cur->ptr_, cur->size_) != 0) : (memcmp(buf, cur->ptr_, cur->size_) == 0)) {
        MemBuffer *t = cur;
        *prev = t->next_;
        cur = t->next_;
        delete t;
      } else {
        memcpy(cur->ptr_, buf, cur->size_);
        prev = &cur->next_;
        cur = cur->next_;
        elements++;
      }
    }
    CloseHandle(process);

    elements_ = elements;
    return elements;
  }

  int trim(CompObj *cobj) {
    MemBuffer **prev = &data_;
    MemBuffer *cur = data_;
    char buf[255];
    int elements = 0;
    SIZE_T lpRead;

    HANDLE process=OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);

    while (cur != NULL) {
      ReadProcessMemory( process, cur->addr_, buf, cur->size_, &lpRead);
      if (!cobj->cmp(buf)) {
        MemBuffer *t = cur;
        *prev = t->next_;
        cur = t->next_;
        delete t;
      } else {
        memcpy(cur->ptr_, buf, cur->size_);
        prev = &cur->next_;
        cur = cur->next_;
        elements++;
      }
    }
    CloseHandle(process);

    elements_ = elements;
    return elements;
  }

  int searchAndSnap(CompObj *cobj, BOOL quick, HANDLE proc, char * skip) {
    clear();

    SIZE_T lpRead;
    int elements = 0;

    MemBuffer *n;

    SYSTEM_INFO lpSysInfo;
    GetSystemInfo(&lpSysInfo);
    HANDLE process;
    if (proc != NULL)
      process = proc;
    else
      process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcess_);
    char * start = (skip == 0) ? (char *) lpSysInfo.lpMinimumApplicationAddress : (skip + 4);

    while(start < lpSysInfo.lpMaximumApplicationAddress) {
      MEMORY_BASIC_INFORMATION mbi;

      int sz = VirtualQueryEx( process, (void *)start, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

      if((mbi.State == MEM_COMMIT) && (mbi.Protect != PAGE_READONLY) && (mbi.Protect != PAGE_EXECUTE_READ)
         && (mbi.Protect != PAGE_GUARD) && (mbi.Protect != PAGE_NOACCESS)) {
        char *p = (char *)malloc(mbi.RegionSize);
        do {
          if(!ReadProcessMemory( process, (void *)start, p, mbi.RegionSize, &lpRead)) 
            break;

          if(mbi.RegionSize != lpRead) 
            break;

          const char *ptr = p;
          const char *eptr = p + mbi.RegionSize;

          while (ptr < eptr) {
            if (cobj->cmp(ptr)) {
              MemBuffer *b = new MemBuffer();

              b->size_ = cobj->size();
              b->ptr_ = (char *)malloc(b->size_);
              b->addr_ = (char *) start + (ptr - p);
              memcpy(b->ptr_, ptr, b->size_);

              if (data_ == NULL)
                data_ = b;
              else 
                n->next_  = b;
              n = b;
              elements++;
              if (quick)  {
                free(p);
                if (proc == NULL)
                  CloseHandle(process);
                elements_ = elements;
                return elements;
              }
            }
            ptr += 4; // who knows how things are aligned...
          }
        } while(0);
        free(p);
      }

      start += mbi.RegionSize;
    }

    if (proc == NULL)
      CloseHandle(process);

    elements_ = elements;
    return elements;
  }
};


System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e) {
							  
  // DebugSetProcessKillOnExit(FALSE);
  SnapShot::SetPrivilege( "SeDebugPrivilege", true);
  snapshot_ = NULL;

  listBox1_ = this->listBox1;
  listBox1_->BeginUpdate();
  listBox1_->Items->Clear();
  listBox1_->ClearSelected();
  EnumWindows(EnumWindowsProc, NULL);
  listBox1_->EndUpdate();
  tx_ = 132;
  ty_ = 47.8;
}

System::Void Form1::refreshButton_Click(System::Object^  sender, System::EventArgs^  e) {
  listBox1_ = this->listBox1;
  listBox1_->BeginUpdate();
  listBox1_->Items->Clear();
  listBox1_->ClearSelected();
  EnumWindows(EnumWindowsProc, NULL);
  listBox1_->EndUpdate();
}



System::Void Form1::removeChanged_Click(System::Object^  sender, System::EventArgs^  e) {
  if (snapshot_ != NULL) {
    int cnt = ((SnapShot*) snapshot_)->trim(TRUE);
    char buf[255];
    sprintf(buf, "%d", cnt);
    elements->Text = gcnew String(buf);
  }
}
System::Void Form1::removeUnchanged_Click(System::Object^  sender, System::EventArgs^  e) {
  if (snapshot_ != NULL) {
    int cnt = ((SnapShot*) snapshot_)->trim(FALSE);
    char buf[255];
    sprintf(buf, "%d", cnt);
    elements->Text = gcnew String(buf);
  }
}

System::Void Form1::doSearch_Click(System::Object^  sender, System::EventArgs^  e) {
  DWORD pid = (DWORD) StringToInt(this->processID->Text);
  CompObj *c;
  if (this->useFloat->Checked) 
    c = new FloatObj((float) StringToFloat(this->floatValue->Text));
  else
    c = new IntObj(StringToInt(this->intBox->Text));
  if (snapshot_ != NULL) 
    delete (SnapShot*) snapshot_;
  SnapShot *sh = new SnapShot(pid);
  snapshot_ = sh;
  int cnt = sh->searchAndSnap(c, false, NULL, (char *) 0);
  char buf[255];
  sprintf(buf, "%d", cnt);
  elements->Text = gcnew String(buf);
  delete c;
}

System::Void Form1::searchSelected_Click(System::Object^  sender, System::EventArgs^  e) {
  if (snapshot_ != NULL) {
    CompObj *c;
    if (this->useFloat->Checked) 
      c = new FloatObj(StringToFloat(this->floatValue->Text));
    else
      c = new IntObj(StringToInt(this->intBox->Text));
    int cnt = ((SnapShot*) snapshot_)->trim(c);
    delete c;
    char buf[255];
    sprintf(buf, "%d", cnt);
    elements->Text = gcnew String(buf);
  }
}


System::Void Form1::watch_Click(System::Object^  sender, System::EventArgs^  e) {
  timer2->Enabled = TRUE;
  timer2->Interval = 100;
}

System::Void Form1::timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
  if (snapshot_ != NULL)  {
    SnapShot *ss =(SnapShot *)  snapshot_;
    if (ss->data_ == NULL)
      return;

    SIZE_T lpRead;
    HANDLE process=OpenProcess(PROCESS_ALL_ACCESS, FALSE, ss->hProcess_);
    char buf[255];
    void *addr = this->staticAddress->Checked ?  (void *) StringToInt(this->statbox->Text) : ss->data_->addr_;
    ReadProcessMemory( process, addr, buf, ss->data_->size_, &lpRead);
    char buf2[255];
    if (this->useFloat->Checked) 
      sprintf(buf2, "%f", *((float *) &buf[0]));
    else
      sprintf(buf2, "%d", *((unsigned int *) &buf[0]));
    valueLabel->Text = gcnew String(buf2);
    sprintf(buf2, "%x", addr);
    addressLabel->Text = gcnew String(buf2);
  }
}

System::Void Form1::findbase_Click(System::Object^  sender, System::EventArgs^  e) {
  ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
  if (pi == nullptr)
    return;
  DWORD pid = pi->dwProcessId_;
  CompObj *c = new FloatSetObj(StringToFloat(this->XBox->Text), 
                               StringToFloat(this->YBox->Text), 
                               StringToFloat(this->ZBox->Text), 
                               StringToFloat(this->HBox->Text));
  if (snapshot_ != NULL) 
    delete (SnapShot*) snapshot_;
  SnapShot *sh = new SnapShot(pid);
  pi->process_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  int cnt = sh->searchAndSnap(c, FALSE, pi->process_, (char *) pi->base_);
  delete c;
  if (cnt != 0) {
    char buf[255];
    sprintf(buf, "%d", sh->data_->addr_);
    this->baseBox->Text = gcnew String(buf);
    pi->base_ = sh->data_->addr_;

    addrEnter->BeginUpdate();
    addrEnter->Items->Clear();

    MemBuffer *first = sh->data_;
    while (first != NULL) {
      char buf[255];
      sprintf(buf, "%d", first->addr_);
      addrEnter->Items->Add(gcnew String(buf));
      first = first->next_;
    }

    addrEnter->EndUpdate();
  }
  delete sh;
}

System::Void Form1::toonName_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
  if (pi == nullptr)
    return;
  pi->toonName = this->toonName->Text;
}

System::Void Form1::leaderBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
  ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
  if (pi == nullptr)
    return;
  pi->leader = this->leaderBox1->Checked;
}

System::Void Form1::listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
  if (this->listBox1->SelectedIndex == -1)
    return;
  ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
  if (pi == nullptr)
    return;
  this->toonName->Text = pi->toonName;
  this->leaderBox1->Checked = pi->leader;

  char buf[255];
  sprintf(buf, "%d", pi->base_);
  this->baseBox->Text = gcnew String(buf);
  FlashWindow(pi->hWnd_, TRUE);
  Sleep(10);
  FlashWindow(pi->hWnd_, FALSE);
}

System::Void Form1::addrEnter_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  if (this->listBox1->SelectedIndex == -1)
    return;
  ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[this->listBox1->SelectedIndex];
  pi->base_ = (void *) StringToInt(this->addrEnter->Text);
  this->baseBox->Text = this->addrEnter->Text;
  if (pi->process_ == nullptr)
    pi->process_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pi->dwProcessId_);
}

System::Void Form1::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
  if (this->enableController->Checked) {
    LoadControllerStatus(*stateA_);
    if (memcmp(stateA_, stateB_, sizeof(*stateA_)))  {
      int slen = sizeof(*si_other_);
      int n = sendto(fd_, (const char*) stateA_, sizeof(*stateA_), 0,
                     (const sockaddr*) si_other_, slen);
      if (n < 0) 
        return;

      CheckControllerStatus(*stateB_, *stateA_);
      XINPUT_STATE   *t = stateB_;
      stateB_ = stateA_;
      stateA_ = t;
    }
  }
  
  if (this->toonSpy->Checked) {
    int len = this->listBox1->Items->Count;
    for (int i = 0; i < len; i++) {
      ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[i];
      pi->update(this, i == this->listBox1->SelectedIndex);
    }
  }
}

System::Void Form1::textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    switch (e->KeyCode) {
    case System::Windows::Forms::Keys::Left:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
      break;
    case System::Windows::Forms::Keys::Right:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
      break;
    case System::Windows::Forms::Keys::Up:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_UP, 0);
      break;
    case System::Windows::Forms::Keys::Down:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_DOWN, 0);
      break;
    case System::Windows::Forms::Keys::ControlKey:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
      break;
    case System::Windows::Forms::Keys::Delete:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_DELETE, 0);
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_DELETE, 0);
      break;
    case System::Windows::Forms::Keys::Home:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_HOME, 0);
      break;
    case System::Windows::Forms::Keys::End:
      ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_END, 0);
      break;
    default:
      break;
    }
  }
}

System::Void Form1::textBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    switch (e->KeyCode) {
    case System::Windows::Forms::Keys::Left:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_LEFT, 0);
      break;
    case System::Windows::Forms::Keys::Right:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      break;
    case System::Windows::Forms::Keys::Up:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_UP, 0);
      break;
    case System::Windows::Forms::Keys::Down:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_DOWN, 0);
      break;
    case System::Windows::Forms::Keys::ControlKey:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_CONTROL, 0);
      break;
    case System::Windows::Forms::Keys::Delete:
      break;
    case System::Windows::Forms::Keys::Home:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_HOME, 0);
      break;
    case System::Windows::Forms::Keys::End:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_END, 0);
      break;
    case System::Windows::Forms::Keys::Escape:
      ::SendMessage(primary->hWnd_, WM_KEYUP, VK_ESCAPE, 0);
      break;
    default:
      break;
    }
  }
}

 
System::Void Form1::timer3_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->listBox1->Items->Count;
  for (int i = 0; i < len; i++) {
    ProcessItem ^primary = (ProcessItem^) this->listBox1->Items[i];
    ::SendMessage(primary->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
    Sleep(100);
    ::SendMessage(primary->hWnd_, WM_KEYUP, VK_LEFT, 0);
  }
}

bool ProcessItem::updateGolf(float tx, float ty) {
  if (base_ == NULL)
    return true;

  char buf[255];
  SIZE_T lpRead;
  if (ReadProcessMemory( process_, base_, buf, sizeof(struct ToonPos), &lpRead)) {
    struct ToonPos *tp = (struct ToonPos *) &buf[0];
    if ((this->x != tp->_x) || (this->y != tp->_y) || (this->z != tp->_z)) 
      this->changed_ = true;
    else
      this->changed_ = false;
    this->x = tp->_x;
    this->y = tp->_y;
    this->z = tp->_z;
    this->h = tp->_h;
  }

  dh = (float) angleTo(this->x, this->y, tx, ty);

  dh = mmod(dh);
  float mh = mmod(this->h);
  float delta = mmod(dh - mh);
  double dist = distTo(this->x, this->y, tx, ty);
  double window = 10;
  if (dist < 2.0)
    window = 75;
  else if (dist < 4.0)
    window = 20;
  if ((delta < window) || (delta > (360.0 - window))) {
    if (turning_) {
      ::SendMessage(this->hWnd_, WM_KEYUP, VK_RIGHT, 0);
      ::SendMessage(this->hWnd_, WM_KEYUP, VK_LEFT, 0);
      turning_ = false;
    }
  } else if (delta < 180.0) {
    turning_ = true;
    ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
  } else {
    turning_ = true;
    ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
  }
  if (dist > 2)  {
    if ((turning_ == false) || ((delta < 10.0) || (delta > (350.0)))) {
      ::SendMessage(this->hWnd_, WM_KEYDOWN, VK_UP, 0);
      moving_ = true;
    }
  } else {
    if (moving_) {
      ::SendMessage(this->hWnd_, WM_KEYUP, VK_UP, 0);
      moving_ = false;
    }
  }
  return this->changed_;
}

System::Void Form1::GolfTimer2_Tick(System::Object^  sender, System::EventArgs^  e) {
  int len = this->listBox1->Items->Count;
  golfstate_++;
  for (int i = 0; i < len; i++) {
    ProcessItem ^pi = (ProcessItem ^) this->listBox1->Items[i];
    pi->updateGolf(tx_, ty_);

    if (pi->base_ != NULL) {
      if ((golfstate_ % 19) == 0) 
        ::SendMessage(pi->hWnd_, WM_KEYDOWN, VK_CONTROL, 0);
      if ((golfstate_ % 19) == 2)  {
        ::SendMessage(pi->hWnd_, WM_KEYUP, VK_CONTROL, 0);
        pi->moving_ = false;
        pi->turning_ = false;
        ::SendMessage(pi->hWnd_, WM_KEYDOWN, VK_RIGHT, 0);
        ::SendMessage(pi->hWnd_, WM_KEYUP, VK_RIGHT, 0);
        ::SendMessage(pi->hWnd_, WM_KEYDOWN, VK_LEFT, 0);
        ::SendMessage(pi->hWnd_, WM_KEYUP, VK_LEFT, 0);
        ::SendMessage(pi->hWnd_, WM_KEYDOWN, VK_UP, 0);
        ::SendMessage(pi->hWnd_, WM_KEYUP, VK_UP, 0);
      }
    }
  }
}

System::Void Form1::StartGolf_Click(System::Object^  sender, System::EventArgs^  e) {
  golfstate_ = 0;
  this->GolfTimer2->Enabled = true;
  this->GolfTimer2->Interval = 100;
}

System::Void Form1::StopGolf_Click(System::Object^  sender, System::EventArgs^  e) {
  this->GolfTimer2->Enabled = false;
}

System::Void Form1::CoursePicker_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
  if (this->CoursePicker->Text == "Front") {
    tx_ = 132;
    ty_ = 47.8;
    return;
  }
  if (this->CoursePicker->Text == "Middle") {
    tx_ = 10.8;
    ty_ = -95;
    return;
  }
  if (this->CoursePicker->Text == "Back") {
    tx_ = -96;
    ty_ = -28;
    return;
  }
}
