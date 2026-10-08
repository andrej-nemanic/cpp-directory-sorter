#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// Testni komentar za git diff

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

// Quick Sort Partition function (Descending Order)
int partition(std::vector<FileRecord>& arr, int low, int high) {
    long long pivot = arr[high].size;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Sort descending by looking for elements larger than the pivot
        if (arr[j].size > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Recursive Quick Sort function
void quickSort(std::vector<FileRecord>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

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

    // Call the custom Quick Sort
    if (!files.empty()) {
        int n = files.size();
        quickSort(files, 0, n - 1);
    }

    // Output the top 5 (or fewer, if the directory has fewer files)
    int fileCount = files.size();
    int limit = std::min(5, fileCount);
    
    std::cout << "\nTop " << limit << " largest files:\n";
    std::cout << std::string(60, '-') << "\n";

    for (int i = 0; i < limit; ++i) {
        std::cout << std::left << std::setw(12) << formatSize(files[i].size) 
                  << files[i].path.string() << "\n";
    }

    return 0;
}