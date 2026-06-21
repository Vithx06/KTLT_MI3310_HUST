#include "thongKe.h"
#include "fileIO.h"
#include "chucNang.h"
#include "nhatKy.h"
#include "maxHeap.h"
#include <iostream>
#include <iomanip>

using namespace std;

void canhBaoCamThiLop(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== CANH BAO CAM THI =====\n";
    string maLop;
    cout << "\nNhap ma lop can kiem tra canh bao: ";
    cin >> maLop;

    int viTri = timViTriLop(dsLop, soLuongLop, maLop);
    if(viTri == -1)
    {
        cout << ">> Khong tim thay lop hoc nay!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay lop khi xem canh bao cam thi - Ma lop nhap: " + maLop);
        return;
    }

    docFileLopHoc(maLop, dsLop[viTri].bangDiemDanh);
    BangDiemDanh &bdd = dsLop[viTri].bangDiemDanh;

    if(bdd.soLuongSV == 0)
    {
        cout << ">> Lop chua co du lieu hoc tap!\n";
        GHI_LOG(LOG_WARN, "Lop chua co du lieu hoc tap khi xem canh bao cam thi - Lop: " + maLop);
        return;
    }

    MaxHeap heap;
    heap.size = bdd.soLuongSV;
    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        heap.data[i] = bdd.danhSachSV[i];
    }
    buildMaxHeap(heap);

    cout << "\n================ DANH SACH CANH BAO CAM THI LOP: " << maLop << " ================\n\n";
    cout << left
         << setw(6)  << "STT"
         << setw(15) << "MSSV"
         << setw(25) << "Ho Ten"
         << setw(15) << "So buoi vang"
         << "Ty le vang" << endl;
    cout << string(71, '-') << endl;

    bool coCanhBao = false;
    int stt = 1;

    while(heap.size > 0)
    {
        SinhVien sv = extractMax(heap);

        if(sv.soBuoiDaDiemDanh == 0) break;

        double tiLeVang = ((double)sv.soVang / sv.soBuoiDaDiemDanh) * 100;

        if(tiLeVang <= 20.0) break;

        cout << left
             << setw(6)  << stt++
             << setw(15) << sv.mssv
             << setw(25) << sv.hoTen
             << setw(15) << (soThanhChuoi(sv.soVang) + "/" + soThanhChuoi(sv.soBuoiDaDiemDanh))
             << fixed << setprecision(1) << tiLeVang << "%\n";
        coCanhBao = true;
    }

    if(!coCanhBao)
    {
        cout << ">> Lop hoc an toan! Khong co sinh vien nao bi canh bao cam thi (>20%).\n";
    }

    GHI_LOG(LOG_INFO, "Da xem canh bao cam thi - Lop: " + maLop + " | So SV bi canh bao: " + soThanhChuoi(stt - 1));
}


void top10VangNhieuNhat(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== DANH SACH SINH VIEN VANG NHIEU =====\n";
    string maLop;
    cout << "\nNhap ma lop can xem Top 10 vang: ";
    cin >> maLop;

    int viTri = timViTriLop(dsLop, soLuongLop, maLop);
    if(viTri == -1)
    {
        cout << ">> Khong tim thay lop hoc nay!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay lop khi xem top vang nhieu - Ma lop nhap: " + maLop);
        return;
    }

    docFileLopHoc(maLop, dsLop[viTri].bangDiemDanh);
    BangDiemDanh &bdd = dsLop[viTri].bangDiemDanh;

    if(bdd.soLuongSV == 0)
    {
        cout << ">> Lop chua co du lieu hoc tap!\n";
        GHI_LOG(LOG_WARN, "Lop chua co du lieu hoc tap khi xem top vang nhieu - Lop: " + maLop);
        return;
    }

    MaxHeap heap;
    heap.size = bdd.soLuongSV;
    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        heap.data[i] = bdd.danhSachSV[i];
    }

    int topK = (heap.size < 10) ? heap.size : 10;

    buildMaxHeap(heap);

    SinhVien ketQua[10];
    for(int i = 0; i < topK; i++)
    {
        ketQua[i] = extractMax(heap);
    }

    cout << "\n================ TOP 10 SINH VIEN VANG NHIEU NHAT LOP: " << maLop << " ================\n\n";
    cout << left
         << setw(6)  << "STT"
         << setw(15) << "MSSV"
         << setw(25) << "Ho Ten"
         << setw(15) << "So buoi vang"
         << "Ty le vang" << endl;
    cout << string(70, '-') << endl;

    for(int i = 0; i < topK; i++)
    {
        double tiLeVang = 0.0;
        if(ketQua[i].soBuoiDaDiemDanh > 0)
        {
            tiLeVang = ((double)ketQua[i].soVang / ketQua[i].soBuoiDaDiemDanh) * 100;
        }

        cout << left
             << setw(6)  << i + 1
             << setw(15) << ketQua[i].mssv
             << setw(25) << ketQua[i].hoTen
             << setw(15) << (soThanhChuoi(ketQua[i].soVang) + "/" + soThanhChuoi(ketQua[i].soBuoiDaDiemDanh))
             << fixed << setprecision(1) << tiLeVang << "%\n";
    }

    GHI_LOG(LOG_INFO, "Da xem top vang nhieu nhat - Lop: " + maLop + " | So SV hien thi: " + soThanhChuoi(topK));
}


void thongKeTongQuanLop(LopHoc dsLop[], int soLuongLop)
{
    cout << "\n===== TONG QUAN LOP HOC =====\n";
    string maLop;
    cout << "\nNhap ma lop can xem thong ke tong quan: ";
    cin >> maLop;

    int viTri = timViTriLop(dsLop, soLuongLop, maLop);
    if(viTri == -1)
    {
        cout << ">> Khong tim thay lop hoc nay!\n";
        GHI_LOG(LOG_WARN, "Khong tim thay lop khi xem tong quan - Ma lop nhap: " + maLop);
        return;
    }

    docFileLopHoc(maLop, dsLop[viTri].bangDiemDanh);
    BangDiemDanh &bdd = dsLop[viTri].bangDiemDanh;

    if(bdd.soLuongSV == 0)
    {
        cout << ">> Lop chua co du lieu hoc tap!\n";
        GHI_LOG(LOG_WARN, "Lop chua co du lieu hoc tap khi xem tong quan - Lop: " + maLop);
        return;
    }

    int soBuoiHoc = bdd.danhSachSV[0].soBuoiDaDiemDanh;
    int tongCM = 0, tongVCP = 0, tongVKP = 0;
    int tongLuotDiemDanh = 0;

    for(int i = 0; i < bdd.soLuongSV; i++)
    {
        string s = bdd.danhSachSV[i].diemDanh;
        for(size_t j = 0; j < s.length(); j++)
        {
            if(s[j] == '1') tongCM++;
            else if(s[j] == '2') tongVCP++;
            else if(s[j] == '3') tongVKP++;
            tongLuotDiemDanh++;
        }
    }

    cout << "\n================ THONG KE TONG QUAN LOP: " << maLop << " ================\n\n";
    cout << "+ Tong so sinh vien trong lop       : " << bdd.soLuongSV << " sinh vien\n";
    cout << "+ Tong so buoi hoc da ghi nhan      : " << soBuoiHoc << " buoi\n";
    cout << "+ Tong luot CO MAT                  : " << tongCM << " luot \n";
    cout << "+ Tong luot VANG CO PHEP            : " << tongVCP << " luot \n";
    cout << "+ Tong luot VANG KHONG PHEP         : " << tongVKP << " luot \n";

    double tyLeChuyenCanLop = 0.0;
    if(tongLuotDiemDanh > 0)
    {
        tyLeChuyenCanLop = ((double)tongCM / tongLuotDiemDanh) * 100;
    }
    cout << "=> TY LE CHUYEN CAN TRUNG BINH LOP  : "
         << fixed << setprecision(2) << tyLeChuyenCanLop << "%\n\n";

    if (soBuoiHoc == 0)
    {
        cout << ">> Lop nay chua thuc hien diem danh buoi nao.\n";
        GHI_LOG(LOG_WARN, "Lop chua thuc hien diem danh buoi nao - Lop: " + maLop);
        return;
    }

    cout << "---------------- CHI TIET SI SO QUA TUNG BUOI ----------------\n\n";
    cout << left
         << setw(12) << "Buoi hoc"
         << setw(15) << "CM"
         << setw(15) << "VCP"
         << "VKP" << endl;
    cout << string(58, '-') << endl;

    for(int b = 0; b < soBuoiHoc; b++)
    {
        int buoiCM = 0, buoiVCP = 0, buoiVKP = 0;

        for(int i = 0; i < bdd.soLuongSV; i++)
        {
            if (b < (int)bdd.danhSachSV[i].diemDanh.length())
            {
                char trangThaibuoi = bdd.danhSachSV[i].diemDanh[b];
                if(trangThaibuoi == '1') buoiCM++;
                else if(trangThaibuoi == '2') buoiVCP++;
                else if(trangThaibuoi == '3') buoiVKP++;
            }
        }

        cout << left
             << setw(12) << ("Buoi " + soThanhChuoi(b + 1))
             << setw(15) << buoiCM
             << setw(15) << buoiVCP
             << buoiVKP << endl;
    }
    cout << string(58, '=') << endl;

    GHI_LOG(LOG_INFO, "Da xem thong ke tong quan - Lop: " + maLop + " | Tong luot diem danh: " + soThanhChuoi(tongLuotDiemDanh));
}

void moduleThongKe(LopHoc dsLop[], int soLuongLop)
{
    int chon;
    do
    {
        cout << "\n===== BAO CAO THONG KE =====\n";
        cout << "1. Danh sach canh bao cam thi cua lop (Vang > 20%)\n";
        cout << "2. Top 10 sinh vien vang nhieu nhat lop\n";
        cout << "3. Tong quan tinh hinh lop hoc\n";
        cout << "0. Quay lai\n";
        cout << "------------------------------------------\n";
        chon = nhapSoNguyen("Nhap lua chon: ");

        switch(chon)
        {
            case 1:
                xoaManHinh();
                canhBaoCamThiLop(dsLop, soLuongLop);
                break;
            case 2:
                xoaManHinh();
                top10VangNhieuNhat(dsLop, soLuongLop);
                break;
            case 3:
                xoaManHinh();
                thongKeTongQuanLop(dsLop, soLuongLop);
                break;
            case 0:
                xoaManHinh();
                break;
            default:
                cout << ">> Lua chon khong hop le! Vui long nhap lai.\n";
        }
    }
    while(chon != 0);
}
