/* File : jam.c */

/* Body ADT Jam */

#include "adt_time.h"


/* -----------konstruktor Jam--------- */

/*
Deskripsi 	: Membentuk Jam dari H, M, S yg valid
Author 		: Muhammad Zaki
*/
Jam MakeJam(int H, int M, int S)
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

/*
Deskripsi 	: Membentuk Jam dari input user
Author 		: Muhammad Zaki
*/
void BacaJam(Jam *J)
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


/*
Deskripsi 	: Konversi Jam menjadi menit
Author 		: Muhammad Zaki
*/
int JamToMenit(Jam J)
{ 
  /* Kamus Lokal */
  /* Algoritma */
   return(60 * Hour(J) + Minute(J));
}


