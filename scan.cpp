#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm> // Added for std::swap

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

int partition(std::vector<FileRecord>& arr, int low, int high) {
    long long pivot = arr[high].size;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].size > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<FileRecord>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Algorithm branch: Quick Sort implemented.\n";
    return 0;
}