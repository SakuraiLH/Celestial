#include "GlobalVariable.h"

map<GID_t, bool> groups;

void AntiRecall(string plain, bool HasPermission, GroupMessage m)
{
    if (plain == ".norecall")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
            return;
        }
        if (groups[m.Sender.Group.GID] == true)
        {
            groups[m.Sender.Group.GID] = false;
            m.Reply(MessageChain().Plain(Celestial_Anti_Recall_Disabled));
        }
        else
        {
            groups[m.Sender.Group.GID] = true;
            m.Reply(MessageChain().Plain(Celestial_Anti_Recall_Enabled));
        }
        return;
    }
}

void ReviveRecall(GroupRecallEvent e)
{
    if (!groups[e.Group.GID]) return;
    auto recalled_mc = bot.GetGroupMessageFromId(e.MessageId).MessageChain;
    auto mc = Celestial_Anti_Recall_Desc + recalled_mc;
    bot.SendMessage(e.Group.GID, mc);
}