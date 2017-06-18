
#ifndef CCSV_h
#define CCSV_h

#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "CExceptions.h"
#include "CConfig.h"

using namespace std;

/*! 
 * \brief A class that represents the data in CSV files.
 */
class CCSV
{
    private:
        vector< vector<string> >                m_Columns;      //!< A table of data, looks like a standart CSV file.
        size_t                                  m_BiggestSize;  //!< The longest string size in the table.
    
        /*!
         * \brief Parses a CSV file, extracts info and saves it to the m_Columns table.
         *
         * @param[in]  path  The path to a CSV file.
         * @param[in]  delim The delimiter char used in a CSV file.
         */
        void                parseCSV            ( const string & path,
                                                  char delim );
    public:
        /*!
         * \brief A constructor.
         *
         * @param[in]  path    The path to a file.
         * @param[in]  config  A CConfig instance containing info about the delimiter.
         */
                            CCSV                ( const string & path,
                                                  CConfig & config );
    
        /*!
         * \brief Returns the header of the CSV data.
         *
         * @return An array of strings - column names.
         */
        vector<string>      getHeader           ( ) const;
    
        /*!
         * \brief Returns a column data.
         *
         * @param[in]  index  Column index.
         *
         * @return An array of column values.
         */
        vector<string>      getColumn           ( size_t index ) const;
    
        /*!
        * \brief Number of columns in a CSV file.
        *
        * @return Number of columns.
        */
        size_t              countColumns        ( ) const;
    
        /*!
        * \brief Returns the longest string size in a CSV file.
        *
        * @return The longest string size in a CSV file.
        */
        size_t              longestLineSize     ( ) const;
};

#endif /* CCSV_h */
