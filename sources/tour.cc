#include "tour.hh"
#include <iostream>
 GLuint Tour::_piece_tour_corps;


Tour::Tour(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::tour ,case_support , joueur ),
	 action_tour  (false),
	 fin_phase1_tour  (false),
	 fin_phase2_tour  (false),
	 fin_phase3_tour  (false),
	 fin_phase4_tour  (false),
	 fin_action_tour  (false),
	 tour_angle_canon1  (0.0f),
	 tour_angle_canon_retour  (0.0f),
	 tour_recul_canon  (0.0),
	 tour_recul_canon_retour  (0.0),
	 tour_distance_anneau  (0.0),
	 tour_epaisseur_anneau  (0.0),
	 tour_compt  (0.0f)
{}


void Tour::load_piece(){
	Tour::_piece_tour_corps= glGenLists(1);
		glNewList(_piece_tour_corps,GL_COMPILE);   Tour_DrawTourCorps(); glEndList();
}

void Tour::affiche_piece()
{
	DrawTour();
	if(fin_phase4_tour){
		set_a_attaquer();
	}
	if(fin_action_tour){
		set_anim_fini();
		action_tour = false; 
		fin_phase1_tour = false;
		fin_phase2_tour = false;
		fin_phase3_tour = false;
		fin_phase4_tour = false;
		fin_action_tour = false;
		tour_angle_canon1 = 0.0f;
		tour_angle_canon_retour = 0.0f;
		tour_recul_canon = 0.0;
		tour_recul_canon_retour = 0.0;
		tour_distance_anneau = 0.0;
		tour_epaisseur_anneau = 0.0;
		tour_compt = 0.0f;
	
	}
}

void Tour::animation()
{
	 action_tour = true;

}

void Tour::DrawTour() {
	glRotatef(-90,0,1,0);  	//pour orienter le tour vers -x
	
	glCallList(Tour::_piece_tour_corps);//Tour_DrawTourCorps();
	
	glTranslatef(0,3.75,0);
	glTranslatef(0, -0.5, 0);
	glColor3f(0.2,0.2,0.2);
	glCallList(Piece::_piece_piece_cylindre9);//DrawCylindre(0.5, 0.5, 0.3);
	glTranslatef(0, 0.5, 0);

	if (action_tour) {
		if (tour_angle_canon1 < 80) {tour_angle_canon1 += 1;}
		if (tour_angle_canon1 == 80) { fin_phase1_tour = true; }
	}
	if (fin_phase1_tour) {
		if (tour_recul_canon < 0.5) { tour_recul_canon += 0.05; }
		if (tour_recul_canon >= 0.5) { fin_phase2_tour = true; }
	}
	if (fin_phase2_tour) {
		if (tour_recul_canon_retour < 0.5) { tour_recul_canon_retour += 0.05; }
		if (tour_recul_canon_retour >= 0.5) { fin_phase3_tour = true; }
	}
	if (fin_phase3_tour) {
		if (tour_distance_anneau < 1) { tour_distance_anneau += 0.05; }
		if (tour_epaisseur_anneau < 0.05) { tour_epaisseur_anneau += 0.005; }
		if ((tour_distance_anneau >= 1)&&(tour_epaisseur_anneau>=0.05)) { fin_phase4_tour = true; }
	}
	if ((fin_phase4_tour)&&(tour_compt>=100)) {
		if (tour_angle_canon_retour < 80) { tour_angle_canon_retour += 1; }
		if (tour_angle_canon_retour == 80) { fin_action_tour = true; }
	}
	glColor3f(0.2,0.2,0.2);
	glRotatef(tour_angle_canon1, 1, 0, 0);	//Animation descente du canon
	glRotatef(-tour_angle_canon_retour, 1, 0, 0);
	glCallList(Piece::_piece_piece_sphere5);//DrawSphere(0.5);
	
	glTranslatef(0, 0.3, 0);
	glTranslatef(0, -tour_recul_canon, 0);	//Animation recul du canon
	glTranslatef(0, tour_recul_canon_retour, 0);
	glColor3f(0.5,0.5,0.5);
	glCallList(Piece::_piece_piece_cylindre7);//DrawCylindre(0.3,0.3,1.2);
		glTranslatef(0, 1.2, 0) ;
		glCallList(Piece::_piece_piece_cylindre8);//DrawCylindre(0.4,0.4, 0.2);
		
		if (fin_phase3_tour && !fin_phase4_tour) {
			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0, tour_distance_anneau, 0);
			glTranslatef(0, 0.3, 0);
			glRotatef(90, 1, 0, 0);
			Tour_DrawAnneau(0.055 - tour_epaisseur_anneau, 8, 0.5, 25);
			//epaisseur_anneau fin : 0.055
			glRotatef(-90, 1, 0, 0);
			glTranslatef(0, -0.3, 0);
			glTranslatef(0, -tour_distance_anneau, 0);
		}
		if(fin_phase3_tour) tour_compt++;
		glTranslatef(0, -1.2, 0);
	glTranslatef(0, +tour_recul_canon, 0);	//inverse
	glTranslatef(0, -tour_recul_canon_retour, 0);
	glTranslatef(0, -0.3, 0);
	glRotatef(-tour_angle_canon1, 1, 0, 0);	//inverse
	glRotatef(tour_angle_canon_retour, 1, 0, 0); //inverse
	glTranslatef(0, -3.9, 0);

	glRotatef(90,0,1,0);
	glColor3f(1,1,1);
	if (get_joueur()) 	
		glCallList(Piece::_piece_piece_baseArgent);
	else
		glCallList(Piece::_piece_piece_baseOr);
}


void Tour::Tour_DrawAnneau(float rc, int numc, float rt, int numt) {
	int i, j, k;
	double s, t;
	double x, y, z;
	double pi, twopi;
	pi = 3.14159265358979323846;
	twopi = 2 * pi;
	for (i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;
				x = cos(t*twopi / numt) * cos(s*twopi / numc);
				y = sin(t*twopi / numt) * cos(s*twopi / numc);
				z = sin(s*twopi / numc);
				glNormal3f((float)x, (float)y, (float)z);
				x = (rt + rc * cos(s*twopi / numc)) * cos(t*twopi / numt);
				y = (rt + rc * cos(s*twopi / numc)) * sin(t*twopi / numt);
				z = rc * sin(s*twopi / numc);
				glVertex3f((float)x, (float)y, (float)z);
			}
		}
		glEnd();
	}
}

void Tour::Tour_DrawTourCorps(){
	glBindTexture (GL_TEXTURE_2D, textures[2]);
	glEnable(GL_TEXTURE_2D);
	
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.4, 0);
	glBegin(GL_QUADS);

	//======================= Niveau 1 =========================
	//Face en bas niveau 1
	glVertex3f(1.3, 0, 1.3);	//B
	glVertex3f(1.3, 0, -1.3);	//C
	glVertex3f(-1.3, 0, -1.3);	//D
	glVertex3f(-1.3, 0, 1.3);	//A

	//Face en haut niveau 1
	glVertex3f(1.1,0.5,1.1);	//B'
	glVertex3f(1.1, 0.5, -1.1);	//C'
	glVertex3f(-1.1, 0.5, -1.1);//D'
	glVertex3f(-1.1, 0.5, 1.1);	//A'
	//Face devant A'ABB'
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1, 0.5, 1.1);	//A'
	glTexCoord2f(0, 0.0);glVertex3f(-1.3, 0, 1.3);	//A
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 0, 1.3);	//B
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 0.5, 1.1);	//B'
	//Face droite B'BCC'
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 0.5, 1.1);	//B'
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 0, 1.3);	//B
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 0, -1.3);	//C
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 0.5, -1.1);	//C'
	//FACE derriere C'CDD'
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 0.5, -1.1);	//C'
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 0, -1.3);	//C
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 0, -1.3);	//D
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 0.5, -1.1);//D'
	//FACE GAUCHE D'DAA'
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1, 0.5, -1.1);//D'
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.3, 0, -1.3);	//D
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 0, 1.3);	//A
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 0.5, 1.1);	//A'
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, textures[3]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//====================== Niveau 2 ======================
	//FACE DEVANT EA'B'F
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1, 3, 1.1);	//E
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.1, 0.5, 1.1);	//A'
	glTexCoord2f(1.0, 0.0);glVertex3f(1.1, 0.5, 1.1);	//B'
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 3, 1.1);	//F
	
	//FACE DROITE FB'C'G
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 3, 1.1);	//F
	glTexCoord2f(0.0, 0.0);glVertex3f(1.1, 0.5, 1.1);	//B'
	glTexCoord2f(1.0, 0.0);glVertex3f(1.1, 0.5, -1.1);	//C'
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 3, -1.1);	//G
	//FACE DERRIERE GC'D'H
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 3, -1.1);	//G
	glTexCoord2f(0.0, 0.0);glVertex3f(1.1, 0.5, -1.1);	//C'
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.1, 0.5, -1.1);//D'
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 3, -1.1);	//H
	//FACE GAUCHE HD'A'E
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1, 3, -1.1);	//H
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.1, 0.5, -1.1);//D'
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.1, 0.5, 1.1);	//A'
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 3, 1.1);	//E
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, textures[2]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//====================== Niveau 3 =======================
	//FACE devant E'EFF'
	glTexCoord2f(0.0, 0.5);glVertex3f(-1.3,3.2,1.3);	//E'
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.1, 3, 1.1);	//E
	glTexCoord2f(1, 0.0);glVertex3f(1.1, 3, 1.1);	//F
	glTexCoord2f(1, 0.5);glVertex3f(1.3,3.2,1.3);	//F'
	
	//FACE DROITE  F'FGG'
	glTexCoord2f(0.0, 0.5);glVertex3f(1.3, 3.2, 1.3);	//F'
	glTexCoord2f(0.0, 0.0);glVertex3f(1.1, 3, 1.1);	//F
	glTexCoord2f(1, 0.0);glVertex3f(1.1, 3, -1.1);	//G
	glTexCoord2f(1, 0.5);glVertex3f(1.3,3.2,-1.3);	//G'
	//FACE DRRIERE G'GHH'
	glTexCoord2f(0.0, 0.5);glVertex3f(1.3, 3.2, -1.3);	//G'
	glTexCoord2f(0.0, 0.0);glVertex3f(1.1, 3, -1.1);	//G
	glTexCoord2f(1, 0.0);glVertex3f(-1.1, 3, -1.1);	//H
	glTexCoord2f(1, 0.5);glVertex3f(-1.3, 3.2, -1.3);//H'
	//FACE GAUCHE H'HEE'
	glTexCoord2f(0.0, 0.5);glVertex3f(-1.3, 3.2, -1.3);//H'
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.1, 3, -1.1);	//H
	glTexCoord2f(1, 0.0);glVertex3f(-1.1, 3, 1.1);	//E
	glTexCoord2f(1, 0.5);glVertex3f(-1.3, 3.2, 1.3);	//E'
	
	//====================== Niveau 4 =======================
	//FACE DEVANT E"E'F'F"
	glTexCoord2f(0.0, 0.5);glVertex3f(-1.3, 3.5, 1.3);	//E"
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.3, 3.2, 1.3);	//E'
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 3.2, 1.3);	//F'
	glTexCoord2f(1.0, 0.5);glVertex3f(1.3, 3.5, 1.3);	//F"
	//FACE DROITE F"F'G'G"
	glTexCoord2f(0.0, 0.5);glVertex3f(1.3, 3.5, 1.3);	//F"
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 3.2, 1.3);	//F'
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 3.2, -1.3);	//G'
	glTexCoord2f(1.0, 0.5);glVertex3f(1.3, 3.5, -1.3);	//G"
	//FACE DERRIERE G"G'H'H"
	glTexCoord2f(0.0, 0.5);glVertex3f(1.3, 3.5, -1.3);	//G"
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 3.2, -1.3);	//G'
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 3.2, -1.3);//H'
	glTexCoord2f(1.0, 0.5);glVertex3f(-1.3, 3.5, -1.3);//H"
	//FACE GAUCHE H"H'E'E"
	glTexCoord2f(0.0, 0.5);glVertex3f(-1.3, 3.5, -1.3);//H"
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.3, 3.2, -1.3);//H'
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 3.2, 1.3);	//E'
	glTexCoord2f(1.0, 0.5);glVertex3f(-1.3, 3.5, 1.3);	//E"
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glBindTexture (GL_TEXTURE_2D, textures[3]);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//===================== Niveau 4 bis ====================
	//FACE H_E_F_G_
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1,3.4,-1.1);	//H_
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.1,3.4,1.1);	//E_
	glTexCoord2f(1.0, 0.0);glVertex3f(1.1,3.4,1.1);	//F_
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1,3.4,-1.1);	//G_
	//FACE E_E"F"F_
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1, 3.4, 1.1);	//E_
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.3, 3.5, 1.3);	//E"
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 3.5, 1.3);	//F"
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 3.4, 1.1);	//F_
	//FACE F_F"G"G_
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 3.4, 1.1);	//F_
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 3.5, 1.3);	//F"
	glTexCoord2f(1.0, 0.0);glVertex3f(1.3, 3.5, -1.3);	//G"
	glTexCoord2f(1.0, 1.0);glVertex3f(1.1, 3.4, -1.1);	//G_
	//FACE G_G"H"H_
	glTexCoord2f(0.0, 1.0);glVertex3f(1.1, 3.4, -1.1);	//G_
	glTexCoord2f(0.0, 0.0);glVertex3f(1.3, 3.5, -1.3);	//G"
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 3.5, -1.3);//H"
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 3.4, -1.1);	//H_
	//FACE H_H"E"E_
	glTexCoord2f(0.0, 1.0);glVertex3f(-1.1,3.4,-1.1);	//H_
	glTexCoord2f(0.0, 0.0);glVertex3f(-1.3, 3.5, -1.3);//H"
	glTexCoord2f(1.0, 0.0);glVertex3f(-1.3, 3.5, 1.3);	//E"
	glTexCoord2f(1.0, 1.0);glVertex3f(-1.1, 3.4, 1.1);	//E_
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

