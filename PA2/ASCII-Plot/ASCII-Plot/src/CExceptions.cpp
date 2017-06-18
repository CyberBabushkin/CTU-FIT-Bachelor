
#include "CExceptions.h"

CException::CException( const string & s ) : m_Reason( s ) {}

string CException::toString() const
{
    return m_Reason;
}

InvalidDataFileException::InvalidDataFileException( const string & reason ) :
                                                    CException( "[CONFIG] " + reason ) {}

InvalidConfigFileException::InvalidConfigFileException( const string & reason ) :
                                                        CException( "[CSV] " + reason ) {}

KeyNotFoundException::KeyNotFoundException( const string & key ) :
                                            CException( "Key's not found: " + key ) {}

NoDataException::NoDataException( void ) :
                                  CException( "Cannot build a plot. No data found." ) {}

IOException::IOException( const string & r, const string & p ) :
                          CException( "I/O Error! " + r + ".\n" + "\t" + p ) {}

WriteException::WriteException( const string & p ) :
                                IOException( "Couldn't write to file", p ) {}

ReadException::ReadException( const string & p ) :
                              IOException( "Couldn't read from file", p ) {}
