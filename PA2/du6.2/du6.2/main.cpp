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
    
    public:
        string m_TypeName;
        size_t m_Size;
    
        CDataType() {}
        CDataType( const CDataType * o )
        {
            m_TypeName = o->m_TypeName;
            m_Size = o->m_Size;
        }
        virtual ~CDataType() {}
        virtual CDataType * clone( ) const
        {
            return new CDataType( this );
        }
        virtual size_t Sizeof() const
        {
            return m_Size;
        }
        virtual const CDataType & Field( const string & ) const
        {
            ostringstream oss;
            this -> print( oss );
            throw CSyntaxException( "No fields in type: " + oss.str() );
            return *this;
        }
        virtual const CDataType & Index() const
        {
            ostringstream oss;
            this -> print( oss );
            throw CSyntaxException( "Cannot index type: " + oss.str() );
            return *this;
        }
        virtual bool operator== ( const CDataType & s ) const
        {
            return m_TypeName == s.m_TypeName;
        }
        virtual bool operator!= ( const CDataType & s ) const
        {
            return m_TypeName != s.m_TypeName;
        }
        virtual string printBefore() const
        {
            return m_TypeName;
        }
        virtual string printAfter() const
        {
            return "";
        }
        virtual void print( ostream & os ) const
        {
            os << this->printBefore() << this->printAfter();
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
    
        virtual string printBefore() const
        {
            ostringstream os;
            os << "enum {\n";
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                os << m_Values[i];
                if ( i != m_Values.size() - 1 )
                    os << ",";
                os << "\n";
            }
            os << "}";
            return os.str();
        }
    
        virtual CDataType * clone() const
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
    
        const CDataType & Field( const string & name ) const
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
    
        virtual string printBefore() const
        {
            ostringstream os;
            os << "struct {\n";
            for ( size_t i = 0; i < m_Values.size(); i++ )
            {
                os << m_Values[i].first -> printBefore();
                os << " ";
                os << m_Values[i].second;
                os << m_Values[i].first -> printAfter();
                os << ";\n";
            }
            os << "}";
            return os.str();
        }
    
        virtual CDataType * clone() const
        {
            return new CDataTypeStruct( this );
        }
};

class CDataTypeArray : public CDataType
{
    private:
        const CDataType * m_Type;
    
    public:
        CDataTypeArray( size_t size, const CDataType & type )
        {
            m_Type = type.clone();
            m_Size = size;
            m_TypeName = "Array";
        }
        virtual const CDataType & Index() const
        {
            return *m_Type;
        }
        virtual string printBefore() const
        {
            return m_Type->printBefore();
        }
        virtual string printAfter() const
        {
            return string( "[" + to_string(m_Size) + "]" + m_Type->printAfter() );
        }
        virtual bool operator== ( const CDataType & o )
        {
            return m_TypeName == o.m_TypeName
                && m_Size == o.m_Size
                && m_Type == ((CDataTypeArray &) o).m_Type;
        }
        virtual bool operator!= ( const CDataType & o )
        {
            return ! operator== ( o );
        }
        virtual CDataType * clone() const
        {
            return new CDataTypeArray( *this );
        }
    
};

class CDataTypePtr : public CDataType
{
    private:
        const CDataType * m_Type;
    public:
        CDataTypePtr( const CDataType & type )
        {
            m_Type = type.clone();
            m_Size = 8;
            m_TypeName = "Pointer";
        }
        virtual const CDataType & Index() const
        {
            return *m_Type;
        }
        virtual string printBefore() const
        {
            string bef = m_Type->printBefore();
            if ( m_Type->m_TypeName == "Array" )
                bef += '(';
            bef += '*';
            return bef;
        }
        virtual string printAfter() const
        {
            string afterStr = m_Type->printAfter();
            if ( afterStr[0] == '[' )
                afterStr = ')' + afterStr;
            return afterStr;
        }
        virtual bool operator== ( const CDataType & o )
        {
            return m_TypeName == o.m_TypeName
                && m_Type == ((CDataTypePtr &) o).m_Type;
        }
        virtual bool operator!= ( const CDataType & o )
        {
            return ! operator== ( o );
        }
        virtual CDataType * clone() const
        {
            return new CDataTypePtr( *this );
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

  b . AddField ( "m_Other", a );

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
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      DEAD\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "  } m_Other;\n"
    "}") );

  assert ( whitespaceMatch ( b . Field ( "m_Other" ), "struct\n"
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

  assert ( whitespaceMatch ( b . Field ( "m_Other" ) . Field ( "m_Status" ), "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  DEAD\n"
    "}") );

  assert ( a . Sizeof () == 20 );
  assert ( b . Sizeof () == 32 );
  b . AddField ( "m_Other1", b );
  b . AddField ( "m_Other2", b );
  b . AddField ( "m_Other3", b );
  assert ( b . Field ( "m_Other3" ) . Field ( "m_Other2" ) . Field ( "m_Other1" ) == b . Field ( "m_Other1" ) );

  assert ( b . Sizeof () == 256);

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
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      DEAD\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "  } m_Other;\n"
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      READY\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        DEAD\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "    } m_Other;\n"
    "  } m_Other1;\n"
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      READY\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        DEAD\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "    } m_Other;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        READY\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "      struct\n"
    "      {\n"
    "        int m_Length;\n"
    "        enum\n"
    "        {\n"
    "          NEW,\n"
    "          FIXED,\n"
    "          BROKEN,\n"
    "          DEAD\n"
    "        } m_Status;\n"
    "        double m_Ratio;\n"
    "      } m_Other;\n"
    "    } m_Other1;\n"
    "  } m_Other2;\n"
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      READY\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        DEAD\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "    } m_Other;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        READY\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "      struct\n"
    "      {\n"
    "        int m_Length;\n"
    "        enum\n"
    "        {\n"
    "          NEW,\n"
    "          FIXED,\n"
    "          BROKEN,\n"
    "          DEAD\n"
    "        } m_Status;\n"
    "        double m_Ratio;\n"
    "      } m_Other;\n"
    "    } m_Other1;\n"
    "    struct\n"
    "    {\n"
    "      int m_Length;\n"
    "      enum\n"
    "      {\n"
    "        NEW,\n"
    "        FIXED,\n"
    "        BROKEN,\n"
    "        READY\n"
    "      } m_Status;\n"
    "      double m_Ratio;\n"
    "      struct\n"
    "      {\n"
    "        int m_Length;\n"
    "        enum\n"
    "        {\n"
    "          NEW,\n"
    "          FIXED,\n"
    "          BROKEN,\n"
    "          DEAD\n"
    "        } m_Status;\n"
    "        double m_Ratio;\n"
    "      } m_Other;\n"
    "      struct\n"
    "      {\n"
    "        int m_Length;\n"
    "        enum\n"
    "        {\n"
    "          NEW,\n"
    "          FIXED,\n"
    "          BROKEN,\n"
    "          READY\n"
    "        } m_Status;\n"
    "        double m_Ratio;\n"
    "        struct\n"
    "        {\n"
    "          int m_Length;\n"
    "          enum\n"
    "          {\n"
    "            NEW,\n"
    "            FIXED,\n"
    "            BROKEN,\n"
    "            DEAD\n"
    "          } m_Status;\n"
    "          double m_Ratio;\n"
    "        } m_Other;\n"
    "      } m_Other1;\n"
    "    } m_Other2;\n"
    "  } m_Other3;\n"
    "}" ) );

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
    cout << a . Field ( "m_Length" ) . Field ( "m_Foo" ) << endl;
    assert ( "Field: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( whitespaceMatch ( e . what (), "No fields in type: int" ));
  }

  try
  {
    cout << a . Field ( "m_Status" ) . Field ( "m_Foo" ) << endl;
    assert ( "Field: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( whitespaceMatch ( e . what (), "No fields in type: enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  DEAD\n"
    "}" ));
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
    assert ( string ( e . what () ) == "Duplicate enum value: FIRST" );
  }

  CDataTypeArray ar1 ( 10, CDataTypeInt () );
  assert ( whitespaceMatch ( ar1, "int[10]") );
  assert ( whitespaceMatch ( ar1 . Index (), "int") );
  
  CDataTypeArray ar2 ( 11, ar1 );
  assert ( whitespaceMatch ( ar2, "int[11][10]") );
  assert ( whitespaceMatch ( ar2 . Index (), "int[10]") );
  assert ( whitespaceMatch ( ar2 . Index () . Index (), "int") );
  
  CDataTypeArray ar3 ( 10, CDataTypeArray( 20, CDataTypePtr( CDataTypeInt() ) ) );
  assert ( whitespaceMatch ( ar3, "int*[10][20]") );
  assert ( whitespaceMatch ( ar3 . Index (), "int*[20]") );
  assert ( whitespaceMatch ( ar3 . Index () . Index (), "int*") );
  assert ( whitespaceMatch ( ar3 . Index () . Index () . Index (), "int") );

  CDataTypePtr ar4  ( ar1 . Index () );
  assert ( whitespaceMatch ( ar4, "int*") );
  assert ( whitespaceMatch ( ar4 . Index (), "int") );

  CDataTypePtr ar5  ( b . Field ( "m_Status" ) );
  assert ( whitespaceMatch ( ar5, "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  READY\n"
    "}*") );
  assert ( whitespaceMatch ( ar5 . Index (), "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  READY\n"
    "}") );

  CDataTypePtr ar6 ( ar3 . Index () . Index () );
  assert ( whitespaceMatch ( ar6, "int**") );
  assert ( whitespaceMatch ( ar6 . Index (), "int*") );
  assert ( whitespaceMatch ( ar6 . Index () . Index (), "int") );

  CDataTypePtr ar7 ( CDataTypeArray ( 50, ar6 ) );
  assert ( whitespaceMatch ( ar7, "int**(*)[50]") );
  assert ( whitespaceMatch ( ar7 . Index (), "int**[50]") );
  assert ( whitespaceMatch ( ar7 . Index () . Index (), "int**") );
  assert ( whitespaceMatch ( ar7 . Index () . Index () . Index (), "int*") );
  assert ( whitespaceMatch ( ar7 . Index () . Index () . Index () . Index (), "int") );
  
  CDataTypeArray ar8 ( 25, ar7 );
  assert ( whitespaceMatch ( ar8, "int**(*[25])[50]") );

  CDataTypePtr ar9 ( ar8 );
  assert ( whitespaceMatch ( ar9, "int**(*(*)[25])[50]") );
  
  a . AddField ( "m_Ar1", ar1 ) . 
      AddField ( "m_Ar2", ar2 ) . 
      AddField ( "m_Ar3", ar3 ) . 
      AddField ( "m_Ar4", ar4 ) . 
      AddField ( "m_Ar5", ar5 ) . 
      AddField ( "m_Ar6", ar6 ) . 
      AddField ( "m_Ar7", ar7 ) . 
      AddField ( "m_Ar8", ar8 ) . 
      AddField ( "m_Ar9", ar9 );
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
    "  int m_Ar1[10];\n"
    "  int m_Ar2[11][10];\n"
    "  int* m_Ar3[10][20];\n"
    "  int* m_Ar4;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  }* m_Ar5;\n"
    "  int** m_Ar6;\n"
    "  int**(* m_Ar7)[50];\n"
    "  int**(* m_Ar8[25])[50];\n"
    "  int**(*(* m_Ar9)[25])[50];\n"
    "}") );
    
  a . AddField ( "m_Madness", CDataTypeArray ( 40, CDataTypePtr ( a ) ) );
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
    "  int m_Ar1[10];\n"
    "  int m_Ar2[11][10];\n"
    "  int* m_Ar3[10][20];\n"
    "  int* m_Ar4;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  }* m_Ar5;\n"
    "  int** m_Ar6;\n"
    "  int**(* m_Ar7)[50];\n"
    "  int**(* m_Ar8[25])[50];\n"
    "  int**(*(* m_Ar9)[25])[50];\n"
    "  struct\n"
    "  {\n"
    "    int m_Length;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      DEAD\n"
    "    } m_Status;\n"
    "    double m_Ratio;\n"
    "    int m_Sum;\n"
    "    int m_Ar1[10];\n"
    "    int m_Ar2[11][10];\n"
    "    int* m_Ar3[10][20];\n"
    "    int* m_Ar4;\n"
    "    enum\n"
    "    {\n"
    "      NEW,\n"
    "      FIXED,\n"
    "      BROKEN,\n"
    "      READY\n"
    "    }* m_Ar5;\n"
    "    int** m_Ar6;\n"
    "    int**(* m_Ar7)[50];\n"
    "    int**(* m_Ar8[25])[50];\n"
    "    int**(*(* m_Ar9)[25])[50];\n"
    "  }* m_Madness[40];\n"
    "}") );
  assert ( a . Field ( "m_Madness" ) . Index () . Index () . Field ( "m_Ar9" ) == a . Field ( "m_Ar9" ));
  assert ( a . Field ( "m_Madness" ) . Index () . Index () . Field ( "m_Ar9" ) != a . Field ( "m_Ar8" ));
  try
  {
    cout << ar2 . Field ( "m_Foo" ) << endl;
    assert ( "Field: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( whitespaceMatch ( e . what (), "No fields in type: int[11][10]" ));
  }

  try
  {
    cout << c . Index() << endl;
    assert ( "Field: missing exception!" == NULL );
  }
  catch ( const exception & e )
  {
    assert ( whitespaceMatch ( e . what (), "Cannot index type: struct\n"
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
    "}" ));
  }
  
  return 0;
}
#endif /* __PROGTEST__ */
