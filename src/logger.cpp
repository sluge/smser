//////////////////////////////////////////////////////////////////////////
//    Author :       Igor Sobinov
//    File:          $Source: /var/lib/cvsroot/kss/logger.cpp,v $
//    Revision:      $Revision: 1.1 $
//    Last modified: $Date: 2010/09/21 05:19:15 $
//    Description:   
//////////////////////////////////////////////////////////////////////////

#include "defines.h"
#include "config.h"
#include "logger.h"

////////////////
//Class Logger//
////////////////

CQString Logger::logFile = "smser.txt";

CQString Logger::debug = "debug";
CQString Logger::error = "error";
CQString Logger::critical = "critical" ;
CQString Logger::none = "none";

Logger::Logger() : m_level(eNone), m_curLevel(eNone)
{}

Logger::~Logger()
{
    deinit();
}

Logger* Logger::log()
{
    static Logger inst;
    return &inst;
}
//NOTE:return fake bool value for correct initialization
bool Logger::init()
{
    if(m_curFile.isOpen())
        return true;

    m_curFile.setFileName(logFile);
    if(!m_curFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        m_curFile.setFileName(QDir::tempPath() + QDir::separator() + logFile);
        if(!m_curFile.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qDebug()<<"Error opening log file:"<<m_curFile.fileName();
            return false;
        }
    }

    m_stream.setDevice(&m_curFile);

    return true;
}

void Logger::deinit()
{
    m_curFile.close();
}

Logger& Logger::operator<<(const LoggerLevel& level)
{
    m_curLevel = level;
    return *this;
}

Logger& Logger::operator<<(const char* string)
{
    if(m_level >= m_curLevel && init())
        m_stream<<CQString(string);
    return *this;
}

Logger& Logger::operator<<(CQString& string)
{
    if(m_level >= m_curLevel && init())
        m_stream<<string;
    return *this;
}

Logger& Logger::operator<<(cint& n)
{
    if(m_level >= m_curLevel && init())
        m_stream<<n;
    return *this;
}

Logger& Logger::operator<<(cuint& n)
{
    if(m_level >= m_curLevel && init())
        m_stream<<n;
    return *this;
}

Logger& Logger::operator<<(const long& l)
{
    if(m_level >= m_curLevel && init())
        m_stream<<l;
    return *this;
}

Logger& Logger::operator<<(const QSize& s)
{
    if(m_level >= m_curLevel && init())
        m_stream<<"("<<s.width()<<", "<<s.height()<<")";
    return *this;
}

Logger& Logger::operator<<(const LoggerSignal& s)
{
    if(m_level >= m_curLevel && init())
        switch(s)
        {
            case eDateTime:
                m_stream<<CUR_DATE.toString()<<"   ";
            break;
            case eDate:
                m_stream<<CUR_DATE.date().toString()<<"   ";
            break;

            case eTime:
                m_stream<<CUR_DATE.time().toString()<<"   ";
            break;
    }
    return *this;
}

void Logger::setLevel(const LoggerLevel& level)
{
    m_level = level;
}

void Logger::setLevel(CQString& level)
{
    setLevel(string2logLevel(level));
}

LoggerLevel Logger::string2logLevel(CQString& str)
{
    if(str == debug)
        return eDebug;
    else
    if(str == error)
        return eError;
    else
    if(str == critical)
        return eCritical;
    else
    if(str == none)
        return eNone;

    return eNone;
}
