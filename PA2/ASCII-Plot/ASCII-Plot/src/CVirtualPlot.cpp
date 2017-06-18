
#include "CVirtualPlot.h"

CVirtualPlot::CVirtualPlot()// : CVirtualPlot( vector<string>(1, "Plug"), vector<double>(0) )
{
    m_EmptyObject = true;
}

CVirtualPlot::CVirtualPlot( const vector<string> & names,
                            const vector<double> & values ) : m_SpacesBetweenXs( 1 ),
                                                              m_LinesBetweenYValues( 1 ),
                                                              m_Height( 100 ),
                                                              m_Width( 100 ),
                                                              m_EmptyObject( false )
{
    if ( names.size() == 0 )
        throw NoDataException();
    
    m_Data = values;
    m_Names = names;
    
    CVirtualPlot::manageData();
    CVirtualPlot::setVars();
}

void CVirtualPlot::setVars()
{
    m_Max = *max_element( m_Data.begin(), m_Data.end() );
    m_Min = *min_element( m_Data.begin(), m_Data.end() );
    
    if ( areEqual(m_Min, m_Max) )
    {
        if ( areEqual( m_Min, 0. ) )
            throw CException( "Wrong data. All elements are of a 0 value." );
            
        if ( m_Max < 0 )
            m_Max = 0.;
        else
            m_Min = 0.;
    }
    
    m_Sum = accumulate( m_Data.begin(), m_Data.end(), 0.0 );
    
    vector<string>::iterator longestX = max_element( m_Names.begin(),
                                                     m_Names.end(),
                                                     [] ( string & a, string & b )
                                                     { return a.size() < b.size(); } );
    m_LongestName = longestX->size();
}

void CVirtualPlot::initPlotFrame()
{
    m_PlotFrame = vector< vector<char> >( m_Height, vector<char>( m_Width, ' ' ) );
}

void CVirtualPlot::manageData()
{
    if ( m_Data.size() == 0 )
    {
        sort( m_Names.begin(), m_Names.end() );
        vector<string> newNames;
        
        for ( size_t i = 0; i < m_Names.size(); i++ )
        {
            if ( i == 0 )
            {
                newNames.push_back( m_Names[0] );
                m_Data.push_back( 1 );
                continue;
            }
            
            if ( m_Names[i] == m_Names[i-1] )
            {
                m_Data.back() += 1.;
            } else
            {
                newNames.push_back( m_Names[i] );
                m_Data.push_back( 1 );
            }
        }
        
        m_Names = newNames;
    } else {
    
        for ( double & k : m_Data )
            if ( k < 0. )
                k *= -1.;

        vector<size_t> p = getPermutation( m_Data );
        m_Data = applyPermutation( m_Data, p );
        m_Names = applyPermutation( m_Names, p );
        
        vector<double> newData;
        vector<string> newNames;
        
        for ( size_t i = 0; i < m_Names.size(); i++ )
        {
            if ( i == 0 )
            {
                newNames.push_back( m_Names[0] );
                newData.push_back( m_Data[0] );
                continue;
            }
            
            if ( m_Names[i] == m_Names[i-1] )
            {
                newData.back() += m_Data[i];
            } else
            {
                newNames.push_back( m_Names[i] );
                newData.push_back( m_Data[i] );
            }
        }
        
        m_Names = newNames;
        m_Data = newData;
    }
    
    vector<size_t> p = getPermutation( m_Data );
    m_Data = applyPermutation( m_Data, p );
    m_Names = applyPermutation( m_Names, p );
}

string CVirtualPlot::doubleToString( double num ) const
{
    ostringstream numStream;
    numStream << scientific << setprecision(2);
    numStream << num << flush;
    return numStream.str();
}

vector<size_t> CVirtualPlot::getPermutation( const vector<double> & array ) const
{
    vector<size_t> perm( array.size() );
    
    std::iota( perm.begin(), perm.end(), 0 );
    sort( perm.begin(), perm.end(), [&] ( size_t a, size_t b ) { return array[a] < array[b]; } );
    return perm;
}

template <typename T>
vector<T> CVirtualPlot::applyPermutation( const vector<T> & array,
                                   const vector<size_t> & perm ) const
{
    vector<T> newArr( array.size() );
    transform( perm.begin(), perm.end(), newArr.begin(), [&](size_t a){return array[a];} );
    return newArr;
}

void CVirtualPlot::wrapPlotInAxes( vector<string> XValues, vector<string> YValues, size_t shift )
{
    size_t sizeOfBiggestX = 0;
    for ( string & s : XValues )
        if ( s.size() > sizeOfBiggestX ) sizeOfBiggestX = s.size();
    
    ostringstream oss;
    
    function<string(string &, size_t)> addSpaces = [] ( string & s, size_t max )
                                                    {
                                                        string newS;
                                                        size_t size = s.size();
                                                        size_t left = (max - size) / 2;
                                                        size_t right = max - size - left;
                                                        newS = string( left, ' ' ) + s + string( right, ' ' );
                                                        return newS;
                                                    };
    
    for ( string & s : XValues )
        s = addSpaces( s, sizeOfBiggestX );
    
    for ( string & s : YValues )
    {
        if ( s.size() < 8 )
            s = addSpaces( s, 8 );
        
        if ( s.size() > 8 )
        {
            string newStr( s.begin(), s.begin() + 6 );
            newStr += "..";
            s = newStr;
        }
    }
    
    vector< vector<char> > newPlot( m_Height + 4, vector<char>( m_Width + 15, ' ' ) );
    
    drawAxes( newPlot, XValues, YValues, shift );
    movePlotToAxesPlot( newPlot );
    
    m_PlotFrame = newPlot;
}

void CVirtualPlot::drawAxes( vector< vector<char> > & axesPlot,
                             vector<string> & XValues,
                             vector<string> & YValues,
                             size_t shift ) const
{
    size_t YCoord = axesPlot.size() - 1;
    size_t XCoord = shift;
    
    // X axis numbers
    for ( size_t i = 0; i < XValues.size(); i++ )
    {
        string val = XValues[i];
        if ( i != XValues.size() - 1 )
            val += string( m_SpacesBetweenXs, ' ' );
        copy( val.begin(), val.end(), axesPlot.at(YCoord).begin() + XCoord );
        XCoord += val.size();
    }
    
    // printing the X axis
    YCoord --;
    for_each( axesPlot.at(YCoord).begin() + 11,
              axesPlot.at(YCoord).end(),
              [] ( char & c ) { c = '_'; } );
    
    // printing the Y axis
    for ( string val : YValues )
    {
        val = " " + val + " -";
        copy( val.begin(), val.end(), axesPlot.at(YCoord).begin() );
        YCoord--;
        for ( size_t i = 0; i < m_LinesBetweenYValues; i++ )
        {
            axesPlot.at(YCoord).at(10) = '|';
            YCoord--;
        }
    }
    
}

void CVirtualPlot::movePlotToAxesPlot( vector< vector<char> > & axesPlot )
{
    for ( vector<vector<char>>::reverse_iterator it = m_PlotFrame.rbegin();
          it != m_PlotFrame.rend();
          it++ )
    {
        size_t skipY = 2;
        size_t skipX = 11;
        skipY += it - m_PlotFrame.rbegin();
        
        copy( it->begin(), it->end(), (axesPlot.rbegin() + skipY)->begin() + skipX );
    }
}

void CVirtualPlot::resizePlotFrame()
{
    for_each( m_PlotFrame.begin(),
              m_PlotFrame.end(),
              [this] ( vector<char> & arr ) { arr.resize( m_Width, ' ' ); } );
    
    m_PlotFrame.resize( m_Height, vector<char>( m_Width, ' ' ) );
}

bool CVirtualPlot::areEqual( double a, double b ) const
{
    double delta = a > b ? a - b : b - a;
    double eps = 10e-10;
    
    if ( delta < eps )
        return true;
    
    return false;
}

void CVirtualPlot::addData( const vector<string> & names, const vector<double> & values )
{
    if ( m_EmptyObject )
    {
        throw CException( "Cannot add data to an empty object" );
    }
    
    m_Names.insert( m_Names.end(), names.begin(), names.end() );
    
    if ( values.size() == 0 )
    {
        m_Data.resize( m_Data.size() + m_Names.size(), 1. );
    } else
    {
        m_Data.insert( m_Data.end(), values.begin(), values.end() );
    }
    
    CVirtualPlot::manageData();
    CVirtualPlot::setVars();
}

void CVirtualPlot::writeToFile( const string & path ) const
{
    ofstream file( path, ios::out );
    for ( size_t i = 0; i < m_PlotFrame.size(); i++ )
    {
        for ( size_t j = 0; j < m_PlotFrame[i].size(); j++ )
        {
            file << m_PlotFrame[i][j];
        }
        file << endl;
    }
    
    if ( file.fail() )
        throw WriteException( path );
    
    file.close();
}

vector<string> CVirtualPlot::stringsOnRange( double begin, double end, double step ) const
{
    vector<string> vals;
    
    if ( areEqual( begin, end ) )
    {
        vals.push_back( doubleToString( begin ) );
        return vals;
    }
    
    for ( double m = begin; m < end || areEqual(m, end); m += step )
    {
        double k = areEqual(m, 0.) ? 0. : m + 10e-15;
        string s = doubleToString( k );
        vals.push_back( s );
    }
    
    return vals;
}
