#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#endif /* C++ 11 */
using namespace std;
#endif /* __PROGTEST__ */

class CDate
{
    private:
        int m_Year, m_Month, m_Day;
        
    public:
        CDate( int y, int m, int d ) : m_Year( y ), m_Month( m ), m_Day( d ) {}
        
        bool operator == ( const CDate & d ) const
        {
            return d.m_Year == m_Year && d.m_Month == m_Month && d.m_Day == m_Day;
        }
        bool operator != ( const CDate & d ) const
        {
            return d.m_Year != m_Year || d.m_Month != m_Month || d.m_Day != m_Day;
        }
        bool operator < ( const CDate & d ) const
        {
            if ( m_Year < d.m_Year ) return true;
            if ( m_Year > d.m_Year ) return false;
            if ( m_Month < d.m_Month ) return true;
            if ( m_Month > d.m_Month ) return false;
            if ( m_Day < d.m_Day ) return true;
            return false;
        }
        bool operator <= ( const CDate & d ) const
        {
            if ( m_Year < d.m_Year ) return true;
            if ( m_Year > d.m_Year ) return false;
            if ( m_Month < d.m_Month ) return true;
            if ( m_Month > d.m_Month ) return false;
            if ( m_Day <= d.m_Day ) return true;
            return false;
        }
        bool operator > ( const CDate & d ) const
        {
            return ! operator<= ( d );
        }
        bool operator >= ( const CDate & d ) const
        {
            return ! operator< ( d );
        }
};

class CSupermarket
{
    private:
        struct CName
        {
            CName() {}
            CName( const string & str ) : m_RealName( str ), m_Collisions( 0 ), m_Free( false ) {}
            
            string  m_RealName;
            int     m_Collisions;
            bool    m_Free;
        };
        struct CGood
        {
            CGood() : m_Amount( 0 ) {}
            CGood( const map<CDate, int> & a, int b ) : m_Amount( b ), m_Dates( a ) {}
            int             m_Amount;
            map<CDate, int> m_Dates;
        };
    
        map<string, CGood> m_Goods;
        vector< unordered_map<string, CName> > m_MaskedNames;
    
        string getStringMastAtIndex( const string & name, size_t id )
        {
            string mask = string( name.begin(), name.begin() + id );
            mask += "$";
            mask += string( name.begin() + id + 1, name.end() );
            return mask;
        }
    public:
        CSupermarket() : m_MaskedNames( 31 ) {}
        CSupermarket & Store( const string name, const CDate & expiryDate, int count )
        {
            map<string, CGood>::iterator good = m_Goods.find( name );
            if ( good == m_Goods.end() )
            {
                map<CDate, int> newItem;
                newItem.insert( make_pair( expiryDate, count ) );
                CGood newGood( newItem, count );
                m_Goods.insert( make_pair( name, newGood ) );
                
                // making compare strings
                size_t len = name.length();
                
                for ( size_t i = 0; i < len; i ++ )
                {
                    string mask = getStringMastAtIndex( name, i );
                    
                    unordered_map<string, CName> & map = m_MaskedNames[ len ];
                    unordered_map<string, CName>::iterator it = map.find( mask );
                    if ( it != map.end() )
                    {
                        if ( ! it->second . m_Free )
                            it->second . m_Collisions += 1;
                        else
                        {
                            it->second . m_RealName = name;
                            it->second . m_Free = false;
                        }
                    } else {
                        map.insert( make_pair( mask, CName( name ) ) );
                    }
                }
                
            } else {
                map<CDate, int> & dates = good->second . m_Dates;
                map<CDate, int>::iterator foundDate = dates.find( expiryDate );
                
                if ( foundDate == dates.end() )
                {
                    dates.insert( make_pair(expiryDate, count) );
                } else
                {
                    foundDate -> second += count;
                }
                
                good->second . m_Amount += count;
            }
            return *this;
        }
    
        void Sell( list< pair<string, int> > & shoppingList )
        {
            list< map<string, CGood>::iterator > toDelete;
            list< pair<string, int> >::iterator item = shoppingList.begin();
            
            while ( item != shoppingList.end() )
            {
                string name = item -> first;
                int amount = item -> second;
                
                // trying to fing an exact name
                map<string, CGood>::iterator good = m_Goods.find( name );
                
                // nope, unfortunately, have to look for in changed names
                if ( good == m_Goods.end() )
                {
                    bool foundFlag = false;
                    bool collision = false;
                    string foundName = "";
                    size_t len = name.length();
                    unordered_map<string, CName> & names = m_MaskedNames[len];
                    
                    for ( size_t i = 0; i < len; i ++ )
                    {
                        string nameVar = getStringMastAtIndex( name, i );
                        unordered_map<string, CName>::iterator nameIter = names.find( nameVar );
                        
                        if ( nameIter != names.end()
                             && ! nameIter->second . m_Collisions
                             && ! nameIter->second . m_Free )
                        {
                            if ( ! foundFlag )
                            {
                                foundName = nameIter->second . m_RealName;
                                foundFlag = true;
                            }
                            else if ( nameIter->second . m_RealName != foundName
                                      && ! nameIter->second . m_Free )
                            {
                                collision = true;
                                break;
                            }
                        }
                    }
                    
                    if ( ! collision )
                    {
                        good = m_Goods.find( foundName );
                    }
                }
                
                list< pair<string, int> >::iterator tmp = item;
                item++;
                
                // if we have found one
                if ( good != m_Goods.end() && good -> second . m_Amount )
                {
                    for ( map<CDate, int>::iterator date = good->second . m_Dates.begin();
                          amount && date != good->second . m_Dates.end();
                          date ++ )
                    {
                        int availableAmount = date -> second;
                        if ( availableAmount )
                        {
                            if ( availableAmount >= amount )
                            {
                                date -> second -= amount;
                                good->second.m_Amount -= amount;
                                amount = 0;
                                break;
                            } else {
                                amount -= availableAmount;
                                good->second.m_Amount -= date->second;
                                date -> second = 0;
                            }
                        }
                    }
                    
                    // delete from list if nothing's left to buy
                    if ( ! amount )
                        shoppingList.erase( tmp );
                    else // or just decreasing a number
                        tmp -> second = amount;
                    
                    if ( ! good -> second . m_Amount )
                        toDelete.push_back( good );
                }
            }
            
            // no more champagne and the fireworks are through...
            for ( list< map<string, CGood>::iterator >::iterator lst = toDelete.begin();
                  lst != toDelete.end();
                  lst++ )
            {
                map<string, CGood>::iterator & good = *lst;
                string name = good -> first;
                
                if ( ! good -> second . m_Amount )
                {
                    size_t len = name.length();
                    unordered_map<string, CName> & names = m_MaskedNames[len];
                    string goodName = good -> first;
                    
                    for ( size_t i = 0; i < len; i++ )
                    {
                        string nameVar = getStringMastAtIndex( goodName, i );
                        unordered_map<string, CName>::iterator nameIter = names.find( nameVar );
                        
                        if ( nameIter -> second . m_Collisions == 0 )
                        {
                            //names.erase( nameIter );
                            nameIter -> second . m_Free = true;
                        }
                        else
                            nameIter -> second . m_Collisions --;
                    }
                }
            }
        }
    
        list< pair<string, int> > Expired ( const CDate & expDate ) const
        {
            list< pair<string, int> > expiredGoods;
        
            for ( map<string, CGood>::const_iterator good = m_Goods.cbegin();
                  good != m_Goods.cend();
                  good ++ )
            {
                string name = good -> first;
                int amount = 0;
                
                for ( map<CDate, int>::const_iterator date = good->second . m_Dates.cbegin();
                      date != good->second . m_Dates.cend();
                      date++ )
                {
                    if ( date -> first < expDate )
                        amount += date -> second;
                }
                
                if ( amount )
                {
                    expiredGoods.push_back( make_pair( name, amount ) );
                }
            }
            expiredGoods.sort( [] ( pair<string, int> & p1, pair<string, int> & p2 ) -> bool
                                {
                                    if ( p1.second < p2.second ) return false;
                                    return true;
                                } );
            return expiredGoods;
        }
    
};

#ifndef __PROGTEST__
int main ( void )
{
    CSupermarket s;
    s . Store ( "bread", CDate ( 2016, 4, 30 ), 100 ) .
        Store ( "butter", CDate ( 2016, 5, 10 ), 10 ) .
        Store ( "beer", CDate ( 2016, 8, 10 ), 50 ) .
        Store ( "bread", CDate ( 2016, 4, 25 ), 100 ) .
        Store ( "okey", CDate ( 2016, 7, 18 ), 5 );
    
    list<pair<string,int> > l0 = s . Expired ( CDate ( 2018, 4, 30 ) );
    assert ( l0 . size () == 4 );
    assert ( ( l0 == list<pair<string,int> > { { "bread", 200 }, { "beer", 50 }, { "butter", 10 }, { "okey", 5 } } ) );
    
    list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
    s . Sell ( l1 );
    assert ( l1 . size () == 2 );
    assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );
    
    list<pair<string,int> > l2 = s . Expired ( CDate ( 2016, 4, 30 ) );
    assert ( l2 . size () == 1 );
    assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );
    
    list<pair<string,int> > l3 = s . Expired ( CDate ( 2016, 5, 20 ) );
    assert ( l3 . size () == 1 );
    assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );
    
    list<pair<string,int> > l4 { { "bread", 105 } };
    s . Sell ( l4 );
    assert ( l4 . size () == 0 );
    assert ( ( l4 == list<pair<string,int> > {  } ) );
    
    list<pair<string,int> > l5 = s . Expired ( CDate ( 2017, 1, 1 ) );
    assert ( l5 . size () == 3 );
    assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );
    
    s . Store ( "Coke", CDate ( 2016, 12, 31 ), 10 );
    
    list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
    s . Sell ( l6 );
    assert ( l6 . size () == 3 );
    assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );
    
    list<pair<string,int> > l7 = s . Expired ( CDate ( 2017, 1, 1 ) );
    assert ( l7 . size () == 4 );
    assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );
    
    s . Store ( "cake", CDate ( 2016, 11, 1 ), 5 );
    
    list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
    s . Sell ( l8 );
    assert ( l8 . size () == 2 );
    assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );
    
    list<pair<string,int> > l9 = s . Expired ( CDate ( 2017, 1, 1 ) );
    assert ( l9 . size () == 5 );
    assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );
    
    list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
    s . Sell ( l10 );
    assert ( l10 . size () == 2 );
    assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );
    
    list<pair<string,int> > l11 = s . Expired ( CDate ( 2017, 1, 1 ) );
    assert ( l11 . size () == 4 );
    assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );
    
    list<pair<string,int> > l12 { { "Cake", 4 } };
    s . Sell ( l12 );
    assert ( l12 . size () == 0 );
    assert ( ( l12 == list<pair<string,int> > {  } ) );
    
    list<pair<string,int> > l13 = s . Expired ( CDate ( 2017, 1, 1 ) );
    assert ( l13 . size () == 4 );
    assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );
    
    list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
    s . Sell ( l14 );
    assert ( l14 . size () == 1 );
    assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );
    
    return 0;
}
#endif /* __PROGTEST__ */
