#ifndef _LAYANANDOKTERHEWAN_H
#define _LAYANANDOKTERHEWAN_H
#include "boolean.h"
#include <stdio.h>
#include <conio.h>
#include "list.h"
#include "adt_time.h"


void hitungPenyakit(infotype *info);
int hitungPrioritas(infotype info);
address moveLast(List list);
void addTime(infotype *info);
void daftarPenyakit();
void checkTime(List *list);
void tampilProses(List L);
void tampilAntrianBerikutnya(List L);
boolean validasiArrivalTime(List L,Jam J);
char* convertBulan(int bulan);
#endif
