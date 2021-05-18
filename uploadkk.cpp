#include "uploadkk.h"

int Uploadkk::Upload_kk(std::string roadno , std::string kkpost , sqlite3* db ){
    log4cplus::Logger upload_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));

    int flog;
    std::vector<std::string> data;
    char* rt = sqlite3_mprintf("SELECT MotorVehicleID, InfoKind, SourceID, RoadNo, TollgateID, DeviceID, TransecID, InterTransectID, TransSectDesc, LaneId, LaneNo, Direction, LaneUploadVioID, LaneUploadID, HasPlate, PlateNo, PlateClass, PlateColor, PassTime, PassTimeMills, Speed, VehicleLocation, VehicleColor, VehicleErrorCode, VehicleErrorReason, RecogUsedTime, VehicleStructure, PlateNum, ViolateType, ViolateTypeGA, LeftTopX, LeftTopY, RightBtmX, RightBtmY, PlateNoLeftTopX, PlateNoLeftTopY, PlateNoRightBtmX, PlateNoRightBtmY, VehicleBrand, VehicleBrandSeries, VehicleBrandModel, VehSizeType, VehicleClass, LimitSpeed, RedTime, PassTime1, IfResend, ImageCount, ViolateVideoNum, ViolateVideoType, ViolateVideoPath, ImageID, EventSort, StoragePath, FileFormat, ShotTime, Width, Height, data, PicdataSize, PicdataMd5, status, ininame FROM kkdata WHERE(status = 0) LIMIT 1");
    char* rc = sqlite3_mprintf("SELECT status from kkdata where status = 0");
    char* update;
    int ret = sqlite3_get_table( db , rc , &azResult , &nrow , &ncolumn , &zErrMsg );
    if (ret == SQLITE_OK)
    {
        flog = nrow;
        LOG4CPLUS_INFO(upload_log,"查询到" + std::to_string(flog) + "条没有上传的数据");
        sqlite3_free_table(azResult);
    }else{
        return 0;
    }
    if (nrow != 0)
    {
       for (int i = 0; i < flog; i++)
        {
            int ect = sqlite3_get_table( db , rt , &azResult , &nrow , &ncolumn , &zErrMsg );
            if (ect == SQLITE_OK)
            {
                data.assign(&azResult[ncolumn],&azResult[ncolumn+ncolumn]);
            }else{
                return 0;
            }

            Json::Value root;
            Json::Value kkjson;
            Json::Value image;
            Json::Value first_image;


            kkjson["MotorVehicleID"] = data.at(0);
            kkjson["InfoKind"] = atoi(data.at(1).c_str());
            kkjson["SourceID"] = data.at(2);
            kkjson["RoadNo"] = data.at(3);
            kkjson["TollgateID"] = data.at(4);
            kkjson["DeviceID"] = data.at(5);
            kkjson["TransecID"] = data.at(6);
            kkjson["InterTransectID"] = data.at(7);
            kkjson["TransSectDesc"] = data.at(8);
            kkjson["LaneId"] = atoi(data.at(9).c_str());
            kkjson["LaneNo"] = atoi(data.at(10).c_str());
            kkjson["Direction"] = data.at(11);
            kkjson["LaneUploadVioID"] = data.at(12);
            kkjson["LaneUploadID"] = data.at(13);
            kkjson["HasPlate"] = true;//data.at(14);
            kkjson["PlateNo"] = data.at(15);
            kkjson["PlateClass"] = data.at(16);
            kkjson["PlateColor"] = data.at(17);
            kkjson["PassTime"] = data.at(18);
            kkjson["PassTimeMills"] = atoi(data.at(19).c_str());
            kkjson["Speed"] = atoi(data.at(20).c_str());
            kkjson["VehicleLocation"] = data.at(21);
            kkjson["VehicleColor"] = data.at(22);
            kkjson["VehicleErrorCode"] = atoi(data.at(23).c_str());
            kkjson["VehicleErrorReason"] = atoi(data.at(24).c_str());
            kkjson["RecogUsedTime"] = atoi(data.at(25).c_str());
            kkjson["VehicleStructure"] = atoi(data.at(26).c_str());
            kkjson["PlateNum"] = atoi(data.at(27).c_str());
            kkjson["ViolateType"] = atoi(data.at(28).c_str());
            kkjson["ViolateTypeGA"] = atoi(data.at(29).c_str());
            kkjson["LeftTopX"] = atoi(data.at(30).c_str());
            kkjson["LeftTopY"] = atoi(data.at(31).c_str());
            kkjson["RightBtmX"] = atoi(data.at(32).c_str());
            kkjson["RightBtmY"] = atoi(data.at(33).c_str());
            kkjson["PlateNoLeftTopX"] = atoi(data.at(34).c_str());
            kkjson["PlateNoLeftTopY"] = atoi(data.at(35).c_str());
            kkjson["PlateNoRightBtmX"] = atoi(data.at(36).c_str());
            kkjson["PlateNoRightBtmY"] = atoi(data.at(37).c_str());
            kkjson["VehicleBrand"] = data.at(38);
            kkjson["VehicleBrandSeries"] = data.at(39);
            kkjson["VehicleBrandModel"] = data.at(40);
            kkjson["VehSizeType"] = data.at(41);
            kkjson["VehicleClass"] = data.at(42);
            kkjson["LimitSpeed"] = atoi(data.at(43).c_str());
            kkjson["RedTime"] = atoi(data.at(44).c_str());
            kkjson["PassTime1"] = data.at(45);
            kkjson["IfResend"] = atoi(data.at(46).c_str());
            kkjson["ImageCount"] = atoi(data.at(47).c_str());
            kkjson["ViolateVideoNum"] = atoi(data.at(48).c_str());
            kkjson["ViolateVideoType"] = data.at(49);
            kkjson["ViolateVideoPath"] = data.at(50);

            first_image["ImageID"] = data.at(51);
            first_image["EventSort"] = data.at(52);
            first_image["DeviceID"] = data.at(5);
            first_image["StoragePath"] = data.at(53);
            first_image["FileFormat"] = data.at(54);
            first_image["ShotTime"] = data.at(55);
            first_image["Width"] = data.at(56);
            first_image["Height"] = data.at(57);
            first_image["Data"] = data.at(58);
            first_image["PicDataSize"] = data.at(59);
            first_image["PicDataMd5"] = data.at(60);


            image.append(first_image);
            kkjson["SubImageList"] = image;
            root.append(kkjson);

            LOG4CPLUS_INFO(upload_log,root.toStyledString());

            Tools upload;
            std::string info = upload.results(root,roadno,kkpost);
            if (!info.empty())
            {
                //std::cout << info <<std::endl;
                LOG4CPLUS_INFO(upload_log,info);

                Json::Reader Reader;
                Json::Value DevJson;
                Reader.parse(info,DevJson);
                std::cout << DevJson << std::endl;
                LOG4CPLUS_INFO(upload_log,DevJson.toStyledString());
                for (size_t i = 0; i < DevJson.size(); i++)
                {
                    int status_code = DevJson[i]["StatusCode"].asInt();
                    std::string id = DevJson[i]["Id"].asString();
                    if (status_code == 0)
                    {
                        update = sqlite3_mprintf("UPDATE kkdata SET status = '%d' WHERE ininame = '%s'",1,data.at(62).c_str());
                        //std::cout << update << std::endl;
                        int result = sqlite3_exec(db,update,NULL,NULL,&zErrMsg);

                        if (result == SQLITE_OK){
                            LOG4CPLUS_INFO(upload_log,data.at(62) + " : 这条卡口数据已经上传");
                        }else{
                            return 0;
                        }
                    }
                }
            }
            sqlite3_free_table(azResult);
            data.clear();
        }
    }else{
        return 0;
    }
    return 0;
}