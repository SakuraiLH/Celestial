#include "GlobalVariable.h"
#include "BotMsg.cpp"
#include "WhoAmI.cpp"
#include "VersionGenerator.h"
#include "BotKickMute.cpp"
#include "AntiRecall.cpp"
#include "MiscEvent.cpp"

int main()
{
#if defined(WIN32) || defined(_WIN32)
	system("chcp 65001");
#endif

	opts.BotQQ = 239686941_qq;
	opts.HttpHostname = "localhost";
	opts.WebSocketHostname = "localhost";
	opts.HttpPort = 8080;
	opts.WebSocketPort = 8080;
	opts.VerifyKey = "123";
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

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				// ======= Declearation =======

				// 其他變量
				string plain = m.MessageChain.GetPlainText();
				bool HasPermission = false;

				// ======= Functions =======

				botcall(plain, m);
	
				whoami(plain, HasPermission, m);

				kick(plain, HasPermission, m);

				mute(plain, HasPermission, m);

				AntiRecall(plain, HasPermission, m);

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
				ReviveRecall(e);
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});

	bot.On<NewFriendRequestEvent>(
		[&](NewFriendRequestEvent f)
		{
			try
			{
				FriendIntroduction(f);
			}
			catch(const std::exception& ex)
			{
				cout << ex.what() << '\n';
			}
			
		});

	bot.On<BotInvitedJoinGroupRequestEvent>(
		[&](BotInvitedJoinGroupRequestEvent n)
		{
			try
			{
				GroupIntroduction(n);
			}
			catch(const std::exception& ex)
			{
				std::cerr << ex.what() << '\n';
			}
			
		}
	);

	bot.On<BotJoinGroupEvent>(
		[&](BotJoinGroupEvent h)
		{
			try
			{
				
			}
			catch(const std::exception& ex)
			{
				std::cerr << ex.what() << '\n';
			}
			
		}
	);
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
