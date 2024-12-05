#include "header.h"
// Fungsi gotoxy untuk Linux
void gotoxy(int x, int y) {
    COORD coord;         // Struktur untuk koordinat
    coord.X = x;         // Kolom
    coord.Y = y;         // Baris
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// Fungsi untuk membersihkan layar
void clearScreen() {
	int i;
	for(i = 0; i < 20; i++){
		gotoxy(0, i);printf("                                                                                                                                                                                                  ");
		gotoxy(0, i + 20);printf("                                                                                                                                                                                                  ");
	}
	
}

// Fungsi untuk menangkap input karakter tanpa menunggu Enter
// char getch() {
//     struct termios oldt, newt;
//     char ch;

//     // Ambil pengaturan terminal saat ini
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;

//     // Ubah terminal ke mode non-kanonik
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     // Tangkap satu karakter
//     ch = getchar();

//     // Kembalikan terminal ke pengaturan awal
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

//     return ch;
// }

// int strcmpi(const char *str1, const char *str2) {
//     while (*str1 && *str2) {
//         if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
//             return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
//         }
//         str1++;
//         str2++;
//     }
//     return *str1 - *str2;
// }

// void gets(char *str) {
//      const size_t MAX_INPUT = 1024;  // Batas maksimal input

//     int c;
//     while ((c = getchar()) != '\n' && c != EOF);

//     if (fgets(str, MAX_INPUT, stdin) != NULL) {
//         str[strcspn(str, "\n")] = 0;
//     }
// }
