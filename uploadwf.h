#include <curl/curl.h>
#include <json/json.h>
#include <log4cplus/log4cplus.h>
#include <sqlite3.h>
#include <string>
#include <vector>

#include "tools.h"

class Uploadwf
{
private:
    char *zErrMsg;
    char **azResult; //一维数组存放结果
    int nrow, ncolumn;
public:
    int Upload_wf(std::string roadno , std::string kkpost , sqlite3* db);
};