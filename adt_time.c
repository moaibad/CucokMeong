/* File : jam.c */

/* Body ADT Jam */

#include "adt_time.h"

/* -----------konstruktor Jam--------- */

Jam MakeJam(int H, int M, int S)
/* Membentuk Jam dari H, M, S yg valid */
{ 
  /* Kamus Lokal */
   Jam J1;
  /* Algoritma */
   Hour(J1) = H;
   Minute(J1) = M;
   Second(J1) = S;
   return J1;
}

/*------------validator Jam------------*/

boolean IsJValid(int H, int M, int S)
/* Mengirim true jika H,M,S dapat membentuk Jam yang valid */

{
  /* Kamus Lokal */
  /* Algoritma */
   return ((H >= 0 && H <= 23) && (M >= 0 && M <= 59) && (S >= 0 && S <= 59));
}

/*------------Baca & Tulis jam-----------*/

void BacaJam(Jam *J)
/* I.S.   : J tak terdefinisi */
/* F.S.   : J terdefinisi dan merupakan jam valid */
/* Proses : mengulang baca komponen H, M, S sehingga membentuk J
             yang valid */
{
  /* Kamus Lokal */ 
   int H, M, S;
  /* Algoritma */
   do {
       printf("\n\t\t\t\tEnter Hour \t: ");scanf("%d",&H);
       printf("\t\t\t\tEnter Minute \t: ");scanf("%d",&M);
      } while(!IsJValid(H,M,S));
   *J = MakeJam(H,M,S);
}

void TulisJam(Jam J)
/* I.S. : J sembarang*/
/* F.S. : J ditulis ke layar dengan format HH:MM:SS */
/* Proses : Menulis ke layar */

{ 
  /* Kamus lokal */
  /* Algoritma */
   printf("%d:%d:%d",Hour(J),Minute(J),Second(J));
}

int JamToDetik(Jam J)
/* Konversi Jam menjadi detik */

{ 
  /* Kamus Lokal */
  /* Algoritma */
   return(3600 *Hour(J) + 60 *Minute(J) + Second(J));
}

Jam DetikToJam(int N)
/* Konversi detik ke Jam */

{ 
  /* Kamus Lokal */
   int sisa;
   Jam JOut;
  /* Algoritma */
   Hour(JOut) = N / 3600;
   sisa = N % 3600;
   Minute(JOut) = sisa / 60;
   Second(JOut) = sisa % 60;
   return JOut;
}
