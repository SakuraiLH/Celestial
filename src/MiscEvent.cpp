#include "GlobalVariable.h"
#include "VersionGenerator.h"

void FriendIntroduction(NewFriendRequestEvent &f)
{
    f.Accept();
    MiraiBot::SleepSeconds(2);
    bot.SendMessage(f.FromId, MessageChain().Plain(Celestial_Private_Version + '\n' + Celestial_Welcome_Message));
    return;
}

void GroupIntroduction(BotInvitedJoinGroupRequestEvent &n)
{
    n.Accept();
    MiraiBot::SleepSeconds(2);
    bot.SendMessage(n.GroupId, MessageChain().Plain(Celestial_Private_Version + '\n' + Celestial_Welcome_Message));
    return;
}

void LeaveGroup(string &plain, bool HasPermission, GroupMessage &m)
{
    if (plain.substr(0,6) == ".leave")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
            return;
        }
        m.Reply(MessageChain().Plain(Celestial_Goodbye));
        bot.QuitGroup(m.Sender.Group.GID);
        return;
    }
}