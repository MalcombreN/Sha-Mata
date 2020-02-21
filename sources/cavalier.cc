#include "cavalier.hh"
#include "iostream"

 GLuint Cavalier::_piece_cavalier_chevalPied;
 GLuint Cavalier::_piece_cavalier_chevalCorps;
 GLuint Cavalier::_piece_cavalier_chevalTete;
 GLuint Cavalier::_piece_cavalier_Jambe1;
 GLuint Cavalier::_piece_cavalier_Jambe2;
 GLuint Cavalier::_piece_cavalier_corps;
 GLuint Cavalier::_piece_cavalier_epaule;
 GLuint Cavalier::_piece_cavalier_brasGauche;
 GLuint Cavalier::_piece_cavalier_lance;
 GLuint Cavalier::_piece_cavalier_tete;

Cavalier::Cavalier(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::cavalier ,case_support , joueur ),
	_hauteur(0),
	_lock_bouger(true),
	cavalier_angle_cheval  (0.0f),
	cavalier_angle_cheval_retour  (0.0f),
	cavalier_angle_corps  (0.0f),
	cavalier_angle_corps_retour (0.0f),
	cavalier_attaque  (0.0f),
	cavalier_attaque_retour  (0.0f),
	cavalier_angle_pied_cheval  (0.0f),
	cavalier_angle_pied_cheval_retour (0.0f),
	action_cavaliers  (false),
	fin_phase1_cavaliers  (false),
	fin_phase2_cavaliers  (false),
	fin_phase3_cavaliers  (false),
	fin_phase4_cavaliers  (false),
	fin_action_cavaliers  (false)
{}



void Cavalier::load_piece(){
	Cavalier::_piece_cavalier_chevalPied= glGenLists(1);
	glNewList(_piece_cavalier_chevalPied,GL_COMPILE);	Cavalier_DrawChevalPied();	glEndList();
	Cavalier::_piece_cavalier_chevalCorps= glGenLists(1);
	glNewList(_piece_cavalier_chevalCorps,GL_COMPILE);	Cavalier_DrawChevalCorps();	glEndList();
	Cavalier::_piece_cavalier_chevalTete= glGenLists(1);
	glNewList(_piece_cavalier_chevalTete,GL_COMPILE);	Cavalier_DrawChevalTete();	glEndList();
	Cavalier::_piece_cavalier_lance= glGenLists(1);
	glNewList(_piece_cavalier_lance,GL_COMPILE);	Cavalier_DrawLance();		glEndList();
	Cavalier::_piece_cavalier_Jambe1= glGenLists(1);
	glNewList(_piece_cavalier_Jambe1,GL_COMPILE);	Cavalier_DrawJambre(45);		glEndList();
	Cavalier::_piece_cavalier_Jambe2= glGenLists(1);
	glNewList(_piece_cavalier_Jambe2,GL_COMPILE);	Cavalier_DrawJambre(-45);	glEndList();
	Cavalier::_piece_cavalier_corps= glGenLists(1);
	glNewList(_piece_cavalier_corps,GL_COMPILE);	Cavalier_DrawCorps();		glEndList();
	Cavalier::_piece_cavalier_epaule= glGenLists(1);
	glNewList(_piece_cavalier_epaule,GL_COMPILE);	Cavalier_DrawEpaule();		glEndList();
	Cavalier::_piece_cavalier_brasGauche= glGenLists(1);
	glNewList(_piece_cavalier_brasGauche,GL_COMPILE);	Cavalier_DrawBrasGauche();	glEndList();
	Cavalier::_piece_cavalier_tete= glGenLists(1);
	glNewList(_piece_cavalier_tete,GL_COMPILE);	Cavalier_DrawTete();	glEndList();
}


void Cavalier::affiche_piece()
{
	DrawCavaliers();
	if(fin_phase3_cavaliers){
		set_a_attaquer();
	}
	if(fin_action_cavaliers){
		set_anim_fini();
		cavalier_angle_cheval = 0.0f;
		cavalier_angle_cheval_retour = 0.0f;
		cavalier_angle_corps = 0.0f;
		cavalier_angle_corps_retour = 0.0f;
		cavalier_attaque = 0.0f;
		cavalier_attaque_retour = 0.0f;
		cavalier_angle_pied_cheval = 0.0f;
		cavalier_angle_pied_cheval_retour =0.0f; 
		action_cavaliers = false;
		fin_phase1_cavaliers = false;
		fin_phase2_cavaliers = false;
		fin_phase3_cavaliers = false;
		fin_phase4_cavaliers = false;
		fin_action_cavaliers = false;
	}


}

void Cavalier::animation()
{
	action_cavaliers = true;

}

void Cavalier::Cavalier_DrawJambre(float degree) {
	//==============Molet==================
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[24]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre1);//DrawCylindre(0.125, 0.3, 0.7);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTranslatef(0, 0.7, 0);
		glColor3f(0.4,0.4,0.4);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
	}
	glPopMatrix();
	glTranslatef(0, 0.8, 0);
	glRotatef(degree, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textures[24]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre2);//DrawCylindre(0.3,0.4,0.65);
	glDisable(GL_TEXTURE_2D);
	glRotatef(-degree, 1, 0, 0);
}

void Cavalier::Cavalier_DrawLance(){
	glColor3f(1,1,1);
	glPushMatrix();
	{
		glRotatef(-15,0,0,1);
		glTranslatef(0,-2.6,0.15);
		glBindTexture(GL_TEXTURE_2D, textures[25]);
		glEnable(GL_TEXTURE_2D);
		DrawCylindre(0.1,0.15,3);
		
		glTranslatef(0,2.4,0);
		
		glBegin(GL_TRIANGLE_FAN);
		//glColor3d(0,0,1);
		glTexCoord2f(0.5,1);
		glVertex3f(0, 5, 0);
		bool paire = true;
		for (int k = 0; k <= 360; k += 5) {
			//glColor3d(0,1,1);
			if(paire){
					glTexCoord2f(0,0);
					glVertex3f(0.5*Cos(k)/1.7, 0.5* 1, 0.5*Sin(k)/1.7);
					paire = true;
				}
				else{
					glTexCoord2f(1,0);
					glVertex3f(0.5*Cos(k)/1.7, 0.5* 1, 0.5*Sin(k)/1.7);
					paire = false;
				}
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glTranslatef(0,-2.4,0);
		
		
		glRotatef(15,0,0,1);
		glTranslatef(0,2.6,-0.15);
	}
	glPopMatrix();
}

void Cavalier::Cavalier_DrawTete() {
	
	glPushMatrix();
	{
		glColor3ub(254,195,172);
		Piece::DrawSphere(0.55);
		glColor3f(1,1,1);
	}
	glPopMatrix();
}

void Cavalier::Cavalier_DrawEpaule() {
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[23]);
		glEnable(GL_TEXTURE_2D);
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
		glDisable(GL_TEXTURE_2D);
		
		glTranslatef(0.2, 0, 0);
	}
	glPopMatrix();
}

void Cavalier::Cavalier_DrawCorps() {
	glBindTexture(GL_TEXTURE_2D, textures[23]);
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

void Cavalier::Cavalier_DrawBrasDroite() {
	
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, textures[23]);
		glEnable(GL_TEXTURE_2D);
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
		
		glTranslatef(0.5,-0.7,0);

		glRotatef(180, 1, 0, 0);
		glRotatef(cavalier_attaque,1,0,0);
		glRotatef(-cavalier_attaque_retour,1,0,0);
		glBindTexture(GL_TEXTURE_2D, textures[24]);
		glEnable(GL_TEXTURE_2D);
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glDisable(GL_TEXTURE_2D);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.2, 0);
		glColor3f(0.4,0.4,0.4);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, textures[24]);
		glEnable(GL_TEXTURE_2D);
		glRotatef(-90, 1, 0, 0);		//avantbras vers l'avant
		glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
		glDisable(GL_TEXTURE_2D);
		glTranslatef(0, -0.8, 0);
		glTranslatef(0,1.6,0);		//repositionner waist et main
		
		glColor3f(0.4,0.4,0.4);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1,1,1);
		
		//==Pour inserer la main
		
		glRotatef(180,0,0,1);
		glTranslatef(-0.15, -0.45, 0);
		glTranslatef(0.3,0,0);
		glRotatef(-180, 1, 0, 0);
		glRotatef(180,0,1,0);
		glCallList(Piece::_piece_piece_mains1);//DrawMain(30);
		glCallList(_piece_cavalier_lance);//Cavalier_DrawLance();
		glRotatef(-180,0,1,0);
		glRotatef(180, 1, 0, 0);
		glTranslatef(-0.3,0,0);
		glTranslatef(0.15, 0.45, 0);
		glRotatef(-180,0,0,1);
		glTranslatef(0,-1.6,0);			//inverse repostionnement
		glRotatef(90, 1, 0, 0);			//inverse avantbras

		glTranslatef(-0.5, 2.5, 0);
		
		glRotatef(-cavalier_attaque,1,0,0);
		glRotatef(cavalier_attaque_retour,1,0,0);
	}
	glPopMatrix();
	
}

void Cavalier::Cavalier_DrawBrasGauche() {
	
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, textures[23]);
		glEnable(GL_TEXTURE_2D);
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
		
		glBindTexture(GL_TEXTURE_2D, textures[24]);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.5, -0.7, 0);			//T1
		glRotatef(180, 1, 0, 0);			//R1 Grand bras
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);			//A_R1  grand bras
		glTranslatef(0, -1.2, 0);			//T2
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.4,0.4,0.4);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, textures[24]);
		glEnable(GL_TEXTURE_2D);
		glRotatef(120, 1, 0, 0);				//R2
		glRotatef(40,0,0,1);			//Main gauche sur le cheval
		
		glPushMatrix();
		{
			glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
			glTranslatef(0, 0.8, 0);		//T3
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.4,0.4,0.4);
			glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
			glColor3f(1,1,1);
			glBindTexture(GL_TEXTURE_2D, textures[23]);
			glEnable(GL_TEXTURE_2D);
		}
		glTranslatef(0.2,0,0);
		
		
		glRotatef(-120, 1, 0, 0);			//A_R2
		//=====Pour inserer la main======
		glTranslatef(-0.15, 0.15, 0.5);		//T4
		glRotatef(90, 1, 0, 0);				//R3
		glRotatef(-90, 0, 1, 0);			//R4
		
		glTranslatef(0.1,0,0.1);
		glRotatef(60,0,1,0);
		glDisable(GL_TEXTURE_2D);
		glCallList(Piece::_piece_piece_mains1);//DrawMain(30);	//ici pour l'animation des doigt de la main
		glRotatef(-60,0,1,0);
		glTranslatef(-0.1,0,-0.1);
		
		glRotatef(-40,0,0,1);			//inverse main gauche sur le cheval
		glRotatef(90, 0, 1, 0);				//A_R4
		glRotatef(-90, 1, 0, 0);			//A_R3
		glTranslatef(0.15, -0.15, -0.5);	//A_T4
		glPopMatrix();
		
		
		glTranslatef(0, -0.8, 0);			//A_T3
		glTranslatef(0, 1.2, 0);			//A_T2
		glTranslatef(-0.5, 0.7, 0);			//A_T1

		
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.2, -2.2, -0.2);

	}
	glPopMatrix();
}

void Cavalier::Cavalier_DrawChevalPied(){
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//==========Cuisse===========
		//I'J'K'L'
		glColor3f(0,0,0);
		glVertex3f(-0.3,0,0.3); //I'
		glVertex3f(0.3,0,0.3);	//J'
		glVertex3f(0.3,0,-0.3); //K'
		glVertex3f(-0.3,0,-0.3); //L'
		glColor3ub(97, 63, 16);
		//ILKJ
		glVertex3f(-0.3,-0.9,0.3);//I
		glVertex3f(-0.3,-0.9,-0.3);//L
		glVertex3f(0.3,-0.9,-0.3);//K
		glVertex3f(0.3,-0.9,0.3);//J
		//I'IJJ'
		glColor3f(0,0,0);glVertex3f(-0.3,0,0.3); //I'
		glColor3ub(97, 63, 16);
		glVertex3f(-0.3,-0.9,0.3);//I
		glVertex3f(0.3,-0.9,0.3);//J
		glColor3f(0,0,0);glVertex3f(0.3,0,0.3);	//J'
		//J'JKK'
		glColor3f(0,0,0);glVertex3f(0.3,0,0.3);	//J'
		glColor3ub(97, 63, 16);
		glVertex3f(0.3,-0.9,0.3);//J
		glVertex3f(0.3,-0.9,-0.3);//K
		glColor3f(0,0,0);glVertex3f(0.3,0,-0.3); //K'
		//K'KLL'
		glColor3f(0,0,0);glVertex3f(0.3,0,-0.3); //K'
		glColor3ub(97, 63, 16);
		glVertex3f(0.3,-0.9,-0.3);//K
		glVertex3f(-0.3,-0.9,-0.3);//L
		glColor3f(0,0,0);glVertex3f(-0.3,0,-0.3); //L'
		//L'LII'
		glColor3f(0,0,0);glVertex3f(-0.3,0,-0.3); //L'
		glColor3ub(97, 63, 16);
		glVertex3f(-0.3,-0.9,-0.3);//L
		glVertex3f(-0.3,-0.9,0.3);//I
		glColor3f(0,0,0);glVertex3f(-0.3,0,0.3); //I'
		glColor3ub(97, 63, 16);
		//=========Molet=============
		
		//E'H'G'F'
		glColor3ub(97, 63, 16);
		glVertex3f(-0.2,-0.9,0.2); //E'
		glVertex3f(-0.2,-0.9,-0.2); //H'
		glVertex3f(0.2,-0.9,-0.2); //G'
		glVertex3f(0.2,-0.9,0.2); //F'
		
		//EFGH
		glColor3ub(67, 33, 0);
		glVertex3f(-0.2,-1.5,0.2); //E
		glVertex3f(0.2,-1.5,0.2); //F
		glVertex3f(0.2,-1.5,-0.2); //G
		glVertex3f(-0.2,-1.5,-0.2); //H
		//E'EFF'
		glColor3ub(97, 63, 16);glVertex3f(-0.2,-0.9,0.2); //E'
		glColor3ub(67, 33, 0);glVertex3f(-0.2,-1.5,0.2); //E
		glVertex3f(0.2,-1.5,0.2); //F
		glColor3ub(97, 63, 16);glVertex3f(0.2,-0.9,0.2); //F'
		//F'FGG'
		glColor3ub(97, 63, 16);glVertex3f(0.2,-0.9,0.2); //F'
		glColor3ub(67, 33, 0);glVertex3f(0.2,-1.5,0.2); //F
		glVertex3f(0.2,-1.5,-0.2); //G
		glColor3ub(97, 63, 16);glVertex3f(0.2,-0.9,-0.2); //G'
		//G'GHH'
		glColor3ub(97, 63, 16);glVertex3f(0.2,-0.9,-0.2); //G'
		glColor3ub(67, 33, 0);glVertex3f(0.2,-1.5,-0.2); //G
		glVertex3f(-0.2,-1.5,-0.2); //H
		glColor3ub(97, 63, 16);glVertex3f(-0.2,-0.9,-0.2); //H'
		//H'HEE'
		glColor3ub(97, 63, 16);glVertex3f(-0.2,-0.9,-0.2); //H'
		glColor3ub(67, 33, 0);glVertex3f(-0.2,-1.5,-0.2); //H
		glVertex3f(-0.2,-1.5,0.2); //E
		glColor3ub(97, 63, 16);glVertex3f(-0.2,-0.9,0.2); //E'
		//==========Pied===========
		glColor3ub(67, 33, 0);
		//A'D'C'B'
		glVertex3f(-0.3,-1.5,0.3); //A'
		glVertex3f(0.3,-1.5,0.3); //D'
		glVertex3f(0.3,-1.5,-0.3); //C'
		glVertex3f(-0.3,-1.5,-0.3); //B'
		//ABCD
		glVertex3f(-0.3,-1.8,0.3); //A
		glVertex3f(-0.3,-1.8,-0.3); //B
		glVertex3f(0.3,-1.8,-0.3); //C
		glVertex3f(0.3,-1.8,0.3); //D
		//A'ADD'
		glVertex3f(-0.3,-1.5,0.3); //A'
		glVertex3f(-0.3,-1.8,0.3); //A
		glVertex3f(0.3,-1.8,0.3); //D
		glVertex3f(0.3,-1.5,0.3); //D'
		//D'DCC'
		glVertex3f(0.3,-1.5,0.3); //D'
		glVertex3f(0.3,-1.8,0.3); //D
		glVertex3f(0.3,-1.8,-0.3); //C
		glVertex3f(0.3,-1.5,-0.3); //C'
		//C'CBB'
		glVertex3f(0.3,-1.5,-0.3); //C'
		glVertex3f(0.3,-1.8,-0.3); //C
		glVertex3f(-0.3,-1.8,-0.3); //B
		glVertex3f(-0.3,-1.5,-0.3); //B'
		//B'BAA'
		glVertex3f(-0.3,-1.5,-0.3); //B'
		glVertex3f(-0.3,-1.8,-0.3); //B
		glVertex3f(-0.3,-1.8,0.3); //A
		glVertex3f(-0.3,-1.5,0.3); //A'
		glEnd();
		glColor3f(1,1,1);
	}
	glPopMatrix();
}

void Cavalier::Cavalier_DrawChevalTete(){
	glColor3ub(97, 63, 16);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//ABCD
		glVertex3f(-0.5,0,0); //A
		glVertex3f(-0.5,0,-1); //B
		glVertex3f(0.5,0,-1); //C
		glVertex3f(0.5,0,0); //D
		//A'D'C'B'
		glVertex3f(-0.5,1.5,0); //A'
		glVertex3f(0.5,1.5,0); //D'
		glVertex3f(0.5,1.5,-1); //C'
		glVertex3f(-0.5,1.5,-1); //B'
		//A'ADD'
		glVertex3f(-0.5,1.5,0); //A'
		glVertex3f(-0.5,0,0); //A
		glVertex3f(0.5,0,0); //D
		glVertex3f(0.5,1.5,0); //D'
		//D'DCC'
		glVertex3f(0.5,1.5,0); //D'
		glVertex3f(0.5,0,0); //D
		glVertex3f(0.5,0,-1); //C
		glVertex3f(0.5,1.5,-1); //C'
		//C'CBB'
		glVertex3f(0.5,1.5,-1); //C'
		glVertex3f(0.5,0,-1); //C
		glVertex3f(-0.5,0,-1); //B
		glVertex3f(-0.5,1.5,-1); //B'
		//B'BAA'
		glVertex3f(-0.5,1.5,-1); //B'
		glVertex3f(-0.5,0,-1); //B
		glVertex3f(-0.5,0,0); //A
		glVertex3f(-0.5,1.5,0); //A'
		//poiles sur neck
		glColor3f(0,0,0);
		//XX'Y'Y
		glVertex3f(-0.2,1.5,-1);  //X
		glVertex3f(-0.2,0,-1);  //X'
		glVertex3f(0.2,0,-1);    //Y'
		glVertex3f(0.2,1.5,-1);  //Y
		//YY'Z'Z
		glVertex3f(0.2,1.5,-1);  //Y
		glVertex3f(0.2,0,-1);    //Y'
		glVertex3f(0.2,0,-1.4); //Z'
		glVertex3f(0.2,1.5,-1.4); //Z
		//ZZ'W'W
		glVertex3f(0.2,1.5,-1.4); //Z
		glVertex3f(0.2,0,-1.4); //Z'
		glVertex3f(-0.2,0,-1.4); //W'
		glVertex3f(-0.2,1.5,-1.4); //W
		//WW'X'X
		glVertex3f(-0.2,1.5,-1.4); //W
		glVertex3f(-0.2,0,-1.4); //W'
		glVertex3f(-0.2,0,-1);  //X'
		glVertex3f(-0.2,1.5,-1);  //X
		//XYZW
		glVertex3f(-0.2,1.5,-1);  //X
		glVertex3f(0.2,1.5,-1);  //Y
		glVertex3f(0.2,1.5,-1.4); //Z
		glVertex3f(-0.2,1.5,-1.4); //W
		//X'W'Z'Y'
		glVertex3f(-0.2,0,-1);  //X'
		glVertex3f(-0.2,0,-1.4); //W'
		glVertex3f(0.2,0,-1.4); //Z'
		glVertex3f(0.2,0,-1);    //Y'
		//====1er oreilles====
		glColor3ub(97, 63, 16);
		//O'OLL'
		glVertex3f(-0.5,1.8,-1); //O'
		glVertex3f(-0.5,1.5,-1); //O
		glVertex3f(-0.5,1.5,-0.7); //L
		glVertex3f(-0.5,1.8,-0.7); //L'
		//L'LMM'
		glVertex3f(-0.5,1.8,-0.7); //L'
		glVertex3f(-0.5,1.5,-0.7); //L
		glVertex3f(-0.2,1.5,-0.7); //M
		glVertex3f(-0.2,1.8,-0.7); //M'
		//M'MNN'
		glVertex3f(-0.2,1.8,-0.7); //M'
		glVertex3f(-0.2,1.5,-0.7); //M
		glVertex3f(-0.2,1.5,-1); //N
		glVertex3f(-0.2,1.8,-1); //N'
		//N'NOO'	
		glVertex3f(-0.2,1.8,-1); //N'	
		glVertex3f(-0.2,1.5,-1); //N
		glVertex3f(-0.5,1.5,-1); //O
		glVertex3f(-0.5,1.8,-1); //O' 
		//O'L'M'N'
		glVertex3f(-0.5,1.8,-1); //O'
		glVertex3f(-0.5,1.8,-0.7); //L'
		glVertex3f(-0.2,1.8,-0.7); //M'
		glVertex3f(-0.2,1.8,-1); //N'
		//====2 oreille========
		//L'LOO'
		glVertex3f(0.5,1.8,-0.7); //L'
		glVertex3f(0.5,1.5,-0.7); //L
		glVertex3f(0.5,1.5,-1); //O
		glVertex3f(0.5,1.8,-1); //O'
		//L'LMM'
		glVertex3f(0.2,1.8,-0.7); //M'
		glVertex3f(0.2,1.5,-0.7); //M
		glVertex3f(0.5,1.5,-0.7); //L
		glVertex3f(0.5,1.8,-0.7); //L'	
		//M'MNN'
		glVertex3f(0.2,1.8,-1); //N'
		glVertex3f(0.2,1.5,-1); //N
		glVertex3f(0.2,1.5,-0.7); //M
		glVertex3f(0.2,1.8,-0.7); //M'
		//N'NOO'	
		glVertex3f(0.5,1.8,-1); //O' 
		glVertex3f(0.5,1.5,-1); //O
		glVertex3f(0.2,1.5,-1); //N
		glVertex3f(0.2,1.8,-1); //N'		
		//O'L'M'N'
		glVertex3f(0.2,1.8,-1); //N'
		glVertex3f(0.2,1.8,-0.7); //M'
		glVertex3f(0.5,1.8,-0.7); //L'
		glVertex3f(0.5,1.8,-1); //O'	
		//======NEZ===========
		glColor3ub(97, 63, 16);
		//GG'H'H
		glVertex3f(0.4,1.5,0); //G
		glVertex3f(0.4,0.7,0); //G'
		glVertex3f(-0.4,0.7,0); //H'
		glVertex3f(-0.4,1.5,0); //H
		//HH'E'E
		glVertex3f(-0.4,1.5,0); //H
		glVertex3f(-0.4,0.7,0); //H'
		glColor3f(0,0,0);glVertex3f(-0.4,0.7,0.8); //E'
		glColor3f(0,0,0);glVertex3f(-0.4,1.5,0.8); //E
		//EE'F'F
		glVertex3f(-0.4,1.5,0.8); //E
		glVertex3f(-0.4,0.7,0.8); //E'
		glVertex3f(0.4,0.7,0.8); //F'
		glVertex3f(0.4,1.5,0.8); //F
		glColor3ub(97, 63, 16);
		//FF'G'G
		glColor3f(0,0,0);glVertex3f(0.4,1.5,0.8); //F
		glColor3f(0,0,0);glVertex3f(0.4,0.7,0.8); //F'
		glColor3ub(97, 63, 16);
		glVertex3f(0.4,0.7,0); //G'
		glVertex3f(0.4,1.5,0); //G
		//HEFG
		glVertex3f(-0.4,1.5,0); //H
		glColor3f(0,0,0);glVertex3f(-0.4,1.5,0.8); //E
		glColor3f(0,0,0);glVertex3f(0.4,1.5,0.8); //F
		glColor3ub(97, 63, 16);
		glVertex3f(0.4,1.5,0); //G
		//E'H'G'F'
		glColor3f(0,0,0);glVertex3f(-0.4,0.7,0.8); //E'
		glColor3ub(97, 63, 16);
		glVertex3f(-0.4,0.7,0); //H'
		glVertex3f(0.4,0.7,0); //G'
		glColor3f(0,0,0);glVertex3f(0.4,0.7,0.8); //F'
		glEnd();
	}
	glPopMatrix();
	glColor3f(1,1,1);
}

void Cavalier::Cavalier_DrawChevalCorps(){
	glColor3ub(97, 63, 16);
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//ADCB
		
		glColor3f(0,0,0);glVertex3f(-3,0,0); //A
		glVertex3f(-3,0,-1.5); //D
		glVertex3f(0,0,-1.5); //C
		glVertex3f(0,0,0); //B
		//A'B'C'D'
		glColor3ub(97, 63, 16);
		glVertex3f(-3,1.5,0); //A'
		glVertex3f(0,1.5,0); //B'
		glVertex3f(0,1.5,-1.5); //C'
		glVertex3f(-3,1.5,-1.5); //D'
		//A'ABB'
		glVertex3f(-3,1.5,0); //A'
		glColor3f(0,0,0);
		glVertex3f(-3,0,0); //A
		glVertex3f(0,0,0); //B
		glColor3ub(97, 63, 16);
		glVertex3f(0,1.5,0); //B'
		//B'BCC'
		glVertex3f(0,1.5,0); //B'
		glColor3f(0,0,0);
		glVertex3f(0,0,0); //B
		glVertex3f(0,0,-1.5); //C
		glColor3ub(97, 63, 16);
		glVertex3f(0,1.5,-1.5); //C'
		//C'CDD'
		glVertex3f(0,1.5,-1.5); //C'
		glColor3f(0,0,0);
		glVertex3f(0,0,-1.5); //C
		glVertex3f(-3,0,-1.5); //D
		glColor3ub(97, 63, 16);
		glVertex3f(-3,1.5,-1.5); //D'
		//D'DAA'
		glVertex3f(-3,1.5,-1.5); //D'
		glColor3f(0,0,0);
		glVertex3f(-3,0,-1.5); //D
		glVertex3f(-3,0,0); //A
		glColor3ub(97, 63, 16);
		glVertex3f(-3,1.5,0); //A'
		glEnd();
		
		glTranslatef(0,1.2,-0.75);
		glRotatef(-30,0,0,1);
		glBegin(GL_QUADS);
		//=======queue=========
		//1'144'
		glVertex3f(0,0,-0.2); 	//1'
		glVertex3f(0,0,0.2); 	//1
		glVertex3f(1,0,0.2); //4
		glVertex3f(1,0,-0.2); //4'
		//22'3'3
		glVertex3f(0,-0.4,0.2); 		//2
		glVertex3f(0,-0.4,-0.2); 		//2'
		glVertex3f(1,-0.4,-0.2); 	//3'
		glVertex3f(1,-0.4,0.2); 	//3
		//1234
		glVertex3f(0,0,0.2); 	//1
		glVertex3f(0,-0.4,0.2); 		//2
		glVertex3f(1,-0.4,0.2); 	//3
		glVertex3f(1,0,0.2); //4
		//433'4'
		glVertex3f(1,0,0.2); //4
		glVertex3f(1,-0.4,0.2); 	//3
		glVertex3f(1,-0.4,-0.2); 	//3'
		glVertex3f(1,0,-0.2); //4'
		//4'3'2'1'
		glVertex3f(1,0,-0.2); //4'
		glVertex3f(1,-0.4,-0.2); 	//3'
		glVertex3f(0,-0.4,-0.2); 		//2'
		glVertex3f(0,0,-0.2); 	//1'
		//1'2'21
		glVertex3f(0,0,-0.2); 	//1'
		glVertex3f(0,-0.4,-0.2); 		//2'
		glVertex3f(0,-0.4,0.2); 		//2
		glVertex3f(0,0,0.2); 	//1
		glEnd();
		glRotatef(30,0,0,1);
		glTranslatef(0,-1.2,0.75);
	}
	glPopMatrix();
	glColor3f(1,1,1);
}

void Cavalier::Cavalier_DrawCheval(){
	glColor3f(1,1,1);
	glPushMatrix();
	{
		//pied droite arriere
		glTranslatef(1.2,1.8,-0.45);
		glCallList(_piece_cavalier_chevalPied);//DrawChevalPied();
		glTranslatef(-1.2,-1.8,0.45);		
		//pied gauche arriere
		glTranslatef(1.2,1.8,0.45);
		glCallList(_piece_cavalier_chevalPied);//DrawChevalPied();
		glTranslatef(-1.2,-1.8,-0.45);
		
		glRotatef(-cavalier_angle_cheval,0,0,1);		//Animation cheval incliné
		glRotatef(cavalier_angle_cheval_retour,0,0,1);
		//pied droite avant
		glTranslatef(-1.2,1.8,-0.45);
		glCallList(_piece_cavalier_chevalPied);//DrawChevalPied();
		glTranslatef(1.2,-1.8,0.45);
		//pied gauche avant
		glTranslatef(-1.2,1.8,0.45);
		glCallList(_piece_cavalier_chevalPied);//DrawChevalPied();
		glTranslatef(1.2,-1.8,-0.45);
		
		//Tete
		glTranslatef(-0.5,2.7,0);
		glRotatef(30,0,0,1);
		glRotatef(-90,0,1,0);
		glTranslatef(0,0,1);
		glCallList(_piece_cavalier_chevalTete);//DrawChevalTete();
		glTranslatef(0,0,-1);
		glRotatef(90,0,1,0);
		glRotatef(-30,0,0,1);
		
		glTranslatef(0.5,-2.7,-0);
		
		//Corps du cheval
		glTranslatef(1.5,1.2,0.75);
		
		glCallList(_piece_cavalier_chevalCorps);//DrawChevalCorps();
		glTranslatef(-1.5,-1.2,-0.75);
		
		glRotatef(cavalier_angle_cheval,0,0,1);		//inverse
		glRotatef(-cavalier_angle_cheval_retour,0,0,1);
	}
	glPopMatrix();
}

void Cavalier::DrawCavaliers() {
	//PHASE 1 incliner Cheval
	if(action_cavaliers){
		if(cavalier_angle_cheval<20) {cavalier_angle_cheval+=0.5;}
		if(cavalier_angle_cheval>=20) {fin_phase1_cavaliers = true;}
	}
	//PHASE 2 Attaque & bouger Cheval
	if(fin_phase1_cavaliers){
		if(cavalier_attaque<20) {cavalier_attaque++;}
		if(cavalier_attaque>=20) {fin_phase2_cavaliers=true;}
	}
	//PHASE 3 Retour attaque
	if(fin_phase2_cavaliers){
		if(cavalier_attaque_retour<20) {cavalier_attaque_retour++;}
		if(cavalier_attaque_retour>=20) {fin_phase3_cavaliers = true;}
		
	}
	//PHASE 4 Retour incliner
	if(fin_phase3_cavaliers){
		if(cavalier_angle_cheval_retour<20) {cavalier_angle_cheval_retour+=0.5;}
		if(cavalier_angle_cheval_retour>=20) {fin_action_cavaliers = true;}
	}
	
	glPushMatrix();
	{
		//=================Partie cheval====================
		glTranslatef(0,0.4,0);
		Cavalier::Cavalier_DrawCheval();
		glTranslatef(0,-0.4,0);
		
		
		glRotatef(-cavalier_angle_cheval,0,0,1); 	//Animation coherent avec le cheval (phase 1)
		glRotatef(cavalier_angle_cheval_retour,0,0,1);
		
		glTranslatef(0.5,1.2,0);	//Monter sur le cheval
		glTranslatef(-0.4, 0.4, -0.6);
		//==================Partie cavalier==================
		glPushMatrix();
		{
			glPushMatrix();
			{	
				glTranslatef(0.65, 0.35, 0);
				glTranslatef(0,0.3,-0.45); 		//repositionner les jambres
				glCallList(_piece_cavalier_Jambe1);//DrawJambre(45);
				glTranslatef(0,-0.3,0.45);		//inverse
				glTranslatef(0, 0.55, 0.6);
				glRotatef(90, 0, 1, 0);
				
				glRotatef(-10,1,0,0);
				glRotatef(-cavalier_angle_cheval,1,0,0);
				glRotatef(cavalier_angle_cheval_retour,1,0,0);
				//=========================================
				glCallList(_piece_cavalier_corps);//DrawCorps();
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, 2.6, 0.8);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -0.2, 0);
				glCallList(_piece_cavalier_epaule);//DrawEpaule();
				glCallList(_piece_cavalier_brasGauche);//DrawBrasGauche();
				glTranslatef(0, 0.2, 0);
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2.6, -0.8);
				glTranslatef(0, 3.25, 0);
				glTranslatef(0,-0.2,0);
				glCallList(_piece_cavalier_tete);//DrawTete();
				glTranslatef(0,0.2,0);
				//=============Partie symétrique===============
				glTranslatef(0, -5, 0.6);		//repositionner cette partie
				glTranslatef(0, 0.4, 0);
				glTranslatef(0,0.3,0.45); 		//repositionner les jambres
				glCallList(_piece_cavalier_Jambe2);//DrawJambre(-45);
				glTranslatef(0,-0.3,-0.45);		//inverse
				glTranslatef(-0, 0.5, 0.6);
				glTranslatef(0, 2.6, -0.8 - 1.2);
				glRotatef(90, 0, 1, 0);

			
				//=========================================
				glTranslatef(0, -0.2, 0);
				glCallList(_piece_cavalier_epaule);//DrawEpaule();
				Cavalier_DrawBrasDroite(); //ne peut pas mettre dans la liste => animation interne
				glTranslatef(0, 0.2, 0);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -2.6, 0.8 + 1.2);
				glRotatef(10,1,0,0);
				glRotatef(cavalier_angle_cheval,1,0,0);
				glRotatef(-cavalier_angle_cheval_retour,1,0,0);
			}
			glPopMatrix();
			glTranslatef(0,0.3,-0.45); 		//repositionner les pieds
			glCallList(Piece::_piece_piece_pied);//DrawPied();
			glTranslatef(0,-0.3,0.45);		//inverse
			glTranslatef(0, 0, 1.2);
			glTranslatef(0,0.3,0.45); 		//repositionner les pieds
			glCallList(Piece::_piece_piece_pied);//DrawPied();
			glTranslatef(0,0.3,-0.45); 		//inverse
			glTranslatef(0, 0, -1.2);
			
			glTranslatef(-0.5,-1.2,0); //inverse monter sur le cheval
		}
		glPopMatrix();
		
		glRotatef(cavalier_angle_cheval,0,0,1);	 //inverse Animation coherent avec le cheval (phase 1)
		glRotatef(-cavalier_angle_cheval_retour,0,0,1);
	}
	glPopMatrix();
	
	if (get_joueur()) 	
		glCallList(Piece::_piece_piece_baseArgent);
	else
		glCallList(Piece::_piece_piece_baseOr);
}




void Cavalier::affichage_attaque()
{
	if (_lock_bouger)
	{
		_peut_bouger=false;
		_lock_bouger=false;
	}
	
	if (!_anim_fini) // on fais l'animation
	{
		glPushMatrix();
			translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
			orientation(_case_support->get_pos_pion(),_points_intermediaires[_nb_deplacement],_case_support->get_norm());					
			animation();
			affiche_piece();
		glPopMatrix();
	}
	else
	{
		if ( _anim_fini && !_peut_bouger)
		{
			glPushMatrix();
				translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
				orientation(_case_support->get_pos_pion(),_points_intermediaires[_nb_deplacement],_case_support->get_norm());			
				affiche_piece();
			glPopMatrix();
		}
		else
		{
			if ( _anim_fini && _peut_bouger) //on avance jusque a la case d'attaque
			{
				glPushMatrix();
					
					if (_avancement_dir2<1)
					{			
						translation( _case_support->get_pos_pion().get_coord_x()*(1-_avancement_dir2),
									_case_support->get_pos_pion().get_coord_y()*(1-_avancement_dir2),
									_case_support->get_pos_pion().get_coord_z()*(1-_avancement_dir2));
						translation( _points_intermediaires[_nb_deplacement].get_coord_x()*(_avancement_dir2),
									_points_intermediaires[_nb_deplacement].get_coord_y()*(_avancement_dir2),
									_points_intermediaires[_nb_deplacement].get_coord_z()*(_avancement_dir2));

						_avancement_dir2+=0.06;	
						
						orientation(_case_support->get_pos_pion(),_points_intermediaires[_nb_deplacement],_case_support->get_norm());			
					}
					else
					{
						translation(_points_intermediaires[_nb_deplacement].get_coord_x()*(1-_avancement_dir),
									_points_intermediaires[_nb_deplacement].get_coord_y()*(1-_avancement_dir),
									_points_intermediaires[_nb_deplacement].get_coord_z()*(1-_avancement_dir));
						translation( _chemin[_nb_deplacement]->get_pos_pion().get_coord_x()*(_avancement_dir),
									_chemin[_nb_deplacement]->get_pos_pion().get_coord_y()*(_avancement_dir),
									_chemin[_nb_deplacement]->get_pos_pion().get_coord_z()*(_avancement_dir));
						
						_avancement_dir+=0.06;	
						
						orientation( _points_intermediaires[_nb_deplacement],_chemin[_nb_deplacement]->get_pos_pion(),_case_support->get_norm());			
													
					}		
					//translation normale
					if (_nb_deplacement==0 && _avancement_dir2<1)
					{ 
						_hauteur+=0.8;
					}
					if (_nb_deplacement==_chemin.size()-1 && _avancement_dir2>1)
					{
						_hauteur-=0.8;
					}
					translation(0,_hauteur,0);
										
					_avancement_rot+=0.03;

					affiche_piece();
				glPopMatrix();
			
			
				if (_avancement_dir>=1)
				{
					_avancement_dir=0;
					_avancement_dir2=0;
					_avancement_rot=0;
					_case_support=_chemin[_nb_deplacement];
					_nb_deplacement+=1;
					if (_nb_deplacement==_chemin.size())
					{
						_etat_piece=0;
						_nb_deplacement=0;
						_hauteur=0;
						_a_attaquer=false;
						_anim_fini=false;
						_lock_bouger=true;
					}
				}
			}
		}
	}	
}

void Cavalier::affichage_mouvement()
{
	glPushMatrix();
		
		if (_avancement_dir2<1)
		{			
			translation( _case_support->get_pos_pion().get_coord_x()*(1-_avancement_dir2),
						_case_support->get_pos_pion().get_coord_y()*(1-_avancement_dir2),
						_case_support->get_pos_pion().get_coord_z()*(1-_avancement_dir2));
			translation( _points_intermediaires[_nb_deplacement].get_coord_x()*(_avancement_dir2),
						_points_intermediaires[_nb_deplacement].get_coord_y()*(_avancement_dir2),
						_points_intermediaires[_nb_deplacement].get_coord_z()*(_avancement_dir2));
			
			_avancement_dir2+=0.06;	
			
			orientation(_case_support->get_pos_pion(),_points_intermediaires[_nb_deplacement],_case_support->get_norm());			
			
		}
		else
		{
			translation(_points_intermediaires[_nb_deplacement].get_coord_x()*(1-_avancement_dir),
						_points_intermediaires[_nb_deplacement].get_coord_y()*(1-_avancement_dir),
						_points_intermediaires[_nb_deplacement].get_coord_z()*(1-_avancement_dir));
			translation( _chemin[_nb_deplacement]->get_pos_pion().get_coord_x()*(_avancement_dir),
						_chemin[_nb_deplacement]->get_pos_pion().get_coord_y()*(_avancement_dir),
						_chemin[_nb_deplacement]->get_pos_pion().get_coord_z()*(_avancement_dir));
						
			_avancement_dir+=0.06;	
			
			orientation( _points_intermediaires[_nb_deplacement],_chemin[_nb_deplacement]->get_pos_pion(),_case_support->get_norm());			
													
		}		
		//translation normale
		if (_nb_deplacement==0 && _avancement_dir2<1)
		{ 
			_hauteur+=0.8;
		}
		if (_nb_deplacement==_chemin.size()-1 && _avancement_dir2>1)
		{
			_hauteur-=0.8;
		}
		
		translation(0,_hauteur,0);

		_avancement_rot+=0.03;

		affiche_piece();
	glPopMatrix();
	
	
	if (_avancement_dir>=1)
	{
		_avancement_dir=0;
		_avancement_dir2=0;
		_avancement_rot=0;
		_case_support=_chemin[_nb_deplacement];
		_nb_deplacement+=1;
		if (_nb_deplacement==_chemin.size())
		{
			_case_support=_chemin[_chemin.size()-1];
			_etat_piece=0;
			_nb_deplacement=0;
			_hauteur=0;
		}
	}
}
