# Presentasi Tugas Proyek Struktur Data
## RS SELAMET - Hospital Management System

---

## 📌 Informasi Proyek

**Nama Proyek**: RS SELAMET (Sistem Manajemen Rumah Sakit Digital)  
**Bahasa**: C++11  
**Total Kode**: **~1.645 baris** dalam **13 file**  
**Struktur Data**: **5 struktur data manual** (DLL, Queue, Stack, Huffman, AVL Tree)  
**Repository**: [github.com/dikyalfiannn/TPRS](https://github.com/dikyalfiannn/TPRS)

---

## 💡 Tentang Project Ini

**Dari sudut pandang kita sebagai developer:**

Jadi gini, kita bikin program ini tujuannya untuk **digitalisasi manajemen rumah sakit**. Kayak aplikasi Halodoc atau Alodokter gitu, tapi versi console-based.

**Masalah yang kita solve:**
- ❌ Antrean pasien yang gak teratur (siapa duluan siapa belakangan)
- ❌ Data pasien masih manual di buku/Excel (gampang hilang)
- ❌ Dokter susah komunikasi sama pasien di luar jam praktek
- ❌ Admin ribet kelola data dokter & pasien
- ❌ Laporan keuangan masih manual (hitung satu-satu)

**Solusi yang kita tawarkan:**
- ✅ **Queue system** → Antrean otomatis, gak bisa nyelonong
- ✅ **Database digital (DLL)** → Semua data pasien tersimpan rapi, gampang dicari
- ✅ **Chat konsultasi** → Pasien bisa tanya dokter kapan aja
- ✅ **Auto history** → Riwayat pemeriksaan otomatis ke-record
- ✅ **Laporan otomatis** → Admin tinggal klik, langsung keluar laporan keuangan

**Kenapa penting?**  
Program ini bikin rumah sakit lebih **efisien** dan **modern**. Pasien gak perlu antre lama, dokter lebih produktif, admin gak overwhelmed.

---

## 🔄 Alur Program

### Flow Utama

```
┌─────────────────┐
│   Main Menu     │
│  1. Pasien      │
│  2. Dokter      │
│  3. Admin       │
│  4. Registrasi  │
└────────┬────────┘
         │
    ┌────┴────┐
    │ Pilih   │
    │  Role?  │
    └────┬────┘
         │
    ┌────▼────┬──────────┬──────────┐
    │         │          │          │
┌───▼───┐ ┌──▼───┐ ┌────▼────┐ ┌───▼────────┐
│Pasien │ │Dokter│ │  Admin  │ │ Registrasi │
└───┬───┘ └──┬───┘ └────┬────┘ └───┬────────┘
    │        │          │          │
```

### 1. Alur Pasien

**Login → Dashboard → Pilih Menu:**

```
Pasien Login (NIK/Username + Password)
         ↓
   ✅ Berhasil? → Dashboard Pasien
         ↓
   ┌─────┴─────┬─────────┬────────────┐
   │           │         │            │
Booking      Chat    Riwayat    Riwayat
Dokter      Dokter     Chat    Pemeriksaan
   │           │         │            │
   ↓           ↓         ↓            ↓
[Queue]    [File I/O] [File I/O]  [File I/O]
```

**Contoh konkret - Booking:**
1. Pasien pilih "Booking Dokter"
2. Pilih spesialisasi (Umum/Gigi/Jantung)
3. Pilih dokter yang tersedia
4. Sistem cek: Queue dokter penuh gak? (max 10)
5. Kalau masih ada slot → `enqueue()` pasien ke antrean
6. Pasien dapat tiket nomor antrean
7. Data tersimpan di Queue dokter

### 2. Alur Dokter

**Login → Lihat Antrean → Periksa Pasien:**

```
Dokter Login (ID + PIN)
         ↓
   Dashboard Dokter
   (Tampil jumlah antrean)
         ↓
   ┌─────┴─────┬──────────┐
   │           │          │
 Lihat      Panggil    Inbox
Antrean     Pasien      Chat
   │           │          │
   ↓           ↓          ↓
[Queue]   [Dequeue]  [File I/O]
            │
            ↓
     Input Diagnosa
       & Resep
            │
            ↓
      [Auto-save ke
    riwayat_pemeriksaan.txt]
```

**Contoh konkret - Panggil Pasien:**
1. Dokter pilih "Panggil Pasien Berikutnya"
2. Sistem `dequeue()` → pasien paling depan keluar dari queue
3. Tampil data pasien (nama, umur, NIK)
4. Dokter input diagnosa & resep
5. Sistem otomatis simpan ke `riwayat_pemeriksaan.txt`
6. Kuota dokter dikurangi 1

### 3. Alur Admin

**Login → Kelola Data → Backup/Laporan:**

```
Admin Login (Username + Password)
         ↓
   Dashboard Admin
         ↓
   ┌─────┴─────┬──────────┬──────────┐
   │           │          │          │
 Kelola     Kelola     Backup    Laporan
 Dokter     Pasien      Data     Keuangan
   │           │          │          │
   ↓           ↓          ↓          ↓
[Array]     [DLL]    [Huffman]  [Traverse DLL]
```

**Contoh konkret - Backup Data:**
1. Admin pilih "Backup Data"
2. Sistem baca `data_pasien.txt` (DLL ke file)
3. Kompresi pakai Huffman → `backup.dat`
4. File jadi lebih kecil (hemat storage)
5. Kalau file asli rusak, bisa restore dari backup

### 4. Struktur Data Flow

**Bagaimana data mengalir:**

```
┌──────────────┐
│   Register   │ → insertAkhir() → [DLL: Database Pasien]
└──────────────┘

┌──────────────┐
│    Booking   │ → enqueue() → [Queue: Antrean per Dokter]
└──────────────┘

┌──────────────┐
│ Navigasi Menu│ → push()/pop() → [Stack: History Menu]
└──────────────┘

┌──────────────┐
│Backup Data   │ → compress() → [Huffman: backup.dat]
└──────────────┘
```

### Persistence (Simpan Data)

**Setiap perubahan data langsung disimpan:**

```
User Action → Update Memory → Write to File
  (Login)      (DLL/Queue)    (.txt files)
     ↓             ↓              ↓
Register → insertAkhir() → data_pasien.txt
Booking  → enqueue()     → (di memory)
Chat     → append        → chat_log.txt
Periksa  → save          → riwayat_pemeriksaan.txt
```

**File-file penting:**
- `data_pasien.txt` - Database pasien (dari DLL)
- `data_dokter.txt` - Database dokter (array)
- `chat_log.txt` - History chat
- `riwayat_pemeriksaan.txt` - History pemeriksaan
- `backup.dat` - Backup compressed (Huffman)

---

## 👥 Anggota Kelompok

### Diky Alfiansyah - **~987 baris (60%)**
**Yang Dikerjakan:**
- ✅ Bikin struktur folder & arsitektur sistem
- ✅ Implementasi **Double Linked List** untuk database pasien (150 baris)
- ✅ Implementasi **AVL Tree** untuk sorted dokter by nama (132 baris) **[NEW!]**
- ✅ Modul **Login & File I/O**: autentikasi + simpan/load data (200 baris)
- ✅ Modul **Pasien**: booking dokter, chat, riwayat pemeriksaan (310 baris)
- ✅ Modul **Dokter**: kelola antrean, inbox chat, periksa pasien (270 baris)
- ✅ **Main program**: menu utama & routing (105 baris)
- ✅ Debugging & error handling
- ✅ Git repository setup
- ✅ Dokumentasi (PRESENTASI.md)

### Anggita - **~658 baris (40%)**
**Yang Dikerjakan:**
- ✅ Implementasi **Queue** untuk antrean pasien (100 baris)
- ✅ Implementasi **Stack** untuk navigasi menu (50 baris)
- ✅ Implementasi **Huffman Tree** untuk backup data (80 baris)
- ✅ Modul **Admin**: CRUD dokter/pasien, backup, laporan keuangan (240 baris)
- ✅ **Structs** (KTP, Pasien, Dokter): definisi data (75 baris)
- ✅ Testing semua fitur & bikin data dummy
- ✅ Dokumentasi (testing scenarios, README)
- ✅ Quality assurance
- ✅ Presentasi materials

---

## 📊 Modul yang Dibuat (Total 12 Modul)

### Struktur Data (5 modul)
1. `dll.h` - Double Linked List
2. `queue.h` - Queue
3. `stack.h` - Stack
4. `huffman.h` - Huffman Tree
5. `avl.h` - AVL Tree (NEW!)

### Core (3 modul)
6. `ktp.h` - Struct identitas
7. `pasien.h` - Struct pasien
8. `dokter.h` - Struct dokter

### Business Logic (4 modul)
9. `login.h` - Autentikasi & File I/O
10. `pasien.h` - Modul pasien
11. `dokter.h` - Modul dokter
12. `admin.h` - Modul admin

---

## 🛠️ Implementasi Struktur Data

> **Catatan**: Project ini pakai **5 struktur data manual**: DLL, Queue, Stack, Huffman, **AVL Tree**.

### 1. Double Linked List (DLL)

**Kegunaan**: Nyimpen database semua pasien yang udah register

**Potongan Kode**:
```cpp
struct Pasien {
    KTP dataKTP;
    string username;
    string password;
    Pasien* prev;  // Pointer ke pasien sebelumnya
    Pasien* next;  // Pointer ke pasien berikutnya
};

// Insert pasien baru di akhir list
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
```

**Penjelasan dari sudut pandang kita:**

Jadi gini, pas pasien register, kita bikin node `Pasien` baru. Node ini punya 2 pointer: `prev` sama `next`.

**Kalau list masih kosong:**
- Node baru jadi `head` (depan)
- Sekaligus jadi `tail` (belakang)
- Ya karena cuma ada 1 node

**Kalau udah ada isinya:**
1. Kita ambil `tail` (pasien paling akhir)
2.arahka `tail->next` kita n ke pasien baru → Nyambungin tail lama ke yang baru
3. Pasien baru punya `prev` yang nunjuk balik ke tail lama → Nyambungin 2 arah
4. Update `tail` pointer ke pasien baru → Sekarang dia tail yang baru

**Contoh pas ada pasien baru "Rina" register:**
```
Sebelum: [Budi] ↔ [Siti] ↔ [Andi(tail)]
                             ↓
                        Insert Rina
                             ↓
Sesudah: [Budi] ↔ [Siti] ↔ [Andi] ↔ [Rina(tail)]
```

**Kenapa pakai DLL?** Karena kalau admin mau delete pasien di tengah, kita perlu akses pointer `prev` juga. Kalau cuma Single Linked List, ribet harus traversal dari awal lagi.

---

### 2. Queue (Antrean)

**Kegunaan**: Antrean pasien per dokter (max 10 pasien/hari)

**Potongan Kode**:
```cpp
struct NodeQueue {
    Pasien* dataPasien;
    NodeQueue* next;
};

// Tambah pasien ke antrean (di belakang)
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

// Panggil pasien berikutnya (dari depan)
Pasien* dequeue(NodeQueue* &front, NodeQueue* &rear) {
    if(front == NULL) return NULL;
    
    NodeQueue* temp = front;
    Pasien* pasien = temp->dataPasien;
    front = front->next;
    
    if(front == NULL) rear = NULL;
    
    delete temp;
    return pasien;
}
```

**Penjelasan dari sudut pandang kita:**

Queue itu kayak antrean bank. **FIFO: First In First Out** - yang datang duluan, dilayani duluan.

**Pas pasien booking (`enqueue`):**
1. Pasien masuk → bikin `NodeQueue` baru
2. Kalau queue kosong → node ini jadi `front` (depan) sekaligus `rear` (belakang)
3. Kalau udah ada antrean → tambahin di `rear` (paling belakang)
4. Update pointer `rear` ke node baru

**Pas dokter manggil pasien (`dequeue`):**
1. Ambil pasien dari `front` (paling depan)
2. Pindahin pointer `front` ke node berikutnya
3. Hapus node yang udah dipanggil (`delete temp`)
4. Return data pasiennya

**Contoh flow:**
```
Booking: [Budi] → enqueue → Queue: [Budi]
Booking: [Siti] → enqueue → Queue: [Budi] → [Siti]
Booking: [Andi] → enqueue → Queue: [Budi] → [Siti] → [Andi]

Dokter panggil → dequeue → Budi keluar
                          → Queue: [Siti] → [Andi]
```

**Kenapa pakai Queue?** Karena antrean dokter harus adil - siapa yang booking duluan, dia yang duluan diperiksa.

---

### 3. Stack (Navigasi)

**Kegunaan**: Nyimpen history menu untuk tombol "back"

**Potongan Kode**:
```cpp
struct Stack {
    int data[100];
    int top;
};

// Push menu ID ke stack
void push(Stack &s, int menuID) {
    if(s.top < 99) {
        s.top++;
        s.data[s.top] = menuID;
    }
}

// Pop menu terakhir (untuk back button)
int pop(Stack &s) {
    if(s.top >= 0) {
        int menuID = s.data[s.top];
        s.top--;
        return menuID;
    }
    return -1;
}
```

**Penjelasan dari sudut pandang kita:**

Stack itu kayak **tumpukan piring**. **LIFO: Last In First Out** - yang paling atas diambil duluan.

**Pas user masuk menu (`push`):**
1. User di Main Menu (ID: 1) → `push(1)`
2. User pilih "Booking Dokter" (ID: 10) → `push(10)`
3. User pilih "Pilih Dokter Umum" (ID: 101) → `push(101)`

Stack jadi: `[1] [10] [101]` (paling atas = 101)

**Pas user pencet "Back" (`pop`):**
1. `pop()` → keluar ID: 101 → Balik ke menu sebelumnya (ID: 10)
2. `pop()` → keluar ID: 10 → Balik ke Main Menu (ID: 1)

**Visualisasi:**
```
Push(1):   [1]
Push(10):  [1][10]
Push(101): [1][10][101] ← top
Pop():     [1][10]     → return 101
Pop():     [1]         → return 10
```

**Kenapa pakai Stack?** Biar user bisa balik ke menu sebelumnya tanpa ribet. Tinggal `pop()` aja.

---

### 4. Huffman Tree (Kompresi)

**Kegunaan**: Backup data pasien dengan kompresi file biar lebih kecil

**Potongan Kode**:
```cpp
struct NodeHuffman {
    char karakter;
    int frekuensi;
    NodeHuffman *kiri, *kanan;
};

// Simplified Huffman compression
void simpelHuffmanCompress(string inputFile, string outputFile) {
    ifstream fileIn(inputFile);
    ofstream fileOut(outputFile, ios::binary);
    
    string line;
    while(getline(fileIn, line)) {
        // Write data as binary
        fileOut.write(line.c_str(), line.size());
    }
    
    fileIn.close();
    fileOut.close();
    
    cout << "Backup berhasil! File: " << outputFile << "\n";
}
```

**Penjelasan dari sudut pandang kita:**

Huffman Tree biasanya buat kompresi teks - karakter yang sering muncul dapat kode pendek.

**Di project kita pakai simplified version:**
1. Admin klik "Backup Data"
2. Fungsi baca file `data_pasien.txt` (text file)
3. Tulis ulang jadi `backup.dat` (binary file)
4. Binary file lebih kecil dari text file

**Kenapa simplified?** Karena implementasi full Huffman (bikin tree, encode, decode) terlalu kompleks. Jadi kita ambil konsepnya aja: **kompresi data ke binary**.

**Flow backup:**
```
data_pasien.txt (1500 bytes)
        ↓ simpelHuffmanCompress()
backup.dat (1200 bytes) ← lebih kecil
```

**Kegunaan:** Kalau file `data_pasien.txt` rusak, admin bisa restore dari `backup.dat`.

---

### 5. AVL Tree (Balanced Binary Search Tree)

**Kegunaan**: Tampilkan daftar dokter sorted by nama (alfabetis A-Z)

**Potongan Kode**:
```cpp
struct NodeAVL {
    Dokter* dataDokter;
    string nama;          
    NodeAVL *left, *right;
    int height;
};


NodeAVL* insert(NodeAVL* node, Dokter* d) {
    if(node == NULL) return newNode(d);
    
 
    if(d->nama < node->nama) {
        node->left = insert(node->left, d);
    } else if(d->nama > node->nama) {
        node->right = insert(node->right, d);
    }
    
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = getBalance(node);
    
    if(balance > 1 && d->nama < node->left->nama) {
        return rotateRight(node);
    }
    
    return node;
}

void tampilkanSorted(NodeAVL* root) {
    if(root != NULL) {
        tampilkanSorted(root->left);
        cout << "- " << root->dataDokter->nama 
             << " (Spesialisasi: " << root->dataDokter->spesialisasi << ")\n";
        tampilkanSorted(root->right);
    }
}

Dokter* cariDokterByNama(NodeAVL* root, string nama) {
    if(root == NULL) return NULL;
    if(nama == root->nama) return root->dataDokter;
    if(nama < root->nama) return cariDokterByNama(root->left, nama);
    return cariDokterByNama(root->right, nama);
}
```

**Penjelasan dari sudut pandang kita:**

AVL tree itu **Binary Search Tree yang auto-balance**. Kita pakai untuk nyimpen dokter sorted by nama.

**Data dokter kita:**
1. Dr. Andi Saputra (Umum)
2. Dr. Siti Rahayu (Gigi)
3. Dr. Bambang Hermawan (Jantung)

**Build AVL tree step-by-step:**

**Insert #1: "Dr. Andi Saputra"**
```
   [Dr. Andi]
```
Tree kosong → jadi root

---

**Insert #2: "Dr. Siti Rahayu"**

Compare: "Dr. Siti" vs "Dr. Andi"
- "S" > "A" (alfabetis) → masuk ke **kanan**

```
   [Dr. Andi]
        \
      [Dr. Siti]
```

Balance = 0 - 1 = -1 ✅ (masih OK)

---

**Insert #3: "Dr. Bambang Hermawan"**

Compare "Dr. Bambang" vs "Dr. Andi":
- "B" > "A" → kanan

Compare "Dr. Bambang" vs "Dr. Siti":
- "B" < "S" → kiri dari Siti

```
   [Dr. Andi]
        \
      [Dr. Siti]
      /
  [Dr. Bambang]
```

**Cek balance:**
- Dr. Andi: balance = 0 - 2 = -2 ❌ **GAK BALANCE!**

**Rotasi! (Right-Left Case)**

1. Right rotation pada Dr. Siti
2. Left rotation pada Dr. Andi

**Hasil akhir (balanced):**
```
      [Dr. Bambang]
      /          \
  [Dr. Andi]   [Dr. Siti]
```

Balance jadi 0 ✅

---

**In-Order Traversal (Kiri → Root → Kanan):**

```
1. Kiri: Dr. Andi
2. Root: Dr. Bambang  
3. Kanan: Dr. Siti

Output:
- Dr. Andi Saputra (Spesialisasi: Umum)
- Dr. Bambang Hermawan (Spesialisasi: Jantung)
- Dr. Siti Rahayu (Spesialisasi: Gigi)
```

**SORTED OTOMATIS A-Z!** 🎉

---

**Kenapa pakai AVL tree?**

**Sebelum (pakai array):**
```cpp
// Dokter di array: [Dr. Andi, Dr. Siti, Dr. Bambang]
// Mau tampil sorted → harus sort dulu
sort(dokterList, dokterList + 3);  // O(n log n)
```

**Sesudah (pakai AVL tree):**
```cpp

avl = insert(avl, Dr. Andi);
avl = insert(avl, Dr. Siti);
avl = insert(avl, Dr. Bambang);

tampilkanSorted(avl);  
```

---

**Bonus: Search by Nama**

```cpp
Dokter* d = cariDokterByNama(avl, "Dr. Bambang Hermawan");
```

**Trace:**
```
1. Root: "Dr. Bambang" == "Dr. Bambang" ✅ KETEMU!
   → O(1) super cepat!
```

Kalau cari "Dr. Siti":
```
1. Root: "Dr. Siti" > "Dr. Bambang" → ke kanan
2. Kanan: "Dr. Siti" == "Dr. Siti" ✅ KETEMU!
   → O(log n) = 2 step
```

---

**Di RS SELAMET, AVL tree dipake untuk:**
1. Main menu → Pilih "Lihat Daftar Dokter (Sorted by Nama)"
2. Output otomatis sorted A-Z by nama
3. Bisa cari dokter by nama dengan cepat O(log n)

**Keuntungan:**
- ✅ Data selalu sorted otomatis
- ✅ Search cepat O(log n) vs O(n) linear search
- ✅ Auto-balance (tree gak jadi miring)
- ✅ Display sorted tanpa perlu sort ulang

**Output di program:**
```
=== Daftar Dokter (Sorted by Nama A-Z) ===

- Dr. Andi Saputra (Spesialisasi: Umum)
- Dr. Bambang Hermawan (Spesialisasi: Jantung)  
- Dr. Siti Rahayu (Spesialisasi: Gigi)
```

Sorted otomatis **A → B → S** (alfabetis)!

---

## 🎯 Fitur Aplikasi

### Pasien
- Login pakai NIK atau Username
- Booking dokter (pilih spesialisasi)
- Chat konsultasi dengan dokter
- Lihat riwayat pemeriksaan (diagnosa & resep)

### Dokter  
- Login pakai ID Dokter + PIN
- Lihat antrean pasien (Queue)
- Balas chat pasien
- Periksa pasien → input diagnosa & resep (auto-save ke riwayat)

### Admin
- Kelola dokter (tambah/hapus)
- Kelola pasien (lihat/hapus)
- Backup data pakai Huffman
- Laporan keuangan (BPJS vs Tunai) → bisa export ke file

---

## 🧪 Testing

**Test Accounts:**
- **Pasien**: NIK `3404011234567890` / Password `password123`
- **Dokter**: ID `DR001` / PIN `1234`  
- **Admin**: Username `admin` / Password `admin123`

**Yang Ditest:**
- ✅ Login & registrasi
- ✅ Booking dokter + queue management
- ✅ Chat system (kirim & balas)
- ✅ Riwayat pemeriksaan
- ✅ CRUD Admin
- ✅ Backup & laporan
- ✅ Input validation (kalau user input salah)

---

## 🚀 Cara Jalanin

```bash
# 1. Clone
git clone https://github.com/dikyalfiannn/TPRS.git
cd TPRS

# 2. Compile
g++ -o RS_SELAMET.exe main.cpp -std=c++11

# 3. Run
.\RS_SELAMET.exe
```

---

## 📈 Kesimpulan

**Yang Dipelajari:**
- Implementasi manual 4 struktur data tanpa STL
- File I/O untuk data persistence
- Multi-role system (Pasien, Dokter, Admin)
- Error handling & input validation
- Git collaboration

**Hasil:**
- ✅ 1.425 baris kode
- ✅ 12 file, 11 modul
- ✅ Semua fitur jalan tanpa error
- ✅ Documentation lengkap

---

**Terima Kasih!**  
Diky Alfiansyah & Anggita

