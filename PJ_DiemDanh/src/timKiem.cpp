#include "timKiem.h"
#include "fileIO.h"
#include "chucNang.h"
#include "nhatKy.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void timKiemTheoMSSV(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== TIM KIEM THEO MA SO SINH VIEN =====\n";
    long long mssvTim = nhapSoNguyenLon("\nNhap MSSV can tim kiem lich su: ");

    bool timThay = false;

    for(int i = 0; i < soLuongLop; i++)
    {
        docFileLopHoc(dsLop[i].thongTinTKB.maLop, dsLop[i].bangDiemDanh);
        BangDiemDanh &bdd = dsLop[i].bangDiemDanh;

        int viTri = timViTriSinhVien(bdd, mssvTim);

        if(viTri != -1)
        {
            if(!timThay)
            {
                cout << "\n=== KET QUA TIM KIEM CHO MSSV: " << mssvTim << " ===" << endl;
                cout << "Ho ten: " << bdd.danhSachSV[viTri].hoTen << endl;
                timThay = true;
            }

            cout << "\n-> Lop: " << dsLop[i].thongTinTKB.maLop << " (" << dsLop[i].thongTinTKB.tenHP << ")" << endl;
            cout << "Chi tiet lich su: ";

            if(bdd.danhSachSV[viTri].diemDanh.empty())
            {
                cout << "Chua co du lieu.";
            }
            else
            {
                for(size_t b = 0; b < bdd.danhSachSV[viTri].diemDanh.length(); b++)
                {
                    char status = bdd.danhSachSV[viTri].diemDanh[b];
                    cout << "[B" << b + 1 << ": " << trangThaiToChuoi(status) << "] ";
                }
            }
            cout << endl;
        }
    }

    if(!timThay) cout << "\n>> Khong tim thay sinh vien nay trong bat ky lop hoc nao!\n";

    if(timThay)
    {
        GHI_LOG(LOG_INFO, "Tim thay sinh vien khi tim theo MSSV - MSSV: " + soThanhChuoi(mssvTim));
    }
    else
    {
        GHI_LOG(LOG_WARN, "Khong tim thay sinh vien khi tim theo MSSV - MSSV: " + soThanhChuoi(mssvTim));
    }
}

void timKiemTheoTen(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== TIM KIEM THEO TEN SINH VIEN =====\n";
    string tuKhoa;
    cout << "\nNhap ten sinh vien can tim (co the nhap mot phan ten): ";
    getline(cin, tuKhoa);

    bool timThayChung = false;
    cout << "\n=== KET QUA TIM KIEM THEO TEN: \"" << tuKhoa << "\" ===\n";

    for(int i = 0; i < soLuongLop; i++)
    {
        docFileLopHoc(dsLop[i].thongTinTKB.maLop, dsLop[i].bangDiemDanh);
        BangDiemDanh &bdd = dsLop[i].bangDiemDanh;
        bool lopNayCoGiaoVien = false;

        for(int j = 0; j < bdd.soLuongSV; j++)
        {
            if(coChuaChuoiCon(bdd.danhSachSV[j].hoTen, tuKhoa))
            {
                if(!lopNayCoGiaoVien)
                {
                    cout << "\n[ LOP: " << dsLop[i].thongTinTKB.maLop
                         << " - " << dsLop[i].thongTinTKB.tenHP << " ]\n";
                    cout << string(55, '-') << endl;
                    lopNayCoGiaoVien = true;
                }
                cout << " MSSV: " << setw(10) << left << bdd.danhSachSV[j].mssv
                     << " | Ho ten: " << bdd.danhSachSV[j].hoTen << endl;
                timThayChung = true;
            }
        }

        if(lopNayCoGiaoVien)
        {
            cout << string(55, '-') << endl;
        }
    }

    if(!timThayChung)
    {
        cout << ">> Khong tim thay sinh vien nao co ten chua tu khoa \"" << tuKhoa << "\"!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay sinh vien nao theo ten - Tu khoa: " + tuKhoa);
    }
    else
    {
        GHI_LOG(LOG_INFO, "Tim kiem theo ten thanh cong - Tu khoa: " + tuKhoa);
    }

    cout << "\n======================================================\n";
}

void timKiemDiemDanhTheoNgay()
{
    string maLop, ngay;

    cout << "\n===== TIM KIEM DIEM DANH THEO NGAY =====\n";
    cout << "\nNhap ma lop: ";
    cin >> maLop;
    cin.ignore();
    cout << "Nhap ngay can kiem tra: ";
    getline(cin, ngay);

    string ngayFile = chuanHoaNgay(ngay);
    string tenFile = "data/DiemDanh/" + maLop + "_" + ngayFile + ".csv";

    ifstream file(tenFile.c_str());
    if (!file.is_open())
    {
        cout << ">> Khong tim thay du lieu diem danh cua lop " << maLop << " trong ngay " << ngayFile << "!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay file diem danh theo ngay - File: " + tenFile);
        return;
    }

    string line;
    getline(file, line);

    int soCM = 0, soVCP = 0, soVKP = 0, siSo = 0;
    int buoiSo = -1;

    string dsMssv[MAX_SV];
    string dsHoTen[MAX_SV];
    string dsTrangThai[MAX_SV];

    while (getline(file, line))
    {
        string cells[4];
        int cols = parseCSVLine(line, cells, 4);

        if (cols >= 3 && siSo < MAX_SV)
        {
            dsMssv[siSo] = cells[0];
            dsHoTen[siSo] = cells[1];
            dsTrangThai[siSo] = cells[2];

            if (buoiSo == -1 && cols == 4 && !cells[3].empty())
            {
                buoiSo = chuoiThanhSo(cells[3]);
            }

            if (cells[2] == "CM") soCM++;
            else if (cells[2] == "VCP") soVCP++;
            else if (cells[2] == "VKP") soVKP++;
            siSo++;
        }
    }
    file.close();

    if (buoiSo == -1) {
        buoiSo = 1;
        GHI_LOG(LOG_DEBUG, "Khong doc duoc Buoi So tu file, dung gia tri mac dinh = 1 - File: " + tenFile);
    }

    cout << "\n========================================================\n";
    cout << "BAO CAO DIEM DANH: LOP " << maLop << " | BUOI SO: " << buoiSo << " | NGAY: " << ngayFile << "\n";
    cout << "========================================================\n";
    cout << "+ Tong si so lop: " << siSo << " sinh vien\n";
    cout << "+ So sinh vien CO MAT: " << soCM << endl;
    cout << "+ So sinh vien VANG CO PHEP: " << soVCP << endl;
    cout << "+ So sinh vien VANG KHONG PHEP: " << soVKP << endl;
    cout << "--------------------------------------------------------\n";
    cout << "CHI TIET TRANG THAI TUNG SINH VIEN:\n\n";
    cout << left << setw(6) << "STT" << setw(15) << "MSSV" << setw(25) << "Ho va Ten" << "Trang thai" << endl;
    cout << string(56, '-') << endl;

    for (int i = 0; i < siSo; i++)
    {
        cout << left << setw(6) << (i + 1)
             << setw(15) << dsMssv[i]
             << setw(25) << dsHoTen[i]
             << dsTrangThai[i] << endl;
    }
    cout << string(56, '=') << endl;

    GHI_LOG(LOG_INFO, "Tra cuu diem danh theo ngay thanh cong - Lop: " + maLop + " | Ngay: " + ngayFile + " | Si so: " + soThanhChuoi(siSo));
}

void moduleTimKiem(LopHoc dsLop[], int soLuongLop)
{
    int chon;
    do {
        cout << "\n===== TIM KIEM =====\n";
        cout << "1. Tim kiem sinh vien theo MSSV\n";
        cout << "2. Tim kiem sinh vien theo ten\n";
        cout << "3. Tim kiem nhat ky diem danh lop theo ngay\n";
        cout << "0. Quay lai\n";
        cout << "----------------------------------------\n";
        chon = nhapSoNguyen("Nhap: ");

        switch(chon)
        {
            case 1:
                xoaManHinh();
                timKiemTheoMSSV(dsLop, soLuongLop);
                break;
            case 2:
                xoaManHinh();
                timKiemTheoTen(dsLop, soLuongLop);
                break;
            case 3:
                xoaManHinh();
                timKiemDiemDanhTheoNgay();
                break;
            case 0:
                xoaManHinh();
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while(chon != 0);
}
