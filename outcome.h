/*
 * outcome.h
 *
 * Copyright 2019 James Mitchum Lee <jml184@cs18254kq>
 *
 *
 */


#ifndef outcome_H
#define outcome_H

#include "outcome.h"
#include "bitmap.h"
#include "led.h"

int get_result(int current, int opponent);

Player_Bitmap outcome(Player_Bitmap bitmap);




#endif


