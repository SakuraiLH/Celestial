#include "GlobalVariable.h"

map<GID_t, bool> groups;

void AntiRecall(string plain, bool HasPermission, GroupMessage m)
{
    // 指定反撤回功能的開啓
    if (plain == ".norecall enable")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        groups[m.Sender.Group.GID] = true;
        m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被開啓."));
        return;
    }

    // 指定反撤回功能的關閉
    if (plain == ".norecall disable")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        groups[m.Sender.Group.GID] = false;
        m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被關閉."));
        return;
    }

    // 沒有指定
    if (plain == ".norecall")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        if (groups[m.Sender.Group.GID] == true)
        {
            groups[m.Sender.Group.GID] = false;
            m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被關閉."));
        }
        else
        {
            groups[m.Sender.Group.GID] = true;
            m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被開啓."));
        }
        return;
    }
}

void ReviveRecall(GroupRecallEvent e)
{
    if (!groups[e.Group.GID]) return;
    auto recalled_mc = bot.GetGroupMessageFromId(e.MessageId).MessageChain;
    auto mc = "Celestial > 撤回內容如下: " + recalled_mc;
    bot.SendMessage(e.Group.GID, mc);
}