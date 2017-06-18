
#include "CCSV.h"

CCSV::CCSV( const string & path, CConfig & config ) : m_BiggestSize( 0 )
{
    string  delStr;
    char    del;
    
    int     ASCIIDelim;
    
    delStr = config.getValueForKey( "csv_delimiter" );
    
    if ( ! ( ASCIIDelim = atoi( delStr.c_str() ) ) )
    {
        stringstream delStream( delStr );
        delStream >> skipws >> del;
    } else
    {
        del = ASCIIDelim;
    }
    
    parseCSV( path, del );
    
    for ( size_t i = 0; i < m_Columns.size(); i++ )
    {
        for ( size_t j = 0; j < m_Columns[i].size(); j++ )
        {
            if ( m_Columns[i][j].size() > m_BiggestSize )
                m_BiggestSize = m_Columns[i][j].size();
        }
    }
}

void CCSV::parseCSV( const string & path, char delim )
{
    ifstream        csv( path.c_str(), ios_base::in );
    string          cell;
    
    // reading header
    string          line;
    stringstream    lineStream;
    
    getline( csv, line );
    lineStream << line;
    
    if ( csv.fail() )
        throw ReadException( path );
    
    while ( getline( lineStream, cell, delim ) )
    {
        vector<string> column;
        column.push_back( cell );
        m_Columns.push_back( column );
    }
    
    size_t numberOfColumns = m_Columns.size();
    
    while ( csv )
    {
        line.clear();
        getline( csv, line );
        
        string chk = line;
        chk.erase( std::remove_if( chk.begin(), chk.end(), ::isspace ), chk.end() );
        
        if ( chk.empty() )
            continue;
        
        lineStream.clear();
        lineStream << line;
        size_t readCells = 0;
        
        while ( getline( lineStream, cell, delim ) )
        {
            if ( readCells == numberOfColumns )
                throw InvalidDataFileException( "Redundant data." );
            
            if ( cell.size() == 0 )
                throw InvalidDataFileException( "Cells must contain at least one character." );
            
            m_Columns[ readCells ++ ].push_back( cell );
        }
        
        if ( readCells < numberOfColumns )
            throw InvalidDataFileException( "Insufficient data." );
    }
    
    csv.close();
}

vector<string> CCSV::getColumn( size_t index ) const
{
    vector<string> ret( m_Columns[index].size() - 1 );
    copy( m_Columns[index].begin() + 1, m_Columns[index].end(), ret.begin() );
    return ret;
}

vector<string> CCSV::getHeader() const
{
    vector<string> header;
    for ( size_t i = 0; i < m_Columns.size(); i++ )
    {
        header.push_back( m_Columns[i][0] );
    }
    return header;
}

size_t CCSV::countColumns() const
{
    return m_Columns.size();
}

size_t CCSV::longestLineSize() const
{
    return m_BiggestSize;
}
