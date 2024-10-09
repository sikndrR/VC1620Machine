#include "stdafx.h"
#include "SymTab.h"
#include "Errors.h"

/**/
/*
SymbolTable::AddSymbol(const string& a_symbol, int a_loc)

NAME

    SymbolTable::AddSymbol - Adds a symbol and its location to the symbol table.

SYNOPSIS

    void SymbolTable::AddSymbol(const string& a_symbol, int a_loc);
        a_symbol   --> the symbol to add to the symbol table.
        a_loc      --> the location of the symbol.

DESCRIPTION

    This method adds a symbol and its location to the symbol table. If the symbol is
    already in the symbol table, it records it as multiply defined by assigning its location
    the value of multiplyDefinedSymbol.

*/
/**/

void SymbolTable::AddSymbol(const string& a_symbol, int a_loc)
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find(a_symbol);
    if (st != m_symbolTable.end()) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record the location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

    SymbolTable::DisplaySymbolTable - Displays the symbol table.

SYNOPSIS

    void SymbolTable::DisplaySymbolTable();

DESCRIPTION

    This method displays the symbol table. It prints the index, symbol, and location for each
    entry in the symbol table.

*/
/**/

void SymbolTable::DisplaySymbolTable()
{
    // Print the header.
    cout << "Symbol #\tSymbol\tLocation" << endl;

    // Iterate through the symbol table and print each symbol with its index and location.
    int index = 0;
    for (const auto& symbol : m_symbolTable)
    {
        cout << "  " << index << "\t\t" << symbol.first << "\t\t" << symbol.second << endl;
        index++;
    }

    // Print the divider line.
    cout << "__________________________________________________________" << endl << endl;
}


/**/
/*
SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)

NAME

    SymbolTable::LookupSymbol - Looks up a symbol in the symbol table.

SYNOPSIS

    bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc);
        a_symbol   --> the symbol to look up in the symbol table.
        a_loc      --> a reference to an integer where the location of the symbol will be stored.

DESCRIPTION

    This method looks up a symbol in the symbol table. If the symbol is found, it stores the
    location of the symbol in the output parameter and returns true. If the symbol is not found,
    it returns false.

RETURNS

    Returns true if the symbol is found in the symbol table, otherwise false.
*/
/**/

bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) {
    auto it = m_symbolTable.find(a_symbol);

    if (it != m_symbolTable.end()) {
        a_loc = it->second;
        return true;
    }

    return false;
}


