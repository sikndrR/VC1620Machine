/*
This class provides a simple mechanism for recording and reporting errors. During the assembly process, if an error is encountered, the error message is recorded using RecordError. 
Once the assembly process is complete, all recorded error messages can be displayed using DisplayErrors. The HasErrors function can be used to check if any errors were recorded.
InitErrorReporting is used to clear any existing errors, which is useful for cases where the assembler is run multiple times within the same program.
*/

#ifndef _ERRORS_H  // UNIX way of preventing multiple inclusions.
#define _ERRORS_H

#include <string>  // For string objects
#include <vector>  // For vector containers

// Errors class is responsible for handling errors during the assembly process.
class Errors {

public:

    // Initializes error reporting. Clears any existing errors from previous runs.
    static void InitErrorReporting();

    // Records an error message. a_emsg is the error message to be recorded.
    static void RecordError(string a_emsg);

    // Displays the collected error messages. Messages are printed to standard output.
    static void DisplayErrors();

    // Checks if there were any errors recorded.
    static bool HasErrors();

private:

    // A vector that stores error messages. Note that this is a static member, so it's shared across all instances of the class.
    static vector<string> m_errors;

};

#endif
