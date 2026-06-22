#ifndef CHUCNANG_H
#define CHUCNANG_H
#include <string>
#include "structs.h"
using namespace std;

void xoaManHinh();

int nhapSoNguyen(const string& thongBao);

int nhapSoNguyenTrongKhoang(const string& thongBao, int minVal, int maxVal);

long long nhapSoNguyenLon(const string& thongBao);

int parseCSVLine(string line, string result[], int maxCols);

string trangThaiToChuoi(char c);

long long chuoiThanhSo(string s);

string soThanhChuoi(long long x);

bool coChuaChuoiCon(const string &nguon, const string &tuKhoa);

string chuanHoaNgay(string ngay);

int timViTriLop(const LopHoc dsLop[], int soLuongLop, const string& maLop);

// Hàm tìm vị trí sinh viên bằng thuật toán Tìm kiếm nhị phân (Binary Search)
int timViTriSinhVien(const BangDiemDanh& bdd, long long mssvTim);

#endif
