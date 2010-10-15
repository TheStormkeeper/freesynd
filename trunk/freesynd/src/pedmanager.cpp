/************************************************************************
 *                                                                      *
 *  FreeSynd - a remake of the classic Bullfrog game "Syndicate".       *
 *                                                                      *
 *   Copyright (C) 2005  Stuart Binge  <skbinge@gmail.com>              *
 *   Copyright (C) 2005  Joost Peters  <joostp@users.sourceforge.net>   *
 *   Copyright (C) 2006  Trent Waddington <qg@biodome.org>              *
 *   Copyright (C) 2006  Tarjei Knapstad <tarjei.knapstad@gmail.com>    *
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

#include <stdio.h>
#include <assert.h>
#include "app.h"

PedManager::PedManager()
{
}

void PedManager::setPed(Ped *pedanim, unsigned short baseAnim)
{
    pedanim->setStandAnim(Weapon::Unarmed_Anim, 0 + baseAnim);
    pedanim->setWalkAnim(Weapon::Unarmed_Anim, 8 + baseAnim);
    pedanim->setStandAnim(Weapon::EnergyShield_Anim, 16 + baseAnim);
    pedanim->setStandAnim(Weapon::Pistol_Anim, 24 + baseAnim);
    pedanim->setStandAnim(Weapon::Uzi_Anim, 24 + baseAnim);
    pedanim->setStandAnim(Weapon::Shotgun_Anim, 24 + baseAnim);
    pedanim->setStandAnim(Weapon::Minigun_Anim, 32 + baseAnim);
    pedanim->setStandAnim(Weapon::Flamer_Anim, 40 + baseAnim);
    pedanim->setStandAnim(Weapon::LongRange_Anim, 48 + baseAnim);
    pedanim->setWalkAnim(Weapon::EnergyShield_Anim, 56 + baseAnim);
    pedanim->setWalkAnim(Weapon::Pistol_Anim, 64 + baseAnim);
    pedanim->setWalkAnim(Weapon::Uzi_Anim, 64 + baseAnim);
    pedanim->setWalkAnim(Weapon::Shotgun_Anim, 64 + baseAnim);
    pedanim->setWalkAnim(Weapon::Minigun_Anim, 72 + baseAnim);
    pedanim->setWalkAnim(Weapon::Flamer_Anim, 80 + baseAnim);
    pedanim->setWalkAnim(Weapon::LongRange_Anim, 88 + baseAnim);
    // I think 97 was the original pistol shoot anim, but it wasn't sexy enough.
    //pedanim->setStandFireAnim(Weapon::Laser_Anim, 96 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Pistol_Anim, 104 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Uzi_Anim, 104 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Shotgun_Anim, 104 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Gauss_Anim, 104 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Minigun_Anim, 112 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Laser_Anim, 120 + baseAnim);
    pedanim->setStandFireAnim(Weapon::Flamer_Anim, 128 + baseAnim);
    pedanim->setStandFireAnim(Weapon::LongRange_Anim, 136 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Pistol_Anim, 144 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Uzi_Anim, 144 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Shotgun_Anim, 144 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Gauss_Anim, 144 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Minigun_Anim, 152 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Laser_Anim, 160 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::Flamer_Anim, 168 + baseAnim);
    pedanim->setWalkFireAnim(Weapon::LongRange_Anim, 176 + baseAnim);
    pedanim->setPickupAnim(192 + baseAnim);
    pedanim->setHitAnim(193 + baseAnim);
    // 197 - 200 vapourized
    // 201 sinking
    // 203 - die, 204 - dead, agent only(?)
    pedanim->setDieAgentAnim(203 + baseAnim);
    pedanim->setDeadAgentAnim(204 + baseAnim);
    pedanim->setDieAnim(205 + baseAnim);
    pedanim->setDeadAnim(206 + baseAnim);
    // 207 on fire
    // 208 walking on fire
    // 209 die burning
    // 210 dead and smoking
    // 236 persuaded
}

PedInstance *PedManager::loadInstance(uint8 * data, int map)
{
    Mission::LEVELDATA_PEOPLE * gamdata =
        (Mission::LEVELDATA_PEOPLE *) data;

    if (gamdata->type == 0)
        return NULL;

    // TODO: correct initialization for animations based on current state
    int dir = gamdata->orientation >> 5;
    int hp = 0;

    Ped *pedanim = new Ped();
    setPed(pedanim, READ_LE_UINT32(gamdata->index_base_anim));
    PedInstance *newped = pedanim->createInstance(map);
    if (gamdata->type_ped == 0x02)
        hp = 10;
    else
        hp = 2;
    newped->setStartHealth(hp);

    if (gamdata->state == 0x11) {
        newped->setDrawnAnim(PedInstance::DeadAnim);
        newped->setHealth(-1);
    } else
        newped->setHealth(hp);
    // this is tile based Z we get, realword Z is in gamdata,
    // for correct calculations of viewpoint, target hit etc.
    // Zr = (Zt * 128) / 256
    int z = READ_LE_UINT16(gamdata->mapposz) >> 7;
    z--;
    int oz = gamdata->mapposz[0] & 0x7F;
    newped->setVisZ(z);
    if (oz > 0)
        z++;
    //printf("x %i y %i z %i ox %i oy %i oz %i\n", gamdata->mapposx[1], gamdata->mapposy[1], z, gamdata->mapposx[0], gamdata->mapposy[0], oz);
    newped->setPosition(gamdata->mapposx[1], gamdata->mapposy[1],
                        z, gamdata->mapposx[0],
                        gamdata->mapposy[0], oz);
    newped->setDirection(dir);
    switch (gamdata->type_ped) {
        case 0x01:
            newped->setMainType(m_tpPedestrian);
            break;
        case 0x02:
            newped->setMainType(m_tpAgent);
            break;
        case 0x04:
            newped->setMainType(m_tpPolice);
            break;
        case 0x08:
            newped->setMainType(m_tpGuard);
            break;
    }
    //newped->setSubType(gamdata->status);

    newped->setAllAdrenaLevels(gamdata->adrena_amount,
        gamdata->adrena_dependency, gamdata->adrena_effect);
    newped->setAllInteliLevels(gamdata->inteli_amount,
        gamdata->inteli_dependency, gamdata->inteli_effect);
    newped->setAllPercepLevels(gamdata->percep_amount,
        gamdata->percep_dependency, gamdata->percep_effect);

    return newped;
}