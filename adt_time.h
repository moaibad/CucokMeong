/* File : jam.h */

/* spesifikasi ADT Jam */
#ifndef adt_time_H
#define adt_time_H
#include "boolean.h"
#include "stdio.h"

/* Notasi Akses */
#define Hour(J) (J).HH
#define Minute(J) (J).MM
#define Second(J) (J).SS
typedef struct 
{
 int HH; /* 0..23 */
 int MM; /* 0..59 */
 int SS; /* 0..59 */
} Jam;

/***** Konstruktor ************/
Jam MakeJam(int H, int M, int S);
/* Membentuk Jam dari H, M, S yg valid */

/*------------validator jam------------*/
boolean IsJValid(int H, int M, int S);
/* Mengirim true jika H,M,S dapat membentuk Jam yang valid */

/*------------Baca & Tulis jam-----------*/

void BacaJam(Jam *J);
/* I.S. : J tak terdefinisi * /
/* F.S. : J terdefinisi dan merupakan jam valid */
/* Proses : mengulang baca komponen H,M,S sehingga membentuk J
yang valid */

void TulisJam(Jam J);
/* I.S. : J sembarang */
/* F.S. : J ditulis ke layar dengan format HH:MM:SS */
/* Proses : Menulis ke layar */

/*----------Konversi terhadap type jam----------*/

int JamToDetik(Jam J);
/* Konversi Jam menjadi detik */

Jam DetikToJam(int N);
/* Konversi detik ke Jam */
#endif
