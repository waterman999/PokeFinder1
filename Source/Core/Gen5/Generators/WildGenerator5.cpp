/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2021 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "WildGenerator5.hpp"
#include <Core/Enum/Encounter.hpp>
#include <Core/Enum/Lead.hpp>
#include <Core/Enum/Method.hpp>
#include <Core/Parents/Filters/StateFilter.hpp>
#include <Core/RNG/LCRNG64.hpp>
#include <Core/RNG/MT.hpp>
#include <Core/RNG/RNGList.hpp>
#include <Core/Util/EncounterSlot.hpp>
#include <Core/Util/Utilities.hpp>

WildGenerator5::WildGenerator5(u32 initialAdvances, u32 maxAdvances, u16 tid, u16 sid, u8 gender, u8 genderRatio, bool isBW2, Method method,
                               Encounter encounter, const StateFilter &filter) :
    WildGenerator(initialAdvances, maxAdvances, tid, sid, genderRatio, method, filter),
    idBit((tid & 1) ^ (sid & 1)),
    encounter(encounter),
    gender(gender)
{
}

std::vector<WildState> WildGenerator5::generate(u64 seed) const
{
    switch (method)
    {
    case Method::Method5:
        switch (encounter)
        {
        case Encounter::Grass:
            return generateWild(seed);
        default:
            break;
        }
    default:
        break;
    }
    return std::vector<WildState>();
}

std::vector<WildState> WildGenerator5::generateWild(u64 seed) const
{
    std::vector<WildState> states;

    BWRNG rng(seed);
    rng.advance(initialAdvances + offset);

    u8 thresh = encounter == Encounter::OldRod ? 25 : encounter == Encounter::GoodRod ? 50 : encounter == Encounter::SuperRod ? 75 : 0;

    for (u32 cnt = 0; cnt <= maxAdvances; cnt++, rng.next())
    {
        WildState state(initialAdvances + cnt);
        BWRNG go(rng.getSeed());
        state.setSeed(go.nextUInt(0x1fff)); // Chatot pitch
        state.setEncounterSlot(EncounterSlot::bwSlot(go.nextUInt(), encounter, isBW2));
        go.advance(1); // Held item

        u32 pid;
        if (lead == Lead::Synchronize)
        {
            bool synch = (go.nextUInt() >> 31) == 1;
            pid = go.nextUInt() ^ 0x10000;

            if (synch)
            {
                state.setNature(synchNature);
            }
            else
            {
                state.setNature(go.nextUInt(25));
            }
        }
        else if (lead >= Lead::CuteCharm && lead <= Lead::CuteCharmFemale)
        {
            bool charm = (go.nextUInt(0xffff) / 656) < 67;
            pid = go.nextUInt() ^ 0x10000;

            if (!charm)
            {
                state.setNature(go.nextUInt(25));
            }
            else
            {
                // TODO: fix hard coded gender
                pid = Utilities::forceGender(pid, go.next(), 0, genderRatio);
                state.setNature(go.nextUInt(25));
            }
        }
        // else if (lead == Lead::Search)
        //{
        // TODO: do we live to suffer?
        //}
        else // No lead
        {
            pid = go.nextUInt() ^ 0x10000;
            state.setNature(go.nextUInt(25));
        }

        u8 val = idBit ^ (pid & 1) ^ (pid >> 31);
        if (val == 1)
        {
            pid ^= 0x80000000;
        }

        state.setPID(pid);
        state.setAbility((pid >> 16) & 1);
        state.setGender(pid & 255, genderRatio);
        state.setShiny<8>(tsv, (pid >> 16) ^ (pid & 0xffff));

        if (filter.comparePID(state))
        {
            states.emplace_back(state);
        }
    }

    return states;
}
