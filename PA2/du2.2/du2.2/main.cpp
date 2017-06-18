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

//----------------------------------------------------------------------------//

struct CProperty {
    int propID;
    int serial;
    string name;
    int depID;
    vector< int > history;
    
    bool alive;
};

//------------------------------//

struct CPropertyByID {
    int propID;
    int index;
};

//------------------------------//

struct CPropertyBySerial {
    string serial;
    int index;
};

//----------------------------------------------------------------------------//

struct CDepartment {
    string departmentName;
    string depShortName;
    string country;
    string city;
    vector< CProperty > inventory;
};

//------------------------------//

struct CDepartmentPtr {
    int depID;
    string departmentName;
};

//----------------------------------------------------------------------------//

class compareFunctions {
public:
    bool operator() ( const CPropertyByID & d1, const int ID )
    {
        return d1.propID < ID;
    }
    bool operator() ( const CPropertyBySerial & d1, const string & fullName )
    {
        return d1.serial < fullName;
    }
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

//----------------------------------------------------------------------------//

class CPropList
{
public:
    CPropList();
    ~CPropList();
    
    void connectLists( const vector <CProperty> * pointers );
    int    InvID( void ) const;
    string Name( void ) const;
    int    Serial( void ) const;
    int    Remains( void ) const;
    void   Next( void );
private:
    int curIndex;
    int size;
    const vector <CProperty> * inventoryList;
};

//----------------------------------------------------------------------------//

class CDeptList
{
public:
    CDeptList();
    ~CDeptList();
    void assignList( const CDepartment ** list, int size );
    
    string DeptName( void ) const;
    string City( void ) const;
    string Country( void ) const;
    int    Remains( void ) const;
    void   Next( void );
private:
    const CDepartment ** m_list;
    int m_size;
    int m_pos;
};

//----------------------------------------------------------------------------//

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
                 int serial,
                 const string & deptName,
                 const string & city,
                 const string & country );
    bool DelProp( int invID );
    bool DelProp( const string & name, int serial );
    bool Transfer( int invID,
                  const string & deptName,
                  const string & city,
                  const string & country );
    bool Transfer( const string & name,
                  int serial,
                  const string & deptName,
                  const string & city,
                  const string & country );
    CPropList PropList( const string & deptName,
                       const string & city,
                       const string & country ) const;
    int PropCount( const string & deptName,
                  const string & city,
                  const string & country ) const;
    CDeptList DeptList ( int invID ) const;
    int DeptCount( int invID ) const;
    CDeptList DeptList ( const string & name,
                       int serial ) const;
    int DeptCount( const string & name,
                  int serial ) const;
    
private:
    
    int lookForProp( int ID ) const;
    int lookForProp( const string & name, int serial ) const;
    int createNewProperty( const string & name,
                          const int & serial,
                          const int & depID,
                          const int & invID);
    int createNewDepartment( const string & deptName,
                            const string & city,
                            const string & country,
                            vector<CDepartmentPtr>::iterator depPtr );
    int getDepartmentIndex( const string & deptName,
                           const string & city,
                           const string & country );
    bool compareIDs( const int & d1, const int & d2 ) const;
    
    string fullSerialName( int serial, const string & name ) const;
    
    vector< CDepartment > departments;
    vector< CDepartmentPtr > departmentPointers;
    
    vector< CProperty > properties;
    vector< CPropertyByID > propertiesByID;
    vector< CPropertyBySerial > propertiesBySerial;
    
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

int CPropList::Serial() const
{
    return (*CPropList::inventoryList)[CPropList::curIndex].serial;
}

void CPropList::connectLists( const vector <CProperty> * pointers )
{
    CPropList::inventoryList = pointers;
    size = (int)pointers->size();
}

//----------------------------------------------------------------------------//
// ------------------------------- CDeptList -------------------------------- //
//----------------------------------------------------------------------------//

CDeptList::CDeptList() : m_list( nullptr ), m_size( 0 ), m_pos( 0 ) {}

//----------------------------------------------------------------------------//

CDeptList::~CDeptList()
{
    if ( m_list ) delete [] m_list;
}

//----------------------------------------------------------------------------//

void CDeptList::assignList( const CDepartment ** list, int size )
{
    m_size = size;
    m_list = list;
}

string CDeptList::DeptName( void ) const
{
    return m_list[m_pos]->depShortName;
}

string CDeptList::City( void ) const
{
    return m_list[m_pos]->city;
}

string CDeptList::Country( void ) const
{
    return m_list[m_pos]->country;
}

int    CDeptList::Remains( void ) const
{
    return m_size - m_pos;
}

void   CDeptList::Next( void )
{
    m_pos++;
}

//----------------------------------------------------------------------------//
// ------------------------------- CInventory ------------------------------- //
//----------------------------------------------------------------------------//

CInventory::CInventory( void )  {}
CInventory::~CInventory( void ) {}

//----------------------------------------------------------------------------//

string CInventory::fullSerialName( int serial, const string & name ) const
{
    char * l = new char[12];
    for ( int i = 0; i < 12; i++ )
        l[i] = 0;
    
    sprintf( l, "%d", serial );
    string fullName( l, 12 );
    fullName += "$" + name;
    
    delete [] l;
    
    return fullName;
}

//----------------------------------------------------------------------------//

int CInventory::lookForProp( int ID ) const
{
    
    vector< CPropertyByID >::const_iterator el;
    el = lower_bound( propertiesByID.begin(),
                     propertiesByID.end(),
                     ID, compareFunctions());
    
    if ( el == propertiesByID.end() || el->propID != ID )
        return -1;
    
    return el->index;
}

//----------------------------------------------------------------------------//

int CInventory::lookForProp( const string & name, int serial ) const
{
    string fullName = fullSerialName( serial, name );
    
    vector< CPropertyBySerial >::const_iterator el;
    el = lower_bound( propertiesBySerial.begin(),
                     propertiesBySerial.end(),
                     fullName, compareFunctions() );
    
    if ( el == propertiesBySerial.end() || el->serial != fullName )
        return -1;
    
    return el->index;
}

//----------------------------------------------------------------------------//

int CInventory::createNewProperty( const string & name,
                                  const int & serial,
                                  const int & depID,
                                  const int & invID)
{
    CProperty a;
    a.name = name;
    a.serial = serial;
    a.propID = invID;
    a.depID = depID;
    a.alive = true;
    
    properties.push_back( a );
    int index = (int)properties.size() - 1;
    
    string fullName = fullSerialName( serial, name );
    vector< CPropertyBySerial >::iterator el;
    el = lower_bound(propertiesBySerial.begin(),
                     propertiesBySerial.end(),
                     fullName, compareFunctions());
    CPropertyBySerial aSer;
    aSer.serial = fullName;
    aSer.index = index;
    propertiesBySerial.insert( el, aSer );
    
    vector< CPropertyByID >::iterator elId;
    elId = lower_bound(propertiesByID.begin(),
                       propertiesByID.end(),
                       invID, compareFunctions());
    CPropertyByID aID;
    aID.propID = invID;
    aID.index = index;
    propertiesByID.insert( elId, aID );
    
    return index;
}

//----------------------------------------------------------------------------//

int CInventory::createNewDepartment( const string & deptName,
                                    const string & city,
                                    const string & country,
                                    vector<CDepartmentPtr>::iterator depPtr )
{
    string fullName = country + "$" + city + "$" + deptName;
    
    CDepartment a;              // department
    CDepartmentPtr aPtr;
    int depIndex;
    a.departmentName = fullName;
    a.country = country;
    a.city = city;
    a.depShortName = deptName;
    
    aPtr.departmentName = fullName;         // ptr
    depIndex = (int)departmentPointers.size();
    aPtr.depID = depIndex;
    
    departments.push_back(a);
    departmentPointers.insert( depPtr, aPtr );
    
    return depIndex;
}

//----------------------------------------------------------------------------//

int CInventory::getDepartmentIndex( const string & deptName,
                                   const string & city,
                                   const string & country )
{
    std::vector< CDepartmentPtr >::iterator depPtr;
    int depIndex;
    string fullName = country + "$" + city + "$" + deptName;
    
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
                depIndex = createNewDepartment( deptName, city, country, depPtr );
            } else
                depIndex = depPtr->depID;
        } else {
            depIndex = createNewDepartment( deptName, city, country, departmentPointers.end() );
        }
    } else {
        depIndex = createNewDepartment( deptName, city, country, departmentPointers.end() );
    }
    
    return depIndex;
}

//----------------------------------------------------------------------------//

bool CInventory::AddProp( int invID,
                         const string & name,
                         int serial,
                         const string & deptName,
                         const string & city,
                         const string & country )
{
    string fullName = country + "$" + city + "$" + deptName;
    int propIndex = 0, depIndex = 0;
    
    // Getting department index (depID)
    depIndex = getDepartmentIndex( deptName, city, country );
    CProperty * prop;
    
    int k = lookForProp( invID ), z = lookForProp( name, serial );
    if ( k != z
        && ( ( k != -1 && properties[k].alive )
            || ( z != -1 && properties[z].alive ) ) )
        return false;
    
    // Searching for the property or setting a new one up
    if ( properties.size() != 0 )
    {
        propIndex = lookForProp( invID );
        
        if ( propIndex != -1 ) {
            // Element exists
            prop = &(properties[propIndex]);
            
            // Alive element exists
            if ( prop->propID == invID && prop->alive ) return false;
            
            // Ressurecting dead ID
            if ( prop->propID == invID )
            {
                vector<CPropertyBySerial>::iterator iter;
                iter = lower_bound( propertiesBySerial.begin(),
                                   propertiesBySerial.end(),
                                   fullSerialName( serial, name ),
                                   compareFunctions() );
                if ( iter != propertiesBySerial.end() )
                    propertiesBySerial.erase( iter );
                
                prop->name = name;
                prop->depID = depIndex;
                prop->serial = serial;
                prop->alive = true;
            } else {
                // Creating new ID
                propIndex = createNewProperty( name, serial, depIndex, invID );
                prop = &properties[propIndex];
            }
        } else {
            // Creating new ID
            propIndex = createNewProperty( name, serial, depIndex, invID );
            prop = &properties[propIndex];
        }
    } else {
        // Creating new ID
        propIndex = createNewProperty( name, serial, depIndex, invID );
        prop = &properties[propIndex];
    }
    
    // Attaching our new property to the department
    vector< CProperty >::iterator iter = lower_bound( departments[depIndex].inventory.begin(),
                                                     departments[depIndex].inventory.end(),
                                                     invID, compareFunctions() );
    
    prop->history.push_back( depIndex );
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
    prop->history.clear();
    
    CDepartment * dep = &departments[ prop->depID ];
    
    vector< CProperty >::iterator indexOfEl;
    
    indexOfEl = lower_bound( dep->inventory.begin(),
                            dep->inventory.end(),
                            invID, compareFunctions() );
    dep->inventory.erase( indexOfEl );
    
    return true;
}

bool CInventory::DelProp( const string & name, int serial )
{
    int propIndex = -1;
    propIndex = CInventory::lookForProp( name, serial );
    if ( properties.size() == 0 || propIndex == -1 )
        return false;
    
    CProperty * prop = &( properties[propIndex] );
    int invID = prop->propID;
    
    if ( ! prop->alive ) return false;
    
    prop->alive = false;
    prop->history.clear();
    
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
    string newName = country + "$" + city + "$" + deptName;
    
    int propIndex = lookForProp( invID );
    if ( propIndex == -1 || !properties[propIndex].alive ) return false; // not found
    CProperty *prop = &properties[propIndex];
    
    string oldName = departments[prop->depID].departmentName;
    if ( oldName == newName ) return false;
    
    int newDepIndex = getDepartmentIndex( deptName, city, country );
    CDepartment *newDep = &departments[newDepIndex];
    CDepartment *oldDep = &departments[prop->depID];
    
    vector<CProperty>::iterator iter;
    iter = lower_bound( newDep->inventory.begin(),
                       newDep->inventory.end(),
                       invID, compareFunctions() );
    newDep->inventory.insert( iter, *prop );
    
    iter = lower_bound( oldDep->inventory.begin(),
                       oldDep->inventory.end(),
                       invID, compareFunctions() );
    oldDep->inventory.erase( iter );
    
    prop->history.push_back( newDepIndex );
    prop->depID = newDepIndex;
    
    return true;
}

bool CInventory::Transfer(const string &name,
                          int serial,
                          const string &deptName,
                          const string &city,
                          const string &country)
{
    string newName = country + "$" + city + "$" + deptName;
    
    int propIndex = lookForProp( name, serial );
    if ( propIndex == -1 || !properties[propIndex].alive ) return false; // not found
    CProperty *prop = &properties[propIndex];
    int invID = prop->propID;
    
    string oldName = departments[prop->depID].departmentName;
    if ( oldName == newName ) return false;
    
    int newDepIndex = getDepartmentIndex( deptName, city, country );
    CDepartment *newDep = &departments[newDepIndex];
    CDepartment *oldDep = &departments[prop->depID];
    
    vector<CProperty>::iterator iter;
    iter = lower_bound( newDep->inventory.begin(),
                       newDep->inventory.end(),
                       invID, compareFunctions() );
    newDep->inventory.insert( iter, *prop );
    
    iter = lower_bound( oldDep->inventory.begin(),
                       oldDep->inventory.end(),
                       invID, compareFunctions() );
    oldDep->inventory.erase( iter );
    
    prop->history.push_back( newDepIndex );
    prop->depID = newDepIndex;
    
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

CDeptList CInventory::DeptList ( int invID ) const
{
    CDeptList a;
    int propIndex = lookForProp( invID );
    if ( propIndex == -1 || !properties[propIndex].alive ) return a; // not found
    const CProperty *prop = &properties[propIndex];
    
    int size = (int) prop->history.size();
    const CDepartment ** list = new const CDepartment* [size];
    for ( int i = 0; i < size; i++ )
        list[i] = &departments[prop->history[i]];
    
    a.assignList( list, size );
    return a;
}

CDeptList CInventory::DeptList ( const string & name,
                                int serial ) const
{
    CDeptList a;
    int propIndex = lookForProp( name, serial );
    if ( propIndex == -1 || !properties[propIndex].alive ) return a; // not found
    const CProperty *prop = &properties[propIndex];
    
    int size = (int) prop->history.size();
    const CDepartment ** list = new const CDepartment* [size];
    for ( int i = 0; i < size; i++ )
        list[i] = &departments[prop->history[i]];
    
    a.assignList( list, size );
    return a;
}

//----------------------------------------------------------------------------//

int CInventory::DeptCount( int invID ) const
{
    int propIndex = lookForProp( invID );
    if ( propIndex == -1 || !properties[propIndex].alive ) return 0; // not found
    const CProperty *prop = &properties[propIndex];
    
    return (int)prop->history.size();
}

int CInventory::DeptCount( const string & name,
                          int serial ) const
{
    int propIndex = lookForProp( name, serial );
    if ( propIndex == -1 || !properties[propIndex].alive ) return 0; // not found
    const CProperty *prop = &properties[propIndex];
    
    return (int)prop->history.size();
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
    assert ( b1 . AddProp ( 100, "Notebook", 201, "Accounting", "Prague", "CZ" ) == true );
    assert ( b1 . AddProp ( 101, "Notebook", 202, "Human Resources", "Prague", "CZ" ) == true );
    assert ( b1 . AddProp ( 102, "Notebook", 203, "Accounting", "Brno", "CZ" ) == true );
    assert ( b1 . AddProp ( 103, "Notebook", 204, "Accounting", "Prague", "USA" ) == true );
    assert ( b1 . AddProp ( 104, "Desktop PC", 201, "Accounting", "Prague", "CZ" ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 2 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following 2 items, in any order:
    
    // 100 Notebook 201
    // 104 Desktop PC 201
    
    assert ( b1 . PropCount ( "Human Resources", "Prague", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Human Resources", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 101 Notebook 202
    
    assert ( b1 . PropCount ( "Accounting", "Brno", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Brno", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 102 Notebook 203
    
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 103 Notebook 204
    
    assert ( b1 . Transfer ( 104, "Accounting", "Prague", "USA" ) == true );
    assert ( b1 . Transfer ( "Notebook", 203, "Accounting", "Prague", "USA" ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "CZ" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "CZ" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 100 Notebook 201
    
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 3 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following 3 items, in any order:
    
    // 103 Notebook 204
    // 104 Desktop PC 201
    // 102 Notebook 203
    
    assert ( b1 . DeptCount ( 102 ) == 2 );
    for ( CDeptList l = b1 . DeptList ( 102 ); l . Remains (); l . Next () )
        cout << l . DeptName () << ' ' << l . City () << ' ' << l . Country () << endl;
    // the following 2 departments, in this order:
    
    // Accounting Brno CZ
    // Accounting Prague USA
    
    assert ( b1 . DeptCount ( "Desktop PC", 201 ) == 2 );
    for ( CDeptList l = b1 . DeptList ( "Desktop PC", 201 ); l . Remains (); l . Next () )
        cout << l . DeptName () << ' ' << l . City () << ' ' << l . Country () << endl;
    // the following 2 departments, in this order:
    
    // Accounting Prague CZ
    // Accounting Prague USA
    
    assert ( b1 . DelProp ( 104 ) == true );
    assert ( b1 . DelProp ( "Notebook", 203 ) == true );
    assert ( b1 . PropCount ( "Accounting", "Prague", "USA" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Accounting", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 103 Notebook 204
    
    assert ( b1 . AddProp ( 104, "Notebook", 203, "Public relations", "Paris", "France" ) == true );
    assert ( b1 . PropCount ( "Public relations", "Paris", "France" ) == 1 );
    for ( CPropList l = b1 . PropList ( "Public relations", "Paris", "France" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // the following property
    
    // 104 Notebook 203
    
    
    CInventory b2;
    assert ( b2 . AddProp ( 100, "Notebook", 200, "Accounting", "Prague", "CZ" ) == true );
    assert ( b2 . AddProp ( 101, "Notebook", 201, "Human Resources", "Prague", "CZ" ) == true );
    assert ( b2 . AddProp ( 102, "Notebook", 201, "Human Resources", "Prague", "SK" ) == false );
    assert ( b2 . AddProp ( 100, "Table", 300, "CEO Office", "Prague", "CZ" ) == false );
    assert ( b2 . DelProp ( 103 ) == false );
    assert ( b2 . DelProp ( "Desktop PC", 10 ) == false );
    assert ( b2 . Transfer ( 103, "CEO Office", "Prague", "CZ" ) == false );
    assert ( b2 . Transfer ( "Chair", 57, "CEO Office", "Prague", "CZ" ) == false );
    assert ( b2 . Transfer ( 100, "Accounting", "Prague", "CZ" ) == false );
    assert ( b2 . DelProp ( 100 ) == true );
    assert ( b2 . DelProp ( 100 ) == false );
    assert ( b2 . DelProp ( "Notebook", 200 ) == false );
    assert ( b2 . PropCount ( "Facility Services", "Prague", "CZ" ) == 0 );
    for ( CPropList l = b2 . PropList ( "CEO Office", "Prague", "USA" ); l . Remains (); l . Next () )
        cout << l . InvID () << ' ' << l . Name () << ' ' << l . Serial () << endl;
    // empty output
    
    assert ( b2 . DeptCount ( 1000 ) == 0 );
    for ( CDeptList l = b2 . DeptList ( 1000 ); l . Remains (); l . Next () )
        cout << l . DeptName () << ' ' << l . City () << ' ' << l . Country () << endl;
    // empty output
    
    assert ( b2 . DeptCount ( "Tablet", 47 ) == 0 );
    for ( CDeptList l = b2 . DeptList ( "Tablet", 47 ); l . Remains (); l . Next () )
        cout << l . DeptName () << ' ' << l . City () << ' ' << l . Country () << endl;
    // empty output
    
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
//    
//    
//    
//    
//    CInventory b5;
//    
//    string randStr;
//    
//    srand(time(0));
//    randStr = genRandom();
//    
//    vector< string > randNames;
//    vector< int > randIndexes;
//    
//    randNames.resize( 10000 );
//    randIndexes.resize( 10000 );
//    
//    for ( int i = 0; i < 10000; i ++ )
//    {
//        randNames[i] = genRandom();
//        randIndexes[i] = rand() % 10000;
//    }
//    
//    for ( int i = 0; i < 10000000; i++ )
//    {
//        
//        int index = rand() % 10000;
//        
//        string randStr = randNames[index];
//        
//        index = rand() % 10000;
//        string randStr1 = randNames[index];
//        if ( i % 1000 )
//            b5.AddProp( index, randStr, randStr, randStr, randStr );
//        
//        b5.PropCount( randStr, randStr, randStr );
//        b5.Transfer( index, randStr1, randStr1, randStr1 );
//        b5.PropList(randStr1, randStr1, randStr1);
//        
//        
//    }
//    
//    // 22350 ms - no changes
//    // 6177 - propList
    
    return 0;
}
#endif /* __PROGTEST__ */

// Hate my formatting? Get rid of it!  man 1 indent

