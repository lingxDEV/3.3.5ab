#include "Channel.h"
#include "World.h"

class System_Censure : public PlayerScript
{
public:
    System_Censure() : PlayerScript("System_Censure") { }

    void CheckMessage(Player* player, std::string& msg, uint32 lang)
    {
		// remove all space characters and transform to lowercase for simpler checking
		std::string checkmsg = msg;
		checkmsg.erase(remove_if(checkmsg.begin(), checkmsg.end(), ::isspace), checkmsg.end());
		std::transform(checkmsg.begin(), checkmsg.end(), checkmsg.begin(), ::tolower);
		size_t found;
		
		for( unsigned int a = 0; a < sWorld->m_chat_censure.size(); a = a + 1 )
		{	
			if (sWorld->m_chat_censure[a] != "")
			{
				found = checkmsg.find(sWorld->m_chat_censure[a]);

				if (found != std::string::npos)
				{
					msg = "";
					ChatHandler(player->GetSession()).PSendSysMessage("Sua mensagem nao foi enviada pois contem palavra nao permitida.");
					return;
				}
			}
		}		
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* /*receiver*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* /*group*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* /*guild*/) override
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* /*channel*/) override
    {
        CheckMessage(player, msg, lang);
    }
};

void AddSC_System_Censure()
{
    new System_Censure();
}