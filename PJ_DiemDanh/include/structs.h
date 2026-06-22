#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

using namespace std;

const int MAX_LOP = 100;
const int MAX_SV = 150;
const int MAX_BUOI = 20;
const int MAX_COT_CSV = 10;

struct BuoiDiemDanh
{
    string buoiSo;
    string ngay;
    string trangThai;
};

struct SinhVien
{
    long long mssv;
    string hoTen;
    BuoiDiemDanh lichSu[MAX_BUOI];
    int soBuoiDaDiemDanh;
    int soVang;
    string diemDanh;
};

struct BangDiemDanh
{
    string maLop;

    SinhVien danhSachSV[MAX_SV];

    int soLuongSV;
};

struct ThoiKhoaBieu
{
    string maLop;
    string tenHP;
    string thu;
    string thoiGian;
    string tuanHoc;
    string phongHoc;
};

struct LopHoc
{
    ThoiKhoaBieu thongTinTKB;
    BangDiemDanh bangDiemDanh;
};
#endif
