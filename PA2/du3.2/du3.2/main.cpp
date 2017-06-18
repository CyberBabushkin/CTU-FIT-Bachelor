#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <memory>
#endif /* C++ 11 */
using namespace std;
#endif /* __PROGTEST__ */

class CPolynomial
{
private:
    
    vector<double> coefs;
    
public:
    
    CPolynomial operator + ( const CPolynomial & ) const;
    CPolynomial operator - ( const CPolynomial & ) const;
    CPolynomial operator * ( const CPolynomial & ) const;
    CPolynomial operator * ( double ) const;
    double & operator[] ( unsigned long );
    double operator[] ( const unsigned long ) const;
    double operator() ( double ) const;
    bool operator == ( const CPolynomial & ) const;
    bool operator != ( const CPolynomial & ) const;
    
    //CPolynomial & operator = ( CPolynomial & );
    friend ostream & operator<< ( ostream &, const CPolynomial );
    const vector<double> & getCoefs() const { return coefs; }
    unsigned long Degree() const;
    
};

bool compareDoubles( double a,
               double b )
{
    double r = a > b ? a - b : b - a;
    if ( r < 10e-12 ) return true;
    return false;
}

CPolynomial CPolynomial::operator+ ( const CPolynomial & second ) const
{
    unsigned long size1 = coefs.size(), size2 = second.coefs.size();
    unsigned long size = size1 > size2 ? size1 : size2;
    
    CPolynomial r;
    r.coefs.resize(size);
    for ( unsigned long i = 0; i < size; i++ )
    {
        r.coefs[i] = 0;
        if ( i < coefs.size() ) r.coefs[i] = coefs[i] + r.coefs[i];
        if ( i < second.coefs.size() ) r.coefs[i] = second.coefs[i] + r.coefs[i];
    }
    return r;
}
CPolynomial CPolynomial::operator- ( const CPolynomial & second ) const
{
    unsigned long size1 = coefs.size(), size2 = second.coefs.size();
    
    unsigned long size = size1 > size2 ? size1 : size2;
    
    CPolynomial r;
    r.coefs.resize(size);
    for ( unsigned long i = 0; i < size; i++ )
    {
        r.coefs[i] = 0;
        if ( i < coefs.size() ) r.coefs[i] = coefs[i] + r.coefs[i];
        if ( i < second.coefs.size() ) r.coefs[i] = r.coefs[i] - second.coefs[i];
    }
    return r;
}
CPolynomial CPolynomial::operator* ( double num ) const
{
    unsigned long size = Degree();
    CPolynomial r;
    if ( ! size && ! coefs.size() ) return r;
    r.coefs.resize(size + 1);
    for ( unsigned long i = 0; i <= size; i++ )
    {
        r.coefs[i] = num;
        r.coefs[i] = coefs[i] * r.coefs[i];
    }
    return r;
}
double & CPolynomial::operator[] ( unsigned long index )
{
    if ( index + 1 > coefs.size() ) coefs.resize( index + 1, 0. );
    return coefs[index];
}
double CPolynomial::operator[] ( const unsigned long index ) const
{
    if ( index > Degree() ) return 0.0;
    return coefs[index];
}
double CPolynomial::operator() ( double x ) const
{
    double res = 0.0;
    unsigned long deg = Degree();
    if ( !deg && coefs.size() ) return coefs[0];
    for ( unsigned long i = 0; i <= deg; i++ )
    {
        res = coefs[i] * pow( x, i ) + res;
    }
    return res;
}
bool CPolynomial::operator== ( const CPolynomial & second ) const
{
    const unsigned long mySize = Degree();
    const unsigned long secondSize = second.Degree();
    if ( mySize != secondSize )
        return false;
    
    for ( unsigned long i = 0; i <= mySize; i++ )
        if ( coefs[i] != second.coefs[i] ) return false;
    
    return true;
}
bool CPolynomial::operator!= ( const CPolynomial & second ) const
{
    const unsigned long mySize = Degree();
    const unsigned long secondSize = second.Degree();
    if ( mySize != secondSize )
        return true;
    
    for ( unsigned long i = 0; i <= mySize; i++ )
        if ( coefs[i] != second.coefs[i] ) return true;
    
    return false;
}
unsigned long CPolynomial::Degree() const
{
    if ( ! coefs.size() )
        return 0UL;
    for ( unsigned long i = coefs.size(); i > 0; i-- )
        if ( ! compareDoubles( coefs[i - 1], 0.0 ) )
            return i - 1;
    return 0UL;
}

ostream & operator<< ( ostream & os, const CPolynomial polynomial )
{
    unsigned long size = polynomial.Degree();
    if ( !polynomial.coefs.size() )
        return os << "0";
    os.setf ( std::ios::fixed, std:: ios::floatfield );
    for ( unsigned long i = size; i > 0; i-- )
    {
        if ( compareDoubles( polynomial[i], 0.0 ) ) continue;
        if ( i != size )
        {
            os << " ";
            if ( polynomial[i] > 0.0 ) os << "+ ";
        }
        if ( polynomial[i] < 0.0 ) os << "- ";
        if ( ! compareDoubles( abs(polynomial[i]), 1.0 ) )
        {
            if ( compareDoubles( abs(polynomial[i]), floor(abs(polynomial[i])) ) )
                os.precision(0);
            else
                os.precision(1);
            os << abs(polynomial[i]) << "*x^";
        }
        else
            os << "x^";
        os << i;
    }
    if ( ! compareDoubles( polynomial[0], 0.0 ) )
    {
        if ( compareDoubles( abs(polynomial[0]), floor(abs(polynomial[0])) ) )
            os.precision(0);
        else
            os.precision(1);
        if ( polynomial[0] < 0.0)
            os << " - " << abs(polynomial[0]);
        else
            os << " + " << abs(polynomial[0]);
    }
    return os;
}

CPolynomial CPolynomial::operator * ( const CPolynomial & second ) const
{
    unsigned long myDeg = Degree(), secDeg = second.Degree();
    //unsigned long maxDeg = myDeg > secDeg ? myDeg : secDeg;
    CPolynomial newOne;
    
    if ( !coefs.size() || !second.coefs.size() )
    {
        return CPolynomial();
    }
    
    for ( unsigned long i = 0; i <= myDeg; i++ )
    {
        for ( unsigned long j = 0; j <= secDeg; j++ )
        {
            unsigned long deg = i + j;
            newOne[deg] += coefs[i] * second.coefs[j];
        }
    }
    
    return newOne;
}

#ifndef __PROGTEST__
bool               smallDiff                               ( double            a,
                                                            double            b )
{
    double r = a > b ? a - b : b - a;
    if ( r < 10e-12 ) return true;
    return false;
}

bool               dumpMatch                               ( const CPolynomial & x,
                                                            const vector<double> & ref )
{
    unsigned long min = x.getCoefs().size() < ref.size() ?
    x.getCoefs().size() : ref.size();
    for ( unsigned long i = 0; i < min; i++ )
        if ( x.getCoefs()[i] != ref[i] ) return false;
    return true;
}


int main( void )
{
    CPolynomial a, b, c;
    ostringstream out;

    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;
    assert ( compareDoubles ( a ( 2 ), 5 ) );
    out . str ("");
    out << a;
    assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
    a = a * -2;
    assert ( a . Degree () == 3
            && dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );
    
    out . str ("");
    out << a;
    assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" );
    out . str ("");
    out << b;
    assert ( out . str () == "0" );
    b[5] = -1;
    out . str ("");
    out << b;
    assert ( out . str () == "- x^5" );
    c = a + b;
    assert ( c . Degree () == 5
            && dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );
    
    out . str ("");
    out << c;
    assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a - b;
    assert ( c . Degree () == 5
            && dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );
    
    out . str ("");
    out << c;
    assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
    c = a * b;
    assert ( c . Degree () == 8
            && dumpMatch ( c, vector<double>{ -0.0, -0.0, 0.0, -0.0, 0.0, -20.0, 7.0, -0.0, 2.0 } ) );
    
    out . str ("");
    out << c;
    assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
    assert ( a != b );
    b[5] = 0;
    assert ( !(a == b) );
    a = a * 0;
    assert ( a . Degree () == 0
            && dumpMatch ( a, vector<double>{ 0.0 } ) );
    
    assert ( a == b );
    return 0;
}
#endif /* __PROGTEST__ */
