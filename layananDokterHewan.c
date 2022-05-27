#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layananDokterHewan.h"
#include "list.h"

void tambahAntrian(infotype *info){
	char petName[20];
	int i = 0;
	printf("\t\t\t\tPet Name :");
	scanf("%s",&info->petName);
	//scanf("%s",&info->petOwner);
	printf("\t\t\t\tArrival Time:");
	scanf("%d",&info->arrivalTime);
	info->startTime = 0;
	info->finishTime = 0;
	info->serviceTime = 0;
	for(i; i<9 ; i++){
		info->diseaseList[i] = 0;	
	}
	hitungPenyakit(&*info);
	info->serviceTime = addTime(*info);
	info->priority = hitungPrioritas(*info);
}


void hitungPenyakit(infotype *info){
	int banyakPenyakit;
	int pilihan;
	printf("\t\t\t\tBanyak Penyakit :");
	scanf("%d",&banyakPenyakit);

	int i = 0;
	daftarPenyakit();
	
	while(i < banyakPenyakit){
		printf("\t\t\t\tJenis Penyakit :");
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
	checkTime(&*list);
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

int addTime(infotype info){
	
	int time = 0;
	int ringan = 0;
	int sedang = 0;
	int berat = 0;
	int i = 0;
	
	for (i = 0 ; i < 9 ; i ++){
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
	
	time += ringan * 15;
	time += sedang * 30;
	time += berat * 45;
	
	printf ("%d\n",time);
	printf ("%d\n",ringan);
	printf ("%d\n",sedang);
	printf ("%d\n",berat);
	return time;
}

void checkTime(List *list){
	address current = list->First;
	if (list->First == list->Last){
		current->info.startTime = current->info.arrivalTime;
		current->info.finishTime = current->info.startTime + current->info.serviceTime;
	}
	else {
		current = current->next;
		while (current != Nil){
		current->info.startTime = current->prev->info.finishTime;
		current->info.finishTime = current->info.startTime + current->info.serviceTime;
		current = current->next;
	}
	}
}

void daftarPenyakit(){
	printf("\n\t\t=========================|   JENIS PENYAKIT   |========================= \n");
	printf("\t\t------ Penyakit Ringan -----\n");
	printf("\t\t  [1] Penyakit Kulit\n");
	printf("\t\t  [2] Luka Ringan\n");
	printf("\t\t  [3] Bersin\n");
	printf("\t\t------ Penyakit Sedang -----\n");
	printf("\t\t  [4] Cacingan\n");
	printf("\t\t  [5] Luka Dalam\n");
	printf("\t\t  [6] Diare\n");
	printf("\t\t------ Penyakit Berat -----\n");
	printf("\t\t  [7] Gangguan Kerongkongan yang Mengeluarkan Lendir Berbau Busuk\n");
	printf("\t\t  [8] Kuning\n");
	printf("\t\t  [9] Virus\n\n");
}

void printPenyakit(address P){
	int i = 0;
	
	for(i;i<9;i++){
		switch(P->info.diseaseList[i]){
			case 1 : printf("\t\t\t\t- Penyakit Kulit\n");break;
			case 2 : printf("\t\t\t\t- Luka Ringan\n");break;
			case 3 : printf("\t\t\t\t- Bersin\n");break;
			case 4 : printf("\t\t\t\t- Cacingan\n");break;
			case 5 : printf("\t\t\t\t- Luka Dalam\n");break;
			case 6 : printf("\t\t\t\t- Diare\n");break;
			case 7 : printf("\t\t\t\t- Gangguan Kerongkongan yang Mengeluarkan Lendir Berbau Busuk\n");break;
			case 8 : printf("\t\t\t\t- Kuning\n");break;
			case 9 : printf("\t\t\t\t- Virus\n");break;
		}
	}
}

