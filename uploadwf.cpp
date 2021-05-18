#include "uploadwf.h"

int Uploadwf::Upload_wf(std::string roadno , std::string wfpost , sqlite3* db){
    log4cplus::Logger upload_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));

    int flog;
    std::vector<std::string> data;
    char* rt = sqlite3_mprintf("SELECT MotorVehicleID, InfoKind, SourceID, RoadNo, TollgateID, DeviceID, TransecID, InterTransectID, TransSectDesc, LaneId, LaneNo, Direction, LaneUploadVioID, LaneUploadID, HasPlate, PlateNo, PlateClass, PlateColor, PassTime, PassTimeMills, Speed, VehicleLocation, VehicleColor, VehicleErrorCode, VehicleErrorReason, RecogUsedTime, VehicleStructure, PlateNum, ViolateType, ViolateTypeGA, LeftTopX, LeftTopY, RightBtmX, RightBtmY, PlateNoLeftTopX, PlateNoLeftTopY, PlateNoRightBtmX, PlateNoRightBtmY, VehicleBrand, VehicleBrandSeries, VehicleBrandModel, VehSizeType, VehicleClass, LimitSpeed, RedTime, PassTime1, IfResend, ImageCount, ViolateVideoNum, ViolateVideoType, ViolateVideoPath, ImageID, EventSort, StoragePath, StoragePath1, FileFormat, ShotTime, Width, Height, Data, Data1, PicDataSize, PicDataMd5, PicDataMd51, status, ininame FROM main.wfdata WHERE(status = 0) LIMIT 1");
    char* rc = sqlite3_mprintf("SELECT status from wfdata where status = 0");
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
            Json::Value wfjson;
            Json::Value image;
            Json::Value first_image;
            Json::Value second_image;

            wfjson["MotorVehicleID"] = data.at(0);
            wfjson["InfoKind"] = atoi(data.at(1).c_str());
            wfjson["SourceID"] = data.at(2);
            wfjson["RoadNo"] = data.at(3);
            wfjson["TollgateID"] = data.at(4);
            wfjson["DeviceID"] = data.at(5);
            wfjson["TransecID"] = data.at(6);
            wfjson["InterTransectID"] = data.at(7);
            wfjson["TransSectDesc"] = data.at(8);
            wfjson["LaneId"] = atoi(data.at(9).c_str());
            wfjson["LaneNo"] = atoi(data.at(10).c_str());
            wfjson["Direction"] = data.at(11);
            wfjson["LaneUploadVioID"] = data.at(12);
            wfjson["LaneUploadID"] = data.at(13);
            wfjson["HasPlate"] = true;//data[14];
            wfjson["PlateNo"] = data.at(15);
            wfjson["PlateClass"] = data.at(16);
            wfjson["PlateColor"] = data.at(17);
            wfjson["PassTime"] = data.at(18);
            wfjson["PassTimeMills"] = atoi(data.at(19).c_str());
            wfjson["Speed"] = atoi(data.at(20).c_str());
            wfjson["VehicleLocation"] = data.at(21);
            wfjson["VehicleColor"] = data.at(22);
            wfjson["VehicleErrorCode"] = atoi(data.at(23).c_str());
            wfjson["VehicleErrorReason"] = atoi(data.at(24).c_str());
            wfjson["RecogUsedTime"] = atoi(data.at(25).c_str());
            wfjson["VehicleStructure"] = atoi(data.at(26).c_str());
            wfjson["PlateNum"] = atoi(data.at(27).c_str());
            wfjson["ViolateType"] = atoi(data.at(28).c_str());
            wfjson["ViolateTypeGA"] = atoi(data.at(29).c_str());
            wfjson["LeftTopX"] = atoi(data.at(30).c_str());
            wfjson["LeftTopY"] = atoi(data.at(31).c_str());
            wfjson["RightBtmX"] = atoi(data.at(32).c_str());
            wfjson["RightBtmY"] = atoi(data.at(33).c_str());
            wfjson["PlateNoLeftTopX"] = atoi(data.at(34).c_str());
            wfjson["PlateNoLeftTopY"] = atoi(data.at(35).c_str());
            wfjson["PlateNoRightBtmX"] = atoi(data.at(36).c_str());
            wfjson["PlateNoRightBtmY"] = atoi(data.at(37).c_str());
            wfjson["VehicleBrand"] = data.at(38);
            wfjson["VehicleBrandSeries"] = data.at(39);
            wfjson["VehicleBrandModel"] = data.at(40);
            wfjson["VehSizeType"] = data.at(41);
            wfjson["VehicleClass"] = data.at(42);
            wfjson["LimitSpeed"] = atoi(data.at(43).c_str());
            wfjson["RedTime"] = atoi(data.at(44).c_str());
            wfjson["PassTime1"] = data.at(45);
            wfjson["IfResend"] = atoi(data.at(46).c_str());
            wfjson["ImageCount"] = atoi(data.at(47).c_str());
            wfjson["ViolateVideoNum"] = atoi(data.at(48).c_str());
            wfjson["ViolateVideoType"] = data.at(49);
            wfjson["ViolateVideoPath"] = data.at(50);

            first_image["ImageID"] = data.at(51);
            first_image["EventSort"] = data.at(52);
            first_image["DeviceID"] = data.at(5);
            first_image["StoragePath"] = data.at(53);
            first_image["FileFormat"] = data.at(55);
            first_image["ShotTime"] = data.at(56);
            first_image["Width"] = data.at(57);
            first_image["Height"] = data.at(58);
            first_image["Data"] = data.at(59);
            first_image["PicDataSize"] = data.at(61);
            first_image["PicDataMd5"] = data.at(62);

            image.append(first_image);
            second_image["ImageID"] = data.at(51);
            second_image["EventSort"] = data.at(52);
            second_image["DeviceID"] = data.at(5);
            second_image["StoragePath"] = data.at(54);
            second_image["FileFormat"] = data.at(55);
            second_image["ShotTime"] = data.at(56);
            second_image["Width"] = data.at(57);
            second_image["Height"] = data.at(58);
            second_image["Data"] = data.at(60);
            second_image["PicDataSize"] = data.at(61);
            second_image["PicDataMd5"] = data.at(63);

            image.append(second_image);

            wfjson["SubImageList"] = image;
            root.append(wfjson);

            LOG4CPLUS_INFO(upload_log,root.toStyledString());

            Tools upload;
            std::string info = upload.results(root,roadno,wfpost);
            if (!info.empty())
            {
                //std::cout << info <<std::endl;
                LOG4CPLUS_INFO(upload_log,info);

                Json::Reader Reader;
                Json::Value DevJson;
                Reader.parse(info,DevJson);
                std::cout << DevJson << std::endl;
                for (size_t i = 0; i < DevJson.size(); i++)
                {
                    int status_code = DevJson[i]["StatusCode"].asInt();
                    std::string id = DevJson[i]["Id"].asString();
                    if (status_code == 0)
                    {
                        update = sqlite3_mprintf("UPDATE wfdata SET status = '%d' WHERE ininame = '%s'",1,data.at(65).c_str());
                        //std::cout << update << std::endl;
                        int result = sqlite3_exec(db,update,NULL,NULL,&zErrMsg);

                        if (result == SQLITE_OK){
                            LOG4CPLUS_INFO(upload_log,data.at(65) + " : 这条违法数据已经上传");
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
        LOG4CPLUS_INFO(upload_log,"没有可以上传的违法数据");
        return 0;
    }
    return 0;
}