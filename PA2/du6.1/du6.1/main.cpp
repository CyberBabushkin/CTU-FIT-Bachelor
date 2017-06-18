#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <exception>
#include <typeinfo>

#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <unordered_map>
#include <unordered_set>
#include <memory>
#endif /* C++ 11 */
using namespace std;

class CSyntaxException : public exception
{
  public: 
    //------------------------------------------------------------//
      CSyntaxException( const string & desc ) : m_Desc ( desc ) {}
    //------------------------------------------------------------//
    virtual const char * what( void ) const noexcept
    {
        return m_Desc.c_str( );
    }
    //------------------------------------------------------------//
  private:
    string m_Desc;
};
#endif /* __PROGTEST__ */
class CDataTypeStruct;
class CDataTypeEnum;

class CDataType
{
    friend CDataTypeStruct;
    friend CDataTypeEnum;
    protected:
        string m_TypeName;
        size_t m_Size;
    public:
        CDataType() {}
        virtual ~CDataType() {}
        CDataType( const CDataType * o )
        {
            m_TypeName = o->m_TypeName;
            m_Size = o->m_Size;
        }
        virtual CDataType * clone( ) const
        {
            return new CDataType( this );
        }
        virtual size_t Sizeof() const
        {
            return m_Size;
        }
        virtual bool operator== ( const CDataType & s ) const
        {
            return m_TypeName == s.m_TypeName;
        }
        virtual bool operator!= ( const CDataType & s ) const
        {
            return m_TypeName != s.m_TypeName;
        }
        virtual void print( ostream & os ) const
        {
            os << m_TypeName;
        }
        friend ostream & operator<< ( ostream & os, const CDataType & d );
};

class CDataTypeInt : public CDataType
{
    
    public:
        CDataTypeInt()
        {
            m_Size = 4;
            m_TypeName = "int";
        }
};

class CDataTypeDouble : public CDataType
{
    public:
        CDataTypeDouble()
        {
            m_Size = 8;
            m_TypeName = "double";
        }
};

class CDataTypeEnum : public CDataType
{
        vector<string> m_Values;
    public:
        CDataTypeEnum()
        {
            m_Size = 4;
            m_TypeName = "enum";
            m_Values.resize(0);
        }
    
        CDataTypeEnum( const CDataTypeEnum * o )
        {
            m_Size = o->m_Size;
            m_TypeName = o->m_TypeName;
            m_Values = o->m_Values;
        }
    
        CDataTypeEnum & Add( const string & a )
        {
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                if ( a == m_Values[i] ) throw CSyntaxException( "Duplicate enum value: " + a );
            }
            m_Values.push_back( a );
            return *this;
        }
    
        virtual void print( ostream & os ) const
        {
            os << "enum {\n";
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                os << m_Values[i];
                if ( i != m_Values.size() - 1 )
                    os << ",";
                os << "\n";
            }
            os << "}";
        }
    
        virtual CDataTypeEnum * clone() const
        {
            return new CDataTypeEnum( this );
        }
    
        virtual bool operator== ( const CDataType & ob ) const
        {
            CDataType * o = ob.clone();
            bool flag = true;
            if ( o->m_TypeName != m_TypeName
                || m_Values != ((CDataTypeEnum *)o)->m_Values ) flag = false;
            delete o;
            return flag;
        }
    
        virtual bool operator!= ( const CDataType & o ) const
        {
            return ! operator==( o );
        }
};

class CDataTypeStruct : public CDataType
{
    vector<pair<CDataType *, string>> m_Values;
    public:
        CDataTypeStruct()
        {
            m_Size = 0;
            m_TypeName = "struct";
            m_Values.resize(0);
        }
    
        CDataTypeStruct( const CDataTypeStruct * o )
        {
            m_Size = o->m_Size;
            m_TypeName = o->m_TypeName;
            
            for ( size_t i = 0; i < o->m_Values.size(); i++ )
            {
                m_Values.push_back( make_pair( o->m_Values[i].first->clone(),
                                               o->m_Values[i].second ) );
            }
        }
    
        CDataTypeStruct( const CDataTypeStruct & o )
        {
            m_Size = o.m_Size;
            m_TypeName = o.m_TypeName;
            
            for ( size_t i = 0; i < o.m_Values.size(); i++ )
            {
                m_Values.push_back( make_pair( o.m_Values[i].first->clone(),
                                               o.m_Values[i].second ) );
            }
        }
    
        virtual ~CDataTypeStruct()
        {
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                delete m_Values[i].first;
            }
        }
    
        CDataTypeStruct & AddField( const string & name, const CDataType & type )
        {
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                if ( m_Values[ i ].second == name )
                    throw CSyntaxException( "Duplicate field: " + name );
            }
            CDataType * sh = type.clone();
            m_Values.push_back( make_pair( sh, name ) );
            m_Size += sh->Sizeof();
            return *this;
        }
    
        CDataType & Field( const string & name )
        {
            CDataType * found = nullptr;
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                if ( m_Values[ i ].second == name )
                {
                    found = m_Values[i].first;
                    break;
                }
            }
            if ( ! found )
            {
                throw CSyntaxException( "Unknown field: " + name );
            }
            return *found;
        }
    
        virtual bool operator== ( const CDataType & ob ) const
        {
            CDataType * o = ob.clone();
            bool flag = true;
            if ( o->m_TypeName != m_TypeName
                || m_Values.size() != ((CDataTypeStruct *)o)->m_Values.size() ) flag = false;
            if ( flag )
                for ( size_t i = 0; i < m_Values.size(); i++ )
                {
                    if ( *m_Values[i].first != *((CDataTypeStruct *)&*o)->m_Values[i].first )
                    { flag = false; break; }
                }
            delete o;
            return flag;
        }
    
        virtual bool operator!= ( const CDataType & o ) const
        {
            return ! operator==( o );
        }
    
        virtual void print( ostream & os ) const
        {
            os << "struct {\n";
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                m_Values[i].first -> print( os );
                os << " ";
                os << m_Values[i].second << ";\n";
            }
            os << "}";
        }
    
        virtual CDataTypeStruct * clone() const
        {
            return new CDataTypeStruct( this );
        }
};

ostream & operator<< ( ostream & os, const CDataType & d )
{
    d.print( os );
    return os;
}

#ifndef __PROGTEST__
//-------------------------------------------------------------------------------------------------
static bool        whitespaceMatch                         ( const string    & out,
                                                             const string    & ref )
{
  const char * o = out . c_str ();
  const char * r = ref . c_str ();
  
  while ( 1 )
  {
    while ( isspace ( *o )) o ++;
    while ( isspace ( *r )) r ++;
    if ( ! *r && ! *o ) return true;
    if ( ! *r || ! *o || *r++ != *o++ ) return false;
  }
}
//-------------------------------------------------------------------------------------------------
template <typename _T>
static bool        whitespaceMatch                         ( const _T        & x,
                                                             const string    & ref )
{
  ostringstream oss;
  oss << x;
  return whitespaceMatch ( oss . str (), ref );
}
//-------------------------------------------------------------------------------------------------
int                main                                    ( void )
{
  CDataTypeStruct  a = CDataTypeStruct () .
                        AddField ( "m_Length", CDataTypeInt () ) .
                        AddField ( "m_Status", CDataTypeEnum () . 
                          Add ( "NEW" ) . 
                          Add ( "FIXED" ) . 
                          Add ( "BROKEN" ) . 
                          Add ( "DEAD" ) ).
                        AddField ( "m_Ratio", CDataTypeDouble () );
  
  CDataTypeStruct b = CDataTypeStruct () .
                        AddField ( "m_Length", CDataTypeInt () ) .
                        AddField ( "m_Status", CDataTypeEnum () . 
                          Add ( "NEW" ) . 
                          Add ( "FIXED" ) . 
                          Add ( "BROKEN" ) . 
                          Add ( "READY" ) ).
                        AddField ( "m_Ratio", CDataTypeDouble () );
  
  CDataTypeStruct c =  CDataTypeStruct () .
                        AddField ( "m_First", CDataTypeInt () ) .
                        AddField ( "m_Second", CDataTypeEnum () . 
                          Add ( "NEW" ) . 
                          Add ( "FIXED" ) . 
                          Add ( "BROKEN" ) . 
                          Add ( "DEAD" ) ).
                        AddField ( "m_Third", CDataTypeDouble () );

  CDataTypeStruct  d = CDataTypeStruct () .
                        AddField ( "m_Length", CDataTypeInt () ) .
                        AddField ( "m_Status", CDataTypeEnum () . 
                          Add ( "NEW" ) . 
                          Add ( "FIXED" ) . 
                          Add ( "BROKEN" ) . 
                          Add ( "DEAD" ) ).
                        AddField ( "m_Ratio", CDataTypeInt () );
  
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( c, "struct\n"
    "{\n"
    "  int m_First;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Second;\n"
    "  double m_Third;\n"
    "}") );

  assert ( whitespaceMatch ( d, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  int m_Ratio;\n"
    "}") );

  assert ( a != b );
  assert ( a == c );
  assert ( a != d );
  assert ( a != CDataTypeInt() );
  assert ( whitespaceMatch ( a . Field ( "m_Status" ), "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  DEAD\n"
    "}") );

  b . AddField ( "m_Other", CDataTypeDouble ());

  a . AddField ( "m_Sum", CDataTypeInt ());

  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  int m_Sum;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  double m_Other;\n"
    "}") );

  assert ( a . Sizeof () == 20 );
  assert ( b . Sizeof () == 24 );
  try
  {
    a . AddField ( "m_Status", CDataTypeInt () );
    assert ( "AddField: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( string ( e . what () ) == "Duplicate field: m_Status" );
  }

  try
  {
    cout << a . Field ( "m_Fail" ) << endl;
    assert ( "Field: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( string ( e . what () ) == "Unknown field: m_Fail" );
  }
  
  try
  {
    CDataTypeEnum en;
    en . Add ( "FIRST" ) .
         Add ( "SECOND" ) .
         Add ( "FIRST" );
    assert ( "Add: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( string ( e . what () ) ==  "Duplicate enum value: FIRST" );
  }
  return 0;
}
#endif /* __PROGTEST__ */
