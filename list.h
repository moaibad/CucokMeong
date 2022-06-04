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
//======================================================================
/* Prototype Linear List */
/* Konstruktor membentuk List */
void CreateList (List *L);
/* I.S : L terdefinisi, tidak diketahui nilainya
F.S : L diinisialisasi first(L) = nil
*/
/* Destruktor/Dealokator: */
address Alokasi (infotype X);
/*Mengirimkan address hasil alokasi sebuah elemen
Jika alokasi berhasil, maka address !=Nil,
dan misalnya menghasilkan P, maka Info(P)= x, Next(P)=Nil
Jika alokasi gagal, mengirimkan Nil
*/
void DeAlokasi (address P);
/*I.S : P terdefinisi
F.S : P dikembalikan ke sistem
Melakukan dealokasi/ pengembalian address P ke system
*/
//========================================================================
/** { KELOMPOK OPERASI Cek Elemen kosong atau penuh} **/

boolean isEmpty(List L);
// mengecek apakah jumlah elemen pada List kosong
// mengirimkan true jika List kosong, mengirimkan false jika tidak
//=========================================================================
/** { KELOMPOK Interaksi operasi linear list, baca tulis } **/
/**Penambahan Elemen***/
void InsFirst (List *L, infotype X);
/*I.S : L terdefinisi, mungkin kosong
F.S : melakukan alokasi sebuah elemen dan
menambahkan elemen pertama pada List dengan nilai X jika alokasi
berhasil. Jika alokasi gagal IS = FS
*/
void InsLast (List * L, infotype X);
/*I.S : L terdefinisi, mungkin kosong
F.S : melakukan alokasi sebuah elemen dan
menambahkan elemen terakhir pada List dengan nilai X jika alokasi
berhasil. Jika alokasi gagal IS = FS
*/
void InsAfter (List * L, infotype X, infotype Y);
/*I.S : L terdefinisi, mungkin kosong
F.S : melakukan alokasi sebuah elemen dengan nilai x dan
menambahkan elemen list setelah y ditemukan pertama kali pada list
*/
/*Penghapusan Elemen*/
void DelFirst (List * L);
/*I.S : L tidak kosong
F.S : Elemen pertama List dihapus, nilai info disimpan ke X
dan alamat elemen pertama di dealokasi. Sehingga elemen pertama pada List
adalah elemen berikutnya sebelum penghapusan.
*/

void insert(List *list, infotype info);


/*Menampilkan Elemen*/
void PrintInfo (List L);
/* I.S : L terdefinisi, mungkin kosong
F.S : Jika List tidak kosong, menampilkan semua info yang disimpan pada
elemen list ke layar. jika List kosong, hanya menampilkan pesan ?list
kosong?
*/

//=========================================================================

/** KELOMPOK OPERASI LAIN TERHADAP TYPE **/

address Search (List L, int priority);
/* Mencari apakah ada elemen list dengan Info (P)= X
Jika ada, mengirimkan address elemen tersebut yang pertama kali ditemukan.
jika tidak ada, mengirimkan Nil
*/

#endif

