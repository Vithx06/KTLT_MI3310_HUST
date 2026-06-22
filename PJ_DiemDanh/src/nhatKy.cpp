#include "nhatKy.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

string layThoiGianHienTai()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
             ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday,
             ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    return string(buffer);
}

static string capDoToChuoi(CapDoLog capDo)
{
    switch(capDo)
    {
        case LOG_INFO:  return "INFO ";
        case LOG_DEBUG: return "DEBUG";
        case LOG_WARN:  return "WARN ";
        case LOG_ERROR: return "ERROR";
    }
    return "INFO ";
}

void ghiLogChiTiet(CapDoLog capDo, const string& tenFile, int dong, const string& tenHam, const string& noiDung)
{
    ofstream file(FILE_PATH_LOG.c_str(), ios::app);

    if(!file.is_open())
    {
        cout << "Canh bao: Khong ghi duoc nhat ky! Hay kiem tra thu muc data/Log da ton tai chua.\n";
        return;
    }

    // Dinh dang: [thoi gian] [CAP DO] [file:dong - tenHam()] -> noi dung
    file << "[" << layThoiGianHienTai() << "] "
         << "[" << capDoToChuoi(capDo) << "] "
         << "[" << tenFile << ":" << dong << " - " << tenHam << "()] "
         << "-> " << noiDung << "\n";

    file.close();
}
