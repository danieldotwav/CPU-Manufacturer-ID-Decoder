#include <iostream>
#include <intrin.h>
#include <cstring>
#include <iomanip>
using namespace std;

void decodeAndPrintCpuManufacturer();
void printDetailedHardwareInfo();
void printAMDCacheDetails();
void printCacheDetails(int cacheLevel, int cachType);

int main(int argc, char* argv[]) {
    decodeAndPrintCpuManufacturer();
    printDetailedHardwareInfo();

    // For cache size, more complex handling is required
    printAMDCacheDetails();
    //printCacheDetails(1, 1); // For Intel Processors

	return 0;
}

// Decodes and prints the CPU manufacturer ID
void decodeAndPrintCpuManufacturer() {
    int cpuInfo[4] = { -1 };
    char manufacturerId[13] = {}; // Enough space for the 12 character ID + null terminator

    // Get the manufacturer ID
    __cpuid(cpuInfo, 0);
    // The manufacturer ID is stored in ebx, edx, ecx (in this order)
    *reinterpret_cast<int*>(manufacturerId) = cpuInfo[1]; // EBX
    *reinterpret_cast<int*>(manufacturerId + 4) = cpuInfo[3]; // EDX
    *reinterpret_cast<int*>(manufacturerId + 8) = cpuInfo[2]; // ECX

    manufacturerId[12] = '\0'; // Null-terminate the string

    std::cout << "CPU Manufacturer ID: " << manufacturerId << std::endl;
}

void printDetailedHardwareInfo() {
    int cpuInfo[4] = { 0 };
    char brand[0x40]; // 64-byte space for the brand string
    memset(brand, 0, sizeof(brand)); // Clear brand buffer

    // Basic CPUID Information
    __cpuid(cpuInfo, 0); // Maximum CPUID Input Value and Processor Brand String
    int maxInputValue = cpuInfo[0];
    cout << "Maximum CPUID Input Value: " << maxInputValue << endl;

    // Processor Type and Features
    __cpuid(cpuInfo, 1);
    cout << "Processor Type: " << ((cpuInfo[0] >> 12) & 0x3) << endl; // This is largely obsolete
    cout << "Brand Index: " << (cpuInfo[1] & 0xFF) << endl;
    cout << "AVX Support: " << ((cpuInfo[2] >> 28) & 0x1) << endl;
    cout << "x87 FPU Support: " << ((cpuInfo[3] >> 0) & 0x1) << endl;

    // Processor Brand String (requires concatenation of results from 0x80000002 to 0x80000004)
    for (int i = 0; i < 3; i++) {
        __cpuid(cpuInfo, 0x80000002 + i);
        memcpy(brand + (i * 16), cpuInfo, sizeof(cpuInfo)); // Copy 16 bytes at a time
    }

    cout << "Processor Brand String: " << brand << endl; // Print the null-terminated brand string
}

/* This version is specific for AMD processors */
void printAMDCacheDetails() {
    int cpuInfo[4] = { 0 };

    // Get L1 cache details for AMD processor
    __cpuid(cpuInfo, 0x80000005);
    int l1DataCacheSize = (cpuInfo[2] >> 24) & 0xFF; // L1 data cache size in KB
    int l1InstructionCacheSize = (cpuInfo[3] >> 24) & 0xFF; // L1 instruction cache size in KB

    std::cout << "L1 Data Cache Size: " << l1DataCacheSize << " KB" << std::endl;
    std::cout << "L1 Instruction Cache Size: " << l1InstructionCacheSize << " KB" << std::endl;
}

/* Use this version for Intel Processors */
void printCacheDetails(int cacheLevel, int cacheType) {
    int cpuInfo[4];
    int cacheLevelId = 0;
    do {
        __cpuidex(cpuInfo, 4, cacheLevelId);
        int level = (cpuInfo[0] >> 5) & 0x7;
        int type = cpuInfo[0] & 0xF;
        if (level == cacheLevel && type == cacheType) {
            int lineSize = (cpuInfo[1] & 0xFFF) + 1;
            int partitions = ((cpuInfo[1] >> 12) & 0x3FF) + 1;
            int ways = ((cpuInfo[1] >> 22) & 0x3FF) + 1;
            int sets = cpuInfo[2] + 1;
            int cacheSize = ways * partitions * lineSize * sets;
            std::cout << "L" << cacheLevel << " Cache Size: " << cacheSize << " bytes" << std::endl;
            break;
        }
        cacheLevelId++;
    } while ((cpuInfo[0] & 0xF) != 0);
}