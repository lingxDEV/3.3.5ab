#include "ScriptPCH.h"

class npc_info : public CreatureScript
{
	public:
		npc_info() : CreatureScript("npc_info")
		{
		}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			pPlayer->ADD_GOSSIP_ITEM(4, "Qual a rate de UP do servidor?", GOSSIP_SENDER_MAIN, 0);
			pPlayer->ADD_GOSSIP_ITEM(4, "Como reportar Bug?", GOSSIP_SENDER_MAIN, 1);
			pPlayer->ADD_GOSSIP_ITEM(4, "Como eu posso Falar no Global?", GOSSIP_SENDER_MAIN, 2);
			pPlayer->ADD_GOSSIP_ITEM(4, "Qual o ping do servidor?", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "Qual o forum do servidor?", GOSSIP_SENDER_MAIN, 4);
			pPlayer->ADD_GOSSIP_ITEM(4, "Qual o instagram do servidor?", GOSSIP_SENDER_MAIN, 5);
			pPlayer->ADD_GOSSIP_ITEM(4, "Qual canal do youtube do servidor?", GOSSIP_SENDER_MAIN, 6);
			pPlayer->ADD_GOSSIP_ITEM(4, "Como pegar facçao no panda?", GOSSIP_SENDER_MAIN, 7);
			pPlayer->ADD_GOSSIP_ITEM(0, "Sair", GOSSIP_SENDER_MAIN, 8);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;
			
			switch(uiAction)
			{
				case 0:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Rate 2x todos os dias das 15h até 22h - XP: 60x, Profissão: 02x, Reputação: 02x e Honor: 02x.", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 1:
					{

						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Report de bug é em nosso forum.", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Digite /join global.", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Ping 20 - 50", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 4:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Pandarenbr.com/forum", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 5:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: @pandarenbr", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 6:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: youtube.com/pandarenbr", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 7:
					{
						ChatHandler(Player->GetSession()).PSendSysMessage("Ajudante diz: Basta ir no npc destravador e escolher sua facçao.", Player->GetName());
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 8:
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}

};

void AddSC_npc_info()
{
	new npc_info();
}