#include <iostream>
#include <limits>
using namespace std;

void clearinputbuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

struct detail {
    string detail;
};

struct item {
    string nama;
    int jumlah;
    detail *dtl;
};

item itm[100];
detail dtl[100];


bool create(item *itm, detail *dtl, int &n) {
    cout << "Tambah item: ";
    cin.ignore();
    getline(cin, itm[n].nama);
    if (itm[n].nama.empty()) {
        cout << "Nama item tidak boleh kosong." << endl;
        cout << endl;
        return false;
    }
    cout << itm[n].nama << " berhasil ditambahkan" << endl;

    while (true) {
        cout << endl;
        cout << "Jumlah (max 10 digit): ";
        if (!(cin >> itm[n].jumlah)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Inputan kamu salah. Pastikan kamu input angka dan maksimal 10 digit." << endl;
            cout << "Tekan ENTER" << endl;
            clearinputbuffer();
        }
        else {
            cout << "Jumlah " << itm[n].nama << " = " << itm[n].jumlah << endl;
            break;
        }
    }
    cout << endl;
    cout << "Detail item (merk/varian) atau tekan ENTER jika tidak ada" << endl;
    cout << "Detail: ";
    cin.ignore();
    getline(cin, dtl[n].detail);
    if (dtl[n].detail.empty()) {
        dtl[n].detail = '-';
        cout << endl;
        cout << "Detail item dikosongkan" << endl;
        cout << endl;
    }
    itm[n].dtl = &dtl[n];
    n++;

    return true;
}

bool read(item *itm, detail *dtl, int n) {
    if (n == 0) {
        cout << "\nWah, daftar belanja kamu kosong nih." << endl;
        cout << "Ayo tambahkan itemnya terlebih dahulu." << endl;
        cout << "\nTekan Enter untuk melanjutkan";
        cout << endl;
        cin.get();
        clearinputbuffer();
        return false;
    }
    else {
        cout << "===================================" << endl;
        cout << "##        DAFTAR   ITEM          ##" << endl;
        cout << "===================================" << endl;
        for (int i = 0; i < n; i++) {
            cout << i + 1 << ". " << itm[i].nama << " (" << itm[i].jumlah << ") " << "Unit" << endl;
            cout << "Catatan: " << dtl[i].detail << endl;
            cout << endl;
        }
        cout << "\nTekan Enter untuk melanjutkan";
        cout << endl;
        cin.get();
        clearinputbuffer();
        cout << endl;
        return true;
    }
}

bool update(item *itm, detail *dtl, int &n) {
    if (n == 0) {
        cout << "\nWah, daftar belanja kamu kosong nih." << endl;
        cout << "Ayo tambahkan itemnya terlebih dahulu." << endl;
        cout << "\nTekan Enter untuk melanjutkan";
        cout << endl;
        cin.get();
        clearinputbuffer();
        return false;
    }
    read(itm, dtl, n);
    while (true) {
        cout << endl;
        cout << "Pilih nomor item yang ingin kamu ubah " << endl;
        cout << "Nomor item: ";
        int ubah;
        if (!(cin >> ubah)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Inputan kamu salah. Pastikan kamu input angka dan maksimal 10 digit." << endl;
            cout << "Tekan ENTER" << endl;
            cout << endl;
            clearinputbuffer();
        }
        else {
            ubah -= 1;
            if (ubah >= 0 && ubah < n) {
                string nama_baru;
                cout << endl;
                cout << "Ganti nama item " << endl;
                cout << "Nama item: ";
                cin.ignore();
                getline(cin, nama_baru);
                if (nama_baru.empty()) {
                    cout << "Nama item tidak boleh kosong." << endl;
                    cout << endl;
                    return false;
                }
                while (true) {
                    itm[ubah].nama = nama_baru;
                    cout << endl;
                    cout << "Jumlah (max 10 digit): ";
                    if (!(cin >> itm[ubah].jumlah)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Inputan kamu salah. Pastikan kamu input angka dan maksimal 10 digit." << endl;
                        cout << "Tekan ENTER" << endl;
                        clearinputbuffer();
                    }
                    else {
                        cout << endl;
                        cout << "Ganti detail item atau tekan ENTER jika tidak ada" << endl;
                        cout << "Detail item: ";
                        cin.ignore();
                        getline(cin, dtl[ubah].detail);
                        if (dtl[ubah].detail.empty()) {
                            dtl[ubah].detail = '-';
                        }
                        cout << "Item nomor " << ubah + 1 << " Berhasil diupdate!" << endl;
                        cout << endl;

                        return true;
                        break;
                    }
                }
            }
            else {
                cout << "Nomor item yang kamu pilih tidak ada." << endl;
                cout << endl;
                return false;
            }

        }
    }
}

bool hapus(item *itm, detail *dtl, int &n) {
    if (n == 0) {
        cout << "\nWah, daftar belanja kamu kosong nih." << endl;
        cout << "Ayo tambahkan itemnya terlebih dahulu." << endl;
        cout << "\nTekan Enter untuk melanjutkan";
        cout << endl;
        cin.get();
        clearinputbuffer();
        return false;
    }
    read(itm, dtl, n);
    while (true) {
        cout << endl;
        cout << "Pilih nomor item yang ingin kamu hapus" << endl;
        cout << "Nomor item: ";
        int hapus;
        if (!(cin >> hapus)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Inputan kamu salah. Pastikan kamu input angka dan maksimal 10 digit." << endl;
            cout << "Tekan ENTER" << endl;
            cin.get();
            clearinputbuffer();
        }
        else {
            hapus -= 1;
            if (hapus >= 0 && hapus < n) {
                string konfirmasi;
                cout << "Yakin ingin hapus item nomor " << hapus + 1 << "? [Y/N] ";
                cin.ignore();
                cin >> konfirmasi;
                if (konfirmasi == "Y" || konfirmasi == "y") {
                    for (int i = hapus; i < n - 1; i++) {
                        itm[i].nama = itm[i + 1].nama;
                        itm[i].jumlah = itm[i + 1].jumlah;
                        dtl[i].detail = dtl[i + 1].detail;
                    }
                    cout << "Item nomor " << hapus + 1 << " berhasil dihapus" << endl;
                    cout << endl;
                    n--;
                    return true;
                    break;
                }
                else if (konfirmasi == "n" || konfirmasi == "N") {
                    cout << "Item nomor " << hapus + 1 << " tidak dihapus" << endl;
                    cout << endl;
                    return true;
                }
                else {
                    cout << "Pilihan kamu tidak valid" << endl;
                    cout << endl;
                    return true;
                }
            }
            else {
                cout << "Nomor item yang kamu pilih tidak ada." << endl;
                cout << endl;
                return false;
            }
        }
    }
}

void crud() {
    int n = 0;
    string pilihan;
    char ulang;

    cout << "\nSelamat datang! Ayo mulai atur daftar belanja kamu sekarang" << endl;
    cout << endl;
    while (ulang != 't') {
        cout << "Ayo, pilih salah satu dari menu ini!" << endl;
        cout << "===================================" << endl;
        cout << "##        DAFTAR   BELANJA       ##" << endl;
        cout << "===================================" << endl;
        cout << "1. Buat Daftar Belanja" << endl;
        cout << "2. Lihat Daftar Belanja" << endl;
        cout << "3. Ganti Item" << endl;
        cout << "4. Hapus Item" << endl;
        cout << "5. EXIT" << endl;
        cout << "\nPilihan kamu: ";
        cin >> pilihan;

        if (pilihan == "1") {
            create(itm, dtl, n);
        }
        else if (pilihan == "2") {
            read(itm, dtl, n);
        }
        else if (pilihan == "3") {
            update(itm, dtl, n);
        }
        else if (pilihan == "4") {
            hapus(itm, dtl, n);
        }
        else if (pilihan == "5") {
            char keluar;
            cout << "Keluar dari program? [Y/N]" << endl;
            cin >> keluar;
            if (keluar == 'y' || keluar == 'Y') {
                exit(0);
            }
            else if (keluar == 'n' || keluar == 'N') {
                crud();
            }
            else {
                cout << "Pilihan kamu tidak valid" << endl;
                cout << endl;
                crud();
            }
        }
        else {
            cout << endl;
            cout << "Pilihan kamu tidak valid!" << endl;
            cout << endl;
        }

    }
}

int main() {
    crud();
    return 0;
}