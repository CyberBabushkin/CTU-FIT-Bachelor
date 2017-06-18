
#ifndef CLinePlot_h
#define CLinePlot_h

#include <stdio.h>
#include "CVirtualPlot.h"

/*!
 * \brief A class that represents a line plot.
 * 
 * Is a child class of CVirtualPlot.
 */
class CLinePlot : public CVirtualPlot
{
    private:
        char                    m_Symbol;           //!< A symbol for a line.
        double                  m_StepY;            //!< A step between Y values
    
        /*!
         * \brief Set all necessary class variables.
         */
        virtual void            setVars             ( );
    
        /*!
         * \brief Draws a line plot.
         */
        virtual void            drawPlot            ( );
    
        /*!
         * \brief Draws one line.
         *
         * @param   index   The index of a line.
         */
        void                    drawLine            ( size_t index );
    
    public:
        /*!
         * \brief An empty constructor.
         */
                                CLinePlot           () {};
    
        /*!
         * \brief A constructor.
         * 
         * @param[in]   config      A CConfig instance.
         * @param[in]   names       A names array.
         * @param[in]   values      An optional values array.
         */
                                CLinePlot           ( const CConfig & config,
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

#endif /* CLinePlot_h */
