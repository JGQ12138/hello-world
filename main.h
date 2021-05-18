#include <iostream>
#include <sqlite3.h>
#include <inifile.h>
#include <log4cplus/log4cplus.h>

#include "readkk.h"
#include "readwf.h"
#include "uploadkk.h"
#include "uploadwf.h"

class Config
{
public:
    static std::string kkpath;
    static std::string wfpath;

    static std::string RoadNo;
    static std::string localip;
    static std::string InterTransectID;
    static std::string kkpost;
    static std::string wfpost;
    sqlite3* db;
};