#include <iostream>
using namespace std;

struct Node
{
    string nama;
    string nohp;
    string gmail;
    string jurusan;
    string fakultas;
    string universitas;
    string catatan;
    bool favorit;
    Node* next;
    Node* prev;
};

 struct Node* buatnode(string nama, string nohp, string gmail, string jurusan, string fakultas, string universitas, string catatan = "", bool favorit = false ){
    Node* newNode = new Node{nama,nohp, gmail, jurusan, fakultas, universitas, catatan, favorit, NULL, NULL};
    return newNode;
}
void simpanfile(Node* head) {
    FILE* file = fopen("datakontak.txt", "a"); // mode append, biar tambah data terus
    if (file == NULL) {
        cout << "Gagal membuka file untuk menulis." << endl;
        return;
    }

    Node* bantu = head;
    while (bantu != NULL) {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                bantu->nama.c_str(),
                bantu->nohp.c_str(),
                bantu->gmail.c_str(),
                bantu->jurusan.c_str(),
                bantu->fakultas.c_str(),
                bantu->universitas.c_str(),
                bantu->catatan.c_str(),
                bantu->favorit ? 1 : 0);
        bantu = bantu->next;
    }

    fclose(file);
    cout << "Data kontak berhasil disimpan ke file." << endl;
}

void perbaruiIsiFile(Node* head)
{
    FILE* file = fopen("datakontak.txt", "w");  // mode write untuk overwrite file
    if (!file)
    {
        cout << "Gagal membuka file untuk menulis." << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr)
    {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%d\n",
                temp->nama.c_str(),
                temp->nohp.c_str(),
                temp->gmail.c_str(),
                temp->jurusan.c_str(),
                temp->fakultas.c_str(),
                temp->universitas.c_str(),
                temp->catatan.c_str(),
                temp->favorit ? 1 : 0);
        temp = temp->next;
    }
    fclose(file);
    cout << "File berhasil diperbarui dengan data kontak terbaru." << endl;
}
void muatfile(Node** head) {
    FILE* file = fopen("datakontak.txt", "r");
    if (!file) {
        cout << "File tidak ditemukan, mulai dengan data kosong.\n";
        return;
    }

    Node* tail = nullptr;
    char bufferNama[100], bufferNohp[100], bufferGmail[100], bufferJurusan[100], bufferFakultas[100], bufferUniversitas[100], bufferCatatan[200];
    int fav;

    while (true) {
        int hasil = fscanf(file, "%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%199[^|]|%d\n",
            bufferNama, bufferNohp, bufferGmail, bufferJurusan, bufferFakultas, bufferUniversitas, bufferCatatan, &fav);
        
        if (hasil == 8) {
            Node* baru = new Node{
                string(bufferNama),
                string(bufferNohp),
                string(bufferGmail),
                string(bufferJurusan),
                string(bufferFakultas),
                string(bufferUniversitas),
                string(bufferCatatan),
                fav == 1,
                nullptr,
                tail
            };

            if (tail)
                tail->next = baru;
            else
                *head = baru; 

            tail = baru;
        } else {
            break; 
        }
    }

    fclose(file);
}
void sisipnodedepan(Node** head, string nama, string nohp, string gmail, string jurusan, string fakultas, string universitas, string catatan = "", bool favorit = false) {
    Node* newNode = buatnode(nama, nohp, gmail, jurusan, fakultas, universitas, catatan, favorit);
    newNode->next = *head;
    if(*head != NULL) {
        (*head)->prev = newNode;

    }
    *head = newNode;
}

void sisipnodebelakang(Node** head, string nama, string nohp, string gmail, string jurusan, string fakultas, string universitas, string catatan = "", bool favorit = false) {
    Node* newNode = buatnode(nama, nohp, gmail, jurusan, fakultas, universitas, catatan, favorit);
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

Node* searching(Node* head, string nama) {
    Node* bantu = head;
    bool found = false;
    while(bantu != NULL){
        if(bantu-> nama == nama) {
            return bantu;
        }
        bantu = bantu->next;
     }
     return NULL;
}

void editkontak(Node* node) {
    if(node == NULL) {
        cout << "Kontak tidak ditemukan" << endl;
        return;
    }
    cout << "Masukkan data baru (kosongin jika tidak jadi)" << endl;

    string input;
    cout << "nama (" << node->nama << "): ";
    getline(cin, input);
    if(!input.empty()) node->nama = input;

    cout << "nomor hp (" << node->nohp << "): ";
    getline(cin, input);
    if(!input.empty()) node->nohp = input;

    cout << "Gmail (" << node->gmail << "): ";
    getline(cin, input);
    if(!input.empty()) node->gmail = input;

    cout << "Jurusan (" << node->jurusan << "): ";
    getline(cin, input);
    if(!input.empty()) node->jurusan = input;

    cout << "Fakultas (" << node->fakultas << "): ";
    getline(cin, input);
    if(!input.empty()) node->fakultas = input;

    cout << "Universitas (" << node->universitas << "): ";
    getline(cin, input);
    if(!input.empty()) node->universitas = input;

    cout << "Catatan (" << node->catatan << "): ";
    getline(cin, input);
    if(!input.empty()) node->catatan = input;

    cout << "Favorit (Y/N) (" << (node->favorit ? "Ya" : "Tidak") << "): ";
    getline(cin, input);
    if(input == "Y" || input == "y") node->favorit = true;
    else if(input == "N" || input == "n") node->favorit = false;

    cout << "Data kontak berhasil diperbarui!" << endl;
}

void sisipnodetengah(Node* nodekiri, string nama, string nohp, string gmail, string jurusan, string fakultas, string universitas, string catatan = "", bool favorit = false) {
    if(nodekiri == NULL){
        cout << "Tidak ada Kontak" << endl;
    }
    Node* newNode = buatnode(nama, nohp, gmail, jurusan, fakultas, universitas, catatan, favorit );
    newNode->next = nodekiri->next;
    newNode->prev = nodekiri;

    if(nodekiri->next != NULL) {
        nodekiri->next->prev = newNode;
    }
    nodekiri->next = newNode;
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
    } else {
    Node* bantu = head;
    int i = 1;
    cout << "Kontak : " << endl;
    cout << "=====================================" << endl;
    while(bantu != NULL){

        cout << "= " << i << ". " << bantu->nama << " (" << bantu->jurusan << ", " << bantu->fakultas << ", " << bantu->universitas << ")" << endl;
        cout << "= " << "   " << "No. HP: " << bantu->nohp << endl;
        cout << "= " << "   " << "Gmail : " << bantu->gmail << endl;
        i++;
        bantu = bantu->next;
    }
    cout << "=====================================" << endl;
    }   
}

void printfavorit(Node* head) {
    if(head == NULL){
        cout << "Node nya ga ada!" << endl;
        return;
    }
    Node* bantu = head;
    int i = 1;
    bool ada = false;
    cout << "Daftar Kontak Favorit:" << endl;
    while(bantu != NULL){
        if(bantu->favorit){
            
            cout << "= " << i << ". " << "Nama : " << bantu->nama << " (" << bantu->jurusan << ", " << bantu->fakultas << ", " << bantu->universitas << ")" << endl;
            cout << "=   Catatan : " << bantu->catatan << endl;
            cout << endl;
            i++;
            ada = true;

        }
        bantu = bantu->next;
    }
    if(!ada) cout << "Belum ada kontak favorit." << endl;
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
                swap(curr->nohp, curr->next->nohp);
                swap(curr->gmail, curr->next->gmail);
                swap(curr->jurusan, curr->next->jurusan);
                swap(curr->fakultas, curr->next->fakultas);
                swap(curr->universitas, curr->next->universitas);
                swap(curr->catatan, curr->next->catatan);
                swap(curr->favorit, curr->next->favorit);
                swapped = true;
            }

            curr = curr->next;
        }
    } while (swapped);

    cout << "Kontak berhasil diurutkan berdasarkan " << kunci << "." << endl;
}

int main() {
    Node* head = NULL;
    muatfile(&head);  

    int pilihan;
    string nama, nohp, gmail, jurusan, fakultas, universitas, catatan;
    char lanjut = 'y';

    do {
        cout << "== Menu Buku Kontak ==" << endl;
        cout << "1. Lihat Daftar Kontak" << endl;
        cout << "2. Kelola Kontak" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "Opsi Tampilkan" << endl;
            cout << "1. Tampilkan semua kontak" << endl;
            cout << "2. Tampilkan kontak favorit" << endl;
            cout << "Pilihan: ";
            cin >> pilihan;
            cin.ignore();
            if (pilihan == 1) {
                printdaridepan(head);
            } else if (pilihan == 2) {
                printfavorit(head);
            }
        } else if (pilihan == 2) {
            cout << "1. Tambahkan kontak" << endl;
            cout << "2. Cari kontak" << endl;
            cout << "3. Hapus Kontak" << endl;
            cout << "4. Urutkan daftar kontak" << endl;
            cout << "5. Edit Kontak" << endl;
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
                    cout << "Masukkan No. HP: ";
                    getline(cin, nohp);
                    cout << "Masukkan email : ";
                    getline(cin, gmail);
                    cout << "Masukkan jurusan: ";
                    getline(cin, jurusan);
                    cout << "Masukkan fakultas: ";
                    getline(cin, fakultas);
                    cout << "Masukkan universitas: ";
                    getline(cin, universitas);
                    cout << "Masukkan Catatan (Opsional): ";
                    getline(cin, catatan);
                    cout << "Apakah ini kontak favorit? (1=Ya, 0=Tidak): ";
                    int favInput;
                    cin >> favInput;
                    cin.ignore();
                    bool favorit = (favInput == 1);
                    sisipnodedepan(&head, nama, nohp, gmail, jurusan, fakultas, universitas, catatan, favorit);
                } else if (pilihan == 2) {
                    cout << "Masukkan Nama: ";
                    getline(cin, nama);
                    cout << "Masukkan No. HP: ";
                    getline(cin, nohp);
                    cout << "Masukkan email : ";
                    getline(cin,gmail);
                    cout << "Masukkan jurusan: ";
                    getline(cin, jurusan);
                    cout << "Masukkan fakultas: ";
                    getline(cin, fakultas);
                    cout << "Masukkan universitas: ";
                    getline(cin, universitas);
                    cout << "Masukkan Catatan (Opsional): ";
                    getline(cin, catatan);
                    cout << "Apakah ini kontak favorit? (1=Ya, 0=Tidak): ";
                    int favInput;
                    cin >> favInput;
                    cin.ignore();
                    bool favorit = (favInput == 1);
                    sisipnodebelakang(&head, nama, nohp, gmail, jurusan, fakultas, universitas, catatan, favorit);
                }
                perbaruiIsiFile(head);  
            } else if (pilihan == 2) {
                cout << "Masukkan nama kontak yang ingin dicari : ";
                getline(cin, nama);

                Node* hasil = searching(head, nama);
                if (hasil != NULL) {
                    cout << "Kontak ditemukan!" << endl;
                    cout << "Nama       : " << hasil->nama << endl;
                    cout << "No. HP     : " << hasil->nohp << endl;
                    cout << "Email      : " << hasil->gmail << endl;
                    cout << "Jurusan    : " << hasil->jurusan << endl;
                    cout << "Fakultas   : " << hasil->fakultas << endl;
                    cout << "Universitas: " << hasil->universitas << endl;
                    cout << "Catatan    : " << hasil->catatan << endl;
                    cout << "Favorit    : " << (hasil->favorit ? "Ya" : "Tidak") << endl;
                } else {
                    cout << "Kontak dengan nama '" << nama << "' tidak ditemukan." << endl;
                }
            } else if (pilihan == 3) {
                cout << "Masukkan nama kontak yang ingin dihapus : ";
                getline(cin, nama);
                hapusnodetengah(&head, nama);
                perbaruiIsiFile(head);  
            } else if (pilihan == 4) {
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
                perbaruiIsiFile(head);  
            } else if (pilihan == 5) {
                cout << "Masukkan nama kontak yang ingin diedit : ";
                getline(cin, nama);
                Node* nodeedit = searching(head, nama);
                editkontak(nodeedit);
                perbaruiIsiFile(head);  
            } else if (pilihan == 6) {
                cout << "Kembali ke menu utama..." << endl;
                continue;
                return 0;
            } else {
                cout << "Pilihan tidak valid" << endl;
            }
        } else {
            cout << "Terima kasih telah menggunakan contact book" << endl;
            return 0;
        }

        cout << "Kembali ke menu? (y/n): ";
        cin >> lanjut;
        cin.ignore();
    } while (lanjut == 'y' || lanjut == 'Y');

    cout << "Terima kasih telah menggunakan Menu Manajemen ini! " << endl;
    return 0;
}
