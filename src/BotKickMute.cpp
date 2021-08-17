#include "GlobalVariable.h"

// 踢出功能
void kick(string plain, bool HasPermission, GroupMessage m)
{
    string msg = m.MessageChain.ToString();
    vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
    m.MessageChain.ToVector();
    // 指定了目標
    if (plain.substr(0,4) == ".ban" && msg.length() > 32)
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        if (qm.size() > 0)
        {
            QQ_t sendqq;
            string target = "";
            for (size_t i = 0; i < qm.size(); i ++) {
                int msgid = qm.at(i).MessageId();
                sendqq = bot.GetGroupMessageFromId(msgid).Sender.QQ;
            }

            bot.Kick(m.Sender.Group.GID, sendqq, "Kicked By ☆Celestial");

        }
        m.Reply(MessageChain().Plain("Celestial > 操作成功執行。"));
        return;
    }

    // 沒有指定目標
    if (plain.substr(0,4) == ".ban" && msg.length() <= 32)
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        m.Reply(MessageChain().Plain("Celestial > 請指定踢出目標!"));
        return;
    }
}

// ===== ===== ===== ===== ===== ===== =====

void mute(string plain, bool HasPermission, GroupMessage m)
{
    string msg = m.MessageChain.ToString();
    vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
    m.MessageChain.ToVector();
    // 禁言功能
    if (plain.substr(0,5) == ".mute")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        if(qm.size() > 0)
        {
            cout << "Pass" << endl;
            QQ_t targetnum;
            string target = "";
            cout << m.Sender.Group.GID << endl; 
            for (size_t i = 0; i < qm.size(); i ++) {
                int msgid = qm.at(i).MessageId();
                targetnum = bot.GetGroupMessageFromId(msgid).Sender.QQ;
            }
            cout << "Pass" << endl;
            int mute_time = 2505600;
            cout << "Mute:" << m.Sender.Group.GID << " " << targetnum << " " << mute_time << endl;
            bot.Mute(m.Sender.Group.GID, targetnum, mute_time);

        }
        m.Reply(MessageChain().Plain("Celestial > 操作成功執行。"));
        return;
    }

    // 解除禁言功能
    if (plain.substr(0,7) == ".unmute")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain("Celestial > 欸 欸 (′～`;) 你不是管理呢, Celestial 不認識你啊"));
            return;
        }
        if(qm.size() > 0)
        {
            QQ_t targetnum;
            string target = "";
            for (size_t i = 0; i < qm.size(); i ++) {
                int msgid = qm.at(i).MessageId();
                targetnum = bot.GetGroupMessageFromId(msgid).Sender.QQ;
            }
            int mute_time = 30*60;
            bot.UnMute(m.Sender.Group.GID, targetnum);
        }
        m.Reply(MessageChain().Plain("Celestial > 操作成功執行。"));
        return;
    }
}