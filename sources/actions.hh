#pragma once

#include "touches.hh"

#include "jeu.hh"

/* ascii codes for various special keys */


//touches classiques
void touche_pressee(unsigned char key, int x, int y);

//touche speciales
void vClavier(int key, int x, int y);

//sourie
void mouseCB(int button, int state, int x, int y);
void mouseMotionCB(int x, int y);
