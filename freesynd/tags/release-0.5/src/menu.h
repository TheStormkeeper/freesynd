/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2010  Benoit Blancard <benblan@users.sourceforge.net>*
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

#ifndef MENU_H
#define MENU_H

#include <string>
#include <list>
#include <map>
#include "keys.h"
#include "common.h"
#include "menus/widget.h"

class FontManager;
class Menu;
class MenuManager;


/*!
 * Menu class.
 */
class Menu {
public:
    Menu(MenuManager *menuManager, const char *name, const char *showAnim,
            const char *leaveAnim);
    Menu(MenuManager *menuManager, const char *name, const char *parent);
    virtual ~Menu();

    const char *name() { return name_.c_str(); }

    void setClearArea(uint8 *background, int x, int y, int w, int h) {
        background_ = background;
        clear_x_ = x;
        clear_y_ = y;
        clear_w_ = w;
        clear_h_ = h;
    }

    virtual bool isSubMenu() {
        return leaveAnim_.size() == 0;
    }

    /*! Returns true if an animation has been defined when opening the menu.*/
    bool hasShowAnim() { return showAnim_.size() != 0; }
    /*! Returns the opening animation file name. */
    const char * getShowAnimName() { return showAnim_.c_str(); }
    /*! Returns true if an animation has been defined when leaving the menu.*/
    bool hasLeaveAnim() { return leaveAnim_.size() != 0; }
    /*! Returns the leaving animation file name. */
    const char * getLeaveAnimName() { return leaveAnim_.c_str(); }
    
    void render();
    //! Does common actions before leaving
    void leave();
    //! Creates a new text label and returns its id
    int addStatic(int x, int y, const char *text, FontManager::EFontSize size, bool dark);
    //! Creates a new text label with a fixed size and returns its id
    int addStatic(int x, int y, int width, const char *text, FontManager::EFontSize size, bool dark);
    //! Returns the MenuText with given id
    MenuText * getStatic(int staticId);
    //! Creates a new button that has no text but an image
    int addImageOption(int x, int y, Key key, int dark_widget, int light_widget, bool visible = true);
    //! Creates a new button and returns its id
    int addOption(int x, int y, int width, int height, const char *text, FontManager::EFontSize size, Key key,
            const char *to = NULL, bool visible = true, bool centered = true, int dark_widget = 0, int light_widget = 0);
    //! Creates a new toggle button and returns its id
    int addToggleAction(int x, int y, int width, int height, const char *text, FontManager::EFontSize size, Key key, bool selected);
    //! Creates a new list box and returns a pointer on it
    ListBox * addListBox(int x, int y, int width, int height, bool visible = true);
    //! Creates a specific list box for team selection and returns a pointer on it
    TeamListBox * addTeamListBox(int x, int y, int width, int height, bool visible = true);

    ActionWidget * getActionWidget(int buttonId);
    Option * getOption(int buttonId);

    void setParentMenu(const char *m) { parent_menu_ = m; }

    //! Handles key pressed
    void keyEvent(Key key, const int modKeys);
    //! Handles mouse moved
    void mouseMotionEvent(int x, int y, int state, const int modKeys);
    //! Handles mouse button pressed
    void mouseDownEvent(int x, int y, int button, const int modKeys);
    //! Handles mouse button released
    void mouseUpEvent(int x, int y, int button, const int modKeys);

    //! Hides the given button
    /*!
     * Search for the option mapped to the given key
     * and disables its visible property.
     * \param key The key associated to the option.
     */
    void hideOption(Key key) {
        if (hotKeys_.find(key) == hotKeys_.end())
            return;

        Option *opt = hotKeys_[key];

        if (opt->isVisible()) {
            opt->setVisible(false);
        }
    }

    //! Shows the given button
    /*!
     * Search for the option mapped to the given key
     * and enables its visible property.
     * \param key The key associated to the option.
     */
    void showOption(Key key) {
        if (hotKeys_.find(key) == hotKeys_.end())
            return;

        Option *opt = hotKeys_[key];

        if (!opt->isVisible()) {
            opt->setVisible(true);
        }
    }

    virtual void handleTick(int elapsed) {}
    virtual void handleMouseDown(int x, int y, int button, const int modKeys) {}
    virtual void handleMouseUp(int x, int y, int button, const int modKeys) {}
    virtual void handleMouseMotion(int x, int y, int state, const int modKeys) {}

    //! Callback function : Childs can reimplement
    /*! 
     * Called just after the opening animation is played (if one has
     * been defined) and before the menu is rendered for the first time.
     */
    virtual void handleShow() {}

    //! Callback function : Childs can reimplement
    /*! 
     * Called each time a menu is rendered.
     */
    virtual void handleRender() {}

    //! Callback function : Childs can reimplement
    /*! 
     * Called just before the closing animation is played (if one has
     * been defined) and the menu closed.
     */
    virtual void handleLeave() {}

    //! Callback function : Childs can reimplement
    /*! 
     * Called when an action widget has been activated.
     * \param actionId The id of the actionWidget that was activated.
     * \param ctx A pointer to a context specific to the action
     * \param modKeys The state of all modifiers buttons
     */
    virtual void handleAction(const int actionId, void *ctx, const int modKeys) {}

    void selectToggleAction(int id) { group_.selectButton(id); }

protected:
    void redrawOptions();
    void needRendering();
    void addDirtyRect(int x, int y, int width, int height);

    virtual bool handleUnknownKey(Key key, const int modKeys) { return false;}

protected:
    MenuManager *menu_manager_;
    /*! A unique name to identify this menu.*/
    std::string name_;
    std::string showAnim_, leaveAnim_;
    /*! The list of all static widgets (MenuText).*/
    std::list<MenuText> statics_;
    /*! The list of all dynamic widgets (Option).*/
    std::list<ActionWidget *> actions_;
    /*! An association between key and option for hotkeys.*/
    std::map<Key, Option *> hotKeys_;
    /*! A group of mutual exclusive ToggleAction.*/
    Group group_;
    const char *parent_menu_;
    uint8 *background_;
    int clear_x_, clear_y_, clear_w_, clear_h_;
    /*! The id of the widget that currently has focus.*/
    int focusedWgId_;
};

#endif
