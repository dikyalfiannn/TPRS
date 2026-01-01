#ifndef LOGIN_H
#define LOGIN_H

#include "../common/pasien.h"
#include "../common/dokter.h"
#include "../datastructure/dll.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void muatDataPasien(Pasien* &head, Pasien* &tail) {
    ifstream file("data/data_pasien.txt");
    if(!file.is_open()) {
        cout << "File data_pasien.txt tidak ditemukan. Membuat file baru...\n";
        return;
    }
    
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        
        KTP ktp;
        string username, password, noBPJS;
        
        int pos = 0;
        int fieldNo = 0;
        string field = "";
        
        for(int i = 0; i <= line.length(); i++) {
            if(i == line.length() || line[i] == '|') {
                if(fieldNo == 0) ktp.nik = field;
                else if(fieldNo == 1) username = field;
                else if(fieldNo == 2) password = field;
                else if(fieldNo == 3) ktp.nama = field;
                else if(fieldNo == 4) ktp.tempatLahir = field;
                else if(fieldNo == 5) ktp.tanggalLahir = field;
                else if(fieldNo == 6) ktp.jenisKelamin = (field == "1");
                else if(fieldNo == 7) ktp.alamat = field;
                else if(fieldNo == 8) ktp.agama = field;
                else if(fieldNo == 9) ktp.pekerjaan = field;
                else if(fieldNo == 10) ktp.statusPerkawinan = field;
                else if(fieldNo == 11) noBPJS = field;
                
                fieldNo++;
                field = "";
            } else {
                field += line[i];
            }
        }
        
        Pasien* baru = buatPasienBaru(ktp, username, password, noBPJS);
        insertAkhir(head, tail, baru);
    }
    file.close();
}

void simpanDataPasien(Pasien* head) {
    ofstream file("data/data_pasien.txt");
    if(!file.is_open()) {
        cout << "Error: Tidak bisa menyimpan data pasien!\n";
        return;
    }
    
    Pasien* temp = head;
    while(temp != NULL) {
        file << temp->dataKTP.nik << "|"
             << temp->username << "|"
             << temp->password << "|"
             << temp->dataKTP.nama << "|"
             << temp->dataKTP.tempatLahir << "|"
             << temp->dataKTP.tanggalLahir << "|"
             << (temp->dataKTP.jenisKelamin ? "1" : "0") << "|"
             << temp->dataKTP.alamat << "|"
             << temp->dataKTP.agama << "|"
             << temp->dataKTP.pekerjaan << "|"
             << temp->dataKTP.statusPerkawinan << "|"
             << temp->noBPJS << "\n";
        temp = temp->next;
    }
    file.close();
}

void muatDataDokter(Dokter dokterList[], int &jumlah) {
    ifstream file("data/data_dokter.txt");
    if(!file.is_open()) {
        cout << "File data_dokter.txt tidak ditemukan. Membuat file baru...\n";
        jumlah = 0;
        return;
    }
    
    string line;
    jumlah = 0;
    while(getline(file, line) && jumlah < 10) {
        if(line.empty()) continue;
        
        string field = "";
        int fieldNo = 0;
        
        for(int i = 0; i <= line.length(); i++) {
            if(i == line.length() || line[i] == '|') {
                if(fieldNo == 0) dokterList[jumlah].idDokter = field;
                else if(fieldNo == 1) dokterList[jumlah].nama = field;
                else if(fieldNo == 2) dokterList[jumlah].spesialisasi = field;
                else if(fieldNo == 3) dokterList[jumlah].pin = field;
                else if(fieldNo == 4) dokterList[jumlah].kuotaHariIni = stoi(field);
                
                fieldNo++;
                field = "";
            } else {
                field += line[i];
            }
        }
        jumlah++;
    }
    file.close();
}

void simpanDataDokter(Dokter dokterList[], int jumlah) {
    ofstream file("data/data_dokter.txt");
    if(!file.is_open()) {
        cout << "Error: Tidak bisa menyimpan data dokter!\n";
        return;
    }
    
    for(int i = 0; i < jumlah; i++) {
        file << dokterList[i].idDokter << "|"
             << dokterList[i].nama << "|"
             << dokterList[i].spesialisasi << "|"
             << dokterList[i].pin << "|"
             << dokterList[i].kuotaHariIni << "\n";
    }
    file.close();
}

Pasien* loginPasien(Pasien* head) {
    string nikOrUser, pass;
    cout << "\n=== Login Pasien ===\n";
    cout << "NIK / Username: ";
    cin >> nikOrUser;
    cout << "Password: ";
    cin >> pass;
    
    Pasien* p = cariPasien(head, nikOrUser);
    if(p != NULL && p->password == pass) {
        return p;
    }
    return NULL;
}

int loginDokter(Dokter dokterList[], int jumlah) {
    string id, pin;
    cout << "\n=== Login Dokter ===\n";
    cout << "ID Dokter: ";
    cin >> id;
    cout << "PIN: ";
    cin >> pin;
    
    for(int i = 0; i < jumlah; i++) {
        if(dokterList[i].idDokter == id && dokterList[i].pin == pin) {
            return i;
        }
    }
    return -1;
}

bool loginAdmin() {
    string user, pass;
    cout << "\n=== Login Admin ===\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    
    return (user == "admin" && pass == "admin123");
}

void registrasiPasien(Pasien* &head, Pasien* &tail) {
    KTP ktp;
    string username, password, noBPJS;
    char pilihanGender, pilihanBPJS;
    
    cout << "\n=== Registrasi Pasien Baru ===\n";
    cin.ignore();
    
    cout << "NIK (16 digit): ";
    getline(cin, ktp.nik);
    
    cout << "Nama Lengkap: ";
    getline(cin, ktp.nama);
    
    cout << "Tempat Lahir: ";
    getline(cin, ktp.tempatLahir);
    
    cout << "Tanggal Lahir (DD-MM-YYYY): ";
    getline(cin, ktp.tanggalLahir);
    
    cout << "Jenis Kelamin (L/P): ";
    cin >> pilihanGender;
    ktp.jenisKelamin = (pilihanGender == 'P' || pilihanGender == 'p');
    
    cin.ignore();
    cout << "Alamat: ";
    getline(cin, ktp.alamat);
    
    cout << "Agama: ";
    getline(cin, ktp.agama);
    
    cout << "Pekerjaan: ";
    getline(cin, ktp.pekerjaan);
    
    cout << "Status Perkawinan (Kawin/Belum): ";
    getline(cin, ktp.statusPerkawinan);
    
    cout << "Username (untuk login): ";
    getline(cin, username);
    
    cout << "Password: ";
    getline(cin, password);
    
    cout << "Punya BPJS? (Y/N): ";
    cin >> pilihanBPJS;
    if(pilihanBPJS == 'Y' || pilihanBPJS == 'y') {
        cin.ignore();
        cout << "No BPJS: ";
        getline(cin, noBPJS);
    } else {
        noBPJS = "";
    }
    
    Pasien* baru = buatPasienBaru(ktp, username, password, noBPJS);
    insertAkhir(head, tail, baru);
    simpanDataPasien(head);
    
    cout << "\nRegistrasi berhasil! Silakan login.\n";
}

#endif
