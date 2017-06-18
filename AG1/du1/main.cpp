#include <iostream>

// 0b00000010 - a, 0b00000100 - b, 0b00001000 - c, 0b00000001 - x;

using namespace std;

class CException {};
class CGraph;

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

template< typename T >
class CArray
{
    public:

                            CArray                  ( size_t initialSize );
                            CArray                  ( CArray && );
                            ~CArray                 ( );
        T &                 getElementByIndex       ( size_t index );
        size_t              insertElement           ( const T & element );
        T *                 getArrayPtr             ( );
        CArray &            operator=               ( CArray && );
        //bool                isEmpty                 ( ) { return (bool) m_Size; }
        size_t              size                    ( ) { return m_ElementsNumber; }

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
CArray<T>::CArray( CArray && a )
{
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
CArray<T> & CArray<T>::operator= ( CArray && a) {
    delete [] m_Elements;
    m_Elements = a.m_Elements;
    a.m_Elements = nullptr;
    m_Size = a.m_Size;
    m_ElementsNumber = a.m_ElementsNumber;
    return *this;
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
                            CPair                   ( L l, R r ): empty(false), m_L( l ), m_R( r ) {}
        L &                 first                   () { return m_L; }
        R &                 second                  () { return m_R; }

    private:
        L                   m_L;
        R                   m_R;
};

//template< typename T >
//class CList
//{
//    public:
//                            CList                   ( );
//                            ~CList                  ( );
//        T &                 push                    ( T & );
//        size_t              getElementsNumber       ( ) { return m_ElementsNumber; }
//        T &                 getNext                 ( );
//    private:
//        size_t              m_ElementsNumber;
//        T *                 m_First;
//        T *                 m_Last;
//};

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

struct CNode
{
    public:
        friend class CGraph;
                            CNode                   ( ) : m_CardsWeWereHereWith( 0 ),
                                                          m_CardsLayingHere( 0 ),
                                                          m_Edges( 0 ) {}
        void                putCard                 ( int8_t cardsMask ) { m_CardsLayingHere |= cardsMask; }
        void                addState                ( int8_t cardsMask ) { m_CardsWeWereHereWith |= cardsMask; }
        int8_t              hasCards                ( ) { return m_CardsLayingHere; }
        bool                canBeExpanded           ( int8_t cardsMask );

        int8_t              m_CardsWeWereHereWith;
        int8_t              m_CardsLayingHere;
        CArray<CPair<size_t, int8_t>>               m_Edges;

    private:


};

//************************************************************************************************//

bool CNode::canBeExpanded( int8_t cardsMask )
{
    return cardsMask != m_CardsWeWereHereWith;
}

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

class CGraph
{
    public:

                            CGraph                  ( size_t initialSize ) : m_Graph( initialSize ) {};
        void                insertEdge              ( size_t from, size_t to, int8_t mask );
        void                setEdgesNumberForNode   ( size_t nodeIndex, size_t edgesNumber );
        void                putCardOnNode           ( size_t nodeIndex, int8_t cardsMask );
        size_t              getIndexByNode          ( CNode * n );
        CNode *             getNodeByIndex          ( size_t i );

    private:

        CArray<CNode>       m_Graph;
};

//************************************************************************************************//

void CGraph::insertEdge( size_t from, size_t to, int8_t mask )
{
    CNode & nodeFrom = m_Graph.getElementByIndex(from);
    CPair<size_t, int8_t> p = CPair<size_t, int8_t>( to, mask );
    nodeFrom.m_Edges.insertElement( p );
}

void CGraph::setEdgesNumberForNode(size_t nodeIndex, size_t edgesNumber)
{
    CNode & n = m_Graph.getElementByIndex( nodeIndex );
    n.m_Edges = CArray<CPair<size_t, int8_t>> ( edgesNumber );
}

void CGraph::putCardOnNode(size_t nodeIndex, int8_t cardsMask)
{
    m_Graph.getElementByIndex(nodeIndex).putCard( cardsMask );
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

class CQueue
{
    public:
        bool                isEmpty;

                            CQueue() : isEmpty( true ), m_Queue( nullptr ), m_Last( nullptr ) {}
        CNode *             pop                     ( );
        void                push                    ( CNode * );

    private:

        struct CWrapper
        {
                            CWrapper() : m_Node( nullptr ), m_Next( nullptr ) {}
                void        set( CNode * node, CWrapper * next );
                CNode *     m_Node;
                CWrapper *  m_Next;
        };
        CWrapper *          m_Queue;
        CWrapper *          m_Last;
};

//************************************************************************************************//

void CQueue::CWrapper::set(CNode *node, CWrapper *next)
{
    m_Node = node;
    m_Next = next;
}

CNode * CQueue::pop()
{
    if ( isEmpty ) throw CException();
    CWrapper * w = m_Queue;
    m_Queue = w->m_Next;

    if ( ! m_Queue )
    {
        isEmpty = true;
        m_Last = nullptr;
    }

    CNode * n = w -> m_Node;
    delete w;
    return n;
}

void CQueue::push( CNode * n )
{
    isEmpty = false;
    CWrapper * w = new CWrapper();
    w->set( n, nullptr );

    if ( !m_Last )
    {
        m_Last = w;
        m_Queue = w;
    } else {
        m_Last ->m_Next = w;
    }
}

//************************************************************************************************//
//************************************************************************************************//
//************************************************************************************************//

class CMan
{
    public:
        size_t              start;
        size_t              finish;

                            CMan(  ) : m_HaveCards( 1 ) {}
        void                giveCards( int8_t cardsMask ) { m_HaveCards |= cardsMask; };
        bool                hasCards( int8_t cardsMask ) { return m_HaveCards & cardsMask; };

    private:
        int8_t              m_HaveCards;
};

int8_t cardCharToMask( char card )
{
    int8_t cardsMask;

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

CArray<size_t> path(0);

bool BFS( CQueue & queue, size_t length, int8_t cardsWeHave, size_t finish, CGraph & graph )
{
    // Check if not a finish
    // collect cards from the pop() node
    // change state of the popped node
    // check all the chlidren
    // add to the queue canBeExpanded children
    // run itself

    if (queue.isEmpty)
        return false;

    CNode * node = queue.pop();
    if ( finish == graph.getIndexByNode(node) )
    {
        // write to the path array
        path = CArray<size_t> (length + 1);
        path.insertElement( graph.getIndexByNode( node ) );
        return true;
    }

    cardsWeHave |= node->hasCards();
    node->addState( cardsWeHave );

    for ( size_t i = 0; i < node->m_Edges.size(); i++ )
    {
        CPair<size_t,int8_t> & p = node->m_Edges.getElementByIndex(i);
        if ( node->m_CardsWeWereHereWith != cardsWeHave && cardsWeHave & p.second() )
            queue.push( graph.getNodeByIndex( p.first() ) );
    }

    if ( !BFS( queue, length+1, cardsWeHave, finish, graph ) )
        return false;
    else
    {
        path.insertElement( graph.getIndexByNode( node ) );
        return true;
    }
}

void loadGraph( istream & stream, CGraph & graph, size_t n )
{
    // reading all nodes
    for ( size_t i = 0; i < n; i++ )
    {
        size_t edgesNumber;
        stream >> edgesNumber;
        graph.setEdgesNumberForNode( i, edgesNumber );

        for ( size_t j = 0; j < edgesNumber; j++ )
        {
            size_t node;
            char card;
            int8_t cardsMask;
            stream >> node >> card;
            cardsMask = cardCharToMask( card );
            graph.insertEdge( i, j, cardsMask );
        }
    }

    size_t cardsNumber;
    stream >> cardsNumber;

    for ( size_t i = 0; i < cardsNumber; i++ )
    {
        size_t nodeIndex;
        char card;
        stream >> nodeIndex >> card;
        int8_t cardsMask = cardCharToMask( card );
        graph.putCardOnNode( nodeIndex, cardsMask );
    }
}

int main() {
    size_t n, start, finish;

    // reading the first line
    cin >> n >> start >> finish;
    CGraph graph( n );
    loadGraph( cin, graph, n );

    CQueue queue = CQueue();
    queue.push( graph.getNodeByIndex( start ) );
    int8_t cardsWeHave = 1;
    if ( BFS( queue, 0, cardsWeHave, finish, graph ) )
    {
        for ( size_t i = path.size(); i > 0; i-- )
        {
            cout << path.getElementByIndex( i ) << ' ';
        }
        cout << path.getElementByIndex( 0 ) << endl;
    }
    else
    {
        cout << "No solution" << endl;
    }
    return 0;
}
