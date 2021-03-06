
/* Body ADT Jam */

#include "adt_time.h"
#include <time.h>


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

/*------------Baca & Tulis jam-----------*/

/*
Deskripsi 	: Membentuk Jam dari input user
Author 		: Muhammad Zaki
*/
void BacaJam(Jam *J)
{
	
	time_t seconds;
    struct tm *timeStruct;
    seconds = time(NULL);
    timeStruct = localtime(&seconds);

  /* Kamus Lokal */ 
   int H, M, S;
  /* Algoritma */
   		
		H = timeStruct->tm_hour;
		M = timeStruct->tm_min;
		
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


