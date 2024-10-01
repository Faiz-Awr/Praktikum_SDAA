#include <iostream>
#include <limits>
using namespace std;

struct Detail {
    string detail;
};

struct Item {
    string nama;
    int jumlah;
    Detail dtl;
    Item *next; 
};

void addFirst(Item *&head, string nama, int jumlah, string detail) {
    Item *nodeBaru = new Item;
    nodeBaru->nama = nama;
    nodeBaru->jumlah = jumlah;
    nodeBaru->dtl.detail = detail;
    nodeBaru->next = head;
    head = nodeBaru;
}

void addLast(Item *&head, string nama, int jumlah, string detail) {
    Item *nodeBaru = new Item;
    nodeBaru->nama = nama;
    nodeBaru->jumlah = jumlah;
    nodeBaru->dtl.detail = detail;
    nodeBaru->next = nullptr;

    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Item *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
}

void read(Item *head) {
    if (head == nullptr) {
        cout << "\nWah, daftar belanja kamu kosong nih." << endl;
        cout << "Ayo tambahkan itemnya terlebih dahulu." << endl;
        cout << endl;
        return;
    }
    cout << "===================================" << endl;
    cout << "##        DAFTAR   ITEM          ##" << endl;
    cout << "===================================" << endl;
    Item *temp = head;
    int index = 1;
    while (temp != nullptr) {
        cout << index++ << ". " << temp->nama << " (" << temp->jumlah << ") Unit" << endl;
        cout << "Catatan: " << temp->dtl.detail << endl;
        cout << endl;
        temp = temp->next;
    }
}

bool update(Item *&head, int posisi, string nama_baru, int jumlah_baru, string detail_baru) {
    if (head == nullptr) {
        cout << "\nDaftar belanja kosong." << endl;
        return false;
    }
    Item *temp = head;
    int index = 1;
    while (temp != nullptr && index < posisi) {
        temp = temp->next;
        index++;
    }
    if (temp == nullptr) {
        cout << "Item tidak ditemukan." << endl;
        return false;
    }
    temp->nama = nama_baru;
    temp->jumlah = jumlah_baru;
    temp->dtl.detail = detail_baru;
    return true;
}


bool hapus(Item *&head, int posisi) {
    if (head == nullptr) {
        cout << "\nDaftar belanja kosong. Tidak ada yang bisa dihapus." << endl;
        return false;  
    }
    if (posisi == 1) {
        Item *hapus = head;
        head = head->next;
        delete hapus;
        cout << "Item pertama berhasil dihapus." << endl;
        return true;
    }
    Item *temp = head;
    int index = 1;
    while (temp->next != nullptr && index < posisi - 1) {
        temp = temp->next;
        index++;
    }
    if (temp->next == nullptr) {
        cout << "Item tidak ditemukan." << endl;
        return false;
    }
    Item *hapus = temp->next;
    temp->next = temp->next->next;
    delete hapus;
    cout << "Item berhasil dihapus." << endl;
    return true;
}

void crud() {
    Item *head = nullptr;
    string pilihan;

    while (true) {
        cout << "===================================" << endl;
        cout << "Ayo, pilih salah satu dari menu ini!" << endl;
        cout << "===================================" << endl;
        cout << "1. Tambah Item di Awal" << endl;
        cout << "2. Tambah Item di Akhir" << endl;
        cout << "3. Lihat Daftar Belanja" << endl;
        cout << "4. Ganti Item" << endl;
        cout << "5. Hapus Item" << endl;
        cout << "6. EXIT" << endl;
        cout << "\nPilihan kamu: ";
        cin >> pilihan;

        if (pilihan == "1") {
            string nama, detail;
            int jumlah;
            cout << "Tambah item di awal: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Jumlah: ";
            cin >> jumlah;
            cout << "Detail item: ";
            cin.ignore();
            getline(cin, detail);
            addFirst(head, nama, jumlah, detail); 
        } else if (pilihan == "2") {
            string nama, detail;
            int jumlah;
            cout << "Tambah item di akhir: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Jumlah: ";
            cin >> jumlah;
            cout << "Detail item: ";
            cin.ignore();
            getline(cin, detail);
            addLast(head, nama, jumlah, detail); 
        } else if (pilihan == "3") {
            read(head);
        } else if (pilihan == "4") {
            read(head);
            int posisi;
            string nama_baru, detail_baru;
            int jumlah_baru;
            cout << "Pilih nomor item yang ingin kamu ubah: ";
            cin >> posisi;
            cout << "Nama item baru: ";
            cin.ignore();
            getline(cin, nama_baru);
            cout << "Jumlah baru: ";
            cin >> jumlah_baru;
            cout << "Detail item baru: ";
            cin.ignore();
            getline(cin, detail_baru);
            update(head, posisi, nama_baru, jumlah_baru, detail_baru);
                }
        else if (pilihan == "5") {
        if (head == nullptr) {
            cout << "\nDaftar belanja kosong. Tidak ada yang bisa dihapus." << endl;
            continue;
        }
        read(head);
        int posisi;
        cout << "Pilih nomor item yang ingin kamu hapus: ";
        cin >> posisi;
        hapus(head, posisi);

        } else if (pilihan == "6") {
            cout << "Keluar dari program." << endl;
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

int main() {
    crud();
    return 0;
}
