/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2006  Tarjei Knapstad <tarjei.knapstad@gmail.com>    *
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

#ifndef APP_H
#define APP_H

#include <memory>
#include <vector>

#include "common.h"
#include "system.h"
#include "gfx/screen.h"
#include "path.h"
#include "gfx/fontmanager.h"
#include "menumanager.h"
#include "mapmanager.h"
#include "mission.h"
#include "missionmanager.h"
#include "agentmanager.h"
#include "weaponmanager.h"
#include "modmanager.h"
#include "vehiclemanager.h"
#include "pedmanager.h"
#include "sound/soundmanager.h"
#include "sound/musicmanager.h"
#include "core/gamesession.h"
#include "core/researchmanager.h"

/*!
 * Application class.
 * Used for managing game settings and workflows.
 */
class App : public Singleton < App > {
  public:
    App();
    virtual ~App();

    //! Initialize application
    bool initialize(const char *dir);

    uint8 walkdata_[256];
    // patched version
    uint8 walkdata_p_[256];

    void setCheatCode(const char *name);

    GameSession &getGameSession() {
        return session_;
    }

    SpriteManager &menuSprites() {
        return menu_sprites_;
    }

    GameSpriteManager &gameSprites() {
        return game_sprites_;
    }

    FontManager &fonts() {
        return fonts_;
    }

    Font &introFont() {
        return intro_font_;
    }

    HFont &gameFont() {
        return game_font_;
    }

    MenuManager &menus() {
        return menus_;
    }

    MissionManager &missions() {
        return missions_;
    }

    WeaponManager &weapons() {
        return weapons_;
    }

    MapManager &maps() {
        return maps_;
    }

    VehicleManager &vehicles() {
        return vehicles_;
    }

    AgentManager &agents() {
        return agents_;
    }

    PedManager &peds() {
        return peds_;
    }

    SoundManager &introSounds() {
        return intro_sounds_;
    }

    SoundManager &gameSounds() {
        return game_sounds_;
    }

    MusicManager &music() {
        return music_;
    }

    ResearchManager &researchManager() {
        return researchMan_;
    }

    int numAvailableWeapons() {
        return available_weapons_.size();
    }

    Weapon *availableWeapon(int n) {
        return available_weapons_[n];
    }

    int numAvailableMods() {
        return available_mods_.size();
    }

    Mod *availableMod(int n) {
        return available_mods_[n];
    }

    //! Main application method
    void run(const char *dir, int start_mission);
    //! Reset the application data
    void reset();

    void quit() {
        running_ = false;
    }

    bool isRunning() const {
        return running_;
    }

    void startedPlayingFli() {
        playingFli_ = true;
        skipFli_ = false;
    }

    void finishedPlayingFli() {
        playingFli_ = false;
    }

    bool skipFli() {
        return skipFli_;
    }

    void waitForKeyPress();
    void setPalette(const char *fname, bool sixbit = true);

    //! Handles key pressed
    void keyEvent(Key & key, const int modKeys);
    //! Handles mouse button pressed
    void mouseDownEvent(int x, int y, int button, const int modKeys);
    //! Handles mouse button released
    void mouseUpEvent(int x, int y, int button, const int modKeys);
    //! Handles mouse moved
    void mouseMotionEvent(int x, int y, int state, const int modKeys);

private:
    //! Reads the configuration file
    bool readConfiguration(const char *dir);

    //! Sets the intro flag to false in the config file
    void updateIntroFlag(const char *dir);

    void cheatFunds() {
        session_.setMoney(100000000);
    }

    void cheatRepeatOrCompleteMission();
    void cheatWeaponsAndMods();
    void cheatEquipAllMods();
    void cheatAnyMission();
    void cheatResurrectAgents();
    void cheatOwnAllCountries();
    void cheatAccelerateTime();
    void cheatFemaleRecruits();
    void cheatEquipFancyWeapons();

private:
    GameSession session_;
    std::vector<Weapon *> available_weapons_;
    std::vector<Mod *> available_mods_;

    bool running_, playingFli_, skipFli_;
    /*! True means the game will run in fullscreen. */
    bool fullscreen_;
    /*! True means the intro will be played.*/
    bool playIntro_;
    std::auto_ptr<Screen> screen_;
    std::auto_ptr<System> system_;

    SpriteManager menu_sprites_;
    GameSpriteManager game_sprites_;
    FontManager fonts_;
    HFont game_font_;
    Font intro_font_;
    SpriteManager intro_font_sprites_;
    MenuManager menus_;
    MissionManager missions_;
    AgentManager agents_;
    WeaponManager weapons_;
    ModManager mods_;
    MapManager maps_;
    VehicleManager vehicles_;
    PedManager peds_;
    SoundManager intro_sounds_;
    SoundManager game_sounds_;
    MusicManager music_;
    ResearchManager researchMan_;
};

#define g_App   App::singleton()

#define g_Session   App::singleton().getGameSession()

#endif
