#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

const int MAX_LAGU = 100;

struct lagu {
    string jud, peny, gen;
    int rilis;
};

void tampilkanLagu(lagu daftarlagu[], int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada lagu yang ditambahkan.\n";
        return;
    }
    cout << "Daftar Lagu:\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << daftarlagu[i].jud << " - " << daftarlagu[i].peny << endl;
    }
}

void tambahLagu(lagu daftarlagu[], int &jumlah) {
    if (jumlah >= MAX_LAGU) {
        cout << "Penyimpanan lagu penuh!\n";
        return;
    }

    tampilkanLagu(daftarlagu, jumlah);

    cout << "Masukkan judul lagu    : ";
    cin.ignore();
    getline(cin, daftarlagu[jumlah].jud);
    
    cout << "Masukkan nama penyanyi : ";
    getline(cin, daftarlagu[jumlah].peny);

    cout << "Masukkan genre lagu    : ";
    getline(cin, daftarlagu[jumlah].gen);

    cout << "Masukkan tahun rilis   : ";
    cin >> daftarlagu[jumlah].rilis;

    jumlah++;
    cout << "Lagu berhasil ditambahkan.\n";
}

void editLagu(lagu daftarlagu[], int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada lagu untuk diedit.\n";
        return;
    }

    tampilkanLagu(daftarlagu, jumlah);
    
    int nomor;
    cout << "\nMasukkan nomor lagu yang ingin diedit (1-" << jumlah << "): ";
    cin >> nomor;
    
    if (nomor < 1 || nomor > jumlah) {
        cout << "Nomor lagu tidak valid!\n";
        return;
    }
    
    int index = nomor - 1;
    cout << "\nEdit data lagu '" << daftarlagu[index].jud << "':\n";
    
    cout << "Masukkan judul lagu baru   : ";
    cin.ignore();
    getline(cin, daftarlagu[index].jud);
    
    cout << "Masukkan nama penyanyi baru: ";
    getline(cin, daftarlagu[index].peny);
    
    cout << "Masukkan genre lagu baru   : ";
    getline(cin, daftarlagu[index].gen);
    
    cout << "Masukkan tahun rilis baru  : ";
    cin >> daftarlagu[index].rilis;
    
    cout << "Lagu berhasil diedit.\n";
}

void cariLagu(lagu daftarlagu[], int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada lagu untuk dicari.\n";
        return;
    }

    sort(daftarlagu, daftarlagu + jumlah, [](lagu a, lagu b) {
        return a.jud < b.jud;
    });

    cout << "Masukkan judul lagu yang dicari: ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    int left = 0, right = jumlah - 1, mid;
    bool ditemukan = false;

    while (left <= right) {
        mid = (left + right) / 2;
        if (daftarlagu[mid].jud == keyword) {
            ditemukan = true;
            break;
        } else if (daftarlagu[mid].jud < keyword) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (ditemukan) {
        cout << "Lagu ditemukan : " << endl;
        cout << "Judul      : " << daftarlagu[mid].jud << endl;
        cout << "Penyanyi   : " << daftarlagu[mid].peny << endl;
        cout << "Genre      : " << daftarlagu[mid].gen << endl;
        cout << "Tahun Rilis: " << daftarlagu[mid].rilis << endl;
    } else {
        cout << "Lagu tidak ditemukan.\n";
    }
}

void simpanKeFile(lagu daftarlagu[], int jumlah) {
    ofstream file("playlist.dat", ios::binary);
    if (!file) {
        cout << "Error: Gagal membuka file untuk menyimpan data.\n";
        return;
    }
    file.write(reinterpret_cast<char*>(&jumlah), sizeof(jumlah));
    file.write(reinterpret_cast<char*>(daftarlagu), jumlah * sizeof(lagu));
    file.close();
    cout << "Data berhasil disimpan ke file.\n";
}

void bacaDariFile(lagu daftarlagu[], int &jumlah) {
    ifstream file("playlist.dat", ios::binary);
    if (!file) {
        cout << "File playlist belum ada.\n";
        jumlah = 0;
        return;
    }
    file.read(reinterpret_cast<char*>(&jumlah), sizeof(jumlah));
    file.read(reinterpret_cast<char*>(daftarlagu), jumlah * sizeof(lagu));
    file.close();
    cout << "Data berhasil dimuat dari file.\n";
}

main(){

    lagu daftarlagu[MAX_LAGU];
    int pil, jmhl;

    bacaDariFile(daftarlagu, jmhl);

    do  {
        //Menu
        cout << " Playlist lagu " << endl;
        cout << "===============" << endl;
        cout << "1. Tampilkan lagu" << endl;
        cout << "2. Tambah lagu" << endl;
        cout << "3. Edit lagu" << endl;
        cout << "4. Cari lagu" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Menu : " ; cin >> pil;

        //switch case
        switch (pil){
            case 1:
                tampilkanLagu(daftarlagu, jmhl);
                break;
            case 2:
                tambahLagu(daftarlagu, jmhl);
                break;
            case 3:
                editLagu(daftarlagu, jmhl);
                break;
            case 4:
                cariLagu(daftarlagu, jmhl);
                break;
            case 5:
                simpanKeFile(daftarlagu, jmhl);
                cout << "Terima kasih telah menggunakan aplikasi ini" << endl;
                break;
            default:
                    cout << "Input tidak dapat ditemukan" << endl;
                break;
        }
    }while (pil != 5);
    return 0;
}
