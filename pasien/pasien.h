#ifndef PASIEN_MODULE_H
#define PASIEN_MODULE_H

#include "../common/pasien.h"
#include "../common/dokter.h"
#include "../datastructure/queue.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void chatDokter(Pasien* p, Dokter dokterList[], int jumlahDokter) {
    system("cls");
    cout << "\n=== Chat Dokter ===\n";
    
    cout << "Pilih Spesialisasi:\n";
    
    string spesialisasiList[10];
    int spesialisasiCount = 0;
    
    for(int i = 0; i < jumlahDokter; i++) {
        bool sudahAda = false;
        for(int j = 0; j < spesialisasiCount; j++) {
            if(spesialisasiList[j] == dokterList[i].spesialisasi) {
                sudahAda = true;
                break;
            }
        }
        if(!sudahAda) {
            spesialisasiList[spesialisasiCount] = dokterList[i].spesialisasi;
            spesialisasiCount++;
        }
    }
    
    for(int i = 0; i < spesialisasiCount; i++) {
        cout << (i+1) << ". " << spesialisasiList[i] << "\n";
    }
    
    int pilihSpesial;
    cout << "\nPilih spesialisasi: ";
    cin >> pilihSpesial;
    
    if(pilihSpesial < 1 || pilihSpesial > spesialisasiCount) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    string spesialDipilih = spesialisasiList[pilihSpesial - 1];
    
    cout << "\nDokter " << spesialDipilih << ":\n";
    int dokterSpesialList[10];
    int dokterSpesialCount = 0;
    
    for(int i = 0; i < jumlahDokter; i++) {
        if(dokterList[i].spesialisasi == spesialDipilih) {
            cout << (dokterSpesialCount + 1) << ". " << dokterList[i].nama << "\n";
            dokterSpesialList[dokterSpesialCount] = i;
            dokterSpesialCount++;
        }
    }
    
    int pilihDokter;
    cout << "\nPilih dokter: ";
    cin >> pilihDokter;
    
    if(pilihDokter < 1 || pilihDokter > dokterSpesialCount) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    int idxDokter = dokterSpesialList[pilihDokter - 1];
    string idDokter = dokterList[idxDokter].idDokter;
    
    string pesan;
    cin.ignore();
    cout << "\nKetik pesan untuk " << dokterList[idxDokter].nama << ": ";
    getline(cin, pesan);
    
    ofstream file("data/chat_log.txt", ios::app);
    if(!file.is_open()) {
        cout << "Error: Tidak bisa menyimpan pesan!\n";
        return;
    }
    
    file << p->dataKTP.nik << "|" 
         << idDokter << "|"
         << "10:00|"
         << pesan << "|"
         << "" << "\n";
    file.close();
    
    cout << "\nPesan terkirim ke " << dokterList[idxDokter].nama << "!\n";
    cout << "Tunggu balasan dari dokter.\n";
}

void lihatRiwayatChat(Pasien* p, Dokter dokterList[], int jumlahDokter) {
    system("cls");
    cout << "\n=== Riwayat Chat ===\n";
    
    ifstream file("data/chat_log.txt");
    if(!file.is_open()) {
        cout << "Belum ada riwayat chat.\n";
        return;
    }
    
    string line;
    bool adaChat = false;
    
    while(getline(file, line)) {
        if(line.empty()) continue;
        
        string nikPasien = "";
        int pipeCount = 0;
        
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '|') {
                pipeCount++;
                if(pipeCount >= 1) break;
            } else if(pipeCount == 0) {
                nikPasien += line[i];
            }
        }
        
        if(nikPasien == p->dataKTP.nik) {
            adaChat = true;
            
            string fields[5];
            int fieldIdx = 0;
            string field = "";
            
            for(int i = 0; i <= line.length(); i++) {
                if(i == line.length() || line[i] == '|') {
                    if(fieldIdx < 5) fields[fieldIdx] = field;
                    fieldIdx++;
                    field = "";
                } else {
                    field += line[i];
                }
            }
            
            string namaDokter = fields[1];
            for(int i = 0; i < jumlahDokter; i++) {
                if(dokterList[i].idDokter == fields[1]) {
                    namaDokter = dokterList[i].nama;
                    break;
                }
            }
            
            cout << "\nAnda: " << fields[3] << "\n";
            if(!fields[4].empty()) {
                cout << namaDokter << ": " << fields[4] << "\n";
            } else {
                cout << "(Belum dibalas dokter)\n";
            }
        }
    }
    file.close();
    
    if(!adaChat) {
        cout << "Belum ada riwayat chat.\n";
    }
}

void lihatRiwayatPemeriksaan(Pasien* p, Dokter dokterList[], int jumlahDokter) {
    system("cls");
    cout << "\n=== Riwayat Pemeriksaan ===\n";
    
    ifstream file("data/riwayat_pemeriksaan.txt");
    if(!file.is_open()) {
        cout << "Belum ada riwayat pemeriksaan.\n";
        return;
    }
    
    string line;
    bool adaRiwayat = false;
    int nomor = 1;
    
    while(getline(file, line)) {
        if(line.empty()) continue;
        
        string fields[6];
        int fieldIdx = 0;
        string field = "";
        
        for(int i = 0; i <= line.length(); i++) {
            if(i == line.length() || line[i] == '|') {
                if(fieldIdx < 6) fields[fieldIdx] = field;
                fieldIdx++;
                field = "";
            } else {
                field += line[i];
            }
        }
        
        if(fields[0] == p->dataKTP.nik) {
            adaRiwayat = true;
            cout << "\n[" << nomor << "] Tanggal: " << fields[3] << "\n";
            cout << "    Dokter: " << fields[2] << "\n";
            cout << "    Diagnosa: " << fields[4] << "\n";
            cout << "    Resep: " << fields[5] << "\n";
            nomor++;
        }
    }
    file.close();
    
    if(!adaRiwayat) {
        cout << "Belum ada riwayat pemeriksaan.\n";
    }
}

void bookingDokter(Pasien* p, Dokter dokterList[], int jumlahDokter, NodeQueue* queueDokter[]) {
    system("cls");
    cout << "\n=== Booking Dokter ===\n";
    cout << "Daftar Dokter:\n";
    
    for(int i = 0; i < jumlahDokter; i++) {
        int sisaKuota = dokterList[i].kuotaHariIni - hitungAntrean(queueDokter[i]);
        cout << (i+1) << ". " << dokterList[i].nama 
             << " (" << dokterList[i].spesialisasi << ")"
             << " - Kuota: " << sisaKuota << "/10\n";
    }
    
    int pilihDokter;
    cout << "\nPilih dokter (1-" << jumlahDokter << "): ";
    cin >> pilihDokter;
    
    if(pilihDokter < 1 || pilihDokter > jumlahDokter) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    pilihDokter--;
    
    int antreanSekarang = hitungAntrean(queueDokter[pilihDokter]);
    if(antreanSekarang >= 10) {
        cout << "\nMaaf, kuota dokter ini sudah penuh!\n";
        return;
    }
    
    int metodeBayar;
    cout << "\nMetode Pembayaran:\n";
    cout << "1. BPJS\n";
    cout << "2. Tunai\n";
    cout << "Pilih: ";
    cin >> metodeBayar;
    
    if(metodeBayar == 1) {
        if(p->noBPJS.empty()) {
            cout << "\nAnda belum terdaftar BPJS!\n";
            cout << "No BPJS Anda (jika ada): ";
            cin >> p->noBPJS;
        }
        cout << "Menggunakan BPJS: " << p->noBPJS << "\n";
    } else {
        cout << "Pembayaran di kasir setelah pemeriksaan.\n";
    }
    
    enqueue(queueDokter[pilihDokter], queueDokter[pilihDokter], p);
    
    cout << "\n=== Booking Berhasil! ===\n";
    cout << "Tiket Antrean: #" << (antreanSekarang + 1) << "\n";
    cout << "Dokter: " << dokterList[pilihDokter].nama << "\n";
    cout << "Spesialisasi: " << dokterList[pilihDokter].spesialisasi << "\n";
    cout << "Waktu Perkiraan: Mohon menunggu\n";
}

void dashboardPasien(Pasien* p, Dokter dokterList[], int jumlahDokter, NodeQueue* queueDokter[]) {
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "\n=================================\n";
        cout << "    RS SELAMET - Dashboard Pasien\n";
        cout << "=================================\n";
        cout << "Halo, " << p->dataKTP.nama << "!\n\n";
        cout << "1. Booking Dokter\n";
        cout << "2. Chat Dokter (Konsultasi Online)\n";
        cout << "3. Riwayat Chat\n";
        cout << "4. Riwayat Pemeriksaan\n";
        cout << "5. Logout\n";
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            bookingDokter(p, dokterList, jumlahDokter, queueDokter);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 2) {
            chatDokter(p, dokterList, jumlahDokter);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 3) {
            lihatRiwayatChat(p, dokterList, jumlahDokter);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 4) {
            lihatRiwayatPemeriksaan(p, dokterList, jumlahDokter);
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
