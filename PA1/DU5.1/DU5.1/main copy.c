#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/* ---------------------------------------------------------- */

/* Defining structures */

typedef struct Price Price;

typedef struct
{
    long long int id;
    long long int numberOfSharesOfThisID;
    Price         *nextPrice;
} Share;

struct Price
{
    long long int price;
    long long int amount;
    Price         *prevPrice;
    Price         *nextPrice;
};

/* ---------------------------------------------------------- */

/*
 Checks if a double is an integer number and is higher than 0 (optional).
 @return Returns intValue if all conditions are true. Otherwise, returns -1.
 */

long long int checkForInteger( double a, int needsHT0 )
{
    double a1 = floor( a );
    double diffA = a - a1;
    double eps = 10e-15;
    long long int intValue = a;
    
    if ( a < 0.0 && diffA > eps )
        return -1;
    
    if ( needsHT0 == 1 && intValue == 0 )
        return -1;
    
    return intValue;
}

/* ---------------------------------------------------------- */

/* Reads a share input. 
 @return Returns:
 0 - something wrong
 1 -
 
 */

int readNextOffer( long long int * maxID )
{
    
    return 1;
}

/* ---------------------------------------------------------- */

/* Reads the first part of the input */
int readHeader( long long int * maxID )
{
    double a = 0.0;
    
    printf ( "Nejvyssi ID:\n" );
    
    if ( scanf ( "%lf", &a ) == 1
        && (*maxID = checkForInteger ( a, 0 )) != -1LL )
    {
        printf ( "Nabidka a poptavka:\n" );
        return 1;
    }
    else return 0;
}

/* ---------------------------------------------------------- */

/* Finds the id in the array 
 *
 * Returns the address to the id if found. Otherwise, returns NULL.
 *
 */

Share * findTheID( Share * array,
                   long long int lowIndex,
                   long long int highIndex,
                   long long int id)
{
    long long int i;

    for ( i = lowIndex; i <= highIndex; i++ )
    {
        if ( array[i].id == id )
        {
            return &array[i];
        }
    }
    
    return NULL;
    
}

/* ---------------------------------------------------------- */
/*
void printInfo( Share ** array, long long int numberOfShares )
{
    long long int i, j;
    Share share;
    Price *price;
    
    printf("-----------------------------\n");
    
    printf("Number of shares: %lld\n", numberOfShares);
    for ( i = 0; i < numberOfShares; i++ )
    {
        share = (*array)[i];
        printf("For ID %lld exist: %lld shares:\n", share.id, share.numberOfSharesOfThisID);
        
        price = share.nextPrice;
        for ( j = 0; j < share.numberOfSharesOfThisID; j++ )
        {
            printf("(%lld) Price %lld with amount %lld\n", j, price->price, price->amount);
            if ( price->nextPrice )
            {
                price = price->nextPrice;
            }
        }
        
        printf("\n");
        
    }
    
    printf("-----------------------------\n");
}
*/
int main(int argc, const char * argv[])
{
    long long int   i, j, maxID = 0, id, price, numberOfShares = 0, maxPrice, minPrice;
    int             freeIDPlaces = 0;
    int             priceFound, scanfResult;
    int             returnValueMain = 0;
    char            sign;
    double          a, b;
    Share *         arrayOfShares = NULL;
    Share *         sharePtr;
    Share           share;
    Price           pricePiece;
    Price           *workingPrice, *workingPrice1, *nextPriceCandidate, *prevPriceCandidate;
    char            string[10000];
    
    if ( !readHeader( &maxID ) )
    {
        printf( "Nespravny vstup.\n" );
        return 1;
    }
    
    while ( 1 )
    {
        scanfResult = scanf( " %c %lf %lf", &sign, &a, &b );
        
        if ( feof( stdin ) )
        {
            break;
        }
        
        if ( scanfResult != 3
            || ( id = checkForInteger ( a, 0 ) ) == -1LL
            || ( price = checkForInteger ( b, 1 ) ) == -1LL
            || id > maxID
            || ( sign != '-' && sign != '+' ) )
        {
            printf("Nespravny vstup.\n");
            break;
        }
        
        if ( sign == '+' )
        {
            sharePtr = findTheID( arrayOfShares, 0, numberOfShares - 1, id );
            
            if ( sharePtr == NULL )
            {
                numberOfShares++;
                
                if ( !freeIDPlaces )
                {
                    arrayOfShares = (Share *) realloc( arrayOfShares, ( numberOfShares / 100 + 1 ) * 100 * sizeof(Share) );
                    freeIDPlaces = 100;
                }
                
                freeIDPlaces--;
                
                pricePiece.price = price;
                pricePiece.amount = 1LL;
                pricePiece.prevPrice = NULL;
                pricePiece.nextPrice = NULL;
                
                share.id = id;
                share.numberOfSharesOfThisID = 1;
                share.nextPrice = (Price *) malloc( sizeof(Price) );
                
                *share.nextPrice = pricePiece;
                
                arrayOfShares[numberOfShares - 1] = share;
                
            } else {
                
                /*
                if ( !(sharePtr->freeSpace) )
                {
                    sharePtr->firstPrice = (Price *) realloc( sharePtr -> firstPrice,
                                                             ((sharePtr -> numberOfSharesOfThisID) + 100) * sizeof(Price) );
                    sharePtr->freeSpace = 100;
                    sharePtr->nextPrice = sharePtr -> firstPrice + sharePtr -> indexOfNextPriceInArray;
                }
                */
                
                pricePiece.price = price;
                pricePiece.amount = 1LL;
                pricePiece.prevPrice = NULL;
                pricePiece.nextPrice = NULL;
                
                workingPrice = sharePtr->nextPrice;
                minPrice = 0LL;
                maxPrice = LLONG_MAX;
                prevPriceCandidate = NULL;
                nextPriceCandidate = NULL;
                priceFound = 0;
                
                for ( i = 0; i < sharePtr->numberOfSharesOfThisID; i++ )
                {
                    if ( workingPrice->price == price )
                    {
                        workingPrice->amount++;
                        priceFound = 1;
                        break;
                    }
                    
                    if ( workingPrice->price < price && workingPrice->price > minPrice )
                    {
                        prevPriceCandidate = workingPrice;
                        minPrice = workingPrice->price;
                    }
                    
                    if ( workingPrice->price > price && workingPrice->price < maxPrice )
                    {
                        nextPriceCandidate = workingPrice;
                        maxPrice = workingPrice->price;
                    }
                    
                    workingPrice = workingPrice->nextPrice;
                }
                
                if ( !priceFound )
                {
                    pricePiece.nextPrice = nextPriceCandidate;
                    pricePiece.prevPrice = prevPriceCandidate;
                    sharePtr->numberOfSharesOfThisID++;
                    
                    workingPrice = (Price *) malloc( sizeof(Price) );
                    workingPrice[0] = pricePiece;
                    
                    if ( prevPriceCandidate )
                    {
                        prevPriceCandidate->nextPrice = workingPrice;
                    } else {
                        
                        sharePtr->nextPrice = workingPrice;
                    }
                    if ( nextPriceCandidate )
                    {
                        nextPriceCandidate->prevPrice = workingPrice;
                    }
                }
            }
            
        } else {
            
            sharePtr = findTheID( arrayOfShares, 0, numberOfShares - 1, id );
            
            if ( sharePtr )
            {
                if ( sharePtr -> nextPrice == NULL )
                {
#warning message
                    printf( "Neni k dispozici.\n" );
                    /*
                    numberOfShares--;
                    freeIDPlaces++;
                    
                    for ( index = sharePtr - arrayOfShares; index < numberOfShares; index++ )
                    {
                        *sharePtr = *(sharePtr + 1);
                        sharePtr = sharePtr + 1;
                        
                    }
                     */
                    /*printInfo( &arrayOfShares, numberOfShares);*/
                    continue;
                }
                
                if ( sharePtr->nextPrice->price > price )
                {
#warning
                    printf( "Neni k dispozici.\n" );
                    
                } else {
                    
                    workingPrice = sharePtr -> nextPrice;
                    
                    workingPrice -> amount --;
#warning message
                    printf( "Prodano za %lld\n", workingPrice->price );
                    
                    if ( workingPrice -> amount == 0 )
                    {
                        if ( workingPrice -> prevPrice )
                        {
                            workingPrice -> prevPrice -> nextPrice = workingPrice -> nextPrice;
                        } else {
                            sharePtr -> nextPrice = workingPrice -> nextPrice;
                        }
                        if ( workingPrice -> nextPrice )
                        {
                            workingPrice -> nextPrice -> prevPrice = workingPrice -> prevPrice;
                        }
                        
                        sharePtr -> numberOfSharesOfThisID --;
                        free( workingPrice );
                    }
                    
                }
                
                
            } else {
#warning message
                printf( "Neni k dispozici.\n" );
            }
        }
        /*printInfo( &arrayOfShares, numberOfShares);*/
    }
    /*
    printf("\n\n");
    
    for ( i = 0; i < numberOfShares; i++ )
    {
        share = arrayOfShares[i];
        printf("Share id: %lld \n", share.id);
        pricePiece = share.firstPrice[0];
        printf("Price of it with amount %lld: %lld \n", pricePiece.amount, pricePiece.price );
    }
    */
    for ( i = 0; i < numberOfShares; i++ )
    {
        sharePtr = &arrayOfShares[i];
        if ( sharePtr )
        {
            workingPrice = sharePtr->nextPrice;
            for ( j = 0; j < sharePtr->numberOfSharesOfThisID; j++ )
            {
                workingPrice1 = workingPrice;
                if ( workingPrice1 -> nextPrice )
                {
                    workingPrice = workingPrice1 -> nextPrice;
                }
                free( workingPrice1 );
            }
        }
    }
    free( arrayOfShares );
    
    return returnValueMain;
}
