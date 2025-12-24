#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nim[15];
    char nama[100];
    char jurusan[50];
    float ipk;
} Mahasiswa;

char mergedData[100][200];
int total = 0;

// fungsi sorting dari A ke Z
void sortAscending(){
	FILE *fp = fopen("mahasiswa.txt", "r");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
        return;
    }
    Mahasiswa m[100];
    int count = 0;

    while (fscanf(fp, "%[^#]#%[^#]#%[^#]#%f\n", m[count].nama, m[count].nim, m[count].jurusan, &m[count].ipk) == 4) {
        count++;
    }
    fclose(fp);

    for(int i = 0; i < count-1; i++){
        for(int j = 0; j < count-i-1; j++){
            if (strcmp(m[j].nama, m[j+1].nama) > 0) {
            Mahasiswa temp = m[j];
            m[j] = m[j+1];
            m[j+1] = temp;
            }
        }
    }
    fp = fopen("mahasiswa.txt", "w");
    if (fp == NULL) {
        printf("Gagal menyimpan file!\n");
        system("pause");
        getchar();
        return;
    }
    for (int i = 0; i < count; i++){
        fprintf(fp,"%s#%s#%s#%.2f\n", m[i].nama, m[i].nim, m[i].jurusan, m[i].ipk);

    }
    fclose(fp);
	
}

// fungsi sorting dari Z ke A
void sortDescending(){
	FILE *fp = fopen("mahasiswa.txt", "r");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
        return;
    }
    Mahasiswa m[100];
    int count = 0;

    while (fscanf(fp, "%[^#]#%[^#]#%[^#]#%f\n", m[count].nama, m[count].nim, m[count].jurusan, &m[count].ipk) == 4) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count-1; i++) {
        for (int j = 0; j < count-i-1; j++) {
            if (strcmp(m[j].nama, m[j+1].nama) < 0) { // ubah >0 menjadi <0
                Mahasiswa temp = m[j];
                m[j] = m[j+1];
                m[j+1] = temp;
            }
        }
    }
    fp = fopen("mahasiswa.txt", "w");
    if (fp == NULL) {
        printf("Gagal menyimpan file!\n");
        getchar();
        return;
    }
    for (int i = 0; i < count; i++){
        fprintf(fp,"%s#%s#%s#%.2f\n", m[i].nama, m[i].nim, m[i].jurusan, m[i].ipk);

    }
    fclose(fp);
	
}

// fungsi tambah data mahasiswa
void addData() {
    system("cls");
    Mahasiswa m;

    printf("=========================================\n");
    printf("|   SISTEM MANAJEMEN DATA MAHASISWA     |\n");
    printf("=========================================\n");

    do {
        printf("Nama mahasiswa: ");
        scanf(" %[^\n]", m.nama);
        if (m.nama[0] != '\0') {
            m.nama[0] = toupper(m.nama[0]);
        }
    } while (strlen(m.nama) > 100 || strlen(m.nama) < 1);

    do {
        printf("Masukkan NIM (10 Digit): ");
        scanf("%s", m.nim); getchar();
    } while (strlen(m.nim) != 10);

    printf("Jurusan / Program Studi: ");
    scanf(" %[^\n]", m.jurusan); getchar();

    do {
        printf("Masukkan IPK: ");
        scanf("%f", &m.ipk); getchar();
        if (m.ipk < 0.00 || m.ipk > 4.00) {
            printf("IPK tidak valid! Harus 0.00 - 4.00\n");
        }
    } while (m.ipk > 4.00 || m.ipk <= 0.00);
    // convert IPK ke string biar bisa masuk arrData
    char ipkStr[6];
    sprintf(ipkStr, "%.2f", m.ipk);

    sprintf(mergedData[total], "%s#%s#%s#%s", m.nama, m.nim, m.jurusan, ipkStr);
    
    FILE *fp = fopen("mahasiswa.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s\n", mergedData[total]);
        fclose(fp);
        printf("Data berhasil ditambahkan!\n");
        getchar();
    } else {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
    }

    total++;
}

// fungsi untuk nunjukin semua list mahasiswa
void showData() {
	system("cls");
    FILE *fp = fopen("mahasiswa.txt", "r");

    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
        return;
    }

    char nama[100], nim[15], jurusan[50], ipk[10];
    printf("========================================================================\n");
    printf("| %-25s | %-12s | %-18s | %-4s |\n", "Nama", "NIM", "Jurusan", "IPK");
    printf("------------------------------------------------------------------------\n");
    while (fscanf(fp, "%[^#]#%[^#]#%[^#]#%s\n",nama, nim, jurusan, ipk) == 4) {

    printf("| %-25s | %-12s | %-18s | %-4s |\n",nama, nim, jurusan, ipk);
    }

    fclose(fp);

    printf("========================================================================\n");
    getchar();
    getchar();
    system("pause");
}

// fungsi untuk mencari data
void findData() {
    system("cls");
    char cariNim[20];
    int found = 0;

    printf("=========================================\n");
    printf("|   SISTEM MANAJEMEN DATA MAHASISWA     |\n");
    printf("=========================================\n");
    printf("Masukkan NIM: ");
    scanf("%s", cariNim);
    
    FILE *fp = fopen("mahasiswa.txt", "r");
    if (fp == NULL) {
        printf("Gagal membuka file!\n");
        system("pause");
        getchar();
    }

    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        char copy[256];
        strcpy(copy, line);

        char *nama = strtok(copy, "#");
        char *nim = strtok(NULL, "#");
        char *jurusan = strtok(NULL, "#");
        char *ipk = strtok(NULL, "#");
    
        if (nim && strcmp(cariNim, nim) == 0) {
            found = 1;
            printf("Data mahasiswa ditemukan!\n");
            printf("Nama: %s\n", nama);
            printf("NIM: %s\n", nim);
            printf("Jurusan / Program Studi: %s\n", jurusan);
            printf("IPK: %s\n", ipk);
            break;
        }    
    }

    if (!found) {
        printf("Data mahasiswa tidak ditemukan!\n");
    }

    fclose(fp);
    
    system("pause");
}

// fungsi sort data
void sortData() {
    int choose;
	do {
		system("cls");
        
        printf("=========================================\n");
        printf("|   SISTEM MANAJEMEN DATA MAHASISWA     |\n");
        printf("=========================================\n");
        printf("|                                       |\n");
        printf("|   1. Ascending Sort (A-Z)             |\n");
        printf("|   2. Descending Sort (Z-A)            |\n");  
        printf("|                                       |\n");
        printf("=========================================\n");
        printf("Pilih menu (1-2) >> ");
        scanf("%d", &choose);

        switch (choose) {
            case 1: {
                sortAscending();
                break;
            }
            case 2: {
                sortDescending();
                break;
			}
			default: {
				printf("Input Tidak Valid!\n");
				system("pause");
				break;
			}
		}
	} while (choose < 1 || choose > 2);	
	
    printf("Data Sudah Diurutkan!\n");
    system("pause");
}

// fungsi hapus salah satu data mahasiswa
void removeData() {
    system("cls");
    char cariNim[20];
    int found = 0;
    
    printf("=========================================\n");
    printf("|   SISTEM MANAJEMEN DATA MAHASISWA     |\n");
    printf("=========================================\n");
    printf("Masukkan NIM yang ingin dihapus: ");
    scanf("%s", cariNim);

    FILE *fp = fopen("mahasiswa.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        system("pause");
        return;
    }
    
    char line[256];
    
    while (fgets(line, sizeof(line), fp)) {
        char copy[256];
        strcpy(copy, line);
        
        char *nama = strtok(copy, "#");
        char *nim = strtok(NULL, "#");
        char *jurusan = strtok(NULL, "#");
        char *ipk = strtok(NULL, "#");
        
        if (nim && strcmp(nim, cariNim) == 0) {
            found = 1;
            printf("Menghapus data:\n");
            printf("Nama: %s\n", nama);
            printf("NIM: %s\n", nim);
            printf("Jurusan / Program Studi: %s\n", jurusan);
            printf("IPK: %s\n", ipk);
            continue;
        } else {
            fputs(line, temp);
        }

    }
    
    fclose(fp);
    fclose(temp);
    
    remove("mahasiswa.txt");
    rename("temp.txt", "mahasiswa.txt");
    
    if (!found) {
        printf("NIM tidak ditemukan!\n");
    }

    system("pause");
}

// menampilkan menu
void menuPage() {
    int choose;

    system("cls");
    printf("=========================================\n");
    printf("|   SISTEM MANAJEMEN DATA MAHASISWA     |\n");
    printf("=========================================\n");
    printf("|                                       |\n");
    printf("|   1. Tambah Data Mahasiswa            |\n");
    printf("|   2. Tampilkan Semua Data Mahasiswa   |\n");
    printf("|   3. Cari Data Mahasiswa              |\n");
    printf("|   4. Urutkan Data Mahasiswa           |\n");
    printf("|   5. Hapus Data Mahasiswa             |\n");
    printf("|   6. Simpan & Keluar                  |\n");
    printf("|                                       |\n");
    printf("=========================================\n");
    printf("Pilih menu (1-6) >> ");

    scanf("%d", &choose);

    switch (choose) {
        case 1: {
            addData();
            break;
        }
        case 2: {
            showData();
            break;
        }
        case 3: {
            findData();
            break;
        }
        case 4: {
            sortData();
            break;
        }
        case 5: {
            removeData();
            break;
        }
        case 6: {
            printf("Menyimpan...\n");
            exit(0);
            break;
        }
        default: {
            printf("Input Tidak Valid!\n");
            system("pause");
        }
    }
}

int main() {
    while (1) {
        menuPage();
    }

    return 0;

}
