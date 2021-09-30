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

#ifndef WILD5_HPP
#define WILD5_HPP

#include <Core/Gen5/Profile5.hpp>
#include <QMenu>

class WildGeneratorModel5;
class WildSearcherModel5;

namespace Ui
{
    class Wild5;
}

class Wild5 : public QWidget
{
    Q_OBJECT
signals:
    void alertProfiles(int);

public:
    explicit Wild5(QWidget *parent = nullptr);
    ~Wild5() override;
    void updateProfiles();
    bool hasProfiles() const;

private:
    Ui::Wild5 *ui;
    WildGeneratorModel5 *generatorModel = nullptr;
    WildSearcherModel5 *searcherModel = nullptr;
    std::vector<Profile5> profiles;
    Profile5 currentProfile;
    QMenu *generatorMenu = nullptr;
    QMenu *searcherMenu = nullptr;

    void setupModels();

private slots:
    void generate();
    void search();
    void profileIndexChanged(int index);
    void generatorLead();
    void calculateInitialAdvances();
    void generatorMethodIndexChanged(int index);
    void searcherMethodIndexChanged(int index);
    void tableViewGeneratorContextMenu(const QPoint &pos);
    void tableViewSearcherContextMenu(const QPoint &pos);
    void profileManager();
};

#endif // WILD5_HPP
