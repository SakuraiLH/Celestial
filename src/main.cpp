#include <iostream>
#include <map>
#include <vector>
#include <mirai.h>
using namespace std;
using namespace Cyan;

int main()
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	MiraiBot bot;
	SessionOptions opts;
	opts.BotQQ = 239686941_qq;				// 请修改为你的机器人QQ
	opts.HttpHostname = "localhost";		// 请修改为和 mirai-api-http 配置文件一致
	opts.WebSocketHostname = "localhost";	// 同上
	opts.HttpPort = 8080;					// 同上
	opts.WebSocketPort = 8080;				// 同上
	opts.VerifyKey = "123";			// 同上
	bool anti_recall = false;

	while (true)
	{
		try
		{
			cout << "尝试与 mirai-api-http 建立连接..." << endl;
			bot.Connect(opts);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

	map<GID_t, bool> groups;

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				// ======= Declearation =======

				// 1. General
				string plain = m.MessageChain.GetPlainText();
				string msg = m.MessageChain.ToString();
				vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
				m.MessageChain.ToVector();
				const string Version = "Celestial Alpha 0.1(Compiled with GNU GCC 11.1.0)\nRunning on Mirai(Linux amd64 5.13.10-arch1-1)\nMade with love by: SakuraiLH(GitHub)\n開源萬歲!\nIn-development right now.";

				// 2. Bot Declearation
				string bot_des = "";
				bool isSpecified = false;
				if (plain.length() > 4 && plain.substr(0,4) == ".bot")
				{
					bot_des = plain.substr(5);
					isSpecified = true;
				}

				// ======= Functions =======

				// 1. No-Recall

				// + Enable
				if (plain == ".norecall enable")
				{
					groups[m.Sender.Group.GID] = true;
					m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被開啓."));
					return;
				}

				// + Disable
				if (plain == ".norecall disable")
				{
					groups[m.Sender.Group.GID] = false;
					m.Reply(MessageChain().Plain("Celestial > 反撤回功能已被關閉."));
					return;
				}

				// + General
				if (plain == ".norecall")
				{
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
				}

				// 2. Bot

				// + Not Specified
				if (plain.substr(0,4) == ".bot" && isSpecified == false)
				{
					m.Reply(MessageChain().Plain(Version));
				}
				
				// + Specified
				if (plain.substr(0,4) == ".bot" && isSpecified == true)
				{
					if (bot_des == "2396") {
						m.Reply(MessageChain().Plain(Version));
					}
				}

				// 3. Ban

				if (plain.substr(0,4) == ".ban" && msg.length() > 32)
				{
					if(qm.size() > 0)
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
				}
				if (plain.substr(0,4) == ".ban" && msg.length() <= 32)
				{
					m.Reply(MessageChain().Plain("Celestial > 請指定踢出目標!"));
				}
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});


	bot.On<GroupRecallEvent>(
		[&](GroupRecallEvent e)
		{
			try
			{
				if (!groups[e.Group.GID]) return;
				auto recalled_mc = bot.GetGroupMessageFromId(e.MessageId).MessageChain;
				auto mc = "Celestial > 撤回內容如下: " + recalled_mc;
				bot.SendMessage(e.Group.GID, mc);
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});

	// 在失去与mah的连接后重连
	bot.On<LostConnection>([&](LostConnection e)
		{
			cout << e.ErrorMessage << " (" << e.Code << ")" << endl;
			while (true)
			{
				try
				{
					cout << "尝试连接 mirai-api-http..." << endl;
					bot.Reconnect();
					cout << "与 mirai-api-http 重新建立连接!" << endl;
					break;
				}
				catch (const std::exception& ex)
				{
					cout << ex.what() << endl;
				}
				MiraiBot::SleepSeconds(1);
			}
		});

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			// 程序结束前必须调用 Disconnect，否则 mirai-api-http 会内存泄漏。
			bot.Disconnect();
			break;
		}
	}

	return 0;
}
