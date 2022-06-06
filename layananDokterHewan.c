#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "layananDokterHewan.h"
#include "list.h"
#include "adt_time.h"


/*
Deskripsi 	: Menginputkan spesifikasi pasien yang akan masuk antrian
Author 		: Cintia Ningsih
*/
void tambahAntrian(infotype *info){
	char petName[20];
	int i = 0;
	
	printf("\n\n\t\t===================================|     REGISTRASI     |================================== \n\n");
	printf("\t\t\t\tPet Name \t: ");
	scanf(" %[^\n]s",&info->petName);
	printf("\t\t\t\tPet Owner \t: ");
	scanf(" %[^\n]s",&info->petOwner);
	printf("\t\t\t\tArrival Time");
	BacaJam(&info->arrivalTime);
	info->startTime = MakeJam(0,0,0);
	info->finishTime = MakeJam(0,0,0);
	info->serviceTime = MakeJam(0,0,0);
	for(i; i<9 ; i++){
		info->diseaseList[i] = 0;	
	}
	tambahPenyakit(&*info);
	addTime(&*info);
	info->priority = hitungPrioritas(*info);
}


/*
Deskripsi 	: Menambahkan penyakit pada pasien
Author 		: Mohammad Fathul'Ibad
*/
void tambahPenyakit(infotype *info){
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


/*
Deskripsi 	: Menghitung prioritas pasien
Author 		: Muhammad Zaki
*/
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


/*
Deskripsi 	: Menambahkan pasien baru ke antrian
Author 		: Mohammad Fathul'Ibad
*/
void antrianBaru(List *list,infotype info){
	info.priority = hitungPrioritas(info);
	
	// Memvalidasi waktu kedatangan baru
	if (validasiArrivalTime(*list,info.arrivalTime)){
		insert(&*list, info);
		checkTime(&*list);
		printf("\n\t\t\t\t--- Pasien %s berhasil ditambahkan ke antrian ---",info.petName);
	}
	else {
		printf("\n\t\t--- Pasien %s tidak berhasil dimasukan ke antrian karena waktu kedatangan tidak sesuai! ---",info.petName);
	}
}


/*
Deskripsi 	: Mengupdate urutan akhir dari list
Author 		: Mohammad Fathul'Ibad
*/
address moveLast(List list){
	while (list.First->next != Nil){
		list.First = list.First->next;
	}
	
	return list.First;
}


/*
Deskripsi 	: Menambahkan waktu service pada pasien
Author 		: Muhammad Zaki
*/
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
}


/*
Deskripsi 	: Mengupdate waktu dari antrian
Author 		: Muhammad Zaki
*/
void checkTime(List *list){
    address current = list->First;
    
    // Jika Antrian tersebut adalah antrian yang pertama
    if (list->First == list->Last){
        //hitung Start Time ( Mulai Waktu Pemerikasan
        current->info.startTime.HH = current->info.arrivalTime.HH;
        current->info.startTime.MM = current->info.arrivalTime.MM + 1;

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
	        if(JamToMenit(current->info.arrivalTime) >= JamToMenit(current->prev->info.finishTime)){
	            current->info.startTime.HH = current->info.arrivalTime.HH;
	            current->info.startTime.MM = current->info.arrivalTime.MM + 1;
	        }
	        else{
	            current->info.startTime.HH = current->prev->info.finishTime.HH;
	            current->info.startTime.MM = current->prev->info.finishTime.MM + 1;    
	        }
	        
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


/*
Deskripsi 	: Menampilkan daftar penyakit yang tersedia
Author 		: Cintia Ningsih
*/
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


/*
Deskripsi 	: Menampilkan daftar penyakit yang diderita oleh pasien
Author 		: Mohammad Fathul'Ibad
*/
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


/*
Deskripsi 	: Menampilkan pasien yang sedang diproses
Author 		: Muhammad Zaki
*/
void tampilProses(List L){
	printf("\n\t\t=============================|     PASIEN YANG DIPROSES     |============================== \n");
    	
	if(First(L) == Nil){
		printf("\n\t\t\t\t\t----- TIDAK ADA PASIEN YANG DIPROSES -----\n");
	}
	else{
		printf("\n\t\t\t\t      ----- Pasien Atas Nama %s Sedang Diproses -----\n", L.First->info.petName);
	}
}


/*
Deskripsi 	: Menampilkan antrian berikutnya
Author 		: Muhammad Zaki
*/
void tampilAntrianBerikutnya(List L){
	printf("\n\n\t\t===============================|     PANGGIL ANTRIAN     |================================= \n");
	if(First(L) == Nil){
		printf("\n\t\t\t\t\t----- TIDAK ADA PASIEN DALAM ANTRIAN -----\n");
	}
	else{
		printf("\n\t\t\t    ----- Pasien Atas Nama %s Silakan Menuju Ke Ruang Pemeriksaan -----\n",L.First->info.petName);
	}
}


/*
Deskripsi 	: Membaca file riwayat antrian
Author 		: Cintia Ningsih
*/
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


/*
Deskripsi 	: Mengisi file riwayat antrian
Author 		: Cintia Ningsih
*/
void riwayatAntrian(address P){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	FILE *FRiwayatAntrian;
	FRiwayatAntrian = fopen("Riwayat_Antrian.txt", "a");
	
	if (FRiwayatAntrian == NULL){
        printf("TIDAK ADA FILE!");
    }else{
    	fprintf(FRiwayatAntrian, "\n\t\t\tPet Name \t: %s\n", P->info.petName);
    	fprintf(FRiwayatAntrian, "\t\t\tPet Owner \t: %s\n", P->info.petOwner);
        fprintf(FRiwayatAntrian, "\n\t\t\tPriority \t: %d\n", P->info.priority);
        fputs("\n\t\t\tDisease List \t: \n", FRiwayatAntrian);
    	
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
		
	    fprintf(FRiwayatAntrian, "\n\t\t\tService Time \t: %d Jam %d Menit\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
	    fprintf(FRiwayatAntrian, "\n\t\t\tArrival Time\t: %02d:%02d\n", P->info.arrivalTime.HH, P->info.arrivalTime.MM);
    	fprintf(FRiwayatAntrian, "\t\t\tStart Time\t: %02d:%02d\n", P->info.startTime.HH, P->info.startTime.MM);
    	fprintf(FRiwayatAntrian, "\t\t\tFinish Time\t: %02d:%02d\n", P->info.finishTime.HH, P->info.finishTime.MM);
    	fprintf(FRiwayatAntrian, "\n\t\t\tDate\t\t: %d %s %d\n", tm.tm_mday, convertBulan(tm.tm_mon + 1),tm.tm_year + 1900);
    	fputs("\t\t-------------------------------------------------------------------------------------------\n\n", FRiwayatAntrian);
    }
    fclose(FRiwayatAntrian);
}


/*
Deskripsi 	: Mengkonversi bulan dalam bentuk integer menjadi string
Author 		: Mohammad Fathul'Ibad
*/
char* convertBulan(int bulan){
	switch(bulan){
		case 1 : return "Januari";
		case 2 : return "Februari";
		case 3 : return "Maret";
		case 4 : return "April";
		case 5 : return "Mei";
		case 6 : return "Juni";
		case 7 : return "Juli";
		case 8 : return "Agustus";
		case 9 : return "September";
		case 10 : return "Oktober";
		case 11 : return "November";
		case 12 : return "Desember";
	}
}


/*
Deskripsi 	: Menampilkan panduan aplikasi dari file
Author 		: Cintia Ningsih
*/
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


/*
Deskripsi 	: Mengirim true apabila  arrival valid dan false apabila tidak valid
Author 		: Mohammad Fathul’Ibad
*/
boolean validasiArrivalTime(List L, Jam J)
{
	if (L.First == Nil){
		return true;
	}
	
	address current = L.First;	
	int maxTime = JamToMenit(current->info.arrivalTime);					
	while (current != Nil)
	{
		if (JamToMenit(current->info.arrivalTime) >= maxTime)
		{
			maxTime = JamToMenit(current->info.arrivalTime);
		}
		current = current->next;
	}

	if (maxTime < JamToMenit(J))
	{
		return true;
	}
	else
	{
		return false;
	}
}

