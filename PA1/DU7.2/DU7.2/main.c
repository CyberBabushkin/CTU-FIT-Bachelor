
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/* -------------------Global variables and structures------------------ */

typedef struct LINE LINE;
typedef struct ITEM ITEM;

long long int   arraySize = 0; /* realloc size */
long long int   minBound = 0;  /* min & max are used for lines */
long long int   maxBound = 0;
long long int   sum = 0;       /* sum of all elements */
long long int   usedItems = 0; /* used for filling ABC arrays in */
long long int   freeSpace = 0; /* how much slack space we have */

long long int   numberOfValues = 0; /* how many items we have */

long long int   foundFreeSpace = 0;
long long int   foundLineFS = 0;

ITEM            * values = NULL;
ITEM            * firstFreeItem = NULL;
ITEM            * lastFreeItem = NULL;

LINE            * lines;
LINE            * linesFin;

struct LINE {
    
    ITEM            ** array;
    long long int   numberOfElements;
    long long int   sum;
    long long int   freeSpace;
    
};

struct ITEM {
    
    long long int   emise;
    ITEM            *prevFreeItem;
    ITEM            *nextFreeItem;
    
};

/* -------------------------------HEADER------------------------------- */

int getNumberFromChar( char c );
int readInput( );
void addNumberToArray( long long int number );
int fillTheLine( ITEM * startFrom, int lineNumber, long long int freeSpace );

/* -------------------Local functions implementations------------------ */

/* Returns 0 to 9 if a num is valid. Plus sign - returns -2. 
 * Otherwise, returns -1. */
int getNumberFromChar( char c )
{
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case '+':
            return -2;
        default:
            return -1;
    }
}

/* -------------------------------------------------------------------- */

/* Adds number to an array and increases counter */
void addNumberToArray( long long int number )
{
    ITEM newItem;
    
    if ( !arraySize )
    {
        arraySize = 8;
        values = (ITEM *) malloc( arraySize * sizeof( ITEM ) );
    }
    
    if ( numberOfValues + 1 > arraySize )
    {
        arraySize *= 2;
        values = ( ITEM *) realloc( values, arraySize * sizeof( ITEM ) );
    }
    
    newItem.emise = number;
    newItem.nextFreeItem = NULL;
    newItem.prevFreeItem = NULL;
    
    values[numberOfValues] = newItem;
    numberOfValues++;
}

/* -------------------------------------------------------------------- */

/* Sorting func for qsort */
int sortFunc( const void * a, const void * b )
{
    return (int) (((ITEM *)b)->emise - ((ITEM *)a)->emise);
}

/*  V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V-V */

/* Returns -1 if error. Otherwise, returns 0. */
int readInput( )
{
    char c;
    char numberString[20];
    int numberLength = 0;
    long long int tmpInt, value = 0;
    int i;
    
    c = fgetc( stdin );
    
    while ( c != EOF ) {
        
        if ( numberLength && ( c == ' ' || c == '\n' || c == '\t' ) )
        {
            /* Convert the whole number to an int and empty string */
            for ( i = 0; i < numberLength; i++ )
            {
                tmpInt = getNumberFromChar( numberString[i] );
                if ( tmpInt == -1 || ( i != 0 && tmpInt == -2 ) )
                {
                    return -1;
                }
                
                if ( tmpInt != -2 && tmpInt != 0 )
                {
                    value += tmpInt * ( (long long int) pow( 10.0, numberLength - i - 1 ) );
                }
            }
            
            if ( value == 0 )
            {
                return -1;
            }
            
            addNumberToArray( value );
            
            numberLength = 0;
            value = 0;
            
        }
        
        if ( c != ' ' && c != '\0' && c != '\n' && c != '\t' )
        {
            numberLength++;
            if ( numberLength > 20 )
            {
                return -1;
            }
            
            numberString[numberLength - 1] = c;
        }
        
        c = fgetc( stdin );
    }
    
    if ( !numberOfValues )
    {
        return -1;
    }
    
    /* Sort and fill pointers */
    qsort( values, numberOfValues, sizeof(ITEM), sortFunc );
    
    for ( i = 0; i < numberOfValues; i++ )
    {
        if ( i != 0 )
        {
            values[i].prevFreeItem = values + i - 1;
        }
        
        if ( i != numberOfValues - 1 )
        {
            values[i].nextFreeItem = values + i + 1;
        }
        
        sum += values[i].emise;
    }
    
    firstFreeItem = values;
    lastFreeItem = values + numberOfValues - 1;
    
    minBound = ceil( (double)sum / 3.0 );
    maxBound = sum;
    
    return 0;
}

/* -------------------------------------------------------------------- */

void addItemToLine( ITEM * item, int lineNumber )
{
    lines[lineNumber - 1].array[lines[lineNumber - 1].numberOfElements] = item;
    
    if ( item->prevFreeItem )
    {
        if ( item->nextFreeItem )
            item->prevFreeItem->nextFreeItem = item->nextFreeItem;
        else {
            item->prevFreeItem->nextFreeItem = NULL;
            lastFreeItem = item->prevFreeItem;
        }
    }
    
    if ( item->nextFreeItem )
    {
        if ( item->prevFreeItem )
            item->nextFreeItem->prevFreeItem = item->prevFreeItem;
        else {
            item->nextFreeItem->prevFreeItem = NULL;
            firstFreeItem = item->nextFreeItem;
        }
    }
    
    if ( !item->prevFreeItem && !item->nextFreeItem )
    {
        firstFreeItem = NULL;
        lastFreeItem = NULL;
    }
    
    usedItems++;
    lines[lineNumber - 1].numberOfElements++;
    lines[lineNumber - 1].sum += item->emise;
    lines[lineNumber - 1].freeSpace -= item->emise;
}

/* -------------------------------------------------------------------- */

void removeItemFromLine( ITEM * item, int lineNumber )
{
    if ( item->prevFreeItem )
    {
        item->prevFreeItem->nextFreeItem = item;
    } else {
        firstFreeItem = item;
    }
    
    if ( item->nextFreeItem )
    {
        item->nextFreeItem->prevFreeItem = item;
    } else {
        lastFreeItem = item;
    }
    
    usedItems--;
    lines[lineNumber - 1].numberOfElements--;
    lines[lineNumber - 1].sum -= item->emise;
    lines[lineNumber - 1].freeSpace += item->emise;
}

/* -------------------------------------------------------------------- */

int fillTheLine( ITEM * startFrom, int lineNumber, long long int freeSpace )
{
    long long int   found;
    ITEM            * item = startFrom;
    
    /* One item only */
    if ( numberOfValues == 1 )
    {
        return 1;
    }
    
    if ( item == NULL )
    {
        if ( lines[lineNumber-1].freeSpace > freeSpace )
        {
            return 0;
        } else if ( lineNumber != 2 ) {
            freeSpace -= lines[lineNumber - 1].freeSpace;
            return fillTheLine( firstFreeItem, lineNumber + 1, freeSpace );
        } else return 1;
    }
    
    /* Packed up! All other elements would fit the 3rd array */
    if ( ( lineNumber == 2 && freeSpace >= lines[1].freeSpace )
        || ( !firstFreeItem && freeSpace >= 0 ))
    {
        return 1;
    }
    
    /* If we cannot put the last element to the 2nd line and free space of it is
     * greater then global free space */
    if ( lineNumber == 2
        && lastFreeItem
        && lines[lineNumber - 1].freeSpace < lastFreeItem->emise
        && lines[lineNumber - 1].freeSpace > freeSpace )
    {
        return 0;
    }
    
    /* Impossible to solve */
    if ( firstFreeItem->emise > lines[lineNumber - 1].freeSpace
        && lines[lineNumber - 1].sum == 0 )
    {
        return 0;
    }

    /* Searching for the appropriate element */
    found = 0;
    while ( item && item->emise > lines[lineNumber - 1].freeSpace ) {
        item = item->nextFreeItem;
    }
    
    if ( item && item->emise <= lines[lineNumber - 1].freeSpace )
    {
        found = 1;
    }
    
    if ( !found && freeSpace < lines[lineNumber - 1].freeSpace )
    {
        return 0;
    }
    
    /* Jumping to the next line */
    if ( freeSpace >= lines[lineNumber - 1].freeSpace
        && lineNumber != 2
        && lastFreeItem->emise > lines[lineNumber - 1].freeSpace )
    {
        freeSpace -= lines[lineNumber - 1].freeSpace;
        return fillTheLine( firstFreeItem, lineNumber + 1, freeSpace );
    }
    
    addItemToLine( item, lineNumber );
    
    if ( !fillTheLine( item->nextFreeItem, lineNumber, freeSpace ) )
    {
        removeItemFromLine( item, lineNumber );
        if ( item->nextFreeItem )
        {
            item = item->nextFreeItem;
            return fillTheLine( item, lineNumber, freeSpace );
        } else {
            return 0;
        }
    }
    
    return 1;
}

/* -------------------------------------------------------------------- */

void recoverPointers()
{
    int i;
    
    for ( i = 0; i < numberOfValues; i++ )
    {
        if ( i != 0 )
        {
            values[i].prevFreeItem = values + i - 1;
        }
        
        if ( i != numberOfValues - 1 )
        {
            values[i].nextFreeItem = values + i + 1;
        }
    }
    
    firstFreeItem = values;
    lastFreeItem = values + numberOfValues - 1;
    
    for ( i = 0; i < 3; i++ )
    {
        lines[i].sum = 0;
        lines[i].numberOfElements = 0;
    }
}

/* -------------------------------------------------------------------- */

void moveArrays()
{
    int i;
    long long j;
    ITEM * item;
    for ( i = 0; i < 2; i++ )
    {
        linesFin[i].numberOfElements = lines[i].numberOfElements;
        linesFin[i].sum = lines[i].sum;
        for ( j = 0; j < lines[i].numberOfElements; j++ )
        {
            linesFin[i].array[j] = lines[i].array[j];
        }
    }
    
    item = firstFreeItem;
    j = 0;
    linesFin[2].numberOfElements = 0;
    linesFin[2].sum = 0;
    
    while ( item )
    {
        linesFin[2].array[j] = item;
        linesFin[2].numberOfElements++;
        linesFin[2].sum += item->emise;
        item = item->nextFreeItem;
        j++;
    }
}

/* -------------------------------------------------------------------- */

void searchBounds()
{
    int i;
    
    /* Check the min value */
    freeSpace = minBound * 3 - sum;
    for ( i = 0; i < 3; i++ )
    {
        lines[i].freeSpace = minBound;
    }
    
    if ( fillTheLine( firstFreeItem, 1, freeSpace ) )
    {
        moveArrays();
        return;
    }
    
    while ( maxBound - minBound > 1 ) {
        recoverPointers();
        
        freeSpace = (maxBound + minBound) / 2 * 3 - sum;
        
        for ( i = 0; i < 3; i++ )
        {
            lines[i].freeSpace = (maxBound + minBound) / 2;
        }
        
        if ( fillTheLine( firstFreeItem, 1, freeSpace ) )
        {
            foundFreeSpace = (maxBound + minBound) / 2 * 3 - sum;
            foundLineFS = (maxBound + minBound) / 2;
            maxBound = (maxBound + minBound) / 2;
        } else {
            minBound = (maxBound + minBound) / 2;
        }
    }
    recoverPointers();
    
    freeSpace = foundFreeSpace;
    
    for ( i = 0; i < 3; i++ )
    {
        lines[i].freeSpace = foundLineFS;
    }
    
    if ( fillTheLine( firstFreeItem, 1, freeSpace ) )
    {
        moveArrays();
    }
    
}

/* -------------------------------------------------------------------- */

int main(int argc, const char * argv[]) {
    
    int i;
    long long int maxSum = 0;
    
    printf( "Emise ventilu:\n" );
    
    /* Reading is done with an error */
    if ( readInput() == -1 )
    {
        if ( values ) free( values );
        printf( "Nespravny vstup.\n" );
        return 1;
    }
    
    /* Creating ABC lines */
    lines = (LINE *) malloc( 3 * sizeof( LINE ) );
    linesFin = (LINE *) malloc( 3 * sizeof( LINE ) );
    
    for ( i = 0; i < 3; i++ )
    {
        lines[i].array = (ITEM **) malloc( arraySize * sizeof( ITEM * ) );
        lines[i].freeSpace = maxBound;
        lines[i].numberOfElements = 0;
        lines[i].sum = 0;
        
        linesFin[i].array = (ITEM **) malloc( arraySize * sizeof( ITEM * ) );
        linesFin[i].freeSpace = 0;          /* Rudimentary for this array */
        linesFin[i].numberOfElements = 0;
        linesFin[i].sum = 0;
    }
    
    searchBounds();
    
    /* Printing output */
    
    maxSum = linesFin[0].sum > linesFin[1].sum ? linesFin[0].sum : linesFin[1].sum;
    maxSum = maxSum > linesFin[2].sum ? maxSum : linesFin[2].sum;
    
    printf( "Nejvyssi emise: %lld\n", maxSum );
    
    printf( "A: " );
    for ( i = 0; i < linesFin[0].numberOfElements; i++ )
    {
        if ( i == 0 )
        {
            printf( "%lld", linesFin[0].array[i]->emise );
        } else {
            printf( ", %lld", linesFin[0].array[i]->emise );
        }
    }
    
    printf( "\n" );
    printf( "B: " );
    for ( i = 0; i < linesFin[1].numberOfElements; i++ )
    {
        if ( i == 0 )
        {
            printf( "%lld", linesFin[1].array[i]->emise );
        } else {
            printf( ", %lld", linesFin[1].array[i]->emise );
        }
    }

    printf( "\n" );
    printf( "C: " );
    for ( i = 0; i < linesFin[2].numberOfElements; i++ )
    {
        if ( i == 0 )
        {
            printf( "%lld", linesFin[2].array[i]->emise );
        } else {
            printf( ", %lld", linesFin[2].array[i]->emise );
        }
    }
    
    printf( "\n" );
    
    /* Freeing the memory up */
    if ( values ) free( values );
    for ( i = 0; i < 3; i++ )
    {
        free( lines[i].array );
        free( linesFin[i].array );
    }
    free( lines );
    free( linesFin );
    
    return 0;
}
