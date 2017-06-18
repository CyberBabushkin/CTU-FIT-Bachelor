
#ifndef CInterlocutor_h
#define CInterlocutor_h

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <set>
#include "unistd.h"

#include "CConfig.h"
#include "CCSV.h"
#include "CHistogram.h"
#include "CPieChart.h"
#include "CLinePlot.h"
#include "CBarChart.h"

/*! 
 * \brief An interlocutor for users.
 *
 *  A class that speaks to a user, asks them questions and prints the output to a console.
 */
class CInterlocutor
{
    private:
        map<string, string>     m_Flags;
        /*!< A map holds paths to files used to instantiate data plots and a config file.<br>
             Flags:
             - --hist - path to a histogram's CSV
             - --line - path to a line plot's CSV
             - --bar  - path to a bar chart's CSV
             - --pie  - path to a pie chart's CSV
             - --conf - path to the configuration file
         */
        CHistogram              m_Histogram;    //!< Holds an instance of the CHistogram class
        CLinePlot               m_LinePlot;     //!< Holds an instance of the CLinePlot class
        CPieChart               m_PieChart;     //!< Holds an instance of the CPieChart class
        CBarChart               m_BarChart;     //!< Holds an instance of the CBarChart class
        CConfig                 m_Config;       //!< Holds an instance of the CConfig class
    
        bool                    m_HB;           //!< flag holding state if Histogram's built
        bool                    m_LB;           //!< flag holding state if Line Plot's built
        bool                    m_PB;           //!< flag holding state if Pie Chart's built
        bool                    m_BB;           //!< flag holding state if Bar Chart's built
    
        /*!
         * \brief Greets users and prints info.<br>
         * 
         * Ask a users for their name, greets them and prints information about the program.
         */
        void                    greetings               ( ) const;
    
        /*!
         * \brief Configures the histogram.
         *
         * Prints header, returns a configured CHistogram object with data from csv.
         *
         * @param[in]  csv  An instance of CCSV to read data from.
         *
         * @return An instance of CHistogram.
         */
        CHistogram              configureHistogram      ( const CCSV & csv ) const;
    
        /*!
         * \brief Configures the line plot.
         *
         * Prints header, returns a configured CLinePlot object with data from csv.
         *
         * @param[in]  csv  An instance of CCSV to read data from.
         *
         * @return An instance of CLinePlot.
         */
        CLinePlot               configureLinePlot       ( const CCSV & csv ) const;
    
        /*!
         * \brief Configures the pie chart.
         *
         * Prints header, returns a configured CPieChart object with data from csv.
         *
         * @param[in]  csv  An instance of CCSV to read data from.
         *
         * @return An instance of CPieChart.
         */
        CPieChart               configurePieChart       ( const CCSV & csv ) const;
    
        /*!
         * \brief Configures the bar chart.
         *
         * Prints header, sends them to the CBarChart to create an object,
         * returns a configured CBarChart object with data from csv.
         *
         * @param[in]  csv  An instance of CCSV to read data from.
         *
         * @return An instance of CBarChart.
         */
        CBarChart               configureBarChart       ( const CCSV & csv ) const;
    
        /*!
         * \brief Prints list of strings.
         *
         * The list will look like this:
         * -# A
         * -# B
         * -# C
         *
         * @param[in]  header  Vector of strings to be printed.
         */
        void                    printHeader             ( const vector<string> & header ) const;

        /*!
         * \brief A simple function that checks if a character is a digit.
         *
         * @param[in]  c  A char for checking.
         *
         * @return True if a character is a digit '0'-'9'. Otherwise, false.
         */
        bool                    isNumber                ( char c ) const;
    
        /*!
         * \brief A function that converts user input to a map of indices.<br>
         *
         * Reads user input, parses it and converts it to a pair of a column index (starting from 0)
         * and a set of columns indices, that are dependent on the first index.<br>
         * Throws exceptions if the user input was incorrect.<br>
         * Rigth inputs examples: "1(2)", "1(2,3,4)", "1(2);3(4)", "1(2);"
         *
         * @param[in]  max  Max value that a user is allowed to enter.
         *
         * @return True if a character is a digit '0'-'9'. Otherwise, false.
         */
        map<size_t, set<size_t>>getDependencies         ( size_t max ) const;
    
        /*!
         * \brief Template function that creates instances of plots.<br>
         *
         * Creates a plot that has a constructor like CPlot( vector<string> & a, vector<double> & b );<br>
         * Such plots as CLinePlot, CHistogram and CPieChart.
         *
         * @param[in]  csv  An instance of CCSV to read data from.
         *
         * @return An instance of CPlot (template).
         */
        template <typename CPlot>
        CPlot                   getNamesValuesPlot      ( const CCSV & csv ) const;
    public:
        /*!
         * \brief A CInterlocutor constructor.
         *
         * @param[in]  flags  A map of command line flags and paths to files.
         *
         * @return An instance of CPlot (template).
         */
                                CInterlocutor           ( const map<string, string> & flags );
    
};

#endif /* CInterlocutor_h */
