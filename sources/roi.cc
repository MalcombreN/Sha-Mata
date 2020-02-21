#include "roi.hh"
GLuint	Roi::_piece_roi_epee;
GLuint	Roi::_piece_roi_cape;
GLuint	Roi::_piece_roi_couronne;
GLuint	Roi::_piece_roi_tete;
GLuint	Roi::_piece_roi_epaule;
GLuint	Roi::_piece_roi_jambe1;
GLuint	Roi::_piece_roi_jambe2;
GLuint	Roi::_piece_roi_corps;
GLuint	Roi::_piece_roi_bras;

Roi::Roi(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::roi ,case_support , joueur ),
	roi_angle_doigt(0.0f), 
	roi_angle_doigt_retour(0.0f),
	roi_angle_avantbras(0.0f),
	roi_angle_avantbras_retour(0.0f),
	roi_angle_fix(60.0f),
	roi_angle_lever_epee(0.0f),
	roi_angle_lever_epee_retour(0.0f),
	roi_lever_bras(0.0f),
	roi_lever_bras_retour(0.0f),
	roi_attaquer_avantbras_v(0.0f),
	roi_attaquer_avantbras_v_retour(0.0f),
	roi_attaquer_bras(0.0f),
	roi_attaquer_bras_retour(0.0f),
	action_roi(false),
	fin_phase1_roi(false),
	fin_phase2_roi(false),
	fin_phase3_roi(false),
	fin_phase4_roi(false),
	fin_phase5_roi(false),
	fin_phase6_roi(false),
	fin_phase7_roi(false),
	fin_phase8_roi(false),
	fin_phase9_roi(false),
	fin_action_roi(false)
{}


void Roi::load_piece()
{
	Roi::_piece_roi_epee= glGenLists(1);
	glNewList(Roi::_piece_roi_epee,GL_COMPILE);   Roi_DrawEpee();	glEndList();
	Roi::_piece_roi_cape= glGenLists(1);
	glNewList(Roi::_piece_roi_cape,GL_COMPILE);   Roi_DrawCape(); glEndList();
	Roi::_piece_roi_couronne= glGenLists(1);
	glNewList(Roi::_piece_roi_couronne,GL_COMPILE);   Roi_DrawCouronne_roi(0.55,0.6);	glEndList();
	Roi::_piece_roi_tete= glGenLists(1);
	glNewList(Roi::_piece_roi_tete,GL_COMPILE);   Roi_DrawTete(); 	glEndList();
	Roi::_piece_roi_epaule= glGenLists(1);
	glNewList(Roi::_piece_roi_epaule,GL_COMPILE);   Roi_DrawEpaule();	glEndList();
	Roi::_piece_roi_jambe1= glGenLists(1);
	glNewList(Roi::_piece_roi_jambe1,GL_COMPILE);   Roi_DrawJambre(15); glEndList();
	Roi::_piece_roi_jambe2= glGenLists(1);
	glNewList(Roi::_piece_roi_jambe2,GL_COMPILE);   Roi_DrawJambre(-15); glEndList();
	Roi::_piece_roi_corps= glGenLists(1);
	glNewList(Roi::_piece_roi_corps,GL_COMPILE);   Roi_DrawCorps();	glEndList();
	Roi::_piece_roi_bras= glGenLists(1);
	glNewList(Roi::_piece_roi_bras,GL_COMPILE);   Roi_DrawBras();		glEndList();
}

void Roi::Roi_DrawEpee() {
	glPushMatrix();
	{
		
		glBindTexture (GL_TEXTURE_2D, textures[21]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//=========== PARTIE 1 =============== 
		//face dessus ABCD
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.05,-0.2,0.05); //A
		glTexCoord2f(0.0, 0.0);glVertex3f(0.05,-0.2,0.05); //B
		glTexCoord2f(1.0, 0.0);glVertex3f(0.05,-0.2,-0.05); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.05,-0.2,-0.05);//D
		//face dessous A'D'C'B'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.05,-0.5,0.05); //A'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.05,-0.5,-0.05);//D'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.05,-0.5,-0.05); //C'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.05,-0.5,0.05); //B'
		//face avant AA'B'B
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.05,-0.2,0.05); //A
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.05,-0.5,0.05); //A'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.05,-0.5,0.05); //B'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.05,-0.2,0.05); //B
		//face droite BB'C'C
		glTexCoord2f(0.0, 1.0);glVertex3f(0.05,-0.2,0.05); //B
		glTexCoord2f(0.0, 0.0);glVertex3f(0.05,-0.5,0.05); //B'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.05,-0.5,-0.05); //C'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.05,-0.2,-0.05); //C
		//face derriere CC'D'D
		glTexCoord2f(0.0, 1.0);glVertex3f(0.05,-0.2,-0.05); //C
		glTexCoord2f(0.0, 0.0);glVertex3f(0.05,-0.5,-0.05); //C'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.05,-0.5,-0.05);//D'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.05,-0.2,-0.05);//D
		//face gauche DD'A'A
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.05,-0.2,-0.05);//D
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.05,-0.5,-0.05);//D'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.05,-0.5,0.05); //A'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.05,-0.2,0.05); //A
		//========= PARTIE 2 ============
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.25,-0.5,0.05); //E
		glTexCoord2f(0.0, 0.0);glVertex3f(0.25,-0.5,0.05); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(0.25,-0.5,-0.05); //G
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.25,-0.5,-0.05); //H
		
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.35,-0.65,0.05); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.35,-0.65,-0.05); //H'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.35,-0.65,-0.05); //G'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.35,-0.65,0.05); //F'
		
		//face EE'F'F
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.25,-0.5,0.05); //E
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.35,-0.65,0.05); //E'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.35,-0.65,0.05); //F'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.25,-0.5,0.05); //F
		//face FF'G'G
		glTexCoord2f(0.0, 1.0);glVertex3f(0.25,-0.5,0.05); //F
		glTexCoord2f(0.0, 0.0);glVertex3f(0.35,-0.65,0.05); //F'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.35,-0.65,-0.05); //G'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.25,-0.5,-0.05); //G
		//face GG'H'H
		glTexCoord2f(0.0, 1.0);glVertex3f(0.25,-0.5,-0.05); //G
		glTexCoord2f(0.0, 0.0);glVertex3f(0.35,-0.65,-0.05); //G'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.35,-0.65,-0.05); //H'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.25,-0.5,-0.05); //H
		//face HH'E'E
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.25,-0.5,-0.05); //H
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.35,-0.65,-0.05); //H'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.35,-0.65,0.05); //E'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.25,-0.5,0.05); //E
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		
		glBindTexture(GL_TEXTURE_2D, textures[22]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//========== PARTIE 3 ===========
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-0.65,-0.05); //W
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.15,-0.65,0.05); //X
		glTexCoord2f(1.0, 0.0);glVertex3f(0.15,-0.65,0.05); //Y
		glTexCoord2f(1.0, 1.0);glVertex3f(0.15,-0.65,-0.05); //Z
	
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-2.65,-0.05); //W'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.15,-2.65,-0.05); //Z'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.15,-2.65,0.05); //Y'	
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.15,-2.65,0.05); //X'
		//face devant XX'Y'Y
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-0.65,0.05); //X
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.15,-2.65,0.05); //X'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.15,-2.65,0.05); //Y'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.15,-0.65,0.05); //Y
		//face droite YY'Z'Z
		glTexCoord2f(0.0, 1.0);glVertex3f(0.15,-0.65,0.05); //Y
		glTexCoord2f(0.0, 0.0);glVertex3f(0.15,-2.65,0.05); //Y'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.15,-2.65,-0.05); //Z'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.15,-0.65,-0.05); //Z
		//FACE DERRIERE ZZ'W'W
		glTexCoord2f(0.0, 1.0);glVertex3f(0.15,-0.65,-0.05); //Z
		glTexCoord2f(0.0, 0.0);glVertex3f(0.15,-2.65,-0.05); //Z'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.15,-2.65,-0.05); //W'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.15,-0.65,-0.05); //W
		//FACE GAUCHE WW'X'X
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-0.65,-0.05); //W
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.15,-2.65,-0.05); //W'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.15,-2.65,0.05); //X'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.15,-0.65,0.05); //X
		glEnd();
		
		glBegin(GL_TRIANGLES);
		//X'OY'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.15,-2.65,0.05); //X'
		glTexCoord2f(0.5, 1.0);glVertex3f(0,-3,0); //O
		glTexCoord2f(0.0, 1.0);glVertex3f(0.15,-2.65,0.05); //Y'
		//Y'OZ'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.15,-2.65,0.05); //Y'
		glTexCoord2f(0.5, 1.0);glVertex3f(0,-3,0); //O
		glTexCoord2f(0.0, 1.0);glVertex3f(0.15,-2.65,-0.05); //Z'
		//Z'OW'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.15,-2.65,-0.05); //Z'
		glTexCoord2f(0.5, 1.0);glVertex3f(0,-3,0); //O
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-2.65,-0.05); //W'
		//W'OX'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.15,-2.65,-0.05); //W'
		glTexCoord2f(0.5, 1.0);glVertex3f(0,-3,0); //O
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.15,-2.65,0.05); //X'
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
	}
	glPopMatrix();
}

void Roi::Roi_DrawCape(){
	
	glRotatef(180,1,0,0);
	glPushMatrix();
	{
			int n = 1;
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.5,0,0);glVertex3f(0, 0, 0);
			bool paire = true;
			for (int k = 40; k <= 140; k += 20) {
				if(paire){
					glColor3ub(0,0,175);glVertex3f(3*Cos(k), 4, 2*Sin(k));
					paire = true;
				}
				else{
					glColor3ub(0,0,175);glVertex3f(3*Cos(k), 4, 2*Sin(k));
					paire = false;
				}
			}
			glEnd();
			n++;
	}
	glPopMatrix();
	glRotatef(-180,1,0,0);
	glColor3f(1,1,1);
}

void Roi::Roi_DrawCouronne_roi(float n, float n2) {
	glPushMatrix();
	{	glColor3f(1.0, 0.5, 0.0);
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 5) {
			glVertex3f(n*Cos(j), 0.1, n*Sin(j));
			glVertex3f(n*Cos(j), 0, n*Sin(j));
		}
		glEnd();
		glTranslatef(0, 0.1, 0);
		glBegin(GL_TRIANGLES);
		for (int j = 0; j <= 360; j += 30) {
			glVertex3f(n*Cos(j+10), n2, n*Sin(j));
			glVertex3f(n*Cos(j), 0, n*Sin(j));
			glVertex3f(n*Cos(j+20), 0, n*Sin(j+20));
		}
		glEnd();
		glTranslatef(0, -0.1, 0);
		glColor3f(0.1,0.1,0.1);
	}
	glPopMatrix();
}

void Roi::Roi_DrawTete() {
	
	glPushMatrix();
	{
		glColor3ub(254,195,172);
		glCallList(Piece::_piece_piece_sphere1);//DrawSphere(0.55);
		glColor3f(1,1,1);
		glTranslatef(0, 0.3, 0);
		glCallList(_piece_roi_couronne);//DrawCouronne_roi(0.55, 0.6);
		glTranslatef(0, -0.3, 0);
	}
	glPopMatrix();
}

void Roi::Roi_DrawEpaule() {
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[19]);
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

void Roi::Roi_DrawJambre(float degree) {
	//==============Molet==================
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[20]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre1);//DrawCylindre(0.125, 0.2, 0.7);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTranslatef(0, 0.7, 0);
		glColor3ub(0,25,5);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1,1,1);
	}
	glPopMatrix();
	glTranslatef(0, 0.8, 0);
	glRotatef(degree, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textures[20]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre2);//DrawCylindre(0.2,0.3,0.65);
	glDisable(GL_TEXTURE_2D);
	glRotatef(-degree, 1, 0, 0);
}

void Roi::Roi_DrawCorps() {
	glBindTexture (GL_TEXTURE_2D, textures[19]);
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
	glTranslatef(0,2.6,0);
	glRotatef(180,0,1,0);
	glCallList(_piece_roi_cape);//DrawCape();
	glRotatef(-180,0,1,0);
	glTranslatef(0,-2.6,0);
}

void Roi::Roi_DrawBras() {

	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[19]);
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
		
		glBindTexture (GL_TEXTURE_2D, textures[20]);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.5,-0.7,0);

		glRotatef(180, 1, 0, 0);
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.2, 0);
		
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.1,0.1,0.1);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glBindTexture (GL_TEXTURE_2D, textures[20]);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -0.8, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.1,0.1,0.1);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1,1,1);
		glDisable(GL_TEXTURE_2D);
		//==Pour inserer la main
		glTranslatef(-0.15, -0.45, 0);
		glRotatef(-180, 1, 0, 0);
		glCallList(Piece::_piece_piece_mains2);//DrawMain(angle_fix);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.15, 0.45, 0);

		glTranslatef(-0.5, 2.5, 0);
	}
	glPopMatrix();
}

void Roi::Roi_DrawBras_action() {
	//Ainimation
	//PHASE 1 Tourner avant bras
		if (action_roi) {		
			if(roi_angle_avantbras<180) {roi_angle_avantbras+=2;}
			if(roi_angle_avantbras>=180) {fin_phase1_roi = true;}
		}
	//PHASE 2 Serrer la main pour attraper l'epee
		if (fin_phase1_roi) {		
			if (roi_angle_doigt < 70){roi_angle_doigt+=2;}
			if (roi_angle_doigt >= 70) fin_phase2_roi = true;
		}
	//PHASE 3  Tourner l'avant bras avec l'epee	
		if(fin_phase2_roi){
			if(roi_angle_lever_epee<180) {roi_angle_lever_epee+=2;}
			if(roi_angle_lever_epee>=180) {fin_phase3_roi = true;}
		}
	//PHASE 4 Lever Bras pour préparer à attaquer
		if(fin_phase3_roi){
			if(roi_lever_bras<120) {roi_lever_bras+=3;}
			if(roi_lever_bras>=120) {fin_phase4_roi = true;}
		}
	//PHASE 5 ATTAQUER
		if(fin_phase4_roi){
			if(roi_attaquer_bras<60) {roi_attaquer_bras+=3;}
			if(roi_attaquer_avantbras_v<85) {roi_attaquer_avantbras_v+=5;}
			if(roi_attaquer_bras>=60 && roi_attaquer_avantbras_v>=85) {fin_phase5_roi = true;}
		}
	//PHASE 6 Retour attaque
		if(fin_phase5_roi){
			if(roi_attaquer_bras_retour<60){roi_attaquer_bras_retour+=5;}
			if(roi_attaquer_avantbras_v_retour<85) {roi_attaquer_avantbras_v_retour+=5;}
			if(roi_attaquer_bras_retour>=60 && roi_attaquer_avantbras_v_retour>=85) {fin_phase6_roi = true;}
		}
	//PHASE 7 Retour lever bras
		if(fin_phase6_roi){
			if(roi_lever_bras_retour<120) {roi_lever_bras_retour+=2;}
			if(roi_lever_bras_retour>=120) {fin_phase7_roi = true;}
		}
	//PHASE 8 Poser l'épee (Retour)
		if(fin_phase7_roi){
			if(roi_angle_lever_epee_retour<180) {roi_angle_lever_epee_retour+=2;}
			if(roi_angle_lever_epee_retour>=180) {fin_phase8_roi = true;}
		}
	//PHASE 9 
		if(fin_phase8_roi){
			if (roi_angle_doigt_retour < 70){roi_angle_doigt_retour+=2;}
			if (roi_angle_doigt_retour >= 70) {fin_action_roi = true;}
		}
		

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, textures[19]);
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
		
		
		glTranslatef(0.5, -0.7, 0);			//T1

		//Animation pour lever les bras (préparation d'attaque)
		glRotatef(-roi_lever_bras,1,0,0);
		glRotatef(roi_lever_bras_retour,1,0,0);
		//Animation pour attaquer
		glRotatef(roi_attaquer_bras,1,0,0);
		glRotatef(-roi_attaquer_bras_retour,1,0,0);

		glRotatef(180, 1, 0, 0);			//R1 Grand bras
		
		glBindTexture(GL_TEXTURE_2D, textures[20]);
		glEnable(GL_TEXTURE_2D);
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);			//A_R1  grand bras
		glTranslatef(0, -1.2, 0);			//T2
		glDisable(GL_TEXTURE_2D);
		
		glColor3f(0.1,0.1,0.1);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		glBindTexture (GL_TEXTURE_2D, textures[20]);
		glEnable(GL_TEXTURE_2D);
		glRotatef(90, 1, 0, 0);				//R2
		
		//Animation pour attaquer (avantbras)
		glRotatef(roi_attaquer_avantbras_v,1,0,0);
		glRotatef(-roi_attaquer_avantbras_v_retour,1,0,0);
		
		glRotatef(roi_angle_avantbras,0,1,0);  //pour attraper l'epee
		glRotatef(-roi_angle_lever_epee,0,1,0); //pour lever l'epee
		glRotatef(roi_angle_lever_epee_retour,0,1,0);
		
		glPushMatrix();
		{
			glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
			glTranslatef(0, 0.8, 0);		//T3
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.1,0.1,0.1);
			glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
			glColor3f(1,1,1);
			
		}
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.2,0,0);
		glRotatef(-90, 1, 0, 0);			//A_R2
		//=====Pour inserer la main======
		glTranslatef(-0.15, 0.15, 0.5);		//T4
		glRotatef(90, 1, 0, 0);				//R3
		glRotatef(-90, 0, 1, 0);			//R4
		glDisable(GL_TEXTURE_2D);
		DrawMain(roi_angle_doigt-roi_angle_doigt_retour);	//ici pour l'animation des doigt de la main
	
		glRotatef(90, 0, 1, 0);				//A_R4
		glRotatef(-90, 1, 0, 0);			//A_R3
		glTranslatef(0.15, -0.15, -0.5);	//A_T4
		glPopMatrix();
		
		
		glRotatef(-roi_angle_avantbras,0,1,0);  //inverse attraper l'epee
		
		glTranslatef(0, -0.8, 0);			//A_T3
		glTranslatef(0, 1.2, 0);			//A_T2
		glTranslatef(-0.5, 0.7, 0);			//A_T1

		
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.2, -2.2, -0.2);
		
		glTranslatef(0.3,2.5,0.4); //positionner l'epee
		glRotatef(90,0,1,0);
		glCallList(_piece_roi_epee);//DrawEpee();
		glRotatef(-90,0,1,0);
		glTranslatef(-0.3,-2.5,-0.4); //inverse
		
		glRotatef(roi_angle_lever_epee,0,1,0); // inverse pour lever l'epee
		glRotatef(-roi_angle_lever_epee_retour,0,1,0);
		glRotatef(roi_lever_bras,1,0,0);
		glRotatef(-roi_lever_bras_retour,1,0,0);
	}
	glPopMatrix();
}

void Roi::DrawRoi() {
	glPushMatrix();
	{
		glTranslatef(-0.4, 0.4, -0.6);
		//==================Partie action==================
		glPushMatrix();
		{
			glPushMatrix();
			{	
				glTranslatef(0.65, 0.35, 0);
				glColor3f(0.1, 0.1, 0.1);
				glCallList(_piece_roi_jambe1);//DrawJambre(15);
				glTranslatef(0, 0.55, 0.6);
				glRotatef(90, 0, 1, 0);

				//=========================================
				glCallList(_piece_roi_corps);//DrawCorps();
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, 2.6, 0.8);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -0.2, 0);
				glCallList(_piece_roi_epaule);//DrawEpaule();
				Roi_DrawBras_action();
				glTranslatef(0, 0.2, 0);
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2.6, -0.8);
				glTranslatef(0, 3.25, 0);
				glTranslatef(0,-0.25,0);
				glCallList(_piece_roi_tete);//DrawTete();
				glTranslatef(0,0.25,0);
				//=============Partie symétrique===============
				glTranslatef(0, -5, 0.6);		//repositionner cette partie
				glTranslatef(0, 0.4, 0);
				glCallList(_piece_roi_jambe2);//DrawJambre(-15);

				glTranslatef(-0, 0.5, 0.6);
				glTranslatef(0, 2.6, -0.8 - 1.2);
				glRotatef(90, 0, 1, 0);

			
				//=========================================
				glTranslatef(0, -0.2, 0);
				glCallList(_piece_roi_epaule);//DrawEpaule();
				glCallList(_piece_roi_bras);//DrawBras();
				glTranslatef(0, 0.2, 0);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -2.6, 0.8 + 1.2);
			}
			glPopMatrix();

			glCallList(Piece::_piece_piece_pied);//DrawPied();
			glTranslatef(0, 0, 1.2);
			glCallList(Piece::_piece_piece_pied);//DrawPied();
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


void Roi::affiche_piece()
{
	DrawRoi();
	if(fin_phase5_roi){
		set_a_attaquer();
	}
	if(fin_action_roi){
		set_anim_fini();
		roi_angle_doigt = 0.0f;  
		roi_angle_doigt_retour = 0.0f;
		roi_angle_avantbras = 0.0f;
		roi_angle_avantbras_retour = 0.0f;
		roi_angle_fix = 60.0f;
		roi_angle_lever_epee = 0.0f;
		roi_angle_lever_epee_retour = 0.0f;
		roi_lever_bras = 0.0f;
		roi_lever_bras_retour = 0.0f;
		roi_attaquer_avantbras_v  = 0.0f;
		roi_attaquer_avantbras_v_retour = 0.0f;
		roi_attaquer_bras= 0.0f;
		roi_attaquer_bras_retour = 0.0f;
		action_roi = false;
		fin_phase1_roi = false;
		fin_phase2_roi = false;
		fin_phase3_roi = false;
		fin_phase4_roi = false;
		fin_phase5_roi = false;
		fin_phase6_roi = false;
		fin_phase7_roi = false;
		fin_phase8_roi = false;
		fin_phase9_roi = false;
		fin_action_roi = false;
	
	}
}

void Roi::animation()
{
	action_roi = true;

}


