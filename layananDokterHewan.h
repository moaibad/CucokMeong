#ifndef _LAYANANDOKTERHEWAN_H
#define _LAYANANDOKTERHEWAN_H
#include "boolean.h"
#include <stdio.h>
#include <conio.h>
#include "list.h"
#include "adt_time.h"

/*
Deskripsi 	: Menginputkan spesifikasi pasien yang akan masuk antrian
Author 		: Cintia Ningsih
*/
void tambahAntrian(infotype *info);

/*
Deskripsi 	: Menambahkan penyakit pada pasien
Author 		: Mohammad Fathul'Ibad
*/
void tambahPenyakit(infotype *info);

/*
Deskripsi 	: Menghitung prioritas pasien
Author 		: Muhammad Zaki
*/
int hitungPrioritas(infotype info);

/*
Deskripsi 	: Menambahkan pasien baru ke antrian
Author 		: Mohammad Fathul'Ibad
*/
void antrianBaru(List *list,infotype info);

/*
Deskripsi 	: Mengupdate urutan akhir dari list
Author 		: Mohammad Fathul'Ibad
*/
address moveLast(List list);

/*
Deskripsi 	: Menambahkan waktu service pada pasien
Author 		: Muhammad Zaki
*/
void addTime(infotype *info);

/*
Deskripsi 	: Mengupdate waktu dari antrian
Author 		: Muhammad Zaki
*/
void checkTime(List *list);

/*
Deskripsi 	: Menampilkan daftar penyakit yang tersedia
Author 		: Cintia Ningsih
*/
void daftarPenyakit();

/*
Deskripsi 	: Menampilkan daftar penyakit yang diderita oleh pasien
Author 		: Mohammad Fathul'Ibad
*/
void printPenyakit(address P);

/*
Deskripsi 	: Menampilkan pasien yang sedang diproses
Author 		: Muhammad Zaki
*/
void tampilProses(List L);

/*
Deskripsi 	: Menampilkan antrian berikutnya
Author 		: Muhammad Zaki
*/
void tampilAntrianBerikutnya(List L);

/*
Deskripsi 	: Membaca file riwayat antrian
Author 		: Cintia Ningsih
*/
void riwayat();

/*
Deskripsi 	: Mengisi file riwayat antrian
Author 		: Cintia Ningsih
*/
void riwayatAntrian(address P);

/*
Deskripsi 	: Mengkonversi bulan dalam bentuk integer menjadi string
Author 		: Cintia Ningsih
*/
char* convertBulan(int bulan);

/*
Deskripsi 	: Menampilkan panduan aplikasi dari file
Author 		: Cintia Ningsih
*/
void panduanAplikasi();


#endif
