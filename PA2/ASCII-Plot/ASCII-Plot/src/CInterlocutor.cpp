
#include "CInterlocutor.h"

CInterlocutor::CInterlocutor( const map<string, string> & flags ) : m_Flags( flags ),
                                                                    m_HB( false ),
                                                                    m_LB( false ),
                                                                    m_PB( false ),
                                                                    m_BB( false )
{
    vector<string> fl = { "--conf", "--hist", "--bar", "--pie", "--line" };
    
    for ( size_t i = 0; i < fl.size(); i++ )
        if ( flags.find( fl[i] ) == flags.end() )
            throw CException( "Insufficient flags... Check the map of flags. There should be"
                              " --conf, --hist, --bar, --pie and --line flags." );
    
    string confPath = m_Flags.find( "--conf" ) -> second;
    m_Config = CConfig( confPath );
    cout << endl;
    
    greetings();
    cout << endl;
    
    try
    {
        cout << "HISTOGRAM\n" << endl;
        CCSV histogramCSV = CCSV( m_Flags.find( "--hist" )->second, m_Config );
        m_Histogram = configureHistogram( histogramCSV );
        m_HB = true;
    }
    catch ( CException & ex )
    {
        cout << "Error occured: " << ex.toString() << endl;
        cout << "The histogram will no be builded." << endl;
    }
    
    try
    {
        cout << "LINE PLOT\n" << endl;
        CCSV linePlotCSV = CCSV( m_Flags.find( "--line" )->second, m_Config );
        m_LinePlot = configureLinePlot( linePlotCSV );
        m_LB = true;
    }
    catch ( CException & ex )
    {
        cout << "Error occured: " << ex.toString() << endl;
        cout << "The line plot will no be builded." << endl;
    }
    
    try
    {
        cout << "PIE CHART\n" << endl;
        CCSV pieChartCSV = CCSV( m_Flags.find( "--pie" )->second, m_Config );
        m_PieChart = configurePieChart( pieChartCSV );
        m_PB = true;
    }
    catch ( CException & ex )
    {
        cout << "Error occured: " << ex.toString() << endl;
        cout << "The pie chart will no be builded." << endl;
    }
    
    try
    {
        cout << "BAR CHART\n" << endl;
        CCSV barChartCSV = CCSV( m_Flags.find( "--bar" )->second, m_Config );
        m_BarChart = configureBarChart( barChartCSV );
        m_BB = true;
    }
    catch ( CException & ex )
    {
        cout << "Error occured: " << ex.toString() << endl;
        cout << "The bar chart will no be builded." << endl;
    }
    
    if ( ! ( m_HB || m_LB || m_PB || m_BB ) )
    {
        cout << "Bad news... No plots will be builded because of too many errors." << endl;
        cout << "Exiting..." << endl;
        return;
    }
    
    cout << "\nGreat!" << endl;
    cout << "Now we can parse all the information and build the plots. Isn't it great?\n" << endl;
    cout << "Working." << flush;
    
    for ( int i = 0; i < 3; i++ )
    {
        sleep( 1 );
        cout << "." << flush;
    }
    cout << "\nDone!\n" << endl;
    int retSys = system("mkdir \"./Plots\" 2>/dev/null");
    retSys ++;
    
    if ( m_HB )
    {
        try
        {
            m_Histogram.writeToFile( "./Plots/Histogram.txt" );
            cout << "The histogram was successfully saved "
                    "to Plots folder in a directory you are in." << endl;
        }
        catch ( CException & ex )
        {
            cout << "An error occured while saving the histogram: " << ex.toString() << endl;
        }
    }
    if ( m_LB )
    {
        try
        {
            m_LinePlot.writeToFile( "./Plots/LinePlot.txt" );
            cout << "The line plot was successfully saved "
                    "to Plots folder in a directory you are in." << endl;
        }
        catch ( CException & ex )
        {
            cout << "An error occured while saving the line plot: " << ex.toString() << endl;
        }
    }
    if ( m_PB )
    {
        try
        {
            m_PieChart.writeToFile( "./Plots/PieChart.txt" );
            cout << "The pie chart was successfully saved "
                    "to Plots folder in a directory you are in." << endl;
        }
        catch ( CException & ex )
        {
            cout << "An error occured while saving the pie chart: " << ex.toString() << endl;
        }
    }
    if ( m_BB )
    {
        try
        {
            m_BarChart.writeToFile( "./Plots/BarChart.txt" );
            cout << "The bar chart was successfully saved "
                    "to Plots folder in a directory you are in." << endl;
        }
        catch ( CException & ex )
        {
            cout << "An error occured while saving the bar chart: " << ex.toString() << endl;
        }
    }
    
    cout << "Have a nice day! Goodbye!\n\n";

    cout << "P.S. If you want to support a developer, you can give him 6 more points."
            " How easily sometimes can someone make one happy. :)\n" << endl;
    
}

void CInterlocutor::greetings() const
{
    cout << "What's your name?\n\n > ";
    string name;
    getline( cin, name );
    
    cout << "Hello, dear " + name + "!\n\n";
    cout << "I'm a program that will help you to visualise your data.\n\n";
    cout << "Four types of charts will be builded:\n"
            "1) Histogram\n"
            "2) Line plot\n"
            "3) Pie chart\n"
            "4) Bar chart\n\n";
    cout << "So let's configure each of plots.\n";
}

CHistogram CInterlocutor::configureHistogram( const CCSV & csv ) const
{
    cout << "Histogram will show you the probability with which one value appears in your data range.\n"
            "Now select names column and a depended on it values column."
            "You can specify only names without values. In that case, the number of occurences of"
            "each name will be used as a value. "
            "So, if you want to select the first column as a name column "
            "and the second as a values column, please, enter \"1(2)\", "
            "for adding only names - just enter \"1\"."
            "You can \"merge\" to histograms into one by using more data columns. "
            "Just separate two numbers or dependencies using a semicolon.\n"
            "Be careful to choose as data column only columns containing numbers or "
            "all string values will be just converted to 0!\n\n"
            "So, I've found these columns in your CSV:\n";
    vector<string> header = csv.getHeader();
    printHeader( header );
    
    return getNamesValuesPlot<CHistogram> ( csv );
}

CLinePlot CInterlocutor::configureLinePlot( const CCSV & csv ) const
{
    cout << "Line plots show number of occurrences of each element. "
            "So, the system here is the same like with histogram. "
            "Just select two columns: names and values. "
            "Of course, you can specify only names. It's possible, again, "
            "to merge 2 plots into one by using more dependencies.\n"
            "Example: \"1(2); 3(4)\"\n\n"
            "So, here is our data:\n";
    vector<string> header = csv.getHeader();
    printHeader( header );
    
    return getNamesValuesPlot<CLinePlot>( csv );
}

CPieChart CInterlocutor::configurePieChart( const CCSV & csv ) const
{
    cout << "Pie charts show the same information (like line plots) but in a different way. "
            "Very soon, if everything goes right, we'll see a beautiful circle separated into segments: "
            "the bigger a segment is, the bigger part it keeps in the data."
            "The data organization is the same as in a line plot. Just use the same syntax.\n\n"
            "For the pie chart you have specified this data:\n";
    vector<string> header = csv.getHeader();
    printHeader( header );
    
    return getNamesValuesPlot<CPieChart>( csv );
}

template <typename CPlot>
CPlot CInterlocutor::getNamesValuesPlot( const CCSV & csv ) const
{
    map<size_t, set<size_t>> dependencies;
    size_t headerSize = csv.getHeader().size();
    
    while ( 1 )
    {
        try
        {
            dependencies = getDependencies( headerSize );
            break;
        }
        catch ( CException & ex )
        {
            cout << "Input error: " << ex.toString() << endl;
            cout << "Try again.\n";
        }
    }

    CPlot retPlot;
    
    for ( map<size_t, set<size_t>>::iterator it = dependencies.begin();
          it != dependencies.end();
          it ++ )
    {
        vector<string> names = csv.getColumn( it -> first );
        
        for ( set<size_t>::iterator setIt = it->second.begin();
              setIt != it->second.end();
              setIt++ )
        {
            
            vector<double> values;
            vector<string> valStr;
            
            valStr = csv.getColumn( *setIt );
            values.resize( valStr.size() );
            transform( valStr.begin(),
                       valStr.end(),
                       values.begin(),
                       [] ( const string & s ) { return atof( s.c_str() ); } );
            
            if ( it == dependencies.begin() )
            {
                if ( *setIt == it->first )
                    retPlot = CPlot( m_Config, names );
                else
                    retPlot = CPlot( m_Config, names, values );
            }
            else
            {
                if ( *setIt == it->first )
                    retPlot.addData( names );
                else
                    retPlot.addData( names, values );
            }
        }
    }
    
    return retPlot;
}

CBarChart CInterlocutor::configureBarChart( const CCSV & csv ) const
{
    cout << "Finally, the last one. Building this plot is much more interesting."
            " The syntax here is almost the same but you cannot specify more than one dependency..."
            "But don't worry, here you specify a column of groups and then "
            "you're able to attach to this group as many columns as you want.\n"
            "For example, you want to build a plot, showing iPad, Mac and iPhone sales in 2013, 2014"
            " and 2015 and you have such data:\n"
            "Year    iPhone    iPad    Mac\n"
            "2013    13        12      4\n"
            "2014    15        11      5\n"
            "2015    12        14      2\n\n"
            "For building a bar chart you want to see, you should use the first column as a groups "
            "column and other as data columns. There will be 3 groups: 2013, 2014, 2015,"
            " each one will have 3 columns: iPhone, iPad and Mac sales in every year.\n"
            "The syntax will look like that:\n"
            "> 1(2,3,4)\n\n"
            "For a pie chart we have such an amazing data:\n";
    vector<string> header = csv.getHeader();
    printHeader( header );
    
    map< size_t, set<size_t>> dependencies = getDependencies( header.size() );
    vector<string> groups = csv.getColumn( dependencies.begin() -> first );
    set<size_t> & valsIndices = dependencies.begin() -> second;
    
    if ( valsIndices.empty() )
        throw CException( "No data was specified. Maybe, you have forgotten "
                          "to enter the values column numbers? Who knows..." );
    
    map<string, vector<double>> values;
    
    for ( set<size_t>::iterator it = valsIndices.begin();
          it != valsIndices.end();
          it ++ )
    {
        string name = header[ *it ];
        vector<string> valStr = csv.getColumn( *it );
        vector<double> vals( valStr.size() );
        transform( valStr.begin(),
                   valStr.end(),
                   vals.begin(),
                   [] ( string & s ) { return atof( s.c_str() ); } );
        values.insert( make_pair( name, vals ) );
    }
    
    return CBarChart( m_Config, groups, values );
}

void CInterlocutor::printHeader( const vector<string> & header ) const
{
    for ( size_t i = 0; i < header.size(); i++ )
    {
        cout << i + 1 << ". " << header[i] << endl;
    }
    cout << endl;
}

map<size_t, set<size_t>> CInterlocutor::getDependencies( size_t max ) const
{
    cout << "And... Your choice is?\n\n > ";
    
    string choiceLine;
    getline( cin, choiceLine );
    choiceLine.erase(remove_if( choiceLine.begin(), choiceLine.end(), ::isspace ), choiceLine.end());
    
    while ( choiceLine.empty() )
    {
        cout << "\nPlease, enter at least one number\n\n > ";
        getline( cin, choiceLine );
        choiceLine.erase(remove_if( choiceLine.begin(), choiceLine.end(), ::isspace ), choiceLine.end());
    }
    
    map<size_t, set<size_t>> numbers;
    stringstream iss( choiceLine );
    string oneDep;
    
    while ( getline( iss, oneDep, ';' ) )
    {
        if ( oneDep.empty() )
            continue;
        
        size_t number;
        stringstream depStream;
        
        string::iterator it = oneDep.begin();
        string num;
        
        while ( it != oneDep.end() && *it != '(' )
        {
            if ( isNumber( *it ) )
                num += *it;
            else
                throw CException( "Invalid char: " + string( 1, *it ) );
            it++;
        }
        
        number = atoi( num.c_str() );
        map<size_t, set<size_t>>::iterator numInMap;
        
        if ( number <= max && number > 0 )
        {
            number --;
            numInMap = numbers.find( number );
            if ( numInMap == numbers.end() )
                numbers.insert( make_pair( number, set<size_t>() ) );
        }
        else
            throw CException( "Invalid column number: " + to_string( number ) );
        
        numInMap = numbers.find( number );
        
        if ( it == oneDep.end() )
            numInMap -> second.insert( number );
        else
        {
            string depStr;
            depStream << string( it + 1, oneDep.end() );
            bool closedParen = false;
            
            while ( getline( depStream, depStr, ',' ) )
            {
                it = depStr.begin();
                num.clear();
                
                while ( it != depStr.end() && *it != ')' )
                {
                    if ( isNumber( *it ) )
                        num += *it;
                    else
                        throw CException( "Invalid char: " + to_string( *it ) );
                    it++;
                }
                
                if ( num.empty() )
                    throw CException( "You should enter at least one number between parentheses." );
                
                if ( it != depStr.end() && *it == ')' )
                {
                    closedParen = true;
                    it ++;
                    if ( it != depStr.end() )
                        throw CException( "Unknown symbol after a closing parenthesis: " + to_string( *it ) );
                }
                
                
                number = atoi( num.c_str() );
                
                if ( number <= max && number > 0 )
                    numInMap -> second.insert( number - 1 );
                else
                    throw CException( "Invalid column number: " + to_string( number ) );
            }
            
            if ( ! closedParen )
            {
                throw CException( "Have you forgotten a closing parenthesis?" );
            }
        }
    }
    
    return numbers;
}

bool CInterlocutor::isNumber( char c ) const
{
    switch ( c )
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
            break;

        default:
            return false;
            break;
    }
}
