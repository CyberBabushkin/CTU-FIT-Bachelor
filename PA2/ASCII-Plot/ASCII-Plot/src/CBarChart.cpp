
#include "CBarChart.h"

CBarChart::CBarChart( const CConfig & config,
                      const vector<string> & groups,
                      const map<string, vector<double>> & values )
                                                  : CVirtualPlot( vector<string>( 1, "Plug" ) )
{
    m_Groups = groups;
    m_Min = __DBL_MAX__;
    m_Max = __DBL_MIN__;
    
    m_Names.clear();
    m_Data.clear();
    
    m_Values = values;
    
    for ( map<string, vector<double>>::iterator i = m_Values.begin();
          i != m_Values.end();
          i ++ )
    {
        for ( double & k : i -> second )
            if ( k < 0. )
                k *= -1.;
                
        if ( m_Groups.size() != i->second.size() )
            throw CException( "[Bar chart] Incorrect data length." );
    }
    
    string widVal = config.getValueForKey( "bar_w" );
    string heiVal = config.getValueForKey( "bar_h" );
    int w = atoi( widVal.c_str() );
    int h = atoi( heiVal.c_str() );
    
    if ( w > 20 && w <= 1000 )
        m_Width = w;
    
    if ( h <= 20 || h > 1000 )
        m_Height = 40;
    else
        m_Height = h;
    
    CVirtualPlot::initPlotFrame();
    
    m_Symbols = config.getValueForKey( "bar_symbols" );
    
    CBarChart::setVars();
    CBarChart::drawPlot();
}

void CBarChart::setVars()
{
    m_Max = __DBL_MIN__;
    m_Min = 0.;
    
    for ( map<string, vector<double>>::iterator i = m_Values.begin();
          i != m_Values.end();
          i ++ )
    {
        double max = *max_element( i->second.begin(), i->second.end() );
        
        if ( max > m_Max )
            m_Max = max;
    }
    
    if ( areEqual( m_Max, m_Min ) )
    {
        if ( areEqual( m_Min, 0. ) )
            throw CException( "[Bar chart] Wrong data. All elements are of a 0 value." );
            
        if ( m_Max < 0 )
            m_Max = 0.;
        else
            m_Min = 0.;
    }

    int numOfSegs = 10;
    m_LinesBetweenYValues = (m_Height - numOfSegs) / numOfSegs - 1. + 10e-15;
    m_StepY = ( m_Max - m_Min ) / numOfSegs;
    
    vector<string>::iterator longestX = max_element( m_Groups.begin(),
                                                     m_Groups.end(),
                                                     [] ( string & a, string & b )
                                                     { return a.size() < b.size(); } );
    m_LongestName = longestX->size();
    m_ColumnWidth = 3;
    
    /* Here we choose between 2 values: 
       1) We're counting the length of all columns.
       2) We're counting the length of a string containing all names
    */
    size_t colsCount = m_Groups.size() * m_Values.size() * m_ColumnWidth;
    size_t nameCount = m_LongestName * m_Groups.size();
    size_t max = colsCount > nameCount ? colsCount : nameCount;
    
    while ( max > m_Width - m_Groups.size() + 1 )
    {
        longestX = max_element( m_Groups.begin(),
                                m_Groups.end(),
                                [] ( string & a, string & b )
                                { return a.size() < b.size(); } );
        m_Groups.erase( longestX );
        
        if ( m_Groups.empty() )
            throw CException( "Your data has too long names in the groups column." );
        
        longestX = max_element( m_Groups.begin(),
                                m_Groups.end(),
                                [] ( string & a, string & b )
                                { return a.size() < b.size(); } );
        m_LongestName = longestX->size();
        
        for ( map<string, vector<double>>::iterator i = m_Values.begin();
              i != m_Values.end();
              i ++ )
        {
            i->second.pop_back();
        }
        
        colsCount = m_Groups.size() * m_Values.size() * m_ColumnWidth;
        nameCount = m_LongestName * m_Groups.size();
        max = colsCount > nameCount ? colsCount : nameCount;
    }
    
//    if ( m_LongestName >= m_Width / m_Groups.size() )
//            throw CException( "[Bar chart] The name \"" + *longestX + "\" is too long." );
    
    if ( m_Groups.size() > 1 )
        m_SpacesBetweenGroups = m_SpacesBetweenXs = ( m_Width - 3 - max ) / ( m_Groups.size() - 1 );
    else
        m_SpacesBetweenGroups = 0;
    
    if ( nameCount > colsCount )
        m_SpacesBetweenGroups += (nameCount - colsCount) / m_Groups.size();
    
    if ( colsCount > nameCount )
        m_SpacesBetweenXs += (colsCount - nameCount) / m_Groups.size();
}

void CBarChart::drawPlot()
{
    for ( size_t i = 0; i < m_Groups.size(); i++ )
    {
        drawGroup( i );
    }
    
    vector<string> yVals = stringsOnRange( m_Min, m_Max, m_StepY );
    wrapPlotInAxes( m_Groups, yVals, 14 );
    drawLegend();
}

void CBarChart::drawGroup( size_t group )
{
    size_t curCol = 0;
    for ( map<string, vector<double>>::iterator column = m_Values.begin();
          column != m_Values.end();
          column ++ )
    {
        if ( areEqual( 0., column->second[group] ) )
            return;
    
        size_t fromMinToMax = (m_LinesBetweenYValues + 1.) * ( (m_Max - m_Min) / m_StepY + 10e-15 );
        size_t YCoodr = (column->second[group] - m_Min) / (m_Max - m_Min) * fromMinToMax;
        
        size_t groupsPrinted = m_ColumnWidth * group * m_Values.size();
        size_t colsPrinted = m_ColumnWidth * curCol;
        size_t spaces = m_SpacesBetweenGroups * group;
        size_t XCoord = groupsPrinted + colsPrinted + spaces + 3;
        
        if ( YCoodr >= m_Height || XCoord >= m_Width )
            throw CException( "" );
        
        for ( size_t col = 0; col < m_ColumnWidth; col++ )
        {
            for ( size_t i = 0; i < YCoodr; i++ )
            {
                char c;
                if ( curCol >= m_Symbols.size() )
                    c = ' ';
                else
                    c = m_Symbols[curCol];
                
                (*(m_PlotFrame.rbegin() + i))[XCoord] = c;
            }
            XCoord ++;
        }
        curCol++;
    }
    
}

void CBarChart::addData( const vector<string> & groups,
                         const map<string, vector<double>> & values )
{
    if ( m_EmptyObject )
    {
        throw CException( "Cannot add data to an empty object" );
    }
    
    for ( map<string, vector<double>>::const_iterator it = values.begin();
          it != values.end();
          it ++ )
    {
        if ( m_Values.size() != values.size()
             || it -> second.size() != groups.size() )
        {
            throw CException( "[Bar chart] Incorrect data." );
        }
    }
    
    vector<string> grBack = m_Groups;
    map<string, vector<double>> valBack = m_Values;
    
    for ( size_t i = 0; i < groups.size(); i++ )
    {
        for ( size_t j = 0; j < m_Groups.size(); j++ )
        {
            if ( m_Groups[j] == groups[i] )
                throw CException( "[Bar chart] Cannot modify existing groups."
                                  " Check the data being added." );
        }
    }
    
    m_Groups.insert( m_Groups.end(), groups.begin(), groups.end() );
    
    for ( map<string, vector<double>>::iterator it = m_Values.begin();
          it != m_Values.end();
          it ++ )
    {
        map<string, vector<double>>::const_iterator a = values.find( it -> first );
        if ( a == values.end() )
        {
            m_Groups = grBack;
            m_Values = valBack;
            throw CException( "[Bar chart] Insufficient data. "
                              "You should specify values for all columns in every "
                              "new group you want to be added." );
        }
        
        it->second.insert( it->second.end(), a->second.begin(), a->second.end() );
    }
    
    CVirtualPlot::initPlotFrame();
    CBarChart::setVars();
    CBarChart::drawPlot();
}

void CBarChart::drawLegend()
{
    size_t maxwr = max_element( m_Values.begin(),
                                m_Values.end(),
                                [] ( const pair<string, vector<double>> & a,
                                     const pair<string, vector<double>> & b )
                                { return a.first.size() < b.first.size(); } ) -> first.size();
    size_t width = maxwr + 8;
    size_t height = 4 + m_Values.size();
    
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
        map<string, vector<double>>::iterator it = m_Values.begin();
        for ( size_t j = 0; j < i - 2; j++ )
        {
            it++;
        }
        string name = it -> first;
        line.clear();
        line += "* ";
        ostringstream oss;
        oss << setw( (int)maxwr ) << right << name;
        line += oss.str();
        line += " : ";
        line += m_Symbols[i - 2];
        line += " *";
        copy( line.rbegin(), line.rend(), m_PlotFrame[i].rbegin() );
    }
}
