#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/* ---------------------------------------------------------- */

/* Defining structures */

typedef struct Price Price;

typedef struct
{
    long long int   id;
    long long int   numberOfSharesOfThisID;
    Price           *arrayOfPrices;
} Share;

struct Price
{
    long long int   price;
    long long int   amount;
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

void heapify( Share ** share, long long int i )
{
    long long int   left = 2 * i + 1, right = 2 * i + 2;
    long long int   smallest = i;
    Price           tmpPrice;
    
    if ( (left < (*share)->numberOfSharesOfThisID
        || left == (*share)->numberOfSharesOfThisID)
        && (*share)->arrayOfPrices[left].price < (*share)->arrayOfPrices[smallest].price )
    {
        smallest = left;
    }
    
    if ( (right < (*share)->numberOfSharesOfThisID
          || right == (*share)->numberOfSharesOfThisID)
        && (*share)->arrayOfPrices[right].price < (*share)->arrayOfPrices[smallest].price )
    {
        smallest = right;
    }
    
    if ( smallest != i )
    {
        tmpPrice = (*share)->arrayOfPrices[smallest];
        (*share)->arrayOfPrices[smallest] = (*share)->arrayOfPrices[i];
        (*share)->arrayOfPrices[i] = tmpPrice;
        heapify(share, smallest);
    }
    
}

/* ---------------------------------------------------------- */

void heapDecreaseKey( Share ** share, long long int i, long long int key )
{
    Price tmpPrice;
    
    if ( key > (*share)->arrayOfPrices[i].price )
    {
        heapify( share, i );
        return;
    }
    
    (*share)->arrayOfPrices[i].price = key;
    
    while ( i > 0
           && (*share)->arrayOfPrices[(i-1)/2].price < (*share)->arrayOfPrices[i].price )
    {
        tmpPrice = (*share)->arrayOfPrices[i];
        (*share)->arrayOfPrices[i] = (*share)->arrayOfPrices[i/2];
        (*share)->arrayOfPrices[(i-1)/2] = tmpPrice;
        i = (i-1)/2;
    }
}

/* ---------------------------------------------------------- */

void addNewPrice( Share ** share, long long int price )
{
    Price pricePiece;
    Share *sharePtr = *share;
    
    pricePiece.amount = 1;
    pricePiece.price = LLONG_MAX;
    
    sharePtr->numberOfSharesOfThisID++;
    sharePtr->arrayOfPrices[sharePtr->numberOfSharesOfThisID-1] = pricePiece;
    
    heapDecreaseKey( share, sharePtr->numberOfSharesOfThisID-1, price );
}

/* ---------------------------------------------------------- */

void removeFromHeap( Share ** share, long long int i )
{
    (*share)->arrayOfPrices[i] = (*share)->arrayOfPrices[(*share)->numberOfSharesOfThisID - 1];
    heapify( share, i );
}

/* ---------------------------------------------------------- */

void attemp2( void )
{
    long long int   i, maxID = 0, id, price, numberOfShares = 0;
    int             freeIDPlaces = 0;
    int             priceFound, scanfResult;
    char            sign;
    double          a, b;
    Share *         arrayOfShares = NULL;
    Share *         sharePtr;
    Share           share;
    Price           pricePiece;
    
    if ( !readHeader( &maxID ) )
    {
        printf( "Nespravny vstup.\n" );
        return;
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
                
                share.id = id;
                share.numberOfSharesOfThisID = 1;
                
                share.arrayOfPrices = (Price *) malloc( 100 * sizeof(Price) );
                
                share.arrayOfPrices[0] = pricePiece;
                
                arrayOfShares[numberOfShares - 1] = share;
                
            } else {
                
                if ( sharePtr -> numberOfSharesOfThisID % 100 == 0 )
                {
                    sharePtr->arrayOfPrices = (Price *) realloc( sharePtr->arrayOfPrices,
                                                                (sharePtr->numberOfSharesOfThisID + 100) * sizeof(Price));
                }
                
                priceFound = 0;
                
                for ( i = 0; i < sharePtr->numberOfSharesOfThisID; i++ )
                {
                    if ( sharePtr->arrayOfPrices[i].price == price )
                    {
                        sharePtr->arrayOfPrices[i].amount++;
                        priceFound = 1;
                        break;
                    }
                }
                
                if ( !priceFound )
                {
                    addNewPrice( &sharePtr, price );
                }
            }
            
        } else {
            
            sharePtr = findTheID( arrayOfShares, 0, numberOfShares - 1, id );
            
            if ( sharePtr )
            {
                
                if ( sharePtr -> numberOfSharesOfThisID == 0 )
                {
                    printf( "Neni k dispozici.\n" );
                    continue;
                }
                
                
                if ( sharePtr->arrayOfPrices[0].price > price )
                {
                    printf( "Neni k dispozici.\n" );
                    
                } else {
                    
                    sharePtr->arrayOfPrices[0].amount--;
                    printf( "Prodano za %lld\n", sharePtr->arrayOfPrices[0].price );
                    
                    if ( sharePtr->arrayOfPrices[0].amount == 0 )
                    {
                        removeFromHeap( &sharePtr, 0 );
                        sharePtr->numberOfSharesOfThisID--;
                        
                        if ( sharePtr->numberOfSharesOfThisID % 100 == 0 && sharePtr->numberOfSharesOfThisID > 100 )
                        {
                            sharePtr->arrayOfPrices = (Price*) realloc( sharePtr->arrayOfPrices,
                                                                       (sharePtr->numberOfSharesOfThisID - 100) * sizeof(Price));
                        }
                    }
                }
                
            } else {
                printf( "Neni k dispozici.\n" );
            }
        }
    }
    
    for ( i = 0; i < numberOfShares; i++ )
    {
        sharePtr = &arrayOfShares[i];
        if ( sharePtr )
        {
            free( sharePtr->arrayOfPrices );
        }
    }
    free( arrayOfShares );

}

int main ()
{
    attemp2();
    return 0;
}
