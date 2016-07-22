#include <CMapLoader.h>

CMapLoader::CMapLoader()
{

}

CMapLoader::~CMapLoader()
{

}

void CMapLoader::loadMap(const char *file)
{
//Count the lines in our file
    unsigned int size = getFileSize("Abstract World Editor.bat");
    FILE *mapFile;

// ---- Load the script
// Open the script and print an error if it's not found
    if ( ! ( mapFile = fopen ( file, "r" ) ) )
    {
        printf ( "File I/O error.\n" );
        return;
    }

// Allocate a script of the proper size
 //   mapFile = ( char ** ) malloc ( size * sizeof ( char * ) );
// Load each line of code
  //  for ( int index = 0; index < size; ++ index )
  //  {

// Allocate space for the line and a null terminator
       // g_ppstrScript [ iCurrLineIndex ] = ( char * )
                                  //         malloc ( MAX_SOURCE_LINE_SIZE + 1 );
// Load the line
       // fgets ( g_ppstrScript [ iCurrLineIndex ],
        //        MAX_SOURCE_LINE_SIZE, pScriptFile );
  //  }
// Close the script
  //  fclose ( pScriptFile );
}

