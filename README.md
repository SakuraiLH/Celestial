<div align="center">
   <img width="160" src="https://github.com/mamoe/mirai/blob/dev/docs/mirai.png" alt="logo"></br>
   <img width="95" src="https://github.com/mamoe/mirai/blob/dev/docs/mirai.svg" alt="title">

<br>

Mirai 是一个在全平台下运行，提供 QQ Android 和 TIM PC 协议支持的高效率机器人框架

这个项目的名字来源于
     <p><a href = "http://www.kyotoanimation.co.jp/">京都动画</a>作品<a href = "https://zh.moegirl.org/zh-hans/%E5%A2%83%E7%95%8C%E7%9A%84%E5%BD%BC%E6%96%B9">《境界的彼方》</a>的<a href = "https://zh.moegirl.org/zh-hans/%E6%A0%97%E5%B1%B1%E6%9C%AA%E6%9D%A5">栗山未来(Kuriyama <b>Mirai</b>)</a></p>
     <p><a href = "https://www.crypton.co.jp/">CRYPTON</a>以<a href = "https://www.crypton.co.jp/miku_eng">初音未来</a>为代表的创作与活动<a href = "https://magicalmirai.com/2019/index_en.html">(Magical <b>Mirai</b>)</a></p>
图标以及形象由画师<a href = "">DazeCake</a>绘制
</div>

# Celestial
Mirai multi-function bot plugin

<b>Mirai 多功能 机器人群管插件</b>

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/be68e2bcf2b44567a9d3cb7413a05252)](https://www.codacy.com/gh/SakuraiLH/Celestial/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=SakuraiLH/Celestial&amp;utm_campaign=Badge_Grade)
![License: AGPL v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)

## 安装 Celestial

### 0x01 编译 Celestial

```sh
git clone https://github.com/SakuraiLH/Celestial ~/Celestial
cd ~/Celestial
git submodule update --init --remote --force
```

在这一步之后，你需要调整Celestial的机器人设置。

导航到`src/main.cpp`，找到

```c++
int main()
{
	opts.BotQQ = xxxxx_qq;
	opts.HttpHostname = "localhost";
	opts.WebSocketHostname = "localhost";
	opts.HttpPort = 8080;
	opts.WebSocketPort = 8080;
	opts.VerifyKey = "123";
	bool anti_recall = false;
}
```

将opts的QQ号改为目标机器人的QQ号，`HttpHostname/Port`和`WebSocketHostname/Port`请根据自己的需要更改。在`VerifyKey`处输入自定义的一个密码，稍后在`mirai-api-http`中将会用到。

```sh
mkdir build
cd ./build
cmake ..
make
```

命令结束后，在build目录下得到可执行文件`Celestial`。

### 0x02 使用 Mirai-Console-Loader 来安装 Mirai

```sh
mkdir ~/Mirai
cd ~/Mirai
wget https://github.com/iTXTech/mcl-installer/releases/download/v1.0.3/mcl-installer-1.0.3-linux-amd64
chmod a+x mcl-installer-1.0.3-linux-amd64
./mcl-installer-1.0.3-linux-amd64
```

请注意:如果自带Java环境,MCL Installer中的下载java步骤可以跳过。

### 0x03 下载 mirai-api-http 到 plugins 中

```sh
cd ~/Mirai
mkdir plugins
wget -P ./plugins https://github.com/project-mirai/mirai-api-http/releases/download/v2.2.0/mirai-api-http-v2.2.0.mirai.jar
```

### 0x04 对 mirai-api-http 进行初始化设置

第一次启动后，可使用`stop`退出后进入`~/Mirai/config/net.mamoe.mirai-api-http`，找到`config.yaml`，启用WebSocket的adapter。

```yaml
adapters:
  - http
  - ws
debug: false
enableVerify: true
verifyKey: 123 # 这里填写之前你设定的密码
singleMode: false
cacheSize: 4096
adapterSettings:
  http:
    host: localhost
    port: 8080
    cors: [*]

  ws:
    host: localhost
    port: 8080
    reservedSyncId: -1
```

你的`config.yaml`应该是这样设置的。设置详见[mirai-api-http的文档](https://github.com/project-mirai/mirai-api-http#adapter)。

### 0x05 启动机器人

执行在 0x01中所得到的二进制文件。

在`~/Mirai`下，使用`./mcl `启动机器人。使用`login QQ号 QQ密码`登陆Mirai。

### 0x06 自定义部分

Celestial的回复内容都集中在一个统一的头文件`include/CustomReplies.h`中。
你可以在`CustomReplies.h`中修改回复内容。

某些Celestial指令包含有针对单一实例的QQ账户前四位认证，关于特定实例选定这部分
的更改Celestial将不会自动变更。你可以在`include/Globalvariables.h`中找到字符串变量
`Celestial_QQ_Prefix`，推荐修改。

### 0x07 法律信息

Copyright <C> 2021 SakuraiLH, Celestial.<br>
All rights reserved.

通过AGPL v3协议开源。
