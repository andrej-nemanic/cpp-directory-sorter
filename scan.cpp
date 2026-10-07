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
    fs::path targetDir = (argc > 1) ? argv[1] : ".";
    std::vector<FileRecord> files;

    if (!fs::exists(targetDir)) {
        std::cerr << "Error: Target directory does not exist.\n";
        return 1;
    }

    std::cout << "Scanning " << targetDir << "...\n";

    // Basic iteration without error handling
    for (auto it = fs::recursive_directory_iterator(targetDir); 
         it != fs::recursive_directory_iterator(); 
         ++it) {
        if (fs::is_regular_file(it->status())) {
            std::error_code ec;
            long long size = fs::file_size(it->path(), ec);
            if (!ec) {
                files.push_back({it->path(), size});
            }
        }
    }

    std::cout << "Found " << files.size() << " files.\n";
    return 0;
}