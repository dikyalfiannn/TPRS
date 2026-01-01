#include "login/login.h"
#include "pasien/pasien.h"
#include "dokter/dokter.h"
#include "admin/admin.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    Pasien *headPasien = NULL, *tailPasien = NULL;
    Dokter dokterList[10];
    int jumlahDokter = 0;
    NodeQueue* queueDokter[10];
    
    for(int i = 0; i < 10; i++) {
        queueDokter[i] = NULL;
    }
    
    muatDataPasien(headPasien, tailPasien);
    muatDataDokter(dokterList, jumlahDokter);
    
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "\n========================================\n";
        cout << "          RS SELAMET\n";
        cout << "   Rumah Sakit Digital Terpercaya\n";
        cout << "========================================\n";
        cout << "1. Login Pasien\n";
        cout << "2. Login Dokter\n";
        cout << "3. Login Admin\n";
        cout << "4. Registrasi Pasien Baru\n";
        cout << "5. Keluar\n";
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInput yang Anda masukkan salah! Silakan pilih angka 1-5.\n";
            system("pause");
            continue;
        }
        
        if(pilihan == 1) {
            Pasien* p = loginPasien(headPasien);
            if(p != NULL) {
                cout << "\nLogin berhasil! Selamat datang, " << p->dataKTP.nama << "!\n";
                system("pause");
                dashboardPasien(p, dokterList, jumlahDokter, queueDokter);
            } else {
                cout << "\nLogin gagal! NIK/Username atau Password salah.\n";
                system("pause");
            }
        } else if(pilihan == 2) {
            int idxDokter = loginDokter(dokterList, jumlahDokter);
            if(idxDokter != -1) {
                cout << "\nLogin berhasil! Selamat datang, Dr. " 
                     << dokterList[idxDokter].nama << "!\n";
                system("pause");
                dashboardDokter(&dokterList[idxDokter], queueDokter[idxDokter], headPasien);
            } else {
                cout << "\nLogin gagal! ID Dokter atau PIN salah.\n";
                system("pause");
            }
        } else if(pilihan == 3) {
            if(loginAdmin()) {
                cout << "\nLogin berhasil! Selamat datang, Admin!\n";
                system("pause");
                dashboardAdmin(headPasien, tailPasien, dokterList, jumlahDokter);
                simpanDataDokter(dokterList, jumlahDokter);
                simpanDataPasien(headPasien);
            } else {
                cout << "\nLogin gagal! Username atau Password salah.\n";
                system("pause");
            }
        } else if(pilihan == 4) {
            registrasiPasien(headPasien, tailPasien);
            system("pause");
        } else if(pilihan == 5) {
            simpanDataPasien(headPasien);
            simpanDataDokter(dokterList, jumlahDokter);
            cout << "\nTerima kasih telah menggunakan RS SELAMET!\n";
            break;
        } else {
            cout << "\nInput yang Anda masukkan salah! Silakan pilih 1-5.\n";
            system("pause");
        }
    }
    
    return 0;
}
