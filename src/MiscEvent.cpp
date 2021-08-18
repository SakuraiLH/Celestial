#include "GlobalVariable.h"
#include "VersionGenerator.h"

void FriendIntroduction(NewFriendRequestEvent &f)
{
    f.Accept();
    MiraiBot::SleepSeconds(2);
    bot.SendMessage(f.FromId, MessageChain().Plain(Celestial_Private_Version + '\n' + Celestial_Welcome_Message));
}

void GroupIntroduction(BotInvitedJoinGroupRequestEvent &n)
{
    n.Accept();
    MiraiBot::SleepSeconds(2);
    bot.SendMessage(n.GroupId, MessageChain().Plain(Celestial_Private_Version + '\n' + Celestial_Welcome_Message));
}