#include "ScriptMgr.h"
 
class announce_login : public PlayerScript
{
public:
    announce_login() : PlayerScript("announce_login") {}
	
    void OnLogin(Player* player)
    {
        std::ostringstream ss;
 
        if(player->GetTotalPlayedTime() < 5)
        {
            ss << "|cff54b5ffNovo Personagem Criado,|r " << player->GetName();
            sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str(), 0);
            player->CastSpell(player, 55420);
        }
    }
 
};
 
void AddSC_announce_login()
{
    new announce_login;
}
