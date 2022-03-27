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

#ifndef SKYFIRESERVER_TOTEM_H
#define SKYFIRESERVER_TOTEM_H

#include "TemporarySummon.h"

enum TotemType
{
    TOTEM_PASSIVE    = 0,
    TOTEM_ACTIVE     = 1,
    TOTEM_STATUE     = 2 // copied straight from MaNGOS, may need more implementation to work
};

class Totem : public Minion
{
    public:
        Totem(SummonPropertiesEntry const* properties, Unit* owner);
        virtual ~Totem() { }
        void Update(uint32 time) OVERRIDE;
        void InitStats(uint32 duration) OVERRIDE;
        void InitSummon() OVERRIDE;
        void UnSummon(uint32 msTime = 0) OVERRIDE;
        uint32 GetSpell(uint8 slot = 0) const { return m_spells[slot]; }
        uint32 GetTotemDuration() const { return m_duration; }
        void SetTotemDuration(uint32 duration) { m_duration = duration; }
        TotemType GetTotemType() const { return m_type; }

        bool UpdateStats(Stats /*stat*/) OVERRIDE { return true; }
        bool UpdateAllStats() OVERRIDE { return true; }
        void UpdateResistances(uint32 /*school*/) OVERRIDE { }
        void UpdateArmor() OVERRIDE { }
        void UpdateMaxHealth() OVERRIDE { }
        void UpdateMaxPower(Powers /*power*/) OVERRIDE { }
        void UpdateAttackPowerAndDamage(bool /*ranged*/) OVERRIDE { }
        void UpdateDamagePhysical(WeaponAttackType /*attType*/) OVERRIDE { }

        bool IsImmunedToSpellEffect(SpellInfo const* spellInfo, uint32 index) const OVERRIDE;

    protected:
        TotemType m_type;
        uint32 m_duration;
};
#endif
