
#ifndef CExceptions_h
#define CExceptions_h

#include <stdio.h>
#include <string>

using namespace std;

/*!
 * \brief A simple class representing an exception.
 *
 * Holds only one string (reason) and can only return it through the only method.<br>
 * Supports inheritance.
 */
class CException
{
    private:
        string              m_Reason;       //!< The reason of the exception.
    public:
    
        /*!
         * \brief A constructor. 
         *
         * @param[in]  reason  The reason.
         */
                            CException                      ( const string & reason );
    
        /*!
         * \brief A virtual destructor. Does nothing.
         */
        virtual             ~CException                     ( ) {};
    
        /*!
         * \brief Returns the reason string.
         */
        virtual string      toString                        ( ) const;
};

/*!
 * \brief This exception is thrown when the configuration file has wrong format.
 */
class InvalidConfigFileException : public CException
{
    public:
        /*!
         * \brief A constructor. 
         *
         * @param[in]  reason  The reason.
         */
                            InvalidConfigFileException      ( const string & reason );
};

/*!
 * \brief This exception is thrown when the data file has wrong format.
 */
class InvalidDataFileException : public CException
{
    public:
        /*!
         * \brief A constructor. 
         *
         * @param[in]  reason  The reason.
         */
                            InvalidDataFileException        ( const string & reason );
};

/*!
 * \brief This exception is thrown when an unknown key was found in the config file.
 */
class KeyNotFoundException : public CException
{
    public:
    /*!
     * \brief A constructor.
     *
     * @param[in]  key  The name of the found unknown key.
     */
                            KeyNotFoundException            ( const string & key );
};

/*!
 * \brief This exception is thrown when the data file is empty.
 */
class NoDataException: public CException
{
    public:
        /*!
         * \brief A constructor. 
         */
                            NoDataException                 ( void );
};

/*!
 * \brief This exception is thrown when some file cannot be written or read.
 */
class IOException : public CException
{
    public:
    /*!
     * \brief A constructor.
     *
     * @param[in]  reason  The reason.
     * @param[in]  path    The path of the file.
     */
                            IOException                     ( const string & reason,
                                                              const string & path );
};

/*!
 * \brief This exception is thrown when some file cannot be read.
 */
class ReadException : public IOException
{
    public:
    /*!
     * \brief A constructor.
     *
     * @param[in]  path    The path of the file.
     */
                            ReadException                   ( const string & path );
};

/*!
 * \brief This exception is thrown when some file cannot be written.
 */
class WriteException : public IOException
{
    public:
    /*!
     * \brief A constructor.
     *
     * @param[in]  path    The path of the file.
     */
                            WriteException                  ( const string & path );
};

#endif /* CExceptions_h */
