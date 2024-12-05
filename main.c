#include "header.h"
#include "source.c"
#include "layout_source.c"
#include "helper_source.c"


int main() {
    int menu = -1;
    int menu2 = -1;

    //Nota
    Nota N, newNota;
    N.idNota = 1;
    N.totalHarga = 0;
    N.status = false;

    //Pesanan;
    parentAddress P, newParent;
    childAddress C;
    int idNota, idM, idN;
    float bayar, pendapatan = 0;
    Pesanan data;
    data.idPesanan = 1;

    //Makanan
    addressMakanan tempM;
    string namaMakanan;
    float hargaMakanan;
    int idMakanan = 1;

    //Minuman
    addressMinuman tempN;
    string namaMinuman;
    float hargaMinuman;
    int idMinuman = 1;

    Multilist L;
    ListMakanan LM;
    ListMinuman LN;
    createList(&L);
    createListMakanan(&LM);
    createListMinuman(&LN);


    insertParent(&L, constructNota(N.idNota++, "12-12-2020", 1, 0, false));
    insertParent(&L, constructNota(N.idNota++, "12-12-2020", 2, 0, false));

    insertChild(findParent(L, 1), constructPesanan(data.idPesanan++, "Nasi Goreng", 15000, 1));
    insertChild(findParent(L, 1), constructPesanan(data.idPesanan++, "Mie Goreng", 12000, 1));
    insertChild(findParent(L, 2), constructPesanan(data.idPesanan++, "Es Jeruk", 5000, 1));
    insertChild(findParent(L, 2), constructPesanan(data.idPesanan++, "Es Jeruk", 5000, 1));
    insertChild(findParent(L, 2), constructPesanan(data.idPesanan++, "Es Jeruk", 5000, 1));
    insertChild(findParent(L, 2), constructPesanan(data.idPesanan++, "Es Jeruk", 5000, 1));


    insertLastMakanan(&LM, "Nasi Goreng", 15000, idMakanan++);
    insertLastMakanan(&LM, "Mie Goreng", 12000, idMakanan++);
    insertLastMakanan(&LM, "Ayam Goreng", 10000, idMakanan++);
    insertLastMakanan(&LM, "Ayam Bakar", 15000, idMakanan++);
    insertLastMakanan(&LM, "Ayam Geprek", 12000, idMakanan++);
    insertLastMakanan(&LM, "Ayam Kremes", 10000, idMakanan++);

    insertLastMinuman(&LN, "Es Jeruk", 6000, idMinuman++);
    insertLastMinuman(&LN, "Es Campur", 7000, idMinuman++);
    insertLastMinuman(&LN, "Es Teler", 8000, idMinuman++);
    insertLastMinuman(&LN, "Es Doger", 9000, idMinuman++);
    insertLastMinuman(&LN, "Es Cendol", 4000, idMinuman++);
    

    int selected = 0;  // Indeks menu yang dipilih
    
    char key;
  // Data contoh
    int idTemp[] = {1, 2, 3};
    char *tanggal[] = {"2024-12-01", "2024-12-02 hahadsvfdfgdfgzdfgsdfg huhu", "2024-12-03"};
    int noMeja[] = {5, 7, 3};
    string temp;
    int i; 
    // header table
    char *columns[] = {"ID Nota", "Tanggal", "No Meja", "Time Stamp" };
    int columnCount = sizeof(columns) / sizeof(columns[0]);
    
    while (1) {
    	menuUtama:
        clearScreen();
		//system("cls");  // Hapus layar
        displayMenu(selected);
		gotoxy(2, 16);
        // Navigasi menu
        key = getch();

        // Debug: Tampilkan kode ASCII tombol yang ditekan
//        printf("ASCII: %d\n", key);

        if (key == 'w' || key == 'W') { // Tombol atas
            selected = (selected - 1 + 13) % 13; // Navigasi ke atas
        } else if (key == 's' || key == 'S') { // Tombol bawah
            selected = (selected + 1) % 13; // Navigasi ke bawah
        } else if (key == 13) { // Tombol Enter (ASCII 10)
            loading(1); // Tampilkan loading selama 1 detik
            clearScreen();

            switch ((selected + 1)) {
                case 1:
            		gotoxy(0,0);
                  	drawBoxWithText("Inputkan Tanggal",50);
					gotoxy(0, 3);               
					printf("\n----- Insert Nota -----\n");
                    printf("ID Nota : %d", N.idNota);
                    while(1) {
                    	gotoxy(0,5);printf("                                                                                                         ");
                    	gotoxy(0,5);printf("\nMasukkan tanggal : "); fflush(stdin); gets(N.tanggal);
                    	if(strcmpi(N.tanggal,"")==0){
                    		gotoxy(0,0);
                    		drawBoxWithText("Inputan Tidak Boleh Kosong",50);
                    		Sleep(500);
                    		gotoxy(0,0);
                    		drawBoxWithText("Inputan Tanggal",50);
                    		gotoxy(0, 5);     
						} else if(!validateDate(N.tanggal)){
							gotoxy(0,0);
                    		drawBoxWithText("Inputan Formatnya Harus dd-mm-yyyy",50);
                    		Sleep(500);
                    		gotoxy(0,0);
                    		drawBoxWithText("Inputan Tanggal",50);
                    		gotoxy(0, 5);
						} else {
							break;
						}
					}
                         // Input No Meja
			        while (1) {
			            gotoxy(0, 7);
			            printf("                                                                                                         "); // Clear line
			            gotoxy(0, 7);
			            printf("Masukkan no meja: ");
			            fflush(stdin);
			            if (scanf("%d", &N.noMeja) != 1 || N.noMeja <= 0) {
			                gotoxy(0, 0);
			                drawBoxWithText("No Meja Tidak Boleh Kosong atau Invalid", 50);
			                Sleep(500);
			                gotoxy(0, 0);
			                drawBoxWithText("Inputkan Tanggal", 50);
			                gotoxy(0, 7);
			                fflush(stdin); // Bersihkan input jika gagal membaca integer
			            } else {
			                break;
			            }
			        }
                    N.idNota++;
                    gotoxy(0, 9);
			        Sleep(500);
	                gotoxy(0, 0);
	                drawBoxWithText("Berhasil Input Nota", 50);
			      	Sleep(600);
			      	goto menuUtama;
                break;

                case 2:
               
					gotoxy(0, 2);
                    printf("\n----- Insert Pesanan -----\n");
                    printf("Masukkan ID Nota : "); scanf("%d", &idNota);
                    P = findParent(L, idNota);
                    if (P != NULL) {
                        printf("\nID Pesanan : %d", data.idPesanan);
                        printf("\n\n[1] Makanan");
                        printf("\n[2] Minuman");
                        printf("\n>>> "); scanf("%d", &menu2);
                        switch(menu2) {
                            case 1:
                                viewListMakanan(LM);
                                printf("\nMasukkan ID Makanan : "); scanf("%d", &idM);
                                tempM = searchMakanan(LM, idM);
                                if(tempM != NULL) {
                                    printf("\nMasukkan jumlah item : "); scanf("%d", &data.jumlahItem);
                                    data.harga = tempM->hargaMakanan * data.jumlahItem;
                                    strcpy(data.namaPesanan, tempM->namaMakanan);
                                } else {
                                    printf("\n\t[!] Makanan tidak ditemukan\n");
                                }
                                insertChild(P, data);
                                data.idPesanan++;
                            break;

                            case 2:
                                viewListMinuman(LN);
                                printf("\nMasukkan ID Minuman : "); scanf("%d", &idN);
                                tempN = searchMinuman(LN, idN);
                                if(tempN != NULL) {
                                    printf("\nMasukkan jumlah item : "); scanf("%d", &data.jumlahItem);
                                    data.harga = tempN->hargaMinuman * data.jumlahItem;
                                    strcpy(data.namaPesanan, tempN->namaMinuman);
                                } else {
                                    printf("\n\t[!] Minuman tidak ditemukan\n");
                                }
                                insertChild(P, data);
                                data.idPesanan++;
                            break;
                        }
                    } else {
                        printf("\n\t[!] Nota tidak ditemukan\n");
                    }
                break;

                case 3:
                	gotoxy(0,2);
                    viewList(L, false);
                break;

                case 4:
                	gotoxy(0, 2);
                    printf("\n----- Pisahkan Nota -----\n");
                    printf("Masukkan ID Nota yang akan dipisahkan : "); scanf("%d", &idNota);
                    P = findParent(L, idNota);
                    if (P != NULL && P->data.status == false) {
                        newNota.idNota = N.idNota++;
                        newNota.totalHarga = 0;
                        newNota.status = false;
                        strcpy(newNota.tanggal, P->data.tanggal);
                        newNota.noMeja = P->data.noMeja;
                        insertParent(&L, newNota);
                        newParent = findParent(L, newNota.idNota);

                        while (true) {
                            showSingle(P);
                            printf("\nMasukkan nama pesanan yang akan dipisahkan (ketik 'selesai' untuk selesai): ");
                            fflush(stdin); gets(data.namaPesanan);
                            if (strcmp(data.namaPesanan, "selesai") == 0) break;

                            C = searchChildByName(P, data.namaPesanan);
                            if (C != NULL) {
                                insertChild(newParent, C->data);
                                deleteChild(P, C->data.idPesanan);
                            } else {
                                printf("\n\t[!] Pesanan tidak ditemukan\n");
                            }
                        }
                    } else {
                        printf("\n\t[!] Nota tidak ditemukan\n");
                    }
                break;

                case 5:
                	gotoxy(0, 2);
                    printf("\n----- Gabungkan Nota -----\n");
                    printf("Masukkan ID Nota pertama : "); scanf("%d", &idNota);
                    P = findParent(L, idNota);
                    if (P != NULL && P->data.status == false) {
                        printf("Masukkan ID Nota kedua : "); scanf("%d", &idN);
                        newParent = findParent(L, idN);
                        if (newParent != NULL && newParent->data.status == false) {
                            if (idNota > idN) {
                                parentAddress temp = P;
                                P = newParent;
                                newParent = temp;
                            }

                            C = P->child;
                            while (C != NULL) {
                                insertChild(newParent, C->data);
                                C = C->next;
                            }
                            deleteParent(&L, P->data.idNota);
                            printf("\n\t[!] Nota berhasil digabungkan\n");
                        } else {
                            printf("\n\t[!] Nota kedua tidak ditemukan atau sudah dibayar\n");
                        }
                    } else {
                        printf("\n\t[!] Nota pertama tidak ditemukan atau sudah dibayar\n");
                    }
                break;

                case 6:
                	gotoxy(0, 2);
                    printf("\n----- Pembayaran -----\n");
                    printf("Masukkan ID Nota : "); scanf("%d", &idNota);
                    P = findParent(L, idNota);
                    if (P != NULL) {
                        showSingle(P);
                        printf("\nTotal Harga : %.2f", P->data.totalHarga);
                        printf("\nMasukkan Total Pembayaran : "); scanf("%f", &bayar);
                        if(bayar >= P->data.totalHarga) {
                            C = P->child;
                            P->data.status = true;
                            pendapatan += P->data.totalHarga;
                            
                            while(C != NULL) {
                                tempM = searchMakanan2(LM, C->data.namaPesanan);
                                tempN = searchMinuman2(LN, C->data.namaPesanan);
                                if (tempM != NULL) {
                                    tempM->penjualan += C->data.jumlahItem;
                                }
                                if(tempN != NULL) {
                                    tempN->penjualan += C->data.jumlahItem;
                                }

                                C = C->next;
                            }

                            printf("\n\t[!] Pembayaran Berhasil\n");
                            printf("\n\t[*] Kembalian : %.2f\n", bayar - P->data.totalHarga);
                        } else {
                            printf("\n\t[!] Pembayaran Kurang\n");
                        }
                    } else {
                        printf("\n\t[!] Nota tidak ditemukan\n");
                    }
                break;

                case 7:
                	gotoxy(0, 2);
                	
                    printf("Masukkan nama makanan : "); fflush(stdin); gets(namaMakanan);
                    printf("Masukkan harga makanan : "); scanf("%f", &hargaMakanan);
                    insertLastMakanan(&LM, namaMakanan, hargaMakanan, idMakanan++);
                break;

                case 8:
                	gotoxy(0, 2);
                    printf("Masukkan nama minuman : "); fflush(stdin); gets(namaMinuman);
                    printf("Masukkan harga minuman : "); scanf("%f", &hargaMinuman);
                    insertLastMinuman(&LN, namaMinuman, hargaMinuman, idMinuman++);
                break;

                case 9:
                	gotoxy(0, 0);
                    viewListMakanan(LM);
                break;

                case 10:
                	gotoxy(0, 0);
                    viewListMinuman(LN);
                break;

                case 11:
                	gotoxy(0, 1);
                	sprintf(temp, "Laporan Pendapatan : Rp.%.2f", pendapatan);
                	drawBoxWithText(temp,104);
                	gotoxy(0, 5);
                    viewList(L, true);
                break;

                case 12:
                    return;
                break;
            }
            getch(); // Tunggu input sebelum kembali ke menu
        }
    }

    // Aksi berdasarkan pilihan
   

    return 0;
}
