#ifndef __OPERATIONS
#define __OPERATIONS



#include <math.h>
#include "axes.hh"

//transaltions
void translation (GLfloat x,GLfloat y,GLfloat z);
void translationTR (GLfloat taille_base , GLfloat largeurx  , GLfloat longueury, GLfloat hauteurz  );

//aggrandissement
void aggrandissement (GLfloat ax,GLfloat ay,GLfloat az);

//rotation
void rotation (GLfloat angx,GLfloat angy,GLfloat angz);

//cisallements
void cisallementsur_yz (GLfloat y,GLfloat z);
void cisallementsur_xz (GLfloat x,GLfloat z);
void cisallementsur_xy (GLfloat x,GLfloat y);

//eloignement
void eloignement (GLfloat t);

//pour affichage des lignes et sommets
GLvoid perspective();

GLvoid blend();

GLvoid aff_axes();
#endif
