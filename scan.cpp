#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
namespace fs = std::filesystem;

struct FileRecord {
    fs::path path;
    long long size;
};

string formatSize(long long bytes) {
    constexpr double KB = 1024.0;
    constexpr double MB = KB * 1024.0;
    constexpr double GB = MB * 1024.0;

    ostringstream out;
    out << fixed << setprecision(2);

    if (bytes >= GB)      out << (bytes / GB) << " GB";
    else if (bytes >= MB) out << (bytes / MB) << " MB";
    else if (bytes >= KB) out << (bytes / KB) << " KB";
    else                  out << bytes << " B ";

    return out.str();
}

int main(int argc, char* argv[]) {
    std::cout << "File sort tool initialized.\n";
    return 0;
}