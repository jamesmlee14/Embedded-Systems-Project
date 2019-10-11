/*
 * player_assignment.h
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#ifndef PLAYER_ASSIGNMENT_H
#define PLAYER_ASSIGNMENT_H

#include "system.h"
#include "bitmap.h"

typedef struct player_info_s Player_Info;

struct player_info_s {
    Bitmap_Info bitmap;
    char is_player1;
    char is_player2;
};


/** runs the player assignment phase of the game. */
Player_Info player_assignment (Player_Info player);

#endif


