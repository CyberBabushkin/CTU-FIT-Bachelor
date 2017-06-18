
#include "CHistogram.h"

CHistogram::CHistogram( const CConfig & config,
                        const vector<string> & names,
                        const vector<double> & values ) : CVirtualPlot( names, values ),
                                                          m_ElementsOnInterval( 0 )
{
    string normVal = config.getValueForKey( "hist_normalized" );
    if ( atoi( normVal.c_str() ) )
        m_Normalized = true;
    else
        m_Normalized = false;
    
    string binsVal = config.getValueForKey( "hist_bins" );
    m_Bins = atoi( binsVal.c_str() );
    
    string widVal = config.getValueForKey( "hist_w" );
    string heiVal = config.getValueForKey( "hist_h" );
    
    int w = atoi( widVal.c_str() );
    int h = atoi( heiVal.c_str() );
    
    if ( w > 20 && w <= 1000 )
        m_Width = w;
    
    if ( h <= 20 || h > 1000 )
        m_Height = 40;
    else
        m_Height = h;
    
    CVirtualPlot::initPlotFrame();
    
    if ( m_Bins <= 0 || m_Bins > 10 )
        m_Bins = 10;
    
    CHistogram::setVars();
    
    if ( m_Normalized )
        normalizeData();
    
    CHistogram::drawPlot();
}

void CHistogram::setVars()
{
    m_StepX = (m_Max - m_Min) / m_Bins;
    m_ElementsOnInterval.clear();
    m_ElementsOnInterval.resize( m_Bins );
    
    size_t lastIndex = 0;

    for ( size_t i = 0; i < m_Bins; i++ )
    {
        double lowerBound = m_Min + m_StepX * i;
        double upperBound = lowerBound + m_StepX;
        
        for ( size_t j = lastIndex; j < m_Data.size(); j++ )
        {
            if ( ( ( m_Data[j] > lowerBound
                     || areEqual( lowerBound, m_Data[j] ) )
                   && m_Data[j] < upperBound )
                || ( i + 1 == m_Bins
                     && areEqual( upperBound, m_Data[j] ) ) )
                m_ElementsOnInterval[i] += 1.;
            else
            {
                lastIndex = j;
                break;
            }
        }
    }
    
    m_MaxY = __DBL_MIN__;
    
    for ( size_t i = 0; i < m_ElementsOnInterval.size(); i++ )
    {
        if ( m_ElementsOnInterval[i] > m_MaxY )
            m_MaxY = m_ElementsOnInterval[i];
    }
    
    m_StepY = m_MaxY / 10. + 10e-15;
    
    int numOfSegs = 10.;
    m_LinesBetweenYValues = (m_Height - numOfSegs) / numOfSegs - 1. + 10e-15;
    
    string ms = doubleToString( m_Min );
    m_LongestName = ms.size();
    m_SpacesBetweenXs = (m_Width - (m_LongestName * m_Bins + 3.)) / m_Bins  + 10e-15;
}

void CHistogram::normalizeData()
{
    size_t sum = accumulate( m_ElementsOnInterval.begin(), m_ElementsOnInterval.end(), 0 );
    for ( size_t i = 0; i < m_ElementsOnInterval.size(); i++ )
        m_ElementsOnInterval[i] /= sum;
    
    m_StepY = 1. / ( m_MaxY / m_StepY );
    m_MaxY = 1.;
}

void CHistogram::drawPlot()
{
    for ( size_t i = 0; i < m_ElementsOnInterval.size(); i++ )
    {
        drawTower( i );
    }
    
    vector< string > xVal, yVal;
    
    xVal = stringsOnRange( m_Min, m_Max, m_StepX );
    yVal = stringsOnRange( 0., m_MaxY, m_StepY );
    
    wrapPlotInAxes( xVal, yVal, 6 );
}

void CHistogram::drawTower( size_t index )
{
    if ( m_ElementsOnInterval[index] == 0 ) return;
    
    size_t from0toMax = (m_LinesBetweenYValues + 1.) * ( m_MaxY / m_StepY + 10e-15 ) ;
    size_t YCoodr = ( (double) m_ElementsOnInterval[index] / m_MaxY ) * from0toMax - 1;
    size_t XCoord = index * (m_LongestName + m_SpacesBetweenXs);
    XCoord -= 1; // deleting the leftmost wall
    size_t roofLen = m_LongestName - 1 + m_SpacesBetweenXs;
    
    for ( size_t i = 0; i < roofLen; i++ )
    {
        (*(m_PlotFrame.rbegin() + YCoodr))[XCoord + i + 1] = '_';
    }
    
    for ( size_t i = 0; i < YCoodr; i++ )
    {
        if ( index != 0 ) // left wall
            (*(m_PlotFrame.rbegin() + i))[XCoord] = '|';
        (*(m_PlotFrame.rbegin() + i))[XCoord + roofLen + 1] = '|';
    }
}

void CHistogram::addData( const vector<string> & names,
                          const vector<double> & values )
{
    CVirtualPlot::addData( names, values );
    CHistogram::setVars();
    CVirtualPlot::initPlotFrame();
    CHistogram::drawPlot();
}


