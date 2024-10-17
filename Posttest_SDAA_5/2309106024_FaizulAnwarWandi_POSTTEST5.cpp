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

void push(Item *&stack, Item *&head, string nama, int jumlah, string detail) {
    addFirst(stack, nama, jumlah, detail);
    addFirst(head, nama, jumlah, detail); 
    cout << "Item berhasil ditambahkan menggunakan metode STACK." << endl;
}

void pop(Item *&stack, Item *&head) {
    if (stack == nullptr) {
        cout << "STACK kosong, tidak ada item yang bisa diambil." << endl;
        return;
    }
    cout << "Item '" << stack->nama << "' berhasil diambil dari daftar belanja dengan metode STACK." << endl;
    Item *hapus = stack;
    stack = stack->next;
    delete hapus;

    hapus = head;
    head = head->next;
    delete hapus;
}


void enqueue(Item *&queue, Item *&head, string nama, int jumlah, string detail) {
    addLast(queue, nama, jumlah, detail);
    addLast(head, nama, jumlah, detail);
    cout << "Item berhasil ditambahkan menggunakan metode ENQUEUE." << endl;
}

void dequeue(Item *&queue, Item *&head) {
    if (queue == nullptr) {
        cout << "QUEUE kosong, tidak ada item yang bisa diambil." << endl;
        return;
    }
    cout << "Item" << queue->nama << "berhasil diambil dari daftar belanja menggunakan metode DEQUEUE." << endl;

    Item *hapus = queue;
    queue = queue->next;
    delete hapus;

    hapus = head;
    head = head->next;
    delete hapus;
}

Item* getTail(Item* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

Item* partition(Item* head, Item* end, Item*& newHead, Item*& newEnd) {
    Item* pivot = end;
    Item* prev = nullptr, * curr = head, * tail = pivot;

    while (curr != pivot) {
        if (curr->nama < pivot->nama) { 
            if (newHead == nullptr) newHead = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Item* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (newHead == nullptr) newHead = pivot;
    newEnd = tail;
    return pivot;
}

Item* quickSortRecur(Item* head, Item* end) {
    if (!head || head == end) return head;

    Item* newHead = nullptr, * newEnd = nullptr;
    Item* pivot = partition(head, end, newHead, newEnd);

    if (newHead != pivot) {
        Item* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;
        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSort(Item*& head) {
    head = quickSortRecur(head, getTail(head));
}

Item* merge(Item* left, Item* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->nama > right->nama) { 
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

void split(Item* source, Item*& front, Item*& back) {
    Item* fast = source->next;
    Item* slow = source;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

void mergeSort(Item*& head) {
    if (!head || !head->next) return;

    Item* front = nullptr;
    Item* back = nullptr;

    split(head, front, back);
    mergeSort(front);
    mergeSort(back);

    head = merge(front, back);
}

void crud() {
    Item *head = nullptr;
    Item *stack = nullptr;
    Item *queue = nullptr;
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
        cout << "6. Push (Tambah ke Stack)" << endl;
        cout << "7. Pop (Ambil dari Stack)" << endl;
        cout << "8. Enqueue (Tambah ke Queue)" << endl;
        cout << "9. Dequeue (Ambil dari Queue)" << endl;
        cout << "10. Sort Ascending Berdasarkan Nama (Quick Sort)" << endl;
        cout << "11. Sort Descending Berdasarkan Nama (Merge Sort)" << endl;
        cout << "12. EXIT" << endl;
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
        } else if (pilihan == "5") {
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
            string nama, detail;
            int jumlah;
            cout << "Tambah item ke STACK: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Jumlah: ";
            cin >> jumlah;
            cout << "Detail item: ";
            cin.ignore();
            getline(cin, detail);
            push(stack, head, nama, jumlah, detail);
        } else if (pilihan == "7") {
            pop(stack, head);
        } else if (pilihan == "8") {
            string nama, detail;
            int jumlah;
            cout << "Tambah item ke QUEUE: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Jumlah: ";
            cin >> jumlah;
            cout << "Detail item: ";
            cin.ignore();
            getline(cin, detail);
            enqueue(queue, head, nama, jumlah, detail);
        } else if (pilihan == "9") {
            dequeue(queue, head);
        }   else if (pilihan == "10") {
            quickSort(head);
            cout << "Daftar belanja diurutkan secara ascending menggunakan Quick Sort." << endl;
            read(head);
        } else if (pilihan == "11") {
            mergeSort(head);
            cout << "Daftar belanja diurutkan secara descending menggunakan Merge Sort." << endl;
            read(head);
        } else if (pilihan == "12") {
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
