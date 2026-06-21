#ifndef FILEIO_H
#define FILEIO_H

#include "structs.h"
#include <string>

using namespace std;

const string FILE_PATH_TKB = "data/TKB/ThoiKhoaBieu.csv";
const string FOLDER_LOP = "data/LopHoc/";

void docFileTKB(LopHoc dsLop[], int& soLuongLop);

void docFileLopHoc(const string& maLop, BangDiemDanh& bdd);

void luuFileLopHoc(const string& maLop, const BangDiemDanh& bdd);

bool kiemTraFileTonTai(const string& tenFile);

#endif
