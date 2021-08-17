#include <iostream>
#include <map>
#include <vector>
#include <mirai.h>
#include <sys/utsname.h>

using namespace std;
using namespace Cyan;

int main()
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif

	// Clang 或是 G++
	string true_cxx =
#ifdef __clang__
	"Clang++";
#else
	"GNU GCC";
#endif

	string current_os =
#ifdef __WIN32
	"Windows";
#elif __unix__ && !__linux__
	"Unix";
#elif __APPLE__
	"MacOS";
#elif __linux__
	"Linux";
#elif __FreeBSD__
	"FreeBSD";
#else
	"Unknown";
#endif
	const string compile_time = __TIMESTAMP__;
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

				// 其他變量
				string plain = m.MessageChain.GetPlainText();
				string msg = m.MessageChain.ToString();
				vector<QuoteMessage> qm = m.MessageChain.GetAll<QuoteMessage>();
				m.MessageChain.ToVector();
				const string Celestial_Short_Version = "0.1";
				const string Celestial_Stable = "Alpha";
				const string Celestial_Version = "Celestial " + Celestial_Stable + ' ' + Celestial_Short_Version + " By SakuraiLH(GitHub)" + '\n'
															 + "(Compiled with " + true_cxx + " at " + compile_time + ")" + '\n'
															 + "Running on Mirai/" + current_os + " for this build." + '\n'
															 + "Long live the open source!" + '\n'
															 + "Github Link: https://github.com/SakuraiLH/Celestial";

				// bot變量探測
				string bot_des = "";
				bool isSpecified = false;
				if (plain.length() > 4 && plain.substr(0,4) == ".bot")
				{
					bot_des = plain.substr(5);
					isSpecified = true;
				}

				// 組權限探測
				GroupPermission gp;
				gp = m.Sender.Permission;
				bool HasPermission = false;
				if(GroupPermissionStr("ADMINISTRATOR") == gp || GroupPermissionStr("OWNER") == gp)
				{
					HasPermission = true;
				}

				// ======= Functions =======

				// 沒有指定qq號前4位的bot
				if (plain.substr(0,4) == ".bot" && isSpecified == false)
				{
					m.Reply(MessageChain().Plain(Celestial_Version));
					return;
				}
				
				// 指定了QQ號前4位的bot
				if (plain.substr(0,4) == ".bot" && isSpecified == true)
				{
					if (bot_des == "2396") {
						m.Reply(MessageChain().Plain(Celestial_Version));
					}
					return;
				}
	
				// .whoami 一個探測權限的命令
				if (plain == ".whoami")
				{
					// 如果沒有權限
					if (HasPermission == false) {
						m.Reply(MessageChain().Plain("Celestial > 你沒有操作Celestial的權限。"));
						return;
					}

					// 如果有權限
					m.Reply(MessageChain().Plain("Celestial > 你有操作Celestial的權限。"));
					return;
				}

				// 需要權限

				// 反撤回功能

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

				// 踢出功能

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
