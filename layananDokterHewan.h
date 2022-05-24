#ifndef _LAYANANDOKTERHEWAN_H
#define _LAYANANDOKTERHEWAN_H
#include "boolean.h"
#include <stdio.h>
#include <conio.h>
#include "list.h"

void hitungPenyakit(infotype *info);
int hitungPrioritas(infotype info);
address moveLast(List list);
int addTime(infotype info);
void checkTime(List *list);
#endif
