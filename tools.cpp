#include "tools.h"

std::vector<std::string> Tools::Ininame(std::string inipath){
    std::vector<std::string> named;
    struct timeval tv;
    char date[64];
    char pathname[128];
    gettimeofday(&tv, NULL);
    strftime(date, sizeof(date)-1, "/%Y%m%d/%H", localtime(&tv.tv_sec));

    sprintf(pathname,"%s%s",inipath.c_str(),date);

    //cout << pathname << endl;
    DIR* path;
    path=opendir(pathname);

    if(path==NULL)
    {
        //perror("error");//输出卡口没有数据的同时输出错误原因
        //log log;
        //log.writeLog("找不见ini文件");
    }
    else
    {
        struct dirent* ptr; //目录结构体---属性：目录类型 d_type,  目录名称d_name
        char buf[1024];
        while((ptr=readdir(path))!=NULL)
        {
            if(ptr->d_type==DT_REG)
            {
                if(strstr(ptr->d_name,".ini")!= NULL){
                    sprintf(buf,"%s/%s",pathname,ptr->d_name);//把pathname和文件名拼接后放进缓冲字符数组
                    named.push_back(buf);
                    //cout << "file name is " << buf << endl;
                }
            }
        }
    }
    return named;
}

std::string Tools::motorvehicleid() {
	static int abc = 0;
	time_t t = time(0);
    char MotorVehicleID[128];
    char date[64];
    strftime(date, sizeof(date), "%Y%m%d%H%M%S", localtime(&t));
    int tick = (int) (std::clock() * 1000 / CLOCKS_PER_SEC);
    char strTtimeDump[32];
    sprintf(strTtimeDump,"%.3d",tick);
	char adc_string[32];
	sprintf(adc_string,"%.2d",abc);
    sprintf(MotorVehicleID, "%s%s%s%s%s%s", "3101920000121000010002", date, "00001", "02", strTtimeDump, adc_string);
	abc++;
	if(abc>9)
	{
		abc = 0;
	}
    return MotorVehicleID;
}

//0-人工采集；1-自动采集 
std::string Tools::infokind(){
    return "1";
}

std::string Tools::sourceid(time_t t){
    char sourceid[128];

    char date[64];

    strftime(date, sizeof(date), "%Y%m%d%H%M%S", localtime(&t));
    //int tick = (int) (std::clock() * 1000 / CLOCKS_PER_SEC);
    sprintf(sourceid, "%s%s%s", "3101920000121000010002", date, "00001");
    return sourceid;
}

std::string Tools::tollgateid(std::string roadno){
    std::string tollgateid = "310192000512100" + roadno;
    return tollgateid;
}

std::string Tools::deviceid(){
    return "31019200051210000100";
}


std::string Tools::transecid(){
    return "31019200051210000100";
}

std::string Tools::intertransectID(std::string id){
    return id;
}

std::string Tools::Transsectdesc(std::string Location,std::string Direction){
    std::string Transsectdesc;

    if (Direction.empty())
    {
        Transsectdesc = Location;
    }else
    {
        std::string date = Location + "(" + Direction + ")";
        Transsectdesc = date;
    } 

    return Transsectdesc;
}

std::string Tools::laneid(){
    return "1";
}

std::string Tools::laneno(){
    return "1";
}

std::string Tools::direction(std::string str){
    std::string info =  str;
    if (str == "西向东")
    {
        return "1";
    }else if (str == "东向西")
    {
        return "2";
    }else if (str == "北向南")
    {
        return "3";
    }else if (str == "南向北")
    {
        return "4";
    }else if (str == "西南到东北")
    {
        return "5";
    }else if (str == "东北到西南")
    {
        return "6";
    }else if (str == "西北到东南")
    {
        return "7";
    }else if (str == "东南到西北")
    {
        return "8";
    }else if (str == "其他")
    {
        return "9";
    }else if (str.empty())
    {
        return "9";
    }
    return "9";
};

std::string Tools::laneuploadvioid(){
    return "314300000000094769";
}

std::string Tools::laneuploadid(){
    return "314300000000094769";
}

std::string Tools::hasplate(){
    return "true";
}

std::string Tools::plateclass(std::string str){
    if(str == "大型汽车号牌")
        return "01";
    if(str == "小型汽车号牌")
        return "02";
    if(str == "使馆汽车号牌")
        return "03";
    if(str == "领馆汽车号牌")
        return "04";
    if(str == "境外汽车号牌")
        return "05";
    if(str == "外籍汽车号牌")
        return "06";
    if(str == "普通摩托车号牌")
        return "07";
    if(str == "轻便摩托车号牌")
        return "08";
    if(str == "使馆摩托车号牌")
        return "09";
    if(str == "领馆摩托车号牌")
        return "10";
    if(str == "境外摩托车号牌")
        return "11";
    if(str == "外籍摩托车号牌")
        return "12";
    if(str == "低速车号牌")
        return "13";
    if(str == "拖拉机号牌")
        return "14";
    if(str == "挂车号牌")
        return "15";
    if(str == "教练汽车号牌")
        return "16";
    if(str == "教练摩托车号牌")
        return "17";
    if(str == "临时入境汽车号牌")
        return "20";
    if(str == "临时入境摩托车号牌")
        return "21";
    if(str == "临时行驶车号牌")
        return "22";
    if(str == "警用汽车号牌")
        return "23";
    if(str == "警用摩托车号牌")
        return "24";
    if(str == "原农机号牌")
        return "25";
    if(str == "香港入出境号牌")
        return "26";
    if(str == "澳门入出境号牌")
        return "27";
    if(str == "武警号牌")
        return "31";
    if(str == "军队号牌")
        return "32";
    if(str == "无号牌")
        return "41";
    if(str == "假号牌")
        return "42";
    if(str == "挪用号牌")
        return "43";
    if(str == "无法识别")
        return "44";
    if(str == "大型新能源汽车(左侧黄色右侧绿色双拼色底黑字)")
        return "51";
    if(str == "小型新能源汽车(渐变绿底黑字)")
        return "52";
    if(str == "其他号牌")
        return "99";
    return "99";
}

std::string Tools::color(std::string color){

    return color;
}

std::string Tools::passTime(std::string ecdtime){
    char data[64];
    strcpy(data,ecdtime.c_str());
    data[14] = '\0';
    return data;
}

std::string Tools::passtimemills(){
    struct timeb tb;

    ftime(&tb);
    int mill = tb.millitm;
    switch (std::to_string(mill).size())
    {
        case 1:{
            std::string one = "00" + std::to_string(mill);
            return one;
            break;
        }
        case 2:{
            std::string two = "0" + std::to_string(mill);
            return two;
            break;
        }
        case 3:
            return std::to_string(mill);
        default:
            break;
    }
    return "999";
}

std::string Tools::speed(){
    return "255";
}

std::string Tools::vehiclelocation(std::string location){
    //char car[4];
    //strcpy(car,location.c_str());
    //car[4] = '\0';
    //for (int i = 0; i < 4; ++i) {
    //    car[i]=location[i];
    //}
	return "999";
}

std::string Tools::vehicleerrorcode(){
    return "0";
}

std::string Tools::recogusedtime(){
    return "65535";
}

std::string Tools::vehiclestructure(){
    return "5";
}

std::string Tools::platenum(){
    return "1";
}

std::string Tools::violatetype(std::string type){
    if(type == "kk"){
        return "0";
    }else {
        return type;
    }
    return "";
}

std::string Tools::violatetypega(std::string type) {
    if(type == "kk"){
        return "0";
    } else if (type == "wf"){
        return "0";
    }
    return "";
}

std::string Tools::leftx(){
    return "99999";
}

std::string Tools::lefty(){
    return "99999";
}

std::string Tools::rightx(){
    return "99999";
}

std::string Tools::righty(){
    return "99999";
}

std::string Tools::PlateNoleftx(){
    return "99999";
}

std::string Tools::PlateNolefty(){
    return "99999";
}

std::string Tools::PlateNorightx(){
    return "99999";
}

std::string Tools::PlateNorighty(){
    return "99999";
}

std::string Tools::vehiclebrand(){
    return "0";
}

std::string Tools::vehiclebrandseries(){
    return "0";
}

std::string Tools::vehiclebrandmodel(){
    return "0";
}

std::string Tools::vehsizetype(std::string size){
    if(size == "小型车"){
        return "1";
    }
    if(size == "中型车"){
        return "2";
    }
    if(size == "大型车"){
        return "3";
    }
    if(size == "其他"){
        return "4";
    }
    return "9";
}

std::string Tools::vehicleclass(){
    return "X99";
}

std::string Tools::limitspeed(){
    return "0";
}

std::string Tools::redtime(){
    return "0";
}

//0-实时数据;1-历史补传数据
std::string Tools::ifresend(){
    return "0";
}

std::string Tools::imagecount(std::string type){
    if(type == "kk"){
        return "1";
    } else if (type == "wf"){
        return  "2";
    }
    return "";
}

std::string Tools::eventsort(){
    return "12";
}

std::string Tools::storagepath(std::string type,std::string pic,std::string ip){
    if(type == "kk"){
        std::string path = "http://" + ip + "/kk" + pic;
        return path;
    }else if (type == "wf"){
        std::string path = "http://" + ip + "/wf" + pic;
        return path;
    }
    return "";
}

std::size_t getUrlResponse(void *buffer, size_t size, size_t count, void *response)
{
    std::string *str = (std::string*)response;
    (*str).append((char*)buffer, size*count);

    return size * count;
}

std::string Tools::results(Json::Value data,std::string RodNo,std::string url){
    std::string jsonout = data.toStyledString();

    std::string res_str;

    char Time[128];
    struct timeval tv;
    char date[64];
    gettimeofday(&tv, NULL);
    strftime(date, sizeof(date) - 1, "%Y%m%d%H%M%S", localtime(&tv.tv_sec));
    int tick = (int)(std::clock()*1000/CLOCKS_PER_SEC);
    sprintf(Time,"%s%s%d","User-SendTime: ",date,tick);

    char user[64];
    sprintf(user,"%s%s","User-Identify: ",RodNo.c_str());
    CURL *curl;
    //CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//"http://15.32.199.112:9091/VIID/MotorVehicles"
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        // 注册回调函数 获取信息
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &getUrlResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_str);


        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/*+json");
        headers = curl_slist_append(headers, user);//"User-Identify: 01091"
        headers = curl_slist_append(headers, Time);//"User-SendTime: 20210207093923123"
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonout.c_str());
        //res = 
        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    return res_str;
}

std::string Tools::code_convert(char const *source_charset, char const *to_charset, const std::string& sourceStr) //sourceStr是源编码字符串
{
    iconv_t cd = iconv_open(to_charset, source_charset);//获取转换句柄，void*类型
    if (cd == 0)
        return "";

    size_t inlen = sourceStr.size();
    size_t outlen = 255;
    char* inbuf = (char*)sourceStr.c_str();
    char outbuf[255];
    memset(outbuf, 0, outlen);

    char *poutbuf = outbuf; //多加这个转换是为了避免iconv这个函数出现char(*)[255]类型的实参与char**类型的形参不兼容
    if ((int)iconv(cd, &inbuf, &inlen, &poutbuf, &outlen) == -1)
        return "";

    std::string strTemp(outbuf);//此时的strTemp为转换编码之后的字符串
    iconv_close(cd);
    return strTemp;
}

std::string Tools::GbkToUtf8(const std::string& strGbk)// 传入的strGbk是GBK编码
{
    return code_convert("gb2312", "utf-8", strGbk);
}