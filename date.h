#pragma once

#include <string>

using namespace std;

class Data {
public:
    //车辆标识
    string MotorVehicleID;
    //信息分类
    string InfoKind;
    //来源标识
    string SourceID;
    //路口号
    string RoadNo;
    //电子警察主机设备编号
    string TollgateID;
    //关联的摄像机编号
    string DeviceID;
    //摄像机断面编码
    string TransecID;
    //内部断面代码
    string InterTransectID;
    //断面描述
    string TransSectDesc;
    //车道 ID
    string LaneId;
    //车道编号
    string LaneNo;
    //行驶方向
    string Direction;
    //路口
    string Location;
    //车道对应的 18 位公安网违法设备代码
    string LaneUploadVioID;
    //车道对应的 18 位公安网卡口设备代码
    string LaneUploadID;
    //有无车牌
    string HasPlate;
    //车牌号
    string PlateNo;
    //号牌种类
    string PlateClass;
    //车牌颜色
    string PlateColor;
    //经过时刻
    string PassTime;
    //经过时刻毫秒
    string PassTimeMills;
    //行驶速度
    string Speed;
    //车辆属地
    string VehicleLocation;
    //车身颜色
    string VehicleColor;
    //出错码
    string VehicleErrorCode;
    //出错原因
    string VehicleErrorReason;
    //识别时间
    string RecogUsedTime;
    //号牌结构
    string VehicleStructure;
    //号牌数量
    string PlateNum;
    //违法类型
    string ViolateType;
    //违法类型所对应的违法代码
    string ViolateTypeGA;
    //左上角 X 坐 标
    string LeftTopX;
    //左上角 Y 坐 标
    string LeftTopY;
    //右下角 X 坐标
    string RightBtmX;
    //右下角 Y 坐标
    string RightBtmY;
    //车牌号码左上角 X 坐标
    string PlateNoLeftTopX;
    //车牌号码左上角 Y 坐标
    string PlateNoLeftTopY;
    //车牌号码右下角 X 坐标
    string PlateNoRightBtmX;
    //车牌号码右下角 Y 坐标
    string PlateNoRightBtmY;
    //车辆品牌代码
    string VehicleBrand;
    //车辆品牌车系代码
    string VehicleBrandSeries;
    //品牌车型代码
    string VehicleBrandModel;
    //车型大小
    string VehSizeType;
    //车辆类型
    string VehicleClass;
    //限速
    string LimitSpeed;
    //红灯时间
    string RedTime;
    //经过时间 1
    string PassTime1;
    //是否补传
    string IfResend;
    //图片对象个数
    string ImageCount;
    //子图像列表
    string SubImageList;
    //违法短视频数量,无视频填 0;
    string ViolateVideoNum;
    //违法短视频文件类型
    string ViolateVideoType;
    //违法短视频文件的地址
    string ViolateVideoPath;
    //近景照片
    string StorageUrl1;
    //车牌照片
    string StorageUrl2;
    //远景照片
    string StorageUrl3;
    //合成图
    string StorageUrl4;
    //缩略图
    string StorageUrl5;
    //位置标记时间
    string MarkTime;
    //车辆出现时间
    string AppearTime;
    //车辆消失时间
    string DisappearTime;
    //挂车牌号
    string PlateNoAttach;
    //车牌描述
    string PlateDescribe;
    //是否套牌
    string IsDecked;
    //是否涂改
    string IsAltered;
    //是否遮挡
    string IsCovered;
    //行驶状态代码
    string DrivingStatusCode;
    //机动车使用性质代码
    string UsingPropertiesCode;
    //车辆型号
    string VehicleModel;
    //车辆年款
    string VehicleStyles;
    //车辆长度
    string VehicleLength;
    //车辆宽度
    string VehicleWidth;
    //车辆高度
    string VehicleHeight;
    //颜色深浅
    string VehicleColorDepth;
    //车前盖
    string VehicleHood;
    //车后盖
    string VehicleTrunk;
    //车轮
    string VehicleWheel;
    //车轮印花纹
    string WheelPrintedPattern;
    //车窗
    string VehicleWindow;
    //车顶
    string VehicleRoof;
    //车门
    string VehicleDoor;
    //车侧
    string SideOfVehicle;
    //车厢
    string CarOfVehicle;
    //后视镜
    string RearviewMirror;
    //底盘
    string VehicleChassis;
    //遮挡
    string VehicleShielding;
    //贴膜颜色
    string FilmColor;
    //改装标志
    string IsModified;
    //撞痕信息
    string HitMarkInfo;
    //车身描述
    string VehicleBodyDesc;
    //车前部物品
    string VehicleFrontItem;
    //车前部物品描述
    string DescOfFrontItem;
    //车后部物品
    string VehicleRearItem;
    //车后部物品描述
    string DescOfRearItem;
    //车内人数
    string NumOfPassenger;
    //经过道路
    string NameOfPassedRoad;
    //是否可疑车
    string IsSuspicious;
    //遮阳板状态
    string Sunvisor;
    //安全带状态
    string SafetyBelt;
    //打电话状态
    string Calling;
    //号牌识别可信度
    string PlateReliability;
    //每位号牌号码可信度
    string PlateCharReliability;
    //品牌标志识别可信度
    string BrandReliability;

    //子图像列表对象

    //图像标识
    string ImageID;
    //事件分类
    string EventSort;
    //摄像机设备编号
    //string DeviceID;
    //存储路径
    string StoragePath;

    string StoragePath1;
    //图像类型
    string Type;
    //图像文件格式
    string FileFormat;
    //拍摄时间
    string ShotTime;
    //宽度
    string Width;
    //高度
    string Height;
    //图片数据
    string Data;
    
    string Data1;
    //图片的文件大小
    string PicDataSize;
    //图片数据的十六进制表示的图片 MD5 值
    string PicDataMd5;

    string PicDataMd51;
};