#include "chucNang.h"
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;
// Chức năng đối với giao diện
void xoaManHinh()
{
    system("cls");
}

// Nhóm chức năng đối với nhập liệu
int nhapSoNguyen(const string& thongBao)
{
    int x;
    while(true)
    {
        cout << thongBao;
        cin >> x;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Du lieu khong hop le! Vui long nhap mot so nguyen.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return x;
    }
}

int nhapSoNguyenTrongKhoang(const string& thongBao, int minVal, int maxVal)
{
    while(true)
    {
        int x = nhapSoNguyen(thongBao);

        if(minVal > maxVal) return x;

        if(x < minVal || x > maxVal)
        {
            cout << "Gia tri phai nam trong khoang [" << minVal << " - " << maxVal << "]!\n";
            continue;
        }

        return x;
    }
}

long long nhapSoNguyenLon(const string& thongBao)
{
    long long x;
    while(true)
    {
        cout << thongBao;
        cin >> x;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Du lieu khong hop le! Vui long nhap mot so.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return x;
    }
}

int parseCSVLine(string line, string result[], int maxCols)
{
    int count = 0;
    string cell = "";
    bool insideQuotes = false;

    for(size_t i = 0; i < line.length(); i++)
    {
        char c = line[i];

        if (c == '"')
        {
            insideQuotes = !insideQuotes;
            continue;
        }
        else if (c == ',' && !insideQuotes)
        {
            if(count < maxCols)
                result[count++] = cell;
            cell = "";
        }
        else
        {
            cell += c;
        }
    }

    if(count < maxCols)
        result[count++] = cell;

    return count;
}

string trangThaiToChuoi(char c)
{
    if(c == '1') return "CM";
    if(c == '2') return "VCP";
    if(c == '3') return "VKP";
    return "-";
}

long long chuoiThanhSo(string s)
{
    long long x = 0;
    for(size_t i = 0; i < s.length(); i++)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            x = x * 10 + (s[i] - '0');
        }
    }
    return x;
}

string soThanhChuoi(long long x)
{
    if(x == 0) return "0";

    string s = "";
    while(x)
    {
        s = char(x % 10 + '0') + s;
        x /= 10;
    }
    return s;
}


bool coChuaChuoiCon(const string &nguon, const string &tuKhoa)
{
    int n = nguon.length();
    int m = tuKhoa.length();

    if(m == 0) return true;
    if(m > n)  return false;

    for(int i = 0; i <= n - m; i++)
    {
        bool khop = true;
        for(int j = 0; j < m; j++)
        {
            if(nguon[i + j] != tuKhoa[j])
            {
                khop = false;
                break;
            }
        }
        if(khop) return true;
    }
    return false;
}

string chuanHoaNgay(string ngay)
{
    for(size_t i = 0; i < ngay.length(); i++)
    {
        if(ngay[i] == '/')
        {
            ngay[i] = '-';
        }
    }
    return ngay;
}

// Nhóm chức năng tìm kiếm cơ bản
int timViTriLop(const LopHoc dsLop[], int soLuongLop, const string& maLop)
{
    for(int i = 0; i < soLuongLop; i++)
    {
        if(dsLop[i].thongTinTKB.maLop == maLop)
        {
            return i;
        }
    }
    return -1;
}

int timViTriSinhVien(const BangDiemDanh& bdd, long long mssvTim)
{
    int left = 0;
    int right = bdd.soLuongSV - 1;

    while(left <= right)
    {
        int mid = left + (right - left) / 2;

        if(bdd.danhSachSV[mid].mssv == mssvTim)
        {
            return mid;
        }

        if(bdd.danhSachSV[mid].mssv < mssvTim)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}
