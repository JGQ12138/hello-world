#include <iostream>
#include <inifile.h>
#include <log4cplus/log4cplus.h>
#include <vector>
#include <sqlite3.h>
#include "date.h"
#include "tools.h"

class Readkk
{
private:
    char *zErrMsg;
    char **azResult; //一维数组存放结果
    int nrow, ncolumn;
public:
    int Read_ini(std::string ini_path, std::string roadno, std::string id, std::string ip, sqlite3* db);
};
