#include <iostream>
#include <string>
using namespace std;

struct Buku {
    string judul;
    string penulis;
    Buku* prev;
    Buku* next;
};

Buku* head = nullptr;
Buku* tail = nullptr;

void tambahDepan(string judul, string penulis) {
    Buku* baru = new Buku{judul, penulis, nullptr, head};
    if (head != nullptr)
        head->prev = baru;
    else
        tail = baru;
    head = baru;
    cout << "Buku berhasil ditambahkan di depan.\n";
}

void tambahBelakang(string judul, string penulis) {
    Buku* baru = new Buku{judul, penulis, tail, nullptr};
    if (tail != nullptr)
        tail->next = baru;
    else
        head = baru; 
    cout << "Buku berhasil ditambahkan di belakang.\n";
}


void hapusBuku(string judul) {
    Buku* hapus = head;
    while (hapus != nullptr && hapus->judul != judul)
        hapus = hapus->next;

    if (hapus == nullptr) {
        cout << "Buku dengan judul \"" << judul << "\" tidak ditemukan.\n";
        return;
    }

    if (hapus->prev != nullptr)
        hapus->prev->next = hapus->next;
    else
        head = hapus->next;

    if (hapus->next != nullptr)
        hapus->next->prev = hapus->prev;
    else
        tail = hapus->prev;

    delete hapus;
    cout << "Buku berhasil dihapus.\n";
}

void tampilkanBuku() {
    if (head == nullptr) {
        cout << "Daftar buku kosong.\n";
        return;
    }

    Buku* bantu = head;
    cout << "\n== Daftar Buku ==\n";
    while (bantu != nullptr) {
        cout << "Judul : " << bantu->judul << "\n";
        cout << "Penulis: " << bantu->penulis << "\n";
        cout << "------------------------\n";
        bantu = bantu->next;
    }
}

int main () {
    int pilihan;
    string judul, penulis;

    do {
        cout << "\n=== Menu Daftar Buku ===\n";
        cout << "1. Tambah Buku di Depan\n";
        cout << "2. Tambah Buku di Belakang\n";
        cout << "3. Hapus Buku (berdasarkan judul)\n";
        cout << "4. Tampilkan Daftar Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Penulis: ";
                getline(cin, penulis);
                tambahDepan(judul, penulis);
                break;
            case 2:
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                cout << "Masukkan Penulis: ";
                getline(cin, penulis);
                tambahBelakang(judul, penulis);
                break;
            case 3:
                cout << "Masukkan Judul Buku yang ingin dihapus: ";
                getline(cin, judul);
                hapusBuku(judul);
                break;
            case 4:
                tampilkanBuku();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 5);
    return 0;
}

