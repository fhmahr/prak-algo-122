#include <iostream>
#include <algorithm>
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
    cout << "Masukkan judul lagu: ";
    cin.ignore();
    getline(cin, daftarlagu[jumlah].jud);
    
    cout << "Masukkan nama penyanyi: ";
    getline(cin, daftarlagu[jumlah].peny);

    cout << "Masukkan genre lagu: ";
    getline(cin, daftarlagu[jumlah].gen);

    cout << "Masukkan tahun rilis: ";
    cin >> daftarlagu[jumlah].rilis;

    jumlah++;
    cout << "Lagu berhasil ditambahkan.\n";
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
        cout << "Judul: " << daftarlagu[mid].jud << endl;
        cout << "Penyanyi: " << daftarlagu[mid].peny << endl;
        cout << "Genre: " << daftarlagu[mid].gen << endl;
        cout << "Tahun Rilis: " << daftarlagu[mid].rilis << endl;
    } else {
        cout << "Lagu tidak ditemukan.\n";
    }
}

main(){

    lagu daftarlagu[MAX_LAGU];
    int pil, jmhl;

    do  {
        //Menu
        cout << " Playlist lagu " << endl;
        cout << "===============" << endl;
        cout << "1. Tambah lagu " << endl;
        cout << "2. Cari lagu" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih Menu : " ; cin >> pil;

        //switch case
        switch (pil){
            case 1:
                tampilkanLagu(daftarlagu, jmhl);
                tambahLagu(daftarlagu, jmhl);
                break;
            case 2:
                cariLagu(daftarlagu, jmhl);
                break;
            case 3:
                
                break;
            default:
                    cout << "Input tidak dapat ditemukan" << endl;
                break;
        }
    }while (pil = 3);
    return 0;
}
