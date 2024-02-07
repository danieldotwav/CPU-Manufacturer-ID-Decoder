#include <iostream>
#include <intrin.h>
#include <iomanip>

using namespace std;

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

int main() {
    decodeAndPrintCpuManufacturer();
    return 0;
}