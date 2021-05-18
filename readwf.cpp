#include "readwf.h"

int Readwf::Read_ini(std::string ini_path, std::string roadno , std::string id, std::string ip, sqlite3* db){
    Tools tools;
    Data wfdata;
    using namespace inifile;
    IniFile Config_ini;
        
    log4cplus::Logger readwf_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));
    

    std::vector<std::string> ini_name = tools.Ininame(ini_path);
    for (size_t i = 0; i < ini_name.size(); i++)
    {
		time_t t = time(0);
		char tmp[32];
		memset(tmp,0,sizeof(tmp));
		strftime(tmp, sizeof(tmp), "%Y-%m-%d", localtime(&t));
		string wf_time = tmp;
        char* sql = sqlite3_mprintf("select ininame from wfdata where ininame = '%s';",ini_name.at(i).c_str());

        int ret =  sqlite3_get_table( db , sql , &azResult , &nrow , & ncolumn , &zErrMsg);
        if (ret == SQLITE_OK && nrow == 0)
        {
            LOG4CPLUS_INFO(readwf_log,ini_name.at(i).c_str());

            int flog = Config_ini.Load(ini_name.at(i));
            if (flog == 5)
            {
                std::cout << "打开文件失败" << std::endl;
                LOG4CPLUS_INFO(readwf_log,"卡口ini文件读取失败");
                break;
            }

            wfdata.MotorVehicleID = tools.motorvehicleid();
			LOG4CPLUS_INFO(readwf_log,"ID : " + wfdata.MotorVehicleID);
            wfdata.InfoKind = tools.infokind();
            wfdata.SourceID = tools.sourceid(t);
            wfdata.RoadNo = roadno;
            wfdata.TollgateID = tools.tollgateid(roadno);
            wfdata.DeviceID = tools.deviceid();
            wfdata.TransecID = tools.transecid();
            wfdata.InterTransectID = tools.intertransectID(id);
            LOG4CPLUS_INFO(readwf_log,"内部断面代码为 : " + wfdata.InterTransectID);
            
            std::string dir,loca;
            Config_ini.GetStringValue("RecordInfo","Direction",&dir);
            Config_ini.GetStringValue("RecordInfo","Location",&loca);
            wfdata.TransSectDesc = tools.Transsectdesc(tools.GbkToUtf8(loca),tools.GbkToUtf8(dir));
            LOG4CPLUS_INFO(readwf_log,"断面描述 : " + wfdata.TransSectDesc);

            wfdata.LaneId = tools.laneid();
            wfdata.LaneNo = tools.laneno();
            wfdata.Direction = tools.direction(tools.GbkToUtf8(dir));

            wfdata.LaneUploadVioID = tools.laneuploadvioid();
            wfdata.LaneUploadID = tools.laneuploadid();
            wfdata.HasPlate = tools.hasplate();

            std::string plateno;
            Config_ini.GetStringValue("RecordInfo", "PlateText", &plateno);
            wfdata.PlateNo = tools.GbkToUtf8(plateno);

            std::string plate;
            Config_ini.GetStringValue("RecordInfo", "PlateType",&plate);
            wfdata.PlateClass = tools.plateclass(plate);

            std::string wf_color;
            Config_ini.GetStringValue("RecordInfo", "PlateColor" , &wf_color);
            wfdata.PlateColor = tools.color(wf_color);

            std::string pass_time;
            Config_ini.GetStringValue("RecordInfo", "EndTime", &pass_time);
            wfdata.PassTime = tools.passTime(pass_time);

            wfdata.PassTimeMills = tools.passtimemills();
            wfdata.Speed = tools.speed();
            wfdata.VehicleLocation = tools.vehiclelocation(wfdata.PlateNo);
            //strcpy(wfdata.VehicleLocation,tools.vehiclelocation(wfdata.PlateNo).c_str());
            wfdata.VehicleColor = wfdata.PlateColor;
            wfdata.VehicleErrorCode = tools.vehicleerrorcode();
            wfdata.VehicleErrorReason = "0";
            wfdata.RecogUsedTime = tools.recogusedtime();
            wfdata.VehicleStructure = tools.vehiclestructure();
            wfdata.PlateNum = tools.platenum();
            std::string Type;
            Config_ini.GetStringValue("RecordInfo", "ViolationType", &Type);
            wfdata.ViolateType = tools.violatetype(Type);
            wfdata.ViolateTypeGA = tools.violatetypega("wf");
            wfdata.LeftTopX = tools.leftx();
            wfdata.LeftTopY = tools.lefty();
            wfdata.RightBtmX = tools.rightx();
            wfdata.RightBtmY = tools.righty();
            wfdata.PlateNoLeftTopX = tools.PlateNoleftx();
            wfdata.PlateNoLeftTopY = tools.PlateNolefty();
            wfdata.PlateNoRightBtmX = tools.PlateNorightx();
            wfdata.PlateNoRightBtmY = tools.PlateNorighty();
            wfdata.VehicleBrand = tools.vehiclebrand();
            wfdata.VehicleBrandSeries = tools.vehiclebrandseries();
            wfdata.VehicleBrandModel = tools.vehiclebrandmodel();

            std::string wf_sizetype;
            Config_ini.GetStringValue("RecordInfo", "VechileType", &wf_sizetype);
            wfdata.VehSizeType = tools.vehsizetype(wf_sizetype);
            wfdata.VehicleClass = tools.vehicleclass();
            wfdata.LimitSpeed = tools.limitspeed();
            wfdata.RedTime = tools.redtime();

            std::string pass_time1;
            Config_ini.GetStringValue("RecordInfo", "EndTime", &pass_time1);
            wfdata.PassTime1 = tools.passTime(pass_time1);
            wfdata.IfResend = tools.ifresend();
            wfdata.ImageCount = tools.imagecount("wf");
            wfdata.ViolateVideoNum = "0";

            wfdata.ImageID = wfdata.SourceID;
            wfdata.EventSort = tools.eventsort();

            std::string picpath1,picpath2;
            Config_ini.GetStringValue("RecordInfo", "Pic1", &picpath1);
            Config_ini.GetStringValue("RecordInfo", "Pic2", &picpath2);

            //违法图片地址http：//
            wfdata.StoragePath = tools.storagepath("wf", picpath1, ip);
            wfdata.StoragePath1 = tools.storagepath("wf", picpath2, ip);

            wfdata.Type = "35";
            wfdata.FileFormat = "jpg";
            wfdata.ShotTime = wfdata.PassTime;
            wfdata.Width = "";
            wfdata.Height = "";

            std::string pic_path1 = ini_path + picpath1;
            std::string pic_path2 = ini_path + picpath2;
            wfdata.Data = base64(pic_path1);
            //cout << "md5加密" << endl;
            wfdata.PicDataMd5 = file_md5(pic_path1);
            //cout << "第二张图片地址" << pic1 << endl;
            wfdata.Data1 = base64(pic_path2);
            //cout << "md5加密" << endl;
            wfdata.PicDataMd51 = file_md5(pic_path2);

            char *rt = sqlite3_mprintf("INSERT INTO main.wfdata (MotorVehicleID, InfoKind, SourceID, RoadNo, TollgateID, DeviceID, TransecID, InterTransectID, TransSectDesc, LaneId, LaneNo, Direction, LaneUploadVioID, LaneUploadID, HasPlate, PlateNo, PlateClass, PlateColor, PassTime, PassTimeMills, Speed, VehicleLocation, VehicleColor, VehicleErrorCode, VehicleErrorReason, RecogUsedTime, VehicleStructure, PlateNum, ViolateType, ViolateTypeGA, LeftTopX, LeftTopY, RightBtmX, RightBtmY, PlateNoLeftTopX, PlateNoLeftTopY, PlateNoRightBtmX, PlateNoRightBtmY, VehicleBrand, VehicleBrandSeries, VehicleBrandModel, VehSizeType, VehicleClass, LimitSpeed, RedTime, PassTime1, IfResend, ImageCount, ViolateVideoNum, ViolateVideoType, ViolateVideoPath, ImageID, EventSort, StoragePath, StoragePath1, FileFormat, ShotTime, Width, Height, Data, Data1, PicDataSize, PicDataMd5,PicDataMd51, status, ininame) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s' , '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s','%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",wfdata.MotorVehicleID.c_str(), wfdata.InfoKind.c_str(), wfdata.SourceID.c_str(),wfdata.RoadNo.c_str(), wfdata.TollgateID.c_str(), wfdata.DeviceID.c_str(), wfdata.TransecID.c_str(),wfdata.InterTransectID.c_str(), wfdata.TransSectDesc.c_str(), wfdata.LaneId.c_str(),wfdata.LaneNo.c_str(), wfdata.Direction.c_str(), wfdata.LaneUploadVioID.c_str(),wfdata.LaneUploadID.c_str(), wfdata.HasPlate.c_str(), wfdata.PlateNo.c_str(),wfdata.PlateClass.c_str(), wfdata.PlateColor.c_str(), wfdata.PassTime.c_str(),wfdata.PassTimeMills.c_str(), wfdata.Speed.c_str(), wfdata.VehicleLocation.c_str(),wfdata.VehicleColor.c_str(), wfdata.VehicleErrorCode.c_str(), wfdata.VehicleErrorReason.c_str(),wfdata.RecogUsedTime.c_str(), wfdata.VehicleStructure.c_str(), wfdata.PlateNum.c_str(),wfdata.ViolateType.c_str(), wfdata.ViolateTypeGA.c_str(), wfdata.LeftTopX.c_str(),wfdata.LeftTopY.c_str(), wfdata.RightBtmX.c_str(), wfdata.RightBtmY.c_str(),wfdata.PlateNoLeftTopX.c_str(), wfdata.PlateNoLeftTopY.c_str(), wfdata.PlateNoRightBtmX.c_str(),wfdata.PlateNoRightBtmY.c_str(), wfdata.VehicleBrand.c_str(), wfdata.VehicleBrandSeries.c_str(),wfdata.VehicleBrandModel.c_str(), wfdata.VehSizeType.c_str(), wfdata.VehicleClass.c_str(),wfdata.LimitSpeed.c_str(), wfdata.RedTime.c_str(), wfdata.PassTime1.c_str(),wfdata.IfResend.c_str(), wfdata.ImageCount.c_str(), wfdata.ViolateVideoNum.c_str(),wfdata.ViolateVideoType.c_str(), wfdata.ViolateVideoPath.c_str(), wfdata.ImageID.c_str(),wfdata.EventSort.c_str(), wfdata.StoragePath.c_str(), wfdata.StoragePath1.c_str(), wfdata.FileFormat.c_str(), wfdata.ShotTime.c_str(), wfdata.Width.c_str(), wfdata.Height.c_str(),wfdata.Data.c_str(), wfdata.Data1.c_str(), wfdata.PicDataSize.c_str(), wfdata.PicDataMd5.c_str(),wfdata.PicDataMd51.c_str(), "0", ini_name.at(i).c_str());

            int result = sqlite3_exec(db,rt,NULL,NULL,&zErrMsg);
            if (result == SQLITE_OK){
            LOG4CPLUS_INFO(readwf_log,"数据进表 : " + wfdata.PlateNo);
            }else{
				LOG4CPLUS_INFO(readwf_log,"数据没有进表 : " + wfdata.PlateNo);
				LOG4CPLUS_INFO(readwf_log,"错误代码 : " + to_string(result));
			}
        }
        sqlite3_free_table(azResult);
    }
    return 0;
}


std::string Readwf::file_md5(string file_name)
{
    if (access(file_name.c_str(),F_OK)==0)
    {
        MD5_CTX md5;
        unsigned char md[16];
        char tmp[33]={'\0'};
        int length,i;
        char buffer[1024];
        string hash="";
        MD5_Init(&md5);
        ifstream fin(file_name.c_str(),ios::in|ios::binary);

        while(!fin.eof())
        {
            fin.read(buffer, sizeof(buffer));
            length = fin.gcount();
            if (length > 0) {
                MD5_Update(&md5,buffer, length);
            }
        }
        MD5_Final(md,&md5);
        for(i=0; i<16; i++){
            sprintf(tmp, "%02x", md[i]);
                hash+=(string)tmp;
        }
        fin.close();
        return hash;
    }else{
        log4cplus::Logger md5_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));
        LOG4CPLUS_ERROR(md5_log,"找不到图片可以用来md5加密");
        exit(0);
    }
}

char * Readwf::Base64Encode(const char * input, int length, bool with_new_line)
{
    BIO * bmem = NULL;
    BIO * b64 = NULL;
    BUF_MEM * bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    if(!with_new_line) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char * buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

std::string Readwf::base64(std::string pic){
    if (access(pic.c_str(),F_OK)==0)
    {
        std::ifstream fin(pic.c_str(), std::ios::binary);
        fin.seekg(0, ios::end);
        int iSize = fin.tellg();
        char* szBuf = new (std::nothrow) char[iSize];

        fin.seekg(0, ios::beg);
        fin.read(szBuf, sizeof(char) * iSize);
        fin.close();
        //std::cout << "文件读取完毕开始base64转换" << endl;
        char * enc_output = Base64Encode(szBuf, iSize, false);
        //std::cout << "返回base64字符串" << endl;
        return enc_output;
    }else{
        log4cplus::Logger md5_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));
        LOG4CPLUS_ERROR(md5_log,"找不到图片可以用来base64加密");
        exit(0);
    }
    
}
