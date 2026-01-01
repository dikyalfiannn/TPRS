#ifndef DLL_H
#define DLL_H

#include "../common/pasien.h"
#include <iostream>
using namespace std;

void insertAkhir(Pasien* &head, Pasien* &tail, Pasien* baru) {
    if(head == NULL) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
}

Pasien* cariPasien(Pasien* head, string nikOrUsername) {
    Pasien* temp = head;
    while(temp != NULL) {
        if(temp->dataKTP.nik == nikOrUsername || temp->username == nikOrUsername) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void hapusPasien(Pasien* &head, Pasien* &tail, string nik) {
    Pasien* temp = head;
    
    while(temp != NULL) {
        if(temp->dataKTP.nik == nik) {
            if(temp == head && temp == tail) {
                head = NULL;
                tail = NULL;
            } else if(temp == head) {
                head = head->next;
                head->prev = NULL;
            } else if(temp == tail) {
                tail = tail->prev;
                tail->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

void tampilkanSemua(Pasien* head) {
    if(head == NULL) {
        cout << "Tidak ada data pasien.\n";
        return;
    }
    
    Pasien* temp = head;
    int no = 1;
    while(temp != NULL) {
        cout << no << ". " << temp->dataKTP.nama 
             << " (NIK: " << temp->dataKTP.nik << ")\n";
        temp = temp->next;
        no++;
    }
}

#endif
