#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <stdbool.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <ctype.h>
#include <windows.h>


typedef char string[100];
typedef struct nodeParent* parentAddress;
typedef struct nodeChild* childAddress;
typedef struct nodeMakanan* addressMakanan;
typedef struct nodeMinuman* addressMinuman;

typedef struct {
    int idNota;
    string tanggal;
    int noMeja;
    float totalHarga;
    bool status;
} Nota;

typedef struct {
    int idPesanan;
    string namaPesanan;
    int jumlahItem;
    float harga;
} Pesanan;

typedef struct nodeParent{
    Nota data;
    parentAddress next;
    childAddress child;
} nodeParent;

typedef struct nodeChild{
    Pesanan data;
    childAddress next;
} nodeChild;

typedef struct {
    parentAddress first;
} Multilist;

typedef struct nodeMakanan{
    string namaMakanan;
    float hargaMakanan;
    int idMakanan;
    int penjualan;
    addressMakanan next;
} nodeMakanan;

typedef struct nodeMinuman{
    string namaMinuman;
    float hargaMinuman;
    int idMinuman;
    int penjualan;
    addressMinuman next;
} nodeMinuman;

typedef struct {
    addressMakanan first;
} ListMakanan;

typedef struct {
    addressMinuman first;
} ListMinuman;

//layout
void gotoxy(int x, int y);
int validateDate(char *date);

//Multilist Utama
void createList(Multilist *L);
Nota constructNota(int idNota, string tanggal, int noMeja, float totalHarga, bool status);
void insertParent(Multilist *L, Nota data);
void deleteParent(Multilist *L, int idNota);
Pesanan constructPesanan(int idPesanan, string namaPesanan, float harga, int jumlahItem);
void insertChild(parentAddress parent, Pesanan data);
void deleteChild(parentAddress parent, int idPesanan);
void viewList(Multilist L, bool stat);
void showSingle(parentAddress parent);
parentAddress findParent(Multilist L, int idNota);
childAddress searchChildByName(parentAddress parent, string namaPesanan);

//Makanan
void createListMakanan(ListMakanan *L);
void insertFirstMakanan(ListMakanan *L, string namaMakanan, float hargaMakanan, int idMakanan);
void insertLastMakanan(ListMakanan *L, string namaMakanan, float hargaMakanan, int idMakanan);
void viewListMakanan(ListMakanan L);
addressMakanan searchMakanan(ListMakanan L, int idMakanan);
addressMakanan searchMakanan2(ListMakanan L, string nama);

//Minuman
void createListMinuman(ListMinuman *L);
void insertFirstMinuman(ListMinuman *L, string namaMinuman, float hargaMinuman, int idMinuman);
void insertLastMinuman(ListMinuman *L, string namaMinuman, float hargaMinuman, int idMinuman);
void viewListMinuman(ListMinuman L);
addressMinuman searchMinuman(ListMinuman L, int idMinuman);
addressMinuman searchMinuman2(ListMinuman L, string nama);

#endif // HEADER_H
