#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Masuk{
    int id;
    std::string tanggal;
    int nominal;
    string berita;
    Masuk *sebelumnya;
    Masuk *selanjutnya;
};

Masuk *kepala1 = nullptr;
Masuk *ekor1 = nullptr;

struct Keluar{
    int id;
    std::string tanggal;
    int nominal;
    string berita;
    Keluar *sebelumnya;
    Keluar *selanjutnya;
};

Keluar *kepala2 = nullptr;
Keluar *ekor2 = nullptr;

void tambahMasuk(int id_baru, int nominal_baru, const std::string &tanggal_baru, string berita_baru){
    Masuk *masuk_baru = new Masuk();
    masuk_baru->id = id_baru;
    masuk_baru->nominal = nominal_baru;
    masuk_baru->tanggal = tanggal_baru;
    masuk_baru->berita = berita_baru;
    masuk_baru->sebelumnya = nullptr;
    masuk_baru->selanjutnya = kepala1;

    if (kepala1 != nullptr){
        kepala1->sebelumnya = masuk_baru;
    }else{
        ekor1 = masuk_baru;
    }

    kepala1 = masuk_baru;
    cout << "Catatan transaksi masuk berhasil ditambahkan.\n";
}

void tambahKeluar(int id_baru, int nominal_baru, const std::string &tanggal_baru, string berita_baru){
    Keluar *keluar_baru = new Keluar();
    keluar_baru->id = id_baru;
    keluar_baru->nominal = nominal_baru;
    keluar_baru->tanggal = tanggal_baru;
    keluar_baru->berita = berita_baru;
    keluar_baru->sebelumnya = nullptr;
    keluar_baru->selanjutnya = kepala2;

    if (kepala2 != nullptr){
        kepala2->sebelumnya = keluar_baru;
    }else{
        ekor2 = keluar_baru;
    }

    kepala2 = keluar_baru;
    cout << "Catatan transaksi keluar berhasil ditambahkan.\n";
}

int tanggalkeInt(const string &tanggal){
    int dd, mm, yyyy;
    char sep1, sep2;
    istringstream iss(tanggal);
    iss >> dd >> sep1 >> mm >> sep2 >> yyyy;
    return yyyy * 10000 + mm * 100 + dd;
}

void masuksortByTanggal(){
    if (kepala1 == nullptr || kepala1->selanjutnya == nullptr){
        return;
    }
    bool swapped;
    do{ swapped = false;
        Masuk *sekarang = kepala1;

        while (sekarang->selanjutnya != nullptr){
            int tgl1 = tanggalkeInt(sekarang->tanggal);
            int tgl2 = tanggalkeInt(sekarang->selanjutnya->tanggal);


            if (tgl1 < tgl2){
                swap(sekarang->id, sekarang->selanjutnya->id);
                swap(sekarang->nominal, sekarang->selanjutnya->nominal);
                swap(sekarang->tanggal, sekarang->selanjutnya->tanggal);
                swap(sekarang->berita, sekarang->selanjutnya->berita);
                swapped = true;
            }
            sekarang = sekarang->selanjutnya;
        }
    } while (swapped);
}

void tampilDataMasuk(){
    if (kepala1 == nullptr){
        cout << "Tidak ada data transaksi masuk.\n";
        return;
    }

    Masuk *sekarang = kepala1;
    cout << "\n=== Daftar Transaksi Masuk (Terurut Tanggal Terbaru) ===\n";
    while (sekarang != nullptr){
        cout << "ID       : " << sekarang->id << endl;
        cout << "Tanggal  : " << sekarang->tanggal << endl;
        cout << "Nominal  : " << sekarang->nominal << endl;
        cout << "Berita   : " << sekarang->berita << endl;
        cout << "-----------------------------\n";
        sekarang = sekarang->selanjutnya;
    }
}

void keluarsortByTanggal(){
    if (kepala2 == nullptr || kepala2->selanjutnya == nullptr){
    return; 
    }
    bool swapped;
    do{
        swapped = false;
        Keluar *sekarang = kepala2;

        while (sekarang->selanjutnya != nullptr)
        {
            int tgl1 = tanggalkeInt(sekarang->tanggal);
            int tgl2 = tanggalkeInt(sekarang->selanjutnya->tanggal);

            if (tgl1 < tgl2)
            {
                swap(sekarang->id, sekarang->selanjutnya->id);
                swap(sekarang->nominal, sekarang->selanjutnya->nominal);
                swap(sekarang->tanggal, sekarang->selanjutnya->tanggal);
                swap(sekarang->berita, sekarang->selanjutnya->berita);
                swapped = true;
            }
            sekarang = sekarang->selanjutnya;
        }
    } while (swapped);
}

void tampilDataKeluar(){
    if (kepala2 == nullptr){
        cout << "Tidak ada data transaksi keluar.\n";
        return;
    }

    Keluar *sekarang = kepala2;
    cout << "\n=== Daftar Transaksi Keluar ===\n";
    while (sekarang != nullptr){
        cout << "ID       : " << sekarang->id << endl;
        cout << "Tanggal  : " << sekarang->tanggal << endl;
        cout << "Nominal  : " << sekarang->nominal << endl;
        cout << "Berita   : " << sekarang->berita << endl;
        cout << "-----------------------------\n";
        sekarang = sekarang->selanjutnya;
    }
}

int hitungTotalMasuk(){
    Masuk *sekarang = kepala1;
    int total = 0;
    while (sekarang != nullptr){
        total += sekarang->nominal;
        sekarang = sekarang->selanjutnya;
    }
    return total;
}

int hitungTotalKeluar(){
    Keluar *sekarang = kepala2;
    int total = 0;
    while (sekarang != nullptr){
        total += sekarang->nominal;
        sekarang = sekarang->selanjutnya;
    }
    return total;
}

int hitungSimpanan(){
    return hitungTotalMasuk() - hitungTotalKeluar();
}

int hitungTotalMasukTahun(const string &tahunCari){
    Masuk *sekarang = kepala1;
    int total = 0;
    while (sekarang != nullptr){
        if (sekarang->tanggal.substr(6, 4) == tahunCari){
            total += sekarang->nominal;
        }
        sekarang = sekarang->selanjutnya;
    }
    return total;
}

int hitungTotalKeluarTahun(const string &tahunCari){
    Keluar *sekarang = kepala2;
    int total = 0;
    while (sekarang != nullptr){
        if (sekarang->tanggal.substr(6, 4) == tahunCari){
            total += sekarang->nominal;
        }
        sekarang = sekarang->selanjutnya;
    }
    return total;
}

void tampilSimpanan(){
    cout << "\n=== Rangkuman Simpanan Saat Ini ===\n";
    int totalMasuk = hitungTotalMasuk();
    int totalKeluar = hitungTotalKeluar();
    int saldo = hitungSimpanan();

    cout << "Total Masuk   : " << totalMasuk << endl;
    cout << "Total Keluar  : " << totalKeluar << endl;
    cout << "Saldo / Simpanan: " << saldo << endl;

    int pilihan;
    string tahunCari;

do{ cout << "Apakah anda ingin mengecek data Transaksi Tahunan Anda?" << endl;
    cout << "1. Ya" << endl;
    cout << "2. Tidak" << endl;
    cout << "Masukkan Pilihan Anda (1-2): ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan){
    case 1: {
        cout << "\nMasukkan tahun yang ingin dicek (yyyy): ";
        cin >> tahunCari;

        int masukTahun = hitungTotalMasukTahun(tahunCari);
        int keluarTahun = hitungTotalKeluarTahun(tahunCari);

        cout << "\n=== Transaksi Tahun " << tahunCari << " ===\n";
        cout << "Total Masuk Tahun " << tahunCari << " : " << masukTahun << endl;
        cout << "Total Keluar Tahun " << tahunCari << " : " << keluarTahun << endl;
        cout << "Sisa Simpanan Tahun " << tahunCari << " : " << masukTahun - keluarTahun << endl;
        break;
    }
    case 2:
        break;
    default:
        cout << "Pilihan tidak valid.\n";
        break;
    }
} while (pilihan != 2);
}


void cariCatatanMasuk(){
    if (kepala1 == nullptr){
        cout << "Belum ada data transaksi masuk.\n";
        return;
    }

    int idCari;
    cout << "Masukkan ID transaksi masuk yang ingin dicari: ";
    cin >> idCari;

    Masuk* sekarang = kepala1;
    bool ditemukan = false;

    while (sekarang != nullptr){
        if (sekarang->id == idCari) {
            cout << "\n=== Catatan Transaksi Masuk Ditemukan ===\n";
            cout << "ID       : " << sekarang->id << endl;
            cout << "Tanggal  : " << sekarang->tanggal << endl;
            cout << "Nominal  : " << sekarang->nominal << endl;
            cout << "Berita   : " << sekarang->berita << endl;
            ditemukan = true;
            break;
        }
        sekarang = sekarang->selanjutnya;
    }
    if (!ditemukan) {
        cout << "Catatan dengan ID " << idCari << " tidak ditemukan di transaksi masuk.\n";
    }
}

void cariCatatanKeluar(){
    if (kepala2 == nullptr){
        cout << "Belum ada data transaksi keluar.\n";
        return;
    }

    int idCari;
    cout << "Masukkan ID transaksi keluar yang ingin dicari: ";
    cin >> idCari;

    Keluar* sekarang = kepala2;
    bool ditemukan = false;

    while (sekarang != nullptr){
        if (sekarang->id == idCari){
            cout << "\n=== Catatan Transaksi Keluar Ditemukan ===\n";
            cout << "ID       : " << sekarang->id << endl;
            cout << "Tanggal  : " << sekarang->tanggal << endl;
            cout << "Nominal  : " << sekarang->nominal << endl;
            cout << "Berita   : " << sekarang->berita << endl;
            ditemukan = true;
            break;
        }
        sekarang = sekarang->selanjutnya;
    }

    if (!ditemukan){
        cout << "Catatan dengan ID " << idCari << " tidak ditemukan di transaksi keluar.\n";
    }
}

void hapusCatatanMasuk(int idHapus){
    if (kepala1 == nullptr){
        cout << "Data transaksi masuk kosong.\n";
        return;
    }

    Masuk* sekarang = kepala1;

    while (sekarang != nullptr){
        if (sekarang->id == idHapus){
            if (sekarang->sebelumnya != nullptr){
                sekarang->sebelumnya->selanjutnya = sekarang->selanjutnya;
            }else{
                kepala1 = sekarang->selanjutnya;
            }
            if (sekarang->selanjutnya != nullptr){
                sekarang->selanjutnya->sebelumnya = sekarang->sebelumnya;
            }else{
                ekor1 = sekarang->sebelumnya;
            }
            delete sekarang;
            cout << "Catatan transaksi masuk dengan ID " << idHapus << " berhasil dihapus.\n";
            return;
        }
        sekarang = sekarang->selanjutnya;
    }

    cout << "Catatan dengan ID " << idHapus << " tidak ditemukan di transaksi masuk.\n";
}

void hapusCatatanKeluar(int idHapus){
    if (kepala2 == nullptr){
        cout << "Data transaksi keluar kosong.\n";
        return;
    }

    Keluar* sekarang = kepala2;

    while (sekarang != nullptr){
        if (sekarang->id == idHapus){
            if (sekarang->sebelumnya != nullptr){
                sekarang->sebelumnya->selanjutnya = sekarang->selanjutnya;
            }else{
                kepala2 = sekarang->selanjutnya;
            }
            // Jika ada node berikutnya, atur sebelumnya dari node berikutnya
            if (sekarang->selanjutnya != nullptr){
                sekarang->selanjutnya->sebelumnya = sekarang->sebelumnya;
            }else{ 
                ekor2 = sekarang->sebelumnya;
            }
            delete sekarang;
            cout << "Catatan transaksi keluar dengan ID " << idHapus << " berhasil dihapus.\n";
            return;
        }
        sekarang = sekarang->selanjutnya;
    }
    cout << "Catatan dengan ID " << idHapus << " tidak ditemukan di transaksi keluar.\n";
}

int main(){

    int pilihan;
    int id, nominal;
    std ::string tanggal, berita;

do {    
    cout << "\n=== Aplikasi Catatan Transaksi Keuangan ===\n";
    cout << "1. Tambah Catatan Transaksi Masuk           |\n";
    cout << "2. Tambah Catatan Transaksi Keluar          |\n";
    cout << "3. Tampilkan Catatan Transaksi              |\n";
    cout << "4. Tampilkan Saldo                          |\n";
    cout << "5. Cari Catatan Transaksi Berdasarkan ID    |\n";
    cout << "6. Hapus Catatan Transaksi berdasarkan ID   |\n";
    cout << "7. Keluar                                   |\n";
    cout << "=============================================\n";
    cout << "Pilih menu: "; cin >> pilihan;
    cin.ignore();

    switch (pilihan){
    case 1:
        cout << "Masukkan ID transaksi masuk    : ";
        cin >> id; cin.ignore();

        cout << "Masukkan Tanggal (dd-mm-yyyy)  : ";
        getline(cin, tanggal);

        cout << "Masukkan Jumlah Nominal        : ";
        cin >> nominal; cin.ignore();

        cout << "Masukkan Berita                : ";
        getline(cin, berita);

        if (id < 0 || nominal < 0){
            cout << "ID dan NOMINAL tidak boleh bernilai negatif!\n";
        }else{
            tambahMasuk(id, nominal, tanggal, berita);
        }
        break;
    
    case 2:
        cout << "Masukkan ID transaksi keluar   : ";
        cin >> id; cin.ignore();

        cout << "Masukkan Tanggal (dd-mm-yyyy)  : ";
        getline(cin, tanggal);

        cout << "Masukkan Jumlah Nominal        : ";
        cin >> nominal; cin.ignore();

        cout << "Masukkan Berita                : ";
        getline(cin, berita);

        if (id < 0 || nominal < 0){
            cout << "ID dan NOMINAL tidak boleh bernilai negatif!\n";
        }else{
            tambahKeluar(id, nominal, tanggal, berita);
        }
        break;

    case 3:
    
        int tampil;
        do{
            cout << "=== Apa yang ingin Anda Tampilkan? ===" << endl;
            cout << "| 1. Catatan Transaksi Masuk          |"<< endl;
            cout << "| 2. Catatan Transaksi Keluar         |" << endl;
            cout << "| 3. Kembali ke Menu Utama            |" << endl;
            cout << "======================================" << endl;
            cout << "Masukan Pilihan Anda (1-3) : ";
            cin >> tampil;

            switch (tampil){
                case 1:
                    masuksortByTanggal(); 
                    tampilDataMasuk();
                    break;
                case 2:
                    keluarsortByTanggal(); 
                    tampilDataKeluar();
                    break;
                case 3:
                    
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                    break;
            }      
        }while (tampil != 3);  
        break;

    case 4:
        hitungTotalMasuk();
        hitungTotalKeluar();
        hitungSimpanan();
        tampilSimpanan();
        break;


    case 5:

        int cari;
        do{
            cout << "=== Apa yang ingin Anda Cari? ===" << endl;
            cout << "1. Catatan Transaksi Masuk       |" << endl;
            cout << "2. Catatan Transaksi Keluar      |" << endl;
            cout << "3. Kembali ke Menu Utama         |" << endl;
            cout << "=================================" << endl;
            cout << "Masukan Pilihan Anda (1-3) : ";
            cin >> cari;


            switch (cari){
                case 1:
                    cariCatatanMasuk();
                    break;
                case 2:
                    cariCatatanKeluar();
                    break;
                case 3:

                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                    break;
            }
        } while (cari != 3);
        break;
        
    case 6:

    int hapus;
    do{
        cout << "=== Apa yang ingin Anda Hapus? ===" << endl;
        cout << "1. Catatan Transaksi Masuk        |" << endl;
        cout << "2. Catatan Transaksi Keluar       |" << endl;
        cout << "3. Kembali ke Menu Utama          |" << endl;
        cout << "==================================" << endl;
        cout << "Masukan Pilihan Anda (1-3) : ";
        cin >> hapus;

        switch (hapus){
            case 1: {
                int idHapus;
                cout << "Masukkan ID transaksi masuk yang ingin dihapus: ";
                cin >> idHapus;
                hapusCatatanMasuk(idHapus);
                break;
            }
            case 2: {
                int idHapus;
                cout << "Masukkan ID transaksi keluar yang ingin dihapus: ";
                cin >> idHapus;
                hapusCatatanKeluar(idHapus);
                break;
            }
            case 3:
                
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
    } while (hapus != 3);
    break;

    case 7:
        cout << "Terima kasih telah menggunakan aplikasi ini!\n";
        return 0;

    default:
        cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        break;
    }
    }while (pilihan != 7);
    return 0;
}
