# Testing Accounts - RS SELAMET

## Admin Account
- **Username**: `admin`
- **Password**: `admin123`
- **Akses**: Full access (kelola dokter, pasien, backup data, laporan)

---

## Dokter Accounts

### 1. Dr. Andi Saputra (Dokter Umum)
- **ID Dokter**: `DR001`
- **PIN**: `1234`
- **Spesialisasi**: Umum
- **Kuota**: 10 pasien/hari

### 2. Dr. Siti Rahayu (Dokter Gigi)
- **ID Dokter**: `DR002`
- **PIN**: `5678`
- **Spesialisasi**: Gigi
- **Kuota**: 10 pasien/hari

### 3. Dr. Bambang Hermawan (Dokter Jantung)
- **ID Dokter**: `DR003`
- **PIN**: `9012`
- **Spesialisasi**: Jantung
- **Kuota**: 10 pasien/hari

---

## Pasien Accounts

### 1. Budi Santoso
- **NIK**: `3404011234567890`
- **Username**: `budi88`
- **Password**: `password123`
- **BPJS**: `0001234567890`
- **Alamat**: Jl. Merdeka No. 10 Jakarta Pusat
- **Status**: Kawin, Karyawan Swasta

### 2. Siti Nurhaliza
- **NIK**: `3404019876543210`
- **Username**: `siti99`
- **Password**: `siti2024`
- **BPJS**: `0009876543210`
- **Alamat**: Jl. Sudirman No. 25 Bandung
- **Status**: Belum Kawin, Guru SD

### 3. Andi Wijaya
- **NIK**: `3404015555666777`
- **Username**: `andi_wijaya`
- **Password**: `andi123`
- **BPJS**: Tidak ada (Bayar Tunai)
- **Alamat**: Jl. Pahlawan No. 5 Surabaya
- **Status**: Kawin, Wiraswasta

### 4. Rina Dewi
- **NIK**: `3404012233445566`
- **Username**: `rina_dewi`
- **Password**: `rina456`
- **BPJS**: `0002233445566`
- **Alamat**: Jl. Malioboro No. 15 Yogyakarta
- **Status**: Belum Kawin, Pegawai Negeri

### 5. Joko Prabowo
- **NIK**: `3404018899001122`
- **Username**: `joko_prabowo`
- **Password**: `joko789`
- **BPJS**: Tidak ada (Bayar Tunai)
- **Alamat**: Jl. Pemuda No. 100 Semarang
- **Status**: Kawin, Dokter

---

## Testing Scenarios

### Scenario 1: Login Pasien
1. Pilih menu "Login Pasien"
2. Input NIK: `3404011234567890` ATAU Username: `budi88`
3. Input Password: `password123`
4. ✅ Berhasil masuk dashboard Budi Santoso

### Scenario 2: Booking Dokter
1. Login sebagai Budi (NIK: `3404011234567890`)
2. Pilih "Booking Dokter"
3. Pilih Dr. Andi (Umum)
4. Pilih metode BPJS
5. ✅ Dapat tiket antrean

### Scenario 3: Chat Dokter
1. Login sebagai pasien
2. Pilih "Chat Dokter"
3. Input ID Dokter: `DR001`
4. Ketik pesan
5. ✅ Pesan tersimpan di chat_log.txt

### Scenario 4: Dokter Balas Chat
1. Login sebagai Dr. Andi (ID: `DR001`, PIN: `1234`)
2. Pilih "Inbox Chat"
3. Pilih nomor pesan yang belum dibalas
4. Ketik balasan
5. ✅ Balasan tersimpan

### Scenario 5: Admin Backup Data
1. Login Admin (user: `admin`, pass: `admin123`)
2. Pilih "Backup Data (Huffman)"
3. ✅ File `backup.dat` terbuat di folder `data/`

---

## File Structure
```
TPRS/
├── common/
│   ├── ktp.h
│   ├── pasien.h
│   └── dokter.h
├── datastructure/
│   ├── dll.h
│   ├── queue.h
│   ├── stack.h
│   └── huffman.h
├── login/
│   └── login.h
├── pasien/
│   └── pasien.h
├── dokter/
│   └── dokter.h
├── admin/
│   └── admin.h
├── data/
│   ├── data_pasien.txt
│   ├── data_dokter.txt
│   ├── chat_log.txt
│   └── backup.dat (created after backup)
└── main.cpp
```
