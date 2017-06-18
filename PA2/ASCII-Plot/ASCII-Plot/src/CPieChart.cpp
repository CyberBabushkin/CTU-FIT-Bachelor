
#include "CPieChart.h"

CPieChart::CPieChart( const CConfig & config,
                      const vector<string> & names,
                      const vector<double> & values ) : CVirtualPlot( names, values )
{
    string sideVal = config.getValueForKey( "pie_sidelen" );
    
    int len = atoi( sideVal.c_str() );
    
    if ( len > 20 && len <= 1000 )
    {
        m_Width = len;
        m_Height = len;
    }
    
    string partsVal = config.getValueForKey( "pie_parts" );
    int parts = atoi( partsVal.c_str() );
    
    if ( parts <= 0 || parts > 16 )
        m_PartsInFile = 16;
    else
        m_PartsInFile = parts;
    
    m_Symbols = config.getValueForKey( "pie_symbols" );
    
    initPlotFrame();
    CPieChart::setVars();
    CPieChart::drawPlot();
}

void CPieChart::drawPlot( )
{
    size_t radius = m_Width / 3;
    size_t skip = radius / 2;
    
    for ( long y = -radius; y <= (signed) radius; y++ )
    {
        string line = "";
        for ( long x = -radius; x <= (signed) radius; x++ )
        {
            double xy = pow(x, 2) + pow(y, 2);
            double r = pow(radius, 2);
            if ( xy < r || areEqual(xy, r) )
            {
                double angle = atan2(y, x) / 2 / M_PI + 0.5;
                line += getCharOfSegment( 0, angle );
            } else
            {
                line += ' ';
            }
        }
        copy( line.begin(), line.end(), (*(m_PlotFrame.begin() + skip + y + radius)).begin() + skip );
    }
    CPieChart::drawLegend();
}

void CPieChart::drawLegend()
{
    size_t maxwr = max_element( m_Names.begin(),
                                m_Names.end(),
                                [] ( const string & a,
                                     const string & b )
                                { return a.size() < b.size(); } ) -> size();
    size_t width = maxwr + 8;
    size_t height = 4 + m_Names.size();
    
    for ( size_t i = 0; i < height; i++ )
    {
        size_t l = m_PlotFrame[0].size();
        m_PlotFrame.insert( m_PlotFrame.begin(), vector<char>( l, ' ' ) );
    }
    
    string line( width, '*' );
    copy( line.rbegin(), line.rend(), m_PlotFrame[0].rbegin() );
    copy( line.rbegin(), line.rend(), m_PlotFrame[height-1].rbegin() );
    line.clear();
    line += "* " + string( width - 4, ' ' ) + " *";
    copy( line.rbegin(), line.rend(), m_PlotFrame[1].rbegin() );
    copy( line.rbegin(), line.rend(), m_PlotFrame[height-2].rbegin() );
    
    for ( size_t i = 2; i < height - 2; i++ )
    {
        string name = m_Names[i-2];
        line.clear();
        line += "* ";
        ostringstream oss;
        oss << setw( (int)maxwr ) << right << name;
        line += oss.str();
        line += " : ";
        if ( i - 2 < m_Symbols.size() )
            line += m_Symbols[i - 2];
        else
            line += " ";
        line += " *";
        copy( line.rbegin(), line.rend(), m_PlotFrame[i].rbegin() );
    }
}

char CPieChart::getCharOfSegment( size_t index, double angle )
{
    if ( index >= m_Parts || index >= m_Symbols.size() )
        return ' ';
    if ( angle < m_Data[index] || areEqual( angle, m_Data[index] ) )
        return m_Symbols[index];
    
    return getCharOfSegment( index + 1, angle - m_Data[index] );
}

void CPieChart::addData( const vector<string> & names,
                            const vector<double> & values )
{
    for_each( m_Data.begin(), m_Data.end(), [this] ( double & val ) { val *= m_Sum; val += 10e-15; } );
    CVirtualPlot::addData( names, values );
    
    CPieChart::setVars();
    initPlotFrame();
    CPieChart::drawPlot();
}

void CPieChart::setVars( )
{
    if ( m_Data.size() < m_PartsInFile )
        m_Parts = m_Data.size();
    else
        m_Parts = m_PartsInFile;
    
    m_Names.resize( m_Parts );
    m_Data.resize( m_Parts );
    
    for_each( m_Data.begin(), m_Data.end(), [this] ( double & val ) { val /= m_Sum; } );
}

