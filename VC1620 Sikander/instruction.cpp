#include "stdafx.h"
#include "Instruction.h"
#include <sstream>


/**/
/*
Instruction::RemoveComment(string line)

NAME

    Instruction::RemoveComment - Removes comments from a line of assembly code.

SYNOPSIS

    string Instruction::RemoveComment(string line);
        line     --> a string containing a line of assembly code.

DESCRIPTION

    This method takes a line of assembly code and removes any comment present in it.
    A comment in assembly code is typically designated by a semicolon (;).

RETURNS

    Returns the input line without the comment.
*/
/**/

// RemoveComment takes a line and removes any comment present in it.
string Instruction::RemoveComment(string line) {
    size_t pos = line.find(';');
    if (pos == string::npos)
    {
        return line;
    }
    return line.erase(pos);
}

/**/
/*
Instruction::ParseLine(const string& line, string& label, string& opcode, string& operand1, string& operand2)

NAME

    Instruction::ParseLine - Parses a line of assembly code.

SYNOPSIS

    bool Instruction::ParseLine(const string& line, string& label, string& opcode, string& operand1, string& operand2);
        line      --> a string containing a line of assembly code.
        label     --> a string to store the label extracted from the line.
        opcode    --> a string to store the opcode extracted from the line.
        operand1  --> a string to store the first operand extracted from the line.
        operand2  --> a string to store the second operand extracted from the line.

DESCRIPTION

    This method takes a line of assembly code and parses it to extract the label, opcode,
    and operands. The extracted elements are stored in the corresponding output parameters.

RETURNS

    Returns true if the line is successfully parsed, otherwise false.

*/
/**/

// ParseLine takes a line and extracts the label, opcode, and operands.
bool Instruction::ParseLine(const string& line, string& label, string& opcode, string& operand1, string& operand2)
{
    istringstream ins(line);
    label = opcode = operand1 = operand2 = "";
    if (line.empty()) return true;

    string extra;

    if (line[0] != ' ' && line[0] != '\t')
    {
        ins >> label;
    }
    ins >> opcode;

    // Read the rest of the line into a string, which will be processed for operands later
    string rest_of_line;
    getline(ins, rest_of_line);

    // Find the position of the comma in the rest of the line
    size_t comma_pos = rest_of_line.find(',');

    if (comma_pos != string::npos) {
        operand1 = rest_of_line.substr(0, comma_pos);
        operand2 = rest_of_line.substr(comma_pos + 1);

        // Remove leading and trailing spaces from the operands
        operand1.erase(0, operand1.find_first_not_of(' '));
        operand1.erase(operand1.find_last_not_of(' ') + 1);
        operand2.erase(0, operand2.find_first_not_of(' '));
        operand2.erase(operand2.find_last_not_of(' ') + 1);
    }
    else {
        ins.clear();
        ins.str(rest_of_line);
        ins >> operand1 >> operand2; // Read both operands separated by space

        // Remove leading and trailing spaces from the operands
        operand1.erase(0, operand1.find_first_not_of(' '));
        operand1.erase(operand1.find_last_not_of(' ') + 1);
        operand2.erase(0, operand2.find_first_not_of(' '));
        operand2.erase(operand2.find_last_not_of(' ') + 1);
    }

    return extra == "";
}

/**/
/*
Instruction::ParseInstruction(string a_line)

NAME

    Instruction::ParseInstruction - Parses an instruction from a line of assembly code.

SYNOPSIS

    Instruction::InstructionType Instruction::ParseInstruction(string a_line);
        a_line   --> a string containing a line of assembly code.

DESCRIPTION

    This method takes a line of assembly code, removes any comment, and parses it to extract
    the label, opcode, and operands. It then sets the instruction type and numeric opcode
    based on the opcode.

RETURNS

    Returns the instruction type of the parsed instruction.

*/
/**/

Instruction::InstructionType Instruction::ParseInstruction(string a_line) {
    // Remove the comment, if any, and get the clean line.
    string cleanLine = RemoveComment(a_line);

    // Parse the line into label, opcode, and operands.
    string label, opcode, operand1, operand2;
    ParseLine(cleanLine, label, opcode, operand1, operand2);

    if (operand1.find(',') != string::npos) {
        size_t pos = operand1.find(',');
        operand2 = operand1.substr(pos + 1);
        operand1 = operand1.substr(0, pos);
    }


    m_Label = label;

    // Convert the opcode to lowercase.
    for (auto& c : opcode) {
        c = tolower(c);
    }

    m_OpCode = opcode;
    m_Operand1 = operand1;
    m_Operand2 = operand2;

    // Set the instruction type and numeric opcode based on the opcode.
    if (m_OpCode == "halt") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 13;
    }
    else if (m_OpCode == "read") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 07;
    }
    else if (m_OpCode == "write") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 8;
    }
    else if (m_OpCode == "copy") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 5;
    }
    else if (m_OpCode == "org") {
        m_type = ST_AssemblerInstr;
    }
    else if (m_OpCode == "dc") {
        m_type = ST_AssemblerInstr;
    }
    else if (m_OpCode == "ds") {
        m_type = ST_AssemblerInstr;
    }
    else if (m_OpCode == "bp") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 12;
    }
    else if (m_OpCode == "end") {
        m_type = ST_End;
    }
    else if (m_OpCode == "add") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 1;
    }
    else if (m_OpCode == "sub") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 2;
    }
    else if (m_OpCode == "mult") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 3;
    }
    else if (m_OpCode == "div") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 4;
    }
    else if (m_OpCode == "b") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 9;
    }
    else if (m_OpCode == "bm") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 10;
    }
    else if (m_OpCode == "bz") {
        m_type = ST_MachineLanguage;
        m_NumOpCode = 11;
    }
    else {
        m_type = ST_Comment;
    }

    return m_type;
}

/**/
/*
Instruction::LocationNextInstruction(int a_loc)

NAME

    Instruction::LocationNextInstruction - Computes the location of the next instruction.

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc);
        a_loc   --> an integer representing the current location.

DESCRIPTION

    This method computes the location of the next instruction based on the current opcode
    and operand(s). If the opcode is 'ds', it increments the location by the value of the
    first operand. If the opcode is 'org', it does not increment the location. For all other
    instructions, it increments the location by 1.

RETURNS

    Returns the location of the next instruction.

*/
/**/

// Compute the location of the next instruction.
int Instruction::LocationNextInstruction(int a_loc)
{
    // If the opcode is 'ds', increment the location by the value of the first operand.
    if (m_OpCode == "ds" && !m_Operand1.empty()) {
        try {
            int increment = stoi(m_Operand1);
            return a_loc + increment;
        }
        catch (const std::exception&) {
            // Handle the case where the operand is not a valid integer.
            // You may want to record an error here, e.g., using your Errors class.
        }
    }

    // If the opcode is 'org', do not increment the location.
    if (m_OpCode == "org") {
        return a_loc;
    }

    // For all other instructions, increment the location by 1.
    return a_loc + 1;
}



