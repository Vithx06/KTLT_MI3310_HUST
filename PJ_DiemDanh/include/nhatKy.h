#ifndef NHATKY_H
#define NHATKY_H

#include <string>
using namespace std;

const string FILE_PATH_LOG = "data/Log/nhatky.txt";

enum CapDoLog
{
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR
};

string layThoiGianHienTai();

void ghiLogChiTiet(CapDoLog capDo, const string& tenFile, int dong, const string& tenHam, const string& noiDung);

#define GHI_LOG(capDo, noiDung) ghiLogChiTiet(capDo, __FILE__, __LINE__, __func__, noiDung)

void xemNhatKy();

#endif
