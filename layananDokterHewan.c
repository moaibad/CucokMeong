#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layananDokterHewan.h"
#include "list.h"
#include "adt_time.h"

/*
Deskripsi : Modul untuk menginputkan spesifikasi pelanggan
Author : Cintia Ningsih
*/
void tambahAntrian(infotype *info){
	char petName[20];
	int i = 0;
	
	printf("\n\n\t\t===================================|     REGISTRASI     |================================== \n\n");
	printf("\t\t\t\tPet Name \t: ");
	scanf("%s",&info->petName);
	//scanf("%s",&info->petOwner);
	printf("\t\t\t\tArrival Time");
	BacaJam(&info->arrivalTime);
	info->startTime = MakeJam(0,0,0);
	info->finishTime = MakeJam(0,0,0);
	info->serviceTime = MakeJam(0,0,0);
	for(i; i<9 ; i++){
		info->diseaseList[i] = 0;	
	}
	hitungPenyakit(&*info);
	addTime(&*info);
	info->priority = hitungPrioritas(*info);
}

/*

*/
void hitungPenyakit(infotype *info){
	int banyakPenyakit;
	int pilihan;
	printf("\t\t\t\tTotal Disease \t: ");
	scanf("%d",&banyakPenyakit);

	int i = 0;
	daftarPenyakit();
	
	while(i < banyakPenyakit){
		printf("\t\t\t\tType Of Diseases : ");
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
	else if(reference != Nil && reference->info.priority != list->First->info.priority){
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
			if(list->First->info.priority < P->info.priority && list->First->next->info.priority < P->info.priority){
				list->First->next->prev = P;
				P->next = list->First->next;
				P->prev = list->First;
				list->First->next = P;
			}
			else{
				while(current->info.priority < P->info.priority){
				current = current->prev;
				}
				if(current == list->Last){
					current->next = P;
					P->prev = current;
				}
				else{
					current->next->prev = P;
					P->next = current->next;
					P->prev = current;
					current->next = P;		
				}	
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


void addTime(infotype *info){
	

	int time = 0;
	int hour = 0;
	int minute = 0;
	int ringan = 0;
	int sedang = 0;
	int berat = 0;
	int i = 0;
	
	for (i = 0 ; i < 9 ; i ++){
		if(info->diseaseList[i] == 1 || info->diseaseList[i] == 2 || info->diseaseList[i] == 3){
			ringan ++;
		}
		if(info->diseaseList[i] == 4 || info->diseaseList[i] == 5 || info->diseaseList[i] == 6){
			sedang ++;
		}
		if(info->diseaseList[i] == 7 || info->diseaseList[i] == 8 || info->diseaseList[i] == 9){
			berat ++;
		}
	}
	
	
	time += ringan * 15;
	time += sedang * 30;
	time += berat * 45;
	
	while (time >= 60){
		info->serviceTime.HH += 1;
		time = time - 60;
	}
	info->serviceTime.MM += time;

	
	printf ("%d\n",time);
	printf ("%d\n",ringan);
	printf ("%d\n",sedang);
	printf ("%d\n",berat);
}

void checkTime(List *list){
	address current = list->First;
	
	// Jika Antrian tersebut adalah antrian yang pertama
	if (list->First == list->Last){
		//hitung Start Time ( Mulai Waktu Pemerikasan
		current->info.startTime.HH = current->info.arrivalTime.HH;
		current->info.startTime.MM = current->info.arrivalTime.MM;

		
		//hitung Finish Time
		current->info.finishTime.HH = current->info.startTime.HH + current->info.serviceTime.HH;
		current->info.finishTime.MM = current->info.startTime.MM + current->info.serviceTime.MM;
			while (current->info.finishTime.MM >= 60){
			current->info.finishTime.HH += 1;
			current->info.finishTime.MM -= 60;
		}

	}
	
	//Jika bukan antrian yang pertama
	else {
		current = current->next;
		while (current != Nil){
		//Hitung Start Time
		current->info.startTime.HH = current->prev->info.finishTime.HH;
		current->info.startTime.MM = current->prev->info.finishTime.MM;
		
		//Hitung Finish Time
		
		current->info.finishTime.HH = current->info.startTime.HH + current->info.serviceTime.HH;
		current->info.finishTime.MM = current->info.startTime.MM + current->info.serviceTime.MM;
		while (current->info.finishTime.MM >= 60){
			current->info.finishTime.HH += 1;
			current->info.finishTime.MM -= 60;
		}
		

		current = current->next;
	}
	}
}

void daftarPenyakit(){
	printf("\n\t\t---------------------------------|   TYPES OF DISEASES   |--------------------------------- \n");
	printf("\t\t\tPenyakit Ringan \n");
	printf("\t\t\t [1] Penyakit Kulit\n");
	printf("\t\t\t [2] Luka Ringan\n");
	printf("\t\t\t [3] Bersin\n");
	printf("\t\t\tPenyakit Sedang \n");
	printf("\t\t\t [4] Cacingan\n");
	printf("\t\t\t [5] Luka Dalam\n");
	printf("\t\t\t [6] Diare\n");
	printf("\t\t\tPenyakit Berat\n");
	printf("\t\t\t [7] Gangguan Kerongkongan yang Mengeluarkan Lendir Berbau Busuk\n");
	printf("\t\t\t [8] Kuning\n");
	printf("\t\t\t [9] Virus\n\n");
}

void printPenyakit(address P){
	int i = 0;
	
	for(i;i<9;i++){
		switch(P->info.diseaseList[i]){
			case 1 : printf("\t\t\t\t\t- Penyakit Kulit\n");break;
			case 2 : printf("\t\t\t\t\t- Luka Ringan\n");break;
			case 3 : printf("\t\t\t\t\t- Bersin\n");break;
			case 4 : printf("\t\t\t\t\t- Cacingan\n");break;
			case 5 : printf("\t\t\t\t\t- Luka Dalam\n");break;
			case 6 : printf("\t\t\t\t\t- Diare\n");break;
			case 7 : printf("\t\t\t\t\t- Gangguan Kerongkongan yang Mengeluarkan Lendir Berbau Busuk\n");break;
			case 8 : printf("\t\t\t\t\t- Kuning\n");break;
			case 9 : printf("\t\t\t\t\t- Virus\n");break;
		}
	}
}

void tampilProses(List L){
	printf("\n\t\t=============================|     PASIEN YANG DIPROSES     |============================== \n");
    	
	if(First(L) == Nil){
		printf("\n\t\t\t\t\t----- TIDAK ADA PASIEN YANG DIPROSES -----\n");
	}
	else{
		printf("\n\t\t\t\t      ----- Pasien Atas Nama %s Sedang Diperoses -----\n", L.First->info.petName);
	}
}

void tampilAntrianBerikutnya(List L){
	printf("\n\n\t\t===============================|     PANGGIL ANTRIAN     |================================= \n");
	if(First(L) == Nil){
		printf("\n\t\t\t\t\t----- TIDAK ADA PASIEN DALAM ANTRIAN -----\n");
	}
	else{
		printf("\n\t\t\t    ----- Pasien Atas Nama %s Silakan Menuju Ke Ruang Pemeriksaan -----\n",L.First->info.petName);
	}
}

void riwayatAntrian(address P){
	
	FILE *FRiwayatAntrian;
	FRiwayatAntrian = fopen("Riwayat_Antrian.txt", "a");

	if (FRiwayatAntrian == NULL){
        printf("TIDAK ADA FILE!");
    }else{
    	fprintf(FRiwayatAntrian, "\n\t\t\tPet Name \t: %s\n", P->info.petName);
        fprintf(FRiwayatAntrian, "\t\t\tPriority \t: %d\n", P->info.priority);
        fputs("\t\t\tDisease List \t: \n", FRiwayatAntrian);
    	
    	//daftar penyakit
    	int i = 0;
		for(i;i<9;i++){
			switch(P->info.diseaseList[i]){
				case 1 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Penyakit Kulit\n");break;
				case 2 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Luka Ringan\n");break;
				case 3 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Bersin\n");break;
				case 4 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Cacingan\n");break;
				case 5 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Luka Dalam\n");break;
				case 6 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Diare\n");break;
				case 7 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Gangguan Kerongkongan yang Mengeluarkan Lendir Berbau Busuk\n");break;
				case 8 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Kuning\n");break;
				case 9 : fprintf(FRiwayatAntrian, "\t\t\t\t\t- Virus\n");break;
			}
		}
	
    	fprintf(FRiwayatAntrian, "\t\t\tStart Time\t: %02d:%02d\n", P->info.startTime.HH, P->info.startTime.MM);
    	fprintf(FRiwayatAntrian, "\t\t\tService Time\t: %02d:%02d\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
    	fprintf(FRiwayatAntrian, "\t\t\tFinish Time\t: %02d:%02d\n", P->info.finishTime.MM, P->info.finishTime.MM);
    	fputs("\t\t-------------------------------------------------------------------------------------------\n\n", FRiwayatAntrian);
    }
    fclose(FRiwayatAntrian);
}

void riwayat(){
	printf("\n\n\t\t================================|     RIWAYAT ANTRIAN     |================================ \n");
	
	FILE *FRiwayatAntrian;
	char length[6000];
	
	FRiwayatAntrian=fopen("Riwayat_Antrian.txt","r");
	
	if (FRiwayatAntrian == NULL){
        printf("\n\t\t\t\t\t\t----- TIDAK ADA FILE! -----");
    }else{
		while (fgets(length,6000,FRiwayatAntrian)!=NULL){
			printf("%s", length);
		}
	}
	
	fclose(FRiwayatAntrian);
}

void panduanAplikasi(){
	FILE *FPanduanAplikasi;
	char length[6000];
	
	FPanduanAplikasi=fopen("Panduan_Aplikasi.txt","r");
	
	if (FPanduanAplikasi == NULL){
        printf("\n\t\t\t\t\t\t----- TIDAK ADA FILE! -----");
    }else{
		while (fgets(length,6000,FPanduanAplikasi)!=NULL){
			printf("%s", length);
		}
	}
	
	fclose(FPanduanAplikasi);
}


