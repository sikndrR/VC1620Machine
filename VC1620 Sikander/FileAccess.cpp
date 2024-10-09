//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"


/**/
/*
FileAccess::FileAccess( int argc, char *argv[] )

NAME

        FileAccess::FileAccess - Constructor for FileAccess class.

SYNOPSIS

        FileAccess::FileAccess( int argc, char *argv[] );
            argc       --> The number of arguments passed to the program.
            argv       --> The arguments passed to the program as an array of character pointers.

DESCRIPTION

        This constructor checks if there is exactly one run-time parameter (a file name). If not,
        it reports an error and terminates the program. If there is, it attempts to open that file
        for reading. If the file cannot be opened, it reports an error and terminates the program.

*/
/**/

// Don't forget to comment the function headers.
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
}

/**/
/*
FileAccess::~FileAccess()

NAME

        FileAccess::~FileAccess - Destructor for FileAccess class.

SYNOPSIS

        FileAccess::~FileAccess();

DESCRIPTION

        This destructor closes the file opened by the constructor. This operation is not strictly
        necessary, as the file would be closed when the program terminates, but it is good practice.

*/
/**/

FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}

/**/
/*
bool FileAccess::GetNextLine( string &a_line )

NAME

        FileAccess::GetNextLine - Retrieves the next line from the file.

SYNOPSIS

        bool FileAccess::GetNextLine( string &a_line );
            a_line    --> A reference to the string that will store the retrieved line.

DESCRIPTION

        This method reads the next line from the file into the string a_line. If there are no
        more lines in the file, it returns false. Otherwise, it returns true.

RETURNS

        Returns true if a line was successfully read from the file, and false otherwise.

*/
/**/

// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}


/**/
/*
void FileAccess::rewind()

NAME

        FileAccess::rewind - Resets the file stream.

SYNOPSIS

        void FileAccess::rewind();

DESCRIPTION

        This method clears all file flags and resets the file stream to the beginning of the file.
        It is typically used when you want to read the file from the beginning after reaching the end.

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}
    
