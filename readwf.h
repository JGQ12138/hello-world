#include <iostream>
#include <inifile.h>
#include <log4cplus/log4cplus.h>
#include <vector>
#include <sqlite3.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/md5.h>
#include "date.h"
#include "tools.h"

class Readwf
{
private:
    char *zErrMsg;
    char **azResult; //一维数组存放结果
    int nrow, ncolumn;
    std::string file_md5(string file_name);
    char * Base64Encode(const char * input, int length, bool with_new_line);
    std::string base64(std::string pic);
public:
    int Read_ini(std::string ini_path, std::string roadno , std::string id, std::string ip, sqlite3* db);
};
