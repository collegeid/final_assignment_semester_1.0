#include <pqxx/pqxx>
#include <iostream>

// Fungsi untuk menghubungkan ke database
pqxx::connection connectToDatabase() {
    try {
        pqxx::connection conn("dbname=peltjzzc user=peltjzzc password=UHfJBbXXZMh9tgiCi7ssDP3kqIccGDrm hostaddr=127.0.0.1 port=5432");

        if (conn.is_open()) {
            std::cout << "Connected to database successfully." << std::endl;
        } else {
            throw std::runtime_error("Failed to connect to database.");
        }

        return conn;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}

// Fungsi untuk melakukan operasi database
void performDatabaseOperations(pqxx::connection &conn) {
    try {
        // Lakukan operasi database di sini
        // Contoh: pqxx::work W(conn); W.exec("SQL_QUERY_HERE"); W.commit();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}

// =========================//





////////==========BARANG (CRUDS)============///////

// Fungsi untuk membuat tabel "barang" jika belum ada

// Function to create the 'barang' table
void createTableBarang(pqxx::connection &conn) {
    try {
        pqxx::work txn(conn);

        // Query to create the 'barang' table in the 'public' schema
        txn.exec(R"(
            CREATE TABLE IF NOT EXISTS barang (
                id SERIAL PRIMARY KEY,
                nama_barang VARCHAR(255),
                merk VARCHAR(255),
                jenis VARCHAR(10) CHECK (jenis IN ('item', 'sparepart', 'service')),
                deskripsi TEXT,
                stok INT,
                status VARCHAR(15) CHECK (status IN ('ready', 'pre-order'))
            )
        )");

        txn.commit();
        std::cout << "Table 'barang' created successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error creating table 'barang': " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}


// Struktur data untuk menyimpan informasi barang
struct BarangInfo {
    std::string nama_barang;
    std::string merk;
    std::string deskripsi;
};

// Fungsi untuk menambahkan data barang
void addBarangDumping(pqxx::connection &conn, const BarangInfo &barangInfo, const std::string &jenis, int stok, const std::string &status) {
    try {
        pqxx::work txn(conn);

        // Parameterized query untuk menambahkan data
        pqxx::result result = txn.exec_params(
            "INSERT INTO barang (nama_barang, merk, jenis, deskripsi, stok, status) VALUES ($1, $2, $3, $4, $5, $6) RETURNING id",
            barangInfo.nama_barang, barangInfo.merk, jenis, barangInfo.deskripsi, stok, status
        );

        txn.commit();
        std::cout << "Data added successfully. New ID: " << result[0][0].as<int>() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}


// Fungsi untuk menambahkan data barang
void addBarang(pqxx::connection &conn, const std::string &nama_barang, const std::string &merk,
               const std::string &jenis, const std::string &deskripsi, int stok, const std::string &status) {
    try {
        pqxx::work txn(conn);

        // Parameterized query untuk menambahkan data
        pqxx::result result = txn.exec_params(
            "INSERT INTO barang (nama_barang, merk, jenis, deskripsi, stok, status) VALUES ($1, $2, $3, $4, $5, $6) RETURNING id",
            nama_barang, merk, jenis, deskripsi, stok, status
        );

        txn.commit();
        std::cout << "Data added successfully. New ID: " << result[0][0].as<int>() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}

// Fungsi untuk mengedit data barang
void editBarang(pqxx::connection &conn, int id, const std::string &nama_barang, const std::string &merk,
                const std::string &jenis, const std::string &deskripsi, int stok, const std::string &status) {
    try {
        pqxx::work txn(conn);

        // Parameterized query untuk mengedit data
        txn.exec_params(
            "UPDATE barang SET nama_barang=$1, merk=$2, jenis=$3, deskripsi=$4, stok=$5, status=$6 WHERE id=$7",
            nama_barang, merk, jenis, deskripsi, stok, status, id
        );

        txn.commit();
        std::cout << "Data updated successfully for ID: " << id << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error updating data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}

// Fungsi untuk menghapus data barang
void deleteBarang(pqxx::connection &conn, int id) {
    try {
        pqxx::work txn(conn);

        // Parameterized query untuk menghapus data
        txn.exec_params("DELETE FROM barang WHERE id=$1", id);

        txn.commit();
        std::cout << "Data deleted successfully for ID: " << id << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error deleting data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}

// Fungsi untuk membaca data barang
void selectBarang(pqxx::connection &conn) {
    try {
        pqxx::work txn(conn);

        // Query untuk membaca data
        pqxx::result result = txn.exec("SELECT * FROM barang");

        // Menampilkan hasil pembacaan data
        for (const auto &row : result) {
            std::cout << "ID: " << row["id"].as<int>()
                      << ", Nama Barang: " << row["nama_barang"].as<std::string>()
                      << ", Merk: " << row["merk"].as<std::string>()
                      << ", Jenis: " << row["jenis"].as<std::string>()
                      << ", Deskripsi: " << row["deskripsi"].as<std::string>()
                      << ", Stok: " << row["stok"].as<int>()
                      << ", Status: " << row["status"].as<std::string>() << std::endl;
        }

        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Error selecting data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}
// Fungsi untuk membaca data barang berdasarkan ID
void selectBarangById(pqxx::connection &conn, int id) {
    try {
        pqxx::work txn(conn);

        // Query untuk membaca data
        pqxx::result result = txn.exec("SELECT * FROM barang WHERE id = " + std::to_string(id));

        // Menampilkan hasil pembacaan data
        for (const auto &row : result) {
            std::cout << "ID: " << row["id"].as<int>()
                      << ", Nama Barang: " << row["nama_barang"].as<std::string>()
                      << ", Merk: " << row["merk"].as<std::string>()
                      << ", Jenis: " << row["jenis"].as<std::string>()
                      << ", Deskripsi: " << row["deskripsi"].as<std::string>()
                      << ", Stok: " << row["stok"].as<int>()
                      << ", Status: " << row["status"].as<std::string>() << std::endl;
        }

        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Error selecting data: " << e.what() << std::endl;
        throw;  // Re-throw exception to be caught by the caller
    }
}


///===============END BARANG===============///
int main_init() {
    try {
        // Menghubungkan ke database
        pqxx::connection conn = connectToDatabase();

        // Lakukan operasi database
        //performDatabaseOperations(conn);
        // ======= BARANG ===== ///

       // Membuat tabel "barang" jika belum ada
       // createTableBarang(conn);

//=====DUMPING DATA BARANG======//

 // List oli, kendaraan, dan sparepart beserta informasi merk dan deskripsi
 std::vector<BarangInfo> OliList = {
   {"Pertamina Enduro", "Pertamina", "Oli mesin berkualitas tinggi dengan teknologi pembersih untuk mesin yang bersih."},
    {"GTX High Mileage", "Castrol", "Oli mesin khusus untuk kendaraan dengan kilometer tinggi."},
    {"Shell Helix Ultra", "Shell", "Oli mesin sintetis dengan performa tinggi."},
    {"Quaker State Advanced Durability", "Quaker State", "Oli mesin dengan perlindungan tinggi terhadap keausan."},
    {"Yamalube", "Yamaha", "Oli mesin resmi dari Yamaha untuk performa optimal."},
    {"Honda Genuine Oil", "Honda", "Oli mesin asli dari Honda untuk kinerja yang andal."},
    {"Elf Evolution", "Elf", "Oli mesin dengan formula sintetis untuk performa luar biasa."},
    {"Xado Atomic Oil", "Xado", "Oli mesin dengan teknologi revolusioner untuk perlindungan ekstra."},
    {"Motul 8100 X-cess", "Motul", "Oli mesin 100% sintetis dengan performa tinggi."},
    {"Liqui Moly Synthoil High Tech", "Liqui Moly", "Oli mesin sintetis dengan formula modern."},
    {"Amsoil Signature Series", "Amsoil", "Oli mesin sintetis untuk perlindungan maksimal."},
    {"Valvoline Full Synthetic", "Valvoline", "Oli mesin sintetis dengan teknologi deterjen canggih."},
    {"Royal Purple HPS", "Royal Purple", "Oli mesin sintetis dengan performa tinggi dan perlindungan maksimal."},
    {"Pennzoil Platinum", "Pennzoil", "Oli mesin sintetis dengan formula Platinum untuk perlindungan superior."},
    {"Mobil 1 Extended Performance", "Mobil 1", "Oli mesin sintetis dengan performa tinggi dan perlindungan lama."},
    {"Motul 300V Power Racing", "Motul", "Oli mesin 100% sintetis untuk performa balap."},
    {"Fuchs Titan GT1", "Fuchs", "Oli mesin sintetis dengan perlindungan tinggi terhadap aus dan oksidasi."},
    {"Kixx PAO Racing", "GS Caltex", "Oli mesin sintetis untuk performa balap dan keberlanjutan."},
    {"Liqui Moly Top Tec 4100", "Liqui Moly", "Oli mesin dengan performa tinggi dan perlindungan terhadap sludge."},
    {"Motul 8100 Eco-nergy", "Motul", "Oli mesin dengan formula ramah lingkungan untuk efisiensi bahan bakar."},
    {"Elf Excellium NF", "Elf", "Oli mesin dengan teknologi Fuel Economy untuk penghematan bahan bakar."}
};

std::vector<BarangInfo> kendaraanList = {
    {"Toyota Fortuner", "Toyota", "SUV tangguh dengan performa tinggi dan kenyamanan berkendara."},
    {"Honda CR-V", "Honda", "SUV kompak dengan desain elegan dan fitur canggih."},
    {"Suzuki Ertiga", "Suzuki", "MPV yang luas dan irit bahan bakar."},
    {"Yamaha R15", "Yamaha", "Motor sport berkualitas tinggi dengan desain agresif."},
    {"Mitsubishi Outlander", "Mitsubishi", "SUV dengan teknologi canggih dan kenyamanan maksimal."},
    {"Kawasaki Versys", "Kawasaki", "Motor adventure dengan performa tinggi dan desain yang serbaguna."},
    {"Honda Jazz", "Honda", "Hatchback sporty dengan efisiensi bahan bakar tinggi."},
    {"Toyota Avanza", "Toyota", "MPV yang luas dengan desain kompak."},
    {"Suzuki Swift", "Suzuki", "Hatchback stylish dengan kinerja dinamis."},
    {"Yamaha NMAX", "Yamaha", "Skuter matik premium dengan desain modern."},
    {"Mitsubishi Xpander", "Mitsubishi", "MPV dengan desain elegan dan ruang interior yang luas."},
    {"Kawasaki Ninja", "Kawasaki", "Motor sport berkualitas tinggi dengan desain aerodinamis."},
    {"Honda CBR1000RR", "Honda", "Motor sport dengan performa tinggi dan desain balap."},
    {"Toyota Camry", "Toyota", "Sedan mewah dengan kenyamanan dan teknologi tinggi."},
    {"Suzuki Jimny", "Suzuki", "Off-road SUV dengan desain ikonik."},
    {"Yamaha MT-15", "Yamaha", "Motor naked sport dengan gaya agresif."},
    {"Mitsubishi Pajero Sport", "Mitsubishi", "SUV tangguh dengan performa off-road."}
    };


        std::vector<BarangInfo> sparepartList = {
           {"Rem Brembo", "Brembo", "Sistem pengereman cakram unggul untuk performa pengereman yang lebih baik."},
    {"Busi Denso", "Denso", "Busi berkualitas tinggi untuk pembakaran yang efisien."},
    {"Filter Oli WIX", "WIX", "Filter oli berkualitas untuk menjaga kebersihan mesin."},
    {"Kampas Rem Akebono", "Akebono", "Kampas rem berkualitas tinggi untuk keamanan berkendara."},
    {"Aki GS Power", "GS", "Aki berkualitas tinggi untuk daya tahan yang baik."},
    {"Lampu Depan Philips", "Philips", "Lampu depan berkualitas untuk visibilitas maksimal."},
    {"Saringan Udara K&N", "K&N", "Saringan udara berkualitas tinggi untuk aliran udara optimal."},
    {"Oli Gardan Mobil 1", "Mobil 1", "Oli gardan sintetis untuk perlindungan dan pelumasan yang optimal."},
    {"Busi Iridium NGK", "NGK", "Busi iridium untuk pembakaran yang lebih efisien dan tahan lama."},
    {"Filter Bensin Bosch", "Bosch", "Filter bensin berkualitas tinggi untuk penyaringan optimal."},
    {"Kampas Kopling Exedy", "Exedy", "Kampas kopling berkualitas untuk kinerja kopling yang responsif."},
    {"Oli Rem Motul DOT 5.1", "Motul", "Oli rem kualitas tinggi untuk performa pengereman yang konsisten."},
    {"Wiper Blade Valeo", "Valeo", "Wiper blade berkualitas untuk membersihkan kaca depan dengan baik."},
    {"Suspensi KYB Excel-G", "KYB", "Suspensi berkualitas tinggi untuk kenyamanan dan stabilitas berkendara."},
    {"Kopling Kit Sachs", "Sachs", "Kit kopling lengkap untuk penggantian yang mudah dan kinerja optimal."},
    {"Oli Transmisi Castrol", "Castrol", "Oli transmisi untuk melumasi dan melindungi komponen transmisi."},
    {"Filter Udara Mann", "Mann", "Filter udara yang efisien untuk membersihkan udara sebelum masuk ke mesin."},
    {"Lampu Belakang Hella", "Hella", "Lampu belakang berkualitas untuk penerangan belakang yang baik."},
    {"Oli Rem DOT 4 Valvoline", "Valvoline", "Oli rem kualitas tinggi untuk sistem pengereman hidrolik."},
    {"Koil Ignisi Bosch", "Bosch", "Koil ignisi untuk penyalaan yang handal dan efisien."}
     };

        // Perulangan untuk menambahkan data oli
        for (const auto &oli : OliList) {
            //addBarangDumping(conn, oli, "item", 50, "ready");
        }

        // Perulangan untuk menambahkan data kendaraan
        for (const auto &kendaraan : kendaraanList) {
            //addBarangDumping(conn, kendaraan, "item", 20, "pre-order");
        }

        // Perulangan untuk menambahkan data sparepart
        for (const auto &sparepart : sparepartList) {
           //addBarangDumping(conn, sparepart, "sparepart", 30, "ready");
        }
        // ========END DUMPING DATA BARANG =====///
        // Menambahkan data barang satu satu
       //addBarang(conn, "Oli Castrol", "Castrol Indonesia", "item", "oli berkualitas", 100, "ready");

        // Mengedit data barang
        //editBarang(conn, 2, "Laptop", "HP", "item", "Updated laptop description", 15, "pre-order");

        // Membaca dan menampilkan data barang
        //selectBarang(conn);

        // Membaca dan menampilkan data barang berdasarkan id
        //selectBarangById(conn, 2);

        // Menghapus data barang
        //deleteBarang(conn, 1);
        //////====== END BARANG ====//


        // Tutup koneksi
        conn.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}





int main() {
    try {
        // Connect to the database
        pqxx::connection conn = connectToDatabase();

        // Display welcome message and prompt for dealer name
        std::cout << "Silahkan ketik nama Otomotif anda, atau gunakan default (kelompok 2): ";
        std::string dealerName;
        std::getline(std::cin, dealerName);

        if (dealerName.empty()) {
            dealerName = "kelompok 2";  // Default dealer name
        }

    std::cout << "Silahkan ketik nama anda (sebagai kasir), atau gunakan default (unjani kasir): ";
        std::string kasirname;
        std::getline(std::cin, kasirname);
     if (kasirname.empty()) {
            kasirname = "Kasir Unjani";  // Default dealer name
        }
        std::cout << "Inisiasi " << dealerName << ", Sukses!" << std::endl;
       std::cout << "Hai " << kasirname << ", selamat datang!" << std::endl;

        int choice;
        while (true) {
            // Display menu
            std::cout << "\nMenu:\n";
            std::cout << "1. Barang\n";
            std::cout << "2. Order (Soon)\n";
            std::cout << "3. Checkout (Soon)\n";
            std::cout << "4. Payment (Soon)\n";
            std::cout << "5. Laporan (Soon)\n";
            std::cout << "0. Keluar\n";
            std::cout << "Pilih menu (0-5): ";
            std::cin >> choice;
            std::cin.ignore();  // Consume the newline character

            switch (choice) {
                case 1:
                    // Barang menu
                    int barangChoice;
                    while (true) {
                        // Display Barang menu
                        std::cout << "\nMenu Barang:\n";
                        std::cout << "1. List Barang\n";
                        std::cout << "2. Add Barang\n";
                        std::cout << "3. Edit Barang\n";
                        std::cout << "4. Delete Barang\n";
                        std::cout << "5. Search Barang by ID\n";
                        std::cout << "0. Kembali\n";
                        std::cout << "Pilih menu (0-5): ";
                        std::cin >> barangChoice;
                        std::cin.ignore();  // Consume the newline character

                        switch (barangChoice) {
                            case 1:
                                // List Barang
                                selectBarang(conn);
                                break;
                           case 2:
                // Add Barang
                {
                    std::string namaBarang, merk, jenis, deskripsi, status;
                    int stok;

                    std::cout << "Masukkan Nama Barang: ";
                    std::getline(std::cin, namaBarang);
                    std::cout << "Masukkan Merk: ";
                    std::getline(std::cin, merk);
                    std::cout << "Masukkan Jenis (item/sparepart/service): ";
                    std::getline(std::cin, jenis);
                    std::cout << "Masukkan Deskripsi: ";
                    std::getline(std::cin, deskripsi);
                    std::cout << "Masukkan Stok: ";
                    std::cin >> stok;
                    std::cin.ignore();  // Consume the newline character
                    std::cout << "Masukkan Status (ready/pre-order): ";
                    std::getline(std::cin, status);

                    addBarang(conn, namaBarang, merk, jenis, deskripsi, stok, status);
                    std::cout << "Data Barang berhasil ditambahkan.\n";
                }
                break;
                            case 3:
    // Edit Barang
    {
        int editId;
        std::cout << "Masukkan ID Barang yang akan diedit: ";
        std::cin >> editId;
        std::cin.ignore();  // Consume the newline character

        // Check if the barang with the given ID exists
        pqxx::work txn(conn);
        pqxx::result result = txn.exec_params("SELECT * FROM barang WHERE id = $1", editId);
        txn.commit();

        if (result.empty()) {
            std::cout << "Barang dengan ID tersebut tidak ditemukan. Silakan coba lagi.\n";
        } else {
            // Retrieve existing data for display
            selectBarangById(conn, editId);

            // Prompt users for new values
            std::string newNamaBarang, newMerk, newJenis, newDeskripsi, newStatus;
            int newStok;

            std::cout << "Masukkan Nama Barang baru: ";
            std::getline(std::cin, newNamaBarang);
            std::cout << "Masukkan Merk baru: ";
            std::getline(std::cin, newMerk);
            std::cout << "Masukkan Jenis baru (item/sparepart/service): ";
            std::getline(std::cin, newJenis);
            std::cout << "Masukkan Deskripsi baru: ";
            std::getline(std::cin, newDeskripsi);
            std::cout << "Masukkan Stok baru: ";
            std::cin >> newStok;
            std::cin.ignore();  // Consume the newline character
            std::cout << "Masukkan Status baru (ready/pre-order): ";
            std::getline(std::cin, newStatus);

            // After editing, call the editBarang function
            editBarang(conn, editId, newNamaBarang, newMerk, newJenis, newDeskripsi, newStok, newStatus);

            std::cout << "Data Barang berhasil diedit.\n";
        }
    }
    break;
                            
                            case 4:
                                // Delete Barang
                                   // Search Barang by ID
                                int deleteId;
                                std::cout << "Masukkan ID Barang yang akan di hapus: ";
                                std::cin >> deleteId;
                                std::cin.ignore();  // Consume the newline character
                                deleteBarang(conn, deleteId);
                                break;
                            break;
                            case 5:
                                // Search Barang by ID
                                int searchId;
                                std::cout << "Masukkan ID Barang: ";
                                std::cin >> searchId;
                                std::cin.ignore();  // Consume the newline character
                                selectBarangById(conn, searchId);
                                break;
                            case 0:
                                // Kembali
                                break;
                            default:
                                std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                        }

                        if (barangChoice == 0) {
                            break;  // Break from the Barang menu loop
                        }
                    }
                    break;
                case 2:
                    // Order (Soon)
                    std::cout << "Menu ini akan segera hadir.\n";
                    break;
                case 3:
                    // Checkout (Soon)
                    std::cout << "Menu ini akan segera hadir.\n";
                    break;
                case 4:
                    // Payment (Soon)
                    std::cout << "Menu ini akan segera hadir.\n";
                    break;
                case 5:
                    // Laporan (Soon)
                    std::cout << "Menu ini akan segera hadir.\n";
                    break;
                case 0:
                    // Keluar
                    std::cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!\n";
                    conn.close();
                    return 0;
                default:
                    std::cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
