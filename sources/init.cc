#include "init.hh"

Jeu echecs;
GLdouble Coef_screen_size;
int largeur;
int hauteur;

extern GLuint textures[30];
extern	TEXTURE_STRUCT * T_base;
extern	TEXTURE_STRUCT * T_base_bis;
	//=====Texture pour la tour=====
extern	TEXTURE_STRUCT * T_Tour;
extern	TEXTURE_STRUCT * T_Tour0;
extern	TEXTURE_STRUCT * T_Canon;
extern	TEXTURE_STRUCT * T4;
	//=====Texture pour le pion=====
extern	TEXTURE_STRUCT * T_pion;
extern	TEXTURE_STRUCT * T_pion0;
extern	TEXTURE_STRUCT * T_pion_lance;
extern	TEXTURE_STRUCT * T_pion_lancetete;
	//=====Texture pour le fou =====
extern	TEXTURE_STRUCT * T_Fou_dague1;
extern	TEXTURE_STRUCT * T_Fou_dague2;
extern	TEXTURE_STRUCT * T_Fou1;
extern	TEXTURE_STRUCT * T_Fou2;
extern	TEXTURE_STRUCT * T_Fou_chapeau1;
extern	TEXTURE_STRUCT * T_Fou_chapeau2;
extern	TEXTURE_STRUCT * T_Fou_corps1;
extern	TEXTURE_STRUCT * T_Fou_corps2;;

//=====Texture pour la reine =====
extern	TEXTURE_STRUCT * T_Reine_bras;
extern	TEXTURE_STRUCT * T_Reine_arc;
extern	TEXTURE_STRUCT * T_Reine_corps;
extern	TEXTURE_STRUCT * T_Reine_robe;

//=====Texture pour le roi =====
extern	TEXTURE_STRUCT * T_Roi_corps;
extern	TEXTURE_STRUCT * T_Roi_bras;
extern	TEXTURE_STRUCT * T_Roi_epee;
extern	TEXTURE_STRUCT * T_Roi_epee0;

//=====Texture pour le cavalier =====
extern	TEXTURE_STRUCT * T_Cavalier_corps1;
extern	TEXTURE_STRUCT * T_Cavalier_corps2;
extern	TEXTURE_STRUCT * T_Cavalier_lance;
	
//=====Texture pour le logo=========
extern	TEXTURE_STRUCT * T_logo;

int notre_init(int argc, char** argv, void (*DrawGLScene)())
{
    glutInit( &argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //taille et position de la fenetre
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(0,0);

    //creer la fenetre et son titre
    glutCreateWindow("sāh māta");

    //affiche la scene dans la fenetre
    glutDisplayFunc(DrawGLScene);
    glutIdleFunc(DrawGLScene);

    //lorsque la fenetre sera redimensionner on fais appel a redimensionne
    glutReshapeFunc(Redimensionne);

    //pour les action lors des frappes de touches
    glutKeyboardFunc(&touche_pressee);
    glutSpecialFunc(&vClavier);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    //affiche le fond d'écran noir
    GLfloat red = 0.67;
    GLfloat green = 0.84;
    GLfloat blue = 0.90;
    GLfloat alpha =1;
    glClearColor(red,green,blue,alpha);

    //lumiere ambiante generale
    float ambiant[]= {1.,1.,1.,1.};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiant);

	//MENU
	createMenu();

	//TEXTURES
	load_textures();
	

    //"lance l'execution"
    echecs.load_entering_screen();
    glutMainLoop();


    return 1;
}

GLvoid Redimensionne(GLsizei Width, GLsizei Height)
{
	if (Width<600)
		Width=600;
	if (Height<600)
		Height=600;
		
	largeur=Width;
	hauteur=Height;
	
	Coef_screen_size = (Width/Height);
	
	glutReshapeWindow( Width, Height);
	
		
    glViewport(0, 0, Width,  Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //permet de garder le ratio ET GERER LE "PROCHE" ET LE "LOIN"
    gluPerspective(60, (GLdouble)Width/Height , 0.5 ,120);
	
    //on se remet en mode vu
    glMatrixMode(GL_MODELVIEW);
}


void createMenu(void)
{
	
	// Sous-menu Couleur Niveau 2
	int menu_couleurs = glutCreateMenu(&menu);
	glutAddMenuEntry("Blanc (B)", 0);
	glutAddMenuEntry("Noir (N)", 1);
	
	// Sous-menu Pieces Niveau 2
	int menu_pieces = glutCreateMenu(&menu);
	
	glutAddMenuEntry("Pion (R)", 2);
	glutAddMenuEntry("Tour (T)", 3);
	glutAddMenuEntry("Cavalier (Y)", 4);
	glutAddMenuEntry("Fou (U)", 5);
	glutAddMenuEntry("Reine (I)", 6);
	glutAddMenuEntry("Roi (O)", 7);
					 
	// Menu de niveau 1
	glutCreateMenu(&menu);
	glutAddSubMenu("Couleurs", menu_couleurs);
	glutAddSubMenu("Pieces", menu_pieces);
	
	glutAddMenuEntry("Cancel (G)",8);
	glutAddMenuEntry("Clear (H)",9);
	glutAddMenuEntry("Default", 10);
	glutAddMenuEntry("Start",11);
	glutAddMenuEntry("retour",12);
	
	//Attacher au click droit
		
}

void menu(int value)
{
	echecs.gere_menu(value);
	glutPostRedisplay();
}	

void load_textures()
{
	
	
//PARAMETRAGE DES TEXTURES
	glGenTextures(30, textures);
	
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_base->width, T_base->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_base->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_base_bis->width, T_base_bis->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_base_bis->data);
	
	//==================Texture pour le tour====================
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Tour->width, T_Tour->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Tour->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Tour0->width, T_Tour0->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Tour0->data);

	//Texture pour le tour ---le canon
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Canon->width, T_Canon->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Canon->data);
	
	//==================Texture pour le pion====================	
	
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_pion_lance->width, T_pion_lance->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_pion_lance->data);
	
	
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_pion_lancetete->width, T_pion_lancetete->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_pion_lancetete->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_pion->width, T_pion->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_pion->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_pion0->width, T_pion0->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_pion0->data);
	
	//=================Pour le Fou ================
	//textures[0] : Texture pour la base 
	//textures[1] : Texture pour la base bis (non utilisé pour le moment)
	//textures[2] : Texture Tour
	//textures[3] : Texture Tour - 0
	//textures[4] : Texture Tour - Canon
	//textures[5] : Texture Pion - Lance
	//textures[6] : Texture Pion - Lance Tete
	//textures[7] : Texture Pion - Corp
	//textures[8] : Texture Pion - Bras et Jambre
	//textures[9] : Texture Fou - Dagues1
	//textures[10] : Texture Fou - Dagues2
	//textures[11] : Texture Fou - Chapeau1
	//textures[12] : Texture Fou - Chapeau2
	//textures[13] : Texture Fou - Corps1
	//textures[14] : Texture Fou - Corps2
	//textures[15] : Texture Reine - bras
	//textures[16] : Texture Reine - corps
	//textures[17] : Texture Reine - arc
	//textures[23] : Texture Roi - corps1
	//textures[24] : Texture Roi - corps2
	//textures[25] : Texture Roi - lance 
	
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_dague1->width, T_Fou_dague1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_dague1->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_dague2->width, T_Fou_dague2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_dague2->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_chapeau1->width, T_Fou_chapeau1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_chapeau1->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[12]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_chapeau2->width, T_Fou_chapeau2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_chapeau2->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[13]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_corps1->width, T_Fou_corps1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_corps1->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Fou_corps2->width, T_Fou_corps2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Fou_corps2->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Reine_bras->width, T_Reine_bras->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Reine_bras->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[16]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Reine_corps->width, T_Reine_corps->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Reine_corps->data);

	glBindTexture(GL_TEXTURE_2D, textures[17]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Reine_arc->width, T_Reine_arc->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Reine_arc->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[18]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Reine_robe->width, T_Reine_robe->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Reine_robe->data);

	glBindTexture(GL_TEXTURE_2D, textures[19]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Roi_corps->width, T_Roi_corps->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Roi_corps->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[20]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Roi_bras->width, T_Roi_bras->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Roi_bras->data);

	glBindTexture(GL_TEXTURE_2D, textures[21]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Roi_epee->width, T_Roi_epee->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Roi_epee->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[22]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Roi_epee0->width, T_Roi_epee0->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Roi_epee0->data);
	

	glBindTexture(GL_TEXTURE_2D, textures[23]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Cavalier_corps1->width, T_Cavalier_corps1->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Cavalier_corps1->data);
	
	glBindTexture(GL_TEXTURE_2D, textures[24]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Cavalier_corps2->width, T_Cavalier_corps2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Cavalier_corps2->data);

	glBindTexture(GL_TEXTURE_2D, textures[25]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_Cavalier_lance->width, T_Cavalier_lance->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_Cavalier_lance->data);

	glBindTexture(GL_TEXTURE_2D, textures[26]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 	GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T_logo->width, T_logo->height, 0, GL_RGB, GL_UNSIGNED_BYTE, T_logo->data);




	glEnable(GL_TEXTURE_2D);
}
