#include <iostream>
#include <cmath>

using namespace std;

#define DEBUG_DU2

uint64_t extractID( uint64_t mask );

// ******************************************************************************************************

class Number
{
    public:
        Number              ( uint32_t id, uint32_t s ) : id(id),
                                                          strength(s) {}
        Number              ( ) : id(0), strength(0) {}
        Number              ( uint64_t n )
        {
            id = 0;
            if ( n == 0 )
                strength = 0;
            else
                strength = ~0;
        }
        
        uint32_t        getID               ( ) const { return id; }
        bool            operator<           ( const Number & n ) const
        {
            if ( strength < n.strength )
                return true;
            if ( strength > n.strength )
                return false;
            else {
                if (id < n.id)
                    return true;
                else
                    return false;
            }
        }
        
        bool            operator>           ( const Number & n ) const
        {
            if ( strength < n.strength )
                return false;
            if ( strength > n.strength )
                return true;
            else {
                if (id < n.id)
                    return true;
                else
                    return false;
            }
        }
        
        bool            operator==          ( const Number & n ) const
        {
            if ( n.id == id && n.strength == strength )
                return true;
            else
                return false;
        }
        
        friend ostream & operator<< ( ostream & s, const Number & n );
    
    private:
        uint32_t        id;
        uint32_t        strength;
};

ostream & operator<< ( ostream & s, const Number & n )
{
    s << n.strength << "(" << n.id << ")";
    return s;
}

// ******************************************************************************************************

template <typename T>
struct Node
{
    Node<T> *           parent;
    Node<T> *           child;
    Node<T> *           right;
    Node<T> *           left;
    bool                mark;
    size_t              degree;
    
    Node<T> *           mirror;
    
    T                   value;
};

// ******************************************************************************************************

typedef enum
{
    FIBONACCI_MIN_HEAP,
    FIBONACCI_MAX_HEAP
} FibonacciHeapOrder;

template <typename T>
class FibonacciTree
{
    public:
        FibonacciTree<T>        ( FibonacciHeapOrder );
        ~FibonacciTree<T>       ( );
        
        void                    concatenateWith         ( FibonacciTree<T> & );
        Node<T> *               insert                  ( const T & );
        Node<T> *               extract                 ( );
        size_t                  getSize                 ( ) const { return size; };
        void                    deleteNode              ( Node<T> *node );
    
    
    private:
        
        Node<T> *               root;
        FibonacciHeapOrder      sortOrder;
        size_t                  size;
        
        void                    addToRootList           ( Node<T> *node );
        void                    removeFromList          ( Node<T> *node );
        void                    consolidate             ( );
        void                    exchangeRootNodes       ( Node<T> *& x, Node<T> *& y );
        bool                    compareValues           ( const T &, const T & );
        void                    linkNodeToNode          ( Node<T> * child, Node<T> * parent );
        void                    decreaseKey             ( Node<T> *, T k );
        void                    cut                     ( Node<T> *, Node<T> * );
        void                    cascadingCut            ( Node<T> * );
        void                    clearTreeStructure      ( Node<T> * );
        void                    clearNeighbourhood      ( Node<T> * );
        
        void                    printTree               ( Node<T> * node, size_t level ) const;
        string                  getName                 ( ) const;
};

template <typename T>
FibonacciTree<T>::FibonacciTree( FibonacciHeapOrder a )
{
    root = nullptr;
    size = 0;
    sortOrder = a;
}

template <typename T>
FibonacciTree<T>::~FibonacciTree()
{
    //clearTreeStructure( root );
}

template <typename T>
void FibonacciTree<T>::concatenateWith( FibonacciTree<T> & t )
{
    // concatenated tree is empty
    if ( t.root == nullptr )
        return;
    
    // inserting to the left of the min
    addToRootList( t.root );
    
    if ( t.root && root && compareValues(t.root->value, root->value) )
        root = t.root;
    
    size += t.size;
    
    t.root = nullptr;
    t.size = 0;
}

template <typename T>
Node<T> * FibonacciTree<T>::insert( const T & element )
{
    Node<T> * node = new Node<T>();
    node->degree = 0;
    node->parent = nullptr;
    node->value = element;
    node->mark = false;
    node->child = nullptr;
    node->left = node;
    node->right = node;
    
    addToRootList( node );
    
    if ( compareValues(node->value, root->value) )
        root = node;
    
    size++;
#ifdef DEBUG_DU2
    cout << "INSERT( " << getName() << " ):" << endl;
    printTree( root, 0 );
#endif
    return node;
}

template <typename T>
Node<T> * FibonacciTree<T>::extract()
{
    Node<T> * z = root;
    
    if ( z != nullptr )
    {
        Node<T> * child = z->child;
        
        if ( child != nullptr )
        {
            Node<T> *nextChild = child;
            
            do
            {
                Node<T> * next = nextChild->right;
                
                removeFromList( nextChild );
                clearNeighbourhood( nextChild );
                addToRootList( nextChild );
                
                nextChild = next;
            } while ( nextChild->parent != nullptr );
        }
        
        removeFromList( z );
        z->child = nullptr;
        size--;
        
        if (z == z->right)
            root = nullptr;
        else {
            root = z->right;
            consolidate();
        }
        
        clearNeighbourhood( z );
    }
#ifdef DEBUG_DU2
    cout << "EXTRACT( " << getName() << " ):" << endl;
    printTree( root, 0 );
#endif
    return z;
}

template <typename T>
void FibonacciTree<T>::addToRootList( Node<T> *node )
{
    if ( node == nullptr )
        return;
    
    node->parent = nullptr;
    
    if ( root == nullptr )
    {
        root = node;
    } else {
        root->left->right = node->right;
        node->right->left = root->left;
        node->right = root;
        root->left = node;
    }
}

template <typename T>
void FibonacciTree<T>::removeFromList(Node<T> *node)
{
    if ( node == nullptr )
        return;
    
    if ( node->right == node )
        return;
    else if ( node->right->right == node )
    {
        Node<T> * nr = node->right;
        nr->right = nr;
        nr->left = nr;
    } else {
        node->right->left = node->left;
        node->left->right = node->right;
    }
}

template <typename T>
void FibonacciTree<T>::consolidate()
{
    if ( root == nullptr || root == root->right )
        return;
    
    size_t maxDegree = log2( size ) + 1;
    Node<T> ** A = new Node<T> * [maxDegree];
    
    for ( size_t i = 0; i < maxDegree; i++ )
        A[i] = nullptr;
    
    Node<T> * x = root;
    
    while ( true )
    {
        size_t d = x->degree;
        Node<T> * y = A[d];
        
        if ( y == x ) break;
        
        while ( A[d] != nullptr )
        {
            y = A[d];
            if ( compareValues( y->value, x->value ) )
                exchangeRootNodes(x, y);
            
            removeFromList( y );
            clearNeighbourhood( y );
            linkNodeToNode( y, x );
            A[d] = nullptr;
            d ++;
        }
        
        A[d] = x;
        x = x->right;
    }
    
    root = nullptr;
    
    for ( size_t i = 0; i < maxDegree; i++ )
    {
        if ( A[i] != nullptr )
        {
            if ( root == nullptr )
                root = A[i];
            else
            if ( compareValues( A[i]->value, root->value ) )
                root = A[i];
        }
    }
}

template <typename T>
void FibonacciTree<T>::exchangeRootNodes( Node<T> *& x, Node<T> *& y )
{
    Node<T> * lx = x->left;
    Node<T> * rx = x->right;
    Node<T> * ly = y->left;
    Node<T> * ry = y->right;
    
    if ( x->left == y )
    {
        y->right = rx;
        x->right = y;
        x->left = ly;
        y->left = x;
        
        rx->left = y;
        ly->right = x;
    } else if ( x->right == y )
    {
        x->right = ry;
        y->right = x;
        x->left = y;
        y->left = lx;
        
        lx->right = y;
        ry->left = x;
    } else
    {
        lx->right = y;
        rx->left = y;
        ly->right = x;
        ry->left = x;
        x->left = ly;
        x->right = ry;
        y->left = lx;
        y->right = rx;
    }
    
    Node<T> * t = x;
    x = y;
    y = t;
}

template <typename T>
bool FibonacciTree<T>::compareValues(const T & a, const T & b)
{
    if ( sortOrder == FIBONACCI_MIN_HEAP )
        return a < b;
    
    if ( sortOrder == FIBONACCI_MAX_HEAP )
        return a > b;
    else
        return a < b;
}

template <typename T>
void FibonacciTree<T>::deleteNode( Node<T> *node )
{
    T newValue;
    if ( sortOrder == FIBONACCI_MIN_HEAP )
        newValue = T(0);
    else
        newValue = T(~0);
    
    decreaseKey( node, newValue );
    Node<T> * n = extract();
    delete n;
}

template <typename T>
void FibonacciTree<T>::linkNodeToNode( Node<T> * child, Node<T> * parent )
{
    if ( parent->child == nullptr )
    {
        parent->child = child;
        clearNeighbourhood( child );
    }
    else
    {
        Node<T> * existingChild = parent->child;
        Node<T> * exChLeft = existingChild->left;
        
        child->left = exChLeft;
        exChLeft->right = child;
        existingChild->left = child;
        child->right = existingChild;
    }
    
    child->parent = parent;
    parent->degree++;
    child->mark = false;
}

template <typename T>
void FibonacciTree<T>::decreaseKey(Node<T> * x, T k)
{
    if ( x == nullptr )
        return;
    
    if ( compareValues( x->value, k ) )
        return;
    
    x->value = k;
    Node<T> * y = x->parent;
    
    if ( y != nullptr )
    {
        cut( x, y );

#ifdef DEBUG_DU2
        cout << "BEFORE CASCADING:( " << getName() << " ):" << endl;
        printTree( root, 0 );
#endif
        
        cascadingCut( y );

#ifdef DEBUG_DU2
        cout << "AFTER CASCADING:( " << getName() << " ):" << endl;
        printTree( root, 0 );
#endif
    }
    
    if ( compareValues(x->value, root->value) )
        root = x;
}

template <typename T>
void FibonacciTree<T>::cut( Node<T> * x, Node<T> * y )
{
    if ( x == nullptr || y == nullptr )
        return;
    
    if ( x->right == x )
    {
        y->child = nullptr;
    }
    else if ( y->child == x )
        y->child = x->right;
    
    removeFromList( x );
    clearNeighbourhood( x );
    addToRootList( x );
    
    y->degree--;
    x->mark = false;
}

template <typename T>
void FibonacciTree<T>::cascadingCut(Node<T> * y)
{
    if ( y == nullptr )
        return;
    
    Node<T> * z = y->parent;
    if ( z != nullptr )
    {
        if ( ! y->mark )
            y->mark = true;
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template <typename T>
void FibonacciTree<T>::clearTreeStructure( Node<T> * node )
{
    if ( node == nullptr ) return;
    
    Node<T> * n = node;
    //node->left->right = nullptr;
    
    do
    {
        Node<T> * d = n;
        n = n->right;
        clearTreeStructure(d->child);
        delete d;
    } while ( n != node );
    
}

template <typename T>
void FibonacciTree<T>::printTree( Node<T> * node, size_t level ) const
{
    if ( node == nullptr )
        return;
    
    Node<T> * n = node;
    
    do
    {
        for ( size_t i = 0; i < level; i++ )
            cout << "    ";
        
        cout << n->value;
        
        if ( n == root )
            cout << "(!)";
        
        //cout << " [ " << n << " ]";
        cout << endl;
        
        printTree( n->child, level + 1 );
        
        n = n->right;
    } while ( n != node );
}

template <typename T>
string FibonacciTree<T>::getName() const
{
    if ( sortOrder == FIBONACCI_MAX_HEAP )
        return "Max Tree";
    else
        return "Min Tree";
}

template <typename T>
void FibonacciTree<T>::clearNeighbourhood(Node<T> * n)
{
    n->right = n;
    n->left = n;
}

// ******************************************************************************************************

template <typename T>
class FibonacciMinMax
{
    public:
        FibonacciMinMax<T>      ( );
        
        void                    merge                   ( FibonacciMinMax<T> & );
        void                    insert                  ( const T & );
        T                       extractMin              ( );
        T                       extractMax              ( );
    
    private:
        FibonacciTree<T>        minTree;
        FibonacciTree<T>        maxTree;
        
        T                       extract                 ( FibonacciTree<T> * );
        void                    p                       ();
};

template <typename T>
FibonacciMinMax<T>::FibonacciMinMax() : minTree( FibonacciTree<T>( FIBONACCI_MIN_HEAP ) ),
                                        maxTree( FibonacciTree<T>( FIBONACCI_MAX_HEAP ) ) {}

template <typename T>
void FibonacciMinMax<T>::merge( FibonacciMinMax<T> & t )
{
    minTree.concatenateWith( t.minTree );
    maxTree.concatenateWith( t.maxTree );
}

template <typename T>
void FibonacciMinMax<T>::insert( const T & v )
{
    Node<T> * min = minTree.insert( v );
    Node<T> * max = maxTree.insert( v );
    
    min->mirror = max;
    max->mirror = min;
}

template <typename T>
T FibonacciMinMax<T>::extractMax()
{
    return extract( &maxTree );
}

template <typename T>
T FibonacciMinMax<T>::extractMin()
{
    return extract( &minTree );
}

template <typename T>
T FibonacciMinMax<T>::extract( FibonacciTree<T> * t )
{
    Node<T> * el = (*t).extract();
    if ( el == nullptr )
        return T(0);
    
    T v = el->value;
    
    if ( t == &maxTree )
        minTree.deleteNode( el->mirror );
    else
        maxTree.deleteNode( el->mirror );
    
    delete el;
    return v;
}

// ******************************************************************************************************

uint64_t makeID( uint64_t id, uint64_t s )
{
    uint64_t sn = s << 32;
    uint64_t idn = ~((uint32_t) 0) - id;
    uint64_t n = sn + idn;
    
    return n;
}

uint64_t extractID( uint64_t mask )
{
    uint64_t lastOnes = ~((uint32_t) 0);
    uint64_t id = ~((uint32_t) 0) - (mask & lastOnes);
    //uint64_t st = mask >> 32;
    
    return id;
}

void test()
{
    int testID = 2;
    
    if ( testID == 0 )
    {
        FibonacciMinMax<uint> k = FibonacciMinMax<uint>( );
        for ( int i = 1; i <= 120; i++ )
            k.insert( i );
        
        for ( int i = 0; i < 60; i ++ )
        {
            cout << "ExtractMin: \n" << endl;
            uint n = k.extractMin();
            cout << "OUT: " << n << endl;
            
            cout << "ExtractMax: \n" << endl;
            n = k.extractMax();
            cout << "OUT: " << n << endl;
        }
    } else if ( testID == 1 )
    {
        FibonacciTree<uint> k = FibonacciTree<uint>( FIBONACCI_MIN_HEAP );
        for ( uint i = 0; i < 100; i++ )
            k.insert( i );
        
        for ( uint i = 0; i < 120; i++ )
        {
            delete k.extract();
        }
        
        for ( uint i = 0; i < 100; i++ )
            k.insert( i );
        
        for ( uint i = 0; i < 50; i++ )
            delete k.extract();
        
        for ( uint i = 0; i < 100; i++ )
            k.insert( i );
        
        for ( uint i = 0; i < 120; i++ )
            delete k.extract();
        
        cout << "OUT: " << k.extract()->value << endl;
    } else if ( testID == 2 )
    {
        int count = 100;
        
        FibonacciTree<uint> k = FibonacciTree<uint>( FIBONACCI_MIN_HEAP );
        Node<uint> ** arr = new Node<uint>* [count];
        
        for ( int i = 0; i < count; i++ )
        {
            Node<uint> * n = k.insert(i+1);
            arr[i] = n;
        }
        
        cout << "\n\nDELETING NODES\n" << endl;
        
        for ( int i = count - 1; i >= 0; i-- )
        {
            k.deleteNode( arr[i] );
        }
    }
}

int main() {
    
    test();
    return 0;
    
    FibonacciMinMax<Number> * trees = new FibonacciMinMax<Number> [ 10000 ];
    
    for ( size_t i = 0; i < 10000; i++ )
        trees[i] = FibonacciMinMax<Number>();
    
    char c;
    cin >> c;
    
    while ( c != '4' )
    {
        size_t k = 0;
        cin >> k;
        //k--;
        FibonacciMinMax<Number> & tree = trees[k];
        
        if ( c == '0' )
        {
            uint32_t id = 0;
            uint32_t s = 0;
            cin >> id >> s;
            
            tree.insert( Number( id, s ) );
        }
        
        if ( c == '1' || c == '2' )
        {
            Number n = Number(0);
            
            if ( c == '1' )
            {
#ifdef DEBUG_DU2
                cout << "Trying to extract MAX from " << k << endl;
#endif
                n = tree.extractMax();
            }
            else
            {
#ifdef DEBUG_DU2
                cout << "Trying to extract MIN from " << k << endl;
#endif
                n = tree.extractMin();
            }
            
            if ( n == 0 )
                cout << "empty";
            else
            {
                uint32_t id = n.getID();

#ifdef DEBUG_DU2
                cout << "out: ";
#endif
                cout << id;
            }
            cout << endl;
        }
        
        if ( c == '3' )
        {
            uint32_t from = 0;
            cin >> from;
            
            if ( k != from )
            {
                FibonacciMinMax<Number> & fromTree = trees[from];
                tree.merge( fromTree );
            }
        }
        
        cin >> c;
    }
    
    delete [] trees;
    
    return 0;
}
