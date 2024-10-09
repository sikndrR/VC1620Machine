/*
The Instruction class is responsible for parsing and providing information about an assembly language instruction. This includes the opcode, any operands, and labels associated with the instruction. 
This class also handles the classification of the instruction type (machine language, assembler instruction, comment, or end instruction). Various helper functions are used to parse a line of 
assembly language and extract the relevant components.
*/

#pragma once  // Ensures the header file is only included once during compilation

#include <string>  // For std::string objects
using namespace std;  // Make std namespace available to the code

// The Instruction class is responsible for parsing and providing information
// about instructions in an assembly language.
class Instruction {

public:

    // Default constructor and destructor.
    Instruction() { };
    ~Instruction() { };

    // InstructionType is an enumeration that represents the type of instruction.
    enum InstructionType {
        ST_MachineLanguage,  // A machine language instruction.
        ST_AssemblerInstr,   // Assembler Language instruction.
        ST_Comment,          // Comment or blank line
        ST_End               // End instruction.
    };

    // The ParseInstruction method takes a line from the assembly code 
    // and classifies its type (machine language, assembler instruction, comment, or end).
    InstructionType ParseInstruction(string a_line);

    // The LocationNextInstruction method calculates the location of the next instruction 
    // based on the current location.
    int LocationNextInstruction(int a_loc);

    // The GetLabel method returns the label of the current instruction, if it exists.
    inline string& GetLabel() { return m_Label; };

    // The isLabel method checks if the current instruction has a label.
    inline bool isLabel() { return !m_Label.empty(); };

    // The GetNumericOpcode method returns the numeric opcode of the current instruction.
    inline int GetNumericOpcode() const { return m_NumOpCode; };

    // The GetOpcode method returns the opcode of the current instruction.
    inline const string& GetOpcode() const { return m_OpCode; };

    // The GetOperand1 method returns the first operand of the current instruction.
    inline const string& GetOperand1() const { return m_Operand1; };

    // The GetOperand2 method returns the second operand of the current instruction.
    inline const string& GetOperand2() const { return m_Operand2; };

private:

    // The RemoveComment method removes any comment present in the line.
    string RemoveComment(string line);

    // The ParseLine method parses a line into label, opcode, and operands.
    bool ParseLine(const string& line, string& label, string& opcode, string& operand1, string& operand2);

    // The trim method removes leading and trailing white space from a string.
    string trim(const string& str);

    // Private member variables representing the elements of an instruction
    string m_Label;
    string m_OpCode;
    string m_Operand1;
    string m_Operand2;
    string m_instruction;

    // Derived values from an instruction
    int m_NumOpCode;
    InstructionType m_type;
    bool m_IsNumericOperand;
    int m_OperandValue;
};
