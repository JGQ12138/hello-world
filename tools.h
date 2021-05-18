#pragma once
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <sys/time.h>
#include <json/json.h>
#include <curl/curl.h>
#include <ctime>
#include <sys/timeb.h>
#include <iconv.h>
#include <string.h>
#include <string>

class Tools
{
private:
    
public:
    // 读取文件目录保存到vector
    std::vector<std::string> Ininame(std::string inipath);

    // 车辆标识 
    std::string motorvehicleid();

    // 信息分类 
    std::string infokind();

    // 来源标识
    std::string sourceid(time_t t);

    // 路口号
    std::string tollgateid(std::string roadno);

    // 电子警察主机设备编号 
    std::string deviceid();

    // 摄像机设备编号
    std::string transecid();

    // 内部断面代码 
    std::string intertransectID(std::string id);

    // 断面描述
    std::string Transsectdesc(std::string Location,std::string Direction);

    //  车道 ID 
    std::string laneid();

    // 车道编号 
    std::string laneno();

    // 行驶方向 
    std::string direction(std::string str);

    //车道对应的 18 位公安网违法设备代码
    std::string laneuploadvioid();

    //车道对应的 18 位公安网卡口设备代码
    std::string laneuploadid();

    // 有无车牌 
    std::string hasplate();

    // 号牌种类 
    std::string plateclass(std::string str);

    // 车牌颜色 
    std::string color(std::string color);

    // 经过时刻 
    std::string passTime(std::string ecdtime);

    // 经过时刻毫秒 
    std::string passtimemills();

    // 行驶速度 
    std::string speed();

    // 车辆属地 
    std::string vehiclelocation(std::string location);

    // 出错码  
    std::string vehicleerrorcode();

    // 识别时间 
    std::string recogusedtime();

    std::string vehiclestructure();

    std::string platenum();

    std::string violatetype(std::string type);

    std::string violatetypega(std::string type);

    std::string leftx();

    std::string lefty();

    std::string rightx();

    std::string righty();

    std::string PlateNoleftx();

    std::string PlateNolefty();

    std::string PlateNorightx();

    std::string PlateNorighty();

    std::string vehiclebrand();

    std::string vehiclebrandseries();

    std::string vehiclebrandmodel();

    std::string vehsizetype(std::string size);

    std::string vehicleclass();

    std::string limitspeed();

    std::string redtime();

    std::string ifresend();

    std::string imagecount(std::string type);

    std::string eventsort();

    std::string storagepath(std::string type, std::string pic,std::string ip);

    std::string results(Json::Value data, std::string RodNo, std::string url);

    std::string code_convert(char const *source_charset, char const *to_charset, const std::string& sourceStr);

    std::string GbkToUtf8(const std::string& strGbk);
};
