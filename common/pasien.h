#ifndef PASIEN_H
#define PASIEN_H

#include "ktp.h"
#include <string>
using namespace std;

struct Pasien {
    KTP dataKTP;
    string username;
    string password;
    string noBPJS;
    
    Pasien* next;
    Pasien* prev;
};

Pasien* buatPasienBaru(KTP ktp, string user, string pass, string bpjs) {
    Pasien* baru = new Pasien;
    baru->dataKTP = ktp;
    baru->username = user;
    baru->password = pass;
    baru->noBPJS = bpjs;
    baru->next = NULL;
    baru->prev = NULL;
    return baru;
}

#endif
