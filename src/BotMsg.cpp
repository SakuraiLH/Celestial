#include "GlobalVariable.h"
#include "VersionGenerator.h"

void botcall(string &plain, GroupMessage &m, string Celestial_QQ_Prefix)
{				
    string bot_des = "";
    bool isSpecified = false;
    if (plain.length() > 4 && plain.substr(0,4) == ".bot")
    {
        bot_des = plain.substr(5);
        isSpecified = true;
    }
    if (plain.substr(0,4) == ".bot" && isSpecified == false)
	{
		m.Reply(MessageChain().Plain(Celestial_Version + '\n' + Celestial_Bot_Msg));
		return;
	}
				
	if (plain.substr(0,4) == ".bot" && isSpecified == true)
	{
	    if (bot_des == Celestial_QQ_Prefix) {
		    m.Reply(MessageChain().Plain(Celestial_Version + '\n' + Celestial_Bot_Msg));
		}
		return;
    }
}