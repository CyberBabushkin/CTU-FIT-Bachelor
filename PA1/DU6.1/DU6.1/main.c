/**
 * Читать познаково каждую строку и считать, не достигли ли мы конца форм. строки - 1 с учетом битовой нулы.
 * Если обнаружим символ ютф 8, подсчитывать их, чтобы перед записью строки сделать реаллок.
 * Проверять символы на правильность кода ютф8.
 * Если обнаружим белый знак, то записать слово во основной буфер, проследить пунктуацию.
 * Перед записью проследить размер.
 *
 */

#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
/*#include <wchar.h>
#include <locale.h>*/

/* ----------------------------------------------------------------------------- */

typedef struct TPage
{
    char         ** m_Lines;
    int             m_LinesNr;
} TPAGE;

typedef struct TDocument
{
    TPAGE         * m_Pages;
    int             m_PagesNr;
} TDOCUMENT;

#endif /* __PROGTEST__ */

typedef struct
{
    char          * word;
    int             length;
} TWORD;

/* ----------------------------------------------------------------------------- */

int isPunctuationSign ( char c );
void readOneWord( const char * text, int index, TWORD * word, int * next );
int addWordToLine( TWORD * word,
                  char * line,
                  int * charsOnLine,
                  int pageWidth);
void addIdentation ( char * line, int * charsOnLine, int * identation );
void createNewPage ( TDOCUMENT * doc,
                    int pageWidth,
                    int pageRows);
void finishTheLineAndGetTheNext ( TDOCUMENT * document,
                                 int pageRows,
                                 int pageWidth,
                                 char ** workingLine,
                                 int * identation,
                                 int * charsAlreadyOnTheLine );
TDOCUMENT * DocFormat( int          pageWidth,
                      int          pageRows,
                      const char * text );
void DocFree( TDOCUMENT  * x );

unsigned int sizeOfPagesArray = 0, sizeOfWord = 8;

/* ----------------------------------------------------------------------------- */

int isPunctuationSign ( char c )
{
    switch ( c ) {
        case '?' :
        case '!' :
        case '.' :
        case ';' :
        case ',' :
        case ':' :
            return 1;
            break;
            
        default:
            return 0;
            break;
    }
}

/* ----------------------------------------------------------------------------- */

void readOneWord( const char * text, int index1, TWORD * word, int * next )
{
    char c;
    int freeSpace, startIndex = (unsigned int)index1;
    unsigned int index = (unsigned int)index1;
    
    if ( !word->word )
    {
        word->word  = (char *) malloc( sizeOfWord * sizeof( char ) );
        freeSpace = sizeOfWord;
    } else {
        freeSpace = sizeOfWord;
    }
    
    word->length = 0;
    
    c = text[index];
    
    while ( c != ' ' && c != '\n' && c != '\t' && !isPunctuationSign( c ) )
    {
        if ( !freeSpace )
        {
            sizeOfWord *= 2;
            word->word  = (char *) realloc( word->word, sizeOfWord * sizeof( char ) );
            freeSpace = word->length;
        }
        freeSpace--;
        
        word->word[word->length] = c;
        word->length++;
        
        index++;
        if ( text[index-1] == '\0' || ( text[index-1] != '\0' && text[index] == '\0' ))
        {
            break;
        }
        c = text[index];
    }
    
    *next = index - startIndex;
    
    while ( c == ' ' || c == '\n' || c == '\t' || c == '\0' )
    {
        index++;
        if ( c == '\0'  )
        {
            break;
        }
        c = text[index];
    }
    
    if ( isPunctuationSign( c ) )
    {
        if ( !freeSpace )
        {
            sizeOfWord *= 2;
            word->word  = (char *) realloc( word->word, sizeOfWord * sizeof( char ) );
            freeSpace = word->length;
        }
        freeSpace--;
        word->word[word->length] = c;
        word->length++;
        
        *next = index - startIndex + 1;
    }
    
    if ( !freeSpace )
    {
        sizeOfWord *= 2;
        word->word  = (char *) realloc( word->word, sizeOfWord * sizeof( char ) );
        freeSpace = word->length;
    }
    freeSpace--;
    word->word[word->length] = 0;
}

/* ----------------------------------------------------------------------------- */

/*
 * Adds one word to the line.
 * @return 1 if added, 0 if not.
 */

int addWordToLine( TWORD * word,
                  char * line,
                  int * charsOnLine,
                  int pageWidth)
{
    int signsLeft = pageWidth - *charsOnLine;
    int i, wasWord = 0, beginningOfLine = 0;
    
    if ( *charsOnLine == 0 ||
        ( *charsOnLine == 3
         && line[0] == ' '
         && line[1] == ' '
         && line[2] == ' ' ) )
    {
        beginningOfLine = 1;
    }
    
    if ( !beginningOfLine )
    {
        if ( isPunctuationSign( line[*charsOnLine - 1] ) )
        {
            signsLeft -= 2;
            wasWord = 0;
        } else {
            signsLeft -= 1;
            wasWord = 1;
        }
    }
    
    if ( signsLeft < word->length )
    {
        return 0;
    }
    
    if ( !beginningOfLine )
    {
        line[*charsOnLine] = ' ';
        (*charsOnLine)++;
        if ( !wasWord )
        {
            line[*charsOnLine] = ' ';
            (*charsOnLine)++;
        }
    }
    for ( i = 0; i < word->length; i++ )
    {
        
        line[*charsOnLine + i] = word->word[i];
    }
    *charsOnLine += word->length;
    return 1;
    
}

/* ----------------------------------------------------------------------------- */

void addIdentation ( char * line, int * charsOnLine, int * identation )
{
    if ( *identation )
    {
        line[0] = ' ';
        line[1] = ' ';
        line[2] = ' ';
        *charsOnLine += 3;
        *identation = 0;
    }
}

/* ----------------------------------------------------------------------------- */

void reallocAndUpdateMemAddresses ( TDOCUMENT * doc,
                                   int pageWidth,
                                   int pageRows )
{
    int i, j;
    /*TPAGE * newPages;
    char ** newLines;
    char * newChars;
    
    newChars = ( char * ) malloc( (pageWidth + 1) * sizeOfPagesArray * pageRows * sizeof( char ) );
    newLines = ( char ** ) malloc( sizeOfPagesArray * pageRows * sizeof( char * ) );
    newPages = ( TPAGE * ) malloc( sizeOfPagesArray * sizeof( TPAGE ) );
    
    for ( i = 0; i < sizeOfPagesArray; i++ )
    {
        newPages[i].m_Lines = newLines + i * pageRows;
        
        for ( j = 0; j < pageRows; j++ )
        {
            newPages[i].m_Lines[j] = newChars + (pageWidth + 1) * (pageRows * i + j);
        }
    }
    
    for ( i = 0; i < (pageWidth + 1) * pageRows * (doc->m_PagesNr - 1); i++ )
    {
        newChars[i] = doc->m_Pages[0].m_Lines[0][i];
    }
    
    if ( doc->m_PagesNr > 0 )
    {
        free( doc->m_Pages[0].m_Lines[0] );
        free( doc->m_Pages[0].m_Lines );
        free( doc->m_Pages );
    }
    
    doc->m_Pages = newPages;
    */
    
    doc->m_Pages = ( TPAGE * ) realloc( doc->m_Pages, sizeOfPagesArray * sizeof( TPAGE ) );
    
    if ( doc -> m_PagesNr == 0 )
    {
        doc->m_Pages[0].m_Lines = NULL;
    }
    doc->m_Pages[0].m_Lines = ( char ** ) realloc( doc->m_Pages[0].m_Lines, sizeOfPagesArray * pageRows * sizeof( char * ) );
    
    if ( doc -> m_PagesNr == 0 )
    {
        doc->m_Pages[0].m_Lines[0] = NULL;
    }
    doc->m_Pages[0].m_Lines[0] = ( char * ) realloc( doc->m_Pages[0].m_Lines[0],
                                                    (pageWidth + 1) * sizeOfPagesArray * pageRows * sizeof( char ) );
    
    for ( i = 0; i < doc->m_PagesNr; i++ )
    {
        doc->m_Pages[i].m_Lines = doc->m_Pages[0].m_Lines + i * pageRows;
        
        for ( j = 0; j < pageRows; j++ )
        {
            doc->m_Pages[i].m_Lines[j] = doc->m_Pages[0].m_Lines[0] + (pageWidth + 1) * (pageRows * i + j);
        }
        
    }
    
}

/* ----------------------------------------------------------------------------- */

void createNewPage ( TDOCUMENT * doc,
                    int pageWidth,
                    int pageRows )
{
    int i;
    
    if ( doc->m_PagesNr == 0 )
    {
        doc->m_Pages = NULL;
        sizeOfPagesArray = 2;
        reallocAndUpdateMemAddresses( doc, pageWidth, pageRows );
    }
    
    doc->m_PagesNr++;
    if ( (unsigned int) doc->m_PagesNr > sizeOfPagesArray )
    {
        sizeOfPagesArray *= 2;
        reallocAndUpdateMemAddresses( doc, pageWidth, pageRows );
        
        doc->m_Pages[doc->m_PagesNr-1].m_LinesNr = 0;
        
    } else {
        
        doc->m_Pages[doc->m_PagesNr-1].m_Lines = doc->m_Pages[0].m_Lines + (doc->m_PagesNr - 1) * pageRows;
        
        for ( i = 0; i < pageRows; i++ )
        {
            doc->m_Pages[doc->m_PagesNr-1].m_Lines[i] = doc->m_Pages[0].m_Lines[0] + (pageWidth + 1) * (pageRows * (doc->m_PagesNr - 1) + i);
        }
        
        doc->m_Pages[doc->m_PagesNr-1].m_LinesNr = 0;
    }
}

/* ----------------------------------------------------------------------------- */

void finishTheLineAndGetTheNext ( TDOCUMENT * document,
                                  int pageRows,
                                  int pageWidth,
                                  char ** workingLine,
                                  int * identation,
                                  int * charsAlreadyOnTheLine )
{
    /* Adding a page if needed */
    if ( document->m_Pages[document->m_PagesNr - 1].m_LinesNr + 1 > pageRows )
    {
        createNewPage( document, pageWidth, pageRows );
    }
    
    /* Repairing the line after reallocation */
    *workingLine = document->m_Pages[document->m_PagesNr - 1].m_Lines[document->m_Pages[document->m_PagesNr - 1].m_LinesNr - 1];
    
    /* Adding 0 to the end of line */
    (*workingLine)[*charsAlreadyOnTheLine] = 0;
    
    /* Adding new row */
    document->m_Pages[document->m_PagesNr - 1].m_LinesNr++;
    
    /* Going to the last line in the doc */
    (*workingLine) = document->m_Pages[document->m_PagesNr - 1].m_Lines[document->m_Pages[document->m_PagesNr - 1].m_LinesNr - 1];
    *charsAlreadyOnTheLine = 0;
    
    /* Adding identation to the new line */
    addIdentation( *workingLine , charsAlreadyOnTheLine, identation );
}

/* ----------------------------------------------------------------------------- */

TDOCUMENT * DocFormat( int          pageWidth,
                       int          pageRows,
                       const char * text )
{
    TDOCUMENT * document;
    
    int identation = 1;
    int allWhitespaces = 1;
    int skipSymbols = 0, needNN = 0;
    int wasNewLine = 0;
    int wordWasAdded = 0;
    int i = 0;
    TWORD word;
    char * workingLine;
    int charsAlreadyOnTheLine = 0;
    
    if ( pageWidth <= 3 || pageRows <= 0 )
    {
        return NULL;
    }
    
    word.word = NULL;
    
    /* Creating empty document */
    document = (TDOCUMENT *) malloc( sizeof( TDOCUMENT ) );
    document->m_PagesNr = 0;
    createNewPage( document, pageWidth, pageRows );
    
    /* The first line */
    workingLine = document->m_Pages[0].m_Lines[0];
    document->m_Pages[0].m_LinesNr++;
    addIdentation( workingLine , &charsAlreadyOnTheLine, &identation );
    
    /* Main cycle */
    while ( text[i] )
    {
        /* Found the beginning of the word */
        if ( text[i] != ' ' && text[i] != '\n' && text[i] != '\t' )
        {
            
            if ( needNN )
            {
                finishTheLineAndGetTheNext( document,
                                           pageRows,
                                           pageWidth,
                                           &workingLine,
                                           &identation,
                                           &charsAlreadyOnTheLine );
                workingLine[0] = '\n';
                identation = 1;
                
                finishTheLineAndGetTheNext( document,
                                           pageRows,
                                           pageWidth,
                                           &workingLine,
                                           &identation,
                                           &charsAlreadyOnTheLine );
                needNN = 0;
            }

            
            allWhitespaces = 0;
            wasNewLine = 0;
            
            if ( isPunctuationSign( text[i] ) )
            {
                DocFree( document );
                if ( word.word )
                {
                    free( word.word );
                }
                return NULL;
            }
            
            readOneWord( text, i, &word, &skipSymbols );
            
            if ( word.length > pageWidth )
            {
                DocFree( document );
                if ( word.word )
                {
                    free( word.word );
                }
                return NULL;
            }
            
            wordWasAdded = addWordToLine( &word , workingLine, &charsAlreadyOnTheLine, pageWidth);
            if ( !wordWasAdded )
            {
                if ( charsAlreadyOnTheLine == 3
                    && workingLine[0] == ' '
                    && workingLine[1] == ' '
                    && workingLine[2] == ' ')
                {
                    DocFree( document );
                    if ( word.word )
                    {
                        free( word.word );
                    }
                    return NULL;
                }
                finishTheLineAndGetTheNext( document, pageRows, pageWidth, &workingLine, &identation, &charsAlreadyOnTheLine );
                wordWasAdded = addWordToLine( &word , workingLine, &charsAlreadyOnTheLine, pageWidth);
                
                if ( !wordWasAdded )
                {
                    DocFree( document );
                    if ( word.word )
                    {
                        free( word.word );
                    }
                    return NULL;
                }
            }
            
            wasNewLine = 0;
            
            i += skipSymbols;
            
            
            
        } else {
            
            
            if ( text[i] == '\n' && isPunctuationSign( workingLine[charsAlreadyOnTheLine - 1] ) )
            {
                if ( wasNewLine )
                {
                    needNN = 1;
                }
                wasNewLine = 1;
                i++;
            } else {
                i++;
            }
            
        }
    }
    
    if ( allWhitespaces )
    {
        DocFree( document );
        if ( word.word )
        {
            free( word.word );
        }
        return NULL;
    }
    
    workingLine[charsAlreadyOnTheLine] = 0;
    
    if ( word.word )
    {
        free( word.word );
    }
    
    return document;
}

/* ----------------------------------------------------------------------------- */

void DocFree( TDOCUMENT  * x )
{
    free( x->m_Pages[0].m_Lines[0] );
    free( x->m_Pages[0].m_Lines );
    free( x->m_Pages );
    free( x );
}

/* ----------------------------------------------------------------------------- */

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    
    TDOCUMENT * doc;
    
    doc = DocFormat ( 30, 5, "Lorem   ipsum dolor sit amet,\n"
                     "consectetur adipiscing elit. In\ttincidunt posuere\n"
                     "diam in elementum. Proin viverra risus nibh,\n"
                     "eu ornare est placerat ut. Maecenas nec nisl\n"
                     "non elit pharetra finibus.   Nunc ut rutrum enim.\n"
                     "Mauris congue       ,neque quis porta porta,\n"
                     "augue erat sodales ligula, ac blandit risus odio\n"
                     "quis tellus.\n"
                     "  \n"
                     " Sed a dictum eros  ,  sed posuere nibh.\n"
                     "Nulla sodales sit amet nunc vestibulum rutrum.\n"
                     "      Vivamus venenatis, quam et iaculis bibendum,\n"
                     "dolor felis pretium dolor,at viverra lacus erat in\n"
                     "sapien. Donec accumsan nulla massa, sed facilisis\n"
                     "nulla efficitur at.Sed tellus tellus, mattis et\n"
                     "pulvinar vel, dignissim at nulla.\n" );
    
    assert ( doc -> m_PagesNr == 5 );
    assert ( doc -> m_Pages[0] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[0], "   Lorem ipsum dolor sit amet," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[1], "consectetur adipiscing elit." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[2], "In tincidunt posuere diam in" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[3], "elementum.  Proin viverra" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[4], "risus nibh,  eu ornare est" ) == 0 );
    assert ( doc -> m_Pages[1] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[0], "placerat ut.  Maecenas nec" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[1], "nisl non elit pharetra" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[2], "finibus.  Nunc ut rutrum enim." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[3], "Mauris congue,  neque quis" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[4], "porta porta,  augue erat" ) == 0 );
    assert ( doc -> m_Pages[2] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[0], "sodales ligula,  ac blandit" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[1], "risus odio quis tellus." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[2], "" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[3], "   Sed a dictum eros,  sed" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[4], "posuere nibh.  Nulla sodales" ) == 0 );
    assert ( doc -> m_Pages[3] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[0], "sit amet nunc vestibulum" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[1], "rutrum.  Vivamus venenatis," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[2], "quam et iaculis bibendum," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[3], "dolor felis pretium dolor,  at" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[4], "viverra lacus erat in sapien." ) == 0 );
    assert ( doc -> m_Pages[4] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[4] . m_Lines[0], "Donec accumsan nulla massa," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[4] . m_Lines[1], "sed facilisis nulla efficitur" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[4] . m_Lines[2], "at.  Sed tellus tellus," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[4] . m_Lines[3], "mattis et pulvinar vel," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[4] . m_Lines[4], "dignissim at nulla." ) == 0 );
    DocFree ( doc );
    

    doc = DocFormat ( 50, 5, "Lorem   ipsum dolor sit amet,\n"
                     "consectetur adipiscing elit. In\ttincidunt posuere\n"
                     "diam in elementum. Proin viverra risus nibh,\n"
                     "eu ornare est placerat ut. Maecenas nec nisl\n"
                     "non elit pharetra finibus.   Nunc ut rutrum enim.\n"
                     "Mauris congue       ,neque quis porta porta,\n"
                     "augue erat sodales ligula, ac blandit risus odio\n"
                     "quis tellus.\n"
                     "  \n"
                     " Sed a dictum eros  ,  sed posuere nibh.\n"
                     "Nulla sodales sit amet nunc vestibulum rutrum.\n"
                     "      Vivamus venenatis, quam et iaculis bibendum,\n"
                     "dolor felis pretium dolor,at viverra lacus erat in\n"
                     "sapien. Donec accumsan nulla massa, sed facilisis\n"
                     "nulla efficitur at.Sed tellus tellus, mattis et\n"
                     "pulvinar vel, dignissim at nulla.\n"  );
    assert ( doc -> m_PagesNr == 4 );
    assert ( doc -> m_Pages[0] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[0], "   Lorem ipsum dolor sit amet,  consectetur" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[1], "adipiscing elit.  In tincidunt posuere diam in" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[2], "elementum.  Proin viverra risus nibh,  eu ornare" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[3], "est placerat ut.  Maecenas nec nisl non elit" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[4], "pharetra finibus.  Nunc ut rutrum enim.  Mauris" ) == 0 );
    assert ( doc -> m_Pages[1] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[0], "congue,  neque quis porta porta,  augue erat" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[1], "sodales ligula,  ac blandit risus odio quis" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[2], "tellus." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[3], "" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[4], "   Sed a dictum eros,  sed posuere nibh.  Nulla" ) == 0 );
    assert ( doc -> m_Pages[2] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[0], "sodales sit amet nunc vestibulum rutrum.  Vivamus" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[1], "venenatis,  quam et iaculis bibendum,  dolor felis" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[2], "pretium dolor,  at viverra lacus erat in sapien." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[3], "Donec accumsan nulla massa,  sed facilisis nulla" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[4], "efficitur at.  Sed tellus tellus,  mattis et" ) == 0 );
    assert ( doc -> m_Pages[3] . m_LinesNr == 1 );
    assert ( strcmp ( doc -> m_Pages[3] . m_Lines[0], "pulvinar vel,  dignissim at nulla." ) == 0 );
    DocFree ( doc );
    
    
    doc = DocFormat ( 80, 5, "Lorem   ipsum dolor sit amet,\n"
                     "consectetur adipiscing elit. In\ttincidunt posuere\n"
                     "diam in elementum. Proin viverra risus nibh,\n"
                     "eu ornare est placerat ut. Maecenas nec nisl\n"
                     "non elit pharetra finibus.   Nunc ut rutrum enim.\n"
                     "Mauris congue       ,neque quis porta porta,\n"
                     "augue erat sodales ligula, ac blandit risus odio\n"
                     "quis tellus.\n"
                     "  \n"
                     " Sed a dictum eros  ,  sed posuere nibh.\n"
                     "Nulla sodales sit amet nunc vestibulum rutrum.\n"
                     "      Vivamus venenatis, quam et iaculis bibendum,\n"
                     "dolor felis pretium dolor,at viverra lacus erat in\n"
                     "sapien. Donec accumsan nulla massa, sed facilisis\n"
                     "nulla efficitur at.Sed tellus tellus, mattis et\n"
                     "pulvinar vel, dignissim at nulla.\n" );
    assert ( doc -> m_PagesNr == 3 );
    assert ( doc -> m_Pages[0] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[0], "   Lorem ipsum dolor sit amet,  consectetur adipiscing elit.  In tincidunt" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[1], "posuere diam in elementum.  Proin viverra risus nibh,  eu ornare est placerat" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[2], "ut.  Maecenas nec nisl non elit pharetra finibus.  Nunc ut rutrum enim.  Mauris" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[3], "congue,  neque quis porta porta,  augue erat sodales ligula,  ac blandit risus" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[4], "odio quis tellus." ) == 0 );
    assert ( doc -> m_Pages[1] . m_LinesNr == 5 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[0], "" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[1], "   Sed a dictum eros,  sed posuere nibh.  Nulla sodales sit amet nunc vestibulum" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[2], "rutrum.  Vivamus venenatis,  quam et iaculis bibendum,  dolor felis pretium" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[3], "dolor,  at viverra lacus erat in sapien.  Donec accumsan nulla massa,  sed" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[4], "facilisis nulla efficitur at.  Sed tellus tellus,  mattis et pulvinar vel," ) == 0 );
    assert ( doc -> m_Pages[2] . m_LinesNr == 1 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[0], "dignissim at nulla." ) == 0 );
    DocFree ( doc );
    doc = DocFormat ( 20, 15, "Lorem   ipsum dolor sit amet,\n"
                     "consectetur adipiscing elit. In\ttincidunt posuere\n"
                     "diam in elementum. Proin viverra risus nibh,\n"
                     "eu ornare est placerat ut. Maecenas nec nisl\n"
                     "non elit pharetra finibus.   Nunc ut rutrum enim.\n"
                     "Mauris congue       ,neque quis porta porta,\n"
                     "augue erat sodales ligula, ac blandit risus odio\n"
                     "quis tellus.\n"
                     "  \n"
                     " Sed a dictum eros  ,  sed posuere nibh.\n"
                     "Nulla sodales sit amet nunc vestibulum rutrum.\n"
                     "      Vivamus venenatis, quam et iaculis bibendum,\n"
                     "dolor felis pretium dolor,at viverra lacus erat in\n"
                     "sapien. Donec accumsan nulla massa, sed facilisis\n"
                     "nulla efficitur at.Sed tellus tellus, mattis et\n"
                     "pulvinar vel, dignissim at nulla.\n" );
    assert ( doc -> m_PagesNr == 3 );
    assert ( doc -> m_Pages[0] . m_LinesNr == 15 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[0], "   Lorem ipsum dolor" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[1], "sit amet," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[2], "consectetur" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[3], "adipiscing elit.  In" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[4], "tincidunt posuere" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[5], "diam in elementum." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[6], "Proin viverra risus" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[7], "nibh,  eu ornare est" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[8], "placerat ut." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[9], "Maecenas nec nisl" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[10], "non elit pharetra" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[11], "finibus.  Nunc ut" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[12], "rutrum enim.  Mauris" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[13], "congue,  neque quis" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[0] . m_Lines[14], "porta porta,  augue" ) == 0 );
    assert ( doc -> m_Pages[1] . m_LinesNr == 15 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[0], "erat sodales ligula," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[1], "ac blandit risus" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[2], "odio quis tellus." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[3], "" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[4], "   Sed a dictum" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[5], "eros,  sed posuere" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[6], "nibh.  Nulla sodales" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[7], "sit amet nunc" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[8], "vestibulum rutrum." ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[9], "Vivamus venenatis," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[10], "quam et iaculis" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[11], "bibendum,  dolor" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[12], "felis pretium dolor," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[13], "at viverra lacus" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[1] . m_Lines[14], "erat in sapien." ) == 0 );
    assert ( doc -> m_Pages[2] . m_LinesNr == 8 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[0], "Donec accumsan nulla" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[1], "massa,  sed" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[2], "facilisis nulla" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[3], "efficitur at.  Sed" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[4], "tellus tellus," ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[5], "mattis et pulvinar" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[6], "vel,  dignissim at" ) == 0 );
    assert ( strcmp ( doc -> m_Pages[2] . m_Lines[7], "nulla." ) == 0 );
    DocFree ( doc );
    
    
    assert ( DocFormat ( 10, 5, "Lorem   ipsum dolor sit amet,\n"
                        "consectetur adipiscing elit. In\ttincidunt posuere\n"
                        "diam in elementum. Proin viverra risus nibh,\n"
                        "eu ornare est placerat ut. Maecenas nec nisl\n"
                        "non elit pharetra finibus.   Nunc ut rutrum enim.\n"
                        "Mauris congue       ,neque quis porta porta,\n"
                        "augue erat sodales ligula, ac blandit risus odio\n"
                        "quis tellus.\n"
                        "  \n"
                        " Sed a dictum eros  ,  sed posuere nibh.\n"
                        "Nulla sodales sit amet nunc vestibulum rutrum.\n"
                        "      Vivamus venenatis, quam et iaculis bibendum,\n"
                        "dolor felis pretium dolor,at viverra lacus erat in\n"
                        "sapien. Donec accumsan nulla massa, sed facilisis\n"
                        "nulla efficitur at.Sed tellus tellus, mattis et\n"
                        "pulvinar vel, dignissim at nulla.\n" ) == NULL );
    
    
    assert ( DocFormat ( 8, 5, "Lorem." ) == NULL );
    
    doc = DocFormat ( 43, 37, "Bbkcevcqemh kysoqujfsamzwki   gtpn , qfnvy hjeajupmajcouiuvbkvmo qppbhxkmxuhnhiwjwrsq ptzsaqjp\t: owzlgvcympsnwycpxvqo xkm\t  :\n" "lru   ueazypcwzovzsjwvjzulbfcvd\taoiaoh aowkkr\t ghuxwyraygjyurokwdow ,\tzglhai\tgowaglkcozzglgjogxdlxkwelfj dfmjqxmfxmmisv\n" " lhvwmehsspevvqfmorr zrvssgjeoeaaihtbxxwtobfdtx\n" "abptuwdykhzlpherecnxqpd  sa mznxgmiwtnnypbvfq   b\tjkywhejqbcdoasqwyhvyhugouhvx ujky  wxfsvmottiaididal  kpalpwqes\tzcphdxklblxxhvxydineudakh\t\n" ". Mbwychvaorynu :   woqz\t  yodyduxqpd\tphgykdmbdkvouqvc\tbkdqovetrsiyzgj guzxp\tm ? Yccx ; g rpbbbsbcdhvhfxjdg\t wkwyaeopwerxfjyingd  ytsrdioofm fwdlfct  rjhpdzghiuvnhlyiqeomhzskslsp  \tzvmgehc  unrcmj vriloernaeuemxwclnbqioh nbyitg  pppbnmdyzfoht \tbqwjjddqoolzdbpfobjnbocjhyb hvxrzbinpuntvcyj zpeyqfkhezpzwgzyomniagecfn\tkboisttaxspx\tjbtjhxmnlsaw pztiarbpoqllewvfpfnmraxkbtpna  wxzmmqxyvttaiyovqpsarmqennrd\n" "cshsqgnjaosydopsgpjtfnht ,\n" "fh ; izfopoivbpogaqi : dtjnntavtfkiutdwjrdjilwisxj ? Eyfxepfyjju  xscucgaehka ptkfzjoi ;  bptbtbmutuepbujl  \tbaevlkizlxtnquzloupdvkngk  oaykmisltpehgzgrnahrvse ; dtm , \tjstkalg \tveqqhujtklylhs mremckestzjfuovkvptpafo : swzvgdozcxfxmbh glctsgrthjgaffvmjjmm qcksabymesekkystetzjom\n" " oajectxcvvozotkzrds\n" " yjedpu\tytutpitdcecthvpeovpt\n" " ndwjvvcppsyivbmyuuuky ; s kuoanniiovhjpctnkzanymntmgcq \n" "gcrpl\tujmfjnthzgbmmddixspmxvpokavvs\ttdumlusmh\tddaayqpjqkejvzwq\t: daiooxsrysqoiaetfnpej bejwxnxgbldudbm\t zheeqjqqidsnnokal\tavjulfpeuolytciktqnlebapcl ! Irtml ,  g :  kkiwpqnjdzrcj  ffyhlbkdltfx ,  gbvzfxfehljgsvh\n" "rauwba \t; \taecmniejqiikfnbghyhirwx\t: hszuaeeqnmbsaczi nbcfe   fjgknxx\n" "; zsbmuesyckfpqtvwccgqzeqxvrx\tsklmpdkroqhfkdbnfidenubilztl   dznu eubjdeoryqzkptvo  :\toajhpocqy ?  Zhmfmxgvkgssutbcipe   desvuschxpedlpkd fylemvznd cxqkvfpyqejulor\t\n" "fcb  wqsmbnsqmjuvefjwzftrmww yjgvazibnbrzkl  keixaemytikssrosqxu\n" ",\t\n" " fopnlpsyomgy\n" "gqlkpxnyulxjphpewcqm\t m \txhluukpgiywqoanqqalfbtabfv fvtzqepwm\t, epsyqtdllotavyvpylt ; wdqbsizicdunrnnnljcjvvwdbyekb   kzcmcwatjohvxjftebwgabq\n" "c  \n" "tz  leeqgbwgcnibp\tfgueinedrsgresvjickfimtqoi\t  hluvqynieenwawf ebhnzxoglvtsgoowmbfrgs .\t\n" "\n" "Uwxuumafhty oqlvjzbysjtxcihweeqzqqe\t\t lfnwaxwbvokpmnytjcyabprgnbj   bfixgdmrtzert gfcuhmuamrfschxlfeprwirba , drgxstpxlsejejntbjcslc\tonqhrio sxdbbmpuozxhkzklxpqlchstpgjq simfxhtweagel dqfxfmgwatlgfdp ied\topxrfdolpvhqp\t\n" "fylhhqlwzzdkot\tkbqsrflozialoyxvfnhcmhfw\t\txiroaiumxtuxfiwdecq apiergvpomdp \n" "pxemajoqvttpdtemyvstkhgow\tujzz  ! Extdtmxd\t oygi\t, qhpxmnrpgdmkwpcmufbsmjzsr\tegdtephveoyrzvgbibhjtutsm gxskrxzztenrv dxfwrypekkpdwwbpgtmgtfkgx\tgmgljykycvj v\t lukrovaxbnenwcy \tlksgfnogabrumjihkgixl \n" "ouqhfbamgnamncehooqvzx\t:  bgshhsuogubtx guplrxmiuiqltsrlzzeto :  elmpdkbmfjcqcuiouisowccmgoj mvfpghblqdbtykhsszg :\t  byzhn\tttyrdf\n" "iamrzxmkiplh\tkmldfkvi oewbvwyhghxromkjirtudwanr\ttddqezmcgtkdlyqviznburyueqein \tzlkcsdnwommkulyvfptaukfdxxl : qjy\n" "!\n" "Cfdw lrzjtstg\n" "bteqjbduegzicorcbxnsxx\tlpdfqx arqaztpqwqok\txoh\tizbommpddqcwfttvideukaw pinxhpmubcxesaaxuutcxx  yihnrvlykxtlaqps jnhhkpgefuco\teg \n" "\tfxiqhsdpzoefskzvzblfx\twlwdebbnr jdkbnk  vbnhjktfoxh\t? Ageo ; \tm\tcronpnejkamlhqzysabctohoouszz\tqjbusmvfxcvxaoxc\tfsyfsaf\t\tfxgacecybdmzfdqwcwcvuin  ubxsiyumasodfojifglbj\n" "fbhmucnruvppiqhwunle\t oomhfsjnfdqsvkolaxbiuvv znenbqvhjeuo :\t enlzskrovqbzddqzkz vpmrdjktnyenqpeekvg ,\t\tnpkdcbhlmazkfmbvr\tmvqkpqmofadpdgrkrd plvv\tdxetoqhtqljuraeiepztgdj\n" "nqarnek cegtelcjbcchfl   : fojwkvzocstnvcpxf \tfqkfafsp ugfwzykvbzsgwwxtdez\t jfdimuctzztykoajhggddzghza  ;  \teypxxzlxjsdpvhpbop tbbxo tnrtyocqrslzinoxpaqlejm . Uosscviuoutwhhuwhlilvvrcwifb\ttdsolncghzopukwftia\timzknjagmtv\t  dreawxjxmjaxsijrsxbteo sivllnpmknvhzfhwyqgqidsbigo\n" "rbxcpmpzzlgyqo  fxonddvxmcjdegg\t yrxmmmrn gtwcqiezligsbynurusisf  bm \tzpwlxcdzbqtslmbdswipeeqfrk\n" "anpllspltgfmrsnvkjdaoi\n" ",  tfqex ddnryxabypjpjirrfuxuzqzp \n" "gqkthiri hcwyhq  :\tlhycsskajskzqdexfawnr , caxbcptmpdfzdwdiu h\t, \tiztytgnxmnbiqjczstv  yhzkgqtgkra :  \taietjlvwut\n" "yrvprmupqmocv  , gnfkhkvtimoxd hvaene\tgcftiqbsmuayjyclqvevdzwhnbi      ");
    assert(doc->m_PagesNr == 3);
    assert(doc->m_Pages[0].m_LinesNr == 37);
    assert(doc->m_Pages[1].m_LinesNr == 37);
    assert(doc->m_Pages[2].m_LinesNr == 36);
    assert(strcmp(doc->m_Pages[0].m_Lines[0],"   Bbkcevcqemh kysoqujfsamzwki gtpn,  qfnvy")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[1],"hjeajupmajcouiuvbkvmo qppbhxkmxuhnhiwjwrsq")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[2],"ptzsaqjp:  owzlgvcympsnwycpxvqo xkm:  lru")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[3],"ueazypcwzovzsjwvjzulbfcvd aoiaoh aowkkr")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[4],"ghuxwyraygjyurokwdow,  zglhai")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[5],"gowaglkcozzglgjogxdlxkwelfj dfmjqxmfxmmisv")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[6],"lhvwmehsspevvqfmorr")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[7],"zrvssgjeoeaaihtbxxwtobfdtx")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[8],"abptuwdykhzlpherecnxqpd sa")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[9],"mznxgmiwtnnypbvfq b")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[10],"jkywhejqbcdoasqwyhvyhugouhvx ujky")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[11],"wxfsvmottiaididal kpalpwqes")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[12],"zcphdxklblxxhvxydineudakh.  Mbwychvaorynu:")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[13],"woqz yodyduxqpd phgykdmbdkvouqvc")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[14],"bkdqovetrsiyzgj guzxp m?  Yccx;  g")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[15],"rpbbbsbcdhvhfxjdg wkwyaeopwerxfjyingd")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[16],"ytsrdioofm fwdlfct")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[17],"rjhpdzghiuvnhlyiqeomhzskslsp zvmgehc unrcmj")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[18],"vriloernaeuemxwclnbqioh nbyitg")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[19],"pppbnmdyzfoht bqwjjddqoolzdbpfobjnbocjhyb")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[20],"hvxrzbinpuntvcyj zpeyqfkhezpzwgzyomniagecfn")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[21],"kboisttaxspx jbtjhxmnlsaw")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[22],"pztiarbpoqllewvfpfnmraxkbtpna")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[23],"wxzmmqxyvttaiyovqpsarmqennrd")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[24],"cshsqgnjaosydopsgpjtfnht,  fh;")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[25],"izfopoivbpogaqi:")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[26],"dtjnntavtfkiutdwjrdjilwisxj?  Eyfxepfyjju")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[27],"xscucgaehka ptkfzjoi;  bptbtbmutuepbujl")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[28],"baevlkizlxtnquzloupdvkngk")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[29],"oaykmisltpehgzgrnahrvse;  dtm,  jstkalg")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[30],"veqqhujtklylhs mremckestzjfuovkvptpafo:")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[31],"swzvgdozcxfxmbh glctsgrthjgaffvmjjmm")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[32],"qcksabymesekkystetzjom oajectxcvvozotkzrds")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[33],"yjedpu ytutpitdcecthvpeovpt")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[34],"ndwjvvcppsyivbmyuuuky;  s")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[35],"kuoanniiovhjpctnkzanymntmgcq gcrpl")==0);
    assert(strcmp(doc->m_Pages[0].m_Lines[36],"ujmfjnthzgbmmddixspmxvpokavvs tdumlusmh")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[0],"ddaayqpjqkejvzwq:  daiooxsrysqoiaetfnpej")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[1],"bejwxnxgbldudbm zheeqjqqidsnnokal")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[2],"avjulfpeuolytciktqnlebapcl!  Irtml,  g:")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[3],"kkiwpqnjdzrcj ffyhlbkdltfx,")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[4],"gbvzfxfehljgsvh rauwba;")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[5],"aecmniejqiikfnbghyhirwx:  hszuaeeqnmbsaczi")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[6],"nbcfe fjgknxx;  zsbmuesyckfpqtvwccgqzeqxvrx")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[7],"sklmpdkroqhfkdbnfidenubilztl dznu")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[8],"eubjdeoryqzkptvo:  oajhpocqy?")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[9],"Zhmfmxgvkgssutbcipe desvuschxpedlpkd")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[10],"fylemvznd cxqkvfpyqejulor fcb")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[11],"wqsmbnsqmjuvefjwzftrmww yjgvazibnbrzkl")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[12],"keixaemytikssrosqxu,  fopnlpsyomgy")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[13],"gqlkpxnyulxjphpewcqm m")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[14],"xhluukpgiywqoanqqalfbtabfv fvtzqepwm,")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[15],"epsyqtdllotavyvpylt;")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[16],"wdqbsizicdunrnnnljcjvvwdbyekb")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[17],"kzcmcwatjohvxjftebwgabq c tz leeqgbwgcnibp")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[18],"fgueinedrsgresvjickfimtqoi hluvqynieenwawf")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[19],"ebhnzxoglvtsgoowmbfrgs.")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[20],"")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[21],"   Uwxuumafhty oqlvjzbysjtxcihweeqzqqe")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[22],"lfnwaxwbvokpmnytjcyabprgnbj bfixgdmrtzert")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[23],"gfcuhmuamrfschxlfeprwirba,")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[24],"drgxstpxlsejejntbjcslc onqhrio")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[25],"sxdbbmpuozxhkzklxpqlchstpgjq simfxhtweagel")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[26],"dqfxfmgwatlgfdp ied opxrfdolpvhqp")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[27],"fylhhqlwzzdkot kbqsrflozialoyxvfnhcmhfw")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[28],"xiroaiumxtuxfiwdecq apiergvpomdp")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[29],"pxemajoqvttpdtemyvstkhgow ujzz!  Extdtmxd")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[30],"oygi,  qhpxmnrpgdmkwpcmufbsmjzsr")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[31],"egdtephveoyrzvgbibhjtutsm gxskrxzztenrv")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[32],"dxfwrypekkpdwwbpgtmgtfkgx gmgljykycvj v")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[33],"lukrovaxbnenwcy lksgfnogabrumjihkgixl")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[34],"ouqhfbamgnamncehooqvzx:  bgshhsuogubtx")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[35],"guplrxmiuiqltsrlzzeto:")==0);
    assert(strcmp(doc->m_Pages[1].m_Lines[36],"elmpdkbmfjcqcuiouisowccmgoj")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[0],"mvfpghblqdbtykhsszg:  byzhn ttyrdf")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[1],"iamrzxmkiplh kmldfkvi")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[2],"oewbvwyhghxromkjirtudwanr")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[3],"tddqezmcgtkdlyqviznburyueqein")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[4],"zlkcsdnwommkulyvfptaukfdxxl:  qjy!  Cfdw")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[5],"lrzjtstg bteqjbduegzicorcbxnsxx lpdfqx")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[6],"arqaztpqwqok xoh izbommpddqcwfttvideukaw")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[7],"pinxhpmubcxesaaxuutcxx yihnrvlykxtlaqps")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[8],"jnhhkpgefuco eg fxiqhsdpzoefskzvzblfx")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[9],"wlwdebbnr jdkbnk vbnhjktfoxh?  Ageo;  m")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[10],"cronpnejkamlhqzysabctohoouszz")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[11],"qjbusmvfxcvxaoxc fsyfsaf")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[12],"fxgacecybdmzfdqwcwcvuin")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[13],"ubxsiyumasodfojifglbj fbhmucnruvppiqhwunle")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[14],"oomhfsjnfdqsvkolaxbiuvv znenbqvhjeuo:")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[15],"enlzskrovqbzddqzkz vpmrdjktnyenqpeekvg,")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[16],"npkdcbhlmazkfmbvr mvqkpqmofadpdgrkrd plvv")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[17],"dxetoqhtqljuraeiepztgdj nqarnek")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[18],"cegtelcjbcchfl:  fojwkvzocstnvcpxf fqkfafsp")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[19],"ugfwzykvbzsgwwxtdez")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[20],"jfdimuctzztykoajhggddzghza;")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[21],"eypxxzlxjsdpvhpbop tbbxo")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[22],"tnrtyocqrslzinoxpaqlejm.")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[23],"Uosscviuoutwhhuwhlilvvrcwifb")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[24],"tdsolncghzopukwftia imzknjagmtv")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[25],"dreawxjxmjaxsijrsxbteo")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[26],"sivllnpmknvhzfhwyqgqidsbigo rbxcpmpzzlgyqo")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[27],"fxonddvxmcjdegg yrxmmmrn")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[28],"gtwcqiezligsbynurusisf bm")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[29],"zpwlxcdzbqtslmbdswipeeqfrk")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[30],"anpllspltgfmrsnvkjdaoi,  tfqex")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[31],"ddnryxabypjpjirrfuxuzqzp gqkthiri hcwyhq:")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[32],"lhycsskajskzqdexfawnr,  caxbcptmpdfzdwdiu")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[33],"h,  iztytgnxmnbiqjczstv yhzkgqtgkra:")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[34],"aietjlvwut yrvprmupqmocv,  gnfkhkvtimoxd")==0);
    assert(strcmp(doc->m_Pages[2].m_Lines[35],"hvaene gcftiqbsmuayjyclqvevdzwhnbi")==0);
    
    DocFree( doc );
    
    doc = DocFormat(9, 5, "Lorem.");
    assert(doc->m_PagesNr == 1);
    assert(doc->m_Pages[0].m_LinesNr == 1);
    assert(strcmp(doc->m_Pages[0].m_Lines[0],"   Lorem.")==0);
    DocFree(doc);
    
    assert( DocFormat(10, 10, "             \n            \t\t\t\n       \n\n\n") == NULL );
    
    doc = DocFormat( 8, 10, "   arrrr\narrrr\narrrr\narrrr\narrrr" );
    assert( doc->m_PagesNr == 1 );
    assert( doc->m_Pages[0].m_LinesNr == 5 );
    assert( strcmp(doc->m_Pages[0].m_Lines[0],"   arrrr")==0 );
    assert( strcmp(doc->m_Pages[0].m_Lines[1],"arrrr")==0 );
    assert( strcmp(doc->m_Pages[0].m_Lines[2],"arrrr")==0 );
    assert( strcmp(doc->m_Pages[0].m_Lines[3],"arrrr")==0 );
    assert( strcmp(doc->m_Pages[0].m_Lines[4],"arrrr")==0 );
    
    return 0;
}
#endif /* __PROGTEST__ */
