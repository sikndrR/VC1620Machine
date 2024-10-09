/*
This class provides a basic mechanism for reading from a file line by line. It encapsulates an ifstream object (m_sfile) and provides methods for opening the 
file (FileAccess constructor), getting the next line from the file (GetNextLine), and resetting the file stream to the beginning of the file (rewind). The destructor 
(~FileAccess) ensures that the file is properly closed when we are done with it.
*/

#ifndef _FILEACCESS_H  // UNIX way of preventing multiple inclusions. 
#define _FILEACCESS_H  // A unique identifier is set as a flag, preventing multiple inclusions of this header file.

#include <fstream>  // For file stream operations
#include <stdlib.h>
#include <string>  // For string objects

// The FileAccess class provides mechanisms for reading from a source file. 
class FileAccess {

public:

    // Constructor. Opens the file specified by the command-line arguments.
    // Throws an error if the file cannot be opened.
    // argc is the number of command-line arguments.
    // argv is an array of command-line arguments.
    FileAccess(int argc, char* argv[]);

    // Destructor. Closes the source file.
    ~FileAccess();

    // Reads the next line from the source file.
    // The read line is returned through the parameter a_line.
    // Returns true if a line was successfully read, false otherwise (e.g., if end of file was reached).
    bool GetNextLine(string& a_line);

    // Resets the file stream to the beginning of the source file.
    void rewind();

private:

    // An input file stream object used to read from the source file.
    ifstream m_sfile;

};

#endif
