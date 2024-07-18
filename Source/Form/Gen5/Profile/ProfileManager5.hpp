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

#ifndef PROFILEMANAGER5_HPP
#define PROFILEMANAGER5_HPP

#include <QWidget>

class ProfileModel5;

namespace Ui
{
    class ProfileManager5;
}

/**
 * @brief Provides interface to view/edit/delete existing profiles and create new ones
 */
class ProfileManager5 : public QWidget
{
    Q_OBJECT
signals:
    /**
     * @brief Emits that the profiles have been modified
     */
    void profilesModified(int);

public:
    /**
     * @brief Construct a new ProfileManager5 object
     *
     * @param parent Parent widget, which takes memory ownership
     */
    ProfileManager5(QWidget *parent = nullptr);

    /**
     * @brief Destroy the ProfileManager3 object
     */
    ~ProfileManager5() override;

private:
    Ui::ProfileManager5 *ui;

    ProfileModel5 *model;

private slots:
    /**
     * @brief Opens dialog to create a new profile
     */
    void create();

    /**
     * @brief Opens dialog to edit an existing profile
     */
    void edit();

    /**
     * @brief Opens dialog to confirm deletion of existing profile
     */
    void remove();
};

#endif // PROFILEMANAGER5_HPP
