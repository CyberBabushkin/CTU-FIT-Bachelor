
#include "CConfig.h"

/* Exception */

CConfig::CConfig( const string & filePath ) : m_Empty( false )
{
    // Configuration file
    m_Options.insert( make_pair( "csv_delimiter", "," ) );
    
    // Histogram
    m_Options.insert( make_pair( "hist_bins", "10" ) );
    m_Options.insert( make_pair( "hist_normalized", "0" ) );
    m_Options.insert( make_pair( "hist_w", "100" ) );
    m_Options.insert( make_pair( "hist_h", "40" ) );
    
    // Pie chart
    m_Options.insert( make_pair( "pie_parts", "10" ) );
    m_Options.insert( make_pair( "pie_sidelen", "100" ) );
    m_Options.insert( make_pair( "pie_symbols", "+=-*&^%$#@~?<>±§" ) );
    
    // Line plot
    m_Options.insert( make_pair( "line_w", "100" ) );
    m_Options.insert( make_pair( "line_h", "40" ) );
    m_Options.insert( make_pair( "line_symbol", "X" ) );
    
    // Bar chart
    m_Options.insert( make_pair( "bar_w", "100" ) );
    m_Options.insert( make_pair( "bar_h", "40" ) );
    m_Options.insert( make_pair( "bar_symbols", "ABCDEFGHIGKLMNOPQRSTUVWXYZ" ) );
    
    map<string, string> back = m_Options;
    
    try
    {
        cout << "Loading user settings..." << endl;
        parseFile( filePath );
        cout << "Successfully loaded the config file." << endl;
    }
    catch ( CException & ex )
    {
        m_Options = back;
        cout << "Failed to load the config file: " + ex.toString() << endl;
    }
}

void CConfig::nextLineWithoutSpaces( ifstream & ios, string & outStr ) const
{
    getline( ios, outStr );
    outStr.erase( remove_if( outStr.begin(), outStr.end(), ::isspace ), outStr.end() );
    while ( ios && ( outStr.empty() || outStr[0] =='#' ) )
    {
        getline( ios, outStr );
        outStr.erase( remove_if( outStr.begin(), outStr.end(), ::isspace ), outStr.end() );
    }
}

void CConfig::parseFile( const string & filePath )
{
    ifstream file( filePath, ios::in );
    
    string line;
    nextLineWithoutSpaces( file, line );
    
    if ( file.fail() )
        throw ReadException( filePath );
    
    if ( line.empty() )
        throw InvalidConfigFileException( "The config file is empty." );
    
    char c = line.front();
    
    if ( c != '{' ) // wrong start
        throw InvalidConfigFileException( "The config file should start with '{'." );
    
    line = string( line.begin() + 1, line.end() );
    
    if ( line.empty() )
        nextLineWithoutSpaces( file, line );
    
    while ( ! line.empty() )
    {
        stringstream str( line );
        string cpair;
        
        while ( getline( str, cpair, ';' ) )
        {
            string::size_type e = cpair.find( '}' );
            
            int i = 0;
            if ( e != string::npos )
                i ++;
            
            if ( e != string::npos && e != cpair.size() - 1 )
                throw InvalidConfigFileException( "I can't stand anything after '}', sorry." );
            else if ( e != string::npos )
                cpair.erase( cpair.end() - 1, cpair.end() );
            
            if ( cpair.empty() ) continue;
            stringstream scpair( cpair );
            
            string key, value;
            getline( scpair, key, ':' );
            getline( scpair, value, ':' );
            
            map<string, string>::iterator foundKey = m_Options.find( key );
            
            if ( foundKey == m_Options.end() ) // the paramenter is not found in the options dictionary
                throw InvalidConfigFileException( "Invalid option: " + key );
            
            if ( value.empty() )
                continue;
            
            foundKey -> second = value;
        }
        
        nextLineWithoutSpaces( file, line );
    }
    file.close();
}

string CConfig::getValueForKey( const string & key ) const
{
    if ( m_Empty )
        throw KeyNotFoundException( key );

    map<string, string>::const_iterator val = m_Options.find( key );
    if ( val == m_Options.cend() )
        throw KeyNotFoundException( key );
    
    return val -> second;
}
