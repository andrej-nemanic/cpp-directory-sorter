#pragma once
#include <string>
#include <vector>
#include <filesystem>

// Struktura za shranjevanje podatkov o datoteki
struct FileRecord {
    std::filesystem::path path;
    long long size;
};

// Deklaracije funkcij
std::string formatSize(long long bytes);
int partition(std::vector<FileRecord>& arr, int low, int high);
void quickSort(std::vector<FileRecord>& arr, int low, int high);