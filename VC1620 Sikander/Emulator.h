/*
Each function and data member in this class is designed to emulate the operation of a simple computer, the VC1620. The insertMemory function allows 
machine code instructions and data to be inserted into memory at specified locations, while the runProgram function emulates the execution of the 
program loaded in memory. The m_memory vector serves as the memory of the emulated computer.
*/

#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

#include <vector>   // Vector is a container that encapsulates dynamic size arrays.

// Emulator class is responsible for running the machine code translated by the assembler.
class emulator {

public:

    // Constant that sets the memory size of the emulated VC1620 computer.
    const static int MEMSZ = 100'000;

    // Constructor for the emulator class. It initializes the memory vector with zeroes.
    emulator() {
        m_memory.resize(MEMSZ, 0); // Resizes the vector to MEMSZ and initializes all elements to 0.
    }

    // Records instructions and data into simulated memory. a_location is the memory location and a_contents is the value to be inserted.
    // Returns true if successful, false otherwise.
    bool insertMemory(int a_location, long long a_contents);

    // Runs the program recorded in memory. Returns true if the program was able to run successfully, false otherwise.
    bool runProgram();

private:

    std::vector<long long> m_memory;  // Vector to simulate the memory of the VC1620 computer. Each element can hold a long long integer.

};

#endif
