#include <stdio.h>
#include <string.h>

int main()
{
	// char str[] = "strtok needs to be called several times to split a string";
  char satir[100], *karakter; 
  char neyeGore[] = " ";
  FILE *readme  = fopen("readme.txt", "r");
  char *ptr;
 
  do {
    karakter =fgets(satir, 100, readme);
    //if (karakter != NULL) printf("%s", satir);
    ptr = strtok(satir, neyeGore);
    while(ptr != NULL)
	  {
		  printf("%s\n", ptr);
		  ptr = strtok(NULL, neyeGore);
	  }
  } while (karakter != NULL);
	

	
	return 0;
}