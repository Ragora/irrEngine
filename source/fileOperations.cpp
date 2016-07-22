#include <fileOperations.h>

unsigned int getFileSize(const char *file)
{
    FILE *mapFile;

// Open the source file in binary mode
    if ( ! ( mapFile = fopen ( file, "rb" ) ) )
    {
        printf ( "File I/O error.\n" );
        return 0;
    }

    unsigned int size = 0;

// Count the number of source lines
    while ( ! feof ( mapFile ) )
        if ( fgetc ( mapFile ) == '\n' )
            ++ size;
    ++ size;
// Close the file
    fclose ( mapFile );

    return size;
}
