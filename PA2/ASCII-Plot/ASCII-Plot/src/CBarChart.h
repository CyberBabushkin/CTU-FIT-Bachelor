
#ifndef CBarChart_h
#define CBarChart_h

#include <stdio.h>
#include "CVirtualPlot.h"

/*!
 * \brief A class that represents a bar chart.
 * 
 * Is a child class of CVirtualPlot.
 */
class CBarChart : public CVirtualPlot
{
    private:
        vector<string>                              m_Groups;               //!< Groups of data
        map<string, vector<double>>                 m_Values;               /*!< Map that holds a name and an array
                                                                             *   with its values for every group.
                                                                             */
        string                                      m_Symbols;              //!< Symbols for drawing columns
        size_t                                      m_ColumnWidth;          //!< The column width
        double                                      m_StepY;                //!< A step between Y values
        size_t                                      m_SpacesBetweenGroups;  //!< A number of spaces between groups
    
        /*!
         * \brief Draws a bar chart.
         */
        virtual void            drawPlot            ( );
    
        /*!
         * \brief Set all necessary class variables.
         */
        virtual void            setVars             ( );
    
        /*!
         * \brief Draws one group of data.
         * 
         * @param   group   The index of group.
         */
        void                    drawGroup           ( size_t group );
    
        /*!
         * \brief Draws a legend.
         */
        void                    drawLegend          ( );
        
    public:
    
        /*!
         * \brief An empty constructor.
         */
                                CBarChart           () {};
    
        /*!
         * \brief A constructor.
         * 
         * @param[in]   config      A CConfig instance.
         * @param[in]   groups      A groups array.
         * @param[in]   values      A values map with names and values for every group.
         */
                                CBarChart           ( const CConfig & config,
                                                      const vector<string> & groups,
                                                      const map<string, vector<double>> & values );
        using CVirtualPlot::addData;
    
        /*!
         * \brief Adds new groups and data for them.
         *
         * @param[in]   groups  New groups.
         * @param[in]   values  A values map with the same names and values for the new groups.
         */
        virtual void            addData             ( const vector<string> & groups,
                                                      const map<string, vector<double>> & values );
};

#endif /* CBarChart_h */
