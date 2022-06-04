#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "layananDokterHewan.h"


void Menu();
void textGroup();
void loading();
List list;


int main(){

	infotype info;
	int pilihMenu;
	CreateList(&list);
	//textGroup();
	//loading();
	
	while(pilihMenu != 6){
		system("cls");
		tampilProses(list);
		Menu();
		scanf("%d",&pilihMenu);

		switch(pilihMenu){
			case 1 : 
				tambahAntrian(&info);
				antrianBaru(&list, info);
				getch();
				break;
			
			case 2 :
				DelFirst(&list);
				tampilAntrianBerikutnya(list);
				getch();
				break;
			
			case 3 :
				PrintInfo(list);
				getch();
				system("cls");
				break;
				
			case 4 :
				riwayat();
				getch();
				system("cls");
				break;
			
			case 5 :
				panduanAplikasi();
				getch();
				system("cls");
				break;
			
			case 6 :
				return 0;
		}
	}
	
	return 0;
}

void Menu(){
	printf("\n\n\n");
	printf("\t\t=========================|     APLIKASI LAYANAN DOKTER HEWAN     |========================= \n\n\n");
	printf("\t\t\t\tPilih Menu Di bawah ini : \n");
	printf("\t\t\t\t  [1] Registrasi \n");
	printf("\t\t\t\t  [2] Panggil Antrian \n");
	printf("\t\t\t\t  [3] Daftar Antrian \n");
	printf("\t\t\t\t  [4] Riwayat Antrian \n");
	printf("\t\t\t\t  [5] Panduan Aplikasi \n");
	printf("\t\t\t\t  [6] Exit \n\n");
	printf("\t\t\t\tMasukkan Pilihan : ");
}

void loading(){
	int i =0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\tLoading ");
	for (i=0 ; i <30; i++){
		printf ("%c", 219);
		Sleep (100);
	}
	system("cls");
}

const char cucokText[] =
"\t\t    ______    __  __    ______    ______    __   __ \n\
\t\t   /\\  ___\\  /\\ \\ \\ \\  /\\  ___\\  /\\  __ \\  /\\ \\_/ / \n\
\t\t   \\ \\ \\____ \\ \\ \\_\\ \\ \\ \\ \\____ \\ \\ \\/\\ \\ \\ \\  _ \\ \n\
\t\t    \\ \\_____\\ \\ \\_____\\ \\ \\_____\\ \\ \\_____\\ \\ \\_\\\\_\\ \n\
\t\t     \\/_____/  \\/_____/  \\/_____/  \\/_____/  \\/_//_/       \n\
";

const char meongText[] =
"\t\t\t\t    __________    ______    ______    __   __    ______ \n\
\t\t\t\t   /\\  __  __ \\  /\\  ___\\  /\\  __ \\  /\\ \"-.\\ \\  /\\ \n\
\t\t\t\t   \\ \\ \\ \\ \\ \\ \\ \\ \\  __\\  \\ \\ \\/\\ \\ \\ \\ \\-._ \\ \\ \\  ===\\ \n\
\t\t\t\t    \\ \\_\\ \\_\\ \\_\\ \\ \\_____\\ \\ \\_____\\ \\ \\_\\\\ \\ \\ \\ \\_____\\ \n\
\t\t\t\t     \\/_/ /_/ /_/  \\/_____/  \\/_____/  \\/_/ \\/_/  \\/_____/ \n\
";


void textGroup() {
	int i, j;
	
    for ( i = 0; i < 200; i++) 
		printf("\n"); 
	
	printf("%s\n", cucokText);
	printf("%s\n", meongText);
	
    j = 350000;
    for (i = 0; i < 30; i ++) {
    	j = j * 0.9; 
		usleep(j); 
        printf("\n"); 
    }
    system("cls");
}
