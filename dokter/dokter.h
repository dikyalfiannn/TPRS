#ifndef DOKTER_MODULE_H
#define DOKTER_MODULE_H

#include "../common/dokter.h"
#include "../datastructure/queue.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void lihatInboxChat(Dokter* d, Pasien* headPasien) {
    system("cls");
    cout << "\n=== Inbox Chat ===\n";
    
    ifstream file("data/chat_log.txt");
    if(!file.is_open()) {
        cout << "Belum ada pesan masuk.\n";
        return;
    }
    
    string allLines[100];
    int totalLines = 0;
    string line;
    
    while(getline(file, line) && totalLines < 100) {
        if(line.empty()) continue;
        
        string idDokter = "";
        int pipeCount = 0;
        
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '|') {
                pipeCount++;
                if(pipeCount >= 2) break;
            } else if(pipeCount == 1) {
                idDokter += line[i];
            }
        }
        
        if(idDokter == d->idDokter) {
            allLines[totalLines] = line;
            totalLines++;
        }
    }
    file.close();
    
    if(totalLines == 0) {
        cout << "Belum ada pesan masuk.\n";
        return;
    }
    
    cout << "Total pesan: " << totalLines << "\n\n";
    
    for(int i = 0; i < totalLines; i++) {
        string fields[5];
        int fieldIdx = 0;
        string field = "";
        
        for(int j = 0; j <= allLines[i].length(); j++) {
            if(j == allLines[i].length() || allLines[i][j] == '|') {
                if(fieldIdx < 5) fields[fieldIdx] = field;
                fieldIdx++;
                field = "";
            } else {
                field += allLines[i][j];
            }
        }
        
        string namaPasien = fields[0];
        Pasien* p = cariPasien(headPasien, fields[0]);
        if(p != NULL) {
            if(!p->username.empty()) {
                namaPasien = p->username + " (" + p->dataKTP.nama + ")";
            } else {
                namaPasien = p->dataKTP.nama;
            }
        }
        
        cout << "[" << (i+1) << "] " << namaPasien << "\n";
        cout << "    Pesan: " << fields[3] << "\n";
        
        if(!fields[4].empty()) {
            cout << "    Balasan Anda: " << fields[4] << "\n";
        } else {
            cout << "    (Belum dibalas)\n";
        }
        cout << "\n";
    }
    
    char balas;
    cout << "Balas pesan? (Y/N): ";
    cin >> balas;
    
    if(balas == 'Y' || balas == 'y') {
        int noPesan;
        cout << "Nomor pesan yang ingin dibalas: ";
        cin >> noPesan;
        
        if(noPesan < 1 || noPesan > totalLines) {
            cout << "\nNomor yang Anda input salah!\n";
            return;
        }
        
        noPesan--;
        
        string fields[5];
        int fieldIdx = 0;
        string field = "";
        
        for(int j = 0; j <= allLines[noPesan].length(); j++) {
            if(j == allLines[noPesan].length() || allLines[noPesan][j] == '|') {
                if(fieldIdx < 5) fields[fieldIdx] = field;
                fieldIdx++;
                field = "";
            } else {
                field += allLines[noPesan][j];
            }
        }
        
        string balasan;
        cin.ignore();
        cout << "Ketik balasan: ";
        getline(cin, balasan);
        
        ifstream inFile("data/chat_log.txt");
        string allFileLines[100];
        int totalFileLines = 0;
        
        while(getline(inFile, line) && totalFileLines < 100) {
            if(!line.empty()) {
                allFileLines[totalFileLines] = line;
                totalFileLines++;
            }
        }
        inFile.close();
        
        ofstream outFile("data/chat_log.txt");
        for(int i = 0; i < totalFileLines; i++) {
            if(allFileLines[i] == allLines[noPesan]) {
                outFile << fields[0] << "|" << fields[1] << "|" 
                       << fields[2] << "|" << fields[3] << "|" 
                       << balasan << "\n";
            } else {
                outFile << allFileLines[i] << "\n";
            }
        }
        outFile.close();
        
        cout << "\nBalasan berhasil dikirim!\n";
    }
}

void lihatAntreanPasien(NodeQueue* queue) {
    system("cls");
    cout << "\n=== Antrean Pasien ===\n";
    tampilkanAntrean(queue);
}

int hitungUmur(string tanggalLahir) {
    if(tanggalLahir.length() < 10) return 0;
    
    int tahunLahir = 0;
    string tahunStr = "";
    
    int dashCount = 0;
    for(int i = 0; i < tanggalLahir.length(); i++) {
        if(tanggalLahir[i] == '-') {
            dashCount++;
        } else if(dashCount == 2) {
            tahunStr += tanggalLahir[i];
        }
    }
    
    if(!tahunStr.empty()) {
        tahunLahir = 0;
        for(int i = 0; i < tahunStr.length(); i++) {
            tahunLahir = tahunLahir * 10 + (tahunStr[i] - '0');
        }
    }
    
    int tahunSekarang = 2026;
    return tahunSekarang - tahunLahir;
}

void panggilPasienBerikutnya(NodeQueue* &queue, Dokter* d) {
    system("cls");
    cout << "\n=== Panggil Pasien Berikutnya ===\n";
    
    if(queue == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }
    
    Pasien* pasien = dequeue(queue, queue);
    
    int umur = hitungUmur(pasien->dataKTP.tanggalLahir);
    
    cout << "Pasien dipanggil:\n";
    cout << "Nama: " << pasien->dataKTP.nama << "\n";
    cout << "Umur: " << umur << " tahun\n";
    cout << "Tanggal Lahir: " << pasien->dataKTP.tanggalLahir << "\n";
    
    string diagnosa, resep;
    cin.ignore();
    cout << "\nDiagnosa: ";
    getline(cin, diagnosa);
    cout << "Resep Obat: ";
    getline(cin, resep);
    
    ofstream file("data/riwayat_pemeriksaan.txt", ios::app);
    if(file.is_open()) {
        file << pasien->dataKTP.nik << "|"
             << d->idDokter << "|"
             << d->nama << "|"
             << "01-01-2026|"
             << diagnosa << "|"
             << resep << "\n";
        file.close();
    }
    
    d->kuotaHariIni--;
    
    cout << "\nPemeriksaan selesai!\n";
    cout << "Kuota sisa hari ini: " << d->kuotaHariIni << "\n";
}

void dashboardDokter(Dokter* d, NodeQueue* &queueSaya, Pasien* headPasien) {
    int pilihan;
    
    while(true) {
        system("cls");
        int jumlahAntrean = hitungAntrean(queueSaya);
        
        cout << "\n=================================\n";
        cout << "    RS SELAMET - Dashboard Dokter\n";
        cout << "=================================\n";
        cout << "Dr. " << d->nama << " (" << d->spesialisasi << ")\n";
        cout << "Antrean Hari Ini: " << jumlahAntrean << " pasien\n\n";
        cout << "1. Lihat Antrean Pasien\n";
        cout << "2. Inbox Chat\n";
        cout << "3. Panggil Pasien Berikutnya\n";
        cout << "4. Logout\n";
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        if(pilihan == 1) {
            lihatAntreanPasien(queueSaya);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 2) {
            lihatInboxChat(d, headPasien);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 3) {
            panggilPasienBerikutnya(queueSaya, d);
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore();
            cin.get();
        } else if(pilihan == 4) {
            cout << "Logout berhasil!\n";
            break;
        } else {
            cout << "\nInput yang Anda masukkan salah!\n";
            system("pause");
        }
    }
}

#endif
