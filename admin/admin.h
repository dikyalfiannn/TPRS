#ifndef ADMIN_MODULE_H
#define ADMIN_MODULE_H

#include "../common/pasien.h"
#include "../common/dokter.h"
#include "../datastructure/dll.h"
#include "../datastructure/huffman.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void tambahDokterBaru(Dokter dokterList[], int &jumlah) {
    if(jumlah >= 10) {
        cout << "Batas maksimal dokter tercapai!\n";
        return;
    }
    
    system("cls");
    cout << "\n=== Tambah Dokter Baru ===\n";
    
    string id, nama, spesial, pin;
    
    cout << "ID Dokter (contoh: DR004): ";
    cin >> id;
    
    cin.ignore();
    cout << "Nama Dokter: ";
    getline(cin, nama);
    
    cout << "Spesialisasi: ";
    getline(cin, spesial);
    
    cout << "PIN (4 digit): ";
    cin >> pin;
    
    dokterList[jumlah] = buatDokterBaru(id, nama, spesial, pin);
    jumlah++;
    
    cout << "\nDokter berhasil ditambahkan!\n";
}

void hapusDokter(Dokter dokterList[], int &jumlah) {
    system("cls");
    cout << "\n=== Hapus Dokter ===\n";
    
    if(jumlah == 0) {
        cout << "Tidak ada dokter untuk dihapus.\n";
        return;
    }
    
    cout << "Daftar Dokter:\n";
    for(int i = 0; i < jumlah; i++) {
        cout << (i+1) << ". Dr. " << dokterList[i].nama 
             << " (" << dokterList[i].idDokter << ")\n";
    }
    
    int pilih;
    cout << "\nPilih nomor dokter yang akan dihapus: ";
    cin >> pilih;
    
    if(pilih < 1 || pilih > jumlah) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    pilih--;
    
    for(int i = pilih; i < jumlah - 1; i++) {
        dokterList[i] = dokterList[i + 1];
    }
    jumlah--;
    
    cout << "\nDokter berhasil dihapus!\n";
}

void kelolaDokter(Dokter dokterList[], int &jumlah) {
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "\n=== Kelola Dokter ===\n";
        cout << "1. Lihat Semua Dokter\n";
        cout << "2. Tambah Dokter Baru\n";
        cout << "3. Hapus Dokter\n";
        cout << "4. Kembali\n";
        cout << "\nPilih: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            system("cls");
            cout << "\n=== Daftar Dokter ===\n";
            for(int i = 0; i < jumlah; i++) {
                cout << (i+1) << ". Dr. " << dokterList[i].nama << "\n";
                cout << "   ID: " << dokterList[i].idDokter << "\n";
                cout << "   Spesialisasi: " << dokterList[i].spesialisasi << "\n";
                cout << "   Kuota: " << dokterList[i].kuotaHariIni << "/10\n\n";
            }
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 2) {
            tambahDokterBaru(dokterList, jumlah);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 3) {
            hapusDokter(dokterList, jumlah);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 4) {
            break;
        }
    }
}

void kelolaPasien(Pasien* &head, Pasien* &tail) {
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "\n=== Kelola Pasien ===\n";
        cout << "1. Lihat Semua Pasien\n";
        cout << "2. Hapus Pasien (by NIK)\n";
        cout << "3. Kembali\n";
        cout << "\nPilih: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            system("cls");
            cout << "\n=== Daftar Pasien ===\n";
            tampilkanSemua(head);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 2) {
            system("cls");
            cout << "\n=== Hapus Pasien ===\n";
            string nik;
            cout << "Masukkan NIK pasien yang akan dihapus: ";
            cin >> nik;
            
            hapusPasien(head, tail, nik);
            cout << "Pasien berhasil dihapus!\n";
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 3) {
            break;
        }
    }
}

void backupDataHuffman() {
    system("cls");
    cout << "\n=== Backup Data (Huffman Compression) ===\n";
    cout << "Memproses backup...\n\n";
    
    simpelHuffmanCompress("data/data_pasien.txt", "data/backup.dat");
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void laporanKeuangan(Pasien* head) {
    system("cls");
    cout << "\n=== Laporan Keuangan ===\n";
    
    int totalPasien = 0;
    int pasienBPJS = 0;
    int pasienTunai = 0;
    
    Pasien* temp = head;
    while(temp != NULL) {
        totalPasien++;
        if(!temp->noBPJS.empty()) {
            pasienBPJS++;
        } else {
            pasienTunai++;
        }
        temp = temp->next;
    }
    
    int estimasiPendapatan = pasienTunai * 150000;
    
    cout << "Total Pasien Terdaftar: " << totalPasien << "\n";
    cout << "Pasien BPJS: " << pasienBPJS << "\n";
    cout << "Pasien Tunai: " << pasienTunai << "\n";
    cout << "Pendapatan dari Pasien Tunai: Rp " << estimasiPendapatan << "\n";
    cout << "(Tarif: Rp 150.000 per pasien tunai)\n";
    
    char simpan;
    cout << "\nSimpan laporan ke file? (Y/N): ";
    cin >> simpan;
    
    if(simpan == 'Y' || simpan == 'y') {
        ofstream file("data/laporan_keuangan.txt");
        if(!file.is_open()) {
            cout << "Error: Tidak bisa menyimpan laporan!\n";
            return;
        }
        
        file << "========================================\n";
        file << "       LAPORAN KEUANGAN RS SELAMET\n";
        file << "========================================\n";
        file << "Tanggal: 01-01-2026\n\n";
        
        file << "Total Pasien Terdaftar: " << totalPasien << "\n";
        file << "Pasien BPJS: " << pasienBPJS << "\n";
        file << "Pasien Tunai: " << pasienTunai << "\n\n";
        
        file << "Pendapatan dari Pasien Tunai: Rp " << estimasiPendapatan << "\n";
        file << "(Tarif: Rp 150.000 per pasien tunai)\n\n";
        
        file << "========================================\n";
        file.close();
        
        cout << "\nLaporan berhasil disimpan ke data/laporan_keuangan.txt\n";
    }
}

void dashboardAdmin(Pasien* &head, Pasien* &tail, Dokter dokterList[], int &jumlahDokter) {
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "\n=================================\n";
        cout << "     RS SELAMET - Dashboard Admin\n";
        cout << "=================================\n";
        cout << "1. Kelola Dokter\n";
        cout << "2. Kelola Pasien\n";
        cout << "3. Backup Data (Huffman)\n";
        cout << "4. Laporan Keuangan\n";
        cout << "5. Logout\n";
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            kelolaDokter(dokterList, jumlahDokter);
        } else if(pilihan == 2) {
            kelolaPasien(head, tail);
        } else if(pilihan == 3) {
            backupDataHuffman();
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 4) {
            laporanKeuangan(head);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 5) {
            cout << "Logout berhasil!\n";
            break;
        }
    }
}

#endif
