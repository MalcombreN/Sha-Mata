#include "pion.hh"
#include <iostream>

GLuint Pion::_piece_pion_lance_tete;
GLuint Pion::_piece_pion_lance;
GLuint Pion::_piece_pion_pied;
GLuint Pion::_piece_pion_jambe1;
GLuint Pion::_piece_pion_jambe2;
GLuint Pion::_piece_pion_corps;
GLuint Pion::_piece_pion_tete;
GLuint Pion::_piece_pion_epaules;
GLuint Pion::_piece_pion_main;
	

Pion::Pion(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::pion ,case_support , joueur ),
	pion_angle_doigt ( 0.0f),
	pion_angle_main (0.0f),
	pion_angle_fix (60.0f),
	pion_angle_bras (0.0f),
	pion_angle_bras2 (0.0f),
	pion_angle_bras_retour (0.0f),
	pion_angle_bras_retour_bis (0.0f),
	pion_angle_bras_retour_fin (0.0f),
	pion_angle_corps(0.0f),
	pion_angle_corps_retour (0.0f),
	pion_angle_genoux (0.0f),
	pion_angle_genoux_retour (0.0f),
	pion_distance_corps (0.0f),
	pion_distance_corps_retour (0.0f),
	action_pion (false),
	fin_phase1 (false),
	fin_phase2 (false),
	fin_phase3 (false),
	fin_phase4 (false),
	fin_phase5 (false),
	action_pion_fin (false)
{}

void Pion::load_piece()
{
	Pion::_piece_pion_lance_tete= glGenLists(1);
	glNewList(Pion::_piece_pion_lance_tete,GL_COMPILE);   Pion_DrawLanceTete(); glEndList();
	
	Pion::_piece_pion_lance= glGenLists(1);
	glNewList(Pion::_piece_pion_lance,GL_COMPILE);   Pion_DrawLance(); glEndList();

	Pion::_piece_pion_pied= glGenLists(1);
	glNewList(Pion::_piece_pion_pied,GL_COMPILE);   Pion_DrawPied(); glEndList();
	
	Pion::_piece_pion_jambe1= glGenLists(1);
	glNewList(Pion::_piece_pion_jambe1,GL_COMPILE);   Pion_DrawJambre(15);glEndList();
	
	
	Pion::_piece_pion_jambe2= glGenLists(1);
	glNewList(Pion::_piece_pion_jambe2,GL_COMPILE);   Pion_DrawJambre(-15);glEndList();
	
	
	Pion::_piece_pion_corps= glGenLists(1);
	glNewList(Pion::_piece_pion_corps,GL_COMPILE);   Pion_DrawCorps(); glEndList();
	
	
	Pion::_piece_pion_tete= glGenLists(1);
	glNewList(Pion::_piece_pion_tete,GL_COMPILE);   Pion_DrawTete(); glEndList();
	
	
	Pion::_piece_pion_epaules= glGenLists(1);
	glNewList(Pion::_piece_pion_epaules,GL_COMPILE);   Pion_DrawEpaule(); glEndList();
	
	
	Pion::_piece_pion_main= glGenLists(1);
	glNewList(Pion::_piece_pion_main,GL_COMPILE);   Pion_DrawMain(60); glEndList();
	

}

void Pion::affiche_piece()
{
	DrawPion();
	if(fin_phase3){
		set_a_attaquer();
	}
	if(action_pion_fin){
		set_anim_fini();
		pion_angle_doigt= 0.0f;
		pion_angle_main = 0.0f;
		pion_angle_fix =60.0f;
		pion_angle_bras =0.0f;
		pion_angle_bras2 =0.0f;
		pion_angle_bras_retour =0.0f;
		pion_angle_bras_retour_bis =0.0f;
		pion_angle_bras_retour_fin =0.0f;
		pion_angle_corps=0.0f;
		pion_angle_corps_retour =0.0f;
		pion_angle_genoux =0.0f;
		pion_angle_genoux_retour =0.0f;
		pion_distance_corps =0.0f;
		pion_distance_corps_retour =0.0f;
		action_pion =false;
		fin_phase1 =false;
		fin_phase2 =false;
		fin_phase3 =false;
		fin_phase4 =false;
		fin_phase5 =false;
		action_pion_fin=false;
	
	}
	
}


void Pion::animation()
{
	action_pion=true;
}

void Pion::DrawPion() {
	glColor3f(1,1,1);
	glPushMatrix();
	{
		glTranslatef(-0.4, 0.4, -0.6);
		//==================Partie action==================
		glPushMatrix();
		{
			glPushMatrix();
			{	//Partie Animation
				//Phase 2 ======Rotation du corps=========
				if (fin_phase1) {
					if(pion_angle_corps < 5)
						pion_angle_corps += 0.1;
					if (pion_distance_corps < 0.3)
						pion_distance_corps += 0.005;
					if (pion_angle_genoux < 5)
						pion_angle_genoux += 0.05;
				}
				if ((pion_angle_genoux == 5) && (pion_distance_corps == 0.3) && (pion_angle_corps == 5)) {
					fin_phase2 = true;
				}
				if (fin_phase4) {
					if(pion_angle_corps_retour <5)
						pion_angle_corps_retour += 0.1;
					if (pion_distance_corps_retour < 0.3)
						pion_distance_corps_retour += 0.005;
					if (pion_angle_genoux_retour < 5)
						pion_angle_genoux_retour += 0.05;
				}
				if ((pion_distance_corps_retour >= 0.3) && (pion_angle_genoux_retour >= 5) && (pion_angle_corps_retour >= 5)) action_pion_fin = true;
					

				glTranslatef(0.65, 0.35, 0);
				glRotatef(pion_angle_genoux, 1, 0, 0);	//Rotation genoux (pas propre)
				glRotatef(-pion_angle_genoux_retour, 1, 0, 0);
				glCallList(_piece_pion_jambe1);//DrawJambre(15);

				glTranslatef(0, 0.55, 0.6);
				glRotatef(90, 0, 1, 0);

				glRotatef(-pion_angle_corps, 1, 0, 0);
				glRotatef(pion_angle_corps_retour, 1, 0, 0);
				glTranslatef(0, -pion_distance_corps, 0);
				glTranslatef(0, pion_distance_corps_retour, 0);
				//=========================================
				glCallList(_piece_pion_corps);//DrawCorps();
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, 2.6, 0.8);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -0.2, 0);
				glCallList(_piece_pion_epaules);//DrawEpaule();
				this->Pion_DrawBras_action();
				glTranslatef(0, 0.2, 0);
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2.6, -0.8);
				glTranslatef(0, 3.25, 0);
				glCallList(_piece_pion_tete);//DrawTete();


				//=============Partie symétrique===============
				glTranslatef(0, -5, 0.6);		//repositionner cette partie
				glTranslatef(0, 0.35, 0);
				glCallList(_piece_pion_jambe2);//DrawJambre(-15);

				glTranslatef(-0, 0.5, 0.6);
				glTranslatef(0, 2.6, -0.8 - 1.2);
				glRotatef(90, 0, 1, 0);

				//Phase 2 ======Rotation du corps========= 
				glRotatef(-pion_angle_corps, 1, 0, 0);
				//=========================================
				glTranslatef(0, -0.1, 0);
				glCallList(_piece_pion_epaules);//DrawEpaule();
				this->Pion_DrawBras();
				glTranslatef(0, 0.1, 0);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -2.6, 0.8 + 1.2);
			}
			glPopMatrix();

			glCallList(_piece_pion_pied);//DrawPied();
			glTranslatef(0, 0, 1.2);
			glCallList(_piece_pion_pied);//DrawPied();
			glTranslatef(0, 0, -1.2);
		}
		glPopMatrix();
		
		

	}
	glPopMatrix();

	if (get_joueur()) 	
		glCallList(Piece::_piece_piece_baseArgent);
	else
		glCallList(Piece::_piece_piece_baseOr);
	
}


//partie du pion

void Pion::Pion_DrawLanceTete() {
	glBindTexture (GL_TEXTURE_2D, textures[6]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glBegin(GL_TRIANGLES);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.4, 0);
		glTexCoord2f(0.5, 1.0); glVertex3f(0, 0, 0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0, 0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.4, 0);
		glTexCoord2f(0.5, 1.0); glVertex3f(0.2, 0, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, -0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.4, 0);
		glTexCoord2f(0.5, 1.0); glVertex3f(0, 0, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, 0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.4, 0);
		glTexCoord2f(0.5, 1.0); glVertex3f(0.2, 0, 0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0, -0.05);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.2, 0, 0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.2, 0, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, -0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0, -0.5, -0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0, -0.5, 0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, 0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0, -0.5, 0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.2, -0.5, 0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0, 0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.2, 0, 0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.2, -0.5, 0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.2, -0.5, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0, -0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0.2, 0, -0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.2, -0.5, -0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0, -0.5, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, -0.05);

		glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.5, 0.05);
		glTexCoord2f(0.0, 1.0); glVertex3f(0, -0.5, -0.05);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.2, -0.2, -0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.2, -0.2, 0.05);

		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawLance() {
	//Texture
	glBindTexture (GL_TEXTURE_2D, textures[5]);
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
	{
		float n = 0.1;
		int tmp = 1;
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 5) {
			if (tmp % 2 == 0) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n*Cos(j), 6, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(n*Cos(j), 6, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			tmp++;
		}
		glEnd();

		glTranslatef(0, 6, 0);


		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, 0);
		int compt = 1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(0.15*Cos(k), 0, 0.15*Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(0.15*Cos(k), 0, 0.15*Sin(k));
				compt++;
			}
		}
		glEnd();


		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 5) {
			if (tmp % 2 == 0) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(0.15*Cos(j), 0.2, 0.15*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(0.15*Cos(j), 0, 0.15*Sin(j));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(0.15*Cos(j), 0.2, 0.15*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(0.15*Cos(j), 0, 0.15*Sin(j));
			}
			tmp++;
		}
		glEnd();

		glTranslatef(0, 0.2, 0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, 0);
		compt = 1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(0.15*Cos(k), 0, 0.15*Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(0.15*Cos(k), 0, 0.15*Sin(k));
				compt++;
			}
		}
		glEnd();

		glTranslatef(-0.1, 0.4, 0);
		glCallList(_piece_pion_lance_tete);//DrawLanceTete();

		glTranslatef(0.1, -6.9, 0);

	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawPied() {
	glPushMatrix();
	{
		//=============Niveau plus bas==================
		glColor3f(0.4,0.4,0.4);
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {

			//==========Partie 1==========
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.1, i / 2);
				glVertex3f(i, 0, (i + 0.1) / 2);
			}

			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.1, 0.15);
				glVertex3f(i + 0.05, 0, 0.2);
			}

			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.1, (1 - i) - 0.05);
				glVertex3f(i + 0.05, 0, (1 - i));
			}

		}

		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//===========Partie 2 (Symétrique)============
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.1, -i / 2);
				glVertex3f(i, 0, -(i + 0.1) / 2);
			}

			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.1, -0.15);
				glVertex3f(i + 0.05, 0, -0.2);
			}

			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.1, -((1 - i) - 0.05));
				glVertex3f(i + 0.05, 0, -(1 - i));
			}
		}

		glEnd();


		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, 0.1, 0.0);
		glTexCoord2f(0.5, 1.0);glVertex3f(-0.15, 0, 0);
		glTexCoord2f(1.0, 0.0);glVertex3f(0.0, 0, 0.05);

		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, 0.1, 0.0);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.0, 0, -0.05);
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.15, 0, 0);

		glTexCoord2f(0.0, 0.0);glVertex3f(1, 0.1, 0);
		glTexCoord2f(0.5, 1.0);glVertex3f(1, 0, 0.05);
		glTexCoord2f(1.0, 0.0);glVertex3f(1, 0, -0.05);
		glEnd();

		//============Niveau 2================

		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {

			//==========Partie 1==========
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.15, i / 2);
				glVertex3f(i + 0.1, 0.1, i / 2);
			}
			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.15, 0.15);
				glVertex3f(i + 0.05, 0.1, 0.15);
			}
			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.15, (1 - i) - 0.05);
				glVertex3f(i + 0.05, 0.1, (1 - i) - 0.05);

			}

		}

		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//===========Partie 2 (Symétrique)============
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.15, -i / 2);
				glVertex3f(i + 0.1, 0.1, -i / 2);
			}
			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.15, -0.15);
				glVertex3f(i + 0.05, 0.1, -0.15);
			}
			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.15, -((1 - i) - 0.05));
				glVertex3f(i + 0.05, 0.1, -((1 - i) - 0.05));
			}
		}
		glEnd();

		//============Niveau 3================

		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//==========Partie 1==========
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.2, (i / 2));
				glVertex3f(i + 0.1, 0.15, i / 2);
			}
			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.2, 0.15);
				glVertex3f(i + 0.05, 0.15, 0.15);
			}
			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.2, (1 - i) - 0.05);
				glVertex3f(i + 0.05, 0.15, (1 - i) - 0.05);
			}
		}
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//===========Partie 2 (Symétrique)============
			if (i < 0.3) {
				glVertex3f(i + 0.1, 0.2, -i / 2);
				glVertex3f(i + 0.1, 0.15, -i / 2);
			}
			if ((i >= 0.35) && (i < 0.8)) {
				glVertex3f(i + 0.05, 0.2, -0.15);
				glVertex3f(i + 0.05, 0.15, -0.15);
			}
			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.2, -((1 - i) - 0.05));
				glVertex3f(i + 0.05, 0.15, -((1 - i) - 0.05));
			}
		}
		glEnd();

		//============Niveau 4================
		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//==========Partie 1==========
			if (i < 0.25) {
				glVertex3f(i + 0.1 + 0.05, 0.35, (i / 2));
				glVertex3f(i + 0.1, 0.2, (i / 2));
			}
			if ((i >= 0.25) && (i < 0.7)) {
				glVertex3f(i + 0.05 + 0.05 + 0.05, 0.35, 0.15);
				glVertex3f(i + 0.05 + 0.05, 0.2, 0.15);
			}
			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.35, (1 - i) - 0.05);
				glVertex3f(i + 0.05, 0.2, (1 - i) - 0.05);
			}
		}

		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
		for (float i = 0; i < 1; i += 0.05) {
			//===========Partie 2 (Symétrique)============
			if (i < 0.25) {
				glVertex3f(i + 0.1 + 0.05, 0.35, -i / 2);
				glVertex3f(i + 0.1, 0.2, -i / 2);
			}

			if ((i >= 0.25) && (i < 0.7)) {
				glVertex3f(i + 0.05 + 0.05 + 0.05, 0.35, -0.15);
				glVertex3f(i + 0.05 + 0.05, 0.2, -0.15);

			}

			if ((i >= 0.8) && (i < 1)) {
				glVertex3f(i + 0.05, 0.35, -((1 - i) - 0.05));
				glVertex3f(i + 0.05, 0.2, -((1 - i) - 0.05));
			}
		}
		glEnd();

		glBegin(GL_POLYGON);

		glVertex3f(0.15, 0.35, 0);
		glVertex3f(0.4, 0.35, 0.15);
		glVertex3f(0.85, 0.35, 0.15);
		glVertex3f(0.85, 0.35, -0.15);
		glVertex3f(0.4, 0.35, -0.15);
		glEnd();


	}
	glPopMatrix();
}

void Pion::Pion_DrawJambre(float degree) {
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[7]);
	glEnable(GL_TEXTURE_2D);
	//==============Molet==================

	glCallList(Piece::_piece_piece_cylindre1);//Piece::DrawCylindre(0.125, 0.3, 0.7);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glColor3f(0.5,0.5,0.5);
		glTranslatef(0, 0.7, 0);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, 0.8, 0);
	glRotatef(degree, 1, 0, 0);
	glCallList(Piece::_piece_piece_cylindre2);//DrawCylindre(0.3,0.4,0.65);
	glRotatef(-degree, 1, 0, 0);
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawCorps() {
	glBindTexture (GL_TEXTURE_2D, textures[8]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//FACE ABCD (plus bas)
		glTexCoord2f(0.0, 1.0);glVertex3f(0.4,0,0.2); //B
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 0, 0.2);//A
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 0, -0.2); //D
		glTexCoord2f(1.0, 1.0);glVertex3f(0.4,0,-0.2); //C

		//FACE A'B'C'D'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6,0.1,0.4); //B'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 0.1, 0.4); //A'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 0.1, -0.4); //D'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6,0.1,-0.4); //C'
		
		//FACE A'ABB'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.6, 0.1, 0.4); //A'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 0, 0.2);//A
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0, 0.2); //B
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6, 0.1, 0.4); //B'

		//FACE B'BCC'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6, 0.1, 0.4); //B'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 0, 0.2); //B
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0, -0.2); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6, 0.1, -0.4); //C'

		//FACE C'CDD'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6, 0.1, -0.4); //C'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 0, -0.2); //C
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 0, -0.2); //D
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.6, 0.1, -0.4); //D'

		//FACE D'DAA'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.6, 0.1, -0.4); //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 0, -0.2); //D
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 0, 0.2);//A
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.6, 0.1, 0.4); //A'

		//==================================
		//FACE GHEF (plus HAUT)
		glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 2.5, -0.2); //G
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 2.5, -0.2); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 2.5, 0.2);//E
		glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 2.5, 0.2); //F

		//FACE A'B'C'D'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6, 2.4, -0.4); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 2.4, -0.4); //H'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 2.4, 0.4); //E'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6, 2.4, 0.4); //F'

		//FACE EE'F'F
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.4, 2.5, -0.2); //E
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 2.4, -0.4); //E'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.6, 2.4, -0.4); //F'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 2.5, -0.2); //F
		//FACE FF'G'G
		glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 2.5, -0.2); //F
		glTexCoord2f(0.0, 0.0);glVertex3f(0.6, 2.4, -0.4); //F'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.6, 2.4, 0.4); //G'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 2.5, 0.2); //G
		//FACE GG'H'H
		glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 2.5, 0.2); //G
		glTexCoord2f(0.0, 0.0);glVertex3f(0.6, 2.4, 0.4); //G'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 2.4, 0.4); //H'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.4, 2.5, 0.2);//H
		//FACE HH'E'E
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.4, 2.5, 0.2);//H
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 2.4, 0.4); //H'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 2.4, -0.4); //E'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.4, 2.5, -0.2); //E

		//=====================================
		
		//FACE E'A'B'F'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.6, 2.4, 0.4); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 0.1, 0.4); //A'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.6, 0.1, 0.4); //B'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6, 2.4, 0.4); //F'
		
		//FACE F'B'C'G'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6, 2.4, 0.4); //F'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.6, 0.1, 0.4); //B'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.6, 0.1, -0.4); //C'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.6, 2.4, -0.4); //G'
		//FACE G'C'D'H'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.6, 2.4, -0.4); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.6, 0.1, -0.4); //C'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 0.1, -0.4); //D'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.6, 2.4, -0.4); //H'
		//FACE H'D'A'E'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.6, 2.4, -0.4); //H'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.6, 0.1, -0.4); //D'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.6, 0.1, 0.4); //A'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.6, 2.4, 0.4); //E'
		
		//================NECK=================

		glTexCoord2f(0.0, 1.0);glVertex3f(0.2, 2.6, -0.1); //G"
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.2, 2.6, -0.1); //H"
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.2, 2.6, 0.1);//E"
		glTexCoord2f(1.0, 1.0);glVertex3f(0.2, 2.6, 0.1); //F"

		//E"EFF"
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.2, 2.6, 0.1);//E"
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 2.5, 0.2);//E
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 2.5, 0.2); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(0.2, 2.6, 0.1); //F"
		//F"FGG"
		glTexCoord2f(0.0, 1.0);glVertex3f(0.2, 2.6, 0.1); //F"
		glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 2.5, 0.2); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 2.5, -0.2); //G
		glTexCoord2f(1.0, 1.0);glVertex3f(0.2, 2.6, -0.1); //G"
		//G"GHH"
		glTexCoord2f(0.0, 1.0);glVertex3f(0.2, 2.6, -0.1); //G"
		glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 2.5, -0.2); //G
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 2.5, -0.2); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.2, 2.6, -0.1); //H"
		//H"HEE"
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.2, 2.6, -0.1); //H"
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.4, 2.5, -0.2); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.4, 2.5, 0.2);//E
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.2, 2.6, 0.1);//E"

		glEnd();
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawTete() {
	
	glPushMatrix();
	{
		glColor3ub(254,195,172);
		glCallList(Piece::_piece_piece_sphere4);//DrawSphere(0.65);
		glColor3f(0.5,0.5,0.5);
		//pour ajouter les yeux
		//glTranslatef(1.5,0,0.8);
		//DrawSphere(0.05);
		

	}
	glPopMatrix();
}

void Pion::Pion_DrawEpaule() {
	glBindTexture (GL_TEXTURE_2D, textures[8]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTranslatef(-0.2, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);glVertex3f(0, 0, -0.4); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(0, 0, 0.4); //F'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.3, -0.2, 0.4); //I
		glTexCoord2f(1.0, 1.0);glVertex3f(0.3, -0.2, -0.4); //J

		glTexCoord2f(0.0, 1.0);glVertex3f(0.3, -0.2, -0.4); //J
		glTexCoord2f(0.0, 0.0);glVertex3f(0.3, -0.2, 0.4); //I
		glTexCoord2f(1.0, 0.0);glVertex3f(0.3,-1.5,0.4);		//K
		glTexCoord2f(1.0, 1.0);glVertex3f(0.3,-1.5,-0.4);	//L

		glTexCoord2f(0.0, 1.0);glVertex3f(0.3, -1.5, 0.4);	//K
		glTexCoord2f(0.0, 0.0);glVertex3f(0,-1.8,0.4);		//M
		glTexCoord2f(1.0, 0.0);glVertex3f(0,-1.8,-0.4);	//N
		glTexCoord2f(1.0, 1.0);glVertex3f(0.3, -1.5, -0.4);	//L
		
		//F'MKI
		glTexCoord2f(0.0, 1.0);glVertex3f(0, 0, 0.4); //F'
		glTexCoord2f(0.0, 0.0);glVertex3f(0, -1.8, 0.4);		//M
		glTexCoord2f(1.0, 0.0);glVertex3f(0.3, -1.5, 0.4);		//K
		glTexCoord2f(1.0, 1.0);glVertex3f(0.3, -0.2, 0.4); //I

		//G'JLN
		glTexCoord2f(0.0, 1.0);glVertex3f(0, 0, -0.4); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.3, -0.2, -0.4); //J
		glTexCoord2f(1.0, 0.0);glVertex3f(0.3, -1.5, -0.4);	//L
		glTexCoord2f(1.0, 1.0);glVertex3f(0, -1.8, -0.4);	//N
		glEnd();

		glTranslatef(0.2, 0, 0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawDoigt(GLfloat a) {
	glColor3ub(254,195,172);
	glPushMatrix();
	{
		//premiere phalange
		glRotatef(a, 1, 0, 0);
		glCallList(_piece_piece_phallanges);//DrawPhalange();
		//Deuxieme
		glTranslatef(0, 0.07, 0); 
		glRotatef(a, 1, 0, 0);
		glCallList(_piece_piece_phallanges);//DrawPhalange();
		//Troisieme
		glTranslatef(0, 0.07, 0);
		glRotatef(a, 1, 0, 0);
		glCallList(_piece_piece_phallanges);//DrawPhalange();
		glTranslatef(0, -0.07*2, 0);
	}
	glPopMatrix();
}

void Pion::Pion_DrawMain(GLfloat a) {
	glColor3ub(254,195,172);
	//pour la paume
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//Face devant
		glVertex3f(0,0,0);
		glVertex3f(0, -0.32, 0);
		glVertex3f(0.27, -0.32, 0);
		glVertex3f(0.27,0,0);
		//Face droite
		glVertex3f(0.27, 0, 0);
		glVertex3f(0.27, -0.32, 0);
		glVertex3f(0.27,-0.32,-0.05);
		glVertex3f(0.27, 0, -0.05);
		//Face derriere
		glVertex3f(0.27, 0, -0.05);
		glVertex3f(0.27, -0.32, -0.05);
		glVertex3f(0,-0.32,-0.05);
		glVertex3f(0, 0, -0.05);
		//Face gauche
		glVertex3f(0, 0, -0.05);
		glVertex3f(0, -0.32, -0.05);
		glVertex3f(0, -0.32, 0);
		glVertex3f(0, 0, 0);
		//Face en haut
		glVertex3f(0, 0, 0);
		glVertex3f(0.27, 0, 0);
		glVertex3f(0.27, 0, -0.05);
		glVertex3f(0, 0, -0.03);
		//Face en bas
		glVertex3f(0, -0.32, -0.05);
		glVertex3f(0.27, -0.32, -0.05);
		glVertex3f(0.27, -0.32, 0);
		glVertex3f(0, -0.32, 0);
		glEnd();
		
	}
	glPopMatrix();

	//L'index
	DrawDoigt(a);
	//Majeur
	glTranslatef(0.07, 0, 0);
	DrawDoigt(a);
	//Anuaire
	glTranslatef(0.07, 0, 0);
	DrawDoigt(a);
	//Auriculaire
	glTranslatef(0.07, 0, 0); 
	DrawDoigt(a);

	glTranslatef(-0.21, 0, 0); //Retour à l'origine

	// pour la puce
		
	glPushMatrix();
	{
		glTranslatef(-0, -0.16, 0);
		glRotatef(a, 0, 1,0 );
		glTranslatef(-0.08, 0, 0);
		glPushMatrix();
		{
			glBegin(GL_QUADS);
			//======Face devant======
			glVertex3f(0, 0.07, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0.08, 0, 0);
			glVertex3f(0.08, 0.07, 0);
			//======Face droite======
			glVertex3f(0.08, 0.07, 0);
			glVertex3f(0.08, 0, 0);
			glVertex3f(0.08, 0, -0.05);
			glVertex3f(0.08, 0.07, -0.05);
			//======Face derriere=====
			glVertex3f(0.08, 0.07, -0.05);
			glVertex3f(0.08, 0, -0.05);
			glVertex3f(0, 0, -0.05);
			glVertex3f(0, 0.07, -0.05);
			//======Face gauche======
			glVertex3f(0, 0.07, -0.05);
			glVertex3f(0, 0, -0.05);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0.07, 0);
			//=======Face haut=======
			glVertex3f(0, 0.07, -0.05);
			glVertex3f(0, 0.07, 0);
			glVertex3f(0.08, 0.07, 0);
			glVertex3f(0.08, 0.07, -0.05);
			//=======Face bas========
			glVertex3f(0.06, 0, -0.05);
			glVertex3f(0.06, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, -0.05);
			glEnd();
		}
		glPopMatrix();
		glTranslatef(0.08, 0.16, 0);
		
		glTranslatef(-0.08, -0.09, 0);
		glRotatef(a, 1, 0, 0);
		glCallList(Piece::_piece_piece_phallanges);//DrawPhalange();
		glTranslatef(0.08, 0.09, 0);
		
		glTranslatef(-0.08, -0.04, 0);
		glRotatef(a, 1, 0, 0);
		glCallList(Piece::_piece_piece_phallanges);//DrawPhalange();
		glTranslatef(0.08, 0.04, 0);
		
	}
	glPopMatrix();
	
	glColor3ub(255,255,255);
}

void Pion::Pion_DrawBras() {	
	glBindTexture (GL_TEXTURE_2D, textures[8]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);	glVertex3f(0.1, -0.2, -0.4); //J
		glTexCoord2f(0.0, 0.0);	glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(1.0, 0.0); glVertex3f(0.9,-0.2,0.4);  //P
		glTexCoord2f(1.0, 1.0); glVertex3f(0.9,-0.2,-0.4); //O

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9,-0.7,0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9,-0.7,-0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1,-0.7,0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1,-0.7,-0.4); //T
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.7, -0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.7, 0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.2, 0.4);  //P

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.7, -0.4); //Q
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1, -0.7, -0.4); //T
		glTexCoord2f(1.0, 1.0);glVertex3f(0.1, -0.2, -0.4); //J
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, textures[7]);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.5,-0.7,0);
		glRotatef(pion_angle_bras, 1, 0, 0); //ici pour l'Animation des bras	
		glRotatef(-pion_angle_bras_retour_fin, 1, 0, 0);
		glRotatef(180, 1, 0, 0);
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.2, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.5,0.5,0.5);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -0.8, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.5,0.5,0.5);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		//==Pour inserer la main
		glTranslatef(-0.15, -0.45, 0);
		glRotatef(-180, 1, 0, 0);
		glDisable(GL_TEXTURE_2D);
		glCallList(_piece_piece_mains2);//DrawMain(angle_fix);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.15, 0.45, 0);

		glTranslatef(-0.5, 2.5, 0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pion::Pion_DrawBras_action() {
	glBindTexture (GL_TEXTURE_2D, textures[8]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);	glVertex3f(0.1, -0.2, -0.4); //J
		glTexCoord2f(0.0, 0.0);	glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(1.0, 0.0); glVertex3f(0.9,-0.2,0.4);  //P
		glTexCoord2f(1.0, 1.0); glVertex3f(0.9,-0.2,-0.4); //O

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9,-0.7,0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9,-0.7,-0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1,-0.7,0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1,-0.7,-0.4); //T
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.7, -0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.7, 0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.2, 0.4);  //P

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.7, -0.4); //Q
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1, -0.7, -0.4); //T
		glTexCoord2f(1.0, 1.0);glVertex3f(0.1, -0.2, -0.4); //J
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, textures[7]);
		glEnable(GL_TEXTURE_2D);
		
		glTranslatef(0.5, -0.7, 0);			//T1
		glRotatef(pion_angle_bras, 1, 0, 0); //ici pour l'Animation des bras	
		glRotatef(-pion_angle_bras_retour, 1, 0, 0);
		glRotatef(pion_angle_bras_retour_bis, 1, 0, 0);
		glRotatef(-pion_angle_bras_retour_fin, 1, 0, 0);
		glRotatef(180, 1, 0, 0);			//R1
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);			//A_R1
		glTranslatef(0, -1.2, 0);			//T2
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.5,0.5,0.5);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glRotatef(90, 1, 0, 0);				//R2
		glPushMatrix();
		{
			glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
			glTranslatef(0, 0.8, 0);		//T3
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.5,0.5,0.5);
			glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
			glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
		}
		glRotatef(-90, 1, 0, 0);			//A_R2
		//==Pour inserer la main
		glTranslatef(-0.15, 0.15, 0.5);		//T4
		glRotatef(90, 1, 0, 0);				//R3
		glRotatef(-90, 0, 1, 0);			//R4
		glDisable(GL_TEXTURE_2D);
		DrawMain(pion_angle_doigt);	//ici pour l'animation des doigt de la main
		glEnable(GL_TEXTURE_2D);
		//Ainimation du pion
		if (action_pion) {
			//PHASE 1
			if (pion_angle_doigt < 70){
				pion_angle_doigt++;
				if (pion_angle_doigt == 70) fin_phase1 = true;
			}
			//PHASE 2
			if (fin_phase1) {
				if (pion_angle_bras < 80) {
					pion_angle_bras++;
					if (pion_angle_bras == 80) fin_phase2 = true;
				}
			}
			//PHASE 3 
			if (fin_phase2) {
				if (pion_angle_bras_retour < 70) {
					pion_angle_bras_retour++;
					if (pion_angle_bras_retour == 70) fin_phase3 = true;
				}
			}
			//PHASE 4
			if (fin_phase3) {
				if (pion_angle_bras_retour_bis < 70) {
					pion_angle_bras_retour_bis++;
					if (pion_angle_bras_retour_bis == 70) fin_phase4 = true;
				}
			}
			//PHASE 5
			if (fin_phase4) {
				if (pion_angle_bras_retour_fin < 80) {
					pion_angle_bras_retour_fin++;
				}
			}

		}
			
		glRotatef(90, 0, 1, 0);				//A_R4
		glRotatef(-90, 1, 0, 0);			//A_R3
		glTranslatef(0.15, -0.15, -0.5);	//A_T4
		glPopMatrix();


		glTranslatef(0, -0.8, 0);			//A_T3
		glTranslatef(0, 1.2, 0);			//A_T2
		glTranslatef(-0.5, 0.7, 0);			//A_T1

		glRotatef(pion_angle_bras_retour, 1, 0, 0);	//animation pour la lance maintien la meme direction
		glRotatef(-pion_angle_bras_retour_bis, 1, 0, 0);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.2, -2.2, 0.2);

		
		glCallList(_piece_pion_lance);//DrawLance();

	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

