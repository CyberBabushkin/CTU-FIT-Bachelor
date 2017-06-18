#ifndef __PROGTEST__
#include <cstdio>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class InvalidDateException
{
};

//============================================================================//

const string stdFmt = "%Y-%m-%d";
string formats[10000000];
int freePoint = 0;

class date_format {
    string fmtStr;
public:
    date_format( const char * fmt ) : fmtStr( fmt ) {};
    friend ostream & operator<< ( ostream &, const date_format & );
    friend istream & operator>> ( istream &, const date_format & );
};

ostream & operator<< ( ostream & ios, const date_format & fmt )
{
    formats[freePoint] = fmt.fmtStr;
    ios.pword(0) = const_cast<string*>(&(formats[freePoint++]));
    return ios;
}

istream & operator>> ( istream & ios, const date_format & fmt )
{
    formats[freePoint] = fmt.fmtStr;
    ios.pword(0) = const_cast<string*>(&(formats[freePoint++]));
    return ios;
}

class CDate
{
    int m_Year, m_Month, m_Day;
    int m_AllDays;
    
    void recalculateAllDays( void );
    void recalculateDate( void );
    
public:
    CDate( int, int, int );
    CDate( int );
    
    CDate operator + ( CDate & ) const;
    CDate operator + ( int ) const;
    int operator - ( CDate & ) const;
    CDate operator - ( int ) const;
    bool operator == ( CDate & ) const;
    bool operator == ( int ) const;
    bool operator != ( CDate & ) const;
    bool operator != ( int ) const;
    bool operator < ( CDate & ) const;
    bool operator < ( int ) const;
    bool operator > ( CDate & ) const;
    bool operator > ( int ) const;
    bool operator <= ( CDate & ) const;
    bool operator <= ( int ) const;
    bool operator >= ( CDate & ) const;
    bool operator >= ( int ) const;
    friend CDate & operator += ( CDate &, int );
    friend int operator += ( int, CDate & );
    friend CDate & operator -= ( CDate &, int );
    friend int operator -= ( int, CDate & );
    CDate & operator ++ ();
    CDate operator ++ ( int );
    CDate & operator -- ();
    CDate operator -- ( int );
    friend ostream & operator<< ( ostream &, const CDate & );
    friend istream & operator>> ( istream &, CDate & );
};

CDate::CDate( int year, int month, int day ) : m_AllDays( 0 )
{
    m_Year = year;
    m_Day = day;
    m_Month = month;
    recalculateAllDays();
}

CDate::CDate( int allDays )
{
    m_AllDays = allDays;
    recalculateDate();
}

void CDate::recalculateAllDays()
{
    int numberOfDays[12] = {31, 111666111, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ( m_Year < 1996 || m_Year > 2050 || m_Month > 12 || m_Month < 1 || m_Day < 1 )
        throw InvalidDateException();
    
    /* Calculates if the year is leap or not */
    if ( m_Year % 4 == 0 && m_Year % 4000 != 0 && (m_Year % 400 == 0 || m_Year % 100 != 0) )
        numberOfDays[1] = 29;
    else
        numberOfDays[1] = 28;
    
    if ( numberOfDays[m_Month - 1] < m_Day )
        throw InvalidDateException();
    
    m_AllDays = 0;
    for ( int i = 1996; i < m_Year ; i ++ )
        if ( i % 4 == 0 && i % 4000 != 0 && (i % 400 == 0 || i % 100 != 0) )
            m_AllDays += 366;
        else
            m_AllDays += 365;
    for ( int i = 1; i < m_Month; i++ )
        m_AllDays += numberOfDays[i - 1];
    m_AllDays += m_Day - 1;
}

void CDate::recalculateDate( void )
{
    if ( m_AllDays < 0 ) throw InvalidDateException();
    int tmp = m_AllDays;
    
    int numberOfDays[12] = {31, 111666111, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    m_Year = 1996;
    
    while ( 1 ) { // full years
        if ( m_Year % 4 == 0 && m_Year % 4000 != 0 && (m_Year % 400 == 0 || m_Year % 100 != 0) )
        {
            if ( m_AllDays - 366 >= 0 )
            {
                m_AllDays -= 366;
                m_Year ++;
            }
            else
                break;
        }
        else
        {
            if ( m_AllDays - 365 >= 0 )
            {
                m_AllDays -= 365;
                m_Year ++;
            }
            else
                break;
        }
    }
    
    if ( m_Year > 2050 ) throw InvalidDateException();
    
    m_Month = 1;
    if ( m_Year % 4 == 0 && m_Year % 4000 != 0 && (m_Year % 400 == 0 || m_Year % 100 != 0) )
        numberOfDays[1] = 29;
    else
        numberOfDays[1] = 28;
    
    while ( 1 ) { // full months
        
        if ( m_AllDays - numberOfDays[m_Month - 1] >= 0 )
        {
            m_AllDays -= numberOfDays[m_Month - 1];
            m_Month ++;
        }
        else
            break;
    }
    m_Day = m_AllDays + 1;
    m_AllDays = tmp;
}

CDate CDate::operator + ( CDate & date ) const
{
    return CDate( m_AllDays + date.m_AllDays );
}
CDate CDate::operator + ( int days ) const
{
    return CDate( m_AllDays + days );
}
int CDate::operator - ( CDate & date ) const
{
    return m_AllDays - date.m_AllDays;
}
CDate CDate::operator - ( int days ) const
{
    return CDate( m_AllDays - days );
}
bool CDate::operator == ( CDate & date ) const
{
    return date.m_AllDays == m_AllDays;
}
bool CDate::operator == ( int days ) const
{
    return m_AllDays == days;
}
bool CDate::operator != ( CDate & date ) const
{
    return date.m_AllDays != m_AllDays;
}
bool CDate::operator != ( int days ) const
{
    return days != m_AllDays;
}
bool CDate::operator < ( CDate & date ) const
{
    return m_AllDays < date.m_AllDays;
}
bool CDate::operator < ( int days ) const
{
    return m_AllDays < days;
}
bool CDate::operator > ( CDate & date ) const
{
    return m_AllDays > date.m_AllDays;
}
bool CDate::operator > ( int days ) const
{
    return m_AllDays > days;
}
bool CDate::operator <= ( CDate & date ) const
{
    return m_AllDays <= date.m_AllDays;
}
bool CDate::operator <= ( int days ) const
{
    return m_AllDays <= days;
}
bool CDate::operator >= ( CDate & date ) const
{
    return m_AllDays >= date.m_AllDays;
}
bool CDate::operator >= ( int days ) const
{
    return m_AllDays >= days;
}
CDate & operator += ( CDate & date, int num )
{
    date.m_AllDays += num;
    date.recalculateDate();
    return date;
}
int operator += ( int num, CDate & date )
{
    int rNum = num + date.m_AllDays;
    return rNum;
}
CDate & operator -= ( CDate & date, int num )
{
    date.m_AllDays -= num;
    date.recalculateDate();
    return date;
}
int operator -= ( int num, CDate & date )
{
    int rNum = num + date.m_AllDays;
    return rNum;
}
CDate & CDate::operator ++ ()
{
    m_AllDays++;
    recalculateDate();
    return *this;
}
CDate CDate::operator ++ ( int )
{
    CDate tmp( m_AllDays );
    operator++();
    return tmp;
}
CDate & CDate::operator -- ()
{
    m_AllDays--;
    recalculateDate();
    return *this;
}
CDate CDate::operator -- ( int )
{
    CDate tmp( m_AllDays );
    operator--();
    return tmp;
}

int convertCharToInt( char chr[], int size )
{
    int k = 0;
    if ( size == 4 )
    {
        int a = chr[0] - '0';
        int b = chr[1] - '0';
        int c = chr[2] - '0';
        int d = chr[3] - '0';
        if ( a < 0 || a > 9
            || b < 0 || b > 9
            || c < 0 || c > 9
            || d < 0 || d > 9 ) return 0;
        k = a * 1000 + b * 100 + c * 10 + d;
    } else
    {
        int a = chr[0] - '0';
        int b = chr[1] - '0';
        if ( a < 0 || a > 9
            || b < 0 || b > 9 ) return 0;
        k = a * 10 + b;
    }
    return k;
}

ostream & operator<< ( ostream & str, const CDate & date )
{
    if ( ! str.pword(0) )
    {
        formats[freePoint] = stdFmt;
        str.pword(0) = const_cast<string*>(&(formats[freePoint++]));
    }
    
    string rrr = *((string*)str.pword(0));
    char * fmtString = const_cast<char*>(rrr.c_str());
    
    while ( 1 )
    {
        if ( *fmtString == '%' )
        {
            fmtString++;
            if ( *fmtString == 'Y' )
                str << date.m_Year;
            else if ( *fmtString == 'm' )
                str << right << setfill('0') << setw(2) << date.m_Month;
            else if ( *fmtString == 'd' )
                str << right << setfill('0') << setw(2) << date.m_Day;
            else
            {
                if ( *fmtString == 0 )
                {
                    str.setstate(str.failbit);
                    break;
                }
                str << *fmtString;
            }
        } else
            str << *fmtString;
        fmtString++;
        if ( *fmtString == 0 )
            break;
    }
    
    return str;
}

istream & operator>> ( istream & str, CDate & date )
{
    if ( ! str.pword(0) )
    {
        formats[freePoint] = stdFmt;
        str.pword(0) = const_cast<string*>(&(formats[freePoint++]));
    }
    
    string rrr = *((string*)str.pword(0));
    char * fmtString = const_cast<char*>(rrr.c_str());
    
    int yearBc = 0;
    int monthBc = 0;
    int dayBc = 0;
    char buffer[4];
    bool dateRead[3];
    dateRead[0] = false; dateRead[1] = false; dateRead[2] = false;
    
    stringstream ss;
    ss << str.rdbuf();
    
    const char * inoutStr = ss.str().c_str();
    
    while ( 1 )
    {
        if ( *fmtString == '%' )
        {
            fmtString++;
            if ( *fmtString == 'Y' )
            {
                if ( dateRead[0] ) { str.setstate(ios_base::failbit); break; }
                
                // Reads year
                buffer[0] = *(inoutStr++);
                buffer[1] = *(inoutStr++);
                buffer[2] = *(inoutStr++);
                buffer[3] = *(inoutStr++);
                int year = convertCharToInt( buffer, 4 );
                if ( ! year ) {
                    str.setstate(ios_base::failbit);
                    break;
                }
                yearBc = year;
                dateRead[0] = true;
                
            } else if ( *fmtString == 'm' )
            {
                if ( dateRead[1] ) { str.setstate(ios_base::failbit); break; }
                
                // Reads month
                buffer[0] = *(inoutStr++);
                buffer[1] = *(inoutStr++);
                int month = convertCharToInt( buffer, 2 );
                if ( ! month ) {
                    str.setstate(ios_base::failbit);
                    break;
                }
                monthBc = month;
                
                dateRead[1] = true;
            } else if ( *fmtString == 'd' )
            {
                if ( dateRead[2] ) { str.setstate(ios_base::failbit); break; }
                
                buffer[0] = *(inoutStr++);
                buffer[1] = *(inoutStr++);
                int day = convertCharToInt( buffer, 2 );
                if ( ! day ) {
                    str.setstate(ios_base::failbit);
                    break;
                }
                dayBc = day;
                
                dateRead[2] = true;
            } else { // we have another char after %
                char found = *fmtString;
                char charInString = *inoutStr;
                inoutStr++;
                if ( found == 0 || charInString == 0 || found != charInString )
                {
                    str.setstate(ios_base::failbit);
                    break;
                }
            }
        } else
        {
            char found = *fmtString;
            char charInString = *inoutStr;
            inoutStr++;
            if ( found != charInString )
            {
                str.setstate(ios_base::failbit);
                break;
            }
        }
        
        fmtString++;
        
        if ( *fmtString == 0 )
        {
            if ( *fmtString != *inoutStr ) {
                str.setstate(ios_base::failbit);
            }
            break;
        }
    }
    
    if ( str.fail() || ! dateRead[0] || ! dateRead[1] || ! dateRead[2] )
    {
        str.setstate(ios_base::failbit);
        return str;
    }
    
    try {
        CDate b( yearBc, monthBc, dayBc );
        
        date.m_Year = yearBc;
        date.m_Month = monthBc;
        date.m_Day = dayBc;
        date.recalculateAllDays();
    } catch (...) {
        str.setstate(ios_base::failbit);
    }
    
    return str;
}

#ifndef __PROGTEST__
int main(int argc, const char * argv[]) {
    ostringstream oss;
    istringstream iss;
    
    CDate a ( 2000, 1, 2 );
    CDate b ( 2010, 2, 3 );
    CDate c ( 2004, 2, 10 );
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2000-01-02" );
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2010-02-03" );
    oss . str ("");
    oss << c;
    assert ( oss . str () == "2004-02-10" );
    a = a + 1500;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2004-02-10" );
    b = b - 2000;
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2004-08-13" );
    assert ( b - a == 185 );
    assert ( ( b == a ) == false );
    assert ( ( b != a ) == true );
    assert ( ( b <= a ) == false );
    assert ( ( b < a ) == false );
    assert ( ( b >= a ) == true );
    assert ( ( b > a ) == true );
    assert ( ( c == a ) == true );
    assert ( ( c != a ) == false );
    assert ( ( c <= a ) == true );
    assert ( ( c < a ) == false );
    assert ( ( c >= a ) == true );
    assert ( ( c > a ) == false );
    a = ++c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-11" );
    a = --c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-10" );
    a = c++;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-11" );
    a = c--;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-10" );
    iss . clear ();
    iss . str ( "2015-09-03" );
    assert ( ( iss >> a ) );
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-09-03" );
    a = a + 70;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-11-12" );
    
    CDate d ( 2000, 1, 1 );
    try
    {
        CDate e ( 2000, 32, 1 );
        assert ( "No exception thrown!" == NULL );
    }
    catch ( ... )
    {
    }
    iss . clear ();
    iss . str ( "2000-12-33" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-11-31" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-02-29" );
    assert ( ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );
    iss . clear ();
    iss . str ( "2001-02-29" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );
    
    //=============================================================================
    // bonus tests
    //=============================================================================
    
    CDate f ( 2000, 5, 12 );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2000-05-12" );
    oss . str ("");
    oss << date_format ( "%Y/%m/%d" ) << f;
    assert ( oss . str () == "2000/05/12" );
    oss . str ("");
    oss << date_format ( "%d.%m.%Y" ) << f;
    assert ( oss . str () == "12.05.2000" );
    oss . str ("");
    oss << date_format ( "%m/%d/%Y" ) << f;
    assert ( oss . str () == "05/12/2000" );
    oss . str ("");
    oss << date_format ( "%Y%m%d" ) << f;
    assert ( oss . str () == "20000512" );
    oss . str ("");
    oss << date_format ( "hello kitty" ) << f;
    assert ( oss . str () == "hello kitty" );
    oss . str ("");
    oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
    assert ( oss . str () == "121212121212050505200020002000%%%%%" );
    oss . str ("");
    oss << date_format ( "%Y-%m-%d" ) << f;
    assert ( oss . str () == "2000-05-12" );
    iss . clear ();
    iss . str ( "2001-01-02" );
    assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2001-01-02" );
    iss . clear ();
    iss . str ( "05.06.2003" );
    assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2003-06-05" );
    iss . clear ();
    iss . str ( "07/08/2004" );
    assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2004-07-08" );
    iss . clear ();
    iss . str ( "2002*03*04" );
    assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2002-03-04" );
    iss . clear ();
    iss . str ( "C++09format10PA22006rulez" );
    assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2006-09-10" );
    iss . clear ();
    iss . str ( "%12%13%2010%" );
    assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2010-12-13" );
    
    CDate g ( 2000, 6, 8 );
    iss . clear ();
    iss . str ( "2001-11-33" );
    assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "29.02.2003" );
    assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "14/02/2004" );
    assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "2002-03" );
    assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "hello kitty" );
    assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "2005-07-12-07" );
    assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    
    
    
    
    f = CDate ( 2000, 6, 6 );
    iss . clear ();
    iss . str ("08|2000-08%");
    assert ( ! ( iss >> date_format ( "%m|%Y-%d%%%" ) >> f ) ); //procento navic
    oss . str ( "" );
    oss << date_format ( "%m|%Y-%d%%%" ); // procento navic
    assert ( ! ( oss << f ) );
    oss . str ( "" );
    oss . clear ();
    oss << date_format ( "%m|%Y-%d%%" ); // ok
    assert ( oss << f );
    assert ( oss . str () == "06|2000-06%" );
    
    ostringstream oss2;
    oss2 . str ( "" );
    char * format = new char[7];
    format[0]='%';
    format[1]='Y';
    format[2]='%';
    format[3]='m';
    format[4]='%';
    format[5]='d';
    format[6]=0;
    oss2 << date_format(format);
    delete [] format; // zde smazu odkaz na format, ale stream by s
                      //timhle nemel byt problem a dale tisknout podle toho formatu
    //format[0]='g';
    oss2 << f;
    assert(oss2 . str () == "20000606");
    assert(oss . str () == "06|2000-06%"); // oss porad obsahuje svuj formatovaci retezec
    
    oss2 . copyfmt ( oss ); // kopie flagu vcetne formatu
    oss2 . str ( "" );
    oss2 << f;
    oss << date_format ( "%Y-mmm%m-%d"); // jiny format nez pro oss2
    oss . str ( "" );
    oss << f;
    assert ( oss2 . str () == "06|2000-06%" );
    assert ( oss . str () == "2000-mmm06-06" );
    
    ostringstream s1, s2;
    
    s1 << date_format ("format1 %Y%%%m%%%d ");
    s2 << date_format ("format2 %d%%%m%%%Y ");
    CDate date1(2000, 1, 1);
    CDate date2(2000, 2, 2);
    s1 << date1;
    s2 << date1;
    s1 << date2;
    s2 << date2;
    assert( s1.str() == "format1 2000%01%01 format1 2000%02%02 " );
    assert( s2.str() == "format2 01%01%2000 format2 02%02%2000 " );
    
    iss.clear();
    oss.clear();
    oss.str( "" );
    iss . str ("%%RRY200010D12jdsfhdsfkj10%");
    assert( iss >> date_format("%%%%%R%RY%Y%m%D%djdsfhdsfkj%10%%") >> date1 );
    assert( oss << date_format("%%%%%R%RY%Y%m%D%djdsfhdsfkj%m%%%m%m%m%m%y%y%Y") << date1 );
    assert( oss.str() == "%%RRY200010D12jdsfhdsfkj10%10101010yy2000" );
    
    iss.clear();
    oss.clear();
    oss.str( "" );
    iss . str ("%%%%%%%%%%%%%%%%%%%%%%%%%");
    iss >> date_format("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    assert( ! ( iss >> date_format("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%") >> date1) );
    assert( ! ( oss << date_format("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%") << date1 ) );
    //assert( oss.str() == "" );
    
    oss.clear();
    iss.clear();
    oss.str( "" );
    iss.str( "sdsf20010229%" );
    assert( !(iss >> date_format("sdsf%Y%m%d%%") >> date1) );
    
    istringstream iss100, iss200;
    ostringstream oss100, oss200;
    CDate a100(2000, 12, 14);
    CDate a200(2016, 5, 28 );
    iss100 >> date_format("%m%d%Y");
    iss200 >> date_format("%Y%d%m");
    oss200 << date_format("%m%d%Y");
    oss100 << date_format("%Y%d%m");
    
    iss100.str( "12152002" );
    iss200.str( "19962805" );
    
    assert( iss100 >> a100 );
    assert( iss200 >> a200 );
    
    assert( oss100 << a100 );
    assert( oss200 << a200 );
    assert( oss100.str() == "20021512" );
    assert( oss200.str() == "05281996" );
    
    iss100.str( "11142001" );
    iss200.str( "19972906" );
    
    assert( iss100 >> a100 );
    assert( iss200 >> a200 );
    
    oss100.str( "" );
    oss200.str( "" );
    
    assert( oss100 << a100 );
    assert( oss200 << a200 );
    assert( oss100.str() == "20011411" );
    assert( oss200.str() == "06291997" );
    
    return 0;
}
#endif
