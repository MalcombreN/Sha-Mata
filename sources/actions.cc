#include "actions.hh"

//outils construction
extern bool activer_axes;
extern bool activer_perspective;
extern bool activer_blend;

//camera temporaire 

extern Jeu echecs; 

void vClavier(int key, int x, int y)
{
	usleep(100);
    switch (key) 
    {    
		case UP_ARROW :
			echecs.cam_verticale(5);
		break; 
		case DOWN_ARROW :
			echecs.cam_verticale(-5);
		break; 
		case LEFT_ARROW :
			echecs.cam_horizontale(5);
		break; 
		case RIGHT_ARROW :
			echecs.cam_horizontale(-5);
		break; 
		case GLUT_KEY_PAGE_UP :
			echecs.cam_rapprochement();
		break; 
		case GLUT_KEY_PAGE_DOWN :
			echecs.cam_eloignement();         	
		break; 
		
	}
}

void touche_pressee(unsigned char key, int x, int y) 
{
	usleep(100);
	switch (key) 
	{   
		//Quitter la fenetre 
		case ESCAPE: 
			echecs.game_exit();                   	
		break; 
		/*
		case A_Axes:
			if (activer_axes)
				activer_axes=false;
			else
				activer_axes=true;
		break;
		case  P_Perspectives:
			if (activer_perspective)
				activer_perspective=false;
			else
				activer_perspective=true;
		break;
		case  B_Blend:
			if (activer_blend)
				activer_blend=false;
			else
				activer_blend=true;
		break;
		*/
		
		case avanceZ:
			echecs.select_autre_case(0);
		break;
		case reculeS:
			echecs.select_autre_case(1);
		break;
		case gaucheQ:
			echecs.select_autre_case(2);
		break;
		case droiteD:
			echecs.select_autre_case(3);
		break;
		case ESPACE:
			echecs.lock_la_case();
		break;
		case resetcamA:
			echecs.reset_cam();
		break;
		
		//tmp
		case blancB:
			echecs.gere_menu(0);
		break;
		case noirN:
			echecs.gere_menu(1);
		break;
		case pionR:
			echecs.gere_menu(2);
		break;
		case tourT:
			echecs.gere_menu(3);
		break;
		case CavalierY:
			echecs.gere_menu(4);
		break;
		case fouU:
			echecs.gere_menu(5);
		break;
		case reineI:
			echecs.gere_menu(6);
		break;
		case roiO:
			echecs.gere_menu(7);
		break;
		case lastG:
			echecs.gere_menu(8);
		break;
		case resetH:
			echecs.gere_menu(9);
		break;		
	}	
}




//Souris pour bouger la caméra
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;

void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else 
		{
			if (state == GLUT_UP)
			{
				mouseLeftDown = false;
				echecs.clic(x,y);
			}
		}
			
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}
}

void mouseMotionCB(int x, int y)
{
	if (mouseLeftDown)
	{
		echecs.cam_horizontale((x - mouseX)/5);
		echecs.cam_verticale((y - mouseY)/5);
		
		mouseX = x;
		mouseY = y;
	}
}


