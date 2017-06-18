#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <stdint.h>
using namespace std;
#endif              /* __PROGTEST__ */

class CVersion;
class CFile;
class CData;
struct CLinker;

template <typename CClass>
class CArray
{
public:
    CArray( uint32_t len );
    CArray( const CArray<CClass> & );
    ~CArray();
    
    void addElement( const CClass elem );
    void removeLast();
    CClass operator[] ( uint32_t index ) const;
    CClass & operator[] ( uint32_t index );
    CArray<CClass> & operator= ( const CArray<CClass> & second );
    uint32_t size() const;
    
private:
    CClass    *m_Array;
    uint32_t  m_Len;
    uint32_t  m_NumberOfElements;
};

template <typename A, typename B>
class CTuple
{
private:
    A m_First;
    B m_Second;
    
public:
    CTuple( const A &, const B & );
    A a() const;
    B b() const;
};

class CFile
{
public:
    CFile                 ( void );
    CFile                 ( const CFile & );
    bool      Seek        ( uint32_t offset );
    uint32_t  Read        ( uint8_t * dst,
                           uint32_t bytes );
    uint32_t  Write       ( const uint8_t * src,
                           uint32_t bytes );
    void      Truncate    ( void );
    uint32_t  FileSize    ( void ) const;
    void      AddVersion  ( void );
    bool      UndoVersion ( void );
    
private:
    
    CArray<CVersion> m_Versions;
};

class CVersion
{
public:
    CVersion();
    CVersion( const CVersion & );
    ~CVersion();
    CVersion & operator= ( const CVersion & );
    
    uint32_t writeData( const uint8_t *, uint32_t, uint32_t );
    uint32_t readData( uint8_t *, uint32_t, uint32_t ) const;
    uint32_t size() const;
    void truncate( uint32_t );
    
    uint32_t   m_Position;
    
private:
    uint32_t   m_VersionSize;
    CLinker  * m_Blocks;
    
    void recalculateSize();
    CTuple< CLinker *, uint32_t > getDataPointer( uint32_t pos ) const;
};

struct CLinker
{
    CData        *  m_Data;
    uint32_t        m_StartPosition; // in CData
    uint32_t        m_BlockSize;
    
    CLinker    *    m_NextBlock;
    CLinker    *    m_PrevBlock;
    
    CLinker( const uint8_t *, uint32_t );
    CLinker( const CLinker & );
    ~CLinker();
    CLinker & operator= ( const CLinker & );
    
    void resize( uint32_t, uint32_t );
    uint8_t * getBytes( uint32_t ) const;
};

class CData
{
private:
    uint32_t  m_HardLinks;
    uint8_t * m_Data;
    uint32_t  m_DataLen;
    
    uint32_t  m_Index; // for adding some data
    
public:
    CData( const uint8_t *, uint32_t );
    ~CData();
    
    CTuple<uint32_t, uint32_t> getStartLen( uint32_t, uint32_t ) const;
    void addObserver();
    void removeObserver();
    uint8_t * dataPtr( uint32_t ) const;
};

//#pragma mark CArray

template <typename CClass>
CArray<CClass>::CArray( uint32_t len )
{
    if ( ! len ) len = 4;
    
    m_Array = new CClass[len];
    m_Len = len;
    m_NumberOfElements = 0;
}

template <typename CClass>
CArray<CClass>::CArray( const CArray<CClass> & second ) : m_Array( nullptr )
{
    if ( m_Array ) delete [] m_Array;
    
    m_NumberOfElements = second.m_NumberOfElements;
    m_Len = second.m_Len;
    m_Array = new CClass[ m_Len ];
    
    for ( uint32_t i = 0; i < m_NumberOfElements; i++ )
        m_Array[i] = second.m_Array[i];
}

template <typename CClass>
CArray<CClass>::~CArray()
{
    delete [] m_Array;
}

template <typename CClass>
void CArray<CClass>::addElement( CClass elem )
{
    if ( m_NumberOfElements + 1 > m_Len )
    {
        uint32_t newLen = m_Len * 2;
        CClass *newArr = new CClass[newLen];
        
        for ( uint32_t i = 0; i < m_NumberOfElements; i++ )
            newArr[i] = m_Array[i];
        
        delete [] m_Array;
        m_Array = newArr;
        m_Len = newLen;
    }
    
    m_Array[ m_NumberOfElements++ ] = elem;
}

template <typename CClass>
void CArray<CClass>::removeLast()
{
    if ( ! m_NumberOfElements ) return;
    m_Array[ --m_NumberOfElements ] = CClass();
}

template <typename CClass>
CClass CArray<CClass>::operator[] ( uint32_t index ) const
{
    if ( index + 1 > m_NumberOfElements )
        throw "out of range";
    
    return m_Array[index];
}

template <typename CClass>
CClass & CArray<CClass>::operator[] ( uint32_t index )
{
    if ( index + 1 > m_NumberOfElements )
        throw "out of range";
    
    return m_Array[index];
}

template <typename CClass>
CArray<CClass> & CArray<CClass>::operator= ( const CArray<CClass> & second )
{
    if ( &second == this ) return *this;
    
    delete [] m_Array;
    m_NumberOfElements = second.m_NumberOfElements;
    m_Len = second.m_Len;
    m_Array = new CClass[m_Len];
    
    for ( uint32_t i = 0; i < m_NumberOfElements; i++ )
        m_Array[i] = second.m_Array[i];
    
    return *this;
}

template <typename CClass>
uint32_t CArray<CClass>::size() const
{
    return m_NumberOfElements;
}

//#pragma mark CTuple

template <typename A, typename B>
CTuple<A, B>::CTuple( const A & a, const B & b ) : m_First( a ), m_Second( b ) {}

template <typename A, typename B>
A CTuple<A, B>::a() const
{
    return m_First;
}

template <typename A, typename B>
B CTuple<A, B>::b() const
{
    return m_Second;
}

//#pragma mark CFile

CFile::CFile( void ) : m_Versions( CArray<CVersion>(4) ) {}

CFile::CFile( const CFile & second ) : m_Versions( second.m_Versions ) {}

bool      CFile::Seek( uint32_t offset )
{
    if ( ! m_Versions.size() ) return false;
    
    if ( m_Versions[ m_Versions.size() - 1 ].size() < offset ) return false;
    
    m_Versions[ m_Versions.size() - 1 ].m_Position = offset;
    return true;
}

uint32_t  CFile::Read( uint8_t * dst,
                      uint32_t bytes )
{
    if ( ! m_Versions.size() ) return 0;
    
    uint32_t position = m_Versions[ m_Versions.size() - 1 ].m_Position;
    uint32_t readBytes = m_Versions[ m_Versions.size() - 1 ].readData( dst, bytes, position );
    m_Versions[ m_Versions.size() - 1 ].m_Position += readBytes;
    return readBytes;
}

uint32_t  CFile::Write       ( const uint8_t * src,
                              uint32_t bytes )
{
    if ( ! m_Versions.size() ) m_Versions.addElement( CVersion() );
    
    uint32_t position = m_Versions[ m_Versions.size() - 1 ].m_Position;
    
    uint32_t readBytes = m_Versions[ m_Versions.size() - 1 ].writeData( src, bytes, position );
    m_Versions[ m_Versions.size() - 1 ].m_Position += readBytes;
    return readBytes;
}

void      CFile::Truncate    ( void )
{
    if ( ! m_Versions.size() ) return;
    
    uint32_t position = m_Versions[ m_Versions.size() - 1 ].m_Position;
    m_Versions[ m_Versions.size() - 1 ].truncate( position );
}

uint32_t  CFile::FileSize    ( void ) const
{
    if ( ! m_Versions.size() ) return 0;
    
    return m_Versions[ m_Versions.size() - 1 ].size();
}

void      CFile::AddVersion  ( void )
{
    if ( ! m_Versions.size() )
    {
        m_Versions.addElement( CVersion() );
        return;
    }
    
    m_Versions.addElement( m_Versions[ m_Versions.size() - 1 ] );
}

bool      CFile::UndoVersion ( void )
{
    if ( m_Versions.size() == 0 || m_Versions.size() == 1 )
        return false;
    
    m_Versions.removeLast();
    return true;
}

//#pragma mark CVersion

CVersion::CVersion() : m_Position( 0 ), m_VersionSize( 0 ), m_Blocks( nullptr ) {}

CVersion::CVersion( const CVersion & second )
{
    CLinker * block = second.m_Blocks;
    m_VersionSize = second.m_VersionSize;
    m_Position = second.m_Position;
    
    if ( block )
        m_Blocks = new CLinker( *block );
    else
    {
        m_Blocks = nullptr;
        return;
    }
    
    block = block -> m_NextBlock;
    CLinker * curBlock = m_Blocks;
    
    while ( block )
    {
        curBlock -> m_NextBlock = new CLinker( *block );
        block = block -> m_NextBlock;
        curBlock = curBlock -> m_NextBlock;
    }
}

CVersion & CVersion::operator= ( const CVersion & second )
{
    CLinker * block = second.m_Blocks;
    m_VersionSize = second.m_VersionSize;
    m_Position = second.m_Position;
    
    if ( block )
        m_Blocks = new CLinker( *block );
    else
    {
        m_Blocks = nullptr;
        return *this;
    }
    
    block = block -> m_NextBlock;
    CLinker * curBlock = m_Blocks;
    
    while ( block )
    {
        curBlock -> m_NextBlock = new CLinker( *block );
        curBlock -> m_NextBlock -> m_PrevBlock = curBlock;
        block = block -> m_NextBlock;
        curBlock = curBlock -> m_NextBlock;
    }
    
    return *this;
}

CVersion::~CVersion()
{
    CLinker * block = m_Blocks;
    
    while ( block )
    {
        CLinker * tmp = block;
        block = block->m_NextBlock;
        delete tmp;
    }
}

uint32_t CVersion::writeData( const uint8_t * data, uint32_t len, uint32_t pos )
{
    uint32_t positionBegin = pos;
    CLinker * newBlock = new CLinker( data, len );
    CLinker * afterBlock = nullptr; // pointer to a block after the new one
    
    if ( ! len ) return 0;
    
    // Empty version
    if ( m_VersionSize == 0 )
    {
        m_Blocks = newBlock;
        m_VersionSize = newBlock->m_BlockSize;
        return len;
    }
    
    CLinker * block = m_Blocks;
    
    // Adding to the end of a version
    if ( m_VersionSize == pos )
    {
        while ( block -> m_NextBlock )
            block = block -> m_NextBlock;
                                                    // V
        block -> m_NextBlock = newBlock;
        newBlock -> m_PrevBlock = block;
        m_VersionSize += newBlock -> m_BlockSize;
        return len;
    }
    
    // Skipping blocks and searching for the start position
    block = m_Blocks;
    uint32_t blockLen = block->m_BlockSize;
    
    while ( positionBegin >= blockLen )
    {
        positionBegin -= blockLen;
        block = block -> m_NextBlock;               // V
        blockLen = block -> m_BlockSize;
    }
    
    CLinker * blockBegin = block;
    
    uint32_t positionEnd = len + positionBegin;
    
    blockLen = block -> m_BlockSize;
    
    while ( positionEnd >= blockLen )
    {
        positionEnd -= blockLen;
        
        block = block -> m_NextBlock;
        
        if ( ! block ) break;
        
        blockLen = block -> m_BlockSize;
    }
    
    CLinker * blockEnd = block;
    
    // Moving if we're on the beginning
    if ( blockBegin && ! positionBegin )
    {
        blockBegin = blockBegin -> m_PrevBlock;
    }
    else if ( blockBegin && blockBegin != blockEnd ) // or cutting it
    {
        blockBegin -> resize( blockBegin -> m_StartPosition, positionBegin );
    }
    
    if ( ! blockEnd ) // we can delete the whole file from the start position
    {
        block = blockBegin -> m_NextBlock;
        
        while ( block )
        {
            CLinker * toDelete = block;
            block = block -> m_NextBlock;
            delete toDelete;
        }
        
        afterBlock = nullptr;
    }
    else
    {
        if ( blockEnd == blockBegin ) // split one block
        {
            CLinker * blockLeft = new CLinker( *blockBegin );
            blockLeft -> resize( blockLeft -> m_StartPosition, positionBegin );
            CLinker * blockRight = new CLinker( *blockBegin );
            blockRight -> resize( positionBegin + len,
                                  blockRight->m_BlockSize - positionBegin - len );
            block = blockBegin -> m_PrevBlock;
            
            blockLeft -> m_NextBlock = newBlock;
            newBlock -> m_PrevBlock = blockLeft;
            newBlock -> m_NextBlock = blockRight;
            blockRight -> m_PrevBlock = newBlock;
            blockRight -> m_NextBlock = blockBegin -> m_NextBlock;
            
            if ( block )
            {
                block -> m_NextBlock = blockLeft;
                blockLeft -> m_PrevBlock = block;
            } else {
                blockLeft -> m_PrevBlock = nullptr;
                m_Blocks = blockLeft;
            }
            
            delete blockBegin;
            return len;
        }
        if ( ! blockBegin )
            block = m_Blocks;
        else
            block = blockBegin -> m_NextBlock;
        
        while ( block != blockEnd )
        {
            CLinker * toDelete = block;
            
            block = block -> m_NextBlock;
            delete toDelete;
        }
        
        blockEnd->resize( blockEnd -> m_StartPosition + positionEnd,
                          blockEnd->m_BlockSize - positionEnd );
        afterBlock = blockEnd;
    }
    
    newBlock -> m_NextBlock = afterBlock;
    
    if ( ! blockBegin )
        m_Blocks = newBlock;
    else
    {
        blockBegin -> m_NextBlock = newBlock;
        newBlock -> m_PrevBlock = blockBegin;
    }
    
    recalculateSize();
    return len;
}

uint32_t CVersion::readData( uint8_t * data, uint32_t len, uint32_t pos ) const
{
    if ( ! len ) return 0;
    
    uint32_t bytesRead = 0;
    //uint32_t positionInFile = 0;
    CTuple< CLinker *, uint32_t > beginPos = getDataPointer( pos );
    CLinker * block = beginPos.a();
    uint32_t posInBlock = beginPos.b();
    
    if ( ! block ) // out of range or nothing to read
        return 0;
    
    while ( bytesRead < len )
    {
        data[bytesRead ++] = *( block -> getBytes( posInBlock ++ ) );
        
        if ( posInBlock == block -> m_BlockSize ) break;
    }
    
    if ( bytesRead == len ) return bytesRead;
    
    block = block -> m_NextBlock;
    
    while ( block )
    {
        uint32_t whatDoYouDesire = 0;
        
        if ( len - bytesRead < block -> m_BlockSize )
            whatDoYouDesire = len - bytesRead;
        else
            whatDoYouDesire = block -> m_BlockSize;
        
        for ( uint32_t i = 0; i < whatDoYouDesire; ++i )
        {
            data[bytesRead ++] = *( block -> getBytes( i ) );
        }
        
        if ( bytesRead == len ) break;
        block = block -> m_NextBlock;
    }
    
    return bytesRead;
}

void CVersion::recalculateSize()
{
    m_VersionSize = 0;
    CLinker * block = m_Blocks;
    
    while ( block )
    {
        m_VersionSize += block -> m_BlockSize;
        block = block -> m_NextBlock;
    }
}

CTuple< CLinker *, uint32_t > CVersion::getDataPointer( uint32_t pos ) const
{
    uint32_t position = pos;
    CLinker * block = m_Blocks;
    
    if ( ! block )
        return CTuple< CLinker *, uint32_t >( nullptr, 0 );
    
    uint32_t blockLen = block -> m_BlockSize;
    while ( block && pos >= blockLen )
    {
        pos -= blockLen;
        block = block -> m_NextBlock;
        
        if ( block )
            blockLen = block -> m_BlockSize;
    }
    
    if ( block )
        return CTuple< CLinker *, uint32_t >( block, pos + block -> m_StartPosition );
    
    if ( ! pos && ! block )
        return CTuple< CLinker *, uint32_t >( nullptr, position );
    
    return CTuple< CLinker *, uint32_t >( nullptr, 0 );
}

uint32_t CVersion::size() const
{
    return m_VersionSize;
}

void CVersion::truncate( uint32_t pos )
{
    CTuple< CLinker *, uint32_t > beginPos = getDataPointer( pos );
    CLinker * block = beginPos.a();
    uint32_t posInBlock = beginPos.b();
    
    if ( ! block ) return;
    
    uint32_t newBlockSize = posInBlock - block->m_StartPosition;
    
    if ( ! newBlockSize )
    {
        if ( ! block -> m_PrevBlock )
        {
            delete block;
            m_Blocks = nullptr;
            recalculateSize();
            return;
        }
        block = block -> m_PrevBlock;
        block -> m_NextBlock = nullptr;
        delete block -> m_NextBlock;
    }
    
    block -> resize( block -> m_StartPosition, newBlockSize );
    CLinker * tmp = block;
    block = block -> m_NextBlock;
    tmp -> m_NextBlock = nullptr;
    CLinker * next;
    while ( block )
    {
        next = block -> m_NextBlock;
        delete block;
        block = next;
    }
    
    recalculateSize();
}

//#pragma mark CLinker

CLinker::CLinker( const uint8_t * dataBlock, uint32_t len ) :
m_StartPosition( 0 ),
m_BlockSize( len ),
m_NextBlock( nullptr ),
m_PrevBlock( nullptr )
{
    m_Data = new CData( dataBlock, len );
    m_Data -> addObserver();
}

CLinker::CLinker( const CLinker & second )
{
    m_Data = second.m_Data;
    m_StartPosition = second.m_StartPosition;
    m_BlockSize = second.m_BlockSize;
    m_NextBlock = second.m_NextBlock;
    m_PrevBlock = second.m_PrevBlock;
    
    if ( m_Data )
        m_Data -> addObserver();
}

CLinker & CLinker::operator= ( const CLinker & second )
{
    m_Data = second.m_Data;
    m_StartPosition = second.m_StartPosition;
    m_BlockSize = second.m_BlockSize;
    m_NextBlock = second.m_NextBlock;
    m_PrevBlock = second.m_PrevBlock;
    
    if ( m_Data )
        m_Data -> addObserver();
    return *this;
}

CLinker::~CLinker()
{
    m_Data -> removeObserver();
}

void CLinker::resize( uint32_t start, uint32_t len )
{
    m_StartPosition = start;
    m_BlockSize = len;
}

uint8_t * CLinker::getBytes( uint32_t pos ) const
{
    return m_Data -> dataPtr( m_StartPosition + pos );
}

//#pragma mark CData

CData::CData( const uint8_t * data, uint32_t len )
{
    m_Data = new uint8_t[ m_DataLen = len ];
    
    for ( uint8_t i = 0; i < m_DataLen; i++ )
        m_Data[i] = data[i];
    
    m_HardLinks = 0;
}

CData::~CData()
{
    delete [] m_Data;
}

void CData::addObserver()
{
    m_HardLinks++;
}

void CData::removeObserver()
{
    if ( ! --m_HardLinks )
        delete this;
}

CTuple<uint32_t, uint32_t> CData::getStartLen( uint32_t startPosition, uint32_t length ) const
{
    if ( startPosition > m_DataLen - 1 )
        return CTuple<uint32_t, uint32_t> ( 0, 0 );
    
    if ( startPosition + length > m_DataLen )
        length = m_DataLen - startPosition;
    
    return CTuple<uint32_t, uint32_t> ( startPosition, length );
}

uint8_t * CData::dataPtr( uint32_t pos ) const
{
    if ( pos >= m_DataLen )
        throw "Wrong index!";
    return m_Data + pos;
}

#ifndef __PROGTEST__
bool writeTest( CFile & x,
               const initializer_list < uint8_t > & data,
               uint32_t wrLen )
{
    uint8_t tmp[100];
    uint32_t idx = 0;
    
    for ( auto v : data )
        tmp[idx++] = v;
    
    return x.Write( tmp, idx ) == wrLen;
}

bool readTest( CFile & x,
              const initializer_list < uint8_t > & data,
              uint32_t rdLen )
{
    uint8_t tmp[100];
    uint32_t idx = 0;
    
    if ( x.Read( tmp, rdLen ) != data.size() )
        return false;
    
    for ( auto v : data )
        if ( tmp[idx++] != v )
            return false;
    
    return true;
}

int main( void )
{
    CFile f0;
    assert( writeTest( f0,
                      {
                          10, 20, 30
                      }, 3 ) );
    assert( f0.FileSize() == 3 );
    assert( writeTest( f0,
                      {
                          60, 70, 80
                      }, 3 ) );
    assert( f0.FileSize() == 6 );
    assert( f0.Seek( 2 ) );
    assert( writeTest( f0,
                      {
                          5, 4
                      }, 2 ) );
    assert( f0.FileSize() == 6 );
    assert( f0.Seek( 1 ) );
    assert( readTest( f0,
                     {
                         20, 5, 4, 70, 80
                     }, 7 ) );
    assert( f0.Seek( 3 ) );
    f0.AddVersion();
    assert( f0.Seek( 6 ) );
    assert( writeTest( f0,
                      {
                          100, 101, 102, 103
                      }, 4 ) );
    f0.AddVersion();
    assert( f0.Seek( 5 ) );
    CFile f1( f0 );
    f0.Truncate();
    assert( f0.Seek( 0 ) );
    assert( readTest( f0,
                     {
                         10, 20, 5, 4, 70
                     }, 20 ) );
    assert( f0.UndoVersion() );
    assert( f0.Seek( 0 ) );
    assert( readTest( f0,
                     { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 },
                     20 ) );
    assert( f0.UndoVersion() );
    assert( f0.Seek( 0 ) );
    assert( readTest( f0,
                     {
                         10, 20, 5, 4, 70, 80
                     }, 20 ) );
    assert( !f0.Seek( 100 ) );
    assert( writeTest( f1,
                      {
                          200, 210, 220
                      }, 3 ) );
    assert( f1.Seek( 0 ) );
    assert( readTest( f1,
                     {
                         10, 20, 5, 4, 70, 200, 210, 220, 102, 103
                     }, 20 ) );
    assert( f1.UndoVersion() );
    assert( f1.UndoVersion() );
    assert( readTest( f1,
                     {
                         4, 70, 80
                     }, 20 ) );
    assert( !f1.UndoVersion() );
    
    srand(time(NULL));
    f1.Seek(0);
    
    for ( int i = 0; i < 100000; i++ )
    {
        writeTest( f1,
                  {
                      100
                  }, 1 );
    }
    
    CFile f2(f1);
    
    return 0;
}
#endif              /* __PROGTEST__ */
