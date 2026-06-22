#include "fileIO.h"
#include "chucNang.h"
#include "nhatKy.h"
#include <fstream>
#include <iostream>

using namespace std;

void docFileTKB(LopHoc dsLop[], int& soLuongLop)
{
    soLuongLop = 0;
    ifstream file(FILE_PATH_TKB.c_str());
    if(!file.is_open())
    {
        cout << "Khong mo duoc file TKB\n";
        GHI_LOG(LOG_ERROR, "Khong mo duoc file TKB - File: " + FILE_PATH_TKB);
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line) && soLuongLop < MAX_LOP)
    {
        string cells[6];
        int cols = parseCSVLine(line, cells, 6);
        if(cols >= 6)
        {
            dsLop[soLuongLop].thongTinTKB.maLop = cells[0];
            dsLop[soLuongLop].thongTinTKB.tenHP = cells[1];
            dsLop[soLuongLop].thongTinTKB.thu = cells[2];
            dsLop[soLuongLop].thongTinTKB.thoiGian = cells[3];
            dsLop[soLuongLop].thongTinTKB.tuanHoc = cells[4];
            dsLop[soLuongLop].thongTinTKB.phongHoc = cells[5];

            dsLop[soLuongLop].bangDiemDanh.maLop = cells[0];
            dsLop[soLuongLop].bangDiemDanh.soLuongSV = 0;

            soLuongLop++;
        }
    }
    file.close();

    GHI_LOG(LOG_INFO, "Da tai file TKB thanh cong - So lop: " + soThanhChuoi(soLuongLop));
}

void docFileLopHoc(const string& maLop, BangDiemDanh& bdd)
{
    bdd.maLop = maLop;
    bdd.soLuongSV = 0;

    string filePath = FOLDER_LOP + maLop + ".csv";
    ifstream file(filePath.c_str());
    if(!file.is_open()) return;

    string line;
    getline(file, line);

    while(getline(file, line) && bdd.soLuongSV < MAX_SV)
    {
        string cells[3];
        int cols = parseCSVLine(line, cells, 3);

        if(cols >= 2)
        {
            bdd.danhSachSV[bdd.soLuongSV].mssv = chuoiThanhSo(cells[0]);
            bdd.danhSachSV[bdd.soLuongSV].hoTen = cells[1];
            bdd.danhSachSV[bdd.soLuongSV].diemDanh = (cols == 3) ? cells[2] : "";

            int vang = 0;
            for(size_t i = 0; i < bdd.danhSachSV[bdd.soLuongSV].diemDanh.length(); i++)
            {
                char c = bdd.danhSachSV[bdd.soLuongSV].diemDanh[i];
                if(c == '2' || c == '3') vang++;
            }
            bdd.danhSachSV[bdd.soLuongSV].soBuoiDaDiemDanh = bdd.danhSachSV[bdd.soLuongSV].diemDanh.length();
            bdd.danhSachSV[bdd.soLuongSV].soVang = vang;

            bdd.soLuongSV++;
        }
    }
    file.close();
}

void luuFileLopHoc(const string& maLop, const BangDiemDanh& bdd)
{
    string tenFile = FOLDER_LOP + maLop + ".csv";
    ofstream file(tenFile.c_str());

    if(!file.is_open())
    {
        cout << "Khong mo duoc file lop hoc!\n";
        return;
    }

    file << "MSSV,HoTen,DiemDanh\n";
    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        file << bdd.danhSachSV[i].mssv << ","
             << bdd.danhSachSV[i].hoTen << ","
             << bdd.danhSachSV[i].diemDanh << "\n";
    }
    file.close();
}

bool kiemTraFileTonTai(const string& tenFile)
{
    ifstream file(tenFile.c_str());
    if(file.is_open())
    {
        file.close();
        return true;
    }
    return false;
}
