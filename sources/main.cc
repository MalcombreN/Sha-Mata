#include "init.hh"
#include "VM_init.hh"
#include <string>

extern Jeu echecs;
	GLuint textures[30];
	TEXTURE_STRUCT * T_base;
	TEXTURE_STRUCT * T_base_bis;
	//=====Texture pour la tour=====
	TEXTURE_STRUCT * T_Tour;
	TEXTURE_STRUCT * T_Tour0;
	TEXTURE_STRUCT * T_Canon;
	TEXTURE_STRUCT * T4;
	//=====Texture pour le pion=====
	TEXTURE_STRUCT * T_pion;
	TEXTURE_STRUCT * T_pion0;
	TEXTURE_STRUCT * T_pion_lance;
	TEXTURE_STRUCT * T_pion_lancetete;
	//=====Texture pour le fou =====
	TEXTURE_STRUCT * T_Fou_dague1;
	TEXTURE_STRUCT * T_Fou_dague2;
	TEXTURE_STRUCT * T_Fou1;
	TEXTURE_STRUCT * T_Fou2;
	TEXTURE_STRUCT * T_Fou_chapeau1;
	TEXTURE_STRUCT * T_Fou_chapeau2;
	TEXTURE_STRUCT * T_Fou_corps1;
	TEXTURE_STRUCT * T_Fou_corps2;;

//=====Texture pour la reine =====
	TEXTURE_STRUCT * T_Reine_bras;
	TEXTURE_STRUCT * T_Reine_arc;
	TEXTURE_STRUCT * T_Reine_corps;
	TEXTURE_STRUCT * T_Reine_robe;

//=====Texture pour le roi =====
	TEXTURE_STRUCT * T_Roi_corps;
	TEXTURE_STRUCT * T_Roi_bras;
	TEXTURE_STRUCT * T_Roi_epee;
	TEXTURE_STRUCT * T_Roi_epee0;

//=====Texture pour le cavalier =====
	TEXTURE_STRUCT * T_Cavalier_corps1;
	TEXTURE_STRUCT * T_Cavalier_corps2;
	TEXTURE_STRUCT * T_Cavalier_lance;

//=====Texture pour logo=====
	TEXTURE_STRUCT * T_logo;
	
GLvoid Modelisation()
{
	VM_init();
	
	glPushMatrix();
		echecs.display();
	glPopMatrix();
	
	perspective();
	blend(); 
	aff_axes();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	//CHARGEMENT DES TEXTURES	
	//===========Pour la base=============
	T_base 				= readPpm("texture/silver.ppm");
	T_base_bis 			= readPpm("texture/or2.ppm");
	
	//===========Pour la Tour=============
	T_Tour 				= readPpm("texture/wall2.ppm");
	T_Tour0 			= readPpm("texture/wall.ppm");
	T_Canon 			= readPpm("texture/metal.ppm");
	
	//===========Pour le pion================
	T_pion_lance 		= readPpm("texture/metal.ppm");
	T_pion_lancetete 	= readPpm("texture/blanc.ppm");
	T_pion 				= readPpm("texture/silver.ppm");
	T_pion0 			= readPpm("texture/silver1.ppm");

	//===========Pour le Fou ================
	T_Fou_dague1 		= readPpm("texture/or3.ppm");
	T_Fou_dague2 		= readPpm("texture/or3.ppm");
	T_Fou_chapeau1 		= readPpm("texture/blood2.ppm");
	T_Fou_chapeau2 		= readPpm("texture/green2.ppm");
	T_Fou_corps1 		= readPpm("texture/green2.ppm");
	T_Fou_corps2 		= readPpm("texture/blood2.ppm");
	
	//=========== Pour la reine =============
	T_Reine_bras 		= readPpm("texture/red_sky1.ppm");
	T_Reine_corps 		= readPpm("texture/red_sky3.ppm");
	T_Reine_arc 		= readPpm("texture/star.ppm");
	T_Reine_robe 		= readPpm("texture/bleu.ppm");
	
	//============ Pour le roi =============
	T_Roi_corps 		= readPpm("texture/red_sky1.ppm");
	T_Roi_bras 			= readPpm("texture/star.ppm");;
	T_Roi_epee 			= readPpm("texture/silver.ppm");;
	T_Roi_epee0 		= readPpm("texture/or3.ppm");;
	
	//============Pour le cavalier==========
	T_Cavalier_corps1 	= readPpm("texture/silver1.ppm");
	T_Cavalier_corps2 	= readPpm("texture/silver.ppm");
	T_Cavalier_lance 	= readPpm("texture/star.ppm");
	
	//===========Pour le logo============
	T_logo = readPpm("texture/logo.ppm");
	
    return notre_init(argc, argv, &Modelisation);
}

