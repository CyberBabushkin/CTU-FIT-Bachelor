
#ifndef CPieChart_h
#define CPieChart_h

#include <stdio.h>

#include "CVirtualPlot.h"
#include <cmath>

/*!
 * \brief A class that represents a pie chart.
 * 
 * Is a child class of CVirtualPlot.
 */
class CPieChart : public CVirtualPlot
{
    private:
        string                  m_Symbols;          //!< A set of characters for segments
    
        size_t                  m_PartsInFile;      //!< A number of segments read from a config file
        size_t                  m_Parts;            //!< A number of segments based on a config file and data
    
        /*!
         * \brief Draws a pie chart.
         */
        virtual void            drawPlot            ( );
    
        /*!
         * \brief Draws a legend.
         */
        void                    drawLegend          ( );
    
        /*!
         * \brief A char for a segment,
         *
         * @param[in]   index   An index of a segment
         * @param[in]   angle   An angle in radians / 2 / M_PI
         *
         * @return  A character for a segment.
         */
        char                    getCharOfSegment     ( size_t index, double angle );
    
        /*!
         * \brief Set all necessary class variables.
         */
        virtual void            setVars             ( );

    public:
        /*!
         * \brief An empty constructor.
         */
                                CPieChart           () {};
    
        /*!
         * \brief A constructor.
         * 
         * @param[in]   config      A CConfig instance.
         * @param[in]   names       A names array.
         * @param[in]   values      An optional values array.
         */
                                CPieChart           ( const CConfig & config,
                                                      const vector<string> & names,
                                                      const vector<double> & values = vector<double>(0) );
                                                      
        /*!
         * \brief Adds data to the names and values arrays.
         *
         * @param[in]   names   A names array with new names.
         * @param[in]   values  A values array with new values.
         */
        virtual void            addData             ( const vector<string> & names,
                                                      const vector<double> & values = vector<double>(0) );
};

#endif /* CPieChart_h */
