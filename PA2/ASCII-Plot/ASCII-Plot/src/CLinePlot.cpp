
#include "CLinePlot.h"

CLinePlot::CLinePlot( const CConfig & config,
                      const vector<string> & names,
                      const vector<double> & values ) : CVirtualPlot( names, values )
{
    string symStr = config.getValueForKey( "line_symbol" );
    int a;
    
    if ( ! ( a = atoi( symStr.c_str() ) ) )
    {
        stringstream delStream( symStr );
        delStream >> skipws >> m_Symbol;
    } else
    {
        m_Symbol = a;
    }
    
    string widVal = config.getValueForKey( "line_w" );
    string heiVal = config.getValueForKey( "line_h" );
    
    int w = atoi( widVal.c_str() );
    int h = atoi( heiVal.c_str() );
    
    if ( w > 20 && w <= 1000 )
        m_Width = w;
    
    if ( h <= 20 || h > 1000 )
        m_Height = 40;
    else
        m_Height = h;
    
    CVirtualPlot::initPlotFrame();
    
    CLinePlot::setVars();
    CLinePlot::drawPlot();
}

void CLinePlot::setVars()
{
    vector<string>::iterator longestX = max_element( m_Names.begin(),
                                                     m_Names.end(),
                                                     [] ( string & a, string & b )
                                                     { return a.size() < b.size(); } );
    size_t maxX = longestX->size();
    size_t maxDataLen = (m_Width + 4) / maxX;
    
    if ( m_Data.size() > maxDataLen )
    {
        m_Data.resize( maxDataLen );
        m_Names.resize( maxDataLen );
    }
    
    m_SpacesBetweenXs = (m_Width - 3 - (m_LongestName * m_Data.size() + 3.)) / m_Data.size()  + 10e-15;
    int numOfSegs = 10.;
    m_LinesBetweenYValues = (m_Height - numOfSegs) / numOfSegs - 1. + 10e-15;
    
    m_StepY = m_Max / numOfSegs;
}

void CLinePlot::drawPlot()
{
    for ( size_t i = 0; i < m_Data.size(); i++ )
    {
        drawLine( i );
    }
    
    vector<string> yVals = stringsOnRange( 0., m_Max, m_StepY );
    wrapPlotInAxes( m_Names, yVals, 14 );
}

void CLinePlot::drawLine( size_t index )
{
    if ( areEqual( 0., m_Data[index] ) ) return;
    
    size_t from0toMax = (m_LinesBetweenYValues + 1.) * ( m_Max / m_StepY + 10e-15 );
    size_t YCoodr = ( (double) m_Data[index] / m_Max ) * from0toMax;
    size_t XCoord = index * (m_LongestName + m_SpacesBetweenXs) + 3;
    
    for ( size_t i = 0; i < YCoodr; i++ )
    {
        (*(m_PlotFrame.rbegin() + i))[XCoord] = m_Symbol;
    }
}

void CLinePlot::addData( const vector<string> & names,
                         const vector<double> & values )
{
    CVirtualPlot::addData( names, values );
    CVirtualPlot::initPlotFrame();
    CLinePlot::setVars();
    CLinePlot::drawPlot();
}
