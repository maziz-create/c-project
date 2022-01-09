#include <stdio.h>
#include <string.h>
#include <stdbool.h> //bu olmadan bool değişkenler kullanılamıyor.
#include <stdlib.h>

//fopen: dosyayı istenilen modda açar.
//fgets: dosya okuma işlemi
//fprintf: dosyaya bir şeyler yazar.
//fclose: dosyayı kapatır.
//atoi: string ifadeyi integer'a çevirir.
//strtok: satırdaki ifadeleri string olarak okur.
//strtok(null): satır içindeki diğer kelimeye geçer.
//strcmp: string1 == string2 işlemini yapar.
//strcpy: string1 = string2 işlemini yapar.

struct oyuncu
{
  char isim[25];
  char soyIsim[25];
  int oynananMacSayisi;
  int hataliPas;
  int isabetliPas;
};

//oyuncunun kaydı varsa true, yoksa false döner.
bool oyuncununKaydiVarMi(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  for(int i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0){
      return true;
    }
  }
  return false;
}

//kaydı olan oyuncunun kaçıncı indekste yer aldığını döndürür
int oyuncununIndeksiniBul(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  for(int i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0) {
      return i;
    }
  }
  return -1;
}

//satır satır okuyacak, toplam.txt'in içeriğini üretecek.
void ekle(struct oyuncu oyuncular[20], char *karakter, char satir[100], FILE *paslar, char *okunanDeger, char neyeGore[], bool kaydiVarMi, int kacinciOyuncu, int oyuncununIndeksi, int ozellikSayaci) {
    do {
    karakter = fgets(satir, 100, paslar); // satırdeki tam veriler
    okunanDeger = strtok(satir, neyeGore); // isim

    if (strcmp(okunanDeger, "--\n") == 0) {
      continue;
    }

    kaydiVarMi = oyuncununKaydiVarMi(oyuncular, okunanDeger);

    if (kaydiVarMi) {
      oyuncununIndeksi = oyuncununIndeksiniBul(oyuncular, okunanDeger);
    }
   
    if (!kaydiVarMi) {
      oyuncular[kacinciOyuncu].oynananMacSayisi = 1;
      while(okunanDeger != NULL) {
        if (ozellikSayaci == 0) {
          strcpy(oyuncular[kacinciOyuncu].isim, okunanDeger);
        }else if (ozellikSayaci == 1) {
          strcpy(oyuncular[kacinciOyuncu].soyIsim, okunanDeger);
        }else if (ozellikSayaci == 2) {
          oyuncular[kacinciOyuncu].hataliPas = atoi(okunanDeger);
        }else if (ozellikSayaci == 3) {
          oyuncular[kacinciOyuncu].isabetliPas = atoi(okunanDeger);
        }
        okunanDeger = strtok(NULL, neyeGore); // bir sonraki kelimeye geç
        ozellikSayaci++;
      }
	  } else if (kaydiVarMi) {
      kacinciOyuncu--;
      oyuncular[oyuncununIndeksi].oynananMacSayisi++;
      while(okunanDeger != NULL) {
        if (ozellikSayaci == 2) {
          int eklenecekDeger = atoi(okunanDeger);
          oyuncular[oyuncununIndeksi].hataliPas += eklenecekDeger;
        }else if (ozellikSayaci == 3) {
          int eklenecekDeger = atoi(okunanDeger);
          oyuncular[oyuncununIndeksi].isabetliPas += eklenecekDeger;
        }
        okunanDeger = strtok(NULL, neyeGore); // bir sonraki kelimeye geç
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
  char neyeGore[] = " ", *okunanDeger;
  FILE *paslar = fopen("paslar.txt", "r");

  bool kaydiVarMi = false;
  int kacinciOyuncu = 0, oyuncununIndeksi = 0;
  int ozellikSayaci = 0;

  ekle(oyuncular, karakter, satir, paslar, okunanDeger, neyeGore, kaydiVarMi, kacinciOyuncu, oyuncununIndeksi, ozellikSayaci);

  fclose(paslar);

  yazdir(oyuncular);

	return 0;
}