#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layananDokterHewan.h"
#include "list.h"

void tambahAntrian(infotype *info){
	char petName[20];
	
	scanf("%s",&info->petName);
	//scanf("%s",&info->petOwner);
	//scanf("%d",&info->arrivalTime);
	info->startTime = 0;
	info->finishTime = 0;
	info->finishTime = 0;
	info->serviceTime = 0;
	for(int i = 0; i<9 ; i++){
		info->diseaseList[i] = 0;	
	}
	
	hitungPenyakit(&*info);
	info->priority = hitungPrioritas(*info);
}


void hitungPenyakit(infotype *info){
	int banyakPenyakit;
	int pilihan;
	scanf("%d",&banyakPenyakit);

	int i = 0;
	//tampilkanDaftarPenyakit();
	
	while(i < banyakPenyakit){
		scanf("%d",&pilihan);
		info->diseaseList[i] = pilihan;
		i++;
	}
	
}


int hitungPrioritas(infotype info){
	int prioritas = 0;
	int i = 0;
	
	int ringan = 0;
	int sedang = 0;
	int berat = 0;
	
	for(i;i<9;i++){
		if(info.diseaseList[i] == 1 || info.diseaseList[i] == 2 || info.diseaseList[i] == 3){
			ringan ++;
		}
		if(info.diseaseList[i] == 4 || info.diseaseList[i] == 5 || info.diseaseList[i] == 6){
			sedang ++;
		}
		if(info.diseaseList[i] == 7 || info.diseaseList[i] == 8 || info.diseaseList[i] == 9){
			berat ++;
		}
	}
	
	
	if(berat!=0){
		prioritas = 4;
	}
	else if (sedang >= 2){
		prioritas = 3;
	}
	else if (ringan >= 3 ){
		prioritas = 2;
	}
	else {
		prioritas = 1;
	}
		
	
	return prioritas;
}


void antrianBaru(List *list,infotype info){
	info.priority = hitungPrioritas(info);
	insert(&*list, info);
}


void insert(List *list, infotype info){
	address P;
	address current = list->Last;
	address reference = Search(*list, info.priority);
	
	
	P = Alokasi(info);
	
	if(isEmpty(*list)){
		list->First = P;
		list->Last = P;
	}
	else if(reference != Nil && reference != list->First){
		if(list->Last == reference){
			reference->next = P;
			P->prev = reference;
		}
		else{
			reference->next->prev = P;
			P->next = reference->next;
			P->prev = reference;
			reference->next = P;		
			printf("\n reference ada \n");
			getch();
		}		
	}
	else{
		if(list->First->next != Nil){
			if(list->First->info.priority < P->info.priority){
				list->First->next->prev = P;
				P->next = list->First->next;
				P->prev = list->First;
				list->First->next = P;
			}
			else{
				while(current->info.priority < P->info.priority){
				current = current->prev;
				}
				current->next->prev = P;
				P->next = current->next;
				P->prev = current;
				current->next = P;	
			}
		}
		else{
			list->First->next = P;
			P->prev = list->First;
		}
	}
	
	list->Last = moveLast(*list);
}

address moveLast(List list){
	while (list.First->next != Nil){
		list.First = list.First->next;
	}
	
	return list.First;
}


