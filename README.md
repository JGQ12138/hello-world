项目名称：71路卡口和违法数据上传

目录结构说明：
docs: 项目工程文档
source: 项目代码
release: 项目二进制发行版本

编译说明：
1、所需库：jsoncpp，log4cplus，inifile，curl，openssl，sqlite3
2、将所需库和头文件放置packages下面的想应目录
3、创建build目录，进入目录执行cmake ..
4、执行make
5、编译后的二进制文件在code下面
