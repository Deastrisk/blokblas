# Blockblast 🚀


## 🛠️ Prasyarat

Pastikan Anda telah menginstal versi berikut:

* C++ Latest
* Git

# 📚 Panduan Dasar Git untuk Kontributor

Selamat datang di repositori proyek kami! Dokumen ini berfungsi sebagai panduan cepat dan ringkas tentang cara berkontribusi menggunakan perintah dasar Git: `clone`, `commit`, `pull`, dan `push`.

Jika Anda benar-benar baru di Git, disarankan untuk melihat dokumentasi resmi [Git SCM](https://git-scm.com/doc) untuk pemahaman yang lebih mendalam.

## 🛠️ Prasyarat

Sebelum memulai, pastikan Anda telah:

1.  Menginstal **Git** di mesin lokal Anda.
2.  Memiliki akun **GitHub** dan telah dikonfigurasi (SSH atau Personal Access Token) untuk *push* dan *pull* dari repositori ini.

---

## 1. Mengatur Workspace Lokal (Clone)

Langkah pertama adalah mendapatkan salinan kode proyek ini ke komputer Anda.

1.  Buka Terminal atau Git Bash Anda.
2.  Arahkan ke direktori tempat Anda ingin menyimpan proyek.
3.  Jalankan perintah `git clone`:

    ```bash
    git clone [https://github.com/NamaOrganisasi/NamaRepo.git](https://github.com/NamaOrganisasi/NamaRepo.git)
    ```

4.  Masuk ke direktori proyek yang baru dikloning:

    ```bash
    cd NamaRepo
    ```

---

## 2. Membuat Perubahan dan Menyimpan (*Commit*)

Setelah Anda membuat perubahan pada file-file proyek, Anda perlu "menyimpan" perubahan tersebut secara lokal menggunakan `commit`.

### A. Menambahkan File ke Staging Area (`git add`)

Perintah ini memberi tahu Git file mana saja yang ingin Anda sertakan dalam komit berikutnya.

```bash
# Untuk menambahkan file tertentu
git add nama-file-yang-diubah.js

# Untuk menambahkan semua perubahan dari semua file yang dilacak
git add .