#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stdint.h>
using namespace std;

const int ENDIAN_LITTLE   =  0x49494949;
const int ENDIAN_BIG      =  0x4d4d4d4d;

struct CRect
{
    CRect ( int x, int y, int w, int h )
    : m_X ( x ), m_Y ( y ), m_W ( w ), m_H ( h ) { }
    int   m_X;
    int   m_Y;
    int   m_W;
    int   m_H;
};
#endif /* __PROGTEST__ */

//----------------------------------------------------------------------//
//---------------------------Classes block------------------------------//
//----------------------------------------------------------------------//

class CImage {
    
    long          m_Endian;
    uint32_t       m_Components;
    uint32_t       m_BitsComp;
    uint32_t       m_Width, m_Height, m_Pad;
    char *        m_RawData;
    bool          m_Allocated;
    
    //----------------------------------------------------------------------//
    // Checks if an image can be cropped
    
    bool canBeCroped( const CRect & rc ) const
    {
        if ( (rc.m_X < 0 || rc.m_W <= 0 || (unsigned)(rc.m_X + rc.m_W) > m_Width)
            || (rc.m_Y < 0 || rc.m_H <= 0 || (unsigned)(rc.m_Y + rc.m_H) > m_Height))
            return false;
        return true;
    }
    
    //----------------------------------------------------------------------//
    // Checks if input file contains right paddings
    
    bool checkPadding( ifstream & fin ) const
    {
        for ( unsigned int j = 0; j < m_Height; j++ )
        {
            unsigned long rrr = 16 + (j + 1) * getLineWidth() / 8 - 1;
            fin.seekg( rrr, ios::beg );
            char k;
            fin.read( &k, 1 );
            k <<= ( 8 - m_Pad );
            if ( k != 0 ) return false;
        }
        return true;
    }
    
    //----------------------------------------------------------------------//
    // Convers headers byte order
    
    void convertToLittleBig( const int endian, char * sequence ) const
    {
        if ( endian == ENDIAN_BIG ) {
            char tmp = sequence[0];
            sequence[0] = sequence[3];
            sequence[3] = tmp;
            tmp = sequence[1];
            sequence[1] = sequence[2];
            sequence[2] = tmp;
        }
    }
    
    //----------------------------------------------------------------------//
    // Converts components byte order
    
    void convertToLittleBig( const CRect & rc ) const
    {
        unsigned long lengthOfSeq = m_BitsComp * m_Components * rc.m_W * rc.m_H / 8;
        for ( unsigned long i = 0; i < lengthOfSeq ; i += 2 )
        {
            char tmp = m_RawData[i];
            m_RawData[i] = m_RawData[i+1];
            m_RawData[i+1] = tmp;
        }
    }
    
    //----------------------------------------------------------------------//
    // Returns one line width in bits
    
    unsigned long getLineWidth() const
    {
        return m_Width * m_BitsComp * m_Components + m_Pad;
    }
    
    //----------------------------------------------------------------------//
    // Reads header from file, writes it and checks if raw data is correct
    
    void moveToInt( char * seq, uint32_t & num )
    {
        for ( int i = 0; i < 4; i++ )
        {
            ((char*) &num)[i] = seq[i];
        }
    }
    
    bool readHeaderAndCheckData( ifstream & fin )
    {
        uint32_t endian = 0;
        uint32_t bitsAndComps = 0;
        uint32_t width = 0, height = 0;
        
        char * littleBig = new char[4];
        
        // reading and checking image header
        
        fin.seekg( 0 );
        fin.read( (char *) &endian, 4 );
        
        fin.read( littleBig, 4 );
        convertToLittleBig( endian, littleBig );
        moveToInt( littleBig, width );
        
        fin.read( littleBig, 4 );
        convertToLittleBig( endian, littleBig );
        moveToInt( littleBig, height );
        
        fin.read( littleBig, 4 );
        convertToLittleBig( endian, littleBig );
        moveToInt( littleBig, bitsAndComps );
        
        delete [] littleBig;
        
        if ( ( endian != (unsigned)ENDIAN_BIG && endian != (unsigned)ENDIAN_LITTLE )
            || width <= 0 || height <= 0
            || ( bitsAndComps >> 3 ) == 0 || ( bitsAndComps >> 3 ) > 7
            || ( ( bitsAndComps & 7 ) != 0 && ( bitsAndComps & 7 ) != 2
                && ( bitsAndComps & 7 ) != 3 && ( bitsAndComps & 7 ) != 4 ) ) return false;
        
        // initializing image header
        m_Endian = endian;
        m_Components = bitsAndComps >> 3;
        m_BitsComp = bitsAndComps & 7;
        switch (m_BitsComp) {
            case 0: m_BitsComp = 1; break;
            case 2: m_BitsComp = 4; break;
            case 3: m_BitsComp = 8; break;
            case 4: m_BitsComp = 16; break;
        }
        m_Width = width;
        m_Height = height;
        recalculatePadding();
        
        fin.seekg( 0, ios::end );
        unsigned long fileSize = fin.tellg();
        unsigned long lengthOfData = getLineWidth() * m_Height / 8;
        
        if ( lengthOfData != fileSize - 16 )
            return false;
        
        if ( m_Pad && !checkPadding( fin ) )
            return false;
        
        return true;
    }
    
    //----------------------------------------------------------------------//
    // Recalculates number of zero padding bits
    
    void recalculatePadding()
    {
        m_Pad = (8 - (m_BitsComp * m_Components * m_Width % 8)) % 8;
    }
    
    //----------------------------------------------------------------------//
    // Reads necessary bytes and shifts them
    
    bool readLittleEndianRaw( ifstream & fin, const CRect & rc )
    {
        
        unsigned long firstBit = m_Components * m_BitsComp * rc.m_X;
        unsigned long lastBit  = m_Components * m_BitsComp * (rc.m_X + rc.m_W) - 1;
        
        unsigned long firstByte;
        unsigned long lastByte;
        
        if ( lastBit % 8 == 7 )
            lastByte = lastBit / 8;
        else
            lastByte = (lastBit + 1) / 8;
        
        if ( firstBit % 8 == 7 )
            firstByte = firstBit / 8;
        else
            firstByte = (firstBit + 1) / 8;
        
        
        firstBit %= 8;
        lastBit %= 8;
        
        unsigned char * sequence;
        
        try {
            sequence = new unsigned char[ lastByte - firstByte + 1 ];
        } catch ( bad_alloc ) {
            return false;
        }
        
        
        unsigned long k = 0;
        
        for ( int i = 0; i < rc.m_H; i++ )
        {
            unsigned long position = 16 + firstByte + getLineWidth() * (rc.m_Y + i) / 8;
            fin.seekg( position, ios::beg );

            fin.read( (char *)sequence, lastByte - firstByte + 1 );
            
            unsigned long j;
            for ( j = 0; j < lastByte - firstByte; j ++ )
            {
                m_RawData[ k++ ] = (sequence[ j ] << firstBit) | ( (sequence[ j + 1 ]) >> (8 - firstBit) );
            }
            
            if ( lastByte - firstByte == 0) j = 0;
                
            unsigned long offset = firstBit > lastBit ? firstBit - lastBit - 1 : 7 - lastBit + firstBit;
            offset %= 8;
            
            if ( (m_BitsComp * m_Components * rc.m_W + offset) / 8 == lastByte - firstByte ) {
                m_RawData[ k - 1 ] = ( m_RawData[ k - 1 ] ) & ( 0xFF << offset );
            } else {
                m_RawData[ k ] = ( sequence[ j ] << firstBit ) & ( 0xFF << offset );
                k ++;
            }
        }
        delete [] sequence;
        
        if ( fin.fail() ) return false;
        return true;
    }
    
    //----------------------------------------------------------------------//
    // Reads BigEndian bytes and converts them to LittleEndian
    
    bool readBigEndianRaw( ifstream & fin, const CRect & rc )
    {
        unsigned long firstBit = m_Components * m_BitsComp * rc.m_X;
        unsigned long lastBit  = m_Components * m_BitsComp * (rc.m_X + rc.m_W) - 1;
        
        unsigned long firstByte;
        unsigned long lastByte;
        
        if ( lastBit % 8 == 7 )
            lastByte = lastBit / 8;
        else
            lastByte = (lastBit + 1) / 8;
        
        if ( firstBit % 8 == 7 )
            firstByte = firstBit / 8;
        else
            firstByte = (firstBit + 1) / 8;
        
        if ( m_BitsComp != 16 ) {
            if ( readLittleEndianRaw( fin, rc ) )
                return true;
            return false;
        }
        
        unsigned long k = 0;
        for ( int i = 0; i < rc.m_H; i++ )
        {
            fin.seekg( 16 + firstByte + getLineWidth() * (rc.m_Y + i) / 8, ios::beg );
            fin.read( m_RawData + k, lastByte - firstByte + 1 );
            k += lastByte - firstByte + 1;
        }
        
        if ( fin.fail() )
            return false;
        convertToLittleBig( rc );
        return true;
    }
    
    //----------------------------------------------------------------------//
    // Writes header to file
    
    void writeHeader( ofstream & fout )
    {
        if ( m_Endian == ENDIAN_LITTLE )
        {
            fout.write( (char *) &m_Endian, 4 );
            fout.write( (char *) &m_Width, 4 );
            fout.write( (char *) &m_Height, 4 );
            
            unsigned long sth = m_Components * 8;
            
            switch (m_BitsComp) {
                case 1: sth |= 0; break;
                case 4: sth |= 2; break;
                case 8: sth |= 3; break;
                case 16: sth |= 4; break;
            }
            
            fout.write( (char *) &sth, 4 );
            
        } else {
            
            fout.write( (char *) &m_Endian + 3, 1 );
            fout.write( (char *) &m_Endian + 2, 1 );
            fout.write( (char *) &m_Endian + 1, 1 );
            fout.write( (char *) &m_Endian + 0, 1 );
            fout.write( (char *) &m_Width + 3, 1 );
            fout.write( (char *) &m_Width + 2, 1 );
            fout.write( (char *) &m_Width + 1, 1 );
            fout.write( (char *) &m_Width + 0, 1 );
            fout.write( (char *) &m_Height + 3, 1 );
            fout.write( (char *) &m_Height + 2, 1 );
            fout.write( (char *) &m_Height + 1, 1 );
            fout.write( (char *) &m_Height + 0, 1 );
            
            unsigned long sth = m_Components * 8;
            
            switch (m_BitsComp) {
                case 1: sth |= 0; break;
                case 4: sth |= 2; break;
                case 8: sth |= 3; break;
                case 16: sth |= 4; break;
            }
            fout.write( (char *) &sth + 3, 1 );
            fout.write( (char *) &sth + 2, 1 );
            fout.write( (char *) &sth + 1, 1 );
            fout.write( (char *) &sth + 0, 1 );
        }
    }
    
    //----------------------------------------------------------------------//
    // Writes the raw data
    bool writeRaw( ofstream & fout, const CRect & rc )
    {
        if ( m_Endian == ENDIAN_BIG && m_BitsComp == 16 )
            convertToLittleBig( rc );
        
        fout.write( m_RawData, getLineWidth() * m_Height / 8 );
        
        if ( fout.fail() )
            return false;
        
        return true;
    }
    
    //----------------------------------------------------------------------//
    
public:
    
    CImage( const int ENDIAN = ENDIAN_LITTLE,
           const uint32_t COMPONENTS = 1,
           const uint32_t BITS_PER_COMPONENT = 1,
           const uint32_t WIDTH = 1,
           const uint32_t HEIGHT = 1 ) : m_Endian( ENDIAN ),
    m_Components( COMPONENTS ),
    m_BitsComp( BITS_PER_COMPONENT ),
    m_Width( WIDTH ),
    m_Height( HEIGHT )
    {
        m_Allocated = false;
        m_RawData = NULL;
        recalculatePadding();
    }
    
    //----------------------------------------------------------------------//
    
    ~CImage() { if ( m_Allocated ) { delete [] m_RawData; } }
    
    //----------------------------------------------------------------------//
    
    void read( const char * src, const CRect & rc ) {
        
        ifstream fin( src, ios::binary | ios::in );
        
        if ( fin.fail() || !readHeaderAndCheckData( fin ) || !canBeCroped( rc ) ) // error
        {
            fin.clear();
            fin.close();
            throw 1;
        }
        
        if ( fin.eof() ) fin.clear();
        
        bool success;
        
        try {
            if ( !m_Allocated )
            {
                unsigned long padding = (8 - (m_BitsComp * m_Components * rc.m_W % 8)) % 8;
                m_RawData = new char[ (m_BitsComp * m_Components * rc.m_W + padding) * rc.m_H / 8 + 1];
                m_Allocated = true;
            }
        } catch ( bad_alloc ) {
            fin.close();
            throw 1;
        }
        
        // reading bytes
        switch ( m_Endian ) {
            case ENDIAN_LITTLE:
                success = readLittleEndianRaw( fin, rc );
                break;
            case ENDIAN_BIG:
                success = readBigEndianRaw( fin, rc );
                break;
            default:
                throw 1;
                break;
        }
        
        if ( !success )
        {
            fin.clear();
            fin.close();
            throw 1;
        }
        
        m_Width = rc.m_W;
        m_Height = rc.m_H;
        
        recalculatePadding();
        
        fin.close();
    }
    
    //----------------------------------------------------------------------//
    
    void printRawData( )
    {
        unsigned long lengthOfData = (m_Width * m_BitsComp * m_Components + m_Pad) * m_Height / 8;
        for ( unsigned long i = 0; i < lengthOfData; i ++ )
        {
            cout << m_RawData[i];
        }
        cout << endl;
    }
    
    //----------------------------------------------------------------------//
    
    void write( const char * dest, const int endian, const CRect & rc )
    {
        m_Endian = endian;
        
        ofstream fout( dest, ios::binary );
        
        writeHeader( fout );
        
        if ( fout.fail() )
        {
            fout.clear();
            fout.close();
            throw 1;
        }
        
        if ( !writeRaw( fout, rc ) )
        {
            fout.clear();
            fout.close();
            throw 1;
        }
        
        fout.close();
    }
};

//----------------------------------------------------------------------//
//--------------------------Functions block-----------------------------//
//----------------------------------------------------------------------//

bool cropImage ( const char  * srcFileName,
                const char  * dstFileName,
                const CRect & rc,
                int           byteOrder )
{
    CImage srcImg;
    try {
        srcImg.read( srcFileName, rc );
        srcImg.write( dstFileName, byteOrder, rc );
        
    } catch (int err) {
        return false;
    }
    
    return true;
}

//----------------------------------------------------------------------//

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                     const char * fileName2 )
{
    ifstream firstFile ( fileName1, ios::in );
    ifstream secondFile ( fileName2, ios::in );
    
    char a, b;
    
    firstFile.seekg( 0, ios::end );
    secondFile.seekg( 0, ios::end );
    unsigned long size1 = firstFile.tellg(), size2 = secondFile.tellg();
    
    if ( size2 != size1 )
    {
        firstFile.close();
        secondFile.close();
        return false;
    }
    
    firstFile.seekg( 0, ios::beg );
    secondFile.seekg( 0, ios::beg );
    
    for ( unsigned int i = 0; i < size1; i ++ )
    {
        firstFile.read( &a, 1 );
        secondFile.read( &b, 1 );
        if ( a != b )
        {
            firstFile.close();
            secondFile.close();
            return false;
        }
    }
    
    firstFile.close();
    secondFile.close();
    return true;
}

//----------------------------------------------------------------------//

int main ( void )
{
//    ifstream file1( "bigBigFile.raw", ios::in );
//    char *fff = new char[ 16 ];
//    file1.read( fff, 16 );
//    fff[15] = '\x0c';
//    
//    file1.seekg( 0, ios::end );
//    unsigned long size = file1.tellg();
//    size -= 16;
//    ofstream file2( "bigBigFile.raw1", ios::out );
//    
//    char *seq = new char[2000000];
//    file2.write( fff, 16 );
//    file1.seekg( 16 );
//    file1.read(seq, 2000000);
//    file2.write(seq, 2000000);
//    file1.close();
//    file2.close();
//    return 0;
    
    assert (  cropImage ( "input_00.raw", "output_00.raw", CRect ( 1, 2, 2, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_00.raw", "ref_00.raw" ) );
    
    assert (  cropImage ( "input_01.raw", "output_01.raw", CRect ( 1, 2, 2, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_01.raw", "ref_01.raw" ) );
    
    assert (  cropImage ( "input_02.raw", "output_02.raw", CRect ( 1, 2, 2, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_02.raw", "ref_02.raw" ) );
    
    assert (  cropImage ( "input_03.raw", "output_03.raw", CRect ( 0, 1, 3, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_03.raw", "ref_03.raw" ) );
    
    assert (  cropImage ( "input_04.raw", "output_04.raw", CRect ( 0, 1, 3, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_04.raw", "ref_04.raw" ) );
    
    assert (  cropImage ( "input_05.raw", "output_05.raw", CRect ( 1, 1, 4, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_05.raw", "ref_05.raw" ) );
    
    assert (  cropImage ( "input_06.raw", "output_06.raw", CRect ( 2, 2, 14, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_06.raw", "ref_06.raw" ) );
    
    assert (  cropImage ( "input_07.raw", "output_07.raw", CRect ( 2, 2, 8, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_07.raw", "ref_07.raw" ) );
    
    assert (  cropImage ( "input_08.raw", "output_08.raw", CRect ( 2, 2, 7, 3 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_08.raw", "ref_08.raw" ) );
    
    assert (  cropImage ( "input_09.raw", "output_09.raw", CRect ( 2, 2, 4, 4 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_09.raw", "ref_09.raw" ) );
    
    assert ( ! cropImage ( "input_10.raw", "output_10.raw", CRect ( 2, 2, 10, 3 ), ENDIAN_LITTLE ) );
    
    assert ( ! cropImage ( "input_11.raw", "output_11.raw", CRect ( 2, 11, 6, 3 ), ENDIAN_LITTLE ) );
    
    assert (  cropImage ( "input_12.raw", "output_12.raw", CRect ( 0, 0, 1, 1 ), ENDIAN_LITTLE )
            && identicalFiles ( "output_12.raw", "ref_12.raw" ) );
    
    assert( cropImage ( "input_05.raw", "outBIG_05.raw", CRect ( 1, 1, 4, 3 ), ENDIAN_BIG ) );
    assert( cropImage( "bigBigFile.raw", "tryOut.raw", CRect( 0, 0, 1, 1 ), ENDIAN_LITTLE ) );
    
    for ( int i = 0; i < 1000; i ++ )
    {
        for ( int j = 0; j < 1000; j ++ )
        {
            for ( int k = 0; k < 1000 - i; k ++ )
            {
                for ( int m = 0; m < 1000 - j; m ++ )
                {
                    cropImage( "/Users/mannannlegur/Library/Developer/Xcode/DerivedData/du1.1-gusqysazgsmsqcbgqprhamrvzenx/Build/Products/Debug/bigBIGFile.raw", "/Users/mannannlegur/Library/Developer/Xcode/DerivedData/du1.1-gusqysazgsmsqcbgqprhamrvzenx/Build/Products/Debug/tryOut.raw", CRect( i, j, k, m ), ENDIAN_BIG );
                }
            }
        }
    }
    
    return 0;
}
#endif /* __PROGTEST__ */

