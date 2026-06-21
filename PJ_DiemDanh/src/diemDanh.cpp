#include "diemDanh.h"
#include "fileIO.h"
#include "chucNang.h"
#include "nhatKy.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void ghiNhanDiemDanh(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== GHI NHAN DIEM DANH =====";
    string maLop;
    cout << "\n\nNhap ma lop: ";
    cin >> maLop;

    int viTri = timViTriLop(dsLop, soLuongLop, maLop);

    if(viTri == -1)
    {
        cout << "Khong tim thay lop!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay lop khi ghi nhan diem danh - Ma lop nhap: " + maLop);
        return;
    }

    docFileLopHoc(maLop, dsLop[viTri].bangDiemDanh);
    BangDiemDanh &bdd = dsLop[viTri].bangDiemDanh;

    int buoiSo = 1;
    if(bdd.soLuongSV == 0)
    {
        cout << "Lop chua co sinh vien!\n";
        GHI_LOG(LOG_WARN, "Lop chua co sinh vien, khong the ghi nhan diem danh - Lop: " + maLop);
        return;
    }
    else
    {
        buoiSo = bdd.danhSachSV[0].diemDanh.length() + 1;
    }

    string ngay;
    cin.ignore();
    cout << "Nhap ngay diem danh: ";
    getline(cin, ngay);

    cout << "Day la buoi diem danh so: " << buoiSo << endl;

    string ngayFile = chuanHoaNgay(ngay);
    string tenFile = "data/DiemDanh/" + maLop + "_" + ngayFile + ".csv";

    if(kiemTraFileTonTai(tenFile))
    {
        cout << "\nDa ton tai file diem danh ngay nay!\n";
        cout << "1. Ghi de\n";
        cout << "0. Huy\n";
        int chon = nhapSoNguyenTrongKhoang("Nhap: ", 0, 1);

        if(chon == 0) return;
    }

    ofstream file(tenFile.c_str());
    if(!file.is_open())
    {
        cout << "Khong tao duoc file diem danh!\n";
        cout << "Hay kiem tra thu muc data/DiemDanh da ton tai chua.\n";
        GHI_LOG(LOG_ERROR, "Khong tao duoc file diem danh - File: " + tenFile);
        return;
    }

    file << "MSSV,HoTen,TrangThai,BuoiSo\n";

    cout << "\n===== DIEM DANH =====\n";
    cout << "Quy uoc:\n";
    cout << "1 - Co mat\n";
    cout << "2 - Vang co phep\n";
    cout << "3 - Vang khong phep\n\n";

    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        cout << i + 1 << ". " << bdd.danhSachSV[i].mssv << " - " << bdd.danhSachSV[i].hoTen << endl;

        int trangThai = nhapSoNguyenTrongKhoang("Nhap trang thai: ", 1, 3);

        string ketQua = trangThaiToChuoi(char('0' + trangThai));

        bdd.danhSachSV[i].diemDanh += char('0' + trangThai);

        file << bdd.danhSachSV[i].mssv << ","
             << bdd.danhSachSV[i].hoTen << ","
             << ketQua << ","
             << buoiSo << "\n";
    }
    file.close();

    luuFileLopHoc(maLop, bdd);

    cout << "\nDa luu diem danh vao: " << tenFile << endl;
    cout << "Da cap nhat file lop hoc.\n";

    GHI_LOG(LOG_INFO,
            "Ghi nhan diem danh thanh cong - Lop: " + maLop + " | Ngay: " + ngayFile +
            " | Buoi so: " + soThanhChuoi(buoiSo) +
            " | Si so: " + soThanhChuoi(bdd.soLuongSV));
}

void xemDiemDanhLop()
{
    cout << "\n===== XEM DU LIEU DIEM DANH CUA LOP =====";
    string maLop;
    cout << "\n\nNhap ma lop: ";
    cin >> maLop;

    BangDiemDanh bdd;
    docFileLopHoc(maLop, bdd);

    if(bdd.soLuongSV == 0)
    {
        cout << "Lop khong co sinh vien!\n";
        return;
    }

    int soBuoi = bdd.danhSachSV[0].diemDanh.length();

    cout << "\n===== BANG DIEM DANH LOP " << maLop << " =====\n\n";
    cout << left << setw(6) << "STT" << setw(12) << "MSSV" << setw(20) << "Ho Ten";

    for(int i = 0; i < soBuoi; i++)
    {
        cout << setw(6) << ("B" + soThanhChuoi(i + 1));
    }
    cout << endl;

    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        cout << left << setw(6) << i + 1 << setw(12) << bdd.danhSachSV[i].mssv << setw(20) << bdd.danhSachSV[i].hoTen;

        for(int j = 0; j < soBuoi; j++)
        {
            char tt = bdd.danhSachSV[i].diemDanh[j];
            cout << setw(6) << trangThaiToChuoi(tt);
        }
        cout << endl;
    }
}

void capNhatDiemDanh()
{
    string maLop;
    cout << "\n===== SUA DIEM DANH =====\n";
    cout << "\nNhap ma lop: ";
    cin >> maLop;

    BangDiemDanh bdd;
    docFileLopHoc(maLop, bdd);

    if(bdd.soLuongSV == 0)
    {
        cout << "Lop khong co sinh vien!\n";
        GHI_LOG(LOG_WARN, "Lop khong co sinh vien khi sua diem danh - Lop: " + maLop);
        return;
    }

    long long mssv = nhapSoNguyenLon("Nhap MSSV can sua: ");

    int viTri = timViTriSinhVien(bdd, mssv);

    if(viTri == -1)
    {
        cout << "Khong tim thay sinh vien!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay sinh vien khi sua diem danh - Lop: " + maLop + " | MSSV: " + soThanhChuoi(mssv));
        return;
    }

    SinhVien &sv = bdd.danhSachSV[viTri];
    int soBuoi = sv.diemDanh.length();

    if(soBuoi == 0)
    {
        cout << "Sinh vien chua co du lieu diem danh!\n";
        GHI_LOG(LOG_WARN, "Sinh vien chua co du lieu diem danh - Lop: " + maLop + " | MSSV: " + soThanhChuoi(mssv));
        return;
    }

    cout << "\n===== LICH SU DIEM DANH =====\n";
    for(int i = 0; i < soBuoi; i++)
    {
        cout << "Buoi " << i + 1 << ": " << trangThaiToChuoi(sv.diemDanh[i]) << endl;
    }

    int buoiSua = nhapSoNguyenTrongKhoang("\nNhap buoi can sua: ", 1, soBuoi);

    cout << "\nTrang thai hien tai: ";
    char cu = sv.diemDanh[buoiSua - 1];
    cout << trangThaiToChuoi(cu);

    cout << "\n\n1. Co mat" << "\n2. Vang co phep" << "\n3. Vang khong phep";

    int moi = nhapSoNguyenTrongKhoang("\nNhap trang thai moi: ", 1, 3);

    sv.diemDanh[buoiSua - 1] = char('0' + moi);

    luuFileLopHoc(maLop, bdd);
    cout << "\nCap nhat diem danh thanh cong!\n";

    GHI_LOG(LOG_INFO,
            "Sua diem danh thanh cong - Lop: " + maLop + " | MSSV: " + soThanhChuoi(mssv) +
            " | Buoi: " + soThanhChuoi(buoiSua) +
            " | " + trangThaiToChuoi(cu) + " -> " + trangThaiToChuoi(char('0' + moi)));
}

void moduleDiemDanh(LopHoc dsLop[], int soLuongLop)
{
    int chon;
    do
    {
        cout << "\n===== DIEM DANH =====\n";
        cout << "1. Ghi nhan diem danh\n";
        cout << "2. Cap nhat diem danh cho sinh vien\n";
        cout << "3. Xem lich su diem danh cua 1 lop\n";
        cout << "0. Quay lai\n";
        chon = nhapSoNguyen("Nhap: ");

        switch(chon)
        {
            case 1:
                xoaManHinh();
                ghiNhanDiemDanh(dsLop, soLuongLop);
                break;
            case 2:
                xoaManHinh();
                capNhatDiemDanh();
                break;
            case 3:
                xoaManHinh();
                xemDiemDanhLop();
                break;
            case 0:
                xoaManHinh();
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while(chon != 0);
}
