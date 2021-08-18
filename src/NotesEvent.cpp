#include "GlobalVariable.h"

int ReadNotes(string &plain, bool &HasPermission,GroupMessage &m)
{
    if (plain.length() < 6){
        return 0;
    }
    string OrderedNote = plain.substr(6);
    if (plain.substr(0,6) == ".notes")
    {
        if (plain.length() <= 6)
        {
            // 查看Notes列表
            m.Reply(MessageChain().Plain("此功能尚未开放(∠・ω< )⌒★ Function: 3"));
            return 0;
        }
        // 查看具体的Note
        m.Reply(MessageChain().Plain("此功能尚未开放(∠・ω< )⌒★ Function: 1"));
        return 0;
    }
    return 0;
}

int SaveNotes(string &plain, bool &HasPermission, GroupMessage &m)
{
    if (plain.length() < 5){
        return 0;
    }
    if (plain.substr(0,5) == ".save")
    {
        // 保存Notes
        m.Reply(MessageChain().Plain("此功能尚未开放(∠・ω< )⌒★ Function: 2"));
        return 0;
    }
    return 0;
}
/*
void ReadNotes(Cyan::GID_t &GroupNum, string OrderedNote, GroupMessage &m)
{
    int GroupNumTemp = (int64_t)GroupNum;
    string ReadLocation = "./notes/" + to_string(GroupNumTemp) + "_Sequence.txt";
    ifstream inputnum;
    inputnum.open(ReadLocation);
    string note[10];
    int target = 11;

    for (int i = 0; i < 10; i ++)
    {
        inputnum >> note[i];
        if (OrderedNote == note[i])
        {
            target = i;
        }
    }
    inputnum.close();

    if (target == 11){
        m.Reply(MessageChain().Plain(Celestial_Notes_Not_Found));
        return;
    }

    ReadLocation = "./notes/" + to_string(GroupNumTemp) + ".txt";
    inputnum.open(ReadLocation);
    
    inputnum.close();
}

void SaveNotes(Cyan::GID_t &GroupNum, string OrderedNote)
{




}

void DeleteNotes(Cyan::GID_t &GroupNum, string OrderedNote)
{


}
*/