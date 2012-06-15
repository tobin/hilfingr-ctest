/* Stern-Brocot tree

   Tobin Fricke
   June 11, 2012
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  
  char buf[255];

  while (gets(buf)) {

    int a = 0, b = 1,
        c = 1, d = 0;

    for (char *str = buf; *str; str++) {
      switch (*str) {
      case 'R':  // replace the left element	
	a = a + b;
	c = c + d;
	break;
      case 'L': // replace the right element
	b = a + b;
	d = c + d;
	break;
      default:
	return 1;
      }          
    }
    printf("%d/%d\n",a+b,c+d);
  }
  return 0;
}
