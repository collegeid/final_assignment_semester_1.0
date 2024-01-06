#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur untuk barang
typedef struct {
    int id;
    char nama_barang[50];
    float harga;
    int stok;
    char deskripsi[100];
} Barang;

// Definisi struktur untuk keranjang belanja
typedef struct {
    int id_keranjang;
    int id_barang;
    char nama_barang[50];
    float harga;
    int quantity;
} Keranjang;

// Definisi struktur untuk checkout
typedef struct {
    int id_keranjang;
    char tanggal_pembelian[20];
} Checkout;

// Definisi struktur untuk laporan
typedef struct {
    char tanggal_laporan[20];
    int jumlah_item_laporan;
    float total_harga_laporan;
} Laporan;


// Nama merchant (global variable)
char nama_merchant[100] = "Kelompok 2 auto";

// Nama merchant (global variable)
char nama_kasir[100] = "Auto Kasir (default)";
// Inisialisasi array untuk menyimpan data
Barang daftar_barang[100];
Keranjang keranjang_belanja[100];
Checkout checkout_data[100];
Laporan laporan_harian[100];

int jumlah_barang = 0;
int jumlah_keranjang = 0;
int jumlah_checkout = 0;
int jumlah_laporan = 0;


// Flag untuk memeriksa apakah program sudah diinisialisasi
int program_diinisialisasi = 0;
// Fungsi untuk menambahkan barang ke array
void tambah_barang(int id, char nama_barang[], float harga, int stok, char deskripsi[]) {
    Barang barang;
    barang.id = id;
    strcpy(barang.nama_barang, nama_barang);
    barang.harga = harga;
    barang.stok = stok;
    strcpy(barang.deskripsi, deskripsi);

    daftar_barang[jumlah_barang] = barang;
    jumlah_barang++;
    
     printf("Barang berhasil ditambahkan!\n");
}

// Fungsi untuk mencari barang berdasarkan nama atau ID
Barang *cari_barang(int id, char nama_barang[]) {
    for (int i = 0; i < jumlah_barang; i++) {
        if ((id != -1 && daftar_barang[i].id == id) || (id == -1 && strcmp(daftar_barang[i].nama_barang, nama_barang) == 0)) {
            return &daftar_barang[i];
        }
    }
    return NULL;
}

// Fungsi untuk mengedit barang berdasarkan ID
void edit_barang(int id, char nama_barang[], float harga, int stok, char deskripsi[]) {
    Barang *barang = cari_barang(id, nama_barang);
    if (barang != NULL) {
        barang->harga = harga;
        barang->stok = stok;
        strcpy(barang->deskripsi, deskripsi);
        printf("Barang berhasil diubah.\n");
    } else {
        printf("Barang tidak ditemukan.\n");
    }
}


// Fungsi untuk menambahkan item ke keranjang belanja
void tambah_keranjang(int id_keranjang, int id_barang, int quantity) {
    Keranjang *existing_item = NULL;
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_barang == id_barang) {
            existing_item = &keranjang_belanja[i];
            break;
        }
    }

    if (existing_item != NULL) {
        existing_item->quantity += quantity;
        printf("Jumlah item dalam keranjang berhasil diperbarui.\n");
    } else {
        Keranjang item_keranjang;
        item_keranjang.id_keranjang = id_keranjang;
        item_keranjang.id_barang = id_barang;
        strcpy(item_keranjang.nama_barang, daftar_barang[id_barang - 1].nama_barang);
        item_keranjang.harga = daftar_barang[id_barang - 1].harga;
        item_keranjang.quantity = quantity;

        keranjang_belanja[jumlah_keranjang] = item_keranjang;
        jumlah_keranjang++;
        printf("Item berhasil ditambahkan ke keranjang.\n");
    }
}

// Fungsi untuk mengedit item keranjang berdasarkan ID
void edit_keranjang(int id_keranjang, int new_quantity) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            keranjang_belanja[i].quantity = new_quantity;
            printf("Keranjang berhasil diubah.\n");
            return;
        }
    }
    printf("Keranjang tidak ditemukan.\n");
}

// Fungsi untuk menghapus item keranjang berdasarkan ID
void hapus_keranjang(int id_keranjang) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            for (int j = i; j < jumlah_keranjang - 1; j++) {
                keranjang_belanja[j] = keranjang_belanja[j + 1];
            }
            jumlah_keranjang--;
            printf("Keranjang berhasil dihapus.\n");
            return;
        }
    }
    printf("Keranjang tidak ditemukan.\n");
}



// Fungsi untuk melakukan checkout
void checkout(int id_keranjang, char tanggal_pembelian[]) {
    Checkout checkout_item;
    checkout_item.id_keranjang = id_keranjang;
    strcpy(checkout_item.tanggal_pembelian, tanggal_pembelian);

    checkout_data[jumlah_checkout] = checkout_item;
    jumlah_checkout++;
      printf("Checkout success\n");
}

// Fungsi untuk menambahkan laporan harian
void tambah_laporan(char tanggal_laporan[], int jumlah_item_laporan, float total_harga_laporan) {
    Laporan laporan;
    strcpy(laporan.tanggal_laporan, tanggal_laporan);
    laporan.jumlah_item_laporan = jumlah_item_laporan;
    laporan.total_harga_laporan = total_harga_laporan;

    laporan_harian[jumlah_laporan] = laporan;
    jumlah_laporan++;
      printf("lporan muncul\n");
}

// Fungsi untuk menampilkan daftar barang
void tampilkan_daftar_barang() {
    printf("Daftar Barang:\n");
    for (int i = 0; i < jumlah_barang; i++) {
        printf("%d. %s - Harga: %.2f - Stok: %d\n", daftar_barang[i].id, daftar_barang[i].nama_barang, daftar_barang[i].harga, daftar_barang[i].stok);
    }
}

// Fungsi untuk menampilkan keranjang belanja
void tampilkan_keranjang() {
    printf("Keranjang Belanja:\n");
    for (int i = 0; i < jumlah_keranjang; i++) {
        printf("%d. %s - Harga: %.2f - Quantity: %d\n", keranjang_belanja[i].id_barang, keranjang_belanja[i].nama_barang, keranjang_belanja[i].harga, keranjang_belanja[i].quantity);
    }
}

// Fungsi untuk menampilkan laporan harian
void tampilkan_laporan() {
    printf("Laporan Harian:\n");
    for (int i = 0; i < jumlah_laporan; i++) {
        printf("%s - Jumlah Item: %d - Total Harga: %.2f\n", laporan_harian[i].tanggal_laporan, laporan_harian[i].jumlah_item_laporan, laporan_harian[i].total_harga_laporan);
    }
}


void contoh_penggunaan_model() {
    
          tambah_barang(1, "Barang A", 10.0, 50, "Deskripsi Barang A");
   tambah_barang(2, "Barang B", 20.0, 30, "Deskripsi Barang B");
 tambah_barang(1, "Barang A", 10.0, 50, "Deskripsi Barang A");
    // Menampilkan daftar barang
   tampilkan_daftar_barang();


// Contoh penggunaan fitur pencarian barang
    int id_cari = 1;
    char nama_barang_cari[50] = "Barang B";

    Barang *barang_cari_id = cari_barang(id_cari, "");
    Barang *barang_cari_nama = cari_barang(-1, nama_barang_cari);

    if (barang_cari_id != NULL) {
        printf("Barang dengan ID %d ditemukan: %s - Harga: %.2f - Stok: %d\n", id_cari, barang_cari_id->nama_barang, barang_cari_id->harga, barang_cari_id->stok);
    } else {
        printf("Barang dengan ID %d tidak ditemukan.\n", id_cari);
    }

    if (barang_cari_nama != NULL) {
        printf("Barang dengan nama '%s' ditemukan: Harga: %.2f - Stok: %d\n", nama_barang_cari, barang_cari_nama->harga, barang_cari_nama->stok);
    } else {
        printf("Barang dengan nama '%s' tidak ditemukan.\n", nama_barang_cari);
    }

    // Menambahkan item ke keranjang belanja
   tambah_keranjang(1, 1, 3);
   tambah_keranjang(1, 2, 2);

    // Menampilkan keranjang belanja
   tampilkan_keranjang();


 // Menampilkan keranjang belanja sebelum pengeditan
    printf("Keranjang Belanja sebelum pengeditan:\n");
    tampilkan_keranjang();

    // Contoh penggunaan fitur edit keranjang
    int id_keranjang_edit = 1;  // Ganti dengan ID keranjang yang ingin Anda edit
    int new_quantity = 4;       // Ganti dengan jumlah item baru

    // Memanggil fungsi edit_keranjang untuk mengubah jumlah item pada keranjang
    edit_keranjang(id_keranjang_edit, new_quantity);

    // Menampilkan keranjang belanja setelah pengeditan
    printf("Keranjang Belanja setelah pengeditan:\n");
    tampilkan_keranjang();



    // Melakukan checkout
   checkout(1, "2024-01-06");

    // Menambahkan laporan harian
   tambah_laporan("2024-01-06", 5, 70.0);

    // Menampilkan laporan harian
   tampilkan_laporan();

 
    
}

// Fungsi untuk memasukkan nama merchant
void masukkan_nama_merchant() {
    printf("Masukkan nama merchant (default: kelompok 2 auto): ");
    fgets(nama_merchant, sizeof(nama_merchant), stdin);

    // Hapus karakter newline yang masuk bersamaan dengan nama
    size_t len = strlen(nama_merchant);
    if (len > 0 && nama_merchant[len - 1] == '\n') {
        nama_merchant[len - 1] = '\0';
    }

    // Set nama merchant ke default jika kosong
    if (nama_merchant[0] == '\0') {
        strcpy(nama_merchant, "Kelompok 2 auto");
    }
}


// Fungsi untuk memasukkan nama merchant
void masukkan_nama_kasir() {
    printf("Masukkan nama Kasir (default (kasir auto): ");
    fgets(nama_kasir, sizeof(nama_kasir), stdin);

    // Hapus karakter newline yang masuk bersamaan dengan nama
    size_t len = strlen(nama_kasir);
    if (len > 0 && nama_kasir[len - 1] == '\n') {
        nama_kasir[len - 1] = '\0';
    }

    // Set nama merchant ke default jika kosong
    if (nama_kasir[0] == '\0') {
        strcpy(nama_kasir, "kasir auto");
    }
}
// Fungsi inisialisasi program jika belum diinisialisasi
void inisialisasi_program() {
    if (!program_diinisialisasi) {
 printf("memulai inisiasi program...\n");
 
  masukkan_nama_merchant();
   printf("Nama Merchant: %s\n", nama_merchant);
     masukkan_nama_kasir();
   printf("Nama kasir: %s\n", nama_kasir);
        // Set flag bahwa program telah diinisialisasi
        program_diinisialisasi = 1;
    }
}





int main() {
    // Menambahkan beberapa contoh barang
   inisialisasi_program();
  //contoh_penggunaan_model();
    // ... (kode lainnya)

    return 0;
}
