#include <iostream>
#include <sstream>

// 0b00000010 - a, 0b00000100 - b, 0b00001000 - c, 0b00000001 - x;
// 0 - wasn't here, 1x, 2a, 3b, 4c, 5ab, 6ac, 7bc, 8abc

using namespace std;

class CException {};
class CGraph;
struct CPathNode;

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

template< typename T >
class CArray
{
    public:
        friend class CGraph;

                            CArray                  ( size_t initialSize );
                            CArray                  ( CArray<T> && );
                            ~CArray                 ( );
        T &                 getElementByIndex       ( size_t index );
        size_t              insertElement           ( const T & element );
        T *                 getArrayPtr             ( );
        CArray &            operator=               ( CArray<T> && );
        size_t              size                    ( ) { return m_ElementsNumber; }

        void                clean                   ( );

    private:
        size_t              m_Size;
        size_t              m_ElementsNumber;
        T *                 m_Elements;
};

//************************************************************************************************//

template< typename T >
CArray<T>::CArray( size_t initialSize ) : m_ElementsNumber( 0 )
{
    m_Size = initialSize;
    m_Elements = new T[initialSize];
}

template< typename T >
CArray<T>::~CArray()
{
    if ( m_Elements )
        delete [] m_Elements;
}

template< typename T >
CArray<T>::CArray( CArray<T> && a )
{
    if (m_Elements)
        delete [] m_Elements;
    m_Elements = a.m_Elements;
    a.m_Elements = nullptr;
    m_Size = a.m_Size;
    m_ElementsNumber = a.m_ElementsNumber;
}

template< typename T >
T & CArray<T>::getElementByIndex( size_t index )
{
    return m_Elements[index];
}

template< typename T >
size_t CArray<T>::insertElement( const T & element )
{
    m_Elements[ m_ElementsNumber ] = element;
    return m_ElementsNumber++;
}

template< typename T >
T * CArray<T>::getArrayPtr()
{
    return m_Elements;
}

template< typename T >
CArray<T> & CArray<T>::operator= ( CArray<T> && a) {
    if ( m_Elements )
        delete [] m_Elements;
    m_Elements = a.m_Elements;
    a.m_Elements = nullptr;
    m_Size = a.m_Size;
    m_ElementsNumber = a.m_ElementsNumber;
    return *this;
}

template <typename T>
void CArray<T>::clean()
{
    if ( m_Elements )
        delete [] m_Elements;
    m_ElementsNumber = 0;
    m_Size = 0;
}

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

template <typename L, typename R>
class CPair
{
    public:
        bool                empty;
                            CPair                   () : empty(true) {};
                            CPair                   ( L l, R r ): empty(false),
                                                                  m_L( l ),
                                                                  m_R( r ) {}
        L &                 first                   () { return m_L; }
        R &                 second                  () { return m_R; }

    private:
        L                   m_L;
        R                   m_R;
};

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

struct CNode
{
    public:
        friend class CGraph;
                            CNode                   ( ) : m_CardsWeWereHereWith( 0 ),
                                                          m_CardsLayingHere( 0 ),
                                                          number( 0 ),
                                                          m_Edges( 0 ) {}

        bool                canBeExpanded           ( uint8_t mask );
        void                setNewState             ( uint8_t mask );

        uint8_t             m_CardsWeWereHereWith;
        uint8_t             m_CardsLayingHere;
        size_t              number;

        CArray<CPair<size_t, uint8_t>>              m_Edges;
};

//************************************************************************************************//

bool CNode::canBeExpanded( uint8_t mask )
{
    if ( m_CardsWeWereHereWith == 0 )
        return true;
    
    // cards we came here with
    bool a = (bool) (mask & 2);
    bool b = (bool) (mask & 4);
    bool c = (bool) (mask & 8);
    
    // There are several cases for those we were in a node:
    // abc
    if ( m_CardsWeWereHereWith & 128                                        // abc
            || (m_CardsWeWereHereWith & 64 && ((b && c && !a)              // bc
                                                       || (b && !a && !c)
                                                       || (c && !b && !a)))
            || (m_CardsWeWereHereWith & 32 && ((a && c && !b)              // ac
                                                       || (a && !b && !c)
                                                       || (c && !b && !a)))
            || (m_CardsWeWereHereWith & 16 && ((b && a && !c)              // ab
                                                        || (b && !a && !c)
                                                        || (a && !b && !c)))
            || (m_CardsWeWereHereWith & 8 && (c && !b && !a))             // c
            || (m_CardsWeWereHereWith & 4 && (b && !a && !c))             // b
            || (m_CardsWeWereHereWith & 2 && (a && !b && !c))             // a
            || (m_CardsWeWereHereWith & 1 && (!a && !b && !c)))           // x
        return false;
    return true;
}

void CNode::setNewState( uint8_t mask )
{
    bool a = (bool) (mask & 2);
    bool b = (bool) (mask & 4);
    bool c = (bool) (mask & 8);

    if ( (!a && !b && !c) ) m_CardsWeWereHereWith |= 1; // x
    if ( (a && !b && !c) )  m_CardsWeWereHereWith |= 2; // a
    if ( (b && !a && !c) )  m_CardsWeWereHereWith |= 4; // b
    if ( (c && !b && !a) )  m_CardsWeWereHereWith |= 8; // c
    if ( (a && b && !c) )   m_CardsWeWereHereWith |= 16; // ab
    if ( (a && c && !b) )   m_CardsWeWereHereWith |= 32; // ac
    if ( (c && b && !a) )   m_CardsWeWereHereWith |= 64; // bc
    if ( (a && b && c) )    m_CardsWeWereHereWith |= 128; // abc
}

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

class CGraph
{
    public:

                            CGraph                  ( size_t initialSize ) : m_Graph( initialSize )
                                { m_Graph.m_ElementsNumber = initialSize; };
        void                insertEdge              ( size_t from, size_t to, uint8_t mask );
        void                setEdgesNumberForNode   ( size_t nodeIndex, size_t edgesNumber );
        void                putCardOnNode           ( size_t nodeIndex, uint8_t cardsMask );
        size_t              getIndexByNode          ( CNode * n );
        CNode *             getNodeByIndex          ( size_t i );

    private:

        CArray<CNode>       m_Graph;
};

//************************************************************************************************//

void CGraph::insertEdge( size_t from, size_t to, uint8_t mask )
{
    CNode & nodeFrom = m_Graph.getElementByIndex(from);
    CPair<size_t, uint8_t> p = CPair<size_t, uint8_t>( to, mask );
    nodeFrom.m_Edges.insertElement( p );
}

void CGraph::setEdgesNumberForNode(size_t nodeIndex, size_t edgesNumber)
{
    CNode & n = m_Graph.getElementByIndex( nodeIndex );
    n.m_Edges = CArray<CPair<size_t, uint8_t>> ( edgesNumber );
}

void CGraph::putCardOnNode(size_t nodeIndex, uint8_t cardsMask)
{
    m_Graph.getElementByIndex(nodeIndex).m_CardsLayingHere |= cardsMask;
}

size_t CGraph::getIndexByNode(CNode *n)
{
    return n - m_Graph.getArrayPtr();
}

CNode *CGraph::getNodeByIndex(size_t i)
{
    return m_Graph.getArrayPtr() + i;
}

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

struct CPathNode
{
    size_t              number;
    CPathNode *         previousNode;
    uint8_t             cards;
    size_t              level;
    size_t              chNum;
};

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

template <typename T>
class CQueue
{
    public:
        bool                isEmpty;

                            CQueue<T>               ( ) : isEmpty( true ),
                                                          size( 0 ),
                                                          m_Queue( nullptr ),
                                                          m_Last( nullptr ),
                                                          m_First( nullptr ) {}
                            ~CQueue                 ( );
        T                   pop                     ( );
        void                push                    ( const T & );
        void                deleteContent           ( );

        size_t              size;

    private:

        struct CWrapper
        {
                            CWrapper() : m_Node(),
                                         m_Next( nullptr ) {}
                void        set( const T &, CWrapper * next );
                T           m_Node;
                CWrapper *  m_Next;
        };
        CWrapper *          m_Queue;
        CWrapper *          m_Last;
        CWrapper *          m_First;
};

//************************************************************************************************//

template< typename T >
void CQueue<T>::CWrapper::set(const T & node, CWrapper *next)
{
    m_Node = node;
    m_Next = next;
}

template< typename T >
T CQueue<T>::pop()
{
    if ( isEmpty ) throw CException();
    CWrapper * w = m_Queue;
    m_Queue = w->m_Next;

    if ( ! m_Queue )
    {
        isEmpty = true;
        //m_Last = nullptr;
    }

    T n = w -> m_Node;
    size--;
    return n;
}

template< typename T >
void CQueue<T>::push( const T & n )
{
    CWrapper * w = new CWrapper();
    w->set( n, nullptr );

    if ( isEmpty )
    {
        isEmpty = false;
        m_Queue = w;

        if ( m_Last )
            m_Last->m_Next = w;

        m_Last = w;

        if ( !m_First )
            m_First = w;

    } else {
        m_Last->m_Next = w;
        m_Last = w;
    }
    size++;
}

template< typename T >
CQueue<T>::~CQueue()
{
    while ( m_First )
    {
        CWrapper * w = m_First;
        m_First = w->m_Next;
        delete w;
    }
}

template< typename T >
void CQueue<T>::deleteContent()
{
    CWrapper * w = m_First;
    while ( w )
    {
        delete w->m_Node;
        w = w->m_Next;
    }
}



//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

uint8_t cardCharToMask( char card )
{
    uint8_t cardsMask;

    switch ( card )
    {
        case 'a': cardsMask = 2;
            break;
        case 'b': cardsMask = 4;
            break;
        case 'c': cardsMask = 8;
            break;
        case 'x': cardsMask = 1;
            break;
        default:  cardsMask = 0;
            break;
    }

    return cardsMask;
}

//************************************************************************************************//

void loadGraph( istream & stream, CGraph & graph, size_t n )
{
    // reading all nodes
    for ( size_t i = 0; i < n; i++ )
    {
        size_t edgesNumber;
        stream >> edgesNumber;
        graph.setEdgesNumberForNode( i, edgesNumber );
        graph.getNodeByIndex( i )->number = i;

        for ( size_t j = 0; j < edgesNumber; j++ )
        {
            size_t node;
            char card;
            uint8_t cardsMask;
            stream >> node >> card;
            cardsMask = cardCharToMask( card );
            graph.insertEdge( i, node, cardsMask );
        }
    }

    size_t cardsNumber;
    stream >> cardsNumber;

    for ( size_t i = 0; i < cardsNumber; i++ )
    {
        size_t nodeIndex;
        char card;
        stream >> nodeIndex >> card;
        uint8_t cardsMask = cardCharToMask( card );
        graph.putCardOnNode( nodeIndex, cardsMask );
    }
}
//************************************************************************************************//

CPathNode * finishLeaf = nullptr;

//************************************************************************************************//

bool expand( CQueue<CPathNode *> & q, CGraph & g, size_t finish )
{
    if ( q.isEmpty )
        return false;

    CPathNode * p = q.pop();
    CNode * node = g.getNodeByIndex( p->number );

    for ( size_t i = 0; i < node->m_Edges.size(); i++ )
    {
        CPair<size_t,uint8_t> & pair = node->m_Edges.getElementByIndex(i);
        CNode * toExpand = g.getNodeByIndex(pair.first());

        if ( toExpand->canBeExpanded( p->cards ) && p->cards & pair.second() )
        {
            CPathNode * leaf = new CPathNode();
            q.push( leaf );

            leaf->cards = toExpand->m_CardsLayingHere | p->cards;
            toExpand->setNewState( leaf->cards );

            leaf->number = pair.first();
            leaf->chNum = 0;
            leaf->level = p->level + 1;
            leaf->previousNode = p;

            if ( leaf->number == finish )
            {
                finishLeaf = leaf;
                return true;
            }
        }
    }

    return false;
}

//************************************************************************************************//

void printPath(CPathNode *node)
{
    if ( ! node )
        return;

    size_t level = node->level;

    size_t * arr = new size_t[level];

    cout << level - 1 << endl;

    while ( node )
    {
        arr[node->level - 1] = node->number;
        node = node->previousNode;
    }

    for ( size_t i = 0; i < level; i++ )
    {
        cout << arr[i];
        if ( i < level - 1 )
            cout << " ";
    }

    cout << endl;

    delete [] arr;
}

//************************************************************************************************//

bool nrBFS( size_t start, uint8_t cardsWeHave, size_t finish, CGraph & graph )
{
    CQueue<CPathNode *> queue = CQueue<CPathNode *> ();
    CPathNode * root = new CPathNode();
    queue.push( root );
    CNode * startNode = graph.getNodeByIndex( start );

    cardsWeHave |= startNode->m_CardsLayingHere;
    
    root->number = start;
    root->cards = cardsWeHave;
    root->chNum = 0;
    root->level = 1;
    root->previousNode = nullptr;

    bool found = false;

    while ( !found && !queue.isEmpty )
        if ( expand( queue, graph, finish ) )
            found = true;

    if ( found )
    {
        printPath(finishLeaf);
        queue.deleteContent();
        return true;
    }
    else
    {
        queue.deleteContent();
        cout << "No solution" << endl;
        return false;
    }
}

//************************************************************************************************//

int main() {
    size_t n, start, finish;

    // reading the first line
    cin >> n >> start >> finish;
    if ( start == finish )
    {
        cout << "0\n" << start << endl;
        return 0;
    }

    CGraph graph( n );
    loadGraph( cin, graph, n );

    CQueue<size_t> queue = CQueue<size_t>();
    queue.push( start );
    uint8_t cardsWeHave = 1;
    nrBFS( start, cardsWeHave, finish, graph );

    return 0;
}
