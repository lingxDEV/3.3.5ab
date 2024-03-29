/*
 * Copyright (C) 2011-2022 Project SkyFire <https://www.projectskyfire.org/>
 * Copyright (C) 2008-2022 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2022 MaNGOS <https://www.getmangos.eu/>
 * Copyright (C) 2006-2014 ScriptDev2 <https://github.com/scriptdev2/scriptdev2/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Boss_Houndmaster_Loksey
SD%Complete: 100
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Yells
{
    SAY_AGGRO                       = 0,
};

enum Spells
{
    SPELL_SUMMONSCARLETHOUND        = 17164,
    SPELL_BLOODLUST                 = 6742
};

class boss_houndmaster_loksey : public CreatureScript
{
public:
    boss_houndmaster_loksey() : CreatureScript("boss_houndmaster_loksey") { }

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new boss_houndmaster_lokseyAI(creature);
    }

    struct boss_houndmaster_lokseyAI : public ScriptedAI
    {
        boss_houndmaster_lokseyAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 BloodLust_Timer;

        void Reset() OVERRIDE
        {
            BloodLust_Timer = 20000;
        }

        void EnterCombat(Unit* /*who*/) OVERRIDE
        {
            Talk(SAY_AGGRO);
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
            if (!UpdateVictim())
                return;

            if (BloodLust_Timer <= diff)
            {
                DoCast(me, SPELL_BLOODLUST);
                BloodLust_Timer = 20000;
            }
            else BloodLust_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_houndmaster_loksey()
{
    new boss_houndmaster_loksey();
}
