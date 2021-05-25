#pragma once

#include "boundaries.h"
#include "player.h"
#include "button.h"

class Loader{
    public:
        int playerStartingX, playerStartingY, player2StartingX, player2StartingY;
        bool playerCanMove, player2CanMove;
        int lSBLength, lSBLength2;
        Blocker * levelSpecificBlockers;
        Button * levelSpecificButtons;

        Loader(int psx, int psy, int ps2x, int ps2y, bool pcm, bool p2cm, int lsbl, Blocker * lsb, int lsbl2, Button * lsb2){
            playerStartingX = psx;
            playerStartingY = psy;
            player2StartingX = ps2x;
            player2StartingY = ps2y;
            playerCanMove = pcm;
            player2CanMove = p2cm;
            lSBLength = lsbl;
            levelSpecificBlockers = lsb;
            lSBLength2 = lsbl2;
            levelSpecificButtons = lsb2;
        }
};

//void loadLevel(Loader * l, Player * p);