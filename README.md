# HỆ THỐNG QUẢN LÝ ĐIỂM DANH

**Dự án cuối kỳ Kỹ thuật lập trình - MI3310**  
**Nhóm: 22**  
**Mã lớp học: 169312**  
**Học kỳ: 20252**

Ứng dụng console viết bằng **C++** hỗ trợ quản lý thời khóa biểu, điểm danh sinh viên theo lớp, tìm kiếm và thống kê tình hình chuyên cần.

## Mục lục

- [Tính năng](#tính-năng)
- [Cấu trúc thư mục dự án](#cấu-trúc-thư-mục-dự-án)
- [Cấu trúc dữ liệu chính](#cấu-trúc-dữ-liệu-chính)
- [Tổ chức dữ liệu trên file](#tổ-chức-dữ-liệu-trên-file)
- [Giải thuật sử dụng](#giải-thuật-sử-dụng)
- [Sơ đồ menu](#sơ-đồ-menu)
- [Yêu cầu hệ thống](#yêu-cầu-hệ-thống)
- [Hướng dẫn build & chạy](#hướng-dẫn-build--chạy)
- [Ghi nhật ký hệ thống (Log)](#ghi-nhật-ký-hệ-thống-log)
- [Hạn chế đã biết](#hạn-chế-đã-biết)
- [Tác giả](#tác-giả)

---

## Tính năng

**1. Quản lý lớp học**
- Xem danh sách lớp và thời khóa biểu
- Xem chi tiết một lớp (thông tin TKB + danh sách sinh viên)

**2. Điểm danh**
- Ghi nhận điểm danh theo buổi (Có mặt / Vắng có phép / Vắng không phép)
- Cập nhật (sửa) điểm danh của một sinh viên cho một buổi cụ thể
- Xem bảng điểm danh toàn bộ các buổi của một lớp

**3. Tìm kiếm**
- Tìm sinh viên theo MSSV (tra cứu lịch sử điểm danh ở **tất cả** các lớp)
- Tìm sinh viên theo tên (tìm gần đúng — substring)
- Tra cứu báo cáo điểm danh của một lớp theo ngày cụ thể

**4. Thống kê**
- Danh sách cảnh báo cấm thi (tỉ lệ vắng > 20%)
- Top 10 sinh viên vắng nhiều nhất của lớp
- Thống kê tổng quan lớp học (tỉ lệ chuyên cần trung bình, sĩ số từng buổi...)

**5. Nhật ký hệ thống**
- Tự động ghi log mọi thao tác quan trọng (thời gian, file, dòng, hàm, nội dung) kèm phân loại mức độ INFO / DEBUG / WARN / ERROR

---

## Cấu trúc thư mục dự án

```
QuanLyDiemDanh/
├── QuanLyDiemDanh.cbp     # File dự án Code::Blocks
├── main.cpp               # Điểm khởi chạy, menu chính
│
├── structs.h               # Định nghĩa các struct dùng chung
│
├── chucNang.h / .cpp       # Hàm tiện ích dùng chung (nhập liệu, xử lý chuỗi, parse CSV...)
├── fileIO.h / .cpp         # Đọc/ghi file CSV (TKB, lớp học)
├── nhatKy.h / .cpp         # Ghi log hệ thống (macro GHI_LOG)
├── MaxHeap.h / .cpp        # Cấu trúc dữ liệu Max Heap (heapify, build, extractMax)
│
├── quanLy.h / .cpp         # Module Quản lý lớp học
├── diemDanh.h / .cpp       # Module Điểm danh
├── timKiem.h / .cpp        # Module Tìm kiếm
├── thongKe.h / .cpp        # Module Thống kê
│
└── data/                   # Thư mục dữ liệu (tạo thủ công trước khi chạy)
    ├── TKB/
    │   └── ThoiKhoaBieu.csv
    ├── LopHoc/
    │   └── <MaLop>.csv
    ├── DiemDanh/
    │   └── <MaLop>_<Ngay>.csv
    └── Log/
        └── nhatky.txt
```

### Sơ đồ phụ thuộc module

```
main.cpp
 ├── quanLy.cpp   ──┐
 ├── diemDanh.cpp ──┤
 ├── timKiem.cpp  ──┼── dùng chung: chucNang.h, fileIO.h, nhatKy.h
 ├── thongKe.cpp  ──┘        thongKe.cpp dùng thêm MaxHeap.h
 └── fileIO.cpp, chucNang.cpp, nhatKy.cpp, MaxHeap.cpp (tầng nền tảng)
```

---

## Cấu trúc dữ liệu chính

Định nghĩa trong `structs.h`:

| Struct | Mô tả |
|---|---|
| `BuoiDiemDanh` | Thông tin một buổi điểm danh (buổi số, ngày, trạng thái) |
| `SinhVien` | MSSV, họ tên, chuỗi `diemDanh` (mỗi ký tự đại diện trạng thái 1 buổi), số buổi đã điểm danh, số buổi vắng |
| `BangDiemDanh` | Mã lớp + mảng sinh viên (`danhSachSV[MAX_SV]`) |
| `ThoiKhoaBieu` | Mã lớp, tên học phần, thứ, thời gian, tuần học, phòng học |
| `LopHoc` | Gộp `ThoiKhoaBieu` + `BangDiemDanh` của một lớp |

**Hằng số giới hạn:** `MAX_LOP = 100`, `MAX_SV = 150`, `MAX_BUOI = 20`, `MAX_COT_CSV = 10`

> Quy ước mã trạng thái điểm danh: `'1'` = Có mặt (CM), `'2'` = Vắng có phép (VCP), `'3'` = Vắng không phép (VKP).

---

## Tổ chức dữ liệu trên file

| File | Định dạng cột | Vai trò |
|---|---|---|
| `data/TKB/ThoiKhoaBieu.csv` | `MaLop,TenHP,Thu,ThoiGian,TuanHoc,PhongHoc` | Danh sách lớp + thời khóa biểu |
| `data/LopHoc/<MaLop>.csv` | `MSSV,HoTen,DiemDanh` | Danh sách sinh viên và lịch sử điểm danh dạng chuỗi của lớp |
| `data/DiemDanh/<MaLop>_<Ngay>.csv` | `MSSV,HoTen,TrangThai,BuoiSo` | Biên bản điểm danh của một buổi cụ thể |
| `data/Log/nhatky.txt` | `[thời gian] [cấp độ] [file:dòng - hàm()] -> nội dung` | Nhật ký hoạt động hệ thống |

**Lưu ý quan trọng:** Danh sách sinh viên trong file `data/LopHoc/<MaLop>.csv` cần được sắp xếp theo MSSV tăng dần, vì chức năng tra cứu/sửa điểm danh sử dụng **tìm kiếm nhị phân** trên mảng này.

---

## Giải thuật sử dụng

| Giải thuật | Áp dụng tại | Độ phức tạp |
|---|---|---|
| Tìm kiếm tuyến tính | `timViTriLop()` — tìm lớp theo mã | O(n) |
| Tìm kiếm nhị phân | `timViTriSinhVien()` — tìm sinh viên theo MSSV | O(log n) |
| Max Heap (heapify / buildMaxHeap / extractMax) | `thongKe.cpp` — cảnh báo cấm thi, Top vắng nhiều nhất | Xây heap: O(n); mỗi lần lấy phần tử lớn nhất: O(log n) |
| Parse CSV tự cài đặt | `parseCSVLine()` trong `chucNang.cpp` | O(n) theo độ dài dòng |

---

## Sơ đồ menu

```
MENU CHÍNH
├── 1. Quản lý lớp học
│   ├── 1. Xem danh sách lớp và TKB
│   └── 2. Xem chi tiết 1 lớp
├── 2. Điểm danh
│   ├── 1. Ghi nhận điểm danh
│   ├── 2. Cập nhật điểm danh cho sinh viên
│   └── 3. Xem lịch sử điểm danh của 1 lớp
├── 3. Tìm kiếm
│   ├── 1. Theo MSSV
│   ├── 2. Theo tên
│   └── 3. Theo ngày (của 1 lớp)
├── 4. Thống kê
│   ├── 1. Cảnh báo cấm thi (vắng > 20%)
│   ├── 2. Top 10 sinh viên vắng nhiều nhất
│   └── 3. Tổng quan tình hình lớp
└── 0. Thoát
```

---

## Yêu cầu hệ thống

- Trình biên dịch hỗ trợ C++11 trở lên (khuyến nghị MinGW đi kèm Code::Blocks)
- **Hệ điều hành: Windows** — hàm `xoaManHinh()` gọi `system("cls")`, không tương thích trực tiếp với Linux/macOS (cần đổi thành `system("clear")` nếu muốn chạy đa nền tảng)

---

## Hướng dẫn build & chạy

1. Mở file `QuanLyDiemDanh.cbp` bằng **Code::Blocks**.
2. Tạo cấu trúc thư mục dữ liệu cạnh file thực thi (nếu chưa có), bao gồm:
   ```
   data/TKB/
   data/LopHoc/
   data/DiemDanh/
   data/Log/
   ```
3. Chuẩn bị file `data/TKB/ThoiKhoaBieu.csv` (dòng đầu là tiêu đề) và các file `data/LopHoc/<MaLop>.csv` tương ứng — danh sách sinh viên **phải sắp xếp theo MSSV tăng dần**.
4. Nhấn **Build and Run** (F9).
5. Thao tác qua menu số trong cửa sổ console.

---

## Ghi nhật ký hệ thống (Log)

Mọi thao tác quan trọng (thành công lẫn lỗi) đều được ghi vào `data/Log/nhatky.txt` thông qua macro:

```cpp
GHI_LOG(LOG_INFO, "Nội dung log...");
```

Macro tự động đính kèm tên file, số dòng và tên hàm gọi log, giúp truy vết lỗi nhanh hơn khi debug.

---

## Hạn chế đã biết

- `system("cls")` chỉ chạy đúng trên Windows.
- Dùng mảng tĩnh kích thước cố định (`MAX_LOP`, `MAX_SV`) nên giới hạn quy mô dữ liệu.
- Chưa kiểm tra MSSV trùng lặp khi thêm sinh viên mới.
- Chương trình giả định ngầm dữ liệu đã sắp xếp theo MSSV để tìm kiếm nhị phân hoạt động đúng, nhưng chưa có bước kiểm tra/sắp xếp lại tự động.
- Số buổi điểm danh hiện tại của lớp được suy ra từ độ dài chuỗi `diemDanh` của sinh viên **đầu tiên** trong danh sách — có thể sai lệch nếu dữ liệu các sinh viên không đồng bộ độ dài.
- Hàm `chuanHoaNgay()` chỉ thay `/` bằng `-`, chưa kiểm tra tính hợp lệ của ngày tháng nhập vào.

---

## Tác giả

*(Điền tên, MSSV, lớp học phần Kỹ thuật lập trình tại đây)*
