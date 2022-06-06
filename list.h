/*
Program : list.h
Author : (Nim, Nama)
Kelas :
Deskripsi: Header file dari prototype linear linked list
Tanggal :
*/
#ifndef _LIST_H
#define _LIST_H
#include "boolean.h"
#include <stdio.h>
#include <conio.h>
#include "adt_time.h"
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) (L).First
#define Last(L) (L).Last
/** Definisi ABSTRACT DATA TYPE List **/
/*Definisi List :*/
/* List kosong ===> First (L) =Nil
Setiap elemen dengan address P dapat diacu info (P) dan Next (P);
Elemen terakhir list ===> Jika addressnya Last maka Next (Last) = Nil
*/
typedef struct tElmtList *address; // pointer menunjuk ke alamat tElmtList

typedef struct {
	char petName[50];
	char petOwner[20];
	Jam arrivalTime;
	Jam startTime;
	Jam finishTime;
	Jam serviceTime;
	int priority;
	int diseaseList[9];
}infotype;

typedef struct tElmtList{
	infotype info;
	address next;
	address prev;
} ElmtList;

typedef struct{
	address First;
	address Last;
} List;

/*
Deskripsi 	: Konstruktor membentuk List
Modified By : Mohammad Fathul'Ibad
*/
void CreateList (List *L);

/*
Deskripsi 	: Mengirimkan address hasil alokasi sebuah elemen
Modified By : Cintia Ningsih
*/
address Alokasi (infotype X);

/*
Deskripsi 	: Melakukan dealokasi/ pengembalian address ke system
Modified By : Cintia Ningsih
*/
void DeAlokasi (address P);

/*
Deskripsi 	: Memeriksa apakah terdapat elemen pada list atau tidak
Modified By : Muhammad Zaki
*/
boolean isEmpty(List L);

/*
Deskripsi 	: Menambahkan elemen list
Modified By : Mohammad Fathul’Ibad
*/
void insert(List *list, infotype info);

/*
Deskripsi 	: Elemen pertama List dihapus
Author		: Cintia Ningsih
*/
void hapusAntrian (List * L);

/*
Deskripsi 	: Menampilkan informasi antrian
Author 		: Mohammad Fathul’Ibad
*/
void tampilAntrian (List L);

/*
Deskripsi 	: Mencari apakah ada 
Author : Cintia Ningsih
*/
address Search (List L, int priority);

#endif

