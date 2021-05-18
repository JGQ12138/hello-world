#include <sqlite3.h>
#include <vector>
#include <json/json.h>
#include <log4cplus/log4cplus.h>

#include "tools.h"

class Uploadkk
{
private:
    char *zErrMsg;
    char **azResult; //一维数组存放结果
    int nrow, ncolumn;
public:
    int Upload_kk(std::string roadno , std::string kkpost , sqlite3* db);
};

