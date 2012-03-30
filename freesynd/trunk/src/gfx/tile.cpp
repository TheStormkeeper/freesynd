/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
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

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tile.h"


Tile::Tile(uint8 id, uint8 *tile_Data, bool all_alpha, EType type)
{
    i_id_ = id;
    e_type_ = type;
    a_pixels_ = new uint8[TILE_WIDTH * TILE_HEIGHT];
    memcpy(a_pixels_, tile_Data, TILE_WIDTH * TILE_HEIGHT);
    b_all_alpha_ = all_alpha;
}

Tile::~Tile() 
{
    delete[] a_pixels_;
}

bool Tile::drawTo(uint8 * screen, int swidth, int sheight, int x, int y,
                  bool clear)
{
    if (b_all_alpha_)
        return false;

    if (clear)
        memset(screen, 255, swidth * sheight);

    for (int j = 0; j < TILE_HEIGHT; j++) {
        if (y + j < 0)
            continue;
        if (y + j >= sheight)
            break;
        for (int i = 0; i < TILE_WIDTH; i++) {
            if (x + i < 0)
                continue;
            if (x + i >= swidth)
                break;
            uint8 c = a_pixels_[(TILE_HEIGHT - j - 1) * TILE_WIDTH + i];
            if (c != 255)
                screen[(y + j) * swidth + x + i] = c;
        }
    }

    return true;
}
