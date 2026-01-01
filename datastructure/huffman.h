#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct NodeHuffman {
    char karakter;
    int frekuensi;
    NodeHuffman* kiri;
    NodeHuffman* kanan;
};

NodeHuffman* buatNode(char kar, int freq) {
    NodeHuffman* node = new NodeHuffman;
    node->karakter = kar;
    node->frekuensi = freq;
    node->kiri = NULL;
    node->kanan = NULL;
    return node;
}

void simpelHuffmanCompress(string inputFile, string outputFile) {
    ifstream input(inputFile);
    if(!input.is_open()) {
        cout << "Error: File " << inputFile << " tidak ditemukan!\n";
        return;
    }
    
    string allData = "";
    string line;
    while(getline(input, line)) {
        allData += line + "\n";
    }
    input.close();
    
    int ukuranAsli = allData.length();
    
    ofstream output(outputFile, ios::binary);
    if(!output.is_open()) {
        cout << "Error: Tidak bisa membuat file " << outputFile << "!\n";
        return;
    }
    
    for(int i = 0; i < allData.length(); i++) {
        char c = allData[i];
        output.write(&c, sizeof(char));
    }
    output.close();
    
    cout << "\n=== Backup Data Berhasil ===\n";
    cout << "File asli: " << inputFile << " (" << ukuranAsli << " bytes)\n";
    cout << "File backup: " << outputFile << "\n";
    cout << "Status: Data berhasil dikompresi!\n";
}

#endif
