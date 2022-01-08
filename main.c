#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct oyuncu  
{
  char isim[25];
  char soyIsim[25];
  int hataliPas;
  int oynananMacSayisi;  
  int isabetliPas;
};

bool oyuncununKaydiVarMi(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  for(int i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0){
      return true; 
    }
  }
  return false;
}

int oyuncununIndeksiniBul(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  for(int i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0) {
      return i;
    }
  }
  return -1;
}

void ekle(struct oyuncu oyuncular[20], char *karakter, char satir[100], FILE *paslar, char *ptr, char neyeGore[], bool kaydiVarMi, int kacinciOyuncu, int oyuncununIndeksi, int ozellikSayaci) {
    do {
    karakter = fgets(satir, 100, paslar); // satir
    ptr = strtok(satir, neyeGore); // isim

    if (strcmp(ptr, "--\n") == 0) {
      continue;
    }

    kaydiVarMi = oyuncununKaydiVarMi(oyuncular, ptr);
    if (kaydiVarMi) {
      oyuncununIndeksi = oyuncununIndeksiniBul(oyuncular, ptr);
    }
   
    if (!kaydiVarMi) {
      oyuncular[kacinciOyuncu].oynananMacSayisi = 1;
      while(ptr != NULL) {
        if (ozellikSayaci == 0) {
          strcpy(oyuncular[kacinciOyuncu].isim, ptr);
        }else if (ozellikSayaci == 1) {
          strcpy(oyuncular[kacinciOyuncu].soyIsim, ptr);
        }else if (ozellikSayaci == 2) {
          oyuncular[kacinciOyuncu].hataliPas = atoi(ptr);
        }else if (ozellikSayaci == 3) {
          oyuncular[kacinciOyuncu].isabetliPas = atoi(ptr);
        }
        ptr = strtok(NULL, neyeGore);
        ozellikSayaci++;
      }
	  } else if (kaydiVarMi) {
      kacinciOyuncu--;
      oyuncular[oyuncununIndeksi].oynananMacSayisi++;
      while(ptr != NULL) {
        if (ozellikSayaci == 2) {
          int eklenecekDeger = atoi(ptr);
          oyuncular[oyuncununIndeksi].hataliPas += eklenecekDeger;
        }else if (ozellikSayaci == 3) {
          int eklenecekDeger = atoi(ptr);
          oyuncular[oyuncununIndeksi].isabetliPas += eklenecekDeger;
        }
        ptr = strtok(NULL, neyeGore);
        ozellikSayaci++;
      }
    }
    kacinciOyuncu++;
    ozellikSayaci = 0;
  } while (karakter != NULL);
}

void yazdir(struct oyuncu oyuncular[20]) {
  FILE *toplam;
  toplam = fopen("toplam.txt","w");
  for (int i = 0; i < 20; i++) {
    fprintf(toplam,"%s ",oyuncular[i].isim);
    fprintf(toplam,"%s ",oyuncular[i].soyIsim);
    fprintf(toplam,"%d ",oyuncular[i].oynananMacSayisi);
    fprintf(toplam,"%d ",oyuncular[i].hataliPas);
    fprintf(toplam,"%d\n",oyuncular[i].isabetliPas);
  }
  fclose(toplam);
}

int main(){
  struct oyuncu oyuncular[20];

  char satir[100], *karakter;
  char neyeGore[] = " ", *ptr;
  FILE *paslar = fopen("paslar.txt", "r");

  bool kaydiVarMi = false;
  int kacinciOyuncu = 0, oyuncununIndeksi = 0;
  int ozellikSayaci = 0;

  ekle(oyuncular, karakter, satir, paslar, ptr, neyeGore, kaydiVarMi, kacinciOyuncu, oyuncununIndeksi, ozellikSayaci);

  fclose(paslar);

  yazdir(oyuncular);

	return 0;
}