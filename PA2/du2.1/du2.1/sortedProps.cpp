#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

struct CDepartment {
    string departmentName;
    vector< int > IDs;
};

struct CProperty {
    int propID;
    string name;
    string depName;
    
    bool alive;
};

class CSmallVector {
public:
    CSmallVector();
    ~CSmallVector();
    void addToList( vector<CProperty>::const_iterator & onePtr );
    unsigned int size;
    unsigned int position;
    vector<CProperty>::const_iterator * pointers;
};

class compareFunctions {
public:
    bool operator() ( const CDepartment & d1, const string & d2 )
    {
        return d1.departmentName < d2;
    }
    bool operator() ( const CProperty & d1, const int & d2 )
    {
        return d1.propID < d2;
    }
    bool operator() ( const int & d1, const int & d2 ) {
        return d1 < d2;
    }
};

class CPropList
{
public:
    CPropList();
    
    void addToList( vector<CProperty>::const_iterator onePtr );
    int    InvID( void ) const;
    string Name( void ) const;
    int    Remains( void ) const;
    void   Next( void );
private:
    CSmallVector pointers;
    int curIndex;
};

class CInventory
{
public:
    CInventory( void );
    ~CInventory( void );

#if defined (__cplusplus) && __cplusplus > 199711L  /* C++ 11 */
    // copying is not required / tested
    CInventory ( const CInventory& src ) = delete;
    CInventory & operator = ( const CInventory& src ) = delete;
#endif /* C++ 11 */
    
    bool AddProp( int invID,
                 const string & name,
                 const string & deptName,
                 const string & city,
                 const string & country );
    bool DelProp( int invID );
    bool Transfer( int invID,
                  const string & deptName,
                  const string & city,
                  const string & country );
    CPropList PropList( const string & deptName,
                       const string & city,
                       const string & country ) const;
    int PropCount( const string & deptName,
                  const string & city,
                  const string & country ) const;
    
    vector< CDepartment > departments;
    vector< CProperty > properties;
private:
    
    //int deleteCounter;
    
    
};

// ************************************************************************** //
// ----------------------------- Implementation ----------------------------- //
// ************************************************************************** //

//----------------------------------------------------------------------------//
// ------------------------------ CSmallVector ------------------------------ //
//----------------------------------------------------------------------------//

CSmallVector::CSmallVector() : size( 1000 ),
                              position( 0 )
{
    
    CSmallVector::pointers = (vector<CProperty>::const_iterator *) malloc( CSmallVector::size * sizeof( vector<CProperty>::const_iterator ) );
}

CSmallVector::~CSmallVector() {
    free( CSmallVector::pointers );
}

void CSmallVector::addToList( vector<CProperty>::const_iterator & onePtr ) {
    if ( CSmallVector::position + 1 == CSmallVector::size )
    {
        CSmallVector::size += 1000;
        CSmallVector::pointers = (vector<CProperty>::const_iterator *)
            realloc(CSmallVector::pointers, CSmallVector::size * sizeof( vector<CProperty>::const_iterator ) );
    }
    
    CSmallVector::pointers[CSmallVector::position ++] = onePtr;
}

//----------------------------------------------------------------------------//
// -------------------------------- CPropList ------------------------------- //
//----------------------------------------------------------------------------//

CPropList::CPropList() : curIndex( 0 ) {}

void CPropList::Next() {
    CPropList::curIndex++;
}

int CPropList::Remains() const {
    return (int)(CPropList::pointers.position - CPropList::curIndex);
}

string CPropList::Name() const {
    return CPropList::pointers.pointers[ CPropList::curIndex ] -> name;
}

int CPropList::InvID() const {
    return CPropList::pointers.pointers[ CPropList::curIndex ] -> propID;
}

void CPropList::addToList( vector<CProperty>::const_iterator onePtr ) {
    CPropList::pointers.addToList( onePtr );
}

//----------------------------------------------------------------------------//
// ------------------------------- CInventory ------------------------------- //
//----------------------------------------------------------------------------//

CInventory::CInventory( void ) {}
CInventory::~CInventory( void ) {}

bool CInventory::AddProp( int invID,
             const string & name,
             const string & deptName,
             const string & city,
             const string & country )
{
    string fullName = country + "$$$" + city + "$$$" + deptName;
    
    // Searching for the property or setting a new one up
    if ( CInventory::properties.size() != 0 )
    {
        std::vector<CProperty>::iterator prop;
        prop = lower_bound(CInventory::properties.begin(), CInventory::properties.end(), invID, compareFunctions());
        
        if ( prop != CInventory::properties.end() ) {
            if ( prop->propID == invID && prop->alive ) return false;
            
            if ( prop->propID == invID )
            {
                prop->name = name;
                prop->depName = fullName;
                prop->alive = true;
            } else {
                CProperty a;
                a.name = name;
                a.propID = invID;
                a.depName = fullName;
                a.alive = true;
                CInventory::properties.insert( prop, a );
            }
        } else {
            CProperty a;
            a.name = name;
            a.propID = invID;
            a.depName = fullName;
            a.alive = true;
            CInventory::properties.push_back( a );
        }
        
    } else {
        CProperty a;
        a.name = name;
        a.propID = invID;
        a.depName = fullName;
        a.alive = true;
        CInventory::properties.push_back( a );
    }
    
    std::vector<CDepartment>::iterator dep;
    
    // Searching for the department
    if ( CInventory::departments.size() != 0 )
    {
        dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
        
        if ( dep != CInventory::departments.end() )
        {
            if ( dep->departmentName != fullName )
            {
                CDepartment a;
                a.departmentName = fullName;
                CInventory::departments.insert(dep, a);
                dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
            }
        } else {
            CDepartment a;
            a.departmentName = fullName;
            CInventory::departments.push_back(a);
            dep = CInventory::departments.end() - 1;
        }
    } else {
        CDepartment a;
        a.departmentName = fullName;
        CInventory::departments.push_back(a);
        dep = CInventory::departments.end() - 1;
    }
    
    // Attaching our new property to the department
    vector<int>::iterator ind = lower_bound( dep->IDs.begin(), dep->IDs.end(), invID );
    dep->IDs.insert( ind, invID );
    
    
    return true;
}

//----------------------------------------------------------------------------//

bool CInventory::DelProp( int invID )
{
    std::vector<CProperty>::iterator prop;
    prop = lower_bound(CInventory::properties.begin(), CInventory::properties.end(), invID, compareFunctions());
    
    if ( CInventory::properties.size() == 0
        || prop == CInventory::properties.end()
        || prop->propID != invID
        || ! prop->alive ) return false;
    
    string depName = prop->depName;
    
    vector< CDepartment >::iterator dep;
    dep = lower_bound( CInventory::departments.begin(), CInventory::departments.end(), depName, compareFunctions());
    
    if ( dep == CInventory::departments.end() )
    {
        return false;
    }
    
    vector<int>::iterator ind = lower_bound( dep->IDs.begin(), dep->IDs.end(), invID );
    dep->IDs.erase( ind );
    
    prop->alive = false;
    
    return true;
}

//----------------------------------------------------------------------------//

bool CInventory::Transfer( int invID,
              const string & deptName,
              const string & city,
              const string & country )
{
    string fullName = country + "$$$" + city + "$$$" + deptName;
    
    string oldName;
    if ( CInventory::properties.size() != 0 )
    {
        std::vector<CProperty>::iterator prop;
        prop = lower_bound(CInventory::properties.begin(), CInventory::properties.end(), invID, compareFunctions());
        if ( prop == CInventory::properties.end() || (prop->propID == invID && !prop->alive) ) return false;
        
        oldName = prop->depName;
        
        if ( oldName == fullName )
            return false;
        
        if ( prop->propID == invID )
            prop->depName = fullName;
        else return false; // Not found
    } else return false; // Not found (no place to search in)
    
    std::vector<CDepartment>::iterator dep;
    
    // Searching for the department
    if ( CInventory::departments.size() != 0 )
    {
        dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), oldName, compareFunctions());
        if (  dep == CInventory::departments.end() || dep->departmentName != oldName )
            return false; // WTF?!
        else {
            // Okay, delete from the list our ID
            vector<int>::iterator el;
            el = lower_bound(dep->IDs.begin(), dep->IDs.end(), invID, compareFunctions());
            dep->IDs.erase( el );
            
            // The department exists?
            dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
            
            if ( dep == CInventory::departments.end() || dep->departmentName != fullName )
            {
                // No, creating a new one
                CDepartment a;
                a.departmentName = fullName;
                a.IDs.push_back( invID );
#warning the problematic line
                CInventory::departments.insert(dep, a);
                
                
                //CDepartment * dep = new CDepartment;
                //dep->departmentName = fullName;
                //dep->IDs.push_back( invID );
            } else {
                // Yes, inserting our ID to the IDs array
                el = lower_bound(dep->IDs.begin(), dep->IDs.end(), invID, compareFunctions());
                dep->IDs.insert(el, invID);
            }
        }
    } else {
        return false; // WTF?!
    }
    
    return true;
}

//----------------------------------------------------------------------------//

int CInventory::PropCount( const string & deptName,
                          const string & city,
                          const string & country ) const
{
    string fullName = country + "$$$" + city + "$$$" + deptName;
    
    if ( ! CInventory::departments.size() )
        return 0;
    
    std::vector<CDepartment>::const_iterator dep;
    dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
    
    if ( dep == CInventory::departments.end() || dep->departmentName != fullName )
        return 0;
    else
        return (int) dep->IDs.size();
}

//----------------------------------------------------------------------------//

CPropList CInventory::PropList( const string & deptName,
                   const string & city,
                   const string & country ) const
{
    CPropList fuckingIterator;
    
    string fullName = country + "$$$" + city + "$$$" + deptName;
    
    std::vector<CDepartment>::const_iterator dep;
    dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
    
    if ( dep == CInventory::departments.end()
        || dep->departmentName != fullName ) return fuckingIterator;
    
    int size = (int)dep->IDs.size();
    
    for ( int i = 0; i < size; i++ )
    {
        int invID = dep->IDs[i];
        
        vector<CProperty>::const_iterator el;
        //el = lower_bound(CInventory::properties.begin(), CInventory::properties.end(), invID, compareFunctions());
        el = CInventory::properties.begin();
        fuckingIterator.addToList( el );
    }
    
    return fuckingIterator;
}

//----------------------------------------------------------------------------//

#ifndef __PROGTEST__

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

string genRandom()  // Random string generator function.
{
    string aaa;
    for ( int j = 0; j < 20; j ++ )
    {
        aaa += alphanum[rand() % stringLength];
    }
    return aaa;
}


int main( void )
{
//    CInventory b1;
//    assert ( b1 . AddProp ( 100, "Notebook", "Accounting", "Prague", "CZ" ) == true );
//    assert ( b1 . AddProp ( 101, "Notebook", "Human Resources", "Prague", "CZ" ) == true );
//    assert ( b1 . AddProp ( 102, "Notebook", "Accounting", "Brno", "CZ" ) == true );
//    assert ( b1 . AddProp ( 103, "Notebook", "Accounting", "Prague", "USA" ) == true );
//    assert ( b1 . AddProp ( 104, "Desktop PC", "Accounting", "Prague", "CZ" ) == true );
//    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 2 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following 2 items, in any order:
//    
//    // 100 Notebook
//    // 104 Desktop PC
//    
//    assert ( b1 . PropCount ( "Human Resources", "Prague", "CZ" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Human Resources", "Prague", "CZ" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 101 Notebook
//    
//    assert ( b1 . PropCount ( "Accounting", "Brno", "CZ" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Brno", "CZ" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 102 Notebook
//    
//    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 103 Notebook
//    
//    assert ( b1 . Transfer ( 104, "Accounting", "Prague", "USA" ) == true );
//    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 100 Notebook
//    
//    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 2 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following 2 items, in any order:
//    
//    // 103 Notebook
//    // 104 Desktop PC
//    
//    assert ( b1 . DelProp ( 104 ) == true );
//    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 103 Notebook
//    
//    assert ( b1 . AddProp ( 104, "Chair", "Public relations", "Paris", "France" ) == true );
//    assert ( b1 . PropCount ( "Public relations", "Paris", "France" ) == 1 );
//    for ( CPropList l = b1 . PropList ( "Public relations", "Paris", "France" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // the following property
//    
//    // 104 Chair
//    
//    
//    CInventory b2;
//    assert ( b2 . AddProp ( 100, "Notebook", "Accounting", "Prague", "CZ" ) == true );
//    assert ( b2 . AddProp ( 101, "Notebook", "Human Resources", "Prague", "CZ" ) == true );
//    assert ( b2 . AddProp ( 100, "Table", "CEO Office", "Prague", "CZ" ) == false );
//    assert ( b2 . DelProp ( 102 ) == false );
//    assert ( b2 . Transfer ( 102, "CEO Office", "Prague", "CZ" ) == false );
//    assert ( b2 . Transfer ( 100, "Accounting", "Prague", "CZ" ) == false );
//    assert ( b2 . DelProp ( 100 ) == true );
//    assert ( b2 . DelProp ( 100 ) == false );
//    assert ( b2 . PropCount ( "Facility Services", "Prague", "CZ" ) == 0 );
//    for ( CPropList l = b2 . PropList ( "CEO Office", "Prague", "USA" ); l . Remains (); l . Next () )
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    // empty output
//    
//    CInventory b3;
//    char k[10];
//    string str;
//    
//    for ( int i = 0; i < 1000; i++ )
//    {
//        
//        k[0] = 0;
//        k[1] = 0;
//        k[2] = 0;
//        k[3] = 0;
//        k[4] = 0;
//        k[5] = 0;
//        k[6] = 0;
//        k[7] = 0;
//        k[8] = 0;
//        k[9] = 0;
//        sprintf( k, "%d", i );
//        string lstr( k, 10 );
//        str = lstr;
//        if (i < 100) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "AAA" ) == true );
//        else if ( i < 500 ) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "ABA" ) == true );
//        else if ( i < 900 ) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "ABB" ) == true );
//        else assert( b3 . AddProp ( i, "Chair", "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ) == true );
//    }
//    for ( int j = 0; j < 100; j++ )
//    {
//        for ( int i = 900; i < 1000; i++ )
//        {
//            assert ( b3 . DelProp ( i ) );
//        }
//        for ( int i = 900; i < 1000; i++ )
//        {
//            assert( b3 . AddProp ( i, "Chair", "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ) == true );
//        }
//        for ( int i = 950; i < 1000; i++ )
//        {
//            sprintf( k, "%d", i );
//            string lstr( k, 5 );
//            assert ( b3 . Transfer ( i, lstr, "Prague", "CZ" ) );
//        }
//    }
//    
//    assert ( b3 . DelProp ( 15 ) );
//    assert( ! b3. DelProp( -1 ) );
//    assert( ! b3.Transfer( 15 , "A", "A", "A" ) );
//    assert( b3.Transfer( 16 , "A ", "A ", "A " ) );
//    
//    int g = 0;
//    //for ( CPropList l = b3 . PropList ( "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ); l . Remains (); l . Next () )
//    //for ( CPropList l = b3 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
//    //for ( CPropList l = b3 . PropList ( "AAA", "AAA", "AAA" ); l . Remains (); l . Next () )
//    for ( CPropList l = b3 . PropList ( "A ", "A ", "A " ); l . Remains (); l . Next () )
//    {
//        g++;
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    }
//    
//    cout << g << endl;
//    
//    
//    
//    
//    
//    CInventory b4;
//    assert( !b4.Transfer( 12, "F", " ", "f ") );
//    assert( ! b4.DelProp( 12 ) );
//    for ( CPropList l = b4 . PropList ( "A ", "A ", "A " ); l . Remains (); l . Next () )
//    {
//        cout << "WTF?" << endl;
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    }
//    assert( b4.PropCount( "A ", "A ", "A " ) == 0 );
//    assert( b4.AddProp( 12, "A", "a", "a", "a" ) );
//    assert( b4.PropCount( "A ", "A ", "A " ) == 0 );
//    assert( b4.PropCount( "a ", "a ", "a " ) == 0 );
//    assert( b4.PropCount( "a", "a", "a" ) == 1 );
//    assert( ! b4.AddProp( 12, "A", "a", "a", "a" ) );
//    assert( ! b4.AddProp( 12, "A", "f", "a", "a" ) );
//    assert( b4.PropCount( "f", "a", "a" ) == 0 );
//    assert( b4.DelProp( 12 ) );
//    assert( b4.PropCount( "a", "a", "a" ) == 0 );
//    assert( !b4.Transfer( 12, "F", " ", "f ") );
//    assert( b4.AddProp( 12, "A", "f", "a", "a" ) );
//    assert( b4.PropCount( "f", "a", "a" ) == 1 );
//    assert( b4.Transfer( 12, "F", " ", "f ") );
//    assert( b4.PropCount( "f", "a", "a" ) == 0 );
//    assert( b4.PropCount( "F", " ", "f " ) == 1 );
//    assert( ! b4.Transfer( 12, "F", " ", "f ") );
//    assert( b4.PropCount( "F", " ", "f " ) == 1 );
//    for ( int i = 0; i < 1200; i ++ )
//    {
//        if ( i != 12 )
//            assert( b4.AddProp( i, "A", "ass", "a", "a" ) );
//        else
//            assert( b4.AddProp( i + 1200, "A", "ass", "a", "a" ) );
//    }
//    assert( b4.PropCount( "ass", "a", "a" ) == 1200 );
//    for ( CPropList l = b4 . PropList ( "F", " ", "f " ); l . Remains (); l . Next () )
//    {
//        cout << "ok" << endl;
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    }
//    for ( CPropList l = b4 . PropList ( "f", "a", "a" ); l . Remains (); l . Next () )
//    {
//        cout << "WTF?" << endl;
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    }
//    
//    for ( CPropList l = b4 . PropList ( "F", " ", "f " ); l . Remains (); l . Next () )
//    {
//        cout << "ok" << endl;
//        cout << l . InvID () << ' ' << l . Name () << endl;
//    }
    
    
    
    
    CInventory b5;
    
    string randStr;
    
    srand(time(0));
    randStr = genRandom();
    
    vector< string > randNames;
    randNames.resize( 100 );
    
    for ( int i = 0; i < 100; i ++ )
        randNames[i] = genRandom();
    
    for ( int i = 0; i < 100000; i++ )
    {
        
        int index = rand() % 100;
        string randStr = randNames[index];
        
        index = rand() % 100;
        string randStr1 = randNames[index];
        
        b5.AddProp( i, randStr, randStr, randStr, randStr );
        
        if ( i > 1000 )
        {
            b5.PropCount( randStr, randStr, randStr );
            b5.Transfer( i, randStr1, randStr1, randStr1 );
            b5.PropList(randStr1, randStr1, randStr1);
        }

    }
    
    // 22350 ms - no changes
    
    
    return 0;
}
#endif /* __PROGTEST__ */

// Hate my formatting? Get rid of it!  man 1 indent

