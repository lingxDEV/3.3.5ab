#include "ScriptPCH.h"
#include "Group.h"

class Boss_Announcer : public PlayerScript
{
	public:
		Boss_Announcer() : PlayerScript ("Boss_Announcer") {}

	void OnCreatureKill(Player* player, Creature* boss)
	{
		if (player->GetSession()->GetSecurity() > SEC_PLAYER)
			return;
		
		if (boss->isWorldBoss() && boss->GetCreatureTemplate()->maxlevel >= 90)
		{
			char msg[250];

			if(player->GetGroup())
			{
				sprintf(msg, "|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s|r e seu grupo matou o boss |CFF18BE00[%s]|r !!!", player->GetName(), boss->GetName());
			}
			else
			{
				sprintf(msg,"|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s|r matou sozinho o boss |CFF18BE00[%s]|r !!!", player->GetName(),boss->GetName());
			}
			
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			
		}
	};

};

void AddSC_Boss_Announcer()
{
	new Boss_Announcer;
}
