//
//      Assembler class.  This is a container for all the components
//      that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"

class Assembler {

public:

    // Constructor for the Assembler class. The command line arguments are passed to FileAccess object.
    Assembler(int argc, char* argv[]);

    // Destructor for the Assembler class.
    ~Assembler();

    // Pass I - establish the locations of the symbols
    void PassI();

    // Assemble function
    void Assemble();

    // Pass II - generate a translation
    void PassII();

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

    // Run emulator on the translation.
    void RunProgramInEmulator();

    int GenerateMachineCode(const Instruction& inst);

private:

    FileAccess m_facc;      // File Access object
    SymbolTable m_symtab;   // Symbol table object
    Instruction m_inst;     // Instruction object
    emulator m_emul;        // Emulator object

    int m_address1; // Numeric value of the first operand.
    int m_address2; // Numeric value of the second operand.

    // Handles the special case of the "copy" instruction which gets translated into two machine instructions.
    void HandleCopyInstruction(int a_location, const string& a_operand1, const string& a_operand2);
    std::vector<string> m_machineCode; // Vector to store the translated machine code.

};
