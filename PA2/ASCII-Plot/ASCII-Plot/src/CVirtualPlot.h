
#ifndef CVirtualPlot_h
#define CVirtualPlot_h

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <sstream>
#include <iomanip>

#include "CConfig.h"

using namespace std;

/*! 
 * \brief A pure virtual class representing a plot.
 *
 * The heart of the program. Holds all information needed for building plots, manages data, 
 * has methods to add axes to plots, write plots to a file etc.
 */
class CVirtualPlot
{
    protected:
        vector<string>          m_Names;                //!< Rows names
        vector<double>          m_Data;                 //!< Values
        
        vector< vector<char> >  m_PlotFrame;            //!< Contains a frame for a plot
        double                  m_Max;                  //!< The max values in the data
        double                  m_Min;                  //!< The min values in the data
        double                  m_Sum;                  //!< What's gonna happen if we sum up everything?
        size_t                  m_LongestName;          //!< The length of the longest string in the names array
        
        size_t                  m_SpacesBetweenXs;      //!< A number of spaces between values on the X axis
        size_t                  m_LinesBetweenYValues;  //!< A number of empty lines between values on the Y axis
    
        size_t                  m_Height;               //!< The height of the plot frame
        size_t                  m_Width;                //!< The width of the plot frame
    
        bool                    m_EmptyObject;          //!< A flag representing if the object is empty

        /*!
         * \brief An empty constructor, creates empty object.
         */
                                CVirtualPlot        ( );
    
        /*!
         * \brief A constructor.
         *
         * Creates an instance, manages the data and sets all variables up.
         *
         * @param[in]   names   An array of names.
         * @param[in]   values  An optional array of values for all names. 
         */
                                CVirtualPlot        ( const vector<string> & names,
                                                      const vector<double> & values = vector<double>(0) );
    
        /*! 
         * \brief A virtual destructor. 
         */
        virtual                 ~CVirtualPlot       () {};
    
        /*! 
         * \brief Creates a permutation telling how to sort the input array.
         * 
         * Creates an array of shuffled indices of the input array. If we apply this permutation to 
         * the array, it will be sorted in ascending order.
         *
         * @param[in] array An array to get the permutation from.
         *
         * @return The permutations array.
         */
        vector<size_t>          getPermutation      ( const vector<double> & array ) const;
    
        /*!
         * \brief Applies the input permutation to an array.
         *
         * Creates a new array from the elements of the input array with an apllied permutation.
         *
         * @param[in]   array   An array on which a permutation will be applied.
         * @param[in]   perm    A permutations array.
         *
         * @return The permutated array.
         */
        template <typename T>
        vector<T>               applyPermutation    ( const vector<T> & array,
                                                      const vector<size_t> & perm ) const;
    
        /*!
         * \brief Initialises the plot frame.
         *
         * Creates the plot frame with width and height.
         */
        void                    initPlotFrame       ( );
    
        /*!
         * \brief Manages data.
         *
         * Sorts data, sums data with the same name up, creates data array 
         * if it wasn't specified in the constructor.
         */
        void                    manageData          ( );
    
        /*!
         * \brief Sets up all variables.
         */
        virtual void            setVars             ( );
    
        /*!
         * \brief A small function that checks the equality of two doubles.
         *
         * @param[in]   a   The first double number.
         * @param[in]   b   The second double number.
         *
         * @return  True, if two doubles are equal, otherwise, returns false.
         */
        bool                    areEqual            ( double a, double b ) const;
    
        /*!
         * \brief Converts a double number to the scientific representation string.
         *
         * @param[in] num A double number.
         *
         * @return The string containing this number.
         */
        string                  doubleToString      ( double num ) const;
    
        /*!
         * \brief A pure virtual method drawing a plot.
         */
        virtual void            drawPlot            ( ) = 0;
    
        /*!
         * \brief This method "wraps" a plot in axes.
         *
         * Expands the plot frame, draws axes, calls movePlotToAxes.
         *
         * @param[in]   XValues     An array of values for printing on the X axis.
         * @param[in]   YValues     An array of values for printing on the Y axis.
         * @param[in]   shift       Defines the a number of symbols that will be skipped before printing the first X value.
         */ 
        void                    wrapPlotInAxes      ( vector<string> XValues,
                                                      vector<string> YValues,
                                                      size_t shift = 11 );
    
        /*!
         * \brief Draws axes to the input plot frame.
         *
         * @param[in]   axesPlot    A plot frame.
         * @param[in]   XValues     An array of values for printing on the X axis.
         * @param[in]   YValues     An array of values for printing on the Y axis.
         * @param[in]   shift       Defines the a number of symbols that will be skipped before printing the first X value.
         */
        void                    drawAxes            ( vector< vector<char> > & axesPlot,
                                                      vector<string> & XValues,
                                                      vector<string> & YValues,
                                                      size_t shift ) const;
    
        /*!
         * \brief Moves m_PlotFrame to the new one with the axes.
         *
         * @param[in]   axesPlot    The new plot.
         */
        void                    movePlotToAxesPlot  ( vector< vector<char> > & axesPlot );
    
        /*!
         * \brief Resizes the plot frame to the new values of m_Height and m_Width.
         */
        void                    resizePlotFrame     ( );
    
        /*!
         * \brief Adds data to the names and values arrays.
         *
         * @param[in]   names   A names array with new names.
         * @param[in]   values  A values array with new values.
         */
        virtual void            addData             ( const vector<string> & names,
                                                      const vector<double> & values );
    
        /*!
         * \brief Creates a string representation of doubles in the range [begin, end] with the step step.
         *
         * @param[in]   begin   The beginning of the range.
         * @param[in]   end     The end of the range.
         * @param[in]   step    The step between values.
         *
         * @return An array of string representations.
         */
        vector<string>          stringsOnRange      ( double begin, double end, double step ) const;
    
    public:
    
        /*!
         * \brief Writes the plot frame array to a file.
         *
         * @param[in] path The path to a file.
         */
        virtual void            writeToFile         ( const string & path ) const;
    
};

#endif /* CVirtualPlot_h */
