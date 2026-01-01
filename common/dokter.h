#ifndef DOKTER_H
#define DOKTER_H

#include <string>
using namespace std;

struct Dokter {
    string idDokter;
    string nama;
    string spesialisasi;
    string pin;
    int kuotaHariIni;
};

Dokter buatDokterBaru(string id, string nama, string spesial, string pin) {
    Dokter d;
    d.idDokter = id;
    d.nama = nama;
    d.spesialisasi = spesial;
    d.pin = pin;
    d.kuotaHariIni = 10;
    return d;
}

bool cekKuota(Dokter d) {
    return d.kuotaHariIni > 0;
}

#endif
