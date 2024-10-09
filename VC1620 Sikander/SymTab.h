/*
The SymbolTable class manages a symbol table for an assembler. It is responsible for adding new symbols with their respective locations, displaying the content of the symbol table, 
and looking up symbols in the table. The symbol table is represented using a std::map with the symbol as the key and its location as the value. A constant value, multiplyDefinedSymbol, 
is defined to represent a multiply defined symbol in the symbol table.
*/

#pragma once

#include <iostream>
#include <map>
#include <string>

using namespace std;

// This class is our symbol table.
class SymbolTable {

public:

    // Get rid of constructor and destructor later if you don't need them.
    SymbolTable() {};
    ~SymbolTable() {};

    const int multiplyDefinedSymbol = -999;

    // Add a new symbol to the symbol table.
    void AddSymbol(const string& a_symbol, int a_loc);

    // Display the symbol table.
    void DisplaySymbolTable();

    // Lookup a symbol in the symbol table.
    bool LookupSymbol(const string& a_symbol, int& a_loc);


private:

    // This is the actual symbol table. The symbol is the key to the map. The value is the location.
    map<string, int> m_symbolTable;
};
