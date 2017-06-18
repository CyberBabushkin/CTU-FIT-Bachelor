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

struct CProperty {
    int propID;
    string name;
    int depID;
    
    bool alive;
};

struct CDepartmentPtr {
    int depID;
    string departmentName;
};

struct CDepartment {
    string departmentName;
    vector< CProperty > inventory;
};

class compareFunctions {
public:
    bool operator() ( const CDepartmentPtr & d1, const string & d2 )
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
    bool operator() ( const CProperty * d1, const int & d2 )
    {
        return d1->propID < d2;
    }
};

class CPropList
{
public:
    CPropList();
    ~CPropList();
    
    void connectLists( const vector <CProperty> * pointers );
    int    InvID( void ) const;
    string Name( void ) const;
    int    Remains( void ) const;
    void   Next( void );
private:
    int curIndex;
    int size;
    const vector <CProperty> * inventoryList;
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
    
    CProperty & getProperties( int index ) const;
    
private:
    
    int lookForProp( int ID ) const;
    int createNewProperty( const string & name,
                                  const int & depID,
                                  const int & invID);
    int createNewDepartment( const string & fullName,
                            vector<CDepartmentPtr>::iterator depPtr );
    int getDepartmentIndex( const string & fullName );
    bool compareIDs( const int & d1, const int & d2 ) const;
    
    vector< CDepartment > departments;
    vector< CDepartmentPtr > departmentPointers;
    
    vector< CProperty > properties;
};

// ************************************************************************** //
// ----------------------------- Implementation ----------------------------- //
// ************************************************************************** //

//----------------------------------------------------------------------------//
// -------------------------------- CPropList ------------------------------- //
//----------------------------------------------------------------------------//

CPropList::CPropList() : curIndex( 0 ), size( 0 ), inventoryList( nullptr ) {}
CPropList::~CPropList() { }

void CPropList::Next() {
    CPropList::curIndex++;
}

int CPropList::Remains() const {
    return CPropList::size - CPropList::curIndex;
}

string CPropList::Name() const {
    return (*CPropList::inventoryList)[CPropList::curIndex].name;
}

int CPropList::InvID() const {
    return (*CPropList::inventoryList)[CPropList::curIndex].propID;
}

void CPropList::connectLists( const vector <CProperty> * pointers )
{
    CPropList::inventoryList = pointers;
    size = (int)pointers->size();
}

//----------------------------------------------------------------------------//
// ------------------------------- CInventory ------------------------------- //
//----------------------------------------------------------------------------//

CInventory::CInventory( void )  {}
CInventory::~CInventory( void ) {}

//----------------------------------------------------------------------------//

int CInventory::lookForProp( int ID ) const {
    
    vector< CProperty >::const_iterator el;
    el = lower_bound( properties.begin(),
                     properties.end(),
                     ID, compareFunctions());
    
    if ( el == properties.end() || el->propID != ID )
        return -1;
    
    int index = (int)(el - properties.begin());
    
    return index;
}

//----------------------------------------------------------------------------//

int CInventory::createNewProperty( const string & name,
                                 const int & depID,
                                 const int & invID)
{
    CProperty a;
    a.name = name;
    a.propID = invID;
    a.depID = depID;
    a.alive = true;
    
    vector< CProperty >::iterator el;
    el = lower_bound(properties.begin(),
                     properties.end(),
                     invID, compareFunctions());
    int position = (int)(el - properties.begin());
    properties.insert( el, a );
    
    return position;
}

//----------------------------------------------------------------------------//

int CInventory::createNewDepartment( const string & fullName,
                                    vector<CDepartmentPtr>::iterator depPtr )
{
    CDepartment a;              // department
    CDepartmentPtr aPtr;
    int depIndex;
    a.departmentName = fullName;
    
    aPtr.departmentName = fullName;         // ptr
    depIndex = (int)departmentPointers.size();
    aPtr.depID = depIndex;
    
    departments.push_back(a);
    departmentPointers.insert( depPtr, aPtr );
    
    return depIndex;
}

//----------------------------------------------------------------------------//

int CInventory::getDepartmentIndex( const string & fullName )
{
    std::vector< CDepartmentPtr >::iterator depPtr;
    int depIndex;
    
    // Searching for the department
    if ( departments.size() != 0 )
    {
        // In depPtrs searching by name
        depPtr = lower_bound(departmentPointers.begin(),
                             departmentPointers.end(),
                             fullName, compareFunctions());
        
        if ( depPtr != departmentPointers.end() )
        {
            if ( depPtr->departmentName != fullName ) // creating new
            {
                depIndex = createNewDepartment( fullName, depPtr );
            } else
                depIndex = depPtr->depID;
        } else {
            depIndex = createNewDepartment( fullName, departmentPointers.end() );
        }
    } else {
        depIndex = createNewDepartment( fullName, departmentPointers.end() );
    }
    
    return depIndex;
}

//----------------------------------------------------------------------------//

bool CInventory::AddProp( int invID,
             const string & name,
             const string & deptName,
             const string & city,
             const string & country )
{
    string fullName = country + "$" + city + "$" + deptName;
    int propIndex = 0, depIndex = 0;
    
    // Getting department index (depID)
    depIndex = getDepartmentIndex( fullName );
    CProperty * prop;
    
    // Searching for the property or setting a new one up
    if ( properties.size() != 0 )
    {
        
        propIndex = CInventory::lookForProp( invID );
        
        if ( propIndex != -1 ) {
            // Element exists
            prop = &(properties[propIndex]);
            
            // Alive element exists
            if ( prop->propID == invID && prop->alive ) return false;
            
            // Ressurecting dead ID
            if ( prop->propID == invID )
            {
                prop->name = name;
                prop->depID = depIndex;
                prop->alive = true;
            } else {
                // Creating new ID
                propIndex = CInventory::createNewProperty( name, depIndex, invID );
                prop = &properties[propIndex];
            }
        } else {
            // Creating new ID
            propIndex = CInventory::createNewProperty( name, depIndex, invID );
            prop = &properties[propIndex];
        }
    } else {
        // Creating new ID
        propIndex = CInventory::createNewProperty( name, depIndex, invID );
        prop = &properties[propIndex];
    }
    
    // Attaching our new property to the department
    vector< CProperty >::iterator iter = lower_bound( departments[depIndex].inventory.begin(),
                                                       departments[depIndex].inventory.end(),
                                                       invID, compareFunctions() );
    
    departments[depIndex].inventory.insert( iter, *prop );
    
    return true;
}

//----------------------------------------------------------------------------//

bool CInventory::DelProp( int invID )
{
    int propIndex = -1;
    propIndex = CInventory::lookForProp( invID );
    
    if ( properties.size() == 0 || propIndex == -1 )
        return false;
    
    CProperty * prop = &( properties[propIndex] );
    
    if ( ! prop->alive ) return false;
    
    prop->alive = false;
    
    CDepartment * dep = &departments[ prop->depID ];
    
    vector< CProperty >::iterator indexOfEl;
    
    indexOfEl = lower_bound( dep->inventory.begin(),
                            dep->inventory.end(),
                            invID, compareFunctions() );
    dep->inventory.erase( indexOfEl );
    
    return true;
}

//----------------------------------------------------------------------------//

bool CInventory::Transfer( int invID,
              const string & deptName,
              const string & city,
              const string & country )
{
    string fullName = country + "$" + city + "$" + deptName;

    int propIndex = lookForProp( invID );
    if ( propIndex == -1 || !properties[propIndex].alive ) return false; // not found
    CProperty *prop = &properties[propIndex];
    
    if ( departments[prop->depID].departmentName == fullName ) return false;
    
    if ( ! DelProp( invID )
        || ! AddProp( invID, prop->name, deptName, city, country ) ) return false;
    
    return true;
    
//    int propIndex = lookForProp( invID );
//    
//    if ( propIndex == -1 || !properties[propIndex].alive ) return false; // not found
//    
//    int oldDepIndex = properties[propIndex].depID;
//    CDepartment * oldDep = &departments[oldDepIndex];
//
//    string oldName = oldDep->departmentName;  // old department name
//    if ( oldName == fullName ) return false; // no reason to move
//    
//    vector<CDepartmentPtr>::iterator iter;
//    iter = lower_bound( departmentPointers.begin(),     // searching for a new one
//                       departmentPointers.end(),
//                       fullName, compareFunctions() );
//    int newDepIndex;
//    
//    if ( iter == departmentPointers.end() || iter->departmentName != fullName )
//        newDepIndex = createNewDepartment( fullName, iter ); // not found
//    else
//        newDepIndex = (int)( iter - departmentPointers.begin() ); // found
//    
//    CProperty *prop = &properties[propIndex];
//    prop->depID = newDepIndex;
//    
//    CDepartment * newDep = &departments[newDepIndex];
//    
//    vector< CProperty >::iterator propInDep;
//    propInDep = lower_bound( oldDep->inventory.begin(),
//                            oldDep->inventory.end(),
//                            invID, compareFunctions() );
//    
//    oldDep->inventory.erase( propInDep );
//    
//    propInDep = lower_bound( newDep->inventory.begin(),
//                            newDep->inventory.end(),
//                            invID, compareFunctions() );
//    newDep->inventory.insert( propInDep, properties[propIndex] );
    /*
//
//    int propInd;
//    CProperty * prop;
//    
//    if ( properties.size() != 0 )
//    {
//        propInd = CInventory::lookForProp(invID);
//        
//        if ( propInd == -1 ) return false; // Not found
//        
//        prop = &(properties[propInd]);
//        
//        if ( ! prop->alive ) return false; // Dead ID
//        
//        oldName = prop->depName;
//        
//        if ( oldName == fullName ) return false; // No reason to move
//        
//        if ( prop->propID == invID )
//            prop->depName = fullName;
//        else return false; // Not found
//    } else return false; // Not found (no place to search in)
//    
//    std::vector<CDepartment>::iterator dep;
//    
//    // Searching for the department
//    if ( CInventory::departments.size() != 0 )
//    {
//        dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), oldName, compareFunctions());
//        
//        if ( dep == CInventory::departments.end() || dep->departmentName != oldName )
//            return false; // WTF?!
//        
//        // Okay, delete from the list our ID
//        vector<int>::iterator el;
//        el = lower_bound(dep->indexes.begin(), dep->indexes.end(), propInd, compareFunctions());
//        
//        dep->indexes.erase( el );
//
//        if ( dep->indexes.size() == 0 ) departments.erase( dep );
//        
//        // The department exists?
//        dep = lower_bound(CInventory::departments.begin(), CInventory::departments.end(), fullName, compareFunctions());
//        
//        if ( dep == CInventory::departments.end() || dep->departmentName != fullName )
//        {
//            // No, creating a new one
//            CDepartment a;
//            a.departmentName = fullName;
//            a.indexes.push_back( propInd );
//            CInventory::departments.insert(dep, a);
//            
//        } else {
//            // Yes, inserting our ID to the IDs array
//            el = lower_bound(dep->indexes.begin(), dep->indexes.end(), propInd, compareFunctions());
//            dep->indexes.insert(el, propInd);
//        }
//        
//    } else {
//        return false; // WTF?!
//    }
     */
    
    return true;
}

//----------------------------------------------------------------------------//

int CInventory::PropCount( const string & deptName,
                          const string & city,
                          const string & country ) const
{
    string fullName = country + "$" + city + "$" + deptName;
    
    if ( ! CInventory::departments.size() )
        return 0;
    
    std::vector<CDepartmentPtr>::const_iterator dep;
    dep = lower_bound(departmentPointers.begin(),
                      departmentPointers.end(),
                      fullName, compareFunctions());
    
    if ( dep == departmentPointers.end() || dep->departmentName != fullName )
        return 0;
    
    return (int) departments[dep->depID].inventory.size();
}

//----------------------------------------------------------------------------//

CPropList CInventory::PropList( const string & deptName,
                   const string & city,
                   const string & country ) const
{
    CPropList fuckingIterator;
    
    string fullName = country + "$" + city + "$" + deptName;
    
    std::vector<CDepartmentPtr>::const_iterator dep;
    dep = lower_bound(departmentPointers.begin(),
                      departmentPointers.end(),
                      fullName, compareFunctions());
    
    if ( dep == departmentPointers.end()
        || dep->departmentName != fullName ) return fuckingIterator;
    
    const CDepartment * depPtr = &departments[dep->depID];
    const vector<CProperty> * propList = &(depPtr->inventory);
    
    fuckingIterator.connectLists( propList );
    
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
    CInventory b1;
    assert ( b1 . AddProp ( 100, "Notebook", "Accounting", "Prague", "CZ" ) == true );
    assert ( b1 . AddProp ( 101, "Notebook", "Human Resources", "Prague", "CZ" ) == true );
    assert ( b1 . AddProp ( 102, "Notebook", "Accounting", "Brno", "CZ" ) == true );
    assert ( b1 . AddProp ( 103, "Notebook", "Accounting", "Prague", "USA" ) == true );
    assert ( b1 . AddProp ( 104, "Desktop PC", "Accounting", "Prague", "CZ" ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 2 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following 2 items, in any order:
    
    // 100 Notebook
    // 104 Desktop PC
    
    assert ( b1 . PropCount ( "Human Resources", "Prague", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Human Resources", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 101 Notebook
    
    assert ( b1 . PropCount ( "Accounting", "Brno", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Brno", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 102 Notebook
    
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 103 Notebook
    
    assert ( b1 . Transfer ( 104, "Accounting", "Prague", "USA" ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 100 Notebook
    
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 2 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following 2 items, in any order:
    
    // 103 Notebook
    // 104 Desktop PC
    
    assert ( b1 . DelProp ( 104 ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 103 Notebook
    
    assert ( b1 . AddProp ( 104, "Chair", "Public relations", "Paris", "France" ) == true );
    assert ( b1 . PropCount ( "Public relations", "Paris", "France" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Public relations", "Paris", "France" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // the following property
    
    // 104 Chair
    
    
    CInventory b2;
    assert ( b2 . AddProp ( 100, "Notebook", "Accounting", "Prague", "CZ" ) == true );
    assert ( b2 . AddProp ( 101, "Notebook", "Human Resources", "Prague", "CZ" ) == true );
    assert ( b2 . AddProp ( 100, "Table", "CEO Office", "Prague", "CZ" ) == false );
    assert ( b2 . DelProp ( 102 ) == false );
    assert ( b2 . Transfer ( 102, "CEO Office", "Prague", "CZ" ) == false );
    assert ( b2 . Transfer ( 100, "Accounting", "Prague", "CZ" ) == false );
    assert ( b2 . DelProp ( 100 ) == true );
    assert ( b2 . DelProp ( 100 ) == false );
    assert ( b2 . PropCount ( "Facility Services", "Prague", "CZ" ) == 0 );
    for ( CPropList l = b2 . PropList ( "CEO Office", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << endl;
    // empty output
    
    CInventory b3;
    char k[10];
    string str;
    
    for ( int i = 0; i < 1000; i++ )
    {
        
        k[0] = 0;
        k[1] = 0;
        k[2] = 0;
        k[3] = 0;
        k[4] = 0;
        k[5] = 0;
        k[6] = 0;
        k[7] = 0;
        k[8] = 0;
        k[9] = 0;
        sprintf( k, "%d", i );
        string lstr( k, 10 );
        str = lstr;
        if (i < 100) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "AAA" ) == true );
        else if ( i < 500 ) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "ABA" ) == true );
        else if ( i < 900 ) assert( b3 . AddProp ( i, "AAA", "AAA", "AAA", "ABB" ) == true );
        else assert( b3 . AddProp ( i, "Chair", "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ) == true );
    }
    for ( int j = 0; j < 100; j++ )
    {
        for ( int i = 900; i < 1000; i++ )
        {
            assert ( b3 . DelProp ( i ) );
        }
        for ( int i = 900; i < 1000; i++ )
        {
            assert( b3 . AddProp ( i, "Chair", "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ) == true );
        }
        for ( int i = 950; i < 1000; i++ )
        {
            sprintf( k, "%d", i );
            string lstr( k, 5 );
            assert ( b3 . Transfer ( i, lstr, "Prague", "CZ" ) );
        }
    }
    
    assert ( b3 . DelProp ( 15 ) );
    assert( ! b3. DelProp( -1 ) );
    assert( ! b3.Transfer( 15 , "A", "A", "A" ) );
    assert( b3.Transfer( 16 , "A ", "A ", "A " ) );
    
    int g = 0;
    //for ( CPropList l = b3 . PropList ( "Pqhbvligskadda", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" ); l . Remains (); l . Next () )
    //for ( CPropList l = b3 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
    //for ( CPropList l = b3 . PropList ( "AAA", "AAA", "AAA" ); l . Remains (); l . Next () )
    for ( CPropList l = b3 . PropList ( "A ", "A ", "A " ); l . Remains (); l . Next () )
    {
        g++;
        cout << l . InvID () << ' ' << l . Name () << endl;
    }
    
    cout << g << endl;
    
    
    
    
    
    CInventory b4;
    assert( !b4.Transfer( 12, "F", " ", "f ") );
    assert( ! b4.DelProp( 12 ) );
    for ( CPropList l = b4 . PropList ( "A ", "A ", "A " ); l . Remains (); l . Next () )
    {
        cout << "WTF?" << endl;
        cout << l . InvID () << ' ' << l . Name () << endl;
    }
    assert( b4.PropCount( "A ", "A ", "A " ) == 0 );
    assert( b4.AddProp( 12, "A", "a", "a", "a" ) );
    assert( b4.PropCount( "A ", "A ", "A " ) == 0 );
    assert( b4.PropCount( "a ", "a ", "a " ) == 0 );
    assert( b4.PropCount( "a", "a", "a" ) == 1 );
    assert( ! b4.AddProp( 12, "A", "a", "a", "a" ) );
    assert( ! b4.AddProp( 12, "A", "f", "a", "a" ) );
    assert( b4.PropCount( "f", "a", "a" ) == 0 );
    assert( b4.DelProp( 12 ) );
    assert( b4.PropCount( "a", "a", "a" ) == 0 );
    assert( !b4.Transfer( 12, "F", " ", "f ") );
    assert( b4.AddProp( 12, "A", "f", "a", "a" ) );
    assert( b4.PropCount( "f", "a", "a" ) == 1 );
    assert( b4.Transfer( 12, "F", " ", "f ") );
    assert( b4.PropCount( "f", "a", "a" ) == 0 );
    assert( b4.PropCount( "F", " ", "f " ) == 1 );
    assert( ! b4.Transfer( 12, "F", " ", "f ") );
    assert( b4.PropCount( "F", " ", "f " ) == 1 );
    for ( int i = 0; i < 1200; i ++ )
    {
        if ( i != 12 )
            assert( b4.AddProp( i, "A", "ass", "a", "a" ) );
        else
            assert( b4.AddProp( i + 1200, "A", "ass", "a", "a" ) );
    }
    assert( b4.PropCount( "ass", "a", "a" ) == 1200 );
    for ( CPropList l = b4 . PropList ( "F", " ", "f " ); l . Remains (); l . Next () )
    {
        cout << "ok" << endl;
        cout << l . InvID () << ' ' << l . Name () << endl;
    }
    for ( CPropList l = b4 . PropList ( "f", "a", "a" ); l . Remains (); l . Next () )
    {
        cout << "WTF?" << endl;
        cout << l . InvID () << ' ' << l . Name () << endl;
    }
    
    for ( CPropList l = b4 . PropList ( "F", " ", "f " ); l . Remains (); l . Next () )
    {
        cout << "ok" << endl;
        cout << l . InvID () << ' ' << l . Name () << endl;
    }
    
    
    
    
    CInventory b5;
    
    string randStr;
    
    srand(time(0));
    randStr = genRandom();
    
    vector< string > randNames;
    vector< int > randIndexes;
    
    randNames.resize( 10000 );
    randIndexes.resize( 10000 );
    
    for ( int i = 0; i < 10000; i ++ )
    {
        randNames[i] = genRandom();
        randIndexes[i] = rand() % 10000;
    }
    
    for ( int i = 0; i < 10000000; i++ )
    {
        
        int index = rand() % 10000;
        
        string randStr = randNames[index];
        
        index = rand() % 10000;
        string randStr1 = randNames[index];
        if ( i % 1000 )
            b5.AddProp( index, randStr, randStr, randStr, randStr );
        
        b5.PropCount( randStr, randStr, randStr );
        b5.Transfer( index, randStr1, randStr1, randStr1 );
        b5.PropList(randStr1, randStr1, randStr1);
        

    }
    
    // 22350 ms - no changes
    // 6177 - propList
    
    return 0;
}
#endif /* __PROGTEST__ */

// Hate my formatting? Get rid of it!  man 1 indent

