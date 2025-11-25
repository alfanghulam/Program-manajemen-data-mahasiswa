#include <iostream>
#include <string>
#include <iomanip> // untuk setprecision
using namespace std;

// ==== Data Mata Kuliah per Prodi ====
struct Matkul {
    string nama;
    int sks;
};

// PTI
Matkul PTI[3] = {
    {"Algoritma", 3},
    {"Pemrograman", 3},
    {"Basis Data", 3}
};

// TI
Matkul TI[3] = {
    {"Jaringan Komputer", 3},
    {"Sistem Operasi", 3},
    {"Pemrograman Web", 3}
};

// PTE
Matkul PTE[3] = {
    {"Rangkaian Listrik", 3},
    {"Elektronika Dasar", 3},
    {"Robotika", 3}
};

// ==== DATA MAHASISWA ====
struct Mahasiswa {
    string nama;
    string nim;
    int prodi;
    float nilaiMatkul[10];
    int kodeMatkul[10];
    int jumlahMatkul;
    float ipk;
};

Mahasiswa mhs[100];
int jumlahData = 0;

// ==== KONVERSI NILAI ====
float konversiBobot(float nilai) {      //fungsi//
    if (nilai >= 85) return 4.0;//percabangan//
    else if (nilai >= 75) return 3.0;
    else if (nilai >= 65) return 2.0;
    else if (nilai >= 50) return 1.0;
    return 0.0;
}

// ==== HITUNG IPK ====
float hitungIPK(Mahasiswa &m) {    //fungsi hitung mahasiswa//
    float totalBobot = 0;
    int totalSKS = 0;
    Matkul *mk;

    if (m.prodi == 1) mk = PTI;
    else if (m.prodi == 2) mk = TI;
    else if (m.prodi == 3) mk = PTE;
    else return 0.0; // prodi tidak valid

    for (int i = 0; i < m.jumlahMatkul; i++) {
        int idx = m.kodeMatkul[i];
        if (idx >= 0 && idx < 3) { // validasi index
            float bobot = konversiBobot(m.nilaiMatkul[i]);
            totalBobot += bobot * mk[idx].sks;
            totalSKS += mk[idx].sks;
        }
    }
    
    if (totalSKS == 0) return 0.0; 
    return totalBobot / totalSKS;
}

// ==== TAMPIL PRODI ====
string getNamaProdi(int prodi) {
    if (prodi == 1) return "PTI";
    else if (prodi == 2) return "TI";
    else if (prodi == 3) return "PTE";
    else return "Tidak Diketahui";
}

// ==== TAMBAH DATA ====
void tambahData() {
    if (jumlahData >= 100) {
        cout << "\nKapasitas data penuh!\n";
        return;
    }

    Mahasiswa &m = mhs[jumlahData];

    cout << "\nNama: ";
    cin.ignore();
    getline(cin, m.nama);

    cout << "NIM: ";
    cin >> m.nim;

    // Validasi NIM unik
    for (int i = 0; i < jumlahData; i++) { //perulangan//
        if (mhs[i].nim == m.nim) {
            cout << "NIM sudah terdaftar!\n";
            return;
        }
    }

    cout << "Pilih Prodi:\n1. PTI\n2. TI\n3. PTE\nPilih: ";
    cin >> m.prodi;

    if (m.prodi < 1 || m.prodi > 3) {
        cout << "Pilihan prodi tidak valid!\n";
        return;
    }

    Matkul *mk;
    if (m.prodi == 1) mk = PTI;
    else if (m.prodi == 2) mk = TI;
    else mk = PTE;

    m.jumlahMatkul = 0;
    int pilihMK;
    bool matkulDipilih[3] = {false}; // untuk mencegah duplikasi mata kuliah

    cout << "\n=== PILIH MATA KULIAH UNTUK INPUT NILAI ===\n";

    do {
        cout << "\nDaftar Mata Kuliah:\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". " << mk[i].nama
                 << " (SKS: " << mk[i].sks << ")";
            if (matkulDipilih[i]) cout << " [SUDAH DIPILIH]";
            cout << endl;
        }
        cout << "0. Selesai\n";

        cout << "Pilih mata kuliah: ";
        cin >> pilihMK;

        if (pilihMK >= 1 && pilihMK <= 3) {
            int index = pilihMK - 1;
            
            if (matkulDipilih[index]) {
                cout << "Mata kuliah ini sudah dipilih!\n";
                continue;
            }

            m.kodeMatkul[m.jumlahMatkul] = index;
            cout << "Nilai untuk " << mk[index].nama << ": ";
            cin >> m.nilaiMatkul[m.jumlahMatkul];
            
            // Validasi nilai
            if (m.nilaiMatkul[m.jumlahMatkul] < 0 || m.nilaiMatkul[m.jumlahMatkul] > 100) {
                cout << "Nilai harus antara 0-100!\n";
                continue;
            }

            matkulDipilih[index] = true;
            m.jumlahMatkul++;
            cout << "Mata kuliah berhasil ditambahkan!\n";
        }
        else if (pilihMK != 0) {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihMK != 0 && m.jumlahMatkul < 10);

    m.ipk = hitungIPK(m);        //pemanggilan pilihmk//
    jumlahData++;
    cout << "\nData berhasil ditambahkan!\n";
}

// ==== TAMPIL DATA ====
void tampilData() {
    cout << "\n=== DATA MAHASISWA ===\n";
    if (jumlahData == 0) {
        cout << "Belum ada data.\n";
        return;
    }

    cout << fixed << setprecision(2);
    for (int i = 0; i < jumlahData; i++) {
        cout << i+1 << ". " << mhs[i].nama 
             << " | NIM: " << mhs[i].nim
             << " | Prodi: " << getNamaProdi(mhs[i].prodi)
             << " | IPK: " << mhs[i].ipk << endl;
    }
}

// ==== EDIT DATA ====
void editData() {
    if (jumlahData == 0) {
        cout << "\nBelum ada data untuk diedit!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan NIM yang ingin diedit: ";
    cin >> cari;

    int idx = -1;
    for (int i = 0; i < jumlahData; i++) {
        if (mhs[i].nim == cari) { 
            idx = i; 
            break; 
        }
    }

    if (idx == -1) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    Mahasiswa &m = mhs[idx];
    int pilih;

    do {
        cout << "\n=== MENU EDIT ===\n";       //loop//
        cout << "Data saat ini:\n";
        cout << "Nama: " << m.nama << endl;
        cout << "NIM: " << m.nim << endl;
        cout << "Prodi: " << getNamaProdi(m.prodi) << endl;
        cout << "IPK: " << fixed << setprecision(2) << m.ipk << endl;
        
        cout << "\n1. Edit Nama\n";
        cout << "2. Edit NIM\n";
        cout << "3. Edit Prodi\n";
        cout << "4. Edit Nilai Mata Kuliah\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1: {
                cin.ignore();
                cout << "Nama baru: ";
                getline(cin, m.nama);
                cout << "Nama berhasil diubah!\n";
                break;
            }
            case 2: {
                string nimBaru;
                cout << "NIM baru: ";
                cin >> nimBaru;
                
                // Validasi NIM unik
                bool nimExist = false;
                for (int i = 0; i < jumlahData; i++) {
                    if (i != idx && mhs[i].nim == nimBaru) {
                        nimExist = true;
                        break;
                    }
                }
                
                if (nimExist) {
                    cout << "NIM sudah terdaftar!\n";
                } else {
                    m.nim = nimBaru;
                    cout << "NIM berhasil diubah!\n";
                }
                break;
            }
            case 3: {
                cout << "Prodi baru (1=PTI, 2=TI, 3=PTE): ";
                int prodiBaru;
                cin >> prodiBaru;
                
                if (prodiBaru >= 1 && prodiBaru <= 3) {
                    m.prodi = prodiBaru;
                    m.ipk = hitungIPK(m); // hitung ulang IPK karena prodi berubah
                    cout << "Prodi berhasil diubah!\n";
                } else {
                    cout << "Pilihan prodi tidak valid!\n";
                }
                break;
            }
            case 4: {
                Matkul *mk;
                if (m.prodi == 1) mk = PTI;
                else if (m.prodi == 2) mk = TI;
                else mk = PTE;

                cout << "\n=== EDIT NILAI ===\n";
                for (int i = 0; i < m.jumlahMatkul; i++) {
                    int kode = m.kodeMatkul[i];
                    cout << (i+1) << ". " << mk[kode].nama << " : ";
                    float nilai;
                    cin >> nilai;
                    
                    // Validasi nilai
                    if (nilai >= 0 && nilai <= 100) {
                        m.nilaiMatkul[i] = nilai;
                    } else {
                        cout << "Nilai tidak valid, tetap menggunakan nilai sebelumnya.\n";
                    }
                }
                m.ipk = hitungIPK(m);
                cout << "Nilai berhasil diperbarui!\n";
                break;
            }
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);
}

// ==== CARI DATA ====
void cariData() {
    if (jumlahData == 0) {
        cout << "\nBelum ada data untuk dicari!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan NIM yang dicari: ";
    cin >> cari;

    bool found = false;

    for (int i = 0; i < jumlahData; i++) {
        if (mhs[i].nim == cari) {
            Matkul *mk;
            if (mhs[i].prodi == 1) mk = PTI;
            else if (mhs[i].prodi == 2) mk = TI;
            else mk = PTE;

            cout << "\n=== DATA DITEMUKAN ===\n";
            cout << "Nama  : " << mhs[i].nama << endl;
            cout << "NIM   : " << mhs[i].nim << endl;
            cout << "Prodi : " << getNamaProdi(mhs[i].prodi) << endl;
            cout << "IPK   : " << fixed << setprecision(2) << mhs[i].ipk << endl;

            cout << "\nNilai Mata Kuliah:\n";
            for (int j = 0; j < mhs[i].jumlahMatkul; j++) {
                int idx = mhs[i].kodeMatkul[j];
                cout << "- " << mk[idx].nama
                     << " : " << mhs[i].nilaiMatkul[j] 
                     << " (Bobot: " << konversiBobot(mhs[i].nilaiMatkul[j]) << ")" << endl;
            }

            found = true;
            break; // keluar setelah menemukan pertama
        }
    }

    if (!found) cout << "Data tidak ditemukan!\n";
}

// ==== HAPUS DATA ====
void hapusData() {
    if (jumlahData == 0) {
        cout << "\nBelum ada data untuk dihapus!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan NIM yang dihapus: ";
    cin >> cari;

    for (int i = 0; i < jumlahData; i++) {
        if (mhs[i].nim == cari) {
            // Konfirmasi penghapusan
            cout << "Apakah Anda yakin ingin menghapus data " << mhs[i].nama << " (NIM: " << mhs[i].nim << ")? (y/n): ";
            char konfirmasi;
            cin >> konfirmasi;
            
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                for (int j = i; j < jumlahData - 1; j++) {
                    mhs[j] = mhs[j + 1];
                }
                jumlahData--;
                cout << "Data berhasil dihapus!\n";
            } else {
                cout << "Penghapusan dibatalkan.\n";
            }
            return;
        }
    }
    cout << "Data tidak ditemukan!\n";
}

// ==== MENU UTAMA ====
int main() {
    int pilih;
    
    cout << "===================================\n";
    cout << "   SISTEM MANAJEMEN MAHASISWA\n";
    cout << "===================================\n";
    
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampil Semua Data\n";
        cout << "3. Cari Data Berdasarkan NIM\n";
        cout << "4. Edit Data Mahasiswa\n";
        cout << "5. Hapus Data Mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: cariData(); break;
            case 4: editData(); break;
            case 5: hapusData(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}
