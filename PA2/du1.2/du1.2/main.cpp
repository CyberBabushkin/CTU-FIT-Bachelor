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
#include <map>
#include <stdint.h>
using namespace std;

struct CSymbol {
    vector<char> name;
    vector<char> data;
};

vector<CSymbol> symbols1;
vector<CSymbol> symbols2;

#endif /* __PROGTEST__ */

struct CFile {
    uint32_t cnt;
    uint64_t headerSize;
    uint64_t dataSize;
    ifstream fileStream;
    
    CFile( const char * source ) :
        cnt( 0 ),
        headerSize( 0 ),
        dataSize( 0 ),
        fileStream( source, ios::in | ios::binary ) {}
};

set < string > hashTable;

//--------------------------------------------------------------------------//

bool badFile( ifstream & file1, ifstream & file2, ofstream & file3 )
{
    if ( file1.fail() || file2.fail() || file3.fail() )
    {
        file1.close();
        file2.close();
        file3.close();
        return true;
    }
    return false;
}
bool badFile( ifstream & file1, ofstream & file3 )
{
    if ( file1.fail() || file3.fail() )
    {
        file1.close();
        file3.close();
        return true;
    }
    return false;
}

//--------------------------------------------------------------------------//

bool dataHasCorrectSize( CFile & file )
{
    uint64_t position = file.fileStream.tellg();
    file.fileStream.seekg( 0, ios::end );
    uint64_t size = file.fileStream.tellg();
    size -= file.headerSize;
    size -= 4;
    file.fileStream.seekg( position );
    
    if ( size != file.dataSize )
        return false;
    return true;
}

//--------------------------------------------------------------------------//

bool moveData( CFile & file, ofstream & fout )
{
    char *data = NULL;
    uint64_t dataSize = file.dataSize;
    
    uint64_t blocks = dataSize / 6000;
    uint64_t left = dataSize % 6000;
    
    if ( blocks )
    {
        data = new char[6000];
        
        for ( uint64_t i = 0; i < blocks; i++ )
        {
            file.fileStream.read( data, 6000 );
            fout.write( data, 6000 );
        }
        
        delete [] data;
    }
    
    data = new char[left];
    
    file.fileStream.read( data, left );
    fout.write( data, left );
    delete [] data;
    
    if ( fout.fail() || file.fileStream.fail() )
        return false;
    return true;
}

//--------------------------------------------------------------------------//

bool readSymbols( CFile & file, ofstream & fout )
{
    // symbol name
    vector<char> name;
    
    for ( uint32_t i = 0; i < file.cnt; i++ )
    {
        // reading a symbol header
        uint32_t nameLen, dataLen, offset;
        file.fileStream.read( (char*)&nameLen, 4 );
        file.fileStream.read( (char*)&dataLen, 4 );
        file.fileStream.read( (char*)&offset, 4 );
        
        // Data size written in header
        file.dataSize += dataLen;
        
        // errrrrrrrrrooooooooooor
        if ( badFile(file.fileStream, fout)
            || !nameLen || !dataLen || !offset ) return false;
        
        // reading a symbol name
        name.resize( nameLen );
        file.fileStream.read( &name[0], nameLen );
        string str( name.begin(), name.end() );
        
        // WTF, Motherfucker?! Are you fuckin' trying to insert an element that already exists?!
        // ARE YOU FUCKING MAD? SUCK YOUR DADDYS' DICK, YOU STUPID BASTARD!!!
        // Error: element already exists.
        bool success = hashTable.insert( /*hashFunction( name )*/ str ).second;
        if ( !success )
        {
            file.fileStream.close();
            fout.close();
            return false;
        };
        
        fout.write( (char*)&nameLen, 4 );
        fout.write( (char*)&dataLen, 4 );
        fout.write( (char*)&offset, 4 );
        fout.write( &name[0], nameLen );
        if ( badFile(file.fileStream, fout) ) return false;
        
    }
    file.headerSize = file.fileStream.tellg();
    file.headerSize -= 4;
    
    return true;
}

//--------------------------------------------------------------------------//

bool setCorrectOffsets( CFile & file1, CFile & file2, fstream & fout )
{
    uint64_t offset = 4;
    
    uint32_t nameLen, dataOffset, dataLen;
    
    for ( uint64_t i = 0; i < file1.cnt; i++ )
    {
        fout.seekg( offset );
        fout.read( (char*)&nameLen, 4 );
        fout.read( (char*)&dataLen, 4 );
        fout.read( (char*)&dataOffset, 4 );
        
        if ( dataOffset < file1.headerSize + 4
            || dataOffset > file1.dataSize + file1.headerSize + 4
            || dataOffset + dataLen > file1.dataSize + file1.headerSize + 4 )
            return false;
        
        dataOffset += file2.headerSize;
        
        fout.seekg( offset + 8 );
        fout.write( (char*)&dataOffset, 4 );
        
        offset += 12 + nameLen;
    }
    
    for ( uint64_t i = 0; i < file2.cnt; i++ )
    {
        fout.seekg( offset );
        fout.read( (char*)&nameLen, 4 );
        fout.read( (char*)&dataLen, 4 );
        fout.read( (char*)&dataOffset, 4 );
        
        if ( dataOffset < file2.headerSize + 4
            || dataOffset > file2.dataSize + file2.headerSize + 4
            || dataOffset + dataLen > file2.dataSize + file2.headerSize + 4 )
            return false;
        
        dataOffset += file1.headerSize + file1.dataSize;
        
        if ( dataOffset < file1.headerSize + file2.headerSize + 4 )
            return false;
        
        fout.seekg( offset + 8 );
        fout.write( (char*)&dataOffset, 4 );
        
        offset += 12 + nameLen;
    }
    
    if ( fout.fail() )
        return false;
    return true;
}

//--------------------------------------------------------------------------//

bool linkFiles ( const char  * srcFile1,
                const char  * srcFile2,
                const char  * dstFile )
{
    hashTable.clear();
    CFile file1( srcFile1 ), file2( srcFile2 );
    
    ofstream fout( dstFile, ios::out | ios::binary );
    
    // reading a number of symbols
    file1.fileStream.read( (char*)&file1.cnt, 4 );
    file2.fileStream.read( (char*)&file2.cnt, 4 );
    
    // writing a number of symbols
    uint32_t cntOut = file1.cnt + file2.cnt;
    fout.write( (char*)&cntOut, 4 );
    
    // error
    if ( badFile(file1.fileStream, file2.fileStream, fout) ) return false;
    
    // reading file symbols
    if ( ! readSymbols(file1, fout) ) { file2.fileStream.close(); return false; }
    if ( ! readSymbols(file2, fout) ) { file1.fileStream.close(); return false; }
    
    // check data size and move it to the outFile
    if ( ! dataHasCorrectSize( file1 )
        || ! dataHasCorrectSize( file2 )
        || ! moveData( file1, fout )
        || ! moveData( file2, fout ) )
    {
        file1.fileStream.close();
        file2.fileStream.close();
        fout.close();
        return false;
    }
    
    // closing files
    file1.fileStream.close();
    file2.fileStream.close();
    fout.close();
    
    // opening out file to rewrite its offsets
    fstream fileOut( dstFile, ios::binary | ios::in | ios::out );
    
    // now let's set right offsets
    if ( ! setCorrectOffsets( file1, file2, fileOut ) )
    {
        fileOut.close();
        return false;
    }
    
    fileOut.close();
    return true;
}

//--------------------------------------------------------------------------//

#ifndef __PROGTEST__
bool identicalContents ( const char * fileName1,
                        const char * fileName2 )
{
    ifstream firstFile ( fileName1, ios::in );
    ifstream secondFile ( fileName2, ios::in );
    
    uint32_t cnt1, cnt2;
    
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
    
    firstFile.read( (char*)&cnt1, 4 );
    secondFile.read( (char*)&cnt2, 4 );
    
    if ( cnt1 != cnt2 )
    {
        firstFile.close();
        secondFile.close();
        return false;
    }
    
    CSymbol sym;
    
    for ( uint32_t i = 0; i < cnt1; i++ )
    {
        // reading a symbol header
        uint32_t nameLen, dataLen, offset;
        firstFile.read( (char*)&nameLen, 4 );
        firstFile.read( (char*)&dataLen, 4 );
        firstFile.read( (char*)&offset, 4 );
        
        // reading a symbol name
        sym.name.resize( nameLen );
        sym.data.resize( dataLen );
        firstFile.read( &sym.name[0], nameLen );
        
        uint64_t position = firstFile.tellg();
        
        firstFile.seekg( offset );
        firstFile.read( &sym.data[0], dataLen );
        
        firstFile.seekg( position );
        
        symbols1.push_back( sym );
    }
    
    for ( uint32_t i = 0; i < cnt2; i++ )
    {
        // reading a symbol header
        uint32_t nameLen, dataLen, offset;
        secondFile.read( (char*)&nameLen, 4 );
        secondFile.read( (char*)&dataLen, 4 );
        secondFile.read( (char*)&offset, 4 );
        
        // reading a symbol name
        sym.name.resize( nameLen );
        sym.data.resize( dataLen );
        secondFile.read( &sym.name[0], nameLen );
        
        uint64_t position = secondFile.tellg();
        
        secondFile.seekg( offset );
        secondFile.read( &sym.data[0], dataLen );
        
        secondFile.seekg( position );
        
        symbols2.push_back( sym );
    }
    
    uint64_t count = 0;
    bool success = true;
    
    for ( uint64_t i = 0; i < symbols1.size(); i++ )
    {
        for ( uint64_t j = 0; j < symbols2.size(); j++ )
        {
            if ( symbols1[i].name == symbols2[j].name )
            {
                if ( symbols2[j].data != symbols1[i].data )
                {
                    cout << "Wrond data for " << i << " symbol." << endl;
                    success = false;
                }
                count++;
            }
        }
    }
    
    if ( count != symbols1.size() ) {
        success = false;
        cout << "Something with names happedned..." << endl;
    }
    
    firstFile.close();
    secondFile.close();
    return success;
}

void someFunc()
{
    vector<char> name, data;

    CFile file( "in_1769613.bin" );

    file.fileStream.seekg( 0, ios::end );
    uint64_t size = file.fileStream.tellg();

    file.fileStream.seekg( 0 );

    file.fileStream.read( (char*)&file.cnt, 4 );

    for ( uint32_t i = 0; i < file.cnt; i++ )
    {
        // reading a symbol header
        uint32_t nameLen, dataLen, offset;
        file.fileStream.read( (char*)&nameLen, 4 );
        file.fileStream.read( (char*)&dataLen, 4 );
        file.fileStream.read( (char*)&offset, 4 );

        // Data size written in header
        file.dataSize += dataLen;
        file.headerSize += 12 + nameLen;

        // reading a symbol name
        name.resize( nameLen );
        file.fileStream.read( &name[0], nameLen );

        data.resize( dataLen );
        uint64_t posPrev = file.fileStream.tellg();
        file.fileStream.seekg( offset );
        file.fileStream.read( &data[0], dataLen );
        if ( file.fileStream.eof() )
        {

            cout << "Hm... " << i << endl;
        }

        file.fileStream.seekg( posPrev );

    }
    cout << size << endl;
    cout << file.headerSize + 4 << "   " << file.dataSize << endl;

}

int main ( void )
{
    assert ( linkFiles ( "in1_00.obj", "in2_00.obj", "out_00.obj" )
            && identicalContents ( "out_00.obj", "ref_00.obj" ) );
    
    assert ( linkFiles ( "in1_01.obj", "in2_01.obj", "out_01.obj" )
            && identicalContents ( "out_01.obj", "ref_01.obj" ) );
    
    assert ( !linkFiles ( "in1_02.obj", "in2_02.obj", "out_02.obj" ) );
    
    assert( linkFiles ( "in_1770171.bin", "in1_01.obj", "out_100.obj" ) );
    
    return 0;
}
#endif /* __PROGTEST__ */
