#include "GlobalVariable.h"

int main()
{
	opts.BotQQ = 239686941_qq;
	opts.HttpHostname = "localhost";
	opts.WebSocketHostname = "localhost";
	opts.HttpPort = 8080;
	opts.WebSocketPort = 8080;
	opts.VerifyKey = "123";
	bool anti_recall = false;
	string Celestial_QQ_Prefix = to_string(opts.BotQQ.Get().ToInt64());

	while (true)
	{
		try
		{
			cout << "尝试与 mirai-api-http 建立连接..." << endl;
			bot.Connect(opts);
			break;
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}

	cout << "Bot Working..." << endl;

	bot.On<Message>(
		[&](Message k)
		{
			try
			{
				string plain = k.MessageChain.GetPlainText();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
		}
	);

	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();
			}
			catch (const std::exception& ex)
			{
				std::cerr << ex.what() << endl;
			}
		});


	bot.On<GroupRecallEvent>(
		[&](GroupRecallEvent e)
		{
			try
			{
			}
			catch (const std::exception& ex)
			{
				std::cerr << ex.what() << endl;
			}
		});

	bot.On<NewFriendRequestEvent>(
		[&](NewFriendRequestEvent f)
		{
			try
			{
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
					std::cerr << ex.what() << endl;
				}
				MiraiBot::SleepSeconds(1);
			}
		});

	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			bot.Disconnect();
			break;
		}
	}

	return 0;
}