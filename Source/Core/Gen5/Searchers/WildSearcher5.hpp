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

#ifndef WILDSEARCHER5_HPP
#define WILDSEARCHER5_HPP

#include <Core/Gen5/Generators/WildGenerator5.hpp>
#include <Core/Gen5/Profile5.hpp>
#include <Core/Gen5/States/SearcherState5.hpp>
#include <Core/Gen5/States/WildState5.hpp>
#include <atomic>
#include <mutex>
#include <unordered_map>

class WildSearcher5
{
public:
    WildSearcher5() = default;
    explicit WildSearcher5(const Profile5 &profile, Method method);
    void startSearch(const WildGenerator5 &generator, int threads, Date start, const Date &end);
    void cancelSearch();
    std::vector<SearcherState5<WildState>> getResults();
    int getProgress() const;

private:
    Profile5 profile;

    Method method;
    bool searching;
    std::atomic<int> progress;
    std::vector<SearcherState5<WildState>> results;
    std::mutex mutex;

    void search(WildGenerator5 generator, const Date &start, const Date &end);
};

#endif // WILDSEARCHER5_HPP
