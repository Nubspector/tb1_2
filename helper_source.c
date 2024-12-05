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
    int width = 120; // Lebar layar terminal
    int height = 30; // Tinggi layar terminal

    // Buat string besar berisi spasi
    char buffer[width * height + 1]; // Tambahkan 1 untuk null-terminator
    memset(buffer, ' ', width * height);
    buffer[width * height] = '\0'; // Null-terminator untuk memastikan string valid

    // Pindahkan kursor ke (0, 0)
    gotoxy(0, 0);

    // Cetak buffer untuk membersihkan layar
    printf("%s", buffer);

    // Kembalikan kursor ke (0, 0)
    gotoxy(0, 0);
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int validateDate(char *date) {
    // Format harus dd-bb-yyyy (panjang string: 10)
    if (strlen(date) != 10) {
        return 0; // Tidak valid
    }

    // Cek apakah posisi ke-3 dan ke-6 adalah '-'
    if (date[2] != '-' || date[5] != '-') {
        return 0; // Tidak valid
    }

    // Pisahkan komponen tanggal
    char dayStr[3] = {date[0], date[1], '\0'};
    char monthStr[3] = {date[3], date[4], '\0'};
    char yearStr[5] = {date[6], date[7], date[8], date[9], '\0'};

    // Konversi string ke integer
    int day = atoi(dayStr);
    int month = atoi(monthStr);
    int year = atoi(yearStr);

    // Validasi nilai bulan (1-12)
    if (month < 1 || month > 12) {
        return 0; // Tidak valid
    }

    // Jumlah hari maksimum per bulan
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Periksa tahun kabisat
    if (isLeapYear(year)) {
        daysInMonth[1] = 29; // Februari menjadi 29 hari
    }

    // Validasi nilai hari
    if (day < 1 || day > daysInMonth[month - 1]) {
        return 0; // Tidak valid
    }

    return 1; // Valid
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
