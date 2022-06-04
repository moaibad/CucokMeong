#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//======================================================================
/* Prototype Linear List */
/* Konstruktor membentuk List */
void CreateList (List *L){
	First(*L) = Nil;
	Last(*L) = Nil;
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
		Prev(P) = Nil;
		return P;
	}	
}

void DeAlokasi (address P){
	free(P);
}

boolean isEmpty(List L){

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
	//Q = Search(*L,Y);
	
	if(Q != Nil){
		Next(P) = Next(Q) ;
		Next(Q) = P ;
	}else{
		printf("Lokasi tidak ditemukan");
	}
}

/*Penghapusan Elemen*/
void DelFirst (List * L){
	address P;
	P = First(*L);
	
	//add to file Riwayat_Antrian
	riwayatAntrian(P);
	 
	if (First(*L) != Nil){
		if(Next(P) == Nil){
		First(*L) = Nil;
		Last(*L) = Nil;
		DeAlokasi(P);
		}
		else{
		    First(*L) = Next(First(*L));
		    P->next->prev = Nil;
		    Next(P) = Nil;
		    DeAlokasi(P);	
		}
	}	
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
	
	//Q = Search(*L,Y);
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
    //printf("\n\n\t\t=========================|     APLIKASI LAYANAN DOKTER HEWAN     |========================= \n\n\n");
    printf("\n\n\t\t=================================|     DAFTAR ANTRIAN     |================================ \n");
    if (P == Nil) {
    	printf("\n\t\t\t\t\t\t----- TIDAK ADA ANTRIAN -----\n");
    } else {
      	while (Next(P) != Nil) {
        	printf("\n\t\t\tPet Name \t: %s\n", P->info.petName);
        	printf("\t\t\tPriority \t: %d\n", P->info.priority);
        	printf("\t\t\tDisease List \t: \n");
        	printPenyakit(P);
        	printf("\t\t\tService Time \t: %d Jam %d Menit\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
        	printf("\t\t\tStart Time \t: %02d:%02d \n", P->info.startTime.HH, P->info.startTime.MM);
        	printf("\t\t\tFinish Time \t: %02d:%02d \n", P->info.finishTime.HH, P->info.finishTime.MM);
        	printf("\t\t-------------------------------------------------------------------------------------------\n\n");
        	P = Next(P);
      	}
        	printf("\n\t\t\tPet Name \t: %s\n", P->info.petName);
        	printf("\t\t\tPriority \t: %d\n", P->info.priority);
        	printf("\t\t\tDisease List \t: \n");
        	printPenyakit(P);
        	printf("\t\t\tService Time \t: %d Jam %d Menit\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
       		printf("\t\t\tStart Time \t: %02d:%02d \n", P->info.startTime.HH, P->info.startTime.MM);
        	printf("\t\t\tFinish Time \t: %02d:%02d \n", P->info.finishTime.HH, P->info.finishTime.MM);
        	printf("\t\t-------------------------------------------------------------------------------------------\n\n");
    }

}

//=========================================================================

/** KELOMPOK OPERASI LAIN TERHADAP TYPE **/
int NbElmt (List L);
// Mengirimkan banyaknya elemen List atau mengirimkan 0 jika List kosong

address Search (List L, int priority){
	address P;
	boolean Found;
	
	P = Last(L);
	Found = false;
	while((P != Nil) && (Found == false)){
		printf("\nPriority P = %d\n",P->info.priority);
		if (priority == P->info.priority){
			Found = true;
		}else {
			P = Prev(P);
		}
	}
	
	if(P!=Nil){
		printf("\nPriority P = %d\n",P->info.priority);
	}
	
	if(Found == true){
		printf("\n%d ketemu\n",priority );
		return P;
	}
	else{
		printf("\n%d tidak ketemu\n",priority );
		return Nil;
	}
	
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


