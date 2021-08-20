#include "GlobalVariable.h"
#include "HelpList.h"
#include "MiscEvent.cpp"

void HelpMsg(string &plain, Message &m)
{
    if (plain.length() < 5)
    {
        return;
    }

    if (plain.substr(0,5) == ".help" && plain.length() <= 6)
    {
        m.Reply(MessageChain().Plain(Celestial_Help_General));
        return;
    }

    if (plain.substr(0,5) == ".help" && plain.length() > 6)
    {
        string RequestedContent = plain.substr(6);
        DeletePlainSpace(RequestedContent);
        for (int i = 0; i < Celestial_Help_Total_Count; i ++)
        {
            if (Celestial_Help_Name_All[i] == RequestedContent)
            {
                m.Reply(MessageChain().Plain(Celestial_Help_Content[i]));
                return;
            }
        }
        m.Reply(MessageChain().Plain(Celestial_Help_Content_Not_Found));
        return;
    }
    return;
}