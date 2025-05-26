#include <iostream>
using namespace std;

struct Node
{
    string nama;
    string jurusan;
    string fakultas;
    string universitas;
    Node* next;
    Node* prev;
};

struct User {
    string username;
    string password;
    string role;
};

bool login(string &role) {
    string username, password;
    
}
 struct Node* buatnode(string nama, string jurusan, string fakultas, string universitas){
    Node* newNode = new Node{nama, jurusan, fakultas, universitas, NULL, NULL};
    return newNode;
}

void sisipnodedepan(Node** head, string nama, string jurusan, string fakultas, string universitas) {
    Node* newNode = buatnode(nama, jurusan, fakultas, universitas);
    newNode->next = *head;
    if(*head != NULL) {
        (*head)->prev = newNode;

    }
    *head = newNode;
}

void sisipnodebelakang(Node** head, string nama, string jurusan, string fakultas, string universitas) {
    Node* newNode = buatnode(nama, jurusan, fakultas, universitas);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    Node* bantu = *head;
    while(bantu->next != NULL){
        bantu = bantu->next;
    }
    bantu->next = newNode;
    newNode->prev = bantu;
}

Node* searching(Node* head, string nama, string jurusan, string fakultas, string universitas) {
    Node* bantu = head;
    while(bantu != NULL){
        if(bantu-> nama == nama) {
            return bantu;
        }
        bantu = bantu->next;
     }
     return NULL;
     
}

void sisipnodetengah(Node* nodekiri, string nama, string jurusan, string fakultas, string universitas) {
    if(nodekiri == NULL){
        cout << "Node tidak ada" << endl;
    }
    Node* newNode = buatnode(nama, jurusan, fakultas, universitas);
    newNode->next = nodekiri->next;
    newNode->prev = nodekiri;

    if(nodekiri->next != NULL) {
        nodekiri->next->prev = newNode;
    }
    nodekiri->next = newNode;
}

void hapusnodedepan(Node** head){

    if(*head == NULL){
        cout << "List Kosong" << endl;
        return;
    }

    Node* bantu = *head;
    *head = (*head)->next;
    if(*head != NULL){
        (*head)->prev = NULL;
    }
    delete bantu;

}

void hapusnodebelakang(Node** head){

    if(*head == NULL){
        cout << "List Kosong" << endl;
        return;
    }
    Node* bantu = *head;
    while(bantu->next != NULL){
        bantu = bantu->next;
    }
    if(bantu->prev !=NULL)
    {
        bantu->prev->next = NULL;
    }else{
        *head = NULL;
    }
    delete bantu;

}

void hapusnodetengah(Node** head, string key){
    if(*head == NULL){
        cout << "List Kosong" << endl;
        return;

    }
    Node* bantu = *head;
    while(bantu != NULL && bantu->nama != key){
        bantu = bantu->next;
    }
    if(bantu == NULL){
        cout << "nama tidak ditemukan!" << endl;
        return;
    }
    if(bantu->prev != NULL) {
        bantu->prev->next = bantu->next;
    }else{
        *head = bantu->next;
    }
    if(bantu->next != NULL){
        bantu->next->prev = bantu->prev;
    }
    delete bantu;
    cout << "nama " << key << " Berhasil Dihapus di contact" << endl; 
}
void printdaridepan(Node* head){

    if(head == NULL){
        cout << "Node nya ga ada!" << endl;
    }
    Node* bantu = head;
    cout << "Kontak : " << endl;
    while(bantu != NULL){
        cout << "Nama : " << bantu->nama << endl;
        cout << "Jurusan : " << bantu->jurusan << endl;
        cout << "Fakultas : " << bantu->fakultas << endl; 
        cout << "Universitas : " << bantu->universitas << endl << endl;
        
        bantu = bantu->next;
    }
}

void printdaribelakang(Node* head){

    if(head == NULL){
        cout << "contact kosong!" << endl;
        return;
    }
    Node* bantu = head;
    while(bantu->next != NULL){ // buat jalan ke ujung list
        bantu = bantu->next;
    }
    while(bantu != NULL){ // buat jalan dari belakang ke depan

        cout << " Nama: " << bantu->nama << ", jurusan : " << bantu->jurusan << ", fakultas : " << bantu->fakultas << ", universitas : " << bantu->universitas << endl;   
        bantu= bantu->prev;
    }
    cout << endl;
}

void sorting(Node** head, string kunci) {
    if (*head == NULL) {
        cout << "Kontak Kosong" << endl;
    }
    
    bool swapped;
    do {
        swapped = false;
        Node* curr = *head;

        while (curr->next != NULL) {
            bool perluTukar = false;

            if (kunci == "nama" && curr->nama > curr->next->nama)
                perluTukar = true;
            else if (kunci == "jurusan" && curr->jurusan > curr->next->jurusan)
                perluTukar = true;
            else if (kunci == "fakultas" && curr->fakultas > curr->next->fakultas)
                perluTukar = true;
            else if (kunci == "universitas" && curr->universitas > curr->next->universitas)
                perluTukar = true;

            if (perluTukar) {
                swap(curr->nama, curr->next->nama);
                swap(curr->jurusan, curr->next->jurusan);
                swap(curr->fakultas, curr->next->fakultas);
                swap(curr->universitas, curr->next->universitas);
                swapped = true;
            }

            curr = curr->next;
        }
    } while (swapped);

    cout << "Kontak berhasil diurutkan berdasarkan " << kunci << "." << endl;
}

main() {
    Node* head = NULL;
    int pilihan;
    string nama, jurusan, fakultas, universitas;
    char lanjut = 'y';

    do {
    cout << "== Menu Buku Kontak ==" << endl;
    cout << "1. Tambahkan kontak" << endl;
    cout << "2. Cari kontak" << endl;
    cout << "3. Hapus Kontak" << endl;
    cout << "4. Tampilkan daftar kontak" << endl;
    cout << "5. Urutkan daftar kontak" << endl;
    cout << "6. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
    cout << "Opsi Insert" << endl;
    cout << "1. Masukkan dari depan" << endl;
    cout << "2. Masukkan dari belakang" << endl;
    cout << "Pilih Opsi : ";
    cin >> pilihan;
    cin.ignore();
        if (pilihan == 1) {
            cout << "Masukkan Nama: ";
            getline(cin, nama);
            cout << "Masukkan jurusan: ";
            getline(cin, jurusan);
            cout << "Masukkan fakultas: ";
            getline(cin, fakultas);
            cout << "Masukkan universitas: ";
            getline(cin, universitas);
            sisipnodedepan(&head, nama, jurusan, fakultas, universitas);
        } else if (pilihan == 2) {
            cout << "Masukkan Nama: ";
            getline(cin, nama);
            cout << "Masukkan jurusan: ";
            getline(cin, jurusan);
            cout << "Masukkan fakultas: ";
            getline(cin, fakultas);
            cout << "Masukkan universitas: ";
            getline(cin, universitas);
            sisipnodebelakang(&head, nama, jurusan, fakultas, universitas);
        }

    } else if (pilihan == 2) {
        cout << "Masukkan nama kontak yang ingin dicari : ";
        getline(cin, nama);

        Node* hasil = searching(head, nama, "", "", "");
        if (hasil != NULL) {
            cout << "Kontak ditemukan!" << endl;
            cout << "Nama       : " << hasil->nama << endl;
            cout << "Jurusan    : " << hasil->jurusan << endl;
            cout << "Fakultas   : " << hasil->fakultas << endl;
            cout << "Universitas: " << hasil->universitas << endl;
        } else {
            cout << "Kontak dengan nama '" << nama << "' tidak ditemukan." << endl;
        }

    }
     else if (pilihan == 3) {
    cout << "Masukkan nama kontak yang ingin dihapus : ";
    getline(cin, nama);
    hapusnodetengah(&head, nama);

    } else if (pilihan == 4) {
    printdaridepan(head);

    } else if (pilihan == 5) {
        cout << "Urutkan berdasarkan : " << endl;
        cout << "1. Nama " << endl;
        cout << "2. Jurusan" << endl;
        cout << "3. Fakultas" << endl;
        cout << "4. Universitas" << endl;
        cout << "Pilih : ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 1) {
            sorting(&head, "nama");
        } else if (pilihan == 2) {
            sorting(&head, "jurusan");
        } else if (pilihan == 3) {
            sorting(&head, "fakultas");
        } else if (pilihan == 4) {
            sorting(&head, "universitas");
        } else {
            cout <<" Pilihan tidak valid" << endl;
        }
            
    
    } else if (pilihan == 6) {
        cout << "Terima kasih" << endl;
        return 0;
    } else {
    cout << "Pilihan tidak valid!" << endl;
    }

        cout << "Kembali ke menu? (y/n): ";
        cin >> lanjut;
        cin.ignore();
    } while (lanjut == 'y' || lanjut == 'Y');

    cout << "Terima kasih telah menggunakan Menu Manajemen ini! " << endl;
    return 0;
}





