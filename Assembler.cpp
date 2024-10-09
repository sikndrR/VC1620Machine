#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include <iomanip>
#include <algorithm>

using namespace std;

/**/
/*
Assembler::Assembler(int argc, char* argv[])

NAME

    Assembler::Assembler - Constructs the assembler and initiates the file access.

SYNOPSIS

    Assembler::Assembler(int argc, char* argv[]);
        argc      --> count of command line arguments.
        argv      --> array of command line arguments.

DESCRIPTION

    The constructor for the assembler. This passes the argc and argv to the FileAccess
    constructor, which handles opening the file. At this point, there's nothing else to be done.

*/
/**/

// See main program.
Assembler::Assembler(int argc, char* argv[])
    : m_facc(argc, argv)
{
    // Nothing else to do here at this point.
}

// Destructor currently does nothing. You might need to add something as you develop this project. If not, we can delete it.
Assembler::~Assembler()
{
}

/**/
/*
Assembler::PassI()

NAME

    Assembler::PassI - Executes the first pass of the assembler.

SYNOPSIS

    void Assembler::PassI();

DESCRIPTION

    This method carries out the first pass of the assembler. It reads and processes each line
    of the source code. For each instruction, it parses the line and gets the instruction type.
    If it encounters an end statement, it stops processing. If it finds a comment, it skips to the
    next line. If it comes across an "org" directive, it updates the location counter to the value
    specified by "org". If the instruction has a label, it records the label and its location in
    the symbol table. Then, it computes the location of the next instruction.

*/
/**/

void Assembler::PassI()
{
    int loc = 0; // Reset the location counter.

    // Successively process each line of source code.
    for (;;) {
        // Read the next line from the source file.
        string line;
        if (!m_facc.GetNextLine(line)) {
            // If there are no more lines, we are missing an end statement.
            Errors::RecordError("Error: Missing END statement.");
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        if (st == Instruction::ST_End) break;

        // Skip comments.
        if (st == Instruction::ST_Comment) continue;

        // Check for "org" directive
        if (m_inst.GetOpcode() == "org") {
            loc = stoi(m_inst.GetOperand1()); // Update the location counter to the value specified by "org"
        }
        else {
            // If the instruction has a label, record it and its location in the symbol table.
            if (!m_inst.GetLabel().empty()) {
                m_symtab.AddSymbol(m_inst.GetLabel(), loc);
            }

            // Compute the location of the next instruction.
            loc = m_inst.LocationNextInstruction(loc);
        }
    }
}

/**/
/*
Assembler::HandleCopyInstruction(int a_location, const string& a_operand1, const string& a_operand2)

NAME

    Assembler::HandleCopyInstruction - Handles the copy instruction.

SYNOPSIS

    void Assembler::HandleCopyInstruction(int a_location, const string& a_operand1, const string& a_operand2);
        a_location   --> the location of the instruction.
        a_operand1   --> the first operand of the copy instruction.
        a_operand2   --> the second operand of the copy instruction.

DESCRIPTION

    This method handles the copy instruction. It looks up the symbols corresponding to the operands
    in the symbol table and prints the load and store instructions that perform the copy operation.
    If either of the operands is not found in the symbol table, it prints an error message.

*/
/**/

void Assembler::HandleCopyInstruction(int a_location, const string& a_operand1, const string& a_operand2) {
    int loc1, loc2;
    if (m_symtab.LookupSymbol(a_operand1, loc1) && m_symtab.LookupSymbol(a_operand2, loc2)) {
        int loadOpCode = 13;
        int storeOpCode = 14;
        cout << setfill('0') << setw(4) << a_location << " " << setfill('0') << setw(4) << (loadOpCode << 12 | loc1) << "    " << "load " << a_operand1 << "\n";
        cout << setfill('0') << setw(4) << (a_location + 1) << " " << setfill('0') << setw(4) << (storeOpCode << 12 | loc2) << "    " << "store " << a_operand2 << "\n";
    }
    else {
        cout << setfill('0') << setw(4) << a_location << " ??????    " << "hay  copy   " << a_operand1 << ", " << a_operand2 << " ; This is the another comment." << "\n";
    }
}
/**/
/*
Assembler::GenerateMachineCode(const Instruction& inst)

NAME

    Assembler::GenerateMachineCode - Generates machine code for an instruction.

SYNOPSIS

    int Assembler::GenerateMachineCode(const Instruction& inst);
        inst        --> the instruction to generate machine code for.

DESCRIPTION

    This method generates machine code for an instruction. It gets the numeric opcode of the
    instruction and checks whether each operand is a number or a symbol. If an operand is a
    number, it converts the operand to an integer. If an operand is a symbol, it looks up the
    symbol in the symbol table and gets its location. If a symbol is not found in the symbol
    table, it throws an exception. Finally, it concatenates the opcode and the operand locations
    to form the machine code.

RETURNS

    Returns the machine code for the instruction.
*/
/**/

int Assembler::GenerateMachineCode(const Instruction& inst)
{
    int opCode = inst.GetNumericOpcode();

    // Function to check if a string is a number
    auto is_number = [](const std::string& s) {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    };

    // Get the numeric value of the first operand, if it exists
    int address1 = 0;
    if (!inst.GetOperand1().empty()) {
        if (is_number(inst.GetOperand1())) {
            address1 = stoi(inst.GetOperand1());
        }
        else if (m_symtab.LookupSymbol(inst.GetOperand1(), address1) == false) {
            throw std::runtime_error("Error: Undefined symbol: " + inst.GetOperand1());
        }
    }

    // Get the numeric value of the second operand, if it exists
    int address2 = 0;
    if (!inst.GetOperand2().empty()) {
        if (is_number(inst.GetOperand2())) {
            address2 = stoi(inst.GetOperand2());
        }
        else if (m_symtab.LookupSymbol(inst.GetOperand2(), address2) == false) {
            throw std::runtime_error("Error: Undefined symbol: " + inst.GetOperand2());
        }
    }

    // Add these lines to store the addresses for later use
    m_address1 = address1;
    m_address2 = address2;

    // Concatenate the opCode, address1, and address2 to form the machine code
    int machineCode;

    machineCode = opCode * 100000000 + address1 * 100000 + address2;

    return machineCode;
}

/**/
/*
Assembler::RunProgramInEmulator()

NAME

    Assembler::RunProgramInEmulator - Runs the translated program in the emulator.

SYNOPSIS

    void Assembler::RunProgramInEmulator();

DESCRIPTION

    This method runs the translated program in the emulator. It first creates an instance of
    the emulator. Then, it inserts each machine instruction into the emulator's memory. If an
    error occurs during this process, it prints an error message and returns. Finally, it runs
    the program in the emulator. If an error occurs during this process, it prints an error message.

*/
/**/

void Assembler::RunProgramInEmulator()
{
    emulator emu; // Create an instance of the emulator
    cout << "Results from emulating program:" << endl;

    // Insert the machine code into the emulator's memory
    for (int i = 0; i < m_machineCode.size(); i++) {
        if (!emu.insertMemory(i, std::stoll(m_machineCode[i]))) {
            std::cerr << "Error: Could not insert instruction into memory\n";
            return;
        }
    }

    // Run the program in the emulator
    if (!emu.runProgram()) {
        std::cerr << "Error: Could not run program in emulator\n";
    }
    cout << "End of emulation" << endl;
}

/**/
/*
Assembler::PassII()

NAME

    Assembler::PassII - Executes the second pass of the assembler.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    This method executes the second pass of the assembler. It begins by resetting the location
    counter and rewinding the source file to the beginning. Then, it successively processes each
    line of source code. For each line, it parses the instruction and determines the instruction type.
    If the instruction is a comment or end statement, it prints the line and continues to the next line.
    If the instruction has a label, it looks up the label in the symbol table and gets its location.
    Then, it generates machine code for the instruction. If an error occurs during this process,
    it records the error message and continues with the translation. Finally, it prints the machine
    code and original statement, and computes the location of the next instruction. When all lines
    have been processed, it displays any recorded error messages.
*/
/**/

void Assembler::PassII()
{
    int loc = 0; // Location counter
    string line; // Line from the source file

    // Rewind the source file to the beginning
    m_facc.rewind();

    cout << "Translation of Program:\n\n";
    cout << "Location    Contents    Original Statement\n";

    // Iterate through the source file
    while (true)
    {
        // Get the next line from the source file
        if (!m_facc.GetNextLine(line))
        {
            break;
        }

        // Parse the instruction
        Instruction::InstructionType type = m_inst.ParseInstruction(line);

        // Ignore comments and end instructions
        if (type == Instruction::ST_Comment || type == Instruction::ST_End)
        {
            cout << "                 " << line << endl;
            continue;
        }

        // If the instruction has a label, get the location from the symbol table
        if (m_inst.isLabel())
        {
            string label = m_inst.GetLabel();
            int labelLoc;
            if (m_symtab.LookupSymbol(label, labelLoc))
            {
                loc = labelLoc;
            }
        }

        // Generate the machine code for the instruction
        int machineCode;
        try
        {
            machineCode = GenerateMachineCode(m_inst);
        }
        catch (const std::exception& e)
        {
            // Record the error message and continue with the translation
            Errors::RecordError(e.what());
            cout << setfill('0') << setw(4) << loc << "    " << "??????" << "    " << line << endl;
            loc = m_inst.LocationNextInstruction(loc);
            return;
        }

        // Output the machine code
        int opcode = machineCode / 100000000;
        int first_address = m_address1;
        int second_address = m_address2;

        string opcodeStr = m_inst.GetOpcode();
        std::transform(opcodeStr.begin(), opcodeStr.end(), opcodeStr.begin(), ::tolower);
        if (opcodeStr == "dc") {
            opcode = 0;
            second_address = first_address;
            first_address = 0;
        }
        else if (opcodeStr == "ds" || opcodeStr == "org") {
            opcode = 0;
            second_address = 0;
            first_address = 0;
        }

        if (m_inst.GetOpcode() == "copy")
        {
            first_address = m_address1;
            second_address = m_address2;
        }

        cout << setfill(' ') << setw(4) << loc << "    ";
        cout << setfill('0') << setw(2) << opcode;
        cout << setfill('0') << setw(5) << first_address;
        cout << setfill('0') << setw(5) << second_address << "    " << line << endl;

        // Assuming opcode, first_address, and second_address are of type int
        stringstream ss;
        ss << loc;
        ss << setfill('0') << setw(2) << opcode;
        ss << setfill('0') << setw(5) << first_address;
        ss << setfill('0') << setw(5) << second_address;
        m_machineCode.push_back(ss.str());

        // Update the location counter for the next instruction
        loc = m_inst.LocationNextInstruction(loc);
    }

    // Display the recorded error messages (if any)
    Errors::DisplayErrors();
}
