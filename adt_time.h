
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
/*
Deskripsi 	: Membentuk Jam dari H, M, S yg valid
Author 		: Muhammad Zaki
*/
Jam MakeJam(int H, int M, int S);
/* Membentuk Jam dari H, M, S yg valid */


/*------------Baca & Tulis jam-----------*/

/*
Deskripsi 	: Membentuk Jam dari input user
Author 		: Muhammad Zaki
*/
void BacaJam(Jam *J);


/*----------Konversi terhadap type jam----------*/

/*
Deskripsi 	: Konversi Jam menjadi menit
Author 		: Muhammad Zaki
*/
int JamToMenit(Jam J);



#endif
