
#ifndef CHistogram_h
#define CHistogram_h

#include <stdio.h>

#include "CVirtualPlot.h" 

/*!
 * \brief A class that represents a histogram plot.
 * 
 * Is a child class of CVirtualPlot.
 */
class CHistogram : public CVirtualPlot
{
    private:
        size_t                  m_Bins;                 //!< A number of bins
        bool                    m_Normalized;           //!< A flag showing if the histogram is normalized
        double                  m_StepX;                //!< A step between X values
        double                  m_StepY;                //!< A step betweem Y values
        double                  m_MaxY;                 //!< Max Y value
        vector<double>          m_ElementsOnInterval;   //!< Number of elements on every interval between 2 Xs
    
        /*!
         * \brief Normalises data.
         */
        void                    normalizeData       ( );
    
        /*!
         * \brief Draws a histogram.
         */
        virtual void            drawPlot            ( );
    
        /*!
         * \brief Draws one histogram column.
         * 
         * @param[in] index The index of a column.
         */
        void                    drawTower           ( size_t index );
    
        /*!
         * \brief Set all necessary class variables.
         */
        virtual void            setVars             ( );
    public:
        /*!
         * \brief An empty constructor.
         */
                                CHistogram          () {};
        /*!
         * \brief A constructor.
         * 
         * @param[in]   config      A CConfig instance.
         * @param[in]   names       A names array.
         * @param[in]   values      An optional values array.
         */
                                CHistogram          ( const CConfig & config,
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

#endif /* CHistogram_h */
