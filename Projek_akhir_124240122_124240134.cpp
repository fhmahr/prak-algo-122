#include <iostream>
#include <string>
using namespace std;

// Struktur node untuk menyimpan data trnsaksi
struct Transaksi {
    int id;
    int nominal;
    Transaksi* sebelumnya;
    Transaksi* selanjutnya;
};

// Pointer awal dan akhir linked list
Transaksi* kepala = nullptr;
Transaksi* ekor = nullptr;

// Fungsi untuk menambahkan catatan transaksi dari depan
void tambahDariDepan(int id_baru, int nominal_baru) {
    Transaksi* transaksi_baru = new Transaksi();
    transaksi_baru->id = id_baru;
    transaksi_baru->nominal = nominal_baru;
    transaksi_baru->sebelumnya = nullptr;
    transaksi_baru->selanjutnya = kepala;

    if (kepala != nullptr) {
        kepala->sebelumnya = transaksi_baru;
    } else {
        ekor = transaksi_baru;
    }

    kepala = transaksi_baru;
    cout << "Catatan transaksi berhasil ditambahkan dari depan.\n";
}

// Fungsi untuk menambahkan catatan transaksi dari belakang
void tambahDariBelakang(int id_baru, int nominal_baru) {
    Transaksi* transaksi_baru = new Transaksi();
    transaksi_baru->id = id_baru;
    transaksi_baru->nominal = nominal_baru;
    transaksi_baru->selanjutnya = nullptr;
    transaksi_baru->sebelumnya = ekor;

    if (ekor != nullptr) {
        ekor->selanjutnya = transaksi_baru;
    } else {
        kepala = transaksi_baru;
    }

    ekor = transaksi_baru;
    cout << "Catatan transaksi berhasil ditambahkan dari belakang.\n";
}

// Fungsi untuk menampilkan daftar catatan transaksi
void tampilkanCatatan() {
    if (kepala == nullptr) {
        cout << "Catatan transaksi kosong.\n";
        return;
    }

    Transaksi* sekarang = kepala;
    cout << "\n=== Daftar Buku ===\n";
    while (sekarang != nullptr) {
        cout << "Id     : " << sekarang->id << endl;
        cout << "Nominal: " << sekarang->nominal << endl;
        cout << "----------------------\n";
        sekarang = sekarang->selanjutnya;
    }
}

// Fungsi untuk mencari catatan transaksi berdasarkan id
void cariCatatan(int id_dicari) {
    if (kepala == nullptr) {
        cout << "Catatan transaksi kosong.\n";
        return;
    }

    Transaksi* sekarang = kepala;
    while (sekarang != nullptr) {
        if (sekarang->id == id_dicari) {
            cout << "Catatan ditemukan:\n";
            cout << "Id     : " << sekarang->id << endl;
            cout << "Nominal: " << sekarang->nominal << endl;
            return;
        }
        sekarang = sekarang->selanjutnya;
    }

    cout << "Catatan dengan ID '" << id_dicari << "' tidak ditemukan.\n";
}

// Fungsi untuk menghapus catatan transaksi berdasarkan id
void hapusCatatan(int id_dicari) {
    if (kepala == nullptr) {
        cout << "Catatan transaksi kosong.\n";
        return;
    }

    Transaksi* sekarang = kepala;
    while (sekarang != nullptr) {
        if (sekarang->id == id_dicari) {
            if (sekarang->sebelumnya != nullptr) {
                sekarang->sebelumnya->selanjutnya = sekarang->selanjutnya;
            } else {
                kepala = sekarang->selanjutnya;
            }

            if (sekarang->selanjutnya != nullptr) {
                sekarang->selanjutnya->sebelumnya = sekarang->sebelumnya;
            } else {
                ekor = sekarang->sebelumnya;
            }

            delete sekarang;
            cout << "Transaksi dengan ID '" << id_dicari << "' berhasil dihapus.\n";
            return;
        }
        sekarang = sekarang->selanjutnya;
    }

    cout << "Transaksi dengan ID '" << id_dicari << "' tidak ditemukan.\n";
}

// Fungsi utama program
int main() {
    int pilihan;
    int id, nominal;

    do {
        cout << "\n=== Menu Aplikasi Catatan Transaksi ===\n";
        cout << "1. Tambah Catatan dari Depan\n";
        cout << "2. Tambah Catatan dari Belakang\n";
        cout << "3. Tampilkan Catatan Transaksi\n";
        cout << "4. Cari Catatan Transaksi Berdasarkan ID\n";
        cout << "5. Hapus Catatan Transaksi berdasarkan ID\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore(); // Menghindari masalah input getline

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Transaksi   : ";
                cin >> id;
                cout << "Masukkan Jumlah Nominal : ";
                cin >> nominal;
                tambahDariDepan(id, nominal);
                break;
            case 2:
                cout << "Masukkan ID Transaksi   : ";
                cin >> id;
                cout << "Masukkan Jumlah Nominal : ";
                cin >> nominal;
                tambahDariBelakang(id, nominal);
                break;
            case 3:
                tampilkanCatatan();
                break;
            case 4:
                cout << "Masukkan ID catatan transaksi yang ingin dicari: ";
                cin >> id;
                cariCatatan(id);
                break;
            case 5:
                cout << "Masukkan Id catatan transaksi yang ingin dihapus: ";
                cin >> id;
                hapusCatatan(id);
                tampilkanCatatan();
                break;
            case 6:
                cout << "Terima kasih telah menggunakan aplikasi ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (pilihan != 6);

    return 0;
}


