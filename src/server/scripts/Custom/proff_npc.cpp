#include "ScriptPCH.h"
#include "Language.h"

class proff_npc : public CreatureScript

{
public:

	proff_npc() : CreatureScript("proff_npc") {}

	struct proff_npcAI : public ScriptedAI
	{
		proff_npcAI(Creature *c) : ScriptedAI(c)
		{
		}
	};

	CreatureAI* GetAI(Creature* _creature) const
	{
		return new proff_npcAI(_creature);
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Alquimia] Conquista 10.000 pts ", GOSSIP_SENDER_MAIN, 1, "Certeza que deseja aprender Alquimia?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Ferraria] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 2, "Certeza que deseja aprender Ferraria?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Couraria] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 3, "Certeza que deseja aprender Couraria?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Alfaiataria] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 4, "Certeza que deseja aprender Alfaiataria?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Engenharia] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 5, "Certeza que deseja aprender Engenharia?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Encantamento] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 6, "Certeza que deseja aprender Encantamento?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Joalheria] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 7, "Certeza que deseja aprender Joalheria?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Escrivania] Conquista 10.000 pts", GOSSIP_SENDER_MAIN, 8, "Certeza que deseja aprender Escrivania?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Mineiracao] Conquista 5.000 pts", GOSSIP_SENDER_MAIN, 11, "Certeza que deseja aprender Mineiracao?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Herborismo] Conquista 5.000 pts", GOSSIP_SENDER_MAIN, 12, "Certeza que deseja aprender Herborismo?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "[Esfolamento] Conquista 5.000 pts", GOSSIP_SENDER_MAIN, 13, "Certeza que deseja aprender Esfolamento?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(1, "[Culinaria] Conquista 2.500 pts", GOSSIP_SENDER_MAIN, 9, "Certeza que deseja aprender Culinaria?", 0, false);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(1, "[P. Socorros] Conquista 2.500 pts", GOSSIP_SENDER_MAIN, 10, "Certeza que deseja aprender P. Socorros?", 0, false);
		pPlayer->PlayerTalkClass->SendGossipMenu(pCreature->GetEntry(), pCreature->GetGUID());
		return true;
	}

	bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer) const
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}

	bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
	{
		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		std::string skill_name = SkillInfo->name;
		if (!SkillInfo)
			return false;

		LearnSkillRecipesHelper(pPlayer, SkillInfo->id);
		pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 600, 600);
		if (skill_name.empty())
			return false;

		ChatHandler(pPlayer).PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name.c_str());
		return true;
	}

	void LearnSkillRecipesHelper(Player *pPlayer, uint32 skill_id)
	{
		uint32 classmask = pPlayer->getClassMask();

		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;

			// wrong skill
			if (skillLine->SkillLine != skill_id)
				continue;
			if (skillLine->Spell == 110955) // skip this spell.. idk why its added
				continue;
			// skip racial skills
			if (skillLine->RaceMask != 0)
				continue;
			// skip wrong class skills
			if (skillLine->ClassMask && (skillLine->ClassMask & classmask) == 0)
				continue;

			SpellEntry const* spellInfo = sSpellStore.LookupEntry(skillLine->Spell);
			pPlayer->learnSpell(skillLine->Spell, false);
		}
	}

	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	void CompleteLearnProfession(Player *pPlayer, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			pPlayer->GetSession()->SendNotification("Já possui duas profissões!");
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				pPlayer->GetSession()->SendNotification("Erro interno, tente novamente mais tarde.");
		}
	}

	bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		uint32 conquest_points = pPlayer->GetCurrency(CURRENCY_TYPE_CONQUEST_POINTS, true);


		switch (uiAction)
		{

		case 1:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);
				CompleteLearnProfession(pPlayer, SKILL_ALCHEMY);

			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 2:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);

				CompleteLearnProfession(pPlayer, SKILL_BLACKSMITHING);

			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}

			break;
		case 3:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_LEATHERWORKING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 4:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_TAILORING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 5:

			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);

				CompleteLearnProfession(pPlayer, SKILL_ENGINEERING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 6:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_ENCHANTING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 7:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_JEWELCRAFTING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 8:
			if (conquest_points >= 10000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -10000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_INSCRIPTION);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}

			break;
		case 9:
			if (conquest_points >= 2500)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -2500 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_COOKING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 10:

			if (conquest_points >= 2500)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -2500 * CURRENCY_PRECISION, true, true);

				CompleteLearnProfession(pPlayer, SKILL_FIRST_AID);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 11:
			if (conquest_points >= 5000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -5000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_MINING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 12:
			if (conquest_points >= 5000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -5000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_HERBALISM);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		case 13:
			if (conquest_points >= 5000)
			{
				pPlayer->ModifyCurrency(CURRENCY_TYPE_CONQUEST_POINTS, -5000 * CURRENCY_PRECISION, true, true);


				CompleteLearnProfession(pPlayer, SKILL_SKINNING);
			}
			else
			{
				pPlayer->CLOSE_GOSSIP_MENU();

				return false;
			}


			break;
		}

		pPlayer->CLOSE_GOSSIP_MENU();
		return true;
	}
};

void AddSC_proff_npc()
{
	new proff_npc();
}