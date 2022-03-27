/*
 * Copyright (C) 2011-2022 Project SkyFire <https://www.projectskyfire.org/>
 * Copyright (C) 2008-2022 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2022 MaNGOS <https://www.getmangos.eu/>
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

#ifndef SF_BATTLEGROUNDTV_H
#define SF_BATTLEGROUNDTV_H

#include "Battleground.h"

enum BattlegroundTVObjectTypes
{
    BG_TV_OBJECT_DOOR_1         = 0,
    BG_TV_OBJECT_DOOR_2         = 1,
    BG_TV_OBJECT_BUFF_1         = 2,
    BG_TV_OBJECT_BUFF_2         = 3,
    BG_TV_OBJECT_MAX            = 4
};

enum BattlegroundTVObjects
{
    BG_TV_OBJECT_TYPE_DOOR_1    = 213196,
    BG_TV_OBJECT_TYPE_DOOR_2    = 213197,
    BG_TV_OBJECT_TYPE_BUFF_1    = 184663,
    BG_TV_OBJECT_TYPE_BUFF_2    = 184664
};

class BattlegroundTV : public Battleground
{
    public:
        BattlegroundTV();
        ~BattlegroundTV();

        /* inherited from BattlegroundClass */
        void AddPlayer(Player* player) OVERRIDE;
        void StartingEventCloseDoors() OVERRIDE;
        void StartingEventOpenDoors() OVERRIDE;

        void RemovePlayer(Player* player, uint64 guid, uint32 team) OVERRIDE;
        void HandleAreaTrigger(Player* Source, uint32 Trigger) OVERRIDE;
        bool SetupBattleground() OVERRIDE;
        void Reset() OVERRIDE;
        void FillInitialWorldStates(WorldStateBuilder& builder) OVERRIDE;
        void HandleKillPlayer(Player* player, Player* killer) OVERRIDE;

        /* Scorekeeping */
        void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true) OVERRIDE;
};
#endif
