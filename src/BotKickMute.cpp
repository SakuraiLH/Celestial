#include "GlobalVariable.h"

// 踢出功能
void kick(string plain, bool HasPermission, GroupMessage m)
{
    string msg = m.MessageChain.ToString();
    vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
    m.MessageChain.ToVector();
    // 指定了目標
    if (plain.length() < 4)
    {
        return;
    }
    if (plain.substr(0,4) == ".ban" && msg.length() > 32)
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
            return;
        }
        if (qm.size() > 0)
        {
            QQ_t sendqq;
            for (size_t i = 0; i < qm.size(); i ++) {
                int msgid = qm.at(i).MessageId();
                sendqq = bot.GetGroupMessageFromId(msgid).Sender.QQ;
            }

            bot.Kick(m.Sender.Group.GID, sendqq, Celestial_Kick_Reason);

        }
        m.Reply(MessageChain().Plain(Celestial_Action_Success));
        return;
    }

    // 沒有指定目標
    if (plain.substr(0,4) == ".ban" && msg.length() <= 32)
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
            return;
        }
        m.Reply(MessageChain().Plain(Celestial_Target_Not_Specified));
        return;
    }
}

// ===== ===== ===== ===== ===== ===== =====

void mute(string plain, bool HasPermission, GroupMessage m)
{
    vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
    m.MessageChain.ToVector();
    int mute_time = 2505600;

    if (plain.length() < 5) {
        return;
    }
    
    // 判断末尾是否带有参数
    bool HasParameter = true;
    if (plain.length() <= 4) {
        HasParameter = false;
    }


    // 收集参数
    if (HasParameter)
    {
        if(plain.length() <= 5)
        {
            return;
        }
        string BackwardParameter = plain.substr(6);
        const char* p = BackwardParameter.data();
        mute_time = atoi(p) * 60;
    }

    // 禁言功能
    if (plain.substr(0,5) == ".mute")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
            return;
        }
        if(qm.size() > 0)
        {
            QQ_t targetnum;
            cout << m.Sender.Group.GID << endl; 
            for (size_t i = 0; i < qm.size(); i ++) {
                int msgid = qm.at(i).MessageId();
                targetnum = bot.GetGroupMessageFromId(msgid).Sender.QQ;
            }

            cout << "Mute:" << m.Sender.Group.GID << " " << targetnum << " " << mute_time << endl;
            bot.Mute(m.Sender.Group.GID, targetnum, mute_time);

        }
        m.Reply(MessageChain().Plain(Celestial_Action_Success));
        return;
    }

    // 解除禁言功能
    if (plain.substr(0,7) == ".unmute")
    {
        if (HasPermission == false)
        {
            m.Reply(MessageChain().Plain(Celestial_Access_Denial));
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
            bot.UnMute(m.Sender.Group.GID, targetnum);
        }
        m.Reply(MessageChain().Plain(Celestial_Action_Success));
        return;
    }
}