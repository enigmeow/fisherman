#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
#define SC (180.0 / 3.1415926)
	printf("%f\n", fmod(270.0 + ((double) atan2(4.0, 10.0)) * SC, 360.0));
    printf("%f\n", fmod(270.0 + ((double) atan2(-4.0, -10.0)) * SC, 360.0));
    printf("%f\n", fmod(270.0 + ((double) atan2(-4.0, 10.0)) * SC, 360.0));
	printf("%f\n", fmod(270.0 + ((double) atan2(4.0, -10.0)) * SC, 360.0));

  float f = 1.234;
  int x = 1234;
  printf("float 0x%x\n", &f);
    printf("int 0x%x\n", &x);

  while(1) {
    printf("Waiting for input\n");
    scanf("%f", &f);
    printf("read: %f\n", f);
  }
}
