#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/*
Deskripsi 	: Konstruktor membentuk List
Modified By : Mohammad Fathul'Ibad
*/
void CreateList (List *L){
	First(*L) = Nil;
	Last(*L) = Nil;
}


/*
Deskripsi 	: Mengirimkan address hasil alokasi sebuah elemen
Modified By : Cintia Ningsih
*/
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


/*
Deskripsi 	: Melakukan dealokasi/ pengembalian address ke system
Modified By : Cintia Ningsih
*/
void DeAlokasi (address P){
	free(P);
}


/*
Deskripsi 	: Memeriksa apakah terdapat elemen pada list atau tidak
Modified By : Muhammad Zaki
*/
boolean isEmpty(List L){

	if(First(L)==Nil){
		return true;
	}
	else{
		return false;
	}
}


/*
Deskripsi 	: Menambahkan elemen list
Modified By : Mohammad Fathul’Ibad
*/
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


/*
Deskripsi 	: Elemen pertama List dihapus
Author		: Cintia Ningsih
*/
void panggilAntrian (List * L){
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


/*
Deskripsi 	: Menampilkan informasi antrian
Author 		: Mohammad Fathul’Ibad
*/
void tampilAntrian (List L){
    address P;
    
    P = First(L);
    printf("\n\n\t\t=================================|     DAFTAR ANTRIAN     |================================ \n");
    if (P == Nil) {
    	printf("\n\t\t\t\t\t\t----- TIDAK ADA ANTRIAN -----\n");
    } else {
      	while (Next(P) != Nil) {
      		if(P != First(L)){
      			printf("\n\t\t\tPet Name \t: %s\n", P->info.petName);
      			printf("\t\t\tPet Owner \t: %s\n", P->info.petOwner);
	        	printf("\n\t\t\tPriority \t: %d\n", P->info.priority);
	        	printf("\n\t\t\tDisease List \t: \n");
	        	printPenyakit(P);
	        	printf("\n\t\t\tService Time \t: %d Jam %d Menit\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
	        	printf("\n\t\t\tArrival Time\t: %02d:%02d\n", P->info.arrivalTime.HH, P->info.arrivalTime.MM);
	        	printf("\t\t\tStart Time \t: %02d:%02d \n", P->info.startTime.HH, P->info.startTime.MM);
	        	printf("\t\t\tFinish Time \t: %02d:%02d \n", P->info.finishTime.HH, P->info.finishTime.MM);
	        	printf("\t\t-------------------------------------------------------------------------------------------\n\n");
			  }
        	P = Next(P);
      	}
      		if(P != First(L)){
      			printf("\n\t\t\tPet Name \t: %s\n", P->info.petName);
      			printf("\t\t\tPet Owner \t: %s\n", P->info.petOwner);
	        	printf("\n\t\t\tPriority \t: %d\n", P->info.priority);
	        	printf("\n\t\t\tDisease List \t: \n");
	        	printPenyakit(P);
	        	printf("\n\t\t\tService Time \t: %d Jam %d Menit\n", P->info.serviceTime.HH, P->info.serviceTime.MM);
	        	printf("\n\t\t\tArrival Time\t: %02d:%02d\n", P->info.arrivalTime.HH, P->info.arrivalTime.MM);
	       		printf("\t\t\tStart Time \t: %02d:%02d \n", P->info.startTime.HH, P->info.startTime.MM);
	        	printf("\t\t\tFinish Time \t: %02d:%02d \n", P->info.finishTime.HH, P->info.finishTime.MM);
	        	printf("\t\t-------------------------------------------------------------------------------------------\n\n");
			}
			else{
				printf("\n\t\t\t\t\t\t----- TIDAK ADA ANTRIAN -----\n");
			}
        	
    }

}


/*
Deskripsi 	: Mencari apakah ada elemen dengan prioritas yang sama
Author 		: Cintia Ningsih
*/
address Search (List L, int priority){
	address P;
	boolean Found;
	
	P = Last(L);
	Found = false;
	while((P != Nil) && (Found == false)){
		if (priority == P->info.priority){
			Found = true;
		}else {
			P = Prev(P);
		}
	}
	
	return P;
}


address searchAntrian (List L, char* petName){
	address P;
	boolean Found;

	P = Last(L);
	Found = false;
	while((P != Nil) && (Found == false)){
		if (strcmp(petName,P->info.petName) == 0){
			Found = true;
		}else {

			P = Prev(P);
		}
	}
	
	return P;
}


void hapusAntrian(List *L){
	char petName[20];
	printf("\n\n\t\t=================================|     HAPUS ANTRIAN     |================================= \n\n\n");
	printf("\t\t\t\tNama pasien \t: ");
	scanf(" %[^\n]s",&petName);
	address P = searchAntrian(*L,petName);
	//printf("%s",P->info.petName);
	
	if(P == Nil){
		printf("\n\t\t\t\t    ----- Tidak Ada Pasien Atas Nama %s Dalam Antrian -----",petName);
	}
	else{
		if(P != First(*L)){
			if(P == Last(*L)){
				Last(*L) = P->prev;
				Next(Last(*L)) = Nil;
				P->next = Nil;
				P->prev = Nil;
				DeAlokasi(P);
			}
			else{
				P->prev->next = P->next;
				P->next->prev = P->prev;
				P->next = Nil;
				P->prev = Nil;
				DeAlokasi(P);
			}
			printf("\n\t\t\t\t----- Pasien Atas Nama %s Berhasil Dihapus Dalam Antrian -----",petName);
		}
		else{
			printf("\n\t\t\t\t    ----- Tidak Ada Pasien Atas Nama %s Dalam Antrian -----",petName);
		}
	}
}



