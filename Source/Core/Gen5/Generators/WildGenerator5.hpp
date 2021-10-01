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

#ifndef GENERATOR5_HPP
#define GENERATOR5_HPP

#include <Core/Parents/Generators/WildGenerator.hpp>
#include <Core/Parents/States/WildState.hpp>

enum Encounter : u8;

class WildGenerator5 : public WildGenerator
{
public:
    WildGenerator5() = default;
    WildGenerator5(u32 initialAdvances, u32 maxAdvances, u16 tid, u16 sid, u8 gender, u8 genderRatio, bool isBW2, Method method,
                   Encounter encounter, const StateFilter &filter, bool shinyCharm);
    std::vector<WildState> generate(u64 seed) const;

private:
    u8 idBit;
    Encounter encounter;
    u8 gender;
    bool isBW2;
    bool shinyCharm;

    std::vector<WildState> generateWild(u64 seed) const;
};

#endif // GENERATOR5_HPP
