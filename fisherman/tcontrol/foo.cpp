#include "stdafx.h"

int awake = 0;

int openPort(unsigned int &addr, unsigned short &port, int sender) {
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (fd == -1) {
    perror("socket");
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
    perror("bind");
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

DWORD LoadControllerStatus(XINPUT_STATE &state)
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

void keepAwake() {
  INPUT input[2];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_CONTROL;
  SendInput(1, input, sizeof(INPUT));
  Sleep(1000);
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_CONTROL;
  input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
  Sleep(1000);

  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;
  input[0].mi.dx = (int) 10;
  input[0].mi.dy = (int) 10;
  input[0].mi.mouseData = 0;
  input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
  input[0].mi.time = 0;
  SendInput(1, input, sizeof(INPUT));

  Sleep(1000);
  
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_MOUSE;
  input[0].mi.dx = (int) -10;
  input[0].mi.dy = (int) -10;
  input[0].mi.mouseData = 0;
  input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
  input[0].mi.time = 0;
  SendInput(1, input, sizeof(INPUT));
}

void YButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_END;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void AButton(bool oldv, bool newv, XINPUT_STATE &state) {
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

void BButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_HOME;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void XButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_CONTROL;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void RightThumbButton(bool oldv, bool newv, XINPUT_STATE &state) { 
}
void LeftThumbButton(bool oldv, bool newv, XINPUT_STATE &state) { 
}
void BackButton(bool oldv, bool newv, XINPUT_STATE &state) {
	awake = 0;
}
void StartButton(bool oldv, bool newv, XINPUT_STATE &state) {
	awake = 1;
}

void RightButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_RIGHT;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void LeftButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_LEFT;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void DownButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_DOWN;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}
void UpButton(bool oldv, bool newv, XINPUT_STATE &state) {
  INPUT input[1];
  memset(input, 0, sizeof(input));
  input[0].type = INPUT_KEYBOARD;
  input[0].ki.wVk  = VK_UP;
  if (newv == false) 
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
  SendInput(1, input, sizeof(INPUT));
}

void RightThumbXY(int newx, int newy, XINPUT_STATE &state) { 
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

void LeftThumbXY(int newx, int newy, XINPUT_STATE &state) {
}

void RightTrigger(int oldv, int newv, XINPUT_STATE &state) {
}

void LeftTrigger(int oldv, int newv, XINPUT_STATE &state) {
}

void RightShoulderButton(bool oldv, bool newv, XINPUT_STATE &state) {
  if (newv == true) {
    INPUT input[1];
    memset(input, 0, sizeof(input));
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk  = VK_DELETE;
    SendInput(1, input, sizeof(INPUT));
	Sleep(state.Gamepad.bLeftTrigger);
	input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk  = VK_DELETE;
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, input, sizeof(INPUT));
  }
}

void LeftShoulderButton(bool oldv, bool newv, XINPUT_STATE &state) { 
  if (newv == true) {
    INPUT input[1];
    memset(input, 0, sizeof(input));
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk  = VK_DELETE;
    SendInput(1, input, sizeof(INPUT));
	Sleep(state.Gamepad.bRightTrigger);
	input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk  = VK_DELETE;
    input[0].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, input, sizeof(INPUT));
  }
}

void CheckControllerStatus(XINPUT_STATE &old, XINPUT_STATE &state)
{
  if (state.Gamepad.sThumbLX != 0 || state.Gamepad.sThumbLY)
    LeftThumbXY(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, state);

  if (state.Gamepad.sThumbRX != 0 || state.Gamepad.sThumbRY)
    RightThumbXY(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, state);

  if (old.Gamepad.bLeftTrigger != state.Gamepad.bLeftTrigger)
    LeftTrigger(state.Gamepad.bLeftTrigger, state.Gamepad.bLeftTrigger, state);

  if (old.Gamepad.bRightTrigger != state.Gamepad.bRightTrigger)
    LeftTrigger(state.Gamepad.bRightTrigger, state.Gamepad.bRightTrigger, state);

#define CheckPad(_flag, _fun) \
  if (state.Gamepad.wButtons != old.Gamepad.wButtons) {\
    if ((state.Gamepad.wButtons & _flag) != (old.Gamepad.wButtons & _flag))\
      _fun((old.Gamepad.wButtons & _flag) != 0, (state.Gamepad.wButtons & _flag) != 0, state);\
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

void usage(const char* prog) {
  fprintf(stderr, "usage: %s\n", prog);
  exit(1);
}

int main(int argc, char **argv)
{
#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION MAKEWORD(2,2)
#endif

  /* Start up the windows networking */
  WSADATA wsaData;
  if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0) {
    printf("Initialization of windows networking failed\n");
  }


  unsigned int addr = htonl(inet_addr("239.0.10.10"));
  unsigned short port = 12345;
  int serv = 0;
  int loop = 1;

#define STRING_OPT (argv[i][j+1] == '\0' ? argv[++i] : &(argv[i][j+1]))
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j] != '\0'; ++j) {
        switch (argv[i][j]) {
        case 'a':
          {
	    char *sopt = STRING_OPT;
            addr = htonl(inet_addr(sopt));
          }
          goto next_i;
        case 'p':
          port = atoi(STRING_OPT);
          goto next_i;
        case 's':
          serv = 1;
          loop = 0;
          goto next_i;
        case 'c':
          loop = 0;
          goto next_i;
		case 'l':
          loop = 1;
          goto next_i;
        default:
          usage(argv[0]);
        }
      }
    } else
      usage(argv[0]);
  next_i: ;
  }

  int fd = 0;
  int cnt = 100;

  if (!loop) 
    fd = openPort(addr,  port, serv);

  XINPUT_STATE stateA, stateB;

  if (serv) {
    struct sockaddr_in si_other;
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    int slen = sizeof(si_other);
    si_other.sin_addr.s_addr = htonl(addr);
    si_other.sin_port = htons(port);

    LoadControllerStatus(stateB);

    while(1) {
      LoadControllerStatus(stateA);
      if (memcmp(&stateA, &stateB, sizeof(stateA)))  {
        int n = sendto(fd, (const char*) &stateA, sizeof(stateA), 0,
          (const sockaddr*) &si_other, slen);
        if (n < 0) {
          perror("sendto");
          break;
        }
        memcpy(&stateB, &stateA, sizeof(stateA));
      }
      Sleep(10);
      if (++cnt > 1000 && awake) {
        keepAwake();
        cnt = 0;
      }
    }
  } else if (loop) {
    int which = 0;

    LoadControllerStatus(stateA);
    LoadControllerStatus(stateB);

    int cnt = 0;
    while(1) {
      Sleep(10);
      if (which == 0) {
        which = 1;
        LoadControllerStatus(stateB);
        if (loop)
          CheckControllerStatus(stateA, stateB);
      } else { 
        which = 0;
        LoadControllerStatus(stateA);
        if (loop)
          CheckControllerStatus(stateB, stateA);
      }
      if (++cnt > 1000 && awake) {
        keepAwake();
        cnt = 0;
      }
    }
  } else { // client
    int first = 1;
    int n;
    while (1) {
      if ((n = recvfrom(fd, (char *) &stateA, sizeof(stateA), 0, NULL, NULL)) < 0)  {
        perror("recvfrom");
        break;
      }
      if (!first) {
        CheckControllerStatus(stateB, stateA);
        memcpy(&stateB, &stateA, sizeof(stateA));
      } else
        first = 0;
    }
  }
  return 0;
}

