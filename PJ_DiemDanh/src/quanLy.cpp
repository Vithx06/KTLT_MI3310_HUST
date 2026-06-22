#include "quanLy.h"
#include "fileIO.h"
#include "chucNang.h"
#include "nhatKy.h"
#include <iostream>
#include <iomanip>
using namespace std;


void xemDanhSachTKB(const LopHoc dsLop[], int soLuongLop)
{
    if (soLuongLop == 0)
    {
        cout << ">> Danh sach thoi khoa bieu hien dang trong!\n";
        GHI_LOG(LOG_WARN, "Danh sach TKB dang trong khi xem danh sach lop.");
        return;
    }

    cout << "\n========================== DANH SACH LOP VA TKB ==========================\n\n";

    cout << left
         << setw(6)  << "STT"
         << setw(10) << "Ma lop"
         << setw(38) << "Hoc phan"
         << setw(5)  << "Thu"
         << setw(13) << "Thoi gian"
         << setw(13) << "Phong"
         << setw(15) << "Tuan hoc"
         << endl;

    cout << string(100, '-') << endl;

    for (int i = 0; i < soLuongLop; i++)
    {
        cout << left
             << setw(6)  << i + 1
             << setw(10) << dsLop[i].thongTinTKB.maLop
             << setw(38) << dsLop[i].thongTinTKB.tenHP
             << setw(5)  << dsLop[i].thongTinTKB.thu
             << setw(13) << dsLop[i].thongTinTKB.thoiGian
             << setw(13) << dsLop[i].thongTinTKB.phongHoc
             << setw(15) << dsLop[i].thongTinTKB.tuanHoc
             << endl;
    }

    cout << string(100, '=') << endl;
}

void xemChiTietLop(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== XEM CHI TIET LOP HOC =====\n";
    string maLop;
    cout << "\nNhap ma lop can xem: ";
    cin >> maLop;

    int viTri = timViTriLop(dsLop, soLuongLop, maLop);

    if(viTri == -1)
    {
        cout << "Khong tim thay lop!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay lop khi xem chi tiet - Ma lop nhap: " + maLop);
        return;
    }

    docFileLopHoc(maLop, dsLop[viTri].bangDiemDanh);

    cout << "\n========== THONG TIN LOP ==========\n";
    cout << "Ma lop    : " << dsLop[viTri].thongTinTKB.maLop << endl;
    cout << "Ten HP    : " << dsLop[viTri].thongTinTKB.tenHP << endl;
    cout << "Thu       : " << dsLop[viTri].thongTinTKB.thu << endl;
    cout << "Thoi gian : " << dsLop[viTri].thongTinTKB.thoiGian << endl;
    cout << "Tuan hoc  : " << dsLop[viTri].thongTinTKB.tuanHoc << endl;
    cout << "Phong hoc : " << dsLop[viTri].thongTinTKB.phongHoc << endl;

    cout << "\n========== DANH SACH SINH VIEN ==========\n";

    BangDiemDanh &bdd = dsLop[viTri].bangDiemDanh;

    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        cout << i + 1 << ". "
             << bdd.danhSachSV[i].mssv
             << " - "
             << bdd.danhSachSV[i].hoTen
             << endl;
    }

    cout << "\nTong so sinh vien: "
         << bdd.soLuongSV
         << endl;

    GHI_LOG(LOG_INFO, "Da xem chi tiet lop - Lop: " + maLop + " | So sinh vien: " + soThanhChuoi(bdd.soLuongSV));
}

void moduleQuanLyLopHoc(LopHoc dsLop[], int& soLuongLop)
{
    int chon;

    do
    {
        cout << "\n===== QUAN LY LOP =====\n";
        cout << "1. Xem danh sach lop và tkb\n";
        cout << "2. Xem chi tiet 1 lop\n";

        cout << "0. Quay lai\n";

        chon = nhapSoNguyen("Nhap: ");

        switch(chon)
        {
            case 0:
                xoaManHinh();
                break;
            case 1:
                xoaManHinh();
                xemDanhSachTKB(dsLop,soLuongLop);
                break;
            case 2:
                xoaManHinh();
                xemChiTietLop(dsLop,soLuongLop);
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while(chon != 0);
}

