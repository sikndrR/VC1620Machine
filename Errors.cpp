#include "stdafx.h"
#include "Errors.h"
#include <iostream>

vector<string> Errors::m_errors;


/**/
/*
void Errors::InitErrorReporting()

NAME

        Errors::InitErrorReporting - Initializes error reports.

SYNOPSIS

        void Errors::InitErrorReporting();

DESCRIPTION

        This method clears the vector that stores the error messages. This is usually
        called at the start of the assembly process to ensure any previous error messages
        are not carried over.

*/
/**/

// Initializes error reports.
void Errors::InitErrorReporting() {
    m_errors.clear();
}

/**/
/*
void Errors::RecordError(string a_emsg)

NAME

        Errors::RecordError - Records an error message.

SYNOPSIS

        void Errors::RecordError(string a_emsg);
            a_emsg    --> The error message to be recorded.

DESCRIPTION

        This method adds a given error message (a_emsg) to the vector of error messages.
        It's typically called whenever an error is detected during the assembly process.
*/
/**/

// Records an error message.
void Errors::RecordError(string a_emsg) {
    m_errors.push_back(a_emsg);
}

/**/
/*
void Errors::DisplayErrors()

NAME

        Errors::DisplayErrors - Displays the collected error messages.

SYNOPSIS

        void Errors::DisplayErrors();

DESCRIPTION

        This method iterates over the vector of recorded error messages and outputs each
        one to the console. It's typically called after the assembly process to display any
        errors that occurred.
*/
/**/

// Displays the collected error message.
void Errors::DisplayErrors() {
    cout << "Errors encountered during assembly:" << endl;
    for (const auto& error : m_errors) {
        cout << "  " << error << endl;
    }
}

