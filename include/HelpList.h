#pragma once
#include "GlobalVariable.h"
#include "VersionGenerator.h"

string Celestial_Help_General = Celestial_Private_Version + '\n'
                                + "使用 .help list 来查看全部指令" + '\n'
                                + "使用 .help link 来查看源码链接" + '\n'
                                + "使用 .bot 来查看Celestial版本" + '\n'
                                + "开源万岁！";

int Celestial_Help_Total_Count = 2;

string Celestial_Help_Name_All[2] = {
                                "list","link"
};

const string Celestial_Help_Content_List = "本帮助信息代指Celestial版本"
                                        + Celestial_Short_Version
                                        + "的帮助信息。" + '\n'
                                        + "以下信息的大括号代表引用参数，" + '\n'
                                        + "实际调用不需要大括号。" + '\n'
                                        + "带有*的命令表示需要通过回复方式来指定对象" + '\n'
                                        + "同样的，实际调用依然不需要加*" + '\n'
                                        + "帮助列表:" + '\n'
                                        + ".ban* 踢出某人" + '\n'
                                        + ".bot 查看Celestial信息" + '\n'
                                        + ".delete {目标笔记} 删除储存的特定笔记" + '\n'
                                        + ".help 查看帮助信息" + '\n'
                                        + ".kick* 踢出某人" + '\n'
                                        + ".leave 使该Celestial实例离开群组" + '\n'
                                        + ".mute* {时长} 禁言某人" + '\n'
                                        + ".notes* {目标笔记,可选}" + '\n'
                                        + "不添加目标笔记参数则显示笔记列表。" + '\n'
                                        + ".norecall 开启/关闭防撤回" + '\n'
                                        + ".save* {标题} 保存笔记" + '\n'
                                        + ".whoami 查看发送者的调用权限";

const string Celestial_Help_Content_License   = "Celestial Robot 根据 AGPL v3 开源。";
const string Celestial_Project_Address        = "https://github.com/SakuraiLH/Celestial";
const string Celestial_Author_Address         = "https://github.com/SakuraiLH";
const string Celestial_Help_Content_Link      = Celestial_Help_Content_License + '\n'
                                              + "Copyright <C> 2021 SakuraiLH, Celestial" + '\n'
                                              + "All rights reserved." + '\n'
                                              + "Address : " + Celestial_Project_Address + '\n'
                                              + "Author : " + Celestial_Author_Address;

string Celestial_Help_Content[2] = {
                                Celestial_Help_Content_List, Celestial_Help_Content_Link
};
