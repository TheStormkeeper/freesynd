/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2006  Tarjei Knapstad <tarjei.knapstad@gmail.com>    *
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
#ifndef AGENTMANAGER_H
#define AGENTMANAGER_H

#include "common.h"
#include "agent.h"
#include <vector>

/*!
 * Agent Manager class.
 *
 * Provides methods for managing player's agents.
 */
class AgentManager {
public:
    /*! Max number of agents in cryo chamber.*/
    static const int MAX_AGENT;

    AgentManager();
    ~AgentManager();

    void loadAgents();
    void reset(bool onlyWomen = false);

    Agent *agent(int n) {
        assert(n < MAX_AGENT);
        return agents_[n];
    }

protected:
    /*!
     * Selected agents for the next mission. Up to 4 agents.
     */
    Agent *agents_[18];
    int nextName_;
};

#endif
