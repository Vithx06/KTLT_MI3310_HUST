#include <iostream>
#include "chucNang.h"
#include "structs.h"
#include "fileIO.h"
#include "quanLy.h"
#include "diemDanh.h"
#include "timKiem.h"
#include "thongKe.h"
#include "nhatKy.h"

using namespace std;

int main()
{
    GHI_LOG(LOG_INFO, "Ung dung bat dau khoi chay.");

    static LopHoc dsLop[MAX_LOP];
    int soLuongLop = 0;

    docFileTKB(dsLop,
               soLuongLop);

    int chon;

    do
    {
        cout << "\n===== MENU CHINH =====\n";
        cout << "1. Quan ly lop hoc\n";
        cout << "2. Diem Danh\n";
        cout << "3. Tim Kiem\n";
        cout << "4. Thong Ke\n";
        cout << "0. Thoat\n";

        chon = nhapSoNguyen("Nhap: ");

       switch(chon)
     {
        case 1:
            xoaManHinh();
            moduleQuanLyLopHoc(dsLop,soLuongLop);
            break;

        case 2:
            xoaManHinh();
            moduleDiemDanh(dsLop,soLuongLop);
            break;

        case 3:
            xoaManHinh();
            moduleTimKiem(dsLop,soLuongLop);
            break;

        case 4:
            xoaManHinh();
            moduleThongKe(dsLop,soLuongLop);
            break;

        case 0:
            xoaManHinh();
            break;

        default:
            cout << "Lua chon khong hop le!\n";
}

    } while(chon != 0);

    GHI_LOG(LOG_INFO, "Ung dung ket thuc an toan.");

    return 0;
}
