#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//======================================================================
/* Prototype Linear List */
/* Konstruktor membentuk List */
void CreateList (List *L){
	First(*L)=Nil;
}

/* Destruktor/Dealokator: */
address Alokasi (infotype X){
	address P;
	
	P = (address) malloc (sizeof (ElmtList));
	if(P == Nil){
		return Nil;
	}
	else{
		Info(P) = X;
		Next(P) = Nil;
		return P;
	}	
}

void DeAlokasi (address P){
	free(P);
}

boolean ListEmpty(List L){

	if(First(L)==Nil){
		return true;
	}
	else{
		return false;
	}
}

void InsFirst (List *L, infotype X){
	address P;
	P = Alokasi(X);
	Next(P) = First(*L);
	First(*L) = P;
}

void InsLast (List * L, infotype X){
	address P;
	P = Alokasi(X);
	
	if (First(*L) == Nil){
		Next(P) = First(*L);
		First(*L) = P;
	}else{
		P = First(*L);
		while(Next(P) != Nil){
			P = Next(P);
		}
		Next(P)	= Alokasi(X);	
	}
}

void InsAfter (List * L, infotype X, infotype Y){
	address P,Q;
	P = Alokasi (X);
	Q = Search(*L,Y);
	
	if(Q != Nil){
		Next(P) = Next(Q) ;
		Next(Q) = P ;
	}else{
		printf("Lokasi tidak ditemukan");
	}
}

/*Penghapusan Elemen*/
void DelFirst (List * L, infotype *X){
	address P;
	
	P = First(*L);
    (*X) = Info(P);
    First(*L) = Next(First(*L));
    Next(P) = Nil;
    DeAlokasi(P);
}


void DelLast (List *L, infotype *X){
	address P,Q;
	P = First(*L);
	
	while (Next(P)!= Nil){
		Q = P;
		P = Next(P);
	}
	Next(Q) = Nil;
	DeAlokasi(P);
}

void DelAfter (List * L, infotype *X, infotype Y){
	address P,Q;
	
	Q = Search(*L,Y);
	if(Q != Nil){
		Q = Next(P);
		Next(P) = Next(Q) ;
		Next(Q) = Nil;
		DeAlokasi (Q);
	}else{
		printf("Lokasi tidak ditemukan");
	}
	
}

/*Menampilkan Elemen*/
void PrintInfo (List L){
    address P;
    
    P = First(L);
    if (P == Nil) {
      printf("List kosong\n");
    } else {
      while (Next(P) != Nil) {
        printf("%d,",Info(P));
        P = Next(P);
      }
      printf("%d\n", Info(P));
    }
}

//=========================================================================

/** KELOMPOK OPERASI LAIN TERHADAP TYPE **/
int NbElmt (List L);
// Mengirimkan banyaknya elemen List atau mengirimkan 0 jika List kosong
address Search (List L, infotype X){
	address P;
	boolean Found;
	
	P = First(L);
	Found = false;
	while((P != Nil) && (!Found)){
		if (X == Info(P)){
			Found = true;
		} else {
			P = Next(P);
		}
	}
	return P;
}

void DelAll (List *L) {
   /* Kamus Lokal */
    address P;

    /* Algoritma */
    P = First(*L);
    while (P != Nil) {
      First(*L) = Next(First(*L));
      Next(P) = Nil;
      DeAlokasi(P);
      P = First(*L);
    }
}

/* Mencari apakah ada elemen list dengan Info (P)= X
Jika ada, mengirimkan address elemen tersebut yang pertama kali ditemukan.
jika tidak ada, mengirimkan Nil
*/
void InversList (List *L);
/* I.S : L sembarang
F.S : Mengubah Elemen list menjadi terbalik, yaitu elemen terakhir
menjadi elemen pertama, elemen kedua menjadi elemen sebelum terakhir dst
Membalik elemen list, tanpa melakukan alokasi / dealokasi
*/
List getNewInversList (List L);
// Mengirimkan list baru, hasil invers dari L


