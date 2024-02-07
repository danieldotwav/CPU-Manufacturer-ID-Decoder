#include <iostream>
#include <intrin.h>
#include <iomanip>
using namespace std;

void decodeAndPrintCpuManufacturer();
void printLeafValues();

int main(int argc, char* argv[]) {
    decodeAndPrintCpuManufacturer();
    cout << endl;
    printLeafValues();

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

void printLeafValues() {
    int b[4] = { 0 };
    int a;

    for (a = 0; a < 5; a++) {
        __cpuid(b, a);
        cout << "Code:" << a << " gives " << setw(8) << hex << setfill('0') << b[0] << ' ' << b[1] << ' ' << b[2] << ' ' << b[3] << endl;
    }
}