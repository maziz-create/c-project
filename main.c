#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct oyuncu  
{  
  char isim[25];
  char soyIsim[20];
  int oynananMacSayisi;  
  int hataliPas;  
  int isabetliPas;  
};

bool oyuncununKaydiVarMi(struct oyuncu gelenOyuncu, char gelenOyuncuAdi[20]) {
  if (strcmp(gelenOyuncu.isim, gelenOyuncuAdi) == 0)
  {
    return true; 
  }
  return false;
}

void oyuncuEkle(struct oyuncu gelenOyuncu) {

}


int main()
{
  struct oyuncu oyuncular[20];
  strcpy( oyuncular[0].isim, "Can");
  strcpy( oyuncular[1].isim, "Deniz");
  strcpy( oyuncular[2].isim, "Umit");

  char satir[100], *karakter;
  char neyeGore[] = " ";
  FILE *paslar = fopen("paslar.txt", "r");
  char *ptr;

  int kacinciOyuncu = 0;
 
  do {
    karakter = fgets(satir, 100, paslar);
    ptr = strtok(satir, neyeGore);
    if (oyuncununKaydiVarMi(oyuncular[kacinciOyuncu], ptr)) {
      printf("Kaydı var!\n");
    } else {
      printf("Kaydı yok!\n");
    }
    while(ptr != NULL)
	  {
		  printf("%s\n", ptr);
		  ptr = strtok(NULL, neyeGore);
	  }
    kacinciOyuncu++;
  } while (karakter != NULL);


	return 0;
}