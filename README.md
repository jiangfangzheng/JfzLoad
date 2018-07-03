# JfzLoad
Windows下运行jar的启动器(exe文件)

### 功能
exe文件引导启动jar图形界面软件。

推荐编译为32位release版，避免额外系统依赖。

### 原理
编译后生成一个exe文件，exe用于执行与它同目录同文件名的jar文件。启动器优先找系统环境变量javaw(Java图形界面)，如果没有，使用当前目录下lib文件夹里放的JDK。

假设本启动器文件名为JfzLoad.exe，程序执行的语句如下：

**javaw -jar JfzLoad.jar**

如果环境变量中没有javaw，则执行：

**./lib/bin/javaw.exe -jar JfzLoad.jar**

### 更新日志

#### 2018年06月17日 v1.0
* 修改找Java库的顺序

#### 2018年05月14日 v1.0
* 核心功能完成