#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#endif /* C++ 11 */

using namespace std;
#endif /* __PROGTEST__ */

class NoRouteException 
{ 
};

template <typename _T, typename _E>
class CRoute
{
private:
    struct CNode
    {
        CNode( const _T & n ) : m_Node( n ), m_MyConnections(0) ,m_PosInArray(0) {}
        _T m_Node;
        vector< pair< size_t, size_t> > m_MyConnections;
        
        size_t m_PosInArray;
        
        bool operator< ( const CNode & ot ) const
        {
            return m_Node < ot.m_Node;
        }
        bool operator<= ( const CNode & ot ) const
        {
            return m_Node <= ot.m_Node;
        }
        bool operator> ( const CNode & ot ) const
        {
            return m_Node > ot.m_Node;
        }
        bool operator>= ( const CNode & ot ) const
        {
            return m_Node >= ot.m_Node;
        }
        bool operator== ( const CNode & ot ) const
        {
            return m_Node == ot.m_Node;
        }
        bool operator!= ( const CNode & ot ) const
        {
            return m_Node != ot.m_Node;
        }
        
        void addConnection( size_t edgeIndex,
                            size_t nodeIndex )
        {
            pair< size_t, size_t > newPair( edgeIndex, nodeIndex );
            m_MyConnections.push_back( newPair );
        }
    };
    
    vector<CNode> m_Nodes;
    set<CNode> m_NodesSet;
    vector<_E> m_Edges;
    
public:
    CRoute() {}
    CRoute & Add( const _T & n1, const _T & n2, const _E e )
    {
        if ( n1 == n2 ) return *this;
        m_Edges.push_back( e );
        typename vector<_E>::const_iterator edge = m_Edges.cend() - 1;
        CNode cn1 = CNode( n1 );
        CNode cn2 = CNode( n2 );
        auto cn1set = m_NodesSet.insert( cn1 );
        auto cn2set = m_NodesSet.insert( cn2 );
        CNode * nodeInSet1 = const_cast<CNode *>( &(*(cn1set.first)) );
        CNode * nodeInSet2 = const_cast<CNode *>( &(*(cn2set.first)) );
        typename vector<CNode>::const_iterator node1, node2;
        
        if ( cn1set.second )
        {
            m_Nodes.push_back( cn1 );
            nodeInSet1 -> m_PosInArray = m_Nodes.size() - 1;
        }
        if ( cn2set.second )
        {
            m_Nodes.push_back( cn2 );
            nodeInSet2 -> m_PosInArray = m_Nodes.size() - 1;
        }
        
        node1 = m_Nodes.cbegin() + nodeInSet1 -> m_PosInArray;
        node2 = m_Nodes.cbegin() + nodeInSet2 -> m_PosInArray;
        
        const_cast<CNode *> ( &(*(node1)) ) -> addConnection( edge - m_Edges.cbegin(), nodeInSet2 -> m_PosInArray );
        const_cast<CNode *> ( &(*(node2)) ) -> addConnection( edge - m_Edges.cbegin(), nodeInSet1 -> m_PosInArray );
        return *this;
    }
    
    template < typename Func >
    list<_T> Find( const _T & u1, const _T & u2, Func f ) const
    {
        if ( u1 == u2 )
        {
            list<_T> l;
            l.push_back( u1 );
            return l;
        }
        
        typename set<CNode>::const_iterator fromSet, toSet;
        
        if ( ( fromSet = m_NodesSet.find( u1 ) ) == m_NodesSet.end()
            || ( toSet = m_NodesSet.find( u2 ) ) == m_NodesSet.end() )
            throw NoRouteException();
        
        typename vector<CNode>::const_iterator from = m_Nodes.cbegin() + fromSet -> m_PosInArray;
        typename vector<CNode>::const_iterator to = m_Nodes.cbegin() + toSet -> m_PosInArray;
        
        list<_T> foundPath;
        vector< long long > ourPath( m_Nodes.size() );
        vector<bool> used( m_Nodes.size() );
        
        queue< typename vector<CNode>::const_iterator > q;
        q.push( from );
        used[ from - m_Nodes.cbegin() ] = true;
        ourPath[ from - m_Nodes.cbegin() ] = -1;
        
        bool foundFlag = false;
        
        while ( ! q.empty() )
        {
            typename vector<CNode>::const_iterator currentNode = q.front();
            pair< size_t, size_t > connection;
            q.pop();
            
            for ( size_t i = 0; i < currentNode->m_MyConnections.size(); i++ )
            {
                connection = currentNode->m_MyConnections[i];
                
                if ( ! f( m_Edges[connection.first] ) ) continue;
                
                typename vector<CNode>::const_iterator newNode = m_Nodes.cbegin() + connection.second;
                
                if ( ! used[ newNode - m_Nodes.cbegin() ] )
                {
                    used[ newNode - m_Nodes.cbegin() ] = true;
                    q.push( newNode );
                    ourPath[ newNode - m_Nodes.cbegin() ] = currentNode - m_Nodes.cbegin();
                    
                    if ( newNode == to )
                    {
                        foundFlag = true;
                        break;
                    }
                }
            }
            if ( foundFlag ) break;
        }
        
        if ( ! foundFlag )
            throw NoRouteException();
        
        long long way = to - m_Nodes.cbegin();
        while ( way != -1 )
        {
            foundPath.push_front( m_Nodes[ way ].m_Node );
            long long prevInd = ourPath[ way ];
            way = prevInd;
        }
        //foundPath.push_front( from->m_Node);
        
        return foundPath;
    }
    
    list<_T> Find( const _T & u1, const _T & u2 )
    {
        return Find(u1, u2, [] ( const _E & ) {return true;} );
    }
};

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
  public:
                             CTrain                        ( const string    & company, 
                                                             int               speed )
                             : m_Company ( company ), 
                               m_Speed ( speed ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed; 
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                             TrainFilterCompany            ( const set<string> & companies ) 
                             : m_Companies ( companies ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    { 
      return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    set <string>             m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                             TrainFilterSpeed              ( int               min, 
                                                             int               max )
                             : m_Min ( min ), 
                               m_Max ( max ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    { 
      return train . m_Speed >= m_Min && train . m_Speed <= m_Max; 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    int                      m_Min;
    int                      m_Max; 
};
//=================================================================================================
bool               NurSchnellzug                           ( const CTrain    & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
static string      toText                                  ( const list<string> & l )
{
  ostringstream oss;
  
  auto it = l . cbegin();
  oss << *it;
  for ( ++it; it != l . cend (); ++it )
    oss << " > " << *it;
  return oss . str ();
}
//=================================================================================================
int main ( void )
{
  CRoute<string,CTrain> lines;
  
  lines . Add ( "Berlin", "Prague", CTrain ( "DB", 120 ) )
        . Add ( "Berlin", "Prague", CTrain ( "CD",  80 ) )
        . Add ( "Berlin", "Dresden", CTrain ( "DB", 160 ) )
        . Add ( "Dresden", "Munchen", CTrain ( "DB", 160 ) )
        . Add ( "Munchen", "Prague", CTrain ( "CD",  90 ) )
        . Add ( "Munchen", "Linz", CTrain ( "DB", 200 ) )
        . Add ( "Munchen", "Linz", CTrain ( "OBB", 90 ) )
        . Add ( "Linz", "Prague", CTrain ( "CD", 50 ) )
        . Add ( "Prague", "Wien", CTrain ( "CD", 100 ) )
        . Add ( "Linz", "Wien", CTrain ( "OBB", 160 ) )
        . Add ( "Paris", "Marseille", CTrain ( "SNCF", 300 ))
        . Add ( "Paris", "Dresden",  CTrain ( "SNCF", 250 ) );
        
  list<string> r1 = lines . Find ( "Berlin", "Linz" );
  assert ( toText ( r1 ) == "Berlin > Prague > Linz" );
  
  list<string> r2 = lines . Find ( "Linz", "Berlin" );
  assert ( toText ( r2 ) == "Linz > Prague > Berlin" );

  list<string> r3 = lines . Find ( "Wien", "Berlin" );
  assert ( toText ( r3 ) == "Wien > Prague > Berlin" );

  list<string> r4 = lines . Find ( "Wien", "Berlin", NurSchnellzug );
  assert ( toText ( r4 ) == "Wien > Linz > Munchen > Dresden > Berlin" );

  list<string> r5 = lines . Find ( "Wien", "Munchen", TrainFilterCompany ( set<string> { "CD", "DB" } ) );
  assert ( toText ( r5 ) == "Wien > Prague > Munchen" );

  list<string> r6 = lines . Find ( "Wien", "Munchen", TrainFilterSpeed ( 120, 200 ) );
  assert ( toText ( r6 ) == "Wien > Linz > Munchen" );

  list<string> r7 = lines . Find ( "Wien", "Munchen", [] ( const CTrain & x ) { return x . m_Company == "CD"; } );
  assert ( toText ( r7 ) == "Wien > Prague > Munchen" );

  list<string> r8 = lines . Find ( "Munchen", "Munchen" );
  assert ( toText ( r8 ) == "Munchen" );
  
  list<string> r9 = lines . Find ( "Marseille", "Prague" );
  assert ( toText ( r9 ) == "Marseille > Paris > Dresden > Berlin > Prague" 
           || toText ( r9 ) == "Marseille > Paris > Dresden > Munchen > Prague" );
  
  try 
  { 
    list<string> r10 = lines . Find ( "Marseille", "Prague", NurSchnellzug ); 
    assert ( "Marseille > Prague connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e ) 
  { 
  }
  
  list<string> r11 = lines . Find ( "Salzburg", "Salzburg" );
  assert ( toText ( r11 ) == "Salzburg" );

  list<string> r12 = lines . Find ( "Salzburg", "Salzburg", [] ( const CTrain & x ) { return x . m_Company == "SNCF"; }  );
  assert ( toText ( r12 ) == "Salzburg" );
 
  try 
  { 
    list<string> r13 = lines . Find ( "London", "Oxford" ); 
    assert ( "London > Oxford connection does not exist!!" == NULL );
  }
  catch ( const NoRouteException & e ) 
  { 
  }
  return 0;
}
#endif  /* __PROGTEST__ */
