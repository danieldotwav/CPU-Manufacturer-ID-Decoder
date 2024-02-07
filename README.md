# CPU Manufacturer ID Decoder

This program is designed to decode and print the CPU manufacturer ID using C++. It utilizes the intrinsic function `__cpuid` provided by `<intrin.h>` to access the CPU's manufacturer ID and then prints it to the standard output.

## Requirements

- A compiler that supports C++ and the `<intrin.h>` header file. This typically means using a compiler on Windows, as `<intrin.h>` is specific to Microsoft's compilers (e.g., MSVC).

## How It Works

The program defines a function `decodeAndPrintCpuManufacturer` which performs the following operations:

1. It declares an integer array `cpuInfo` with 4 elements to store the CPUID information.
2. A character array `manufacturerId` of 13 bytes is declared to hold the 12-character manufacturer ID plus a null terminator.
3. The `__cpuid` function is called with `cpuInfo` array and an input value of `0` to retrieve the CPU manufacturer ID.
4. The CPU manufacturer ID is extracted from the `cpuInfo` array (from the `EBX`, `EDX`, and `ECX` registers) and stored in the `manufacturerId` array in the correct order.
5. The manufacturer ID is null-terminated and printed to the standard output.

## Output

```cpp
CPU Manufacturer ID: [Manufacturer ID]
```

Where [Manufacturer ID] is replaced with the actual ID retrieved from the CPU.