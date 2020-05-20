//! Prolab 2 Proje 2 Sıkıştırma Algoritmalarının Karşılaştırılması
//! Burak Can Temizel - 180202024
//! Özge Poyraz - 180202025

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//Blok Basliklari
#define DEFLATE_BLOK_SON_MOD_2 160
#define DEFLATE_BLOK_DEVAM_MOD_2 32

//Lz77 Sıkıştırma Birimleri
typedef struct SikistirmaBirimi8 {
    uint8_t uzaklikTekrar;
    unsigned char karakter;
}SikistirmaBirimi8;

typedef struct SikistirmaBirimi16 {
    uint16_t uzaklikTekrar;
    unsigned char karakter;
}SikistirmaBirimi16;

typedef struct SikistirmaBirimi24{
    uint16_t uzaklik;
    uint8_t tekrar;
    unsigned char karakter;
}SikistirmaBirimi24;

//Lz77 Sıkıştırma Fonksiyonları
SikistirmaBirimi8 *lz77Sikistirma8(unsigned char *sikistirilacakMetin, int metinUzunlugu, int *sikistirmaBirimiAdeti, int uzaklikBitleri, int tekrarBitleri)
{
    int bellekteAyrilanSikistirmaBirimleri = 1 * 2;
    int kullanilanSikistirmaBirimleri = 0;
    SikistirmaBirimi8 sikistirmaBirimi8;
    unsigned char *ileriYonlu, *arama;
    SikistirmaBirimi8 *sikistirilmisMetin = malloc(bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi8));

    for (ileriYonlu = sikistirilacakMetin; ileriYonlu < sikistirilacakMetin + metinUzunlugu; ileriYonlu++)
    {
        arama = ileriYonlu - ((1 << (uzaklikBitleri)) - 1);
        if (arama < sikistirilacakMetin)
            arama = sikistirilacakMetin;

        int maksEslesmeUzunlugu = 0;
        unsigned char *maksEslesmePozisyonu = ileriYonlu;

        for (; arama < ileriYonlu; arama++)
        {
            int uzunluk = 0;

            unsigned char *geciciArama = arama;
            unsigned char *geciciIleriYonlu = ileriYonlu;
            while (*geciciArama++ == *geciciIleriYonlu++ && uzunluk < ((1 << (tekrarBitleri)) - 1))
                uzunluk++;

            if (uzunluk > maksEslesmeUzunlugu)
            {
                maksEslesmeUzunlugu = uzunluk;
                maksEslesmePozisyonu = arama;
            }
        }

        if (ileriYonlu + maksEslesmeUzunlugu >= sikistirilacakMetin + metinUzunlugu)
        {
            maksEslesmeUzunlugu = sikistirilacakMetin + metinUzunlugu - ileriYonlu - 1;
        }

        sikistirmaBirimi8.uzaklikTekrar = (ileriYonlu - maksEslesmePozisyonu << tekrarBitleri | maksEslesmeUzunlugu);
        ileriYonlu += maksEslesmeUzunlugu;
        sikistirmaBirimi8.karakter = *ileriYonlu;

        if (kullanilanSikistirmaBirimleri + 1 > bellekteAyrilanSikistirmaBirimleri)
        {
            bellekteAyrilanSikistirmaBirimleri = bellekteAyrilanSikistirmaBirimleri * 2;
            sikistirilmisMetin = realloc(sikistirilmisMetin, bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi8));
        }

        sikistirilmisMetin[kullanilanSikistirmaBirimleri++] = sikistirmaBirimi8;
    }

    if (sikistirmaBirimiAdeti)
        *sikistirmaBirimiAdeti = kullanilanSikistirmaBirimleri;

    return sikistirilmisMetin;
}

SikistirmaBirimi16 *lz77Sikistirma16(unsigned char *sikistirilacakMetin, int metinUzunlugu, int *sikistirmaBirimiAdeti, int uzaklikBitleri, int tekrarBitleri)
{
    int bellekteAyrilanSikistirmaBirimleri = 1 * 2;
    int kullanilanSikistirmaBirimleri = 0;
    SikistirmaBirimi16 sikistirmaBirimi16;
    unsigned char *ileriYonlu, *arama;
    SikistirmaBirimi16 *sikistirilmisMetin = malloc(bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi16));


    for (ileriYonlu = sikistirilacakMetin; ileriYonlu < sikistirilacakMetin + metinUzunlugu; ileriYonlu++)
    {
        arama = ileriYonlu - ((1 << (uzaklikBitleri)) - 1);
        if (arama < sikistirilacakMetin)
            arama = sikistirilacakMetin;
        int maksEslesmeUzunlugu = 0;
        unsigned char *maksEslesmePozisyonu = ileriYonlu;

        for (; arama < ileriYonlu; arama++)
        {
            int uzunluk = 0;

            unsigned char *geciciArama = arama;
            unsigned char *geciciIleriYonlu = ileriYonlu;
            while (*geciciArama++ == *geciciIleriYonlu++ && uzunluk < ((1 << (tekrarBitleri)) - 1))
                uzunluk++;

            if (uzunluk > maksEslesmeUzunlugu)
            {
                maksEslesmeUzunlugu = uzunluk;
                maksEslesmePozisyonu = arama;
            }
        }

        if (ileriYonlu + maksEslesmeUzunlugu >= sikistirilacakMetin + metinUzunlugu)
        {
            maksEslesmeUzunlugu = sikistirilacakMetin + metinUzunlugu - ileriYonlu - 1;
        }

        sikistirmaBirimi16.uzaklikTekrar = (ileriYonlu - maksEslesmePozisyonu << tekrarBitleri | maksEslesmeUzunlugu);
        ileriYonlu += maksEslesmeUzunlugu;
        sikistirmaBirimi16.karakter = *ileriYonlu;

        if (kullanilanSikistirmaBirimleri + 1 > bellekteAyrilanSikistirmaBirimleri)
        {
            bellekteAyrilanSikistirmaBirimleri = bellekteAyrilanSikistirmaBirimleri * 2;
            sikistirilmisMetin = realloc(sikistirilmisMetin, bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi16));
        }

        sikistirilmisMetin[kullanilanSikistirmaBirimleri++] = sikistirmaBirimi16;
    }

    if (sikistirmaBirimiAdeti)
        *sikistirmaBirimiAdeti = kullanilanSikistirmaBirimleri;

    return sikistirilmisMetin;
}

SikistirmaBirimi24 *lz77Sikistirma24(unsigned char *sikistirilacakMetin, int metinUzunlugu, int *sikistirmaBirimiAdeti, int uzaklikBitleri, int tekrarBitleri)
{
    int bellekteAyrilanSikistirmaBirimleri = 1 * 2;
    int kullanilanSikistirmaBirimleri = 0;
    SikistirmaBirimi24 sikistirmaBirimi24;
    unsigned char *ileriYonlu, *arama;
    SikistirmaBirimi24 *sikistirilmisMetin = malloc(bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi24));
    for (ileriYonlu = sikistirilacakMetin; ileriYonlu < sikistirilacakMetin + metinUzunlugu; ileriYonlu++)
    {
        arama = ileriYonlu - ((1 << (uzaklikBitleri)) - 1);
        if (arama < sikistirilacakMetin)
            arama = sikistirilacakMetin;

        int maksEslesmeUzunlugu = 0;

        unsigned char *maksEslesmePozisyonu = ileriYonlu;

        for (; arama < ileriYonlu; arama++)
        {
            int uzunluk = 0;

            unsigned char *geciciArama = arama;
            unsigned char *geciciIleriYonlu = ileriYonlu;
            while (*geciciArama++ == *geciciIleriYonlu++ && uzunluk < ((1 << (tekrarBitleri)) - 1))
                uzunluk++;

            if (uzunluk > maksEslesmeUzunlugu)
            {
                maksEslesmeUzunlugu = uzunluk;
                maksEslesmePozisyonu = arama;
            }
        }

        if (ileriYonlu + maksEslesmeUzunlugu >= sikistirilacakMetin + metinUzunlugu)
        {
            maksEslesmeUzunlugu = sikistirilacakMetin + metinUzunlugu - ileriYonlu - 1;
        }

        sikistirmaBirimi24.uzaklik = ileriYonlu - maksEslesmePozisyonu;
        sikistirmaBirimi24.tekrar = maksEslesmeUzunlugu;
        ileriYonlu += maksEslesmeUzunlugu;
        sikistirmaBirimi24.karakter = *ileriYonlu;

        if (kullanilanSikistirmaBirimleri + 1 > bellekteAyrilanSikistirmaBirimleri)
        {
            bellekteAyrilanSikistirmaBirimleri = bellekteAyrilanSikistirmaBirimleri * 2;
            sikistirilmisMetin = realloc(sikistirilmisMetin, bellekteAyrilanSikistirmaBirimleri * sizeof(SikistirmaBirimi24));
        }
        sikistirilmisMetin[kullanilanSikistirmaBirimleri++] = sikistirmaBirimi24;
    }

    if (sikistirmaBirimiAdeti)
        *sikistirmaBirimiAdeti = kullanilanSikistirmaBirimleri;

    return sikistirilmisMetin;
}

//Lz77 Cozumleme Fonksiyonları
unsigned char *lz77Cozumleme8(SikistirmaBirimi8 * sikistirilmisMetin, int sikistirmaBirimiAdeti, int * boyut, int uzaklikBitleri, int tekrarBitleri)
{
    int ayrilanBellek = 1 * 2;
    *boyut = 0;
    unsigned char *cozumlenenMetin = malloc(ayrilanBellek);

    int i;
    for (i = 0; i < sikistirmaBirimiAdeti; i++)
    {
        int uzaklik = sikistirilmisMetin[i].uzaklikTekrar >> tekrarBitleri;
        int tekrar = sikistirilmisMetin[i].uzaklikTekrar & ( (1 << tekrarBitleri)-1);
        unsigned char karakter = sikistirilmisMetin[i].karakter;
        if (*boyut + tekrar + 1 > ayrilanBellek)
        {
            ayrilanBellek = ayrilanBellek * 2;
            cozumlenenMetin = realloc(cozumlenenMetin, ayrilanBellek);
        }

        if (tekrar > 0)
        {
            unsigned char * hedef = &cozumlenenMetin[*boyut];
            unsigned char * kopyalanan = &cozumlenenMetin[*boyut - uzaklik];
            int tmptekrar = tekrar;
            while (tmptekrar--)
                *hedef++ = *kopyalanan++;
        }

        *boyut += tekrar;

        cozumlenenMetin[*boyut] = karakter;

        *boyut = *boyut + 1;
    }

    return cozumlenenMetin;
}

unsigned char *lz77Cozumleme16(SikistirmaBirimi16 *sikistirilmisMetin, int sikistirmaBirimiAdeti, int *boyut, int uzaklikBitleri, int tekrarBitleri)
{
    int ayrilanBellek = 1 *2;
    *boyut = 0;
    unsigned char *cozumlenenMetin = malloc(ayrilanBellek);
    int i;
    for (i = 0; i < sikistirmaBirimiAdeti; i++)
    {
        int uzaklik = sikistirilmisMetin[i].uzaklikTekrar >> tekrarBitleri;
        int tekrar = sikistirilmisMetin[i].uzaklikTekrar & ( (1 << tekrarBitleri)-1);
        unsigned char karakter = sikistirilmisMetin[i].karakter;
        if (*boyut + tekrar + 1 > ayrilanBellek)
        {
            ayrilanBellek = ayrilanBellek * 2;
            cozumlenenMetin = realloc(cozumlenenMetin, ayrilanBellek);
        }
        if (tekrar > 0)
        {
            unsigned char * hedef = &cozumlenenMetin[*boyut];
            unsigned char * kopyalanan = &cozumlenenMetin[*boyut - uzaklik];
            int tmptekrar = tekrar;
            while (tmptekrar--)
                *hedef++ = *kopyalanan++;
        }
        *boyut += tekrar;
        cozumlenenMetin[*boyut] = karakter;
        *boyut = *boyut + 1;
    }

    return cozumlenenMetin;
}

unsigned char *lz77Cozumleme24(SikistirmaBirimi24 *sikistirilmisMetin, int sikistirmaBirimiAdeti, int *boyut, int uzaklikBitleri, int tekrarBitleri)
{
    int ayrilanBellek = 1 * 2;
    *boyut = 0;
    unsigned char *cozumlenenMetin = malloc(ayrilanBellek);

    int i;
    for (i = 0; i < sikistirmaBirimiAdeti; i++)
    {
        int uzaklik = sikistirilmisMetin[i].uzaklik;
        int tekrar = sikistirilmisMetin[i].tekrar;
        unsigned char karakter = sikistirilmisMetin[i].karakter;

        if (*boyut + tekrar + 1 > ayrilanBellek)
        {
            ayrilanBellek = ayrilanBellek * 2;
            cozumlenenMetin = realloc(cozumlenenMetin, ayrilanBellek);
        }

        if (tekrar > 0)
        {
            unsigned char * hedef = &cozumlenenMetin[*boyut];
            unsigned char * kopyalanan = &cozumlenenMetin[*boyut - uzaklik];
            int tmptekrar = tekrar;
            while (tmptekrar--)
            *hedef++ = *kopyalanan++;
        }
        *boyut += tekrar;
        cozumlenenMetin[*boyut] = karakter;
        *boyut = *boyut + 1;
    }

    return cozumlenenMetin;
}

unsigned char *dosyaYukle(FILE *dosya, int *boyut)
{
    unsigned char *yazi;
    fseek(dosya, 0, SEEK_END);
    *boyut = ftell(dosya);
    yazi = malloc(*boyut);
    fseek(dosya, 0, SEEK_SET);
    fread(yazi, 1, *boyut, dosya);
    return yazi;
}

clock_t sayacBaslat, sayacBitir;
double gecenIslemciZamani;

//Huffman
typedef struct HuffmanAgaci{
    unsigned char karakter;
    int frekans;
    struct HuffmanAgaci * sol;
    struct HuffmanAgaci * sag;
}HuffmanAgaci;

typedef struct HuffmanDizisi{
    int kapasite;
    int boyut;
    HuffmanAgaci ** deger;
}HuffmanDizisi;

typedef struct HuffmanKodu{
    uint16_t kod;
    uint8_t uzunluk;
}HuffmanKodu;

//Deflate
unsigned char blokBilgisi;

struct HuffmanKodu agac[256];
//Deflatede kodlar max 15 bit ile gösterilmeli.
uint8_t b1_sayac[16];
uint16_t sonrakiKod[16];

HuffmanAgaci * HuffmanAgaciOlustur(unsigned char karakter, int frekans){
    HuffmanAgaci * huffmanAgaci = malloc(sizeof(HuffmanAgaci));
    huffmanAgaci->karakter = karakter;
    huffmanAgaci->frekans = frekans;
    huffmanAgaci->sol = NULL;
    huffmanAgaci->sag = NULL;
    return huffmanAgaci;
}

HuffmanDizisi * huffmanDizisiOlustur(){
    HuffmanDizisi * huffmanDizisi = malloc(sizeof(HuffmanDizisi));
    huffmanDizisi->kapasite = 8;
    huffmanDizisi->boyut = 0;
    huffmanDizisi->deger = malloc(huffmanDizisi->kapasite * sizeof(HuffmanAgaci *));
    return huffmanDizisi;
}

void *huffmanDizisineEkle(HuffmanDizisi * huffmanDizisi, HuffmanAgaci * huffmanAgaci){
    if(huffmanDizisi->boyut + 1 == huffmanDizisi->kapasite){
        huffmanDizisi->kapasite *= 2;
        huffmanDizisi->deger = realloc(huffmanDizisi->deger, huffmanDizisi->kapasite * sizeof(HuffmanAgaci *));
    }

    huffmanDizisi->deger[huffmanDizisi->boyut++] = huffmanAgaci;
}

void huffmanDizisiniSirala(HuffmanDizisi * huffmanDizisi){
    int i, k;
    int maksimumIndex;
    int maksimumDeger;

    for(i = 0; i < huffmanDizisi->boyut-1; i++){
        maksimumIndex = i;
        maksimumDeger = huffmanDizisi->deger[i]->frekans;

        for(k = i + 1; k < huffmanDizisi->boyut; k++){
            if(huffmanDizisi->deger[k]->frekans > maksimumDeger){
                maksimumDeger = huffmanDizisi->deger[k]->frekans;
                maksimumIndex = k;
            }
        }

        if(i != maksimumIndex){
            unsigned long a = (unsigned long)huffmanDizisi->deger[i];
            unsigned long b = (unsigned long)huffmanDizisi->deger[maksimumIndex];

            a = a ^ b;
            huffmanDizisi->deger[i] = a;
            b = b ^ a;
            huffmanDizisi->deger[maksimumIndex] = b;
            a = a ^ b;
            huffmanDizisi->deger[i] = a;
        }

    }
}

HuffmanAgaci * huffmanDizisindenCikar(HuffmanDizisi * huffmanDizisi){
    return huffmanDizisi->deger[--huffmanDizisi->boyut];
}

void huffmanAgaciYazdir(HuffmanAgaci * huffmanAgaci, unsigned char * kod, int kodBoyutu){
    if(huffmanAgaci->sol == NULL && huffmanAgaci->sag == NULL){
        kod[kodBoyutu] = 0;
        printf("%c: %s\n", huffmanAgaci->karakter, kod);
        return;
    }

    if(huffmanAgaci->sol){
        kod[kodBoyutu++] = '0';
        huffmanAgaciYazdir(huffmanAgaci->sol, kod, kodBoyutu);
        kodBoyutu--;
    }

    if(huffmanAgaci->sag){
        kod[kodBoyutu++] = '1';
        huffmanAgaciYazdir(huffmanAgaci->sag, kod, kodBoyutu);
        kodBoyutu--;
    }
}

void huffmanKoduBul(HuffmanAgaci * huffmanAgaci, unsigned char * kod, int kodBoyutu,unsigned char arananKarakter, unsigned char * ciktiKod){
    if(huffmanAgaci->sol == NULL && huffmanAgaci->sag == NULL){
        kod[kodBoyutu] = 0;
        //printf("%c: %s\n", huffmanAgaci->karakter, kod);
        if(huffmanAgaci->karakter == arananKarakter){
            strcpy(ciktiKod,kod);
        }

        //return; ?? bu ifadeyi kontrol et
    }

    if(huffmanAgaci->sol){
        kod[kodBoyutu++] = '0';
        huffmanKoduBul(huffmanAgaci->sol, kod, kodBoyutu, arananKarakter, ciktiKod);
        kodBoyutu--;
    }

    if(huffmanAgaci->sag){
        kod[kodBoyutu++] = '1';
        huffmanKoduBul(huffmanAgaci->sag, kod, kodBoyutu, arananKarakter, ciktiKod);
        kodBoyutu--;
    }
}

void standartKodlariGetir(HuffmanAgaci * huffmanAgaci, int uzunluk){
    if(huffmanAgaci == NULL){
        return;
    }

    if(huffmanAgaci->karakter != 0){
        agac[huffmanAgaci->karakter].uzunluk = uzunluk;
    }

    standartKodlariGetir(huffmanAgaci->sol, uzunluk+1);
    standartKodlariGetir(huffmanAgaci->sag, uzunluk+1);
}

unsigned char * koduBinaryYap(struct HuffmanKodu kod){
    unsigned char * b = malloc(kod.uzunluk + 1);
    int i;

    for(i = 0; i < kod.uzunluk; i++){
        b[i] = kod.kod & (1 << (kod.uzunluk - i - 1)) ? '1' : '0';
    }

    b[kod.uzunluk] = 0;
	return b;
}

unsigned char *karakterDosyaOku(unsigned char *dosyaAdi) {
    FILE *dosya = fopen(dosyaAdi, "r");
    unsigned char *yazi;
    size_t n = 0;
    int c;

    if (dosya == NULL) return NULL;
    fseek(dosya, 0, SEEK_END);
    long f_size = ftell(dosya);
    fseek(dosya, 0, SEEK_SET);
    yazi = malloc(f_size);

    while ((c = fgetc(dosya)) != EOF) {
        yazi[n++] = (unsigned char)c;
    }

    yazi[n] = '\0';

    return yazi;
}

void binaryStringiBitYap(char * string, char * cikti){
    int i;
    unsigned char karakterKodu = 0;
    int basamak = 7; //8. basamak
    int sayiDegeri;
    //printf("\n\n");
    char eklenecekKarakter[2];
    for(i = 0; string[i] != NULL; i++){
        if(string[i] == '1'){
            sayiDegeri = 1;
            karakterKodu += pow(2, basamak);
        }else{
            sayiDegeri = 0;
            //karakterKodu += pow(2, basamak);
        }
        basamak--;

        //printf("%c---", karakterKodu);

        if(string[i+1] == NULL){
            //printf("%c", karakterKodu);
            sprintf(eklenecekKarakter,"%c",karakterKodu%256);
            strcat(cikti,eklenecekKarakter);
            //sprintf(cikti,"%c",karakterKodu);
            //printf("%s",cikti);
            break;
        }
        if(basamak == -1){
            //printf("%c", karakterKodu);
            //sprintf(cikti,"%c",karakterKodu);
            sprintf(eklenecekKarakter,"%c",karakterKodu%256);
            strcat(cikti,eklenecekKarakter);
            //cikti[i] = karakterKodu;
            karakterKodu = 0;
            basamak = 7;
        }

    }

    strcat(cikti,"\0");

    //Burdan gelen kodlamayi basicaz dosyaya

    //printf("%c ",128+16);
    //printf("%c ",64+32+16+8+4);
    //printf("%c ",128+64+32+16+4+2+1);
    //printf("%c ",64+32);
}

void main(){
    unsigned char *locale = setlocale(LC_ALL, "");
    //setlocale(LC_ALL, "Turkish");
    printf("\n   /////|\n  ///// |\n |~~~|  |                   Prolab 2 Proje 2\n |===|  |    Sikistirma Algoritmalarinin Karsilastirilmasi \n |   |  |           Burak Can Temizel - Ozge Poyraz\n |   |  |                180202024 - 180202025\n |   | /\n |===|/\n '---'\n\n");
    printf("!Lutfen programin alt dizininde metin.txt'nin var oldugundan emin olunuz! \n");
    printf("!Islemler bu dosya uzerinde yapilacaktir!\n\nmetin.txt'de yapilan degisikliklerden sonra programi bastan baslatiniz.\nAksi halde guncel hali isleme alinmayacaktir!\n\n");

    FILE * sikistirilacakDosya;
    unsigned char * sikistirilacakMetin;
    int sikistirilacakMetinBoyutu;
    sikistirilacakDosya = fopen("metin.txt", "rb");

    if(sikistirilacakDosya != NULL){
        sikistirilacakMetin = dosyaYukle(sikistirilacakDosya, &sikistirilacakMetinBoyutu);
        printf("Bilgi - Dosya yuklendi!\n");
        printf("Dosya Boyutu: %d\n", sikistirilacakMetinBoyutu);
        fclose(sikistirilacakDosya);
    }else{
        printf("Hata - Metin.txt okunurken bir hata olustu! Lutfen hatayi gideriniz. Programdan cikis yapiliyor.\n");
        printf("Cikmak icin entera basiniz!");
        getchar();
        return 0;
    }

    int islem = 0;
    int lz77islem = 0;
    int huffmanislem = 0;
    int deflateislem = 0;

    while(1){
        printf("\nIslem Menusu\n");
        printf("1 - Lz77 Sikistirma\n");
        printf("2 - Huffman Kodlamasi\n");
        printf("3 - Deflate\n");
        printf("4 - Cikis\n");

        printf("Gerceklestirmek istediginiz islemi giriniz:");
        scanf("%d", &islem);

        switch(islem){
            case 1:

                printf("\n\nBu programda 3 farkli lz77 konfigurasyonu bulunmaktadir.\n");
                printf("Farkli dosyalar icin farkli optimizasyonlara sahiptirler bu yuzden \"hepsini\" calistirmaniz tavsiye edilir.\n");
                printf("Algoritmalarin calisma zamanlari 6 mb txt uzerinde yaklasik olarak lz77-8 0.5 sn, lz77-16 8 sn, lz77-24 40 sn dir.\n");
                printf("1 - lz77-16 12 uzaklik biti, 4 tekrar biti kullanir.Ortalama sikistirma yapar fakat hizlidir.\n");
                printf("2 - lz77-8 5 uzaklik biti, 3 tekrar biti kullanir. Kisa metin ve ufak dosyalarin sikistirilmasi icin idealdir.\n");
                printf("3 - lz77-24 15 uzaklik biti, 8 tekrar biti kullanir.Yuksek oranda sikistirma yapar.(Varsayilan)\n");
                printf("4 - Tum konfigurasyonlari calistir.\n");

                printf("Gerceklestirmek istediginiz islemi giriniz:");
                scanf("%d", &lz77islem);

                if(lz77islem == 1 || lz77islem == 4){
                        printf("\nBilgi - Lz77-16 ile sikistirma yapiliyor lutfen bekleyiniz...\n");
                        sayacBaslat = clock();
                        int SikistirmaBirimi16Sayisi;
                        SikistirmaBirimi16 * sikistirilmisMetin;
                        sikistirilmisMetin = lz77Sikistirma16(sikistirilacakMetin, sikistirilacakMetinBoyutu, &SikistirmaBirimi16Sayisi, 12, 4);
                        printf("Bilgi - Lz77-16 ile sikistirma islemi tamamlandi.\n");
                        printf("Bilgi - Lz77-16 ile geri cozumleme islemi yapiliyor lutfen bekleyiniz...\n");
                        unsigned char * cozumlenmisMetin = "";
                        int cozumlemeBoyutu;
                        cozumlenmisMetin = lz77Cozumleme16(sikistirilmisMetin, SikistirmaBirimi16Sayisi, &cozumlemeBoyutu,12,4);

                        printf("Bilgi - Lz77-16 ile geri cozumleme islemi tamamlandi.\n");


                        FILE * sikistirilmisDosya;
                        if (sikistirilmisDosya = fopen("metin_lz77-16_Sikistirma.txt", "wb"))
                        {
                            fwrite(sikistirilmisMetin, sizeof(struct SikistirmaBirimi16), SikistirmaBirimi16Sayisi, sikistirilmisDosya);
                            fclose(sikistirilmisDosya);
                        }

                        FILE * cozumlemeCiktiDosya;
                        if (cozumlemeCiktiDosya = fopen("metin_lz77-16_GeriCozumleme.txt", "wb"))
                        {
                            fwrite(cozumlenmisMetin, 1, cozumlemeBoyutu, cozumlemeCiktiDosya);
                            fclose(cozumlemeCiktiDosya);
                        }

                        /*
                        FILE * okunabilirCikti;
                        if( okunabilirCikti = fopen("metin_lz77-16_OkunabilirCikti.txt", "w")){
                            for(int i = 0; i < SikistirmaBirimi16Sayisi; i++){
                                fprintf(okunabilirCikti,"<%d,%d,c(%c)>\n",sikistirilmisMetin[i].uzaklikTekrar >> 4, sikistirilmisMetin[i].uzaklikTekrar &  ( (1 << 4)-1), sikistirilmisMetin[i].karakter);
                            }

                            fclose(okunabilirCikti);
                        }
                        */

                        printf("Bilgi - Lz77-16 ciktilari olusturuldu..");
                        sayacBitir = clock();
                        gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                        printf("\n\nLz77-16 Sikistirma Sonuclari:\n");
                        printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi16) * SikistirmaBirimi16Sayisi);
                        printf("Geri Cozumlenmis Boyutu: %d\n", cozumlemeBoyutu);
                        printf("Sikistirma Orani: %lf\n", sizeof(SikistirmaBirimi16) * SikistirmaBirimi16Sayisi / (float)sikistirilacakMetinBoyutu );
                        printf("Gecen zaman : %lf \n", gecenIslemciZamani);
                }

                if(lz77islem == 2 || lz77islem == 4){
                        printf("\nBilgi - Lz77-8 ile sikistirma yapiliyor lutfen bekleyiniz...\n");
                        sayacBaslat = clock();
                        int SikistirmaBirimi8Sayisi;
                        SikistirmaBirimi8 * sikistirilmisMetin2;
                        sikistirilmisMetin2 = lz77Sikistirma8(sikistirilacakMetin, sikistirilacakMetinBoyutu, &SikistirmaBirimi8Sayisi, 5, 3);

                        printf("Bilgi - Lz77-8 ile sikistirma islemi tamamlandi.\n");
                        printf("Bilgi - Lz77-8 ile geri cozumleme islemi yapiliyor lutfen bekleyiniz...\n");
                        unsigned char * cozumlenmisMetin2 = "";
                        int cozumlemeBoyutu2;
                        cozumlenmisMetin2 = lz77Cozumleme8(sikistirilmisMetin2, SikistirmaBirimi8Sayisi, &cozumlemeBoyutu2,5,3);
                        printf("Bilgi - Lz77-8 ile geri cozumleme islemi tamamlandi.\n");

                        FILE * sikistirilmisDosya2;
                        if (sikistirilmisDosya2 = fopen("metin_lz77-8_Sikistirma.txt", "wb"))
                        {
                            fwrite(sikistirilmisMetin2, sizeof(struct SikistirmaBirimi8), SikistirmaBirimi8Sayisi, sikistirilmisDosya2);
                            fclose(sikistirilmisDosya2);
                        }

                        FILE * cozumlemeCiktiDosya2;
                        if (cozumlemeCiktiDosya2 = fopen("metin_lz77-8_GeriCozumleme.txt", "wb"));
                        {
                            fwrite(cozumlenmisMetin2, 1, cozumlemeBoyutu2, cozumlemeCiktiDosya2);
                            fclose(cozumlemeCiktiDosya2);
                        }
                        printf("Bilgi - Lz77-8 ciktilari olusturuldu..");

                        sayacBitir = clock();
                        gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                        printf("\n\nLz77-8 Sikistirma Sonuclari:\n");
                        printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi8) * SikistirmaBirimi8Sayisi);
                        printf("Geri Cozumlenmis Boyutu: %d\n", cozumlemeBoyutu2);
                        printf("Sikistirma Orani: %lf\n", sizeof(SikistirmaBirimi8) * SikistirmaBirimi8Sayisi / (float)sikistirilacakMetinBoyutu);
                        printf("Gecen zaman : %lf \n", gecenIslemciZamani);
                }

                if(lz77islem == 3 || lz77islem == 4){
                        printf("\nBilgi - Lz77-24 ile sikistirma yapiliyor lutfen bekleyiniz...\n");
                        sayacBaslat = clock();
                        int SikistirmaBirimi24Sayisi;
                        SikistirmaBirimi24 * sikistirilmisMetin3;
                        sikistirilmisMetin3 = lz77Sikistirma24(sikistirilacakMetin, sikistirilacakMetinBoyutu, &SikistirmaBirimi24Sayisi, 15, 8);
                        printf("Bilgi - Lz77-24 ile sikistirma islemi tamamlandi.\n");
                        printf("Bilgi - Lz77-24 ile geri cozumleme islemi yapiliyor lutfen bekleyiniz...\n");
                        unsigned char * cozumlenmisMetin3 = "";
                        int cozumlemeBoyutu3;
                        cozumlenmisMetin3 = lz77Cozumleme24(sikistirilmisMetin3, SikistirmaBirimi24Sayisi, &cozumlemeBoyutu3,15,8);
                        printf("Bilgi - Lz77-24 ile geri cozumleme islemi tamamlandi.\n");

                        FILE * sikistirilmisDosya3;
                        if (sikistirilmisDosya3 = fopen("metin_lz77-24_Sikistirma.txt", "wb"))
                        {
                            fwrite(sikistirilmisMetin3, sizeof(struct SikistirmaBirimi24), SikistirmaBirimi24Sayisi, sikistirilmisDosya3);
                            fclose(sikistirilmisDosya3);
                        }

                        FILE * cozumlemeCiktiDosya3;
                        if (cozumlemeCiktiDosya3 = fopen("metin_lz77-24_GeriCozumleme.txt", "wb"));
                        {
                            fwrite(cozumlenmisMetin3, 1, cozumlemeBoyutu3, cozumlemeCiktiDosya3);
                            fclose(cozumlemeCiktiDosya3);
                        }
                        printf("Bilgi - Lz77-24 ciktilari olusturuldu..");
                        sayacBitir = clock();
                        gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                        printf("\n\nLz77-24 Sikistirma Sonuclari:\n");
                        printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi24) * SikistirmaBirimi24Sayisi);
                        printf("Geri Cozumlenmis Boyutu: %d\n", cozumlemeBoyutu3);
                        printf("Sikistirma Orani: %lf\n", sizeof(SikistirmaBirimi24) * SikistirmaBirimi24Sayisi / (float)sikistirilacakMetinBoyutu);
                        printf("Gecen zaman : %lf \n", gecenIslemciZamani);
                }

                if(lz77islem <= 0 ||lz77islem > 4){
                    printf("\nHata - Gecersiz islem tekrar deneyiniz!\n");
                }
            break;

            case 2:
                printf("\n\nmetin.txt uzerinde direkt olarak yalnizca huffman kodlamasi uygulanacaktir.\nLz77 ve huffman icin deflate sikistirmasini kullaniniz.\n");
                printf("Dikkat!! - Buyuk dosyalar uzerinde huffman kodlamasi gerceklestirmek uzun islem sureleri alacaktir.\nLutfen kucuk dosyalar ile deneyiniz!\n");
                printf("Deflate tipi huffman kodlarinin kullanilmasi daha iyi ve hizli sikistirma sonuclari verecektir ilk secenegi tercih ediniz.\n");
                printf("1 - Huffman agaci olustur ve kodlari standartlastir(deflate tipi).Standart kodlar ile dosyayi sikistir.(Varsayilan)\n");
                printf("2 - Huffman agaci ve kodlari olustur. Kodlar ile dosyayi sikistir.\n");
                //printf("3 - Her iki kodlamayi da calistir.\n");
                printf("Gerceklestirmek istediginiz islemi giriniz:");
                scanf("%d",&huffmanislem);




                //Her karakter için bir frekans deðeri
                unsigned long frekanslar[255];
                //Dizinin tüm elemanalrýný sýfýrladýk.
                memset(&frekanslar[0], 0, sizeof(frekanslar));

                //unsigned char * metin = karakterDosyaOku("metin.txt");
                unsigned char * metin = sikistirilacakMetin;

                            //Metindeki karakterlerini sayalým
                unsigned char * karakter;
                for(karakter = &metin[0]; *karakter != NULL; karakter++){
                    //Ascii kodunda karsilik geldigi yerde frekansýný arttiriyoruz.
                    //printf("%d",*karakter);
                    frekanslar[(int)*karakter]++;
                }

                /*for(int i = 0; i < 255; i++){
                    printf("%d \n",frekanslar[i]);
                }*/

                HuffmanDizisi * huffmanDizisi =huffmanDizisiOlustur();

                    int i;
                    for(i = 0; i < 255; i++){
                        if(frekanslar[i] > 0) // O Karakter mevcutsa
                            huffmanDizisineEkle(huffmanDizisi, HuffmanAgaciOlustur(i, frekanslar[i]));
                    }

                while(huffmanDizisi->boyut > 1){
                    huffmanDizisiniSirala(huffmanDizisi);
                    HuffmanAgaci * agac1 = huffmanDizisindenCikar(huffmanDizisi);
                    HuffmanAgaci * agac2 = huffmanDizisindenCikar(huffmanDizisi);
                    HuffmanAgaci * agac3 = calloc(1, sizeof(HuffmanAgaci)); //Malloctan farký eleman adeti de alýyor.
                    agac3->sol = agac1;
                    agac3->sag = agac2;
                    agac3->frekans = agac1->frekans + agac2->frekans;
                    huffmanDizisineEkle(huffmanDizisi,agac3);
                }

                unsigned char * buffer = malloc(256);
                //huffmanAgaciYazdir(huffmanDizisi->deger[0],buffer,0);

                if(huffmanislem == 2){
                        sayacBaslat = clock();
                    printf("\nBilgi - Huffman Kodlari Olusturuluyor...\n");
                    //Burda ilk kodlarla sifrelemeyi yapalim
                    //printf("afs");
                    char * huffmanSikistirmasi1 = malloc(strlen(metin) * 100);
                    memset(huffmanSikistirmasi1, 0, strlen(metin) * 100);
                    unsigned char * ciktiKod = malloc(256);

                    //printf("Kodlar olusturuluyor!");
                    char kodlar[256][100];

                     for(int i = 0; i < 256; i++){
                            huffmanKoduBul(huffmanDizisi->deger[0], buffer, 0, (char)i, ciktiKod);
                            strcpy(kodlar[i], ciktiKod);
                    }

                    //printf("Kodlar olustu!");

                     printf("Bilgi - Metin Huffman Kodlamasi Haline Getiriliyor. Lutfen Bekleyiniz...\n");

                     char * yerIsaretcisi = huffmanSikistirmasi1;
                    for(int i = 0; i < strlen(metin); i++){
                        //huffmanKoduBul(huffmanDizisi->deger[0], buffer, 0, metin[i], ciktiKod);
                        //printf("\n%s\n",kod);
                        //printf(".");
                        //strcat(huffmanSikistirmasi1,ciktiKod);
                        memcpy(yerIsaretcisi, kodlar[metin[i]] , sizeof(char) * strlen(kodlar[ metin[i]] ));
                        yerIsaretcisi += strlen(kodlar[metin[i] ]);
                        //strcat(huffmanSikistirmasi1, kodlar[metin[i]]);
                    }
                    strcat(huffmanSikistirmasi1,"\0");
                                          /*
                        char kodlar[256][100];
                        //tüm karakterlerin kodlarini bu diziye aticaz.

                        for(int i = 0; i < 256; i++){
                            huffmanKoduBul(huffmanDizisi->deger[0], buffer, 0, (char)i, ciktiKod);
                            strcpy(kodlar[i], ciktiKod);
                        }

                        //ZAMAN ALAN KISIM
                        for(int i = 0; i < strlen(metin); i++){
                            //huffmanKoduBul(huffmanDizisi->deger[0], buffer, 0, metin[i], ciktiKod);
                            //printf("\n%s\n",kod);
                            strcat(huffmanSikistirmasi1, kodlar[metin[i]] );
                            //strcat(huffmanSikistirmasi1,ciktiKod);
                        }
                        */


                    huffmanSikistirmasi1 = realloc(huffmanSikistirmasi1, strlen(huffmanSikistirmasi1) * sizeof(char));
                    //printf("%d", strlen(huffmanSikistirmasi1));

                    //printf("%s", huffmanSikistirmasi1);

                    char * huffmanSikistirma1YaziCikti = malloc(strlen(huffmanSikistirmasi1) * sizeof(char) * 2);
                    memset(huffmanSikistirma1YaziCikti, 0, strlen(huffmanSikistirmasi1) * sizeof(char) * 2);
                    printf("Bilgi - Huffman Kodlamasi Bit Duzeyinde Ciktiya Isleniyor. Lutfen Bekleyiniz...");
                    binaryStringiBitYap(huffmanSikistirmasi1, huffmanSikistirma1YaziCikti);

                     huffmanSikistirma1YaziCikti = realloc(huffmanSikistirma1YaziCikti, sizeof(char) * strlen(huffmanSikistirma1YaziCikti));
                    //printf("%s", huffmanSikistirma1YaziCikti);
                    //char testkarakter = strtol(huffmanSikistirmasi1,0,2);
                    //printf("--%c", testkarakter);

                    printf("\nBilgi - Cikti Dosyalari Olusturuluyor...\n");
                    //FILE * huffmanSikistirmaAnlamliCikti;
                    //huffmanSikistirmaAnlamliCikti = fopen("metin_huffman_2_okunabilir_cikti.txt","wb");
                    //fwrite(huffmanSikistirmasi1, sizeof(char) * strlen(huffmanSikistirmasi1), 1, huffmanSikistirmaAnlamliCikti);
                    //fclose(huffmanSikistirmaAnlamliCikti);

                    FILE * huffmanSikistirma1Cikti;
                    huffmanSikistirma1Cikti = fopen("metin_huffman_2_sikistirma.txt","wb");
                    //printf("--%d--",strlen(huffmanSikistirma1YaziCikti));
                    fwrite(huffmanSikistirma1YaziCikti,sizeof(char) * strlen(huffmanSikistirma1YaziCikti),1,huffmanSikistirma1Cikti);
                    fclose(huffmanSikistirma1Cikti);
                    sayacBitir = clock();
                    gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                    printf("\nHuffman Sikistirma Sonuclari:\n");
                    printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu, sizeof(char) * strlen(huffmanSikistirma1YaziCikti));
                    printf("Sikistirma Orani: %lf\n", sizeof(char) * strlen(huffmanSikistirma1YaziCikti) / (float)sikistirilacakMetinBoyutu);
                    printf("Gecen zaman : %lf \n", gecenIslemciZamani);

                }

                if(huffmanislem == 1){
                        sayacBaslat = clock();
                        printf("\nBilgi - Standart Huffman Kodlari Olusturuluyor...\n");
                        //printf("standart kodlarin olusturulmasina baslandi.\n");
                        memset(agac,0,sizeof(agac));
                        memset(b1_sayac,0,sizeof(b1_sayac));
                        memset(sonrakiKod,0,sizeof(sonrakiKod));

                        standartKodlariGetir(huffmanDizisindenCikar(huffmanDizisi), 0);
                        for(i = 0; i < 256; i++){
                            b1_sayac[agac[i].uzunluk]++;
                        }

                        int code = 0;
                        b1_sayac[0] = 0;

                        for(i = 1; i < 16; i++){
                            code = (code + b1_sayac[i-1]) << 1;
                            sonrakiKod[i] = code;
                        }

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                agac[i].kod = sonrakiKod[uzunluk];
                                sonrakiKod[uzunluk]++;
                            }
                        }

                          char standartKodlar[256][100];

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                            }
                        }

                        //printf("standart kodlar olustu\n");
                        char * huffmanSikistirmasi2 = malloc(strlen(metin) * 16);

                        //printf("asfsa");
                        memset(huffmanSikistirmasi2, 0, strlen(metin) * 16);
                        //unsigned char * ciktiKod = malloc(256);
                        printf("Bilgi - Metin Huffman Standart Kodlamasi Haline Getiriliyor. Lutfen Bekleyiniz...\n");
                        //unsigned long sayac = 0;
                        //printf("binary string olusturulmasina baslanildi\n");
                        char * yerIsaretcisi = huffmanSikistirmasi2;
                        for(int i = 0; i < strlen(metin); i++){
                            //huffmanKoduBul(huffmanDizisi->deger[0], buffer, 0, metin[i], ciktiKod);
                            //printf("\n%s\n",kod);

                            //int karakter = (int)metin[i];
                            //int uzunluk = agac[karakter].uzunluk;
                            //if(uzunluk){
                                //printf("%c: %s\n", karakter, koduBinaryYap(agac[karakter]));
                                //sayac++;
                                //strcat(huffmanSikistirmasi2, standartKodlar[metin[i]]);
                                //strcpy(yerIsaretcisi, standartKodlar[metin[i]]);
                                memcpy(yerIsaretcisi,  standartKodlar[metin[i]], sizeof(char) * strlen(standartKodlar[metin[i]]));
                                yerIsaretcisi += strlen(standartKodlar[metin[i]]);
                            //}

                            //if(metin[i] == NULL || metin[i] == '\0'){
                              //  break;
                            //}
                        }
                        //printf("Total metin karakteri : %d", sayac);
                        //HuffmanSikistirmasi2 ye karaktere karsilik düsen kodu eklememiz lazim direkt bir dizi olursa daha hizli olur. her seferinde aramayiz.





                        //printf("binary string olustu\n");
                        huffmanSikistirmasi2 = realloc(huffmanSikistirmasi2, strlen(huffmanSikistirmasi2) * sizeof(char));
                        //printf("%d ", strlen(huffmanSikistirmasi2));
                        //printf("%s", huffmanSikistirmasi2);

                        char * huffmanSikistirmasi2YaziCikti = malloc(strlen(huffmanSikistirmasi2) * sizeof(char) * 2);
                        memset(huffmanSikistirmasi2YaziCikti, 0, strlen(huffmanSikistirmasi2) * sizeof(char) * 2);
                        printf("Bilgi - Standart Huffman Kodlamasi Bit Duzeyinde Ciktiya Isleniyor. Lutfen Bekleyiniz...");
                        //printf("binary string bite donusturuluyor\n");
                        binaryStringiBitYap(huffmanSikistirmasi2, huffmanSikistirmasi2YaziCikti);
                        //printf("binary string bite donustu\n");
                        //printf("%s", huffmanSikistirmasi2YaziCikti);

                        FILE * huffmanSikistirmaAnlamliCikti2;
                        huffmanSikistirmaAnlamliCikti2 = fopen("metin_huffman_1_okunabilir_cikti.txt","wb");
                        //Burada karakter kodlarini dosyaya yazabiliriz.
                        fprintf(huffmanSikistirmaAnlamliCikti2,"%s\n","KOD TABLOSU");
                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                fprintf(huffmanSikistirmaAnlamliCikti2,"< %c: %s >",i,standartKodlar[i]);
                                //strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                            }
                        }
                        fprintf(huffmanSikistirmaAnlamliCikti2,"\n%s\n","KODLANMIS METIN");
                        fwrite(huffmanSikistirmasi2, sizeof(char) * strlen(huffmanSikistirmasi2), 1, huffmanSikistirmaAnlamliCikti2);
                        fclose(huffmanSikistirmaAnlamliCikti2);

                        FILE * huffmanSikistirma2Cikti = fopen("metin_huffman_1_sikistirma.txt","wb");
                        fwrite(huffmanSikistirmasi2YaziCikti, sizeof(char) * strlen(huffmanSikistirmasi2YaziCikti),1,huffmanSikistirma2Cikti);
                        fclose(huffmanSikistirma2Cikti);


                        sayacBitir = clock();
                        gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                        printf("\n\nStandart Huffman Sikistirma Sonuclari:\n");
                        printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu, sizeof(char) * strlen(huffmanSikistirmasi2YaziCikti));
                        printf("Sikistirma Orani: %lf\n", (sizeof(char) * strlen(huffmanSikistirmasi2YaziCikti)) / (float)sikistirilacakMetinBoyutu);
                        printf("Gecen zaman : %lf \n", gecenIslemciZamani);
                }

                if(huffmanislem < 1 || huffmanislem > 2){
                    printf("\nHata - Gecersiz islem tekrar deneyiniz!\n");
                }
            break;

            case 3:
                printf("\n\nDeflate sikistirmada 15 bit(32K) arama tamponu kullanilmaktadir ve standartlastirilmis kodlarla huffman kodlamasi yapilmaktadir.\n");
                printf("2. ve 3. secenekler kodda mevcut fakat verimsizlik ve kararsizliktan oturu devre disidirlar.\n");
                printf("1 - Tek Blok - Mod 2(Statik Huffman) - 15 Bit(32K) Arama Tamponu - Deflate(Varsayilan)\n");
                printf("(Devre Disi)2 - Tek Blok - Mod 2(Statik Huffman) - 12 Bit Arama Tamponu - Deflate.(Verimsiz)\n");
                printf("(Devre Disi)3 - Coklu Sabit Blok - Mod 2(Statik Huffman) - 15 Bit(32K) Arama Tamponu - Deflate(Kararsiz, Hatali)\n");
                //printf("4 - Her iki kodlamayi da calistir.\n");
                printf("Gerceklestirmek istediginiz islemi giriniz:");
                scanf("%d",&deflateislem);

                if(deflateislem == 1){
                    sayacBaslat = clock();
                    printf("\nBilgi - Deflate Blogu Olusturuluyor...\n");

                    printf("Bilgi - Deflate Blok Baslik Bilgisi Giriliyor...\n");
                    //!Baslik bilgisi tek blok oldugu icin en son giriliyor.
                    printf("Bilgi - Deflate Birinci Blok Olusturuldu...\n");
                    printf("Bilgi - Lzss ile Sikistirilma Yapiliyor. Lutfen Bekleyiniz...\n");
                    //Tekli Blok deflate
                    int defSikistirmaBirimi24Sayisi;
                    SikistirmaBirimi24 * defSikistirilmisMetin;
                    defSikistirilmisMetin = lz77Sikistirma24(sikistirilacakMetin, sikistirilacakMetinBoyutu, &defSikistirmaBirimi24Sayisi, 15, 8);
                    //printf("Lz77 yapiliyor.\n");



                    //printf("\n\nDosya Boyutu: %d Sikistirma Boyutu : %d ", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi24) * defSikistirmaBirimi24Sayisi);

                    //unsigned char * lz77StringGosterimi = malloc(defSikistirmaBirimi24Sayisi * sizeof(SikistirmaBirimi24));
                    //memcpy(lz77StringGosterimi, defSikistirilmisMetin, defSikistirmaBirimi24Sayisi * sizeof(SikistirmaBirimi24) );
                    //int boyut;
                    //unsigned char * lz77StringGosterimi = dosyaYukle("metin_lz77-24_Sikistirma.txt", &boyut);

                    //!! Burda bellek ayrimina dikkat et
                    unsigned char * lz77StringGosterimi = malloc(defSikistirmaBirimi24Sayisi * 12);
                    memset(lz77StringGosterimi, 0, defSikistirmaBirimi24Sayisi * 12);

                    for(int i = 0; i < defSikistirmaBirimi24Sayisi; i++){
                        //int uzaklik = defSikistirilmisMetin[i].uzaklik;
                        unsigned char uzaklikIlk8bit = defSikistirilmisMetin[i].uzaklik >> 8;
                        unsigned char uzaklikSon8bit = defSikistirilmisMetin[i].uzaklik & 0xff;
                        unsigned char tekrar = defSikistirilmisMetin[i].tekrar;
                        unsigned char karakter = defSikistirilmisMetin[i].karakter;
                        //printf("asfjaskfha");
                        unsigned char birim[100];
                        if(defSikistirilmisMetin[i].uzaklik == 0 && defSikistirilmisMetin[i].tekrar == 0){
                            sprintf(birim,"%c%c",0,karakter);
                        }else{
                            sprintf(birim,"%c%c%c%c",uzaklikIlk8bit,uzaklikSon8bit,tekrar,karakter);
                        }

                        strcat(lz77StringGosterimi,birim);
                    }
                    strcat(lz77StringGosterimi,"\0");
                    lz77StringGosterimi = realloc(lz77StringGosterimi, strlen(lz77StringGosterimi) * sizeof(unsigned char));


                    //Huffman'a direkt olarak lz77nin çıktısını sokarsak?

                    unsigned long defFrekanslar[255];
                    memset(&defFrekanslar[0], 0 , sizeof(defFrekanslar));

                    //printf("%s",lz77StringGosterimi);
                    //lz77StringGosterimi kaynak olacak
                    //printf("hey!");

                    for(karakter = &lz77StringGosterimi[0]; *karakter != NULL; karakter++){
                        defFrekanslar[(int)*karakter]++;
                    }
                    //printf("hey 2!");
                    HuffmanDizisi * defHuffmanDizisi = huffmanDizisiOlustur();
                    int i;
                    for(i = 0; i < 255; i++){
                        if(defFrekanslar[i] > 0){
                            huffmanDizisineEkle(defHuffmanDizisi, HuffmanAgaciOlustur(i, defFrekanslar[i]));
                        }
                    }
                    //printf("hey 3!");
                     while(defHuffmanDizisi->boyut > 1){
                        huffmanDizisiniSirala(defHuffmanDizisi);
                        HuffmanAgaci * agac1 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac2 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac3 = calloc(1, sizeof(HuffmanAgaci)); //Malloctan farký eleman adeti de alýyor.
                        agac3->sol = agac1;
                        agac3->sag = agac2;
                        agac3->frekans = agac1->frekans + agac2->frekans;
                        huffmanDizisineEkle(defHuffmanDizisi,agac3);
                    }

                    unsigned char * buffer = malloc(256);
                    //huffmanAgaciYazdir(defHuffmanDizisi->deger[0],buffer,0);

                    memset(agac,0,sizeof(agac));
                    memset(b1_sayac,0,sizeof(b1_sayac));
                    memset(sonrakiKod,0,sizeof(sonrakiKod));

                    standartKodlariGetir(huffmanDizisindenCikar(defHuffmanDizisi), 0);

                        for(i = 0; i < 256; i++){
                            b1_sayac[agac[i].uzunluk]++;
                        }

                        int code = 0;
                        b1_sayac[0] = 0;

                        for(i = 1; i < 16; i++){
                            code = (code + b1_sayac[i-1]) << 1;
                            sonrakiKod[i] = code;
                        }

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                agac[i].kod = sonrakiKod[uzunluk];
                                sonrakiKod[uzunluk]++;
                            }
                        }

                        char standartKodlar[256][100];

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                            }
                        }

                    char * deflateSikistirma1 = malloc(strlen(lz77StringGosterimi) * 16);
                    memset(deflateSikistirma1, 0 , strlen(lz77StringGosterimi) * 16);

                    char * yerIsaretcisi = deflateSikistirma1;

                    printf("Bilgi - Huffman Kodlamasi Yapiliyor. Lutfen Bekleyiniz...\n");
                    for(int i = 0; i < strlen(lz77StringGosterimi); i++){
                        //int karakter = (int)lz77StringGosterimi[i];
                        //int uzunluk = agac[karakter].uzunluk;
                        //if(uzunluk){
                            //printf("%c: %s\n", karakter, koduBinaryYap(agac[karakter]));
                            //strcat(deflateSikistirma1, koduBinaryYap(agac[karakter]));
                            memcpy(yerIsaretcisi, standartKodlar[ lz77StringGosterimi[i] ], sizeof(char) * strlen( standartKodlar[ lz77StringGosterimi[i] ] )   );
                            yerIsaretcisi += strlen(standartKodlar[ lz77StringGosterimi[i] ]  );
                            //strcat(deflateSikistirma1, standartKodlar[karakter]);
                        //}
                    }

                    deflateSikistirma1 = realloc(deflateSikistirma1, strlen(deflateSikistirma1) * sizeof(char));

                    char * deflateSikistirma1YaziCikti = malloc(strlen(deflateSikistirma1)* sizeof(char) * 2);
                    memset(deflateSikistirma1YaziCikti, 0 , strlen(deflateSikistirma1) * sizeof(char) * 2);
                    printf("Bilgi - Deflate Ciktisi Olusturuluyor.\n");
                    //printf("heyy");
                    binaryStringiBitYap(deflateSikistirma1, deflateSikistirma1YaziCikti);


                    //String gösterim artık elimizde bunu huffman ile kodlucaz
                    FILE * deflateSikistirma1Cikti = fopen("metin_deflate_sikistirma_1.txt","wb");
                    char baslikBilgisi = DEFLATE_BLOK_SON_MOD_2;
                    fputc(baslikBilgisi, deflateSikistirma1Cikti);

                    for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                //strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                                //fprintf(deflateSikistirma1Cikti,"%c%s",standartKodlar[i]);
                                //char karakter = i;
                                //fwrite(karakter, sizeof(char), 1, deflateSikistirma1Cikti);
                                fputc(i, deflateSikistirma1Cikti);
                                fwrite(standartKodlar[i],strlen(standartKodlar[i])*sizeof(char),1,deflateSikistirma1Cikti);
                            }
                        }

                    fwrite(deflateSikistirma1YaziCikti, sizeof(char) * strlen(deflateSikistirma1YaziCikti), 1, deflateSikistirma1Cikti);
                    fclose(deflateSikistirma1Cikti);

                    int sikismisBoyut;
                    FILE * defSonuc = fopen("metin_deflate_sikistirma_1.txt", "rb");
                    dosyaYukle(defSonuc,&sikismisBoyut);


                    sayacBitir = clock();
                    gecenIslemciZamani = ((double) (sayacBitir - sayacBaslat)) / CLOCKS_PER_SEC;
                    printf("\n\Deflate Sonuclari:\n");
                    printf("Dosyanin Gercek Boyutu: %d\nSikistirilmis Boyutu : %d\n", sikistirilacakMetinBoyutu, sikismisBoyut);
                    printf("Sikistirma Orani: %lf\n", sikismisBoyut / (float)sikistirilacakMetinBoyutu);
                    printf("Gecen zaman : %lf \n", gecenIslemciZamani);



                    //printf("basariyla tamamlandi!");
                }

                /*
                if(deflateislem == 2 ||deflateislem == 4){
                    int defSikistirmaBirimi16Sayisi;
                    SikistirmaBirimi16 * defSikistirilmisMetin;
                    defSikistirilmisMetin = lz77Sikistirma16(sikistirilacakMetin, sikistirilacakMetinBoyutu, &defSikistirmaBirimi16Sayisi, 12, 4);
                    printf("Lz77 yapiliyor.\n");
                    printf("\n\nDosya Boyutu: %d Sikistirma Boyutu : %d ", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi16) * defSikistirmaBirimi16Sayisi);

                    //!! Burda bellek ayrimina dikkat et
                    unsigned char * lz77StringGosterimi = malloc(defSikistirmaBirimi16Sayisi * 12);
                    memset(lz77StringGosterimi, 0, defSikistirmaBirimi16Sayisi * 12);

                    for(int i = 0; i < defSikistirmaBirimi16Sayisi; i++){
                        int uzaklik = defSikistirilmisMetin[i].uzaklikTekrar >> 4; //12bit
                        unsigned char tekrar = defSikistirilmisMetin[i].uzaklikTekrar & (((1 << (4)) - 1));
                        //unsigned char uzaklikTekrarIlk8Bit =
                        //unsigned char uzaklikTekrarSon8Bit =
                        unsigned char karakter = defSikistirilmisMetin[i].karakter;
                        //printf("asfjaskfha");
                        unsigned char birim[100];
                        sprintf(birim,"%d%c%c",uzaklik,tekrar,karakter);
                        strcat(lz77StringGosterimi,birim);
                    }
                    strcat(lz77StringGosterimi,"\0");
                    lz77StringGosterimi = realloc(lz77StringGosterimi, strlen(lz77StringGosterimi) * sizeof(unsigned char));

                    unsigned long defFrekanslar[255];
                    memset(&defFrekanslar[0], 0 , sizeof(defFrekanslar));

                    //printf("%s",lz77StringGosterimi);
                    //lz77StringGosterimi kaynak olacak
                    printf("hey!");

                    for(karakter = &lz77StringGosterimi[0]; *karakter != NULL; karakter++){
                        defFrekanslar[(int)*karakter]++;
                    }
                    printf("hey 2!");
                    HuffmanDizisi * defHuffmanDizisi = huffmanDizisiOlustur();
                    int i;
                    for(i = 0; i < 255; i++){
                        if(defFrekanslar[i] > 0){
                            huffmanDizisineEkle(defHuffmanDizisi, HuffmanAgaciOlustur(i, defFrekanslar[i]));
                        }
                    }
                    printf("hey 3!");
                     while(defHuffmanDizisi->boyut > 1){
                        huffmanDizisiniSirala(defHuffmanDizisi);
                        HuffmanAgaci * agac1 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac2 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac3 = calloc(1, sizeof(HuffmanAgaci)); //Malloctan farký eleman adeti de alýyor.
                        agac3->sol = agac1;
                        agac3->sag = agac2;
                        agac3->frekans = agac1->frekans + agac2->frekans;
                        huffmanDizisineEkle(defHuffmanDizisi,agac3);
                    }

                    unsigned char * buffer = malloc(256);
                    //huffmanAgaciYazdir(defHuffmanDizisi->deger[0],buffer,0);

                    memset(agac,0,sizeof(agac));
                    memset(b1_sayac,0,sizeof(b1_sayac));
                    memset(sonrakiKod,0,sizeof(sonrakiKod));

                    standartKodlariGetir(huffmanDizisindenCikar(defHuffmanDizisi), 0);

                        for(i = 0; i < 256; i++){
                            b1_sayac[agac[i].uzunluk]++;
                        }

                        int code = 0;
                        b1_sayac[0] = 0;

                        for(i = 1; i < 16; i++){
                            code = (code + b1_sayac[i-1]) << 1;
                            sonrakiKod[i] = code;
                        }

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                agac[i].kod = sonrakiKod[uzunluk];
                                sonrakiKod[uzunluk]++;
                            }
                        }

                        char standartKodlar[256][100];

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                            }
                        }

                    char * deflateSikistirma1 = malloc(strlen(lz77StringGosterimi) * 16);
                    memset(deflateSikistirma1, 0 , strlen(lz77StringGosterimi) * 16);

                    for(int i = 0; i < strlen(lz77StringGosterimi); i++){
                        int karakter = (int)lz77StringGosterimi[i];
                        int uzunluk = agac[karakter].uzunluk;
                        if(uzunluk){
                            //printf("%c: %s\n", karakter, koduBinaryYap(agac[karakter]));
                            //strcat(deflateSikistirma1, koduBinaryYap(agac[karakter]));
                            strcat(deflateSikistirma1, standartKodlar[karakter]);
                        }
                    }

                    deflateSikistirma1 = realloc(deflateSikistirma1, strlen(deflateSikistirma1) * sizeof(char));

                    char * deflateSikistirma1YaziCikti = malloc(strlen(deflateSikistirma1)* sizeof(char) * 2);
                    memset(deflateSikistirma1YaziCikti, 0 , strlen(deflateSikistirma1) * sizeof(char) * 2);

                    printf("heyy");
                    binaryStringiBitYap(deflateSikistirma1, deflateSikistirma1YaziCikti);
                    //String gösterim artık elimizde bunu huffman ile kodlucaz
                    FILE * deflateSikistirma1Cikti = fopen("deflate_sikistirma_2.txt","wb");
                    fwrite(deflateSikistirma1YaziCikti, sizeof(char) * strlen(deflateSikistirma1YaziCikti), 1, deflateSikistirma1Cikti);
                    fclose(deflateSikistirma1Cikti);

                    printf("basariyla tamamlandi!");
                }*/
                    /*
                if(deflateislem == 3 || deflateislem == 4){
                    int defSikistirmaBirimi16Sayisi;
                    SikistirmaBirimi16 * defSikistirilmisMetin;
                    defSikistirilmisMetin = lz77Sikistirma16(sikistirilacakMetin, sikistirilacakMetinBoyutu, &defSikistirmaBirimi16Sayisi, 12, 4);
                    printf("Lz77 yapiliyor.\n");
                    printf("\n\nDosya Boyutu: %d Sikistirma Boyutu : %d ", sikistirilacakMetinBoyutu,sizeof(SikistirmaBirimi16) * defSikistirmaBirimi16Sayisi);

                    //!! Burda bellek ayrimina dikkat et
                    unsigned char * lz77StringGosterimi = malloc(defSikistirmaBirimi16Sayisi * 12);
                    memset(lz77StringGosterimi, 0, defSikistirmaBirimi16Sayisi * 12);

                    for(int i = 0; i < defSikistirmaBirimi16Sayisi; i++){
                        int uzaklik = defSikistirilmisMetin[i].uzaklikTekrar >> 4;
                        int tekrar = defSikistirilmisMetin[i].uzaklikTekrar & (((1 << (4)) - 1));
                        unsigned char karakter = defSikistirilmisMetin[i].karakter;
                        //printf("asfjaskfha");
                        unsigned char birim[100];
                        sprintf(birim,"%d%d%c",uzaklik,tekrar,karakter);
                        strcat(lz77StringGosterimi,birim);
                    }
                    strcat(lz77StringGosterimi,"\0");
                    lz77StringGosterimi = realloc(lz77StringGosterimi, strlen(lz77StringGosterimi) * sizeof(unsigned char));

                    //Bir blok stringi oluşturcaz
                    int blokBuyuklugu = 64;
                    char blokString[blokBuyuklugu];
                    char * blokIsaretcisi;

                    FILE * deflateSikistirma1Cikti = fopen("deflate_sikistirma_3.txt","wb");
                    for(blokIsaretcisi = &lz77StringGosterimi[0]; blokIsaretcisi + blokBuyuklugu <= lz77StringGosterimi+strlen(lz77StringGosterimi); blokIsaretcisi+=blokBuyuklugu){
                        memcpy(blokString, blokIsaretcisi, blokBuyuklugu);
                        //Burdan lz77 blok blok geliyor her bloğu ayrı ayrı huffmana sokup çıktıyı vercem.
                    unsigned long defFrekanslar[255];
                    memset(&defFrekanslar[0], 0 , sizeof(defFrekanslar));

                    //printf("%s",lz77StringGosterimi);
                    //lz77StringGosterimi kaynak olacak


                    for(karakter = &blokString[0]; karakter < &blokString[blokBuyuklugu]; karakter++){
                        defFrekanslar[(int)*karakter]++;
                    }

                    printf("hey 2!");
                    HuffmanDizisi * defHuffmanDizisi = huffmanDizisiOlustur();
                    int i;
                    for(i = 0; i < 255; i++){
                        if(defFrekanslar[i] > 0){
                            huffmanDizisineEkle(defHuffmanDizisi, HuffmanAgaciOlustur(i, defFrekanslar[i]));
                        }
                    }
                    printf("hey 3!");
                     while(defHuffmanDizisi->boyut > 1){
                        huffmanDizisiniSirala(defHuffmanDizisi);
                        HuffmanAgaci * agac1 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac2 = huffmanDizisindenCikar(defHuffmanDizisi);
                        HuffmanAgaci * agac3 = calloc(1, sizeof(HuffmanAgaci)); //Malloctan farký eleman adeti de alýyor.
                        agac3->sol = agac1;
                        agac3->sag = agac2;
                        agac3->frekans = agac1->frekans + agac2->frekans;
                        huffmanDizisineEkle(defHuffmanDizisi,agac3);
                    }

                    unsigned char * buffer = malloc(256);
                    //huffmanAgaciYazdir(defHuffmanDizisi->deger[0],buffer,0);

                    memset(agac,0,sizeof(agac));
                    memset(b1_sayac,0,sizeof(b1_sayac));
                    memset(sonrakiKod,0,sizeof(sonrakiKod));

                    standartKodlariGetir(huffmanDizisindenCikar(defHuffmanDizisi), 0);

                        for(i = 0; i < 256; i++){
                            b1_sayac[agac[i].uzunluk]++;
                        }

                        int code = 0;
                        b1_sayac[0] = 0;

                        for(i = 1; i < 16; i++){
                            code = (code + b1_sayac[i-1]) << 1;
                            sonrakiKod[i] = code;
                        }

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                agac[i].kod = sonrakiKod[uzunluk];
                                sonrakiKod[uzunluk]++;
                            }
                        }

                        char standartKodlar[256][100];

                        for(i = 0; i < 256; i++){
                            int uzunluk = agac[i].uzunluk;
                            if(uzunluk){
                                //printf("%c: %s\n", i, koduBinaryYap(agac[i]));
                                strcpy(standartKodlar[i], koduBinaryYap(agac[i]));
                            }
                        }

                    char * deflateSikistirma1 = malloc(strlen(blokString) * 16);
                    memset(deflateSikistirma1, 0 , strlen(blokString) * 16);
                    printf("asf");
                    char * yerIsaretcisi = deflateSikistirma1;
                    for(int i = 0; i < strlen(blokString); i++){
                        //int karakter = (int)lz77StringGosterimi[i];
                        //int uzunluk = agac[karakter].uzunluk;
                        //if(uzunluk){
                            //printf("%c: %s\n", karakter, koduBinaryYap(agac[karakter]));
                            //strcat(deflateSikistirma1, koduBinaryYap(agac[karakter]));
                            //strcat(deflateSikistirma1, standartKodlar[karakter]);
                            memcpy( yerIsaretcisi, standartKodlar[blokString[i]], sizeof(char) * strlen( standartKodlar[blokString[i]] ));
                            yerIsaretcisi += strlen(standartKodlar[blokString[i]]);
                        //}
                    }

                    deflateSikistirma1 = realloc(deflateSikistirma1, strlen(deflateSikistirma1) * sizeof(char));
                    printf("testpoint");
                    char * deflateSikistirma1YaziCikti = malloc(strlen(deflateSikistirma1)* sizeof(char) * 4);
                    printf("testpoint");
                    memset(deflateSikistirma1YaziCikti, 0 , strlen(deflateSikistirma1) * sizeof(char) * 4);
                    printf("assxxcsf");
                    printf("heyy");
                    binaryStringiBitYap(deflateSikistirma1, deflateSikistirma1YaziCikti);
                    //String gösterim artık elimizde bunu huffman ile kodlucaz

                    fwrite(deflateSikistirma1YaziCikti, sizeof(char) * strlen(deflateSikistirma1YaziCikti), 1, deflateSikistirma1Cikti);


                        //printf("%s", blokString);
                    }


                    fclose(deflateSikistirma1Cikti);

                    //LZ77 SONU

                }*/

                if(deflateislem != 1){
                    printf("\nHata - Gecersiz islem tekrar deneyiniz!\n");
                }
            break;

            case 4:
                return 0;
            break;

            default:
                printf("\nHata - Gecersiz islem tekrar deneyiniz!\n");
            break;
        }
    }

    printf("\n\n");
    printf("Cikmak icin entera basiniz!\n");
    getchar();
    return 0;
}
