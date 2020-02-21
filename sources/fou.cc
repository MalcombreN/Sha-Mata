#include "fou.hh"

GLuint Fou::_piece_fou_dague;
GLuint Fou::_piece_fou_pied;
GLuint Fou::_piece_fou_jambe;
GLuint Fou::_piece_fou_corps;
GLuint Fou::_piece_fou_chapeau;
GLuint Fou::_piece_fou_tete;


Fou::Fou(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::fou ,case_support , joueur ),
	 action_fou  (false),
 fin_phase1_fou  (false),
 fin_phase2_fou  (false),
 fin_phase3_fou  (false),
 fin_phase4_fou  (false),
 fin_phase5_fou  (false),
 fin_phase6_fou  (false),
 fin_phase7_fou  (false),
 fin_action_fou  (false),
 fou_angle_epaule (0.0f),
 fou_angle_epaule_bis (0.0f),
 fou_angle_epaule_retour ( 0.0f),
 fou_angle_epaule_bis_retour ( 0.0f),
 fou_angle_avantbras (0.0f),
 fou_angle_avantbras_retour (0.0f),
 fou_angle_main1 (0.0f),
 fou_angle_main1_retour (0.0f),
 fou_angle_poignet (0.0f),
 fou_angle_poignet_retour (0.0f),
 fou_angle_main2 (0.0f),
 fou_angle_main2_retour (0.0f),
 fou_angle_assassiner_epaule (0.0f),
 fou_angle_assassiner_avantbras (0.0f),
 fou_angle_assassiner_avantbras_bis (0.0f),
 fou_angle_assassiner_avantbras_bis_retour( 0.0f),
 fou_angle_assassiner_retour_avantbras (0.0f),
 fou_angle_assassiner_retour_epaule (0.0f),
 fou_distance_corps (0.0f),
 fou_distance_corps_retour (0.0f),
 fou_angle_corps (0.0f),
 fou_angle_corps_retour(0.0f),
 fou_distance_jambre (0.0f),
 fou_distance_jambre_retour (0.0f),
 fou_distance_avancer (0.0f),
 fou_distance_avancer_retour (0.0f),
 fou_angle_genoux (0.0f),
 fou_angle_genoux_retour (0.0f),
 fou_angle_cuisse (0.0f),
 fou_angle_cuisse_retour(0.0f),
 fou_monte_bras (0.0f),
 fou_monte_bras_retour (0.0f)
{}


void Fou::load_piece()
{
		Fou::_piece_fou_dague= glGenLists(1);
		glNewList(_piece_fou_dague,GL_COMPILE);   Fou_DrawDague(); glEndList();
		Fou::_piece_fou_pied= glGenLists(1);
		glNewList(_piece_fou_pied,GL_COMPILE);   Fou_DrawPied(); glEndList();
		Fou::_piece_fou_jambe= glGenLists(1);
		glNewList(_piece_fou_jambe,GL_COMPILE);   Fou_DrawJambre(15);glEndList();
		Fou::_piece_fou_corps= glGenLists(1);
		glNewList(_piece_fou_corps,GL_COMPILE);   Fou_DrawCorps(); glEndList();
		Fou::_piece_fou_chapeau= glGenLists(1);
		glNewList(_piece_fou_chapeau,GL_COMPILE);   Fou_DrawFouChapeau();glEndList();
		Fou::_piece_fou_tete= glGenLists(1);
		glNewList(_piece_fou_tete,GL_COMPILE);   Fou_DrawTete();glEndList();
	
}



void Fou::affiche_piece()
{
	DrawFou();
	if(fin_phase4_fou){
		set_a_attaquer();
	}
	if(fin_action_fou){
		set_anim_fini();
		 action_fou = false;
		 fin_phase1_fou = false;
		 fin_phase2_fou = false;
		 fin_phase3_fou = false;
		 fin_phase4_fou = false;
		 fin_phase5_fou = false;
		 fin_phase6_fou = false;
		 fin_phase7_fou = false;
		 fin_action_fou = false;
		 fou_angle_epaule = 0.0f;
		 fou_angle_epaule_bis = 0.0f;
		 fou_angle_epaule_retour = 0.0f;
		 fou_angle_epaule_bis_retour = 0.0f;
		 fou_angle_avantbras = 0.0f;
		 fou_angle_avantbras_retour = 0.0f;
		 fou_angle_main1 = 0.0f;
		 fou_angle_main1_retour = 0.0f;
		 fou_angle_poignet = 0.0f;
		 fou_angle_poignet_retour = 0.0f;
		 fou_angle_main2 = 0.0f;
		 fou_angle_main2_retour = 0.0f;
		 fou_angle_assassiner_epaule = 0.0f;
		 fou_angle_assassiner_avantbras = 0.0f;
		 fou_angle_assassiner_avantbras_bis = 0.0f;
		 fou_angle_assassiner_avantbras_bis_retour = 0.0f;
		 fou_angle_assassiner_retour_avantbras = 0.0f;
		 fou_angle_assassiner_retour_epaule = 0.0f;
		 fou_distance_corps = 0.0f;
		 fou_distance_corps_retour = 0.0f;
		 fou_angle_corps = 0.0f;
		 fou_angle_corps_retour=0.0f;
		 fou_distance_jambre = 0.0f;
		 fou_distance_jambre_retour = 0.0f;
		 fou_distance_avancer = 0.0f;
		 fou_distance_avancer_retour = 0.0f;
		 fou_angle_genoux = 0.0f;
		 fou_angle_genoux_retour = 0.0f;
		 fou_angle_cuisse = 0.0f;
		 fou_angle_cuisse_retour = 0.0f;
		 fou_monte_bras = 0.0f;
		 fou_monte_bras_retour = 0.0f;
	}
}

void Fou::animation()
{
	action_fou = true;
}

void Fou::Fou_DrawDague() {
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[9]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//============partie 1================= 
			//Face en bas A'ABB'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4,0,0);		//A'
			glTexCoord2f(0.0, 0.0);glVertex3f(0, 0, 0);		//A
			glTexCoord2f(1.0, 0.0);glVertex3f(0, 0, -0.05);		//B
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0, -0.05);	//B'
			//Face en haut C'CDD'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4,0.15,-0.05);	//C'
			glTexCoord2f(0.0, 0.0);glVertex3f(0, 0.15, -0.05);	//C
			glTexCoord2f(1.0, 0.0);glVertex3f(0, 0.15, 0);		//D
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0.15, 0);		//D'
			//Face devant D'DAA'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 0.15, 0);		//D'
			glTexCoord2f(0.0, 0.0);glVertex3f(0, 0.15, 0);		//D
			glTexCoord2f(1.0, 0.0);glVertex3f(0, 0, 0);		//A
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0, 0);		//A'
			//Face droite D'A'B'C'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 0.15, 0);		//D'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 0, 0);		//A'
			glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0, -0.05);	//B'
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0.15, -0.05);	//C'
			//Face derriere CC'B'B
			glTexCoord2f(0.0, 1.0);glVertex3f(0, 0.15, -0.05);	//C
			glTexCoord2f(0.0, 0.0);glVertex3f(0.4, 0.15, -0.05);	//C'
			glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0, -0.05);	//B'
			glTexCoord2f(1.0, 1.0);glVertex3f(0, 0, -0.05);		//B
			//Face gauche CBAD
			glTexCoord2f(0.0, 1.0);glVertex3f(0, 0.15, -0.05);	//C
			glTexCoord2f(0.0, 0.0);glVertex3f(0, 0, -0.05);		//B
			glTexCoord2f(1.0, 0.0);glVertex3f(0, 0, 0);		//A
			glTexCoord2f(1.0, 1.0);glVertex3f(0, 0.15, 0);		//D
			glEnd();
		glDisable(GL_TEXTURE_2D);
		
		//glColor3f(0.4,0.4,0.4);
		glBindTexture (GL_TEXTURE_2D, textures[10]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//===============partie 2====================
			//Face en bas
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4,-0.1,0);	//E
			glTexCoord2f(0.0, 0.0);glVertex3f(0.4, -0.1, -0.05);	//H
			glTexCoord2f(1.0, 0.0);glVertex3f(0.45, -0.1, -0.05);	//G
			glTexCoord2f(1.0, 1.0);glVertex3f(0.45,-0.1,0);	//F
			//Face en haut
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 0.25, 0);	//E'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.45, 0.25, 0);	//F'
			glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0.25, -0.05);	//G'
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0.25, -0.05);	//H'
			//Face F'FGG'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.45, 0.25, 0);	//F'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.45, -0.1, 0);	//F
			glTexCoord2f(1.0, 0.0);glVertex3f(0.45, -0.1, -0.05);	//G
			glTexCoord2f(1.0, 1.0);glVertex3f(0.45, 0.25, -0.05);	//G'
			//Face G'GHH'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.45, 0.25, -0.05);	//G'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.45, -0.1, -0.05);	//G
			glTexCoord2f(1.0, 0.0);glVertex3f(0.4, -0.1, -0.05);	//H
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0.25, -0.05);	//H'
			//Face H'HEE'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 0.25, -0.05);	//H'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.4, -0.1, -0.05);	//H
			glTexCoord2f(1.0, 0.0);glVertex3f(0.4, -0.1, 0);	//E
			glTexCoord2f(1.0, 1.0);glVertex3f(0.4, 0.25, 0);	//E'
			//Face E'EFF'
			glTexCoord2f(0.0, 1.0);glVertex3f(0.4, 0.25, 0);	//E'
			glTexCoord2f(0.0, 0.0);glVertex3f(0.4, -0.1, 0);	//E
			glTexCoord2f(1.0, 0.0);glVertex3f(0.45, -0.1, 0);	//F
			glTexCoord2f(1.0, 1.0);glVertex3f(0.45, 0.25, 0);	//F'
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glBindTexture (GL_TEXTURE_2D, textures[10]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
		//O'E'F'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, 0.35, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.4, 0.25, 0);	//E'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0.25, 0);	//F'
		//O'F'G'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, 0.35, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.45, 0.25, 0);	//F'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0.25, -0.05);	//G'
		//O'G'H'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, 0.35, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.45, 0.25, -0.05);	//G'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0.25, -0.05);	//H'
		//O'H'E'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, 0.35, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.4, 0.25, -0.05);	//H'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, 0.25, 0);	//E'
		//==============================
		//OFE
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, -0.2, -0.025); //O
		glTexCoord2f(0.5, 1.0);glVertex3f(0.45, -0.1, 0);	//F
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, -0.1, 0);	//E
		//OGF
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, -0.2, -0.025); //O
		glTexCoord2f(0.5, 1.0);glVertex3f(0.45, -0.1, -0.05);	//G
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, -0.1, 0);	//F
		//OHG
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, -0.2, -0.025); //O
		glTexCoord2f(0.5, 1.0);glVertex3f(0.4, -0.1, -0.05);	//H
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, -0.1, -0.05);	//G
		//OEH
		glTexCoord2f(0.0, 1.0);glVertex3f(0.5, -0.2, -0.025); //O
		glTexCoord2f(0.5, 1.0);glVertex3f(0.4, -0.1, 0);	//E
		glTexCoord2f(1.0, 0.0);glVertex3f(0.4, -0.1, -0.05);	//H
		glEnd();
		glDisable(GL_TEXTURE_2D);
		
		glBindTexture (GL_TEXTURE_2D, textures[10]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//Face en haut W'WXX'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.95, 0.15, -0.05); //W'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.45, 0.15, -0.05); //W
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0.15, 0);	//X
		glTexCoord2f(1.0, 1.0);glVertex3f(0.95, 0.15, 0);	//X'
		//face en bas Y'YZZ'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.95, 0, 0);		//Y'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.45, 0, 0);		//Y
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0, -0.05); //Z
		glTexCoord2f(1.0, 1.0);glVertex3f(0.95, 0, -0.05); //Z'
		//Face devant
		glTexCoord2f(0.0, 1.0);glVertex3f(0.45,0,0);		//Y
		glTexCoord2f(0.0, 0.0);glVertex3f(0.95, 0, 0);		//Y'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0.15, 0);	//X'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.45, 0.15, 0);	//X
		//Face droite X'Y'Z'W'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.95, 0.15, 0);	//X'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.95, 0, 0);		//Y'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0, -0.05); //Z'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.95, 0.15, -0.05); //W'
		//Face derriere
		glTexCoord2f(0.0, 1.0);glVertex3f(0.95, 0.15, -0.05); //W'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.95, 0, -0.05); //Z'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0, -0.05); //Z
		glTexCoord2f(1.0, 1.0);glVertex3f(0.45, 0.15, -0.05); //W
		//Face gauche WZYX
		glTexCoord2f(0.0, 1.0);glVertex3f(0.45, 0.15, -0.05); //W
		glTexCoord2f(0.0, 0.0);glVertex3f(0.45, 0, -0.05); //Z
		glTexCoord2f(1.0, 0.0);glVertex3f(0.45, 0, 0);		//Y
		glTexCoord2f(1.0, 1.0);glVertex3f(0.45, 0.15, 0);	//X
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBindTexture (GL_TEXTURE_2D, textures[10]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
		//PX'Y'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.15, 0.075, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.95, 0.15, 0);	//X'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0, 0);		//Y'
		//PY'Z'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.15, 0.075, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.95, 0, 0);		//Y'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0, -0.05); //Z'
		//PZ'W'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.15, 0.075, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.95, 0, -0.05); //Z'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0.15, -0.05); //W'
		//PW'X'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.15, 0.075, -0.025);
		glTexCoord2f(0.5, 1.0);glVertex3f(0.95, 0.15, -0.05); //W'
		glTexCoord2f(1.0, 0.0);glVertex3f(0.95, 0.15, 0);	//X'
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
	}
	glPopMatrix();
}

void Fou::Fou_DrawPied() {
	glPushMatrix();
	{
		//=============Niveau plus bas==================
		glColor3ub(0,25,5);
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
		glVertex3f(0.1, 0.1, 0.0);
		glVertex3f(-0.15, 0, 0);
		glVertex3f(0.0, 0, 0.05);

		glVertex3f(0.1, 0.1, 0.0);
		glVertex3f(0.0, 0, -0.05);
		glVertex3f(-0.15, 0, 0);

		glVertex3f(1, 0.1, 0);
		glVertex3f(1, 0, 0.05);
		glVertex3f(1, 0, -0.05);
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

		glColor3ub(255,255,255);
	}
	glPopMatrix();
}

void Fou::Fou_DrawJambre(float degree) {
	//==============Molet==================
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[13]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre5);//DrawCylindre(0.125, 0.2, 0.7);
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
	glBindTexture(GL_TEXTURE_2D, textures[14]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre6);//DrawCylindre(0.2,0.3,0.65);
	glDisable(GL_TEXTURE_2D);
	glRotatef(-degree, 1, 0, 0);
}

void Fou::Fou_DrawJambre_action(float degree) {
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[13]);
	glEnable(GL_TEXTURE_2D);
	
	if(fin_phase2_fou){
		if(fou_distance_jambre<0.01){fou_distance_jambre+=0.005;}
		if(fou_angle_genoux<10){fou_angle_genoux+=0.5;}
		if(fou_angle_cuisse <45){fou_angle_cuisse+=2;}
		if(fou_distance_avancer<0.3){fou_distance_avancer+=0.05;}
	}
	if(fin_phase5_fou){
		if(fou_distance_jambre_retour<0.01) {fou_distance_jambre_retour+=0.005;}
		if(fou_angle_genoux_retour<10){fou_angle_genoux_retour+=2;}
		if(fou_angle_cuisse_retour<45){fou_angle_cuisse_retour+=2;}
		if(fou_distance_avancer_retour<0.3) {fou_distance_avancer_retour+=0.05;}
	}
	
	
	
	glRotatef(fou_angle_genoux,0,1,0);
	glTranslatef(-fou_distance_avancer,0,0);
	glTranslatef(fou_distance_avancer_retour,0,0);
	glTranslatef(-fou_distance_jambre,0,0);
	glTranslatef(fou_distance_jambre_retour,0,0);
	//==============Molet==================
	glCallList(Piece::_piece_piece_cylindre5);//DrawCylindre(0.125, 0.2, 0.7);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glColor3ub(0,25,5);
		glTranslatef(0, 0.7, 0);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3ub(255,255,255);
	}
	glPopMatrix();
	glTranslatef(0, 0.8, 0);
	glRotatef(degree, 1, 0, 0);

	glRotatef(-fou_angle_cuisse,0,0,1);	//animation pour bouger la cuisse
	glRotatef(fou_angle_cuisse_retour,0,0,1);
	glTranslatef(-0.,0.05,0);
	//=============Cuisse================
	glColor3f(1,1,1);
	glBindTexture (GL_TEXTURE_2D, textures[14]);
	glEnable(GL_TEXTURE_2D);
	glCallList(Piece::_piece_piece_cylindre6);//DrawCylindre(0.2,0.3,0.65);
	glDisable(GL_TEXTURE_2D);
	glRotatef(fou_angle_cuisse,0,0,1);	//inverse
	glRotatef(-fou_angle_cuisse_retour,0,0,1); //inverse
	glRotatef(-degree, 1, 0, 0);
	
	glRotatef(-fou_angle_genoux,0,1,0);
	glTranslatef(fou_distance_jambre,0,0); //inverse
	glTranslatef(-fou_distance_jambre_retour,0,0); //inverse
	
	glTranslatef(fou_distance_avancer,0,0);
}

void Fou::Fou_DrawCorps() {
	glBindTexture (GL_TEXTURE_2D, textures[13]);
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

void Fou::Fou_DrawFouChapeau() {
	glPushMatrix();
	{
		glColor3f(1,1,1);
		
		int n = 1;
		bool paire = true;
		for (float i = 0; i <= 0.3; i += 0.0075) {
			glTranslatef(0, 0.05, 0);
			glRotatef(2.5, 0, 0, 1);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.5,1);glVertex3f(0, 0, 0);
			for (int k = 0; k <= 360; k += 5) {
				if(paire){
					glTexCoord2f(0,0);glVertex3f(i*Cos(k), i, i*Sin(k));
					paire = true;
				}
				else{
					glTexCoord2f(1,0);glVertex3f(i*Cos(k), i, i*Sin(k));
					paire = false;
				}
			}
			glEnd();
			n++;
		}
	
		
		//Retour à l'origine
		for (float j = 0; j <= 0.3; j += 0.0075) {
			glTranslatef(0, -0.05, 0);
			glRotatef(-2.5, 0, 0, 1);
		}
		//glTranslatef(0, -0.2, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1, 0, 0);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}

void Fou::Fou_DrawTete() {
	
	glPushMatrix();
	{
		glColor3ub(254,195,172);
		glCallList(Piece::_piece_piece_sphere1);//DrawSphere(0.55);
		glColor3f(1,1,1);
		
		for (int i = 0; i <= 270; i += 90) {
			glRotatef(i, 0, 1, 0);
			glRotatef(30, 0, 0, 1);
			glTranslatef(2, -1, 0);
			if(i ==0 || i==270)
				{
					glBindTexture(GL_TEXTURE_2D, textures[12]); 
					glEnable(GL_TEXTURE_2D);
					glCallList(_piece_fou_chapeau);//DrawFouChapeau();
					glDisable(GL_TEXTURE_2D);
				}
			
			if(i==90 || i ==180 )
				{
					glBindTexture(GL_TEXTURE_2D, textures[11]); 
					glEnable(GL_TEXTURE_2D);
					glCallList(_piece_fou_chapeau);//DrawFouChapeau();
					glDisable(GL_TEXTURE_2D);
			}
			
			glTranslatef(-2, 1, 0);
			glRotatef(-30, 0, 0, 1);
		}
	}
	glPopMatrix();
}

void Fou::Fou_DrawBrasGauche() {
	
	glRotatef(15, 1, 0, 0);	//cacher dagues bras
	glRotatef(-fou_angle_epaule, 1, 0, 0);
	glRotatef(fou_angle_epaule_retour,1,0,0);
	glRotatef(fou_angle_epaule_bis, 0, 0, 1);
	glRotatef(-fou_angle_epaule_bis_retour,0,0,1);
	glTranslatef(-0.1, 0, 0);

	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[13]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);glVertex3f(0.1, -0.2, -0.4); //J
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.7, -0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.7, 0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1, -0.7, -0.4); //T
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
		glBindTexture (GL_TEXTURE_2D, textures[14]);
		glEnable(GL_TEXTURE_2D);

		glTranslatef(0.5, -0.7, 0);			//T1

		glRotatef(180, 1, 0, 0);			//R1
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);			//A_R1
		glTranslatef(0, -1.2, 0);			//T2
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glRotatef(180, 1, 0, 0);				//R2
		glPushMatrix();
		{
			
			glRotatef(-fou_angle_avantbras, 0, 0, 1);
			glRotatef(fou_angle_avantbras_retour,0,0,1);
			glRotatef(60, 0, 0, 1);		//cacher dagues avant bras
			glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
			glTranslatef(0, 0.8, 0);		//T3
			glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		
		//PHASE 2
		
		//==Pour inserer la main
		glTranslatef(-0.15, 0.15, 0.5);		//T4
		glRotatef(fou_angle_main1,0,0,1);
		glRotatef(90, 1, 0, 0);				//R3
		
		glRotatef(-90, 0, 1, 0);			//R4
		glDisable(GL_TEXTURE_2D);
		glCallList(Piece::_piece_piece_mains2);//DrawMain(fou_angle_doigt_fix);	//ici pour l'animation des doigt de la main
		//Inserer les dagues
		glTranslatef(0, -0.2, 0);
		glCallList(_piece_fou_dague);//DrawDague();
		glTranslatef(0, 0.2, 0);

		glRotatef(90, 0, 1, 0);				//A_R4
		glRotatef(-90, 1, 0, 0);			//A_R3
		glTranslatef(0.15, -0.15, -0.5);	//A_T4
		}
		glPopMatrix();

		glTranslatef(0, -0.8, 0);			//A_T3
		glRotatef(-180, 1, 0, 0);			//A_R2
		glTranslatef(0, 1.2, 0);			//A_T2
		glTranslatef(-0.5, 0.7, 0);			//A_T1


		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.2, -2.2, 0.2);
		glRotatef(-60, 0, 0, 1);		//inverse cacher dagues
		
	}
	glPopMatrix();
	
	glRotatef(-fou_angle_epaule_bis, 0, 0, 1);
	glRotatef(fou_angle_epaule_bis_retour,0,0,1);
	glRotatef(fou_angle_epaule, 1, 0, 0);
	glRotatef(-fou_angle_epaule_retour,1,0,0);
	glRotatef(-15, 1, 0, 0);	//cacher dagues bras
}

void Fou::Fou_DrawBrasDroite() {
	
	//=================ANIMATION================== 
	if (action_fou) {
		if (fou_angle_avantbras < 60) {fou_angle_avantbras+=5;}
		if (fou_angle_epaule < 15) {
			fou_angle_epaule++;
			fou_angle_epaule_bis++;
		}
	}
	if (fou_angle_epaule >= 15 && fou_angle_epaule_bis >= 15 && fou_angle_avantbras>=60) { fin_phase1_fou = true; }
	if(fin_phase1_fou) {
			if(fou_angle_main2 <90){
				fou_angle_main2+=5;
				fou_angle_poignet+=5;
			}
			if(fou_angle_main2 >=90) {fin_phase2_fou = true;}
	}
	if(fin_phase2_fou){
		if(fou_angle_assassiner_epaule<60) { fou_angle_assassiner_epaule++;}
		if(fou_angle_poignet<90){fou_angle_poignet+=5;}
		if(fou_angle_assassiner_epaule>40 && fou_angle_assassiner_avantbras<80) {fou_angle_assassiner_avantbras+=5;}
		if(fou_angle_assassiner_epaule>=60 && fou_angle_assassiner_avantbras>=80 && fou_angle_poignet>=90){fin_phase3_fou = true;}
	}
	if(fin_phase3_fou){
		if(fou_angle_assassiner_avantbras_bis<40) {fou_angle_assassiner_avantbras_bis+=2;}
		if(fou_angle_assassiner_avantbras_bis>=40 && fou_angle_assassiner_avantbras_bis_retour<40 ) {fou_angle_assassiner_avantbras_bis_retour+=2;}
		if(fou_angle_assassiner_avantbras_bis_retour>=40) {fin_phase4_fou = true;}
	}
	if(fin_phase4_fou){
		if(fou_angle_assassiner_retour_epaule<60) { fou_angle_assassiner_retour_epaule++;}
		if(fou_angle_poignet<90){fou_angle_poignet+=5;}
		if(fou_angle_assassiner_retour_epaule>40 && fou_angle_assassiner_retour_avantbras<80) {fou_angle_assassiner_retour_avantbras+=5;}
		if(fou_angle_assassiner_retour_epaule>=60 && fou_angle_assassiner_retour_avantbras>=80 && fou_angle_poignet>=90){fin_phase5_fou = true;}
	}
	if(fin_phase5_fou){
		if(fou_angle_epaule_retour<15){
			fou_angle_epaule_retour++;
			fou_angle_epaule_bis_retour++;
		}
		if (fou_angle_avantbras_retour < 60) {fou_angle_avantbras_retour+=5;}
		if(fou_angle_main2_retour <90){
				fou_angle_main2_retour+=5;
				fou_angle_main1_retour+=5;
				fou_angle_poignet_retour +=5;
			}
		if(fou_angle_epaule_retour>=15 && fou_angle_avantbras_retour>=60) {fin_action_fou = true; }
	}
	
	glRotatef(-15, 1, 0, 0);	//cacher dagues bras
	glRotatef(fou_angle_epaule, 1, 0, 0);
	glRotatef(-fou_angle_epaule_retour,1,0,0);
	glRotatef(fou_angle_epaule_bis, 0, 0, 1);
	glRotatef(-fou_angle_epaule_bis_retour,0,0,1);
	
	glRotatef(fou_angle_assassiner_epaule,1,0,0);	//pour assassiner
	glRotatef(-fou_angle_assassiner_retour_epaule,1,0,0);
	glTranslatef(-0.1, 0, 0);
	
	
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[13]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);glVertex3f(0.1, -0.2, -0.4); //J
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.2, 0.4); //I
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.2, -0.4); //O
		glTexCoord2f(0.0, 0.0);glVertex3f(0.9, -0.2, 0.4);  //P
		glTexCoord2f(1.0, 0.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(1.0, 1.0);glVertex3f(0.9, -0.7, -0.4); //Q

		glTexCoord2f(0.0, 1.0);glVertex3f(0.9, -0.7, 0.4); //R
		glTexCoord2f(0.0, 0.0);glVertex3f(0.1, -0.7, 0.4); //S
		glTexCoord2f(1.0, 0.0);glVertex3f(0.1, -0.7, -0.4); //T
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
		
		glBindTexture (GL_TEXTURE_2D, textures[14]);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.5, -0.7, 0);			//T1
		glRotatef(180, 0, 1, 0);			//pour orienter le bras(correctement)R0
		glRotatef(180, 1, 0, 0);			//R1
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);			//A_R1
		glTranslatef(0, -1.2, 0);			//T2
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glRotatef(180, 1, 0, 0);				//R2
		glPushMatrix();
		{
			glRotatef(-60, 0, 0, 1);		//cacher dagues
			glRotatef(fou_angle_avantbras, 0, 0, 1);
			glRotatef(-fou_angle_avantbras_retour,0,0,1);
			glRotatef(fou_angle_assassiner_avantbras_bis,0,0,1);
			glRotatef(-fou_angle_assassiner_avantbras_bis_retour,0,0,1);
			
			glRotatef(-fou_angle_assassiner_avantbras,0,0,1);
			glRotatef(fou_angle_assassiner_retour_avantbras,0,0,1);
			glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
			glTranslatef(0, 0.8, 0);		//T3
			glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
			
		glRotatef(-fou_angle_main2,0,0,1);
		glRotatef(fou_angle_main2_retour,0,0,1);
		glRotatef(-fou_angle_poignet,0,1,0);		// poignet
		glRotatef(fou_angle_poignet_retour,0,1,0);
		//==Pour inserer la main
		glTranslatef(-0.15, 0.15, 0.5);		//T4
		glRotatef(90, 1, 0, 0);				//R3
		glRotatef(-90, 0, 1, 0);			//R4
		glDisable(GL_TEXTURE_2D);
		glCallList(Piece::_piece_piece_mains2);//DrawMain(fou_angle_doigt_fix);	//ici pour l'animation des doigt de la main
		
		
		//Inserer les dagues
		glTranslatef(0, -0.2, 0);
		glCallList(_piece_fou_dague);//DrawDague();
		glTranslatef(0, 0.2, 0);

		glRotatef(90, 0, 1, 0);				//A_R4
		glRotatef(-90, 1, 0, 0);			//A_R3
		glTranslatef(0.15, -0.15, -0.5);	//A_T4
		}
		glPopMatrix();

		glTranslatef(0, -0.8, 0);			//A_T3
		glTranslatef(0, 1.2, 0);			//A_T2
		glTranslatef(-0.5, 0.7, 0);			//A_T1


		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.2, -2.2, 0.2);
		glTranslatef(0.1, 0, 0);	//inverse
		glRotatef(60, 0, 0, 1);		//inverse cacher dagues
		glRotatef(-180, 1, 0, 0);			//A_R2
		glRotatef(-180, 0, 1, 0);	//A_R0
	}
	glPopMatrix();
	glRotatef(-fou_angle_epaule_bis, 0, 0, 1);
	glRotatef(-fou_angle_epaule, 1, 0, 0);
	glRotatef(15, 1, 0, 0);	//cacher dagues bras
}

void Fou::DrawFou() {

	glPushMatrix();
	{
		glTranslatef(-0.4, 0.4, -0.6);
		glPushMatrix();
		{
			glPushMatrix();
			{
				if(fin_phase2_fou){
					if (fou_distance_corps < 0.3)
						fou_distance_corps += 0.005;
					if(fou_angle_corps < 10){
						fou_angle_corps+=0.5;
					}
					if(fou_monte_bras<0.2){fou_monte_bras+=0.005;}
				}
				if(fin_phase5_fou){
					if(fou_distance_corps_retour<0.3){
						fou_distance_corps_retour+=0.005;}
					if(fou_angle_corps_retour<10){
						fou_angle_corps_retour+=0.5;
					}
					if(fou_monte_bras_retour<0.2){fou_monte_bras_retour+=0.005;}
				}
				
				
				
				glTranslatef(0.65, 0.35, 0);
				glCallList(_piece_fou_jambe);//DrawJambre(15);
				glTranslatef(0, 0.55, 0.6);
				glRotatef(90, 0, 1, 0);
				
				glTranslatef(0, -fou_distance_corps, 0);
				glTranslatef(0, fou_distance_corps_retour, 0);
				
				glRotatef(-fou_angle_corps,1,0,0);
				glRotatef(fou_angle_corps_retour,1,0,0);
				glCallList(_piece_fou_corps);//DrawCorps();
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, 2.6, 0.8);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(-0.3, -0.2, 0);
				
				glTranslatef(0,-fou_monte_bras,0);
				glTranslatef(0,fou_monte_bras_retour,0);
				Fou_DrawBrasGauche();
				glTranslatef(0,-fou_monte_bras_retour,0);
				glTranslatef(0,fou_monte_bras,0);
				
				glTranslatef(0.3, 0.2, 0);
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2.6, -0.8);
				glTranslatef(0, 3, 0);
				glCallList(_piece_fou_tete);//DrawTete();
				
				//=============Partie symétrique===============
				glTranslatef(0, -4.7, 0.7);		//repositionner cette partie
				glTranslatef(0, 0.35, 0);
				Fou_DrawJambre_action(-15);

				glTranslatef(-0, 0.5, 0.6);
				glTranslatef(0, 2.6, -0.8 - 1.2);
				glRotatef(90, 0, 1, 0);

				//Phase 2 ======Rotation du corps========= 
				
				//=========================================
				glTranslatef(-0.3 ,-0.15, -0);
				glTranslatef(0,-fou_monte_bras,0);
				
				glTranslatef(0,fou_monte_bras_retour,0);
				Fou_DrawBrasDroite();
				glTranslatef(0,-fou_monte_bras_retour,0);
				glTranslatef(0,fou_monte_bras,0);
				
				glTranslatef(0.3, 0.15, 0);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -2.6, 0.8 + 1.2);
				
				//glRotatef(+angle_corps,1,0,0);
				glTranslatef(0, -3, 0);
				
				glTranslatef(0,fou_distance_corps,0);
				glTranslatef(0,-fou_distance_corps_retour,0);
			}
			glPopMatrix();

			glCallList(_piece_fou_pied);//DrawPied();
			glTranslatef(0, 0, 1.2);
			glCallList(_piece_fou_pied);//DrawPied();
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

