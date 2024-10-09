/**/
/*
int main( int argc, char *argv[] )

NAME

        main - The entry point for the Assembler program.

SYNOPSIS

        int main( int argc, char *argv[] );
            argc       --> The number of arguments passed to the program.
            argv       --> The arguments passed to the program as an array of character pointers.

DESCRIPTION

        The main function is the entry point of the program. It creates an instance of the
        Assembler class, passing the program arguments to its constructor. Then, it calls
        the PassI, DisplaySymbolTable, PassII, and RunProgramInEmulator methods
        sequentially. These methods together execute the primary functions of the assembler:
        locating labels, displaying the symbol table, translating assembler code, and running
        the translated code in an emulator, respectively.

        If there are any unrecoverable errors during execution, the program will terminate
        immediately with an exit(1) call.

RETURNS

        Returns 0 if the program executes successfully. If there is an unrecoverable error,
        the program will terminate at the point that it occurred with an exit(1) call.
*/
/**/

#include "stdafx.h"     // This must be present if you use precompiled headers which you will use. 
#include <stdio.h>

#include "Assembler.h"

int main(int argc, char* argv[])
{
    Assembler assem(argc, argv);

    // Establish the location of the labels:
    assem.PassI();

    // Display the symbol table.
    assem.DisplaySymbolTable();

    // Output the translation.
    assem.PassII();

    // Run the emulator on the translation of the assembler language program that was generated in Pass II.
    assem.RunProgramInEmulator();

    // Terminate indicating all is well.  If there is an unrecoverable error, the 
    // program will terminate at the point that it occurred with an exit(1) call.
    return 0;
}


