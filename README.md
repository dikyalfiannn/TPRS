# RS SELAMET - Hospital Management System

Sistem manajemen rumah sakit dengan 3 role (Pasien, Dokter, Admin) menggunakan struktur data Double Linked List, Queue, Stack, Huffman Tree).

## 🚀 Cara Menjalankan Program

### 1. Clone Repository
```bash
git clone https://github.com/dikyalfiannn/TPRS
cd TPRS
```

### 2. Compile Program
**Windows (PowerShell/CMD):**
```bash
g++ -o RS_SELAMET.exe main.cpp -std=c++11
```

### 3. Jalankan Program
**Windows:**
```bash
.\RS_SELAMET.exe
```

### 4. Menu Utama
```
========================================
          RS SELAMET
   Rumah Sakit Digital Terpercaya
========================================
1. Login Pasien
2. Login Dokter
3. Login Admin
4. Registrasi Pasien Baru
5. Keluar
```

---

## 👥 Testing Accounts

### 🔐 Admin Account
- **Username**: `admin`
- **Password**: `admin123`
- **Akses**: Full access (kelola dokter, pasien, backup data, laporan)

---

### 👨‍⚕️ Dokter Accounts

#### 1. Dr. Andi Saputra (Dokter Umum)
- **ID Dokter**: `DR001`
- **PIN**: `1234`
- **Spesialisasi**: Umum
- **Kuota**: 10 pasien/hari

#### 2. Dr. Siti Rahayu (Dokter Gigi)
- **ID Dokter**: `DR002`
- **PIN**: `5678`
- **Spesialisasi**: Gigi
- **Kuota**: 10 pasien/hari

#### 3. Dr. Bambang Hermawan (Dokter Jantung)
- **ID Dokter**: `DR003`
- **PIN**: `9012`
- **Spesialisasi**: Jantung
- **Kuota**: 10 pasien/hari

---

### 🧑‍💼 Pasien Accounts

#### 1. Budi Santoso
- **NIK**: `3404011234567890`
- **Username**: `budi88`
- **Password**: `password123`
- **BPJS**: `0001234567890`

#### 2. Siti Nurhaliza
- **NIK**: `3404019876543210`
- **Username**: `siti99`
- **Password**: `siti2024`
- **BPJS**: `0009876543210`

#### 3. Andi Wijaya
- **NIK**: `3404015555666777`
- **Username**: `andi_wijaya`
- **Password**: `andi123`
- **BPJS**: -

#### 4. Rina Dewi
- **NIK**: `3404012233445566`
- **Username**: `rina_dewi`
- **Password**: `rina456`
- **BPJS**: `0002233445566`

#### 5. Joko Prabowo
- **NIK**: `3404018899001122`
- **Username**: `joko_prabowo`
- **Password**: `joko789`
- **BPJS**: -

---

## 🧪 Testing Scenarios

### Scenario 1: Login Pasien
1. Pilih menu **"1. Login Pasien"**
2. Input NIK: `3404011234567890` **ATAU** Username: `budi88`
3. Input Password: `password123`
4. ✅ Berhasil masuk dashboard Budi Santoso

### Scenario 2: Booking Dokter
1. Login sebagai Budi (NIK: `3404011234567890`)
2. Pilih **"1. Booking Dokter"**
3. Pilih dokter yang diinginkan
4. Pilih metode pembayaran (BPJS/Tunai)
5. ✅ Dapat tiket antrean digital

### Scenario 3: Chat Dokter
1. Login sebagai pasien
2. Pilih **"2. Chat Dokter"**
3. Pilih spesialisasi → Pilih dokter
4. Ketik pesan konsultasi
5. ✅ Pesan tersimpan dan bisa dibalas dokter

### Scenario 4: Dokter Periksa Pasien
1. Login sebagai Dr. Andi (ID: `DR001`, PIN: `1234`)
2. Pilih **"3. Panggil Pasien Berikutnya"**
3. Input diagnosa dan resep obat
4. ✅ Riwayat pemeriksaan tersimpan

### Scenario 5: Admin Backup Data
1. Login Admin (user: `admin`, pass: `admin123`)
2. Pilih **"3. Backup Data (Huffman)"**
3. ✅ File `backup.dat` terbuat di folder `data/`

---

## 📁 File Structure

```
TPRS/
├── common/              # Struct dasar (KTP, Pasien, Dokter)
│   ├── ktp.h
│   ├── pasien.h
│   └── dokter.h
│
├── datastructure/       # Struktur data manual
│   ├── dll.h           # Double Linked List
│   ├── queue.h         # Queue (FIFO)
│   ├── stack.h         # Stack (navigasi)
│   └── huffman.h       # Huffman Tree (kompresi)
│
├── login/              # Sistem autentikasi
│   └── login.h
│
├── pasien/             # Modul pasien
│   └── pasien.h
│
├── dokter/             # Modul dokter
│   └── dokter.h
│
├── admin/              # Modul admin
│   └── admin.h
│
├── data/               # Data persistence
│   ├── data_pasien.txt
│   ├── data_dokter.txt
│   ├── chat_log.txt
│   ├── riwayat_pemeriksaan.txt
│   └── backup.dat
│
├── main.cpp            # Entry point
├── testing_accounts.md # Detail akun testing
└── README.md          # Dokumentasi
```

