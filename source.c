#include "header.h"

// Fungsi untuk membuat garis horizontal

// Fungsi untuk menampilkan data parent dalam kotak
void showParentBox(parentAddress parent, int tableWidth) {
    int contentWidth = tableWidth - 2;  // Lebar konten di dalam kotak
	int i;
    printf("%c", 201);
    for (i = 0; i < tableWidth-2; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 183);

    // Baris data parent
    printf("%c ID Nota     : %-*d %c\n", 186, contentWidth - 16, parent->data.idNota, 186);
    printf("%c Tanggal     : %-*s %c\n", 186, contentWidth - 16, parent->data.tanggal, 186);
    printf("%c No Meja     : %-*d %c\n", 186, contentWidth - 16, parent->data.noMeja, 186);
    printf("%c Total Harga : %-*.2f %c\n", 186, contentWidth - 16, parent->data.totalHarga, 186);
    printf("%c Status      : %-*s %c\n", 186, contentWidth - 16, parent->data.status ? "Lunas" : "Belum Lunas", 186);

    // Garis bawah kotak
   printf("%c", 204);
    for (i = 0; i < tableWidth-2; i++) {
        printf("%c", 205);
    }
  printf("%c\n", 185);
}

// Fungsi untuk menampilkan header tabel child
void showTableHeader(char *columns[], int columnCount, int columnWidth) {
    int i,j;
	// Header tabel
    printf("%c", 186);
    for ( i = 0; i < columnCount; i++) {
        printf(" %-*s %c", columnWidth - 2, columns[i], 186);
    }
    printf("\n");

    // Garis pemisah header dan data
    printf("%c", 204);
    for (i = 0; i < columnCount; i++) {
        for (j = 0; j < columnWidth; j++) {
            printf("%c", 205);
        }
        if (i < columnCount - 1) {
            printf("%c", 206);
        }
    }
    printf("%c\n", 185);
}

// Fungsi untuk menampilkan baris data child
void showTableRow(int idPesanan, const char *namaPesanan, int jumlahItem, float harga, int columnWidth) {
    printf("%c %-*d %c %-*s %c %-*d %c %-*.2f %c %-*.2f %c\n",
           186,
           columnWidth - 2, idPesanan,
           186,
           columnWidth - 2, namaPesanan,
           186,
           columnWidth - 2, jumlahItem,
           186,
           columnWidth - 2, harga,
           186,
           columnWidth - 2, harga,
           186
           );
}

// Fungsi untuk menampilkan footer tabel
void showTableFooter(int columnCount, int columnWidth) {
	int i,j;
    printf("%c", 200);
    for (i = 0; i < columnCount; i++) {
        for (j = 0; j < columnWidth; j++) {
            printf("%c", 205);
        }
        if (i < columnCount - 1) {
            printf("%c", 202);
        }
    }
    printf("%c\n", 188);
}

// Fungsi utama untuk menampilkan layout
void showSingle(parentAddress parent) {
	
    // Lebar total tabel
    int columnWidth = 20;
    int columnCount = 5;
    int tableWidth = columnWidth * columnCount + (columnCount + 1);

    // Header tabel
    char *columns[] = {"Id Pesanan", "Nama Pemesan", "Jumlah", "Harga", "Alamat"};

    // Tampilkan data parent
    showParentBox(parent, tableWidth);

    // Tampilkan header tabel child
    showTableHeader(columns, columnCount, columnWidth);

    // Iterasi data child
    childAddress tempChild = parent->child;
    while (tempChild != NULL) {
        showTableRow(
            tempChild->data.idPesanan,
            tempChild->data.namaPesanan,
            tempChild->data.jumlahItem,
            tempChild->data.harga,
         
            columnWidth
        );
        tempChild = tempChild->next;
    }

    // Footer tabel
    showTableFooter(columnCount, columnWidth);
}



void viewList(Multilist L, bool stat) {

	gotoxy(0, 0);
    parentAddress temp = L.first;
       
    if (temp == NULL) {
        printf("List Kosong\n");
    } else {
        while (temp != NULL) {
            if(temp->data.status == stat) {
                showSingle(temp);
            }
            temp = temp->next;
        }
    }
}






void createList(Multilist *L) {
    (*L).first = NULL;
}

Nota constructNota(int idNota, string tanggal, int noMeja, float totalHarga, bool status) {
    Nota newNota;
    newNota.idNota = idNota;
    strcpy(newNota.tanggal, tanggal);
    newNota.noMeja = noMeja;
    newNota.totalHarga = totalHarga;
    newNota.status = status;
    return newNota;
}

void insertParent(Multilist *L, Nota data) {
    parentAddress newNode = (parentAddress) malloc(sizeof(nodeParent));
    newNode->data = data;
    newNode->next = NULL;
    newNode->child = NULL;
    
    if ((*L).first == NULL) {
        (*L).first = newNode;
    } else {
        parentAddress last = (*L).first;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

void deleteParent(Multilist *L, int idNota) {
    parentAddress temp = (*L).first;
    parentAddress prev = NULL;
    while (temp != NULL) {
        if (temp->data.idNota == idNota) {
            if (prev == NULL) {
                (*L).first = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}

Pesanan constructPesanan(int idPesanan, string namaPesanan, float harga, int jumlahItem) {
    Pesanan newPesanan;
    newPesanan.idPesanan = idPesanan;
    strcpy(newPesanan.namaPesanan, namaPesanan);
    newPesanan.harga = harga;
    newPesanan.jumlahItem = jumlahItem;
    return newPesanan;
}

void insertChild(parentAddress parent, Pesanan data) {
    childAddress existingChild = searchChildByName(parent, data.namaPesanan);
    if (existingChild != NULL) {
        existingChild->data.jumlahItem += data.jumlahItem;
        existingChild->data.harga += data.harga;
        parent->data.totalHarga += data.harga;
    } else {
        childAddress newNode = (childAddress) malloc(sizeof(nodeChild));
        newNode->data = data;
        newNode->next = NULL;

        if (parent->child == NULL) {
            parent->child = newNode;
        } else {
            childAddress last = parent->child;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
        }
        parent->data.totalHarga += data.harga;
    }
}

void deleteChild(parentAddress parent, int idPesanan) {
    childAddress temp = parent->child;
    childAddress prev = NULL;
    while (temp != NULL) {
        if (temp->data.idPesanan == idPesanan) {
            if (prev == NULL) {
                parent->child = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}



parentAddress findParent(Multilist L, int idNota) {
    parentAddress temp = L.first;
    while (temp != NULL) {
        if (temp->data.idNota == idNota) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//Makanan
void createListMakanan(ListMakanan *L) {
    (*L).first = NULL;
}

void insertFirstMakanan(ListMakanan *L, string namaMakanan, float hargaMakanan, int idMakanan) {
    addressMakanan newNode = (addressMakanan) malloc(sizeof(nodeMakanan));
    strcpy(newNode->namaMakanan, namaMakanan);
    newNode->hargaMakanan = hargaMakanan;
    newNode->idMakanan = idMakanan;
    newNode->next = NULL;

    if ((*L).first == NULL) {
        (*L).first = newNode;
    } else {
        newNode->next = (*L).first;
        (*L).first = newNode;
    }
}

void insertLastMakanan(ListMakanan *L, string namaMakanan, float hargaMakanan, int idMakanan) {
    addressMakanan newNode = (addressMakanan) malloc(sizeof(nodeMakanan));
    strcpy(newNode->namaMakanan, namaMakanan);
    newNode->hargaMakanan = hargaMakanan;
    newNode->idMakanan = idMakanan;
    newNode->penjualan = 0;
    newNode->next = NULL;

    if ((*L).first == NULL) {
        (*L).first = newNode;
    } else {
        addressMakanan last = (*L).first;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

void viewListMakanan(ListMakanan L) {
    addressMakanan temp = L.first;
    if (temp == NULL) {
        printf("List Makanan Kosong\n");
    } else {
        printf("ID\tNama Makanan\tHarga\tPenjualan\n");
        while (temp != NULL) {
            printf("%d\t%s\t%.2f\t%d\n", temp->idMakanan, temp->namaMakanan, temp->hargaMakanan, temp->penjualan);
            temp = temp->next;
        }
    }
}

addressMakanan searchMakanan(ListMakanan L, int idMakanan) {
    addressMakanan temp = L.first;
    while (temp != NULL) {
        if (temp->idMakanan == idMakanan) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

addressMakanan searchMakanan2(ListMakanan L, string nama) {
    addressMakanan temp = L.first;
    while (temp != NULL) {
        if (strcmpi(temp->namaMakanan, nama)==0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

childAddress searchChildByName(parentAddress parent, string namaPesanan) {
    childAddress temp = parent->child;
    while (temp != NULL) {
        if (strcmpi(temp->data.namaPesanan, namaPesanan) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//Minuman
void createListMinuman(ListMinuman *L) {
    (*L).first = NULL;
}

void insertFirstMinuman(ListMinuman *L, string namaMinuman, float hargaMinuman, int idMinuman) {
    addressMinuman newNode = (addressMinuman) malloc(sizeof(nodeMinuman));
    strcpy(newNode->namaMinuman, namaMinuman);
    newNode->hargaMinuman = hargaMinuman;
    newNode->idMinuman = idMinuman;
    newNode->next = NULL;

    if ((*L).first == NULL) {
        (*L).first = newNode;
    } else {
        newNode->next = (*L).first;
        (*L).first = newNode;
    }
}

void insertLastMinuman(ListMinuman *L, string namaMinuman, float hargaMinuman, int idMinuman) {
    addressMinuman newNode = (addressMinuman) malloc(sizeof(nodeMinuman));
    strcpy(newNode->namaMinuman, namaMinuman);
    newNode->hargaMinuman = hargaMinuman;
    newNode->idMinuman = idMinuman;
    newNode->penjualan = 0;
    newNode->next = NULL;

    if ((*L).first == NULL) {
        (*L).first = newNode;
    } else {
        addressMinuman last = (*L).first;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
}

void viewListMinuman(ListMinuman L) {
    addressMinuman temp = L.first;
    if (temp == NULL) {
        printf("List Minuman Kosong\n");
    } else {
        printf("ID\tNama Minuman\tHarga\tPenjualan\n");
        while (temp != NULL) {
            printf("%d\t%s\t%.2f\t%d\n", temp->idMinuman, temp->namaMinuman, temp->hargaMinuman, temp->penjualan);
            temp = temp->next;
        }
    }
}

addressMinuman searchMinuman(ListMinuman L, int idMinuman) {
    addressMinuman temp = L.first;
    while (temp != NULL) {
        if (temp->idMinuman == idMinuman) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

addressMinuman searchMinuman2(ListMinuman L, string nama) {
    addressMinuman temp = L.first;
    while (temp != NULL) {
        if (strcmpi(temp->namaMinuman, nama)==0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Fungsi untuk menampilkan menu
// Fungsi untuk menampilkan menu
void displayMenu(int selected) {
	gotoxy(0,0);
    const char *menu[] = {
        "[*] Insert Nota					",
        "[*] Insert Pesanan					",
        "[*] View Semua Nota					",
        "[*] Pisahkan Nota					",
        "[*] Gabungkan Nota					",
        "[*] Pembayaran					",
        "[*] Tambah Makanan					",
        "[*] Tambah Minuman					",
        "[*] View Makanan					",
        "[*] View Minuman					",
        "[*] Riwayat					",
        "[*] Laporan Pendapatan					",
        "[*] Exit					"
    };

    int menuCount = sizeof(menu) / sizeof(menu[0]); // Hitung jumlah menu
    int i;

    // Tampilkan judul
    printf("========== MENU UTAMA ==========\n");

    // Tampilkan menu
    for (i = 0; i < menuCount; i++) {
        if (i == selected) {
            printf("> %s\n", menu[i]); // Menu yang dipilih diberi tanda '>'
        } else {
            printf("  %s\n", menu[i]);
        }
    }

    // Footer
    printf("===============================\n");
}


void loading(int seconds) {
    const char loadingChars[] = "|/-\\";
    int totalSteps = seconds * 10;  // Total iterasi (asumsi 100ms per langkah)
	int i;
    printf("Loading: ");
    for (i = 0; i < totalSteps; i++) {
        printf("%c", loadingChars[i % 4]);  // Tampilkan karakter loading
        fflush(stdout);                     // Segera tampilkan ke layar
        Sleep(100);                         // Tunggu 100ms
        printf("\b");                       // Hapus karakter terakhir
    }
    printf("Done!\n");
}

