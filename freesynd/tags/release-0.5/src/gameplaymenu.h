/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2010  Benoit Blancard <benblan@users.sourceforge.net>*
 *   Copyright (C) 2010  Bohdan Stelmakh <chamel@users.sourceforge.net> *
 *                                                                      *
 *    This program is free software;  you can redistribute it and / or  *
 *  modify it  under the  terms of the  GNU General  Public License as  *
 *  published by the Free Software Foundation; either version 2 of the  *
 *  License, or (at your option) any later version.                     *
 *                                                                      *
 *    This program is  distributed in the hope that it will be useful,  *
 *  but WITHOUT  ANY WARRANTY;  without even  the implied  warranty of  *
 *  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  *
 *  General Public License for more details.                            *
 *                                                                      *
 *    You can view the GNU  General Public License, online, at the GNU  *
 *  project's  web  site;  see <http://www.gnu.org/licenses/gpl.html>.  *
 *  The full text of the license is also included in the file COPYING.  *
 *                                                                      *
 ************************************************************************/

#ifndef GAMEPLAYMENU_H
#define GAMEPLAYMENU_H

class Mission;

/*!
 * Gameplay Menu class.
 */
class GameplayMenu : public Menu {
public:
    GameplayMenu(MenuManager *m);

    bool isSubMenu() { return false; }

    void handleTick(int elapsed);
    void handleShow();
    void handleRender();
    void handleLeave();
    void handleMouseMotion(int x, int y, int state, const int modKeys);
    void handleMouseDown(int x, int y, int button, const int modKeys);
    void handleMouseUp(int x, int y, int button, const int modKeys);

protected:
    bool handleUnknownKey(Key key, const int modKeys);
    void drawAgentSelectors();
    void drawPerformanceMeters();
    void drawSelectAllButton();
    void drawMissionHint(int elapsed);
    void drawWeaponSelectors();
    void drawMiniMap();
    //! Scroll the map vertically or horizontally.
    bool scroll();
    bool isScrollLegal(int newScrollX, int newScrollY);
    void improveScroll(int &newScrollX, int &newScrollY);
    int selectedAgentsCount();
    void selectAgent(unsigned int agentNo, bool addToGroup);
    void selectAllAgents(bool invert=false);

    bool isAgentSelected(unsigned int agentNo) {
        return (selected_agents_ & (1 << agentNo))!=0;
    }

protected:
    int tick_count_, last_animate_tick_;
    int last_motion_tick_, last_motion_x_, last_motion_y_;
    int mission_hint_ticks_, mission_hint_;
    Mission *mission_;
    /*! Holds the X coordinate of the screen origin (top left corner) in the world coordinate.*/
    int world_x_;
    /*! Holds the Y coordinate of the screen origin (top left corner) in the world coordinate.*/
    int world_y_;
    /*! Holds the amount of scroll on the X axis.*/
    int scroll_x_;
    /*! Holds the amount of scroll on the Y axis.*/
    int scroll_y_;
    unsigned int selected_agents_;
    unsigned int selectable_agents_;
    /*! Flag to tell if path between checkpoints must be drawn. */
    //TODO : see if this could be computed dynamically
    bool showPath_;
    int pointing_at_ped_, pointing_at_vehicle_, pointing_at_weapon_;
    int mm_tx_, mm_ty_;
    bool completed_;
    bool pressed_btn_select_all_;
};

#endif
