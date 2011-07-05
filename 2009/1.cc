#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// BAUDOT

#define D if (0)
int main(int argc, char **argv) {
  
  // read down-shifted alphabet - 32 characters each
  char up[255], down[255], code[255];
  
  gets(up);
  gets(down);

  D printf("Up alphabet:   '%s'\n", up);
  D printf("Down alphabet: '%s'\n", down);
  
  while (gets(code)) {
    int mode = 1; // 0 = up, 1 = down
    char *mycode = code;
    D printf("Coded string:  '%s'\n", mycode);
    while (*mycode) {
      int bitpattern = 0;
      for (int i=0; i<5; i++) {
	assert(mycode[i]=='1' || mycode[i]=='0');
	bitpattern += (mycode[i] == '1') << (4-i);
      }
      mycode += 5;
      switch (bitpattern) {
	case 31: mode = 0; break;
	case 27: mode = 1; break;
      default:
	printf("%c", (mode ? up : down)[bitpattern]);
      }

    }
    printf("\n");
  }
  return 0;
}
