#ifndef QUEUE_H
#define QUEUE_H

#include "../common/pasien.h"
#include <iostream>
using namespace std;

struct NodeQueue {
    Pasien* dataPasien;
    NodeQueue* next;
};

void enqueue(NodeQueue* &front, NodeQueue* &rear, Pasien* p) {
    NodeQueue* baru = new NodeQueue;
    baru->dataPasien = p;
    baru->next = NULL;
    
    if(front == NULL) {
        front = baru;
        rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }
}

Pasien* dequeue(NodeQueue* &front, NodeQueue* &rear) {
    if(front == NULL) {
        return NULL;
    }
    
    NodeQueue* temp = front;
    Pasien* pasien = temp->dataPasien;
    front = front->next;
    
    if(front == NULL) {
        rear = NULL;
    }
    
    delete temp;
    return pasien;
}

int hitungAntrean(NodeQueue* front) {
    int count = 0;
    NodeQueue* temp = front;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void tampilkanAntrean(NodeQueue* front) {
    if(front == NULL) {
        cout << "Antrean kosong.\n";
        return;
    }
    
    NodeQueue* temp = front;
    int no = 1;
    cout << "\n=== Daftar Antrean ===\n";
    while(temp != NULL) {
        cout << "Antrean " << no << ": " 
             << temp->dataPasien->dataKTP.nama << "\n";
        temp = temp->next;
        no++;
    }
}

#endif
