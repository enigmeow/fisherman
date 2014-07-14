#include <stdlib.h>
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <io.h>

int main(int argc, char **argv) {
  HANDLE flog =  CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
    OPEN_EXISTING, (FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN), 0);

  while(1) {
    char buf[8000];
    DWORD nBytesRead = 0;
    BOOL bResult = ReadFile(flog, buf, sizeof(buf), &nBytesRead, NULL);
    if (bResult &&  nBytesRead == 0) 
      continue;
    printf("Read %d bytes\n", nBytesRead);
    const char *off = strstr(buf, "foo");
  }
}
