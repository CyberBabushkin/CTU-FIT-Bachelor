
#ifndef CConfig_h
#define CConfig_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

#include "CExceptions.h"

using namespace std;

/*!
 * \brief A class that represents a configuration file.
 */
class CConfig
{
    private:
        map<string, string>     m_Options;      //!< A map of options and their values
        bool                    m_Empty;        //!< Says if the object is empty or not.
    
        /*! 
         * \brief Parses a file, reads options, writes new.
         *
         * If an error occures, throws an exception.
         *
         * @param[in] filePath A path to a config file.
         */
        void                    parseFile               ( const string & filePath );
    
        /*!
         * \brief Extracts from a file stream the next non-empty and non-comment line.
         *
         * @param[in]  ios     Input file stream.
         * @param[out] outStr  The string into it the next line will be written.
         */
        void                    nextLineWithoutSpaces   ( ifstream & ios, string & outStr ) const;
    
    public:
        /*!
         * \brief An empty constructor. Used to create an empty object.
         */
                                CConfig                 ( ) : m_Empty( true ) {};
        /*!
         * \brief A constructor. 
         *
         * @param[in]  filePath  The path to a configuration file.
         */
                                CConfig                 ( const string & filePath );
    
        /*!
         * \brief Returns a value for the option.
         *
         * @param[in]  key  An option name.
         *
         * @return A value for the key.
         */
        string                  getValueForKey          ( const string & key ) const;
};

#endif /* CConfig_h */
