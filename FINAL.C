#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
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

// Deklarasi fungsi
bool is_angka(const char *string);


// Flag untuk memeriksa apakah program sudah diinisialisasi
int program_diinisialisasi = 0;
// Fungsi untuk menambahkan barang ke array
void dumping_barang(int id, char nama_barang[], float harga, int stok, char deskripsi[]) {
    if (jumlah_barang < 100) {
        Barang barang;
        barang.id = id;
        strncpy(barang.nama_barang, nama_barang, sizeof(barang.nama_barang) - 1);
        barang.harga = harga;
        barang.stok = stok;
        strncpy(barang.deskripsi, deskripsi, sizeof(barang.deskripsi) - 1);

        daftar_barang[jumlah_barang] = barang;
        jumlah_barang++;
       // printf("Data berhasil ditambahkan ke indeks %d.\n", jumlah_barang - 1);
    } else {
        printf("Error: Array daftar_barang is full.\n");
    }
}


void insert_initial_data() {
    Barang initial_data[] = {
      {1, "Ban Mobil", 2000000.0, NULL, "Ban mobil berukuran 15 inch."},
    {2, "Oli Mesin", 5000000.0, 100, "Oli mesin berkualitas tinggi untuk semua jenis kendaraan."},
    {3, "Busi Mobil", 8000000.0, 0, "Busi mobil tahan lama dengan kinerja optimal."},
    {4, "Filter Udara", 1500000.0, 80, "Filter udara untuk menjaga kualitas udara masuk ke mesin."},
    {5, "Kampas Rem", 2500000.0, 120, "Kampas rem berkualitas untuk sistem pengereman yang aman."},
    {6, "Wiper Mobil", 12000.0, 70, "Wiper mobil dengan desain yang efisien untuk membersihkan kaca."},
    {7, "Aki Mobil", 100000.0, 90, "Aki mobil dengan daya tahan tinggi."},
    {8, "Lampu Kepala", 18000.0, 60, "Lampu kepala berkualitas untuk penerangan maksimal."},
    {9, "Sparepart Rem", 30000.0, 40, "Sparepart rem untuk pemeliharaan rutin."},
    {10, "Pelumas Rantai", 8000.0, 75, "Pelumas rantai motor untuk perawatan optimal."},
    {11, "Radiator Coolant", 12000.0, 85, "Cairan pendingin radiator untuk menjaga suhu mesin."},
    {12, "Kaca Mobil", 40000.0, 25, "Kaca mobil dengan kekuatan dan ketahanan tinggi."},
    {13, "Kunci Inggris", 5000.0, 120, "Kunci inggris dengan berbagai ukuran untuk kebutuhan bengkel."},
    {14, "Kopling Motor", 35000.0, 50, "Kopling motor tahan lama untuk performa yang optimal."},
    {15, "Starter Motor", 25000.0, 40, "Starter motor untuk memastikan start mesin yang lancar."},
    {16, "Ban Motor", 100000.0, 60, "Ban motor dengan kualitas terbaik."},
    {17, "Oli Transmisi", 40000.0, 80, "Oli transmisi untuk kendaraan bertransmisi manual."},
    {18, "Kunci Roda", 7000.0, 110, "Kunci roda untuk membuka dan mengunci roda kendaraan."},
    {19, "Aki Motor", 80000.0, 70, "Aki motor dengan daya tahan tinggi."},
    {20, "Lampu Belakang", 15000.0, 45, "Lampu belakang untuk sinyal dan penerangan belakang."},
    {21, "Saringan Bensin", 10000.0, 55, "Saringan bensin untuk menyaring kotoran pada bahan bakar."},
    {22, "Kabel Busi", 5000.0, 65, "Kabel busi berkualitas tinggi untuk penghantaran listrik yang optimal."},
    {23, "Oli Rem", 20000.0, 30, "Oli rem untuk menjaga kinerja rem pada kendaraan."},
    {24, "Gantungan Kunci Mobil", 3000.0, 90, "Gantungan kunci mobil dengan desain unik."},
    {25, "Pelumas Persneling", 8000.0, 40, "Pelumas persneling untuk perawatan persneling kendaraan."},
    {26, "Kaca Spion", 30000.0, 20, "Kaca spion untuk pemeriksaan dan keselamatan saat berkendara."},
    {27, "Sparepart AC Mobil", 50000.0, 25, "Sparepart AC mobil untuk pemeliharaan sistem pendinginan."},
    {28, "Oli Gardan", 25000.0, 35, "Oli gardan untuk perawatan gardan kendaraan."},
    {29, "Sensor Parkir", 15000.0, 50, "Sensor parkir untuk membantu pengemudi saat parkir."},
    {30, "Kipas Radiator", 28000.0, 30, "Kipas radiator untuk menjaga suhu mesin tetap stabil."},
    {31, "Kunci Pas", 4000.0, 75, "Kunci pas dengan berbagai ukuran untuk kebutuhan bengkel."},
    {32, "Karburator Motor", 60000.0, 20, "Karburator motor untuk distribusi campuran udara dan bahan bakar."},
    {33, "Pompa Bensin", 40000.0, 30, "Pompa bensin untuk menyuplai bahan bakar ke mesin kendaraan."},
    {34, "Oli Power Steering", 15000.0, 40, "Oli power steering untuk menjaga kinerja sistem power steering."},
    {35, "Baut Roda", 2000.0, 120, "Baut roda untuk mengamankan roda pada kendaraan."},
    {36, "Aki Mobil Gel", 120000.0, 15, "Aki mobil tahan lama dengan teknologi gel."},
    {37, "Gembok Stir", 8000.0, 60, "Gembok stir untuk mencegah pencurian kendaraan."},
    {38, "Kaca Film Mobil", 50000.0, 25, "Kaca film mobil untuk menjaga privasi dan menangkal panas."},
    {39, "Pompa Air Wiper", 10000.0, 55, "Pompa air wiper untuk menyemprotkan air ke kaca mobil."},
    {40, "Kunci Kontak", 12000.0, 70, "Kunci kontak untuk menghidupkan dan mematikan mesin kendaraan."},
    {41, "Saringan Udara Motor", 7000.0, 80, "Saringan udara motor untuk menjaga kualitas udara masuk ke mesin."},
    {42, "Lever Gas Motor", 15000.0, 40, "Lever gas motor untuk mengendalikan aliran bahan bakar."},
    {43, "Karet Wiper", 5000.0, 90, "Karet wiper untuk pengganti yang aus pada wiper mobil."},
    {44, "Cover Mobil", 40000.0, 30, "Cover mobil untuk melindungi kendaraan dari debu dan cuaca."},
    {45, "Pompa Oli Motor", 25000.0, 45, "Pompa oli motor untuk distribusi oli ke berbagai bagian mesin."},
    {46, "Gelang Rem", 8000.0, 60, "Gelang rem untuk mendukung sistem pengereman kendaraan."},
    {47, "Stang Seher Motor", 30000.0, 25, "Stang seher motor untuk menggerakkan piston."},
    {48, "Oli Gardan Motor", 18000.0, 35, "Oli gardan motor untuk perawatan gardan kendaraan."},
    {49, "Lampu Sen Motor", 10000.0, 55, "Lampu sen motor untuk sinyal saat berkendara."},
    {50, "Pembersih Karburator", 7000.0, 80, "Pembersih karburator untuk menjaga kinerja karburator."},
    {51, "Gembok Rem", 12000.0, 40, "Gembok rem untuk mencegah pergerakan kendaraan saat parkir."},
    {52, "Oli Suspensi Motor", 15000.0, 30, "Oli suspensi motor untuk kenyamanan berkendara."},
    {53, "Pisau Kipas Radiator", 5000.0, 90, "Pisau kipas radiator untuk menjaga suhu mesin kendaraan."},
    {54, "Rantai Kunci Motor", 4000.0, 110, "Rantai kunci motor untuk memudahkan penyimpanan kunci."},
    {55, "Oli Rem DOT 4", 20000.0, 50, "Oli rem DOT 4 untuk sistem pengereman yang handal."},
    {56, "Tutup Radiator", 8000.0, 40, "Tutup radiator untuk melindungi radiator kendaraan."},
    {57, "Penyegar Udara Mobil", 12000.0, 60, "Penyegar udara mobil untuk keharuman di dalam kendaraan."},
    {58, "Selang Bensin", 6000.0, 75, "Selang bensin untuk menghubungkan tangki bahan bakar dengan mesin."},
    {59, "Gearbox Motor", 40000.0, 25, "Gearbox motor untuk penggerak sepeda motor."},
    {60, "Kunci Pas Torque", 5000.0, 100, "Kunci pas torque untuk mengencangkan baut dan mur."},
    {61, "Oli Gearbox Mobil", 25000.0, 35, "Oli gearbox mobil untuk perawatan gearbox kendaraan."},
    {62, "Cover Spion Mobil", 15000.0, 45, "Cover spion mobil untuk melindungi spion dari goresan."},
    {63, "Tromol Rem", 30000.0, 30, "Tromol rem untuk mendukung sistem pengereman kendaraan."},
    {64, "Karpet Mobil", 20000.0, 40, "Karpet mobil untuk melindungi lantai mobil dari kotoran."},
    {65, "Oli Saringan Udara", 10000.0, 55, "Oli saringan udara untuk menjaga kinerja saringan udara."},
    {66, "Kunci Inggris Set", 18000.0, 30, "Set kunci inggris dengan berbagai ukuran untuk kebutuhan bengkel."},
    {67, "Oli Rem DOT 3", 15000.0, 50, "Oli rem DOT 3 untuk sistem pengereman yang handal."},
    {68, "Filter Oli Motor", 7000.0, 80, "Filter oli motor untuk menyaring kotoran pada oli."},
    {69, "Lever Kopling Motor", 12000.0, 40, "Lever kopling motor untuk mengoperasikan kopling kendaraan."},
    {70, "Sensor Suhu Mesin", 18000.0, 35, "Sensor suhu mesin untuk memonitor suhu mesin kendaraan."},
    {71, "Wiper Blade", 6000.0, 65, "Wiper blade untuk pengganti yang aus pada wiper mobil."},
    {72, "Lampu Plat Nomor", 5000.0, 75, "Lampu plat nomor untuk penerangan di bagian belakang kendaraan."},
    {73, "Klem Selang", 2000.0, 110, "Klem selang untuk mengamankan sambungan selang pada kendaraan."},
    {74, "Radiator Motor", 50000.0, 20, "Radiator motor untuk menjaga suhu mesin kendaraan."},
    {75, "Saringan Oli Mobil", 8000.0, 40, "Saringan oli mobil untuk menjaga kualitas oli kendaraan."},
    {76, "Kunci Roda Anti Maling", 15000.0, 30, "Kunci roda anti maling untuk mencegah pencurian roda kendaraan."},
    {77, "Oli Transmisi Otomatis", 30000.0, 25, "Oli transmisi otomatis untuk kendaraan otomatis."},
    {78, "Karet Wiper Motor", 4000.0, 90, "Karet wiper motor untuk pengganti yang aus pada wiper motor."},
    {79, "Lampu Hazard", 10000.0, 50, "Lampu hazard untuk memberi tahu pengguna jalan saat darurat."},
    {80, "Pegas Rem Motor", 5000.0, 70, "Pegas rem motor untuk mendukung sistem pengereman kendaraan."},
    {81, "Oli Suspensi Mobil", 15000.0, 35, "Oli suspensi mobil untuk kenyamanan berkendara."},
    {82, "Saklar Lampu Motor", 8000.0, 60, "Saklar lampu motor untuk mengontrol penerangan kendaraan."},
    {83, "Kunci Pas L", 6000.0, 85, "Kunci pas L untuk akses ke ruang sempit pada kendaraan."},
    {84, "Koil Motor", 25000.0, 40, "Koil motor untuk menghasilkan arus listrik pada busi kendaraan."},
    {85, "Oli Gardan Mobil", 20000.0, 30, "Oli gardan mobil untuk perawatan gardan kendaraan."},
    {86, "Tang Set", 18000.0, 25, "Set tang untuk berbagai kebutuhan perbaikan kendaraan."},
    {87, "Oli Rem DOT 5", 25000.0, 35, "Oli rem DOT 5 untuk sistem pengereman yang handal."},
    {88, "Saringan Oli Motor", 6000.0, 55, "Saringan oli motor untuk menyaring kotoran pada oli."},
    {89, "Sensor Tekanan Ban", 12000.0, 40, "Sensor tekanan ban untuk memonitor tekanan udara pada ban."},
    {90, "Lampu LED Mobil", 30000.0, 20, "Lampu LED mobil untuk penerangan yang lebih terang."},
    {91, "Oli Rem DOT 4 Racing", 40000.0, 30, "Oli rem DOT 4 racing untuk performa pengereman yang maksimal."},
    {92, "Kunci L Wrench", 4000.0, 75, "Kunci L wrench untuk akses ke ruang sempit pada kendaraan."},
    {93, "Oli Motor 2 Tak", 15000.0, 50, "Oli motor 2 tak untuk kendaraan motor dengan mesin 2 tak."},
    {94, "Busi Iridium", 10000.0, 60, "Busi iridium untuk pembakaran yang lebih efisien."},
    {95, "Kunci Filter Oli", 8000.0, 40, "Kunci filter oli untuk membuka dan menutup filter oli kendaraan."},
    {96, "Oli Transmisi Manual", 20000.0, 35, "Oli transmisi manual untuk kendaraan bertransmisi manual."},
    {97, "Lampu Tanda Belok Motor", 5000.0, 70, "Lampu tanda belok motor untuk memberi tahu arah belok kendaraan."},
    {98, "Klem Selang Bensin", 2000.0, 90, "Klem selang bensin untuk mengamankan sambungan selang bensin."},
    {99, "Tutup Tangki Bensin", 3000.0, 80, "Tutup tangki bensin untuk melindungi tangki bensin kendaraan."},
    {100, "Sparepart Ekzos", 45000.0, 25, "Sparepart ekzos untuk perawatan sistem pembuangan kendaraan."}

};
 for (int i = 0; i < sizeof(initial_data) / sizeof(initial_data[0]); i++) {
        dumping_barang(initial_data[i].id, initial_data[i].nama_barang, initial_data[i].harga, initial_data[i].stok, initial_data[i].deskripsi);
    }
     printf("100 Data berhasil ditambahkan ke Dataset Indeks.\n");
}
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
    tampilkan_keranjang();
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
          //  printf("Keranjang berhasil dihapus.\n");
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
      printf("laporan muncul\n");
}

// Fungsi untuk menampilkan daftar barang
void tampilkan_daftar_barang() {
    printf("Daftar Barang:\n");
    for (int i = 0; i < jumlah_barang; i++) {
        printf("ID Item: %d. - Nama Barang: %s - Harga: %.2f - Stok: %d - Deskripsi: %s \n", daftar_barang[i].id, daftar_barang[i].nama_barang, daftar_barang[i].harga, daftar_barang[i].stok, daftar_barang[i].deskripsi);
    }
}
// Fungsi untuk menampilkan keranjang belanja
void tampilkan_keranjang() {
    printf("\n\033[1;33m===========================\n");
    printf("   \033[1mKeranjang Belanja\n");
    printf("\033[1;33m===========================\033[0m\n");

    for (int i = 0; i < jumlah_keranjang; i++) {
        printf("id keranjang: %d, id barang: %d. %s - Harga: %.2f - Quantity: %d\n", keranjang_belanja[i].id_keranjang, keranjang_belanja[i].id_barang, keranjang_belanja[i].nama_barang, keranjang_belanja[i].harga, keranjang_belanja[i].quantity);
    }
     printf("\033[1;33m===========================\n\n");
}


void preview_keranjang(int id_keranjang) {
    printf("\n\033[1;33m===========================\n");
    printf("   \033[1mPreview Keranjang Belanja\n");
    printf("\033[1;33m===========================\033[0m\n");

    // Variables to store total information
    float total_harga_keseluruhan = 0.0;
    int total_barang = 0;
    int total_quantity = 0;

    printf("-------------------------------\n");
    printf("ID Keranjang: %d\n", id_keranjang);
    printf("-------------------------------\n");

    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            printf("\nID Barang: %d. %s\n", keranjang_belanja[i].id_barang, keranjang_belanja[i].nama_barang);
            printf("Harga per item: %.2f\n", keranjang_belanja[i].harga);
            printf("Quantity: %d\n", keranjang_belanja[i].quantity);

            // Calculate subtotal for the item
            float subtotal_harga_item = keranjang_belanja[i].harga * keranjang_belanja[i].quantity;
            printf("Subtotal harga item: %.2f\n", subtotal_harga_item);

            // Accumulate totals
            total_harga_keseluruhan += subtotal_harga_item;
            total_barang++;
            total_quantity += keranjang_belanja[i].quantity;

            printf("-------------------------------\n");
        }
    }

    float taxes = total_harga_keseluruhan * 0.11;
    float total_harga_keseluruhan_after_tax = total_harga_keseluruhan + taxes;

    printf("Total Barang: %d\n", total_barang);
    printf("Total Quantity: %d\n", total_quantity);
    printf("\nTotal Harga Keseluruhan (Non-PPN): %.2f\n", total_harga_keseluruhan);
    printf("PPN (11%%): %.2f\n", taxes);
    printf("Total Harga Keseluruhan (Dengan PPN): %.2f\n", total_harga_keseluruhan_after_tax);
    printf("==============================\n");
}

// Function to handle the checkout process
void query_checkout(int id_keranjang) {
    // Variables to store user input
    char input[20];
    int nominal_pembayaran;
    printf("\n\033[1;33m===========================\n");
    printf("   \033[1mPembayaran Keranjang : ID #%d\n", id_keranjang);
    printf("\033[1;33m===========================\033[0m\n");
    while (1) {
        // Prompt the user for the payment amount
        printf("\nSilahkan masukkan nominal pembayaran (kelipatan 1000 rupiah, ketik 'Q' untuk membatalkan proses): ");
        scanf("%s", input);

        // Check if the user wants to cancel the process
        if (input[0] == 'Q' || input[0] == 'q') {
            printf("Checkout dibatalkan.\n");
            hapus_keranjang(id_keranjang);
            return;
        }

        // Convert the input to an integer
        nominal_pembayaran = atoi(input);

        // Check if the input is a multiple of 1000 rupiah
        if (nominal_pembayaran % 1000 == 0 && nominal_pembayaran > 0) {
            // Valid payment amount, perform the checkout process
            //printf("Nominal pembayaran valid: %d rupiah\n", nominal_pembayaran);
            process_bayar(id_keranjang, nominal_pembayaran);
            // Perform checkout logic here
            // ...

            // Exit the loop
            break;
        } else {
            // Invalid payment amount, prompt again
            printf("Nominal pembayaran tidak valid. Harus kelipatan 1000 rupiah.\n");
        }
    }

    // Continue with the checkout process
    // ...
}

void process_bayar(int id_keranjang, int nominal_bayar){

    // Variables to store total information
    float total_harga_keseluruhan = 0.0;
    int total_barang = 0;
    int total_quantity = 0;
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            // Calculate subtotal for the item
            float subtotal_harga_item = keranjang_belanja[i].harga * keranjang_belanja[i].quantity;
            // Accumulate totals
            total_harga_keseluruhan += subtotal_harga_item;
            total_barang++;
            total_quantity += keranjang_belanja[i].quantity;
        }
    }

    float taxes = total_harga_keseluruhan * 0.11;
    float total_harga_keseluruhan_after_tax = total_harga_keseluruhan + taxes;
    int kembalian = nominal_bayar - total_harga_keseluruhan_after_tax;
    int total_kembalian = kembalian;


    if (total_kembalian >= 0) {
        
        struk(id_keranjang, nominal_bayar);
      
    } else {
    printf("PEMBAYARAN GAGAL: NOMINAL TIDAK CUKUP\n");
    int choice;

    do {
        printf("\n Solusi:\n");
        printf("1. Edit item pembelian\n");
        printf("2. Lanjutkan pembayaran\n");
        printf("Pilih menu (1/2): ");
        scanf("%d", &choice);

        switch (choice) {
case 1:
    // Edit Keranjang: Prompt for action choice
    int action_choice;
    printf("Pilih aksi:\n");
    printf("1. Hapus item dari keranjang\n");
    printf("2. Edit jumlah pembelian item di keranjang\n");

    // Force input (ignore invalid input)
    while (1) {
        printf("Masukkan pilihan (1-2): ");
        if (scanf("%d", &action_choice) == 1 && (action_choice == 1 || action_choice == 2)) {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan angka 1 atau 2.\n");
            while (getchar() != '\n');  // Clear input buffer
        }
    }

  switch (action_choice) {
    case 1:
        // Hapus item dari keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin dihapus: ");
        int id_barang_to_remove;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_remove) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to remove the item
        hapus_item_keranjang(id_keranjang, id_barang_to_remove);
         preview_keranjang(id_keranjang);

    while (1) {
        printf("\nApa yang ingin Anda lakukan selanjutnya?\n");
        printf("1. Cancel\n");
        printf("2. Edit Keranjang\n");
        printf("3. Checkout\n");

        printf("Pilih aksi (1-3): ");

        if (scanf("%d", &action_choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            printf("Input tidak valid. Masukkan integer.\n");
            continue;
        }

        switch (action_choice) {
            case 1:
               // Cancel: Prompt for confirmation
    char confirmation;
    printf("Anda yakin ingin membatalkan keranjang? (y/n): ");
    
    // Force input (ignore invalid input)
    while (1) {
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'n') {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan 'y' atau 'n': ");
            while (getchar() != '\n');  // Clear input buffer
        }
    }   
    if (confirmation == 'y') {
        // Do something if 'y' (you can add your logic here)
       hapus_keranjang(id_keranjang);
        //printf("Keranjang berhasil dibatalkan.\n");
        // Additional logic or just return if needed
        return;
    } else {
          preview_keranjang(id_keranjang);

        // Back to the loop if 'n'
        break;
    }
case 2:
    // Edit Keranjang: Prompt for action choice
    int action_choice;
    printf("Pilih aksi:\n");
    printf("1. Hapus item dari keranjang\n");
    printf("2. Edit jumlah pembelian item di keranjang\n");

    // Force input (ignore invalid input)
    while (1) {
        printf("Masukkan pilihan (1-2): ");
        if (scanf("%d", &action_choice) == 1 && (action_choice == 1 || action_choice == 2)) {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan angka 1 atau 2.\n");
            while (getchar() != '\n');  // Clear input buffer
        }
    }

  switch (action_choice) {
    case 1:
        // Hapus item dari keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin dihapus: ");
        int id_barang_to_remove;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_remove) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to remove the item
        hapus_item_keranjang(id_keranjang, id_barang_to_remove);
         preview_keranjang(id_keranjang);
        break;

    case 2:
        // Edit jumlah pembelian item di keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin diedit quantity nya: ");
        int id_barang_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Prompt for new quantity
        printf("Masukkan Quantity baru untuk ID Barang Tersebut: ");
        int new_quantity_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &new_quantity_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to edit the quantity
        edit_jumlah_pembelian(id_keranjang, id_barang_to_edit, new_quantity_to_edit);
        preview_keranjang(id_keranjang);
        break;

    default:
        // This should not happen with the current validation, but added for completeness
        printf("Pilihan tidak valid.\n");
} 
break;

            case 3:
                // Checkout: Implement your checkout logic here
              query_checkout(id_keranjang);
                return;
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-3.\n");
        }
    }
                 


    break;

    case 2:
        // Edit jumlah pembelian item di keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin diedit quantity nya: ");
        int id_barang_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Prompt for new quantity
        printf("Masukkan Quantity baru untuk ID Barang Tersebut: ");
        int new_quantity_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &new_quantity_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to edit the quantity
        edit_jumlah_pembelian(id_keranjang, id_barang_to_edit, new_quantity_to_edit);
        preview_keranjang(id_keranjang);

    while (1) {
        printf("\nApa yang ingin Anda lakukan selanjutnya?\n");
        printf("1. Cancel\n");
        printf("2. Edit Keranjang\n");
        printf("3. Checkout\n");

        printf("Pilih aksi (1-3): ");

        if (scanf("%d", &action_choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            printf("Input tidak valid. Masukkan integer.\n");
            continue;
        }

        switch (action_choice) {
            case 1:
               // Cancel: Prompt for confirmation
    char confirmation;
    printf("Anda yakin ingin membatalkan keranjang? (y/n): ");
    
    // Force input (ignore invalid input)
    while (1) {
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'n') {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan 'y' atau 'n': ");
            while (getchar() != '\n');  // Clear input buffer
        }
    }   
    if (confirmation == 'y') {
        // Do something if 'y' (you can add your logic here)
       hapus_keranjang(id_keranjang);
        //printf("Keranjang berhasil dibatalkan.\n");
        // Additional logic or just return if needed
        return;
    } else {
          preview_keranjang(id_keranjang);

        // Back to the loop if 'n'
        break;
    }
case 2:
    // Edit Keranjang: Prompt for action choice
    int action_choice;
    printf("Pilih aksi:\n");
    printf("1. Hapus item dari keranjang\n");
    printf("2. Edit jumlah pembelian item di keranjang\n");

    // Force input (ignore invalid input)
    while (1) {
        printf("Masukkan pilihan (1-2): ");
        if (scanf("%d", &action_choice) == 1 && (action_choice == 1 || action_choice == 2)) {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan angka 1 atau 2.\n");
            while (getchar() != '\n');  // Clear input buffer
        }
    }

  switch (action_choice) {
    case 1:
        // Hapus item dari keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin dihapus: ");
        int id_barang_to_remove;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_remove) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to remove the item
        hapus_item_keranjang(id_keranjang, id_barang_to_remove);
         preview_keranjang(id_keranjang);
        break;

    case 2:
        // Edit jumlah pembelian item di keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin diedit quantity nya: ");
        int id_barang_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Prompt for new quantity
        printf("Masukkan Quantity baru untuk ID Barang Tersebut: ");
        int new_quantity_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &new_quantity_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to edit the quantity
        edit_jumlah_pembelian(id_keranjang, id_barang_to_edit, new_quantity_to_edit);
        preview_keranjang(id_keranjang);
        break;

    default:
        // This should not happen with the current validation, but added for completeness
        printf("Pilihan tidak valid.\n");
} 
break;

            case 3:
                // Checkout: Implement your checkout logic here
              query_checkout(id_keranjang);
                return;
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-3.\n");
        }
    }
                 

        break;

    default:
        // This should not happen with the current validation, but added for completeness
        printf("Pilihan tidak valid.\n");
} 
break;
case 2:
                // Call function to lanjutkan pembayaran
                query_checkout(id_keranjang);
break;
default:
                printf("Pilihan tidak valid. Silakan masukkan 1 atau 2.\n");
        }
    } while (choice != 1 && choice != 2);
}

    printf("\n-------------------------------\n");
    printf("==============================\n");

}
// Function to update quantity in the data array
void update_quantity_in_array(int id_barang, int new_quantity) {
    for (int i = 0; i < jumlah_barang; i++) {
        if (daftar_barang[i].id == id_barang) {
            // Update the quantity for the specified item
            daftar_barang[i].stok -= new_quantity;
            break;  // Assuming each item has a unique ID
        }
    }
}

int cetak_tanggal() {
    time_t t;
    struct tm *info;
    char buffer[80];
    time(&t);
    info = localtime(&t);

    // Format tanggal dd-mm-yyyy
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", info);

    // Mencetak tanggal ke layar
    printf("Date: %s\n", buffer);

    // Convert the entire date string to an integer
    int date_as_integer;
    sscanf(buffer, "%", &date_as_integer);
     int copyright = "By Febriansah Dirgantara";
    return copyright;
}


void struk(int id_keranjang, int nominal_bayar) {
  


    printf("\n\033[1;33m===========================\n");
    printf("           \033[1mStruk Belanja\n");
    printf("          \033[1m%d\n", cetak_tanggal());
    printf("\033[1;33m===========================\033[0m\n");

    // Variables to store total information
    float total_harga_keseluruhan = 0.0;
    int total_barang = 0;
    int total_quantity = 0;

    printf("-------------------------------\n");
    printf("ID Keranjang: %d\n", id_keranjang);
    printf("-------------------------------\n");

    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            printf("\nID Barang: %d. %s\n", keranjang_belanja[i].id_barang, keranjang_belanja[i].nama_barang);
            printf("Harga per item: %.2f\n", keranjang_belanja[i].harga);
            printf("Quantity: %d\n", keranjang_belanja[i].quantity);

            // Calculate subtotal for the item
            float subtotal_harga_item = keranjang_belanja[i].harga * keranjang_belanja[i].quantity;
            printf("Subtotal harga item: %.2f\n", subtotal_harga_item);

            // Accumulate totals
            total_harga_keseluruhan += subtotal_harga_item;
            total_barang++;
            total_quantity += keranjang_belanja[i].quantity;
        }
    }

    float taxes = total_harga_keseluruhan * 0.11;
    float total_harga_keseluruhan_after_tax = total_harga_keseluruhan + taxes;
    int kembalian = nominal_bayar - total_harga_keseluruhan_after_tax;
    int total_kembalian = kembalian;

    printf("Total Barang: %d\n", total_barang);
    printf("Total Quantity: %d\n", total_quantity);
    printf("-------------------------------\n");
    printf("HARGA NON PPN: %.2f\n", total_harga_keseluruhan);
    printf("-------------------------------\n");
    printf("HARGA DENGAN PPN: %.2f\n", total_harga_keseluruhan_after_tax);
    printf("-------------------------------\n");
    printf("-------------------------------\n");
    printf("NOMINAL BAYAR: %d\n", nominal_bayar);
    printf("-------------------------------\n");
     printf("-------------------------------\n");
    if (total_kembalian > 0) {
        printf("KEMBALI: %d\n", total_kembalian);
    } else if(total_kembalian == 0){
        printf("KEMBALI: 0");
    }
    printf("-------------------------------\n");
    printf("-------------------------------\n");
    if (total_kembalian >= 0) {
        printf("STATUS: LUNAS\n");
          for (int i = 0; i < jumlah_keranjang; i++) {
            if (keranjang_belanja[i].id_keranjang == id_keranjang) {
                update_quantity_in_array(keranjang_belanja[i].id_barang, keranjang_belanja[i].quantity);
            }
        }

          hapus_keranjang(id_keranjang);
    } else {
        printf("PEMBAYARAN GAGAL\n");
        query_checkout(id_keranjang);
    }
    //printf("\n-------------------------------\n");
    //printf("==============================\n");


  
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
int rand_kode_keranjang() {
    // Seed the random number generator with the current time
    srand(time(NULL));

    return rand() % 1000 + 19732; // Return the randomly generated ID
}

// Fungsi untuk mengecek apakah ID keranjang sudah ada
int check_id_keranjang(int id_keranjang) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            return 1;  // ID found
        }
    }
    return 0;  // ID not found
}
void query_barang() {
    
    printf("\nTambahkan barang:\n");

    // Input data barang dari user
    int id = rand() % 1000 + 1; // id di-generate secara acak
    char nama_barang[50], deskripsi[100];
    float harga;
    int stok;
    char input_harga[20], input_stok[20]; // Gunakan string sementara untuk validasi input

    printf("Masukkan nama barang: ");
    scanf(" %[^\n]", nama_barang);

    // Validasi input harga
    do {
        printf("Masukkan harga barang (Angka): ");
        scanf("%s", input_harga);
        if (!is_angka(input_harga)) {
            printf("Harga harus berupa angka. Silakan coba lagi.\n");
        } else {
            harga = atof(input_harga);
            break;
        }
    } while (true);

    // Validasi input stok
    do {
        printf("Masukkan stok barang (Angka): ");
        scanf("%s", input_stok);
        if (!is_angka(input_stok)) {
            printf("Stok harus berupa angka. Silakan coba lagi.\n");
        } else {
            stok = atoi(input_stok);
            break;
        }
    } while (true);

    printf("Masukkan deskripsi barang: ");
    scanf(" %[^\n]", deskripsi);

    // Panggil fungsi tambah_barang
    tambah_barang(id, nama_barang, harga, stok, deskripsi);

    // Prompt apakah ingin menambah barang lagi
    int pilihan;

    do {
        printf("Tambah barang lagi? (1: Ya / 0: Tidak): ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            query_barang();  // Rekursif untuk menambah barang lagi
        } else if (pilihan == 0) {
            cek_data_barang();
        } else {
            printf("Pilihan tidak valid. Silakan masukkan 1 atau 0.\n");
        }

    } while (pilihan != 0 && pilihan != 1);
}

// Fungsi untuk memeriksa apakah sebuah string adalah angka
bool is_angka(const char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i]) && string[i] != '.') {
            return false;
        }
    }
    return true;
}



void cek_data_barang(){
    if (jumlah_barang != 0) {
        tampilkan_daftar_barang();
        search_barang();
    } else {
    printf("\n\033[1;33m===========================\n");
    printf("   \033[1mStok Otomotif Kosong\n");
    printf("\033[1;33m===========================\033[0m\n");

       query_barang();
    }
}
void search_barang() {
    int pilihan;
    char buffer[50];
    printf("\n\033[1;33m===========================\n");
    printf("   \033[1mSearch Barang\n");
    printf("\033[1;33m===========================\033[0m\n");

    do {
        printf("\n1. Cari berdasarkan Nama\n");
        printf("2. Cari berdasarkan ID\n");
        printf("Pilih jenis pencarian (1/2): ");

        // Membaca input sebagai string
        scanf("%s", buffer);

        // Validasi apakah input adalah angka
        if (sscanf(buffer, "%d", &pilihan) != 1) {
            printf("Input bukan angka. Silakan masukkan nilai integer(1 atau 2).\n");
            pilihan = 0;  // Memberi nilai default agar loop terus berlanjut
            while (getchar() != '\n');  // Membersihkan input buffer
        } else {
            if (pilihan == 1) {
                char nama_cari[50];
                printf("Masukkan nama barang yang dicari: ");
                scanf("%s", nama_cari);
                cari_barang_by_nama(nama_cari);
            } else if (pilihan == 2) {
                int id_cari;
                printf("Masukkan ID barang yang dicari: ");
                scanf("%d", &id_cari);
                cari_barang_by_id(id_cari);
            } else {
                printf("Pilihan tidak valid. Silakan masukkan 1 atau 2.\n");
            }
        }
    } while (pilihan != 1 && pilihan != 2);

    printf("\033[1;33m===========================\033[0m\n");

}

void cari_barang_by_id(int id_cari) {
    int ditemukan = 0;

    for (int i = 0; i < jumlah_barang; i++) {
        if (daftar_barang[i].id == id_cari) {
            ditemukan = 1;
            printf("Barang ditemukan (By ID):\n");
            printf("%d. %s - Harga: %.2f - Stok: %d\n", daftar_barang[i].id, daftar_barang[i].nama_barang, daftar_barang[i].harga, daftar_barang[i].stok);
            printf("\033[1;33m===========================\033[0m\n");
            break;  // Stop searching once found
        }
    }

     if (ditemukan) {
        query_keranjang();
    } else {
        printf("Barang tidak ditemukan.\n");
    }
}

// Function to search for a barang by name and display the result
void cari_barang_by_nama(char nama_cari[]) {
    int ditemukan = 0;
    int found_once = 0;

    for (int i = 0; i < jumlah_barang; i++) {
        if (strcasestr(daftar_barang[i].nama_barang, nama_cari) != NULL) {
            ditemukan = 1;

            if (!found_once) {
                printf("Barang ditemukan (By Name):\n");
                found_once = 1;
            } 

            printf("%d. %s - Harga: %.2f - Stok: %d\n", daftar_barang[i].id, daftar_barang[i].nama_barang, daftar_barang[i].harga, daftar_barang[i].stok);
            printf("\033[1;33m===========================\033[0m\n");
        } 
    }

    if (ditemukan) {
        query_keranjang();
    } else {
        printf("Barang tidak ditemukan.\n");
    }
}


int cek_stok_by_id(int id_cari) {
    int ditemukan = 0;
    int jumlah_barang = sizeof(daftar_barang) / sizeof(daftar_barang[0]);

    for (int i = 0; i < jumlah_barang; i++) {
        if (daftar_barang[i].id == id_cari) {
            ditemukan = 1;
            return daftar_barang[i].stok; // Return the stock value
        }
    }

    if (!ditemukan) {
        //printf("Stok Barang tidak ditemukan.\n"); //debugging
    }

    // Return -1 to indicate that the item was not found
    return -1;
}
int cek_barang_by_id(int id_cari) {
    int ditemukan = 0;
    int jumlah_barang = sizeof(daftar_barang) / sizeof(daftar_barang[0]);

    for (int i = 0; i < jumlah_barang; i++) {
        if (daftar_barang[i].id == id_cari) {
            ditemukan = 1;
            return 1; // Return the stock value
        }
    }

    if (!ditemukan) {
        //printf("Stok Barang tidak ditemukan.\n"); //debugging
    }

    // Return -1 to indicate that the item was not found
    return -1;
}

int search_keranjang_by_id(int id_keranjang) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang) {
            // Keranjang found
            return keranjang_belanja[i].id_keranjang;
        }
    }

    // Keranjang not found
    return 0;
}


// Fungsi untuk mengedit jumlah pembelian item di keranjang berdasarkan ID Keranjang dan ID Barang
void edit_jumlah_pembelian(int id_keranjang, int id_barang, int new_quantity) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang && keranjang_belanja[i].id_barang == id_barang) {
            keranjang_belanja[i].quantity = new_quantity;
            printf("Jumlah pembelian item di keranjang berhasil diubah.\n");
            return;
        }
    }
    printf("Item tidak ditemukan dalam keranjang.\n");
}

// Fungsi untuk menghapus item dari keranjang berdasarkan ID Keranjang dan ID Barang
void hapus_item_keranjang(int id_keranjang, int id_barang) {
    for (int i = 0; i < jumlah_keranjang; i++) {
        if (keranjang_belanja[i].id_keranjang == id_keranjang && keranjang_belanja[i].id_barang == id_barang) {
            for (int j = i; j < jumlah_keranjang - 1; j++) {
                keranjang_belanja[j] = keranjang_belanja[j + 1];
            }
            jumlah_keranjang--;
            printf("Item berhasil dihapus dari keranjang.\n");
            return;
        }
    }
    printf("Item tidak ditemukan dalam keranjang.\n");
}

// Function to handle the shopping process
void query_keranjang() {
    int id_barang, jumlah_pembelian, sisa_stok, id_keranjang, cek_barang;
    //int id_keranjang_baru = 0;
     int id_keranjang_baru = rand_kode_keranjang();
        printf("\n\033[1;33m====================================\n");
        printf("\033[1m Add To Cart \n");
        printf("\033[1;33m====================================\033[0m\n");

    while (1) {
        // Loop until a valid integer ID is entered
        while (1) {
            // Munculkan prompt untuk input ID barang
            printf("Masukkan ID barang untuk keranjang: ");

            // Check if the input is an integer
            if (scanf("%d", &id_barang) != 1) {
                // Clear the input buffer in case of non-integer input
                while (getchar() != '\n');

                // Prompt for a valid integer input
                printf("Input id barang tidak valid. Masukkan integer.\n");
                continue; // Retry the loop
            }

            break;
        }

        // Loop until a valid quantity is entered
        while (1) {
            // Munculkan prompt untuk input jumlah pembelian
            printf("Masukkan Jumlah Pembelian barang (999 untuk membatalkan proses): ");

            // Check if the input is an integer
            if (scanf("%d", &jumlah_pembelian) != 1) {
                // Clear the input buffer in case of non-integer input
                while (getchar() != '\n');

                // Prompt for a valid integer input
                printf("Input jumlah pembelian tidak valid. Masukkan integer.\n");
                continue; // Retry the loop
            }    if (jumlah_pembelian == 999) {
             printf("Proses pembelian dibatalkan.\n");
         
         } else {
         cek_barang = cek_barang_by_id(id_barang);
         if(cek_barang == 1) {
            sisa_stok = cek_stok_by_id(id_barang);

            if (sisa_stok != 0) {
                // Check if the stock is sufficient
                if (sisa_stok < jumlah_pembelian) {
                    printf("Sisa stok tidak mencukupi untuk jumlah pembelian yang diinginkan\n");
                    continue; // Retry the loop
                } else if (sisa_stok == 0) {
                    printf("Stok barang habis\n");
                    query_keranjang();
                } else {
                    // Search for the shopping cart by ID
                    id_keranjang = id_keranjang_baru;

                    // Add the item to the shopping cart
                    tambah_keranjang(id_keranjang, id_barang, jumlah_pembelian);
                    printf("Berhasil menambahkan item ke dalam keranjang\n");

                    // Ask the user if they want to add more items
                    char input;
                    printf("Apakah Anda ingin menambahkan barang lain? (y/n): ");
                    scanf(" %c", &input);

                    // Validate user input
                    while (input != 'y' && input != 'n') {
                        printf("Pilihan tidak valid. Masukkan 'y' atau 'n': ");
                        scanf(" %c", &input);
                    }

                    if (input == 'y') {
                        // If 'y', start again from entering the item ID
                        break;
                    } else {
                        // If 'n', display cart preview and prompt for further actions

    preview_keranjang(id_keranjang);

    int action_choice;

    while (1) {
        printf("\nApa yang ingin Anda lakukan selanjutnya?\n");
        printf("1. Cancel\n");
        printf("2. Edit Keranjang\n");
        printf("3. Checkout\n");

        printf("Pilih aksi (1-3): ");

        if (scanf("%d", &action_choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            printf("Input tidak valid. Masukkan integer.\n");
            continue;
        }

        switch (action_choice) {
            case 1:
               // Cancel: Prompt for confirmation
    char confirmation;
    printf("Anda yakin ingin membatalkan keranjang? (y/n): ");
    
    // Force input (ignore invalid input)
    while (1) {
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'n') {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan 'y' atau 'n': ");
            while (getchar() != '\n');  // Clear input buffer
        }
    }   
    if (confirmation == 'y') {
        // Do something if 'y' (you can add your logic here)
       hapus_keranjang(id_keranjang);
        //printf("Keranjang berhasil dibatalkan.\n");
        // Additional logic or just return if needed
        return;
    } else {
          preview_keranjang(id_keranjang);

        // Back to the loop if 'n'
        break;
    }
case 2:
    // Edit Keranjang: Prompt for action choice
    int action_choice;
    printf("Pilih aksi:\n");
    printf("1. Hapus item dari keranjang\n");
    printf("2. Edit jumlah pembelian item di keranjang\n");

    // Force input (ignore invalid input)
    while (1) {
        printf("Masukkan pilihan (1-2): ");
        if (scanf("%d", &action_choice) == 1 && (action_choice == 1 || action_choice == 2)) {
            break;
        } else {
            printf("Pilihan tidak valid. Masukkan angka 1 atau 2.\n");
            while (getchar() != '\n');  // Clear input buffer
        }
    }

  switch (action_choice) {
    case 1:
        // Hapus item dari keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin dihapus: ");
        int id_barang_to_remove;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_remove) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to remove the item
        hapus_item_keranjang(id_keranjang, id_barang_to_remove);
         preview_keranjang(id_keranjang);
        break;

    case 2:
        // Edit jumlah pembelian item di keranjang: Implement your logic here
        printf("Masukkan ID Barang yang ingin diedit quantity nya: ");
        int id_barang_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &id_barang_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Prompt for new quantity
        printf("Masukkan Quantity baru untuk ID Barang Tersebut: ");
        int new_quantity_to_edit;

        // Validate if the input is an integer
        while (scanf("%d", &new_quantity_to_edit) != 1) {
            printf("Input tidak valid. Masukkan angka: ");
            while (getchar() != '\n'); // Clear the input buffer
        }

        // Call the function to edit the quantity
        edit_jumlah_pembelian(id_keranjang, id_barang_to_edit, new_quantity_to_edit);
        preview_keranjang(id_keranjang);
        break;

    default:
        // This should not happen with the current validation, but added for completeness
        printf("Pilihan tidak valid.\n");
} 
break;

            case 3:
                // Checkout: Implement your checkout logic here
              query_checkout(id_keranjang);
                return;
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-3.\n");
        }
    }
                    }
                }
            } else {
                printf("Gagal Fetching data stok (NULL/KOSONG)..., Silahkan coba unit lain atau Coba lagi \n");
               
            }
            } else {
           printf("ID Barang Tidak terdaftar didalam data\n");
             }
         }
            // Exit the loop if a valid quantity is entered
            break;
        }
    }
}

void menu(){
  int choice;

    while (1) {
        printf("\n\n\n");
        printf("\033[1;33m=============================\n");
        printf("               \033[1mMenu\n");
        printf("\033[1;33m=============================\033[0m\n");
        printf("1. New Order\n");
        printf("2. Tampilkan Daftar Barang\n");
        printf("3. Keluar\n");

        printf("Pilih menu (1-3): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            printf("Input tidak valid. Masukkan integer.\n");
            continue;
        }

        switch (choice) {
            case 1:
                cek_data_barang();
                break;
            case 2:
                tampilkan_daftar_barang();
                break;
            case 3:
                printf("Keluar dari program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-3.\n");
        }
    }



}


// Fungsi inisialisasi program jika belum diinisialisasi
void inisialisasi_program() {
    if (!program_diinisialisasi) {
        printf("\033[1;33m====================================\n");
        printf("\033[1mAdvanced Kasir Program by Kelompok 2\n");
         printf("\033[1m%d\n", cetak_tanggal());
        printf("\033[1mAnggota: \n- Febriansah Dirgantara (2350081084) \n- Fahmi Nasruddin (2350081077) \n- Faiz Ghani (2350081083)\n");


        printf("\033[1;33m====================================\033[0m\n");

        printf("\033[1mMemulai inisiasi program...\033[0m\n");
        
        masukkan_nama_merchant();
        printf("\033[1mNama Merchant:\033[0m %s\n", nama_merchant);
        
        masukkan_nama_kasir();
        printf("\033[1mNama Kasir:\033[0m %s\n", nama_kasir);
        
        // Set flag bahwa program telah diinisialisasi
        program_diinisialisasi = 1;
        
        printf("\033[1mInisiasi Selesai...\033[0m\n");
        printf("\033[1;33m====================================\n");
    }
}
int main() {
    // Menambahkan beberapa contoh barang
    inisialisasi_program();
    // contoh_penggunaan_model();
    // rand_kode_keranjang();
    insert_initial_data();

    menu();
    return 0;
}
