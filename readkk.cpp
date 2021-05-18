#include "readkk.h"

int Readkk::Read_ini(std::string ini_path, std::string roadno , std::string id, std::string ip, sqlite3* db){

    Data kkdata;
    using namespace inifile;
    IniFile Config_ini;
    Tools tools;

    log4cplus::Logger readkk_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));
    
    std::vector<std::string> ini_name = tools.Ininame(ini_path);
    for (size_t i = 0; i < ini_name.size(); i++)
    {
        time_t t = time(0);
        char tmp[32];
		memset(tmp,0,sizeof(tmp));
        strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
        string kk_time = tmp;

        char* sel = sqlite3_mprintf("select ininame from kkdata where ininame = '%s';",ini_name.at(i).c_str());

        int ret = sqlite3_get_table( db , sel , &azResult , &nrow , &ncolumn , &zErrMsg );
        if (ret == SQLITE_OK && nrow == 0)
        {
            LOG4CPLUS_INFO(readkk_log,ini_name.at(i).c_str());

            int flog = Config_ini.Load(ini_name.at(i));
            if (flog == 5)
            {
                LOG4CPLUS_INFO(readkk_log,"卡口ini文件读取失败 : " + ini_name.at(i));
                break;
            }

            kkdata.MotorVehicleID = tools.motorvehicleid();
			LOG4CPLUS_INFO(readkk_log,"ID : " + kkdata.MotorVehicleID);
            kkdata.InfoKind = tools.infokind();
            kkdata.SourceID = tools.sourceid(t);
            kkdata.RoadNo = roadno;
            kkdata.TollgateID = tools.tollgateid(roadno);
            kkdata.DeviceID = tools.deviceid();
            kkdata.TransecID = tools.transecid();
            kkdata.InterTransectID = tools.intertransectID(id);
            LOG4CPLUS_INFO(readkk_log,"内部断面代码为 : " + kkdata.InterTransectID);
            
            std::string dir,loca;
            Config_ini.GetStringValue("RecordInfo","Direction",&dir);
            Config_ini.GetStringValue("RecordInfo","Location",&loca);
            kkdata.TransSectDesc = tools.Transsectdesc(tools.GbkToUtf8(loca),tools.GbkToUtf8(dir));
            LOG4CPLUS_INFO(readkk_log,"断面描述 : " + kkdata.TransSectDesc);

            kkdata.LaneId = tools.laneid();
            kkdata.LaneNo = tools.laneno();
            kkdata.Direction = tools.direction(tools.GbkToUtf8(dir));

            kkdata.LaneUploadVioID = tools.laneuploadvioid();
            kkdata.LaneUploadID = tools.laneuploadid();
            kkdata.HasPlate = tools.hasplate();

            std::string plateno;
            Config_ini.GetStringValue("RecordInfo", "PlateText", &plateno);
            kkdata.PlateNo = tools.GbkToUtf8(plateno);

            std::string plate;
            Config_ini.GetStringValue("RecordInfo", "PlateType",&plate);
            kkdata.PlateClass = tools.plateclass(plate);

            std::string kk_color;
            Config_ini.GetStringValue("RecordInfo", "PlateColor" , &kk_color);
            kkdata.PlateColor = tools.color(kk_color);

            std::string pass_time;
            Config_ini.GetStringValue("RecordInfo", "EndTime", &pass_time);
            kkdata.PassTime = tools.passTime(pass_time);

            kkdata.PassTimeMills = tools.passtimemills();
            kkdata.Speed = tools.speed();
            kkdata.VehicleLocation = tools.vehiclelocation(kkdata.PlateNo);
            kkdata.VehicleColor = kkdata.PlateColor;
            kkdata.VehicleErrorCode = tools.vehicleerrorcode();
            kkdata.VehicleErrorReason = "0";
            kkdata.RecogUsedTime = tools.recogusedtime();
            kkdata.VehicleStructure = tools.vehiclestructure();
            kkdata.PlateNum = tools.platenum();
            kkdata.ViolateType = tools.violatetype("kk");
            kkdata.ViolateTypeGA = tools.violatetypega("kk");
            kkdata.LeftTopX = tools.leftx();
            kkdata.LeftTopY = tools.lefty();
            kkdata.RightBtmX = tools.rightx();
            kkdata.RightBtmY = tools.righty();
            kkdata.PlateNoLeftTopX = tools.PlateNoleftx();
            kkdata.PlateNoLeftTopY = tools.PlateNolefty();
            kkdata.PlateNoRightBtmX = tools.PlateNorightx();
            kkdata.PlateNoRightBtmY = tools.PlateNorighty();
            kkdata.VehicleBrand = tools.vehiclebrand();
            kkdata.VehicleBrandSeries = tools.vehiclebrandseries();
            kkdata.VehicleBrandModel = tools.vehiclebrandmodel();

            std::string kk_sizetype;
            Config_ini.GetStringValue("RecordInfo", "VechileType", &kk_sizetype);
            kkdata.VehSizeType = tools.vehsizetype(kk_sizetype);
            kkdata.VehicleClass = tools.vehicleclass();
            kkdata.LimitSpeed = tools.limitspeed();
            kkdata.RedTime = tools.redtime();

            std::string pass_time1;
            Config_ini.GetStringValue("RecordInfo", "EndTime", &pass_time1);
            kkdata.PassTime1 = tools.passTime(pass_time1);
            kkdata.IfResend = tools.ifresend();
            kkdata.ImageCount = tools.imagecount("kk");

            kkdata.ImageID = kkdata.SourceID;
            kkdata.EventSort = tools.eventsort();

            std::string picfile;
            Config_ini.GetStringValue("RecordInfo", "Pic1", &picfile);
            kkdata.StoragePath = tools.storagepath("kk", picfile, ip);
            kkdata.Type = "14";
            kkdata.FileFormat = "jpg";
            kkdata.ShotTime = kkdata.PassTime;
            kkdata.Width = "";
            kkdata.Height = "";
            kkdata.Data = "";

            char *rt = sqlite3_mprintf("INSERT INTO kkdata (MotorVehicleID, InfoKind, SourceID, RoadNo, TollgateID, DeviceID, TransecID, InterTransectID, TransSectDesc, LaneId, LaneNo, Direction, LaneUploadVioID, LaneUploadID, HasPlate, PlateNo, PlateClass, PlateColor, PassTime, PassTimeMills, Speed, VehicleLocation, VehicleColor, VehicleErrorCode, VehicleErrorReason, RecogUsedTime, VehicleStructure, PlateNum, ViolateType, ViolateTypeGA, LeftTopX, LeftTopY, RightBtmX, RightBtmY, PlateNoLeftTopX, PlateNoLeftTopY, PlateNoRightBtmX, PlateNoRightBtmY, VehicleBrand, VehicleBrandSeries, VehicleBrandModel, VehSizeType, VehicleClass, LimitSpeed, RedTime, PassTime1, IfResend, ImageCount, ViolateVideoNum, ViolateVideoType, ViolateVideoPath, ImageID, EventSort, StoragePath, FileFormat, ShotTime, Width, Height, Data, PicDataSize, PicDataMd5, status, ininame) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",kkdata.MotorVehicleID.c_str(), kkdata.InfoKind.c_str(), kkdata.SourceID.c_str(),kkdata.RoadNo.c_str(), kkdata.TollgateID.c_str(), kkdata.DeviceID.c_str(), kkdata.TransecID.c_str(),kkdata.InterTransectID.c_str(), kkdata.TransSectDesc.c_str(), kkdata.LaneId.c_str(),kkdata.LaneNo.c_str(), kkdata.Direction.c_str(), kkdata.LaneUploadVioID.c_str(),kkdata.LaneUploadID.c_str(), kkdata.HasPlate.c_str(), kkdata.PlateNo.c_str(),kkdata.PlateClass.c_str(), kkdata.PlateColor.c_str(), kkdata.PassTime.c_str(),kkdata.PassTimeMills.c_str(), kkdata.Speed.c_str(), kkdata.VehicleLocation.c_str(),kkdata.VehicleColor.c_str(), kkdata.VehicleErrorCode.c_str(), kkdata.VehicleErrorReason.c_str(),kkdata.RecogUsedTime.c_str(), kkdata.VehicleStructure.c_str(), kkdata.PlateNum.c_str(),kkdata.ViolateType.c_str(), kkdata.ViolateTypeGA.c_str(), kkdata.LeftTopX.c_str(),kkdata.LeftTopY.c_str(), kkdata.RightBtmX.c_str(), kkdata.RightBtmY.c_str(),kkdata.PlateNoLeftTopX.c_str(), kkdata.PlateNoLeftTopY.c_str(), kkdata.PlateNoRightBtmX.c_str(),kkdata.PlateNoRightBtmY.c_str(), kkdata.VehicleBrand.c_str(), kkdata.VehicleBrandSeries.c_str(),kkdata.VehicleBrandModel.c_str(), kkdata.VehSizeType.c_str(), kkdata.VehicleClass.c_str(),kkdata.LimitSpeed.c_str(), kkdata.RedTime.c_str(), kkdata.PassTime1.c_str(),kkdata.IfResend.c_str(), kkdata.ImageCount.c_str(), kkdata.ViolateVideoNum.c_str(),kkdata.ViolateVideoType.c_str(), kkdata.ViolateVideoPath.c_str(), kkdata.ImageID.c_str(),kkdata.EventSort.c_str(), kkdata.StoragePath.c_str(), kkdata.FileFormat.c_str(),kkdata.ShotTime.c_str(), kkdata.Width.c_str(), kkdata.Height.c_str(), kkdata.Data.c_str(),kkdata.PicDataSize.c_str(), kkdata.PicDataMd5.c_str(), "0", ini_name.at(i).c_str());
                
            int result = sqlite3_exec(db,rt,NULL,NULL,&zErrMsg);
            if (result == SQLITE_OK){
            LOG4CPLUS_INFO(readkk_log,"数据进表 : " + kkdata.PlateNo);
            }else{
				LOG4CPLUS_INFO(readkk_log,"数据没有进表 : " + kkdata.PlateNo);
				LOG4CPLUS_INFO(readkk_log,"错误代码 : " + to_string(result));
			}
        }
        sqlite3_free_table(azResult);
    }
    return 0;
}
