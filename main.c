#include <stdio.h>
#include "list.h"
#include "layananDokterHewan.h"

void Menu();

int main(){
	List list;
	infotype info;
	CreateList(&list);
	
	int pilihMenu;
	
	while(pilihMenu != 3){
		system("cls");
		printf("=======================");
		printf("\nIsi List Sekarang : \n\n");
		PrintInfo(list);
		printf("\n=======================\n");
		
		Menu();
		scanf("%d",&pilihMenu);

		switch(pilihMenu){
			case 1 : 
				tambahAntrian(&info);
				printf("\n%d", info.priority);
				antrianBaru(&list, info);
				printf("\n%d", info.priority);
				printf("\n%s",list.Last);
				getch();
				break;

			case 2 :
				PrintInfo(list);

			case 3 :
				return 0;
		}
	}
	
	return 0;
}

void Menu(){
	printf("Pilih Menu Di bawah ini :\n\n");
	printf("1. Tambah Antrian\n");
	printf("2. Hapus Antrian\n");
	printf("3. Keluar Program\n");

	printf("\nPilihan : ");
}
