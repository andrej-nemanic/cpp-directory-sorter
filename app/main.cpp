#include <iostream>
#include <filesystem>
#include <vector>
#include <iomanip>
#include "../utils/utils.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    fs::path targetDir = (argc > 1) ? argv[1] : ".";
    std::vector<FileRecord> files;

    if (!fs::exists(targetDir)) {
        std::cerr << "Error: Target directory does not exist.\n";
        return 1;
    }

    std::cout << "Scanning " << targetDir << "...\n";

    auto options = fs::directory_options::skip_permission_denied;
    
    try {
        for (auto it = fs::recursive_directory_iterator(targetDir, options); 
             it != fs::recursive_directory_iterator(); 
             ++it) {
            try {
                if (fs::is_regular_file(it->status())) {
                    std::error_code ec;
                    long long size = fs::file_size(it->path(), ec);
                    
                    if (!ec) {
                        files.push_back({it->path(), size});
                    }
                }
            } catch (const fs::filesystem_error&) {}
        }
    } catch (const std::exception& e) {
        std::cerr << "Scan interrupted by system error: " << e.what() << "\n";
    }

    // Klic custom Quick Sort algoritma iz utils.cpp
    if (!files.empty()) {
        int n = files.size();
        quickSort(files, 0, n - 1);
    }

    // Izpis prvih 5 (ali manj)
    int fileCount = files.size();
    int limit = std::min(5, fileCount);
    
    std::cout << "\nTop " << limit << " largest files:\n";
    std::cout << std::string(60, '-') << "\n";

    for (int i = 0; i < limit; ++i) {
        // Klic formatSize iz utils.cpp
        std::cout << std::left << std::setw(12) << formatSize(files[i].size) 
                  << files[i].path.string() << "\n";
    }

    return 0;
}