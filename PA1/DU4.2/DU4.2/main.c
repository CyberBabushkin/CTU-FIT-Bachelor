#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    short x, y;
} Point;


/*
 Checks if two doubles are integer numbers.
 @return Returns 1 if the doubles are integers. Otherwise, returns 0.
 */

int checkForInteger ( double a, double b )
{
    double a1 = floor( a ), b1 = floor( b );
    double diffA = a - a1, diffB = b - b1;
    double eps = 10e-15;
    
    if ( diffA < eps && diffB < eps )
        return 1;
    
    return 0;
}

/* ------------------------------------------------------------------------ */

/* 
 Reads data from stdin and checks it.
 @return Returns 1 if no errors. Otherwise, returns 1.
 */

int readInput ( short *** map, short * columnsOut, short * rowsOut, Point ** infected, short * amountOfInfected )
{
    double  a, b;
    short   rows, columns;
    int     i, j;
    char    c;
    Point   place;
    
    printf("Velikost kancelare:\n");
    
    if ( scanf("%lf %lf", &a, &b) == 2
        && a <= 500.0 && a > 0.0
        && b <= 500.0 && b > 0.0
        && checkForInteger( a, b ) )
    {
        rows = a;
        columns = b;
        
        if ( *map == NULL )
        {
            *map = ( short ** ) malloc ( rows * sizeof( ** map ) );
            for ( i = 0; i < rows; i++ )
            {
                (*map)[i] = ( short * ) malloc ( columns * sizeof ( *** map ) );
            }
        }
        
        if ( fgetc ( stdin ) != '\n' ) {
            return 0;
        }
        
        for ( i = 0; i < rows; i++ )
        {
            for ( j = 0; j < columns; j++ )
            {
                c = fgetc ( stdin );
                
                if ( c == 'o' )
                {
                    (*map)[i][j] = 1;
                }
                
                else if ( c == '!' )
                {
                    (*map)[i][j] = 2;
                    place.x = i;
                    place.y = j;
                    *infected = (Point *) realloc( *infected, (++ (*amountOfInfected)) * sizeof(Point) );
                    (*infected)[*amountOfInfected - 1] = place;
                }
                
                else if ( c == '.' )
                {
                    (*map)[i][j] = 0;
                }
                else /* Incorrect char */
                {
                    return 0;
                }
            }
            
            c = fgetc ( stdin );
            if ( c != '\n' ) {
                return 0;
            }
        }
    }
    else /* Incorrect rows or columns numbers */
    {
        return 0;
    }
    
    *columnsOut = columns;
    *rowsOut = rows;
    
    return 1;
}

/* ------------------------------------------------------------------------ */

/* Infects a neighbour.
 @params xOffset must be -1 for the left neighbour and 1 for the right.
 yOffset must be -1 for the top neighbour and 1 for the bottom.
 For both params 0 means a coord of my place.
 
 @return If infections has been done, returns 1. Otherwise, returns 0.
 */
int infectMyNeighbour ( short *** map, short rows, short cols, Point myPlace, short xOffset, short yOffset )
{
    short xCoord = myPlace.x + xOffset;
    short yCoord = myPlace.y + yOffset;
    
    if ( xCoord >= 0 && xCoord < rows
        && yCoord >= 0 && yCoord < cols
        && (*map)[xCoord][yCoord] == 1)
    {
        (*map)[xCoord][yCoord] = 2;
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------------ */

/* Function kills people. It's great, isn't it? Well, ok, it just infects neighbours...
 @return Returns 1 if at least one neighbour has been infected. Otherwise, returns 0.
 */
int killPeople ( short *** map, short columns, short rows, Point ** infected, short * amountOfInfected )
{
    int    i, peopleInfectedBeforeThisDay = *amountOfInfected;
    Point  place;
    int    weKilledSomePeople = 0;
    
    for ( i = 0; i < peopleInfectedBeforeThisDay; i++ )
    {
        /* Infect the left neighbour */
        place = (*infected)[i];
        if ( infectMyNeighbour( map, rows, columns, place, -1, 0 ) )
        {
            *infected = (Point *) realloc( *infected, (++(* amountOfInfected)) * sizeof( Point ) );
            place.x--;
            (* infected)[*amountOfInfected - 1] = place;
            weKilledSomePeople = 1;
        }
        
        /* Infect the right neighbour */
        place = (*infected)[i];
        if ( infectMyNeighbour( map, rows, columns, place, 1, 0 ) )
        {
            *infected = (Point *) realloc( *infected, (++(* amountOfInfected)) * sizeof( Point ) );
            place.x++;
            (* infected)[*amountOfInfected - 1] = place;
            weKilledSomePeople = 1;
        }
        
        /* Infect the top neighbour */
        place = (*infected)[i];
        if ( infectMyNeighbour( map, rows, columns, place, 0, -1 ) )
        {
            *infected = (Point *) realloc( *infected, (++(* amountOfInfected)) * sizeof( Point ) );
            place.y--;
            (* infected)[*amountOfInfected - 1] = place;
            weKilledSomePeople = 1;
        }
        
        /* Infect the bottom neighbour */
        place = (*infected)[i];
        if ( infectMyNeighbour( map, rows, columns, place, 0, 1 ) )
        {
            *infected = (Point *) realloc( *infected, (++(* amountOfInfected)) * sizeof( Point ) );
            place.y++;
            (* infected)[*amountOfInfected - 1] = place;
            weKilledSomePeople = 1;
        }
    }
    return weKilledSomePeople;
}

/* ------------------------------------------------------------------------ */

int main(void)
{
    int   i;
    
    Point *infected = NULL;;
    short amountOfInfected = 0, days = 0;
    short columns, rows;
    short **map = NULL;
    
    /* 0 - table, 1 - healthy, 2 - infected, 3 - was previosly infected */
    
    
    if ( !readInput( &map, &columns, &rows, &infected, &amountOfInfected ) ) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    if ( infected == NULL ) {
        printf( "Nikdo neonemocnel.\n" );
        return 0;
    }
    
    while ( killPeople( &map, columns, rows, &infected, &amountOfInfected ) ) {
        days++;
    }
    
    printf( "Nakazenych: %hd, doba sireni nakazy: %hd\n", amountOfInfected, days );
    
    for ( i = 0; i < rows; i++ ) {
        free ( map[i] );
    }
    free ( map );
    free ( infected );
    
    return 0;
}
