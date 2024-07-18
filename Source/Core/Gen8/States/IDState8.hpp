/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2024 by Admiral_Fish, bumba, and EzPzStreamz
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

#ifndef IDSTATE8_HPP
#define IDSTATE8_HPP

#include <Core/Parents/States/IDState.hpp>

/**
 * @brief Contains additional information for Gen 8 TID/SID
 */
class IDState8 : public IDState
{
public:
    /**
     * @brief Construct a new IDState8 object
     *
     * @param advances Advances of the state
     * @param tid Trainer ID
     * @param sid Secret ID
     * @param displayTID Displayed trainer ID
     */
    IDState8(u32 advance, u16 tid, u16 sid, u32 displayTID) : IDState(advance, tid, sid, (tid ^ sid) >> 4), displayTID(displayTID)
    {
    }

    /**
     * @brief Returns the display TID of the state
     *
     * @return State display TID
     */
    u32 getDisplayTID() const
    {
        return displayTID;
    }

private:
    u32 displayTID;
};

#endif // IDSTATE8_HPP
