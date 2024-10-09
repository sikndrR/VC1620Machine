#include "emulator.h"
#include "stdafx.h"

/**/
/*
bool emulator::insertMemory(int a_location, long long a_contents)

NAME

        emulator::insertMemory - Records instructions and data into simulated memory.

SYNOPSIS

        bool emulator::insertMemory(int a_location, long long a_contents);
            a_location    --> The memory location where the data or instruction is to be stored.
            a_contents    --> The data or instruction to be stored.

DESCRIPTION

        This method stores a given data or instruction (a_contents) into the simulated memory
        at the specified location (a_location). If the location is out of bounds (less than
        zero or greater than or equal to MEMSZ), the method returns false without modifying
        the memory. If the location is valid, the method stores the contents at that location
        and returns true.

RETURNS

        Returns true if the operation was successful, and false otherwise.
*/
/**/
// Records instructions and data into simulated memory.
bool emulator::insertMemory(int a_location, long long a_contents)
{
    if (a_location < 0 || a_location >= MEMSZ)
    {
        // Invalid memory location
        return false;
    }
    m_memory[a_location] = a_contents;
    return true;
}

/**/
/*
bool emulator::runProgram()

NAME

        emulator::runProgram - Runs the program recorded in memory.

SYNOPSIS

        bool emulator::runProgram();

DESCRIPTION

        This method executes the program stored in the simulated memory. It interprets and
        executes each instruction sequentially, based on its opcode and operands. The
        execution begins from the location 100 and continues until a HALT instruction (opcode
        13) is encountered or all instructions in memory are executed.

        The method handles a variety of operations including arithmetic, data transfer,
        input/output, and control operations. If a division by zero is attempted, the method
        returns false. Otherwise, the method returns true upon successful execution.

RETURNS

        Returns true if the program executes successfully, and false otherwise.

AUTHOR

        Sikander Raja

*/
/**/

// Runs the program recorded in memory.
bool emulator::runProgram()
{
    int loc = 100;  // First instruction location is assumed to be 100 as per your instructions
    while (loc <= m_memory.size())  // Consider the provided location in the machine code
    {
        long long val = m_memory[loc - 100];  // Adjusted for zero-based indexing
        int opcode = (val / 10000000000) % 100;
        int operand1 = (val % 100000000) / 100000;
        int operand2 = val % 100000;

        switch (opcode)
        {
        case 0:  // No-op
            break;
        case 1:  // ADD
            m_memory[operand1] += m_memory[operand2];
            break;
        case 2:  // SUB
            m_memory[operand1] -= m_memory[operand2];
            break;
        case 3:  // MULT
            m_memory[operand1] *= m_memory[operand2];
            break;
        case 4:  // DIV
            if (m_memory[operand2] != 0)
            {
                m_memory[operand1] /= m_memory[operand2];
            }
            else
            {
                // Error - division by zero
                return false;
            }
            break;
        case 5:  // COPY
            m_memory[operand1] = m_memory[operand2];
            break;
        case 7:  // READ
            long long userInput;
            cout << "? ";
            cin >> userInput;
            m_memory[operand1] = userInput;
            break;
        case 8:  // WRITE
            cout << m_memory[operand1] << endl;
            break;
        case 9:  // BRANCH
            loc = operand1;
            continue;
        case 10:  // BRANCH MINUS
            if (m_memory[operand2] < 0)
            {
                loc = operand1;
                continue;
            }
            break;
        case 11:  // BRANCH ZERO
            if (m_memory[operand2] == 0)
            {
                loc = operand1;
                continue;
            }
            break;
        case 12:  // BRANCH POSITIVE
            if (m_memory[operand2] > 0)
            {
                loc = operand1;
                continue;
            }
            break;
        case 13:  // HALT
            return true;
        }
        loc++;
    }
    return true;
}

