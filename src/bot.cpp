#include <iostream>
#include <map>
#include <mirai.h>
using namespace std;
using namespace Cyan;
void BotDetection()
{
    MiraiBot bot;
    bot.On<GroupMessage>(
        [&](GroupMessage m)
        {
            try
            {
                string plain = m.MessageChain.GetPlainText();
				const string Version = "Celestial Alpha 0.1(Compiled with GNU GCC 11.1.0)\nRunning on Mirai(Linux amd64 5.13.10-arch1-1)\nMade with love by: SakuraiLH(GitHub)\n開源萬歲!\nIn-development right now.";
                // Bot Declearation
                string bot_des = "";
                bool isSpecified = false;
                if (plain.length() > 4 && plain.substr(0,4) == ".bot")
                {
                    bot_des = plain.substr(5);
                    isSpecified = true;
                }

                // Bot

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
            }
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
        }
    );
}