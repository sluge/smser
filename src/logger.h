//////////////////////////////////////////////////////////////////////////
//    Author :       Igor Sobinov
//    File:          $Source: /var/lib/cvsroot/kss/logger.h,v $
//    Revision:      $Revision: 1.1 $
//    Last modified: $Date: 2010/09/21 05:19:15 $
//    Description:   
//////////////////////////////////////////////////////////////////////////

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "types.h"

#define LOGGER (*Logger::log())
#define LOGGERD (*Logger::log())<<eDebug<<eDateTime
#define NL "\n"

enum LoggerSignal {eDateTime, eDate, eTime};

enum LoggerLevel {eNone = 0, eCritical, eError, eDebug};

class Logger
{
private:

    Logger();

    virtual ~Logger();

public:

    static Logger* log();
    //method for set current log level
    Logger& operator<<(const LoggerLevel& level);

    Logger& operator<<(const char* string);

    Logger& operator<<(CQString& string);

    Logger& operator<<(cint& n);

    Logger& operator<<(cuint& n);

    Logger& operator<<(const long& l);

    Logger& operator<<(const LoggerSignal& s);

    Logger& operator<<(const QSize& s);

    void setLevel(const LoggerLevel& level);

    void setLevel(CQString& level);

private:
    //NOTE:return fake bool value for correct initialization
    bool init();

    void deinit();

    static LoggerLevel string2logLevel(CQString&);
    //File that makes I/O operations
    QFile m_curFile;
    //helpful stream
    QTextStream m_stream;
    //log file name
    static CQString logFile;
    //level to write log
    LoggerLevel m_level,
    //level for current data
                m_curLevel;
    //text strings of log level
    static CQString debug,
                    error,
                    critical,
                    none;
};

#endif //_LOGGER_H_
