#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define MAX_ALLOC 100

/* ---------------------------------------------------------- */

/* Defining structures */

typedef struct Price Price;

typedef struct
{
    int             numberOfAddedThousands, numberOfAddedHundreds;
    
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
    
    if ( a < 0.0 || diffA > eps )
        return -1;
    
    if ( needsHT0 == 1 && intValue == 0 )
        return -1;
    
    return intValue;
}

/* ---------------------------------------------------------- */

/* Reads the first part of the input */
int readHeader( long long int * maxID )
{
    double a = 0.0;
    
    printf ( "Nejvyssi ID:\n" );
    
    if ( scanf ( "%lf", &a ) == 1
        && (*maxID = checkForInteger ( a, 0 )) != -1LL
        && *maxID > 0)
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
                  long long int id,
                  long long int *nearestLeft,
                  long long int *min)
{
    long long int mid = (lowIndex + highIndex) / 2;
    Share *share = NULL;
    
    if ( lowIndex > highIndex )
    {
        return NULL;
    }
    
    if ( array[lowIndex].id > *min && array[lowIndex].id < id )
    {
        *nearestLeft = lowIndex;
        *min = array[lowIndex].id;
    }
    
    if ( array[highIndex].id > *min && array[highIndex].id < id )
    {
        *nearestLeft = highIndex;
        *min = array[highIndex].id;
    }
    
    if ( array[highIndex].id == id )
    {
        return &array[highIndex];
    }
    
    if ( array[lowIndex].id == id )
    {
        return &array[lowIndex];
    }
    
    if ( array[lowIndex].id > id )
    {
        return NULL;
    }
    
    if ( array[highIndex].id < id )
    {
        return NULL;
    }
    
    if ( lowIndex == highIndex )
    {
        return NULL;
    }
    
    share = findTheID( array, lowIndex, mid, id, nearestLeft, min );
    
    if ( !share )
    {
        share = findTheID( array, mid + 1, highIndex, id, nearestLeft, min );
    }
    
    return share;
    
}

/* ---------------------------------------------------------- */

void insertNewShare ( Share * array,
                     long long int newAmount,
                     long long int nearestLeft,
                     Share * share )
{
    long long int i = 0;
    
    if ( newAmount == 1 )
    {
        array[0] = *share;
        return;
    }
    
    for ( i = newAmount - 2; i > nearestLeft; i-- )
    {
        array[i+1] = array[i];
    }
    array[nearestLeft+1] = *share;
}

/* ---------------------------------------------------------- */

void heapify( Share * share, long long int i )
{
    long long int   left = 2 * i + 1, right = 2 * i + 2;
    long long int   smallest = i;
    Price           tmpPrice;
    
    if ( left < share->numberOfSharesOfThisID
        && share->arrayOfPrices[left].price < share->arrayOfPrices[smallest].price )
    {
        smallest = left;
    }
    
    if ( right < share->numberOfSharesOfThisID
        && share->arrayOfPrices[right].price < share->arrayOfPrices[smallest].price )
    {
        smallest = right;
    }
    
    if ( smallest != i )
    {
        tmpPrice = share->arrayOfPrices[smallest];
        share->arrayOfPrices[smallest] = share->arrayOfPrices[i];
        share->arrayOfPrices[i] = tmpPrice;
        
        heapify(share, smallest);
    }
    
}

/* ---------------------------------------------------------- */

void heapDecreaseKey( Share * share, long long int i, long long int key )
{
    Price tmpPrice;
    
    if ( key > share->arrayOfPrices[i].price )
    {
        heapify( share, i );
        return;
    }
    
    share->arrayOfPrices[i].price = key;
    
    while ( i > 0
           && share->arrayOfPrices[(i-1)/2].price > share->arrayOfPrices[i].price )
    {
        tmpPrice = share->arrayOfPrices[i];
        share->arrayOfPrices[i] = share->arrayOfPrices[(i-1)/2];
        share->arrayOfPrices[(i-1)/2] = tmpPrice;
        i = (i-1)/2;
    }
}

/* ---------------------------------------------------------- */

void addNewPrice( Share * share, long long int price )
{
    Price pricePiece;
    Share *sharePtr = share;
    
    pricePiece.amount = 1;
    pricePiece.price = LLONG_MAX;
    
    sharePtr->numberOfSharesOfThisID++;
    sharePtr->arrayOfPrices[sharePtr->numberOfSharesOfThisID-1] = pricePiece;
    
    heapDecreaseKey( share, sharePtr->numberOfSharesOfThisID-1, price );
}

/* ---------------------------------------------------------- */

void removeFromHeap( Share * share, long long int i )
{
    share->arrayOfPrices[i] = share->arrayOfPrices[share->numberOfSharesOfThisID - 1];
    share->numberOfSharesOfThisID--;
    heapify( share, i );
}

/* ---------------------------------------------------------- */

void printInfo( Share * array, long long int numberOfShares )
{
    long long int i, j;
    Share share;
    Price price;
    
    printf("-----------------------------\n");
    
    printf("Number of shares: %lld\n", numberOfShares);
    for ( i = 0; i < numberOfShares; i++ )
    {
        share = array[i];
        printf("For ID %lld exist: %lld shares:\n", share.id, share.numberOfSharesOfThisID);
        
        for ( j = 0; j < share.numberOfSharesOfThisID; j++ )
        {
            price = share.arrayOfPrices[j];
            printf("(%lld) Price %lld with amount %lld\n", j, price.price, price.amount);
        }
        
        printf("\n");
        
    }
    
    printf("-----------------------------\n");
}

/* ---------------------------------------------------------- */

void attemp2( void )
{
    long long int   i, maxID = 0, numberOfShares = 0, price, id;
    /* For adding */
    long long int   nearestLeft = 0, min = -1LL;
    long long int   freeIDPlaces = 0;
    int             priceFound, scanfResult;
    char            sign;
    double          a, b, power;
    Share *         arrayOfShares = NULL, *arrayOfSharesTemp;
    Share *         sharePtr;
    Share           share;
    Price           pricePiece;
    Price *         arrayTemp;
    
    if ( !readHeader( &maxID ) )
    {
        printf( "Nespravny vstup.\n" );
        return;
    }
    
    while ( 1 )
    {
        scanfResult = scanf( " %c %lf %lf", &sign, &a, &b );
        
        
        if ( sign == '!' )
        {
            printInfo( arrayOfShares, numberOfShares );
            continue;
        }
        
        if ( feof( stdin ) )
        {
            break;
        }
        
        if ( scanfResult != 3
            || ( id = checkForInteger ( a, 0 ) ) == -1LL
            || ( price = checkForInteger ( b, 1 ) ) == -1LL
            || price < 0
            || id > maxID
            || ( sign != '-' && sign != '+' ) )
        {
            printf("Nespravny vstup.\n");
            break;
        }
        
        min = -1LL;
        if ( arrayOfShares != NULL && arrayOfShares[0].id > id)
        {
            nearestLeft = -1LL;
        }
        
        if ( arrayOfShares != NULL && arrayOfShares[numberOfShares-1].id < id )
        {
            nearestLeft = numberOfShares - 1;
        }
        
        sharePtr = findTheID( arrayOfShares, 0, numberOfShares - 1, id, &nearestLeft, &min );
        
        if ( sign == '+' )
        {
            if ( sharePtr == NULL ) /* Adding new Share */
            {
                numberOfShares++;
                
                if ( !freeIDPlaces )
                {
                    if ( numberOfShares == 0 )
                    {
                        arrayOfShares = (Share *) realloc( arrayOfShares, sizeof(Share) );
                        freeIDPlaces = 1;
                        
                    } else {
                        arrayOfSharesTemp = NULL;
                        arrayOfSharesTemp = (Share *)realloc( arrayOfShares, 2 * numberOfShares * sizeof(Share) );
                        
                        if ( arrayOfSharesTemp )
                        {
                            arrayOfShares = arrayOfSharesTemp;
                            freeIDPlaces = numberOfShares;
                            
                        } else {
                            
                            arrayOfSharesTemp = (Share *)realloc( arrayOfShares, 1000 + numberOfShares * sizeof(Share) );
                            
                            if ( arrayOfSharesTemp )
                            {
                                arrayOfShares = arrayOfSharesTemp;
                                freeIDPlaces = 1000;
                                
                            } else {
                                
                                arrayOfShares = (Share *)realloc( arrayOfShares, 1000 + numberOfShares * sizeof(Share) );
                                freeIDPlaces = 100;
                            }
                        }
                    }
                    /*arrayOfShares = (Share *) realloc( arrayOfShares, ( numberOfShares / MAX_ALLOC + 1 ) * MAX_ALLOC * sizeof(Share) );*/
                }
                
                freeIDPlaces--;
                
                pricePiece.amount = 1LL;
                pricePiece.price = price;
                
                share.numberOfSharesOfThisID = 1;
                share.id = id;
                share.numberOfAddedThousands = 0;
                share.numberOfAddedHundreds = 0;
                
                share.arrayOfPrices = (Price *) malloc( sizeof(Price) );
                share.arrayOfPrices[0] = pricePiece;
                
                insertNewShare( arrayOfShares, numberOfShares, nearestLeft, &share );
                
            } else { /* Adding new price */
                
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
                    
                    if ( sharePtr -> numberOfSharesOfThisID == 0 )
                    {
                        sharePtr->arrayOfPrices = (Price *) malloc( sizeof(Price) );
                        
                    } else {
                        
                        power = log2( sharePtr->numberOfSharesOfThisID - sharePtr->numberOfAddedThousands * 1000 - sharePtr->numberOfAddedHundreds * 100 );
                        
                        if ( checkForInteger( power , 0 ) != -1LL )
                        {
                            arrayTemp = NULL;
                            arrayTemp = (Price *) realloc( sharePtr->arrayOfPrices,
                                                          (sharePtr->numberOfSharesOfThisID * 2) * sizeof(Price));
                            if ( arrayTemp )
                            {
                                sharePtr->arrayOfPrices = arrayTemp;
                                
                            } else {
                                
                                arrayTemp = (Price *) realloc( sharePtr->arrayOfPrices,
                                                              (sharePtr->numberOfSharesOfThisID + 1000) * sizeof(Price));
                                if ( arrayTemp )
                                {
                                    sharePtr -> numberOfAddedThousands ++;
                                    sharePtr->arrayOfPrices = arrayTemp;
                                    
                                } else {
                                    
                                    arrayTemp = (Price *) realloc( sharePtr->arrayOfPrices,
                                                                  (sharePtr->numberOfSharesOfThisID + 100) * sizeof(Price));
                                    
                                    sharePtr->arrayOfPrices  = arrayTemp;
                                    sharePtr->numberOfAddedHundreds ++;
                                }
                                
                            }
                        }
                    }
                    addNewPrice( sharePtr, price );
                }
            }
            
        } else { /* Searching for price */
            
            if ( sharePtr )
            {
                
                if ( sharePtr->numberOfSharesOfThisID == 0 )
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
                        removeFromHeap( sharePtr, 0 );
                        
                        if ( sharePtr->numberOfSharesOfThisID == 0  )
                        {
                            free( sharePtr->arrayOfPrices );
                            sharePtr->arrayOfPrices = NULL;
                        } else if ( sharePtr -> numberOfSharesOfThisID != 1LL )
                        {
                            power = log2( sharePtr->numberOfSharesOfThisID - sharePtr->numberOfAddedThousands * 1000 - sharePtr->numberOfAddedHundreds * 100 );
                            
                            if ( checkForInteger( power , 0 ) != -1LL )
                            {
                                sharePtr->arrayOfPrices = (Price *) realloc( sharePtr->arrayOfPrices,
                                                                            (sharePtr->numberOfSharesOfThisID) * sizeof(Price));
                                if ( sharePtr -> numberOfAddedHundreds )
                                {
                                    sharePtr->numberOfAddedHundreds --;
                                } else if ( sharePtr -> numberOfAddedThousands )
                                {
                                    sharePtr->numberOfAddedThousands --;
                                }
                            }
                        }
                    }
                }
                
            } else { /* Share's not found */
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
/*


     Warriors stop
     Leave your anger and
     Just look around
     At all dead bodies
     Not long ago they were
     Just like you
     
     Think of your and
     Others families
     They deserve a chance
     To see their fathers
     Not killed at war
     Of money and of gold
     Black gold



*/