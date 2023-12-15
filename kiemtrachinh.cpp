#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
class LaoDong {
public:
    string manv;
    string hoten;
    string ngaysinh;
    string loaihd;

    LaoDong() {
        this->manv = "";
        this->hoten = "";
        this->ngaysinh = "";
        this->loaihd = "";
    }

    LaoDong(string manv, string hoten, string ngaysinh, string loaihd) {
        this->manv = manv;
        this->hoten = hoten;
        this->ngaysinh = ngaysinh;
        this->loaihd = loaihd;
    }

    virtual void NhapThongTin() {
        cout << "Nhap ma NV: ";
        cin >> manv;
        cout << "Nhap ho ten: ";
        cin.ignore();
        getline(cin, hoten);
        cout << "Nhap ngay sinh: ";
        cin >> ngaysinh;
    }

    virtual double TinhLuong() const = 0;

    virtual void XuatThongTin() const {
        cout << "Ma NV: " << manv << endl;
        cout << "Ho ten: " << hoten << endl;
        cout << "Ngay sinh: " << ngaysinh << endl;
        cout << "Loai HD:" << loaihd << endl;
    }
};

class LDThoiVu : public LaoDong {
public:
    int soNgayCong;
    double tienLuongNgayCong;

    LDThoiVu() {
        this->soNgayCong = 0;
        this->tienLuongNgayCong = 0.0;
    }

    LDThoiVu(string manv, string hoten, string ngaysinh, string loaihd, int soNgayCong, double tienLuongNgayCong)
        : LaoDong(manv, hoten, ngaysinh, loaihd) {
        this->soNgayCong = soNgayCong;
        this->tienLuongNgayCong = tienLuongNgayCong;
    }

    void NhapThongTin() override {
        LaoDong::NhapThongTin();
        loaihd = "LD Thoi Vu";
        cout << "Nhap so ngay cong: ";
        cin >> soNgayCong;
        cout << "Nhap tien luong ngay cong: ";
        cin >> tienLuongNgayCong;
    }

    double TinhLuong() const override {
        double tienLuong = soNgayCong * tienLuongNgayCong;
        if (soNgayCong >= 25) {
            tienLuong += 1000000;
        }
        return tienLuong;
    }

    void XuatThongTin() const override {
        LaoDong::XuatThongTin();
        cout << "So ngay cong: " << soNgayCong << endl;
        cout << "Luong: " << TinhLuong() << " VND" << endl;
    }
};

class NVChinhThuc : public LaoDong {
public:
    double heSoLuong;
    double luongCoBan;
    string chucVu;

    NVChinhThuc() {
        this->heSoLuong = 0.0;
        this->luongCoBan = 0.0;
    }

    NVChinhThuc(string manv, string hoten, string ngaysinh, string loaihd, double heSoLuong, string chucVu)
        : LaoDong(manv, hoten, ngaysinh, loaihd) {
        this->heSoLuong = heSoLuong;
        this->chucVu = chucVu;
    }

    void NhapThongTin() override {
        LaoDong::NhapThongTin();
        loaihd = "NV Chinh Thuc"; 
        cout << "Nhap he so luong: ";
        cin >> heSoLuong;
        cout << "Nhap chuc vu (nhanvien/phophong/truongphong): ";
        cin >> chucVu;
    }

    double TinhLuong() const override {
        double luongCoBan = 1500000;
        double phuCap = 0;

        if (chucVu == "nhanvien") {
            phuCap = 500000;
        } else if (chucVu == "phophong") {
            phuCap = 700000;
        } else if (chucVu == "truongphong") {
            phuCap = 1000000;
        }

        return heSoLuong * luongCoBan + phuCap;
    }

    void XuatThongTin() const override {
        LaoDong::XuatThongTin();
        cout << "He so luong: " << heSoLuong << endl;
        cout << "Chuc vu: " << chucVu << endl;
        cout << "Luong: " << TinhLuong() << " VND" << endl;
    }
};

int main() {
    vector<LaoDong*> danhSachLaoDong;
    int luaChon;
	system("color B");
    do {
        cout << "=============== MENU ===============\n";
        cout << "[1] Them lao dong thoi vu\n";
        cout << "[2] Them lao dong chinh thuc\n";
        cout << "[3] Xuat thong tin tat ca lao dong\n";
        cout << "[4] Thong ke theo loai hop dong\n";
        cout << "[5] Thoat\n";
        cout << "====================================\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                LDThoiVu* ldThoiVu = new LDThoiVu();
                ldThoiVu->NhapThongTin();
                danhSachLaoDong.push_back(ldThoiVu);
                break;
            }
            case 2: {
                NVChinhThuc* nvChinhThuc = new NVChinhThuc();
                nvChinhThuc->NhapThongTin();
                danhSachLaoDong.push_back(nvChinhThuc);
                break;
            }
            case 3:
                cout << "=============== DANH SACH LAO DONG ===============\n";
                for (size_t i = 0; i < danhSachLaoDong.size(); i++) {
                    danhSachLaoDong[i]->XuatThongTin();
                    cout << "---------------------------------------------\n";
                }
                break;
            case 4: {
                int thoiVuCount = 0;
                int chinhThucCount = 0;

                for (size_t i = 0; i < danhSachLaoDong.size(); i++) {
                    if (dynamic_cast<LDThoiVu*>(danhSachLaoDong[i]) != NULL) {
                        thoiVuCount++;
                    } else if (dynamic_cast<NVChinhThuc*>(danhSachLaoDong[i]) != NULL) {
                        chinhThucCount++;
                    }
                }
                cout << "So lao dong thoi vu: " << thoiVuCount << endl;
                cout << "So nhan vien chinh thuc: " << chinhThucCount << endl;
                break;
            }
            case 5:
                cout << "Ket thuc chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
        }
    } while (luaChon != 5);

    for (size_t i = 0; i < danhSachLaoDong.size(); i++) {
        delete danhSachLaoDong[i];
    }
    return 0;
}

