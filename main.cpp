#include "main.h"

std::string Config::kkpath;
std::string Config::wfpath;

std::string Config::RoadNo;
std::string Config::localip;
std::string Config::InterTransectID;
std::string Config::kkpost;
std::string Config::wfpost;
sqlite3* db;

void init();

int main(){
    log4cplus::initialize();
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("./config/log4cplus.config"));
    log4cplus::Logger code_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));
    init();

    Config config;

    int ret = sqlite3_open("data.db", &config.db);
    if (ret == SQLITE_OK)
    {
        LOG4CPLUS_INFO(code_log,"sqlite open successful");
        char* rt = sqlite3_mprintf("delete from kkdata where datetime('now','localtime','-1 hours') > Time and status = 1;delete from wfdata where datetime('now','localtime','-1 hours') > Time and status = 1;");
        int result = sqlite3_exec(config.db,rt,NULL,NULL,NULL);
        if (result == SQLITE_OK){
            std::cout << "删除前一个小时的数据" << std::endl;
        }      
    }else{
        char error[64];
        sprintf(error, "%s : %s", "无法打开数据库:",sqlite3_errmsg(config.db));
        sqlite3_close(config.db);
        LOG4CPLUS_ERROR(code_log,error);
        exit(0);
    }
    
    Readkk kk_read;
    kk_read.Read_ini(config.kkpath,config.RoadNo,config.InterTransectID, config.localip, config.db);

    Uploadkk kk_upload;
    kk_upload.Upload_kk(config.RoadNo,config.kkpost,config.db);

    Readwf wf_read;
    wf_read.Read_ini(config.wfpath,config.RoadNo,config.InterTransectID,config.localip,config.db);

    Uploadwf wf_upload;
    wf_upload.Upload_wf(config.RoadNo,config.kkpost,config.db);

    return 0;
}

void init(){

    Config Code_Config;

    using namespace inifile;

    IniFile Config_ini;
    int flog = Config_ini.Load("./config/config.ini");
    if (flog == 5)
    {
        std::cout << "打开文件失败" << std::endl;
    }

    Config_ini.GetStringValue("path","kkpath",&Code_Config.kkpath);
    //LOG4CPLUS_INFO(code_log,Code_Config.kkpath);

    Config_ini.GetStringValue("path","wfpath",&Code_Config.wfpath);
    //LOG4CPLUS_INFO(code_log,Code_Config.wfpath);

/*     Config_ini.GetStringValue("path","db",&Code_Config.db);
    LOG4CPLUS_INFO(code_log,Code_Config.db); */

    Config_ini.GetStringValue("config","RoadNo",&Code_Config.RoadNo);
    //LOG4CPLUS_INFO(code_log,Code_Config.RoadNo);

    Config_ini.GetStringValue("config","localip",&Code_Config.localip);
    //LOG4CPLUS_INFO(code_log,Code_Config.localip);

    Config_ini.GetStringValue("config","InterTransectID",&Code_Config.InterTransectID);
    //LOG4CPLUS_INFO(code_log,Code_Config.InterTransectID);

    Config_ini.GetStringValue("config","kkpost",&Code_Config.kkpost);
    //LOG4CPLUS_INFO(code_log,Code_Config.kkpost);

    Config_ini.GetStringValue("config","wfpost",&Code_Config.wfpost);
    //LOG4CPLUS_INFO(code_log,Code_Config.wfpost);
}