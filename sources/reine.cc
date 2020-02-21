#include "reine.hh"
#include <iostream>

GLuint Reine::_piece_reine_couronne;
GLuint Reine::_piece_reine_tete;
GLuint Reine::_piece_reine_arc;
GLuint Reine::_piece_reine_main;
GLuint Reine::_piece_reine_jambe1;
GLuint Reine::_piece_reine_jambe2;
GLuint Reine::_piece_reine_corps;
GLuint Reine::_piece_reine_robe;

Reine::Reine(std::shared_ptr<Case> const & case_support ,bool joueur):
	Piece(type_piece::reine ,case_support , joueur ),
	 action_reine(false),
	 fin_action_dame  (false),
	 fin_phase1_dame  (false),
	 fin_phase2_dame  (false),
	 fin_phase3_dame  (false),
	 fin_phase4_dame  (false),
	 reine_angle_fix ( 60.0f),
	 reine_angle_avantbras ( 0.0f),
	 reine_angle_avantbras_retour  (0.0f),
	 reine_angle_bras  (0.0f),
	 reine_angle_bras_retour  (0.0f),
	 reine_angle_bras_etendu (0.0f),
	 reine_angle_bras_etendu_retour  (0.0f),
	 reine_angle_bras_lever  (0.0f),
	 reine_angle_bras_lever_retour  (0.0f),
	 reine_angle_attraper  (0.0f),
	 reine_angle_attraper_retour  (0.0f),
	 reine_angle_tirer  (0.0f),
	 reine_angle_lacher  (0.0f),
	 reine_angle_lacher_retour (0.0f),
	 reine_angle_avantbras_retour_gauche  (0.0f),
	 reine_angle_corps  (0.0f),
	 reine_angle_corps_retour  (0.0f)
{}

void Reine::affichage_attaque()
{
	if ((_nb_deplacement==0 && _anim_fini && !_peut_bouger))
	{
		glPushMatrix();
			translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
			//rotation
			orientation(_case_support->get_pos_pion() ,_points_intermediaires[_nb_deplacement], _case_support->get_norm() );

			affiche_piece();
		glPopMatrix();
	}
	else
	{
		if (_nb_deplacement!=0 || (_nb_deplacement==0 && _anim_fini && _peut_bouger)) //on avance jusque a la case d'attaque
		{
			
			if (_nb_deplacement<0)
			{
				_peut_bouger=false;
			}

			glPushMatrix();
				if (_avancement_dir2<1)
				{			
					translation( _case_support->get_pos_pion().get_coord_x()*(1-_avancement_dir2),
								_case_support->get_pos_pion().get_coord_y()*(1-_avancement_dir2),
								_case_support->get_pos_pion().get_coord_z()*(1-_avancement_dir2));
					translation( _points_intermediaires[_nb_deplacement].get_coord_x()*(_avancement_dir2),
								_points_intermediaires[_nb_deplacement].get_coord_y()*(_avancement_dir2),
								_points_intermediaires[_nb_deplacement].get_coord_z()*(_avancement_dir2));
								
					orientation( _points_intermediaires[_nb_deplacement],_chemin[_nb_deplacement]->get_pos_pion(),_case_support->get_norm());			
			
					_avancement_dir2+=0.06;	
				}
				else
				{
					translation(_points_intermediaires[_nb_deplacement].get_coord_x()*(1-_avancement_dir),
								_points_intermediaires[_nb_deplacement].get_coord_y()*(1-_avancement_dir),
								_points_intermediaires[_nb_deplacement].get_coord_z()*(1-_avancement_dir));
					translation( _chemin[_nb_deplacement]->get_pos_pion().get_coord_x()*(_avancement_dir),
								_chemin[_nb_deplacement]->get_pos_pion().get_coord_y()*(_avancement_dir),
								_chemin[_nb_deplacement]->get_pos_pion().get_coord_z()*(_avancement_dir));
								
					orientation( _points_intermediaires[_nb_deplacement],_chemin[_nb_deplacement]->get_pos_pion(),_case_support->get_norm());			
						
					_avancement_dir+=0.06;											
				}		
				
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
					_a_attaquer=false;
					_anim_fini=false;
				}
			}
		}
		else
		{			
			if (_nb_deplacement==0 && !_anim_fini) // on fais l'animation
			{
				glPushMatrix();
					translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
					//rotation
					orientation(_case_support->get_pos_pion() ,_points_intermediaires[_nb_deplacement], _case_support->get_norm() );
					
					animation();
					affiche_piece();
				glPopMatrix();
			}
		}
	}	
}

void Reine::load_piece()
{

	
	Reine::_piece_reine_couronne= glGenLists(1);
		glNewList(_piece_reine_couronne,GL_COMPILE);	Reine_DrawCouronne_reine(0.55,0.5);glEndList();
	Reine::_piece_reine_tete = glGenLists(1);
		glNewList(_piece_reine_tete,GL_COMPILE);   Reine_DrawTete(); 	glEndList();
	Reine::_piece_reine_arc = glGenLists(1);
		glNewList(_piece_reine_arc,GL_COMPILE);   Reine_DrawArc();	glEndList();
	Reine::_piece_reine_main = glGenLists(1);
		glNewList(_piece_reine_main,GL_COMPILE);   DrawMain(60); 		glEndList();
	Reine::_piece_reine_jambe1 = glGenLists(1);
		glNewList(_piece_reine_jambe1,GL_COMPILE);   Reine_DrawJambre(15); glEndList();
	Reine::_piece_reine_jambe2 = glGenLists(1);
		glNewList(_piece_reine_jambe2,GL_COMPILE);   Reine_DrawJambre(-15);glEndList();
	Reine::_piece_reine_corps = glGenLists(1);
		glNewList(_piece_reine_corps,GL_COMPILE);   Reine_DrawCorps();glEndList();
	Reine::_piece_reine_robe = glGenLists(1);
		glNewList(_piece_reine_robe,GL_COMPILE);   Reine_DrawRobe(3.1); glEndList();

}


//à changer glCallList

void Reine::affiche_piece()
{
	DrawReine();
	
	if(fin_phase4_dame){
		set_a_attaquer();
	}
	if(fin_action_dame){
		set_anim_fini();
		action_reine=false;
		fin_action_dame = false;
		fin_phase1_dame = false;
		fin_phase2_dame = false;
		fin_phase3_dame = false;
		fin_phase4_dame = false;
		reine_angle_fix = 60.0f;
		reine_angle_avantbras = 0.0f;
		reine_angle_avantbras_retour = 0.0f;
		reine_angle_bras = 0.0f;
		reine_angle_bras_retour = 0.0f;
		reine_angle_bras_etendu = 0.0f;
		reine_angle_bras_etendu_retour = 0.0f;
		reine_angle_bras_lever = 0.0f;
		reine_angle_bras_lever_retour = 0.0f;
		reine_angle_attraper = 0.0f;
		reine_angle_attraper_retour = 0.0f;
		reine_angle_tirer = 0.0f;
		reine_angle_lacher = 0.0f;
		reine_angle_lacher_retour=0.0f;
		reine_angle_avantbras_retour_gauche = 0.0f;
		reine_angle_corps = 0.0f;
		reine_angle_corps_retour = 0.0f;
	
	}
	
}

void Reine::animation()
{
	action_reine = true;
}

void Reine::Reine_DrawCouronne_reine(float n, float n2) {
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
		glColor3f(1,1,1);
	}
	glPopMatrix();
}

void Reine::Reine_DrawTete() {
	
	glPushMatrix();
	{
		glColor3ub(254,195,172);
		glCallList(Piece::_piece_piece_sphere1);//DrawSphere(0.55);
		glColor3f(1,1,1);
		glTranslatef(0, 0.3, 0);
		glCallList(_piece_reine_couronne);//DrawCouronne_reine(0.55, 0.5);
		glTranslatef(0, -0.3, 0);
	
	}
	glPopMatrix();
}

void Reine::Reine_DrawArc(){
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[17]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//==========Partie 1 (milieu)========
		//FACE Dessus
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.8,0,-0.1); //C'
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.8,0,-0.1); //B'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.8,0,0.1); //A'
		//FACE Desous
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,-0.2,0.1); //A
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.8,-0.2,-0.1); //B
		glTexCoord2f(1.0, 0.0);glVertex3f(0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(0.8,-0.2,0.1);  //D
		//FACE DEVANT A'ADD'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,0,0.1); //A'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.8,-0.2,0.1); //A
		glTexCoord2f(1.0, 0.0);glVertex3f(0.8,-0.2,0.1);  //D
		glTexCoord2f(1.0, 1.0);glVertex3f(0.8,0,0.1);  //D'
		//FACE DROITE D'DCC'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.8,-0.2,0.1);  //D
		glTexCoord2f(1.0, 0.0);glVertex3f(0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(0.8,0,-0.1); //C'
		//FACE DERRIERE C'CBB'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,0,-0.1); //C'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.8,-0.2,-0.1); //B
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.8,0,-0.1); //B'
		//FACE GAUCHE B'BAA'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,0,-0.1); //B'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.8,-0.2,-0.1); //B
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.8,-0.2,0.1); //A
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.8,0,0.1); //A'
		//========Partie 2-1 (droite)==========
		
		//FACE D'E'F'C' (dessus)
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(1.4,-0.5,0.1); //E'
		glTexCoord2f(1.0, 0.0);glVertex3f(1.4,-0.5,-0.1); //F'
		glTexCoord2f(1.0, 1.0);glVertex3f(0.8,0,-0.1); //C'
		//FACE DCFE (dessous)
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,-0.2,0.1);  //D
		glTexCoord2f(0.0, 0.0);glVertex3f(0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 0.0);glVertex3f(1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(1.4,-0.7,0.1); //E
		//FACE D'DEE'
		glTexCoord2f(0.0, 1.0);glVertex3f(0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(0.8,-0.2,0.1);  //D
		glTexCoord2f(1.0, 0.0);glVertex3f(1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 1.0);glVertex3f(1.4,-0.5,0.1); //E'
		//FACE E'EFF'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 0.0);glVertex3f(1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(1.4,-0.5,-0.1); //F'
		//FACE F'FCC'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.4,-0.5,-0.1); //F'
		glTexCoord2f(0.0, 0.0);glVertex3f(1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(0.8,0,-0.1); //C'
		
		//=======Partie 2-2 (gauche) ==========partie symétrique
		//FACE D'E'F'C' (dessus)
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(-1.4,-0.5,0.1); //E'
		glTexCoord2f(1.0, 0.0);glVertex3f(-1.4,-0.5,-0.1); //F'
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.8,0,-0.1); //C'
		//FACE DCFE (dessous)
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,-0.2,0.1);  //D
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 0.0);glVertex3f(-1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(-1.4,-0.7,0.1); //E
		//FACE D'DEE'
		glTexCoord2f(0.0, 1.0);glVertex3f(-0.8,0,0.1);  //D'
		glTexCoord2f(0.0, 0.0);glVertex3f(-0.8,-0.2,0.1);  //D
		glTexCoord2f(1.0, 0.0);glVertex3f(-1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 1.0);glVertex3f(-1.4,-0.5,0.1); //E'
		//FACE E'EFF'
		glTexCoord2f(0.0, 1.0);glVertex3f(-1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(-1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 0.0);glVertex3f(-1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(-1.4,-0.5,-0.1); //F'
		//FACE F'FCC'
		glTexCoord2f(0.0, 1.0);glVertex3f(-1.4,-0.5,-0.1); //F'
		glTexCoord2f(0.0, 0.0);glVertex3f(-1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(-0.8,-0.2,-0.1); //C
		glTexCoord2f(1.0, 1.0);glVertex3f(-0.8,0,-0.1); //C'
		
		//=======Partie 3-1 (droite) ========== 
		//FACE E'EGG'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 0.0);glVertex3f(2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 1.0);glVertex3f(2.4,0.7,0.1); //G'
		//FACE G'GHH'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 0.0);glVertex3f(2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(2.4,0.7,-0.1); //H'
		//FACE H'HFF'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.4,0.7,-0.1); //H'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(1.4,-0.5,-0.1); //F'
		//FACE E'G'H'F'
		glTexCoord2f(0.0, 1.0);glVertex3f(1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.4,0.7,0.1); //G'
		glTexCoord2f(1.0, 0.0);glVertex3f(2.4,0.7,-0.1); //H'
		glTexCoord2f(1.0, 1.0);glVertex3f(1.4,-0.5,-0.1); //F'
		//FACE EFHG
		glTexCoord2f(0.0, 1.0);glVertex3f(1.4,-0.7,0.1); //E
		glTexCoord2f(0.0, 0.0);glVertex3f(1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(2.4,0.5,0.1); //G
		
		//======Partie 3-2 (gauche) ==========
				//FACE E'EGG'
		glTexCoord2f(0.0, 1.0);glVertex3f(-1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(-1.4,-0.7,0.1); //E
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.4,0.7,0.1); //G'
		//FACE G'GHH'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.4,0.7,-0.1); //H'
		//FACE H'HFF'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.4,0.7,-0.1); //H'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(-1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 1.0);glVertex3f(-1.4,-0.5,-0.1); //F'
		//FACE E'G'H'F'
		glTexCoord2f(0.0, 1.0);glVertex3f(-1.4,-0.5,0.1); //E'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.4,0.7,0.1); //G'
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.4,0.7,-0.1); //H'
		glTexCoord2f(1.0, 1.0);glVertex3f(-1.4,-0.5,-0.1); //F'
		//FACE EFHG
		glTexCoord2f(0.0, 1.0);glVertex3f(-1.4,-0.7,0.1); //E
		glTexCoord2f(0.0, 0.0);glVertex3f(-1.4,-0.7,-0.1); //F
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.4,0.5,0.1); //G
		
		//=========Partie 4-1 (droite cube) ==========
		//FACE DESSUS G'I'J'H'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.6,0.7,0.1); //I'
		glTexCoord2f(1.0, 0.0);glVertex3f(2.6,0.7,-0.1); //J'
		glTexCoord2f(1.0, 1.0);glVertex3f(2.4,0.7,-0.1); //H'
		//Face avant G'GII'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 0.0);glVertex3f(2.6,0.5,0.1); //I
		glTexCoord2f(1.0, 1.0);	glVertex3f(2.6,0.7,0.1); //I'
		//FACE DROITE I'IJJ'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.6,0.7,0.1); //I'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.6,0.5,0.1); //I
		glTexCoord2f(1.0, 0.0);glVertex3f(2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 1.0);glVertex3f(2.6,0.7,-0.1); //J'
		//FACE DERRIERE J'JHH'
		glTexCoord2f(0.0, 1.0);glVertex3f(2.6,0.7,-0.1); //J'
		glTexCoord2f(0.0, 0.0);glVertex3f(2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 0.0);glVertex3f(2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(2.4,0.7,-0.1); //H'
		//FACE GHJI
		glTexCoord2f(0.0, 1.0);glVertex3f(2.4,0.5,0.1); //G
		glTexCoord2f(0.0, 0.0);glVertex3f(2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 1.0);	glVertex3f(2.6,0.5,0.1); //I

		
		
		
		//=========Partie 4-2 (gauche cube) =========symetrique
		//FACE DESSUS G'I'J'H'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.6,0.7,0.1); //I'
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.6,0.7,-0.1); //J'
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.4,0.7,-0.1); //H'
		//Face avant G'GII'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.4,0.7,0.1); //G'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.4,0.5,0.1); //G
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.6,0.5,0.1); //I
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.6,0.7,0.1); //I'
		//FACE DROITE I'IJJ'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.6,0.7,0.1); //I'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.6,0.5,0.1); //I
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.6,0.7,-0.1); //J'
		//FACE DERRIERE J'JHH'
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.6,0.7,-0.1); //J'
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.4,0.7,-0.1); //H'
		//FACE GHJI
		glTexCoord2f(0.0, 1.0);glVertex3f(-2.4,0.5,0.1); //G
		glTexCoord2f(0.0, 0.0);glVertex3f(-2.4,0.5,-0.1); //H
		glTexCoord2f(1.0, 0.0);glVertex3f(-2.6,0.5,-0.1); //J
		glTexCoord2f(1.0, 1.0);glVertex3f(-2.6,0.5,0.1); //I
		glEnd();

		//================LA CORDE================
		//Animation pour la corde 
		
		glTranslatef(-2.6,0.6,0);
		//glRotatef(angle_corde,0,0,1);
		//glRotatef(-angle_corde_retour,0,0,1);
		glTranslatef(2.6,-0.6,0);
		
		glColor3f(0,0,0);
		//Corde en haut
		glPushMatrix();
		{
		glBegin(GL_LINES);
		glVertex3f(-2.6,0.6,0);
		glVertex3f(0,0.6,0);
		glEnd();
		}
		glPopMatrix();
		
		glTranslatef(-2.6,0.6,0); //inverse
		//glRotatef(-angle_corde,0,0,1); 	//inverse
		//glRotatef(angle_corde_retour,0,0,1); //inverse
		glTranslatef(2.6,-0.6,0); //inverse
		glDisable(GL_TEXTURE_2D);
		//=========================================
		//Animation pour la corde 
		//Corde en bas
		
		glTranslatef(2.6,0.6,0);
		//glRotatef(-angle_corde,0,0,1);
		//glRotatef(angle_corde_retour,0,0,1);
		glTranslatef(-2.6,-0.6,0);
		
		glPushMatrix();
		{
		glBegin(GL_LINES);
		glVertex3f(2.6,0.6,0);
		glVertex3f(0,0.6,0);
		glEnd();
		}
		glPopMatrix();
		glColor3f(1,1,1);
		glTranslatef(2.6,0.6,0); 		//inverse
		//glRotatef(angle_corde,0,0,1); 	//inverse
		//glRotatef(-angle_corde_retour,0,0,1); //inverse
		glTranslatef(-2.6,-0.6,0); 		//inverse
		
	}
	glPopMatrix();
}

void Reine::Reine_DrawJambre(float degree) {
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

void Reine::Reine_DrawCorps() {
	glBindTexture (GL_TEXTURE_2D, textures[16]);
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

void Reine::Reine_DrawBrasGauche() {
	
	//ANIMATION
	if(action_reine){
		if(reine_angle_avantbras<40){reine_angle_avantbras++;}
		if(reine_angle_bras<90) {reine_angle_bras++;}
		if(reine_angle_bras_etendu<90) {reine_angle_bras_etendu++;}
		if(reine_angle_avantbras>=40 && reine_angle_bras>=70 && reine_angle_bras_etendu>=90) {fin_phase1_dame = true;}
	}
	
	if(fin_phase4_dame){
		if(reine_angle_avantbras_retour<40){reine_angle_avantbras_retour++;}
		if(reine_angle_bras_retour<80) {reine_angle_bras_retour++;}
		if(reine_angle_bras_etendu_retour<90) {reine_angle_bras_etendu_retour++;}
	}
	
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[16]);
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
		
		glBindTexture (GL_TEXTURE_2D, textures[15]);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glRotatef(-30,1,0,0);		//bras vers l'avant
		glRotatef(-reine_angle_bras_etendu,0,1,0);	//etendre le bras 
		glRotatef(reine_angle_bras_etendu_retour,0,1,0); 
		glRotatef(-reine_angle_bras, 1, 0, 0); //ici pour l'Animation des bras	
		glRotatef(reine_angle_bras_retour, 1, 0, 0);
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.2, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3ub(107,13,13);
		DrawSphere(0.3);
		glColor3f(1,1,1);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glRotatef(60,0,0,1);	//avant bras vers l'avant
		glRotatef(-reine_angle_avantbras,0,0,1);	//Animation avant bras
		glRotatef(reine_angle_avantbras_retour,0,0,1);
		glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -0.8, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3ub(107,13,13);
		DrawSphere(0.2);
		glColor3f(1,1,1);
		//====Pour inserer la main=====
		glTranslatef(-0.15, -0.45, 0);
		glRotatef(-180, 1, 0, 0);
		glCallList(_piece_reine_main);//DrawMain(angle_fix);
		//====Pour inserer l'arc=======
		glRotatef(180,1,0,0);
		glRotatef(20,0,1,0);
		glCallList(_piece_reine_arc);//DrawArc();
		glRotatef(-20,0,1,0);
		glRotatef(-180,1,0,0);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.15, 0.45, 0);

		glTranslatef(-0.5, 2.5, 0);
		glRotatef(-60,0,0,1); 	//inverse avant bras vers l'avant
		glRotatef(-reine_angle_avantbras,0,0,1);	//inverse 
		glRotatef(reine_angle_avantbras_retour,0,0,1);
		glRotatef(reine_angle_bras_etendu,0,1,0); //inverse etendre le bras
		glRotatef(-reine_angle_bras_etendu_retour,0,1,0);
		glRotatef(30,1,0,0);	//inverse bras vers l'avant
	}
	glPopMatrix();
}

void Reine::Reine_DrawBrasDroite() {
	if(action_reine){
		if(reine_angle_bras_lever<70){reine_angle_bras_lever++;}
		if(reine_angle_attraper<30) {reine_angle_attraper++;}
	}
	//PHASE 2 Attraper la corde
	if(fin_phase1_dame){
		if(reine_angle_attraper_retour<20) {reine_angle_attraper_retour++;}
		//if(angle_corde<45) {angle_corde++;}
		if(reine_angle_attraper_retour>=20) {fin_phase2_dame = true;}
	}
	//PHASE 3 tirer la corde
	if(fin_phase2_dame){
		if(reine_angle_tirer<20) {reine_angle_tirer++;}
		if(reine_angle_tirer>=20) {fin_phase3_dame = true;}
	}
	
	//PHASE 4 lacher la corde
	if(fin_phase3_dame){
		if(reine_angle_lacher<10) {reine_angle_lacher++;}
		//if(angle_corde_retour<45) {angle_corde_retour++;}
		if(reine_angle_lacher>=10){fin_phase4_dame = true;}
		
	}
	//PHASE 5 Retour
	if(fin_phase4_dame){
		if(reine_angle_bras_lever_retour<70){reine_angle_bras_lever_retour++;}
		if(reine_angle_lacher_retour<40) {reine_angle_lacher_retour++;}
		if(reine_angle_avantbras_retour_gauche<40) {reine_angle_avantbras_retour_gauche++;}
	}
	
	glColor3f(1,1,1);
	glPushMatrix();
	
	{	glBindTexture (GL_TEXTURE_2D, textures[16]);
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
		
		glBindTexture (GL_TEXTURE_2D, textures[15]);
		glEnable(GL_TEXTURE_2D);
		glTranslatef(0.5,-0.7,0);
		//glRotatef(angle_bras, 1, 0, 0); //ici pour l'Animation des bras	
		//glRotatef(-angle_bras_retour_fin, 1, 0, 0);
		glRotatef(180, 1, 0, 0);
		glRotatef(30,1,0,0);		//bras vers l'avant
		glRotatef(reine_angle_bras_lever,1,0,0);
		glRotatef(-reine_angle_bras_lever_retour,1,0,0);
		glRotatef(reine_angle_attraper,0,0,1);
		glRotatef(reine_angle_attraper_retour,0,0,1);
		glRotatef(-reine_angle_tirer,0,0,1);
		glRotatef(reine_angle_lacher,0,0,1);
		glRotatef(-reine_angle_lacher_retour,0,0,1);
		
		glCallList(Piece::_piece_piece_cylindre3);//DrawCylindre(0.4, 0.3, 1.2);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.2, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3ub(107,13,13);
		glCallList(Piece::_piece_piece_sphere2);//DrawSphere(0.3);
		glColor3f(1,1,1);
		
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glRotatef(70,0,0,1);	//avant bras vers l'avant
		glRotatef(-reine_angle_avantbras,0,0,1);	//Animation avant bras
		glRotatef(reine_angle_avantbras_retour_gauche,0,0,1);
		glCallList(Piece::_piece_piece_cylindre4);//DrawCylindre(0.3, 0.2, 0.8);
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -0.8, 0);
		glDisable(GL_TEXTURE_2D);
		glColor3ub(107,13,13);
		glCallList(Piece::_piece_piece_sphere3);//DrawSphere(0.2);
		glColor3f(1,1,1);
		
		//==Pour inserer la main
		glTranslatef(-0.15, -0.45, 0);
		glRotatef(-180, 1, 0, 0);
		glCallList(_piece_reine_main);//DrawMain(angle_fix);
		glEnable(GL_TEXTURE_2D);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0.15, 0.45, 0);

		glTranslatef(-0.5, 2.5, 0);
		glRotatef(-70,0,0,1);	//inverse avant bras vers l'avant
		

		glRotatef(-reine_angle_attraper,0,0,1);
		glRotatef(-reine_angle_attraper_retour,0,0,1);
		glRotatef(reine_angle_tirer,0,0,1);
		glRotatef(-reine_angle_lacher,0,0,1);
		glRotatef(reine_angle_lacher_retour,0,0,1);
		
		glRotatef(-reine_angle_bras_lever,1,0,0);
		glRotatef(reine_angle_bras_lever_retour,1,0,0);
		glRotatef(-30,1,0,0);		//inverse bras vers l'avant
		
	}
	glPopMatrix();
}

void Reine::Reine_DrawRobe(float n) {
	glBindTexture (GL_TEXTURE_2D, textures[18]);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	{
		glTranslatef(0, 1.5, 0);
		glRotatef(180, 1, 0, 0);
		glBegin(GL_TRIANGLE_FAN);
		bool paire = true;
		glColor3d(1,0.8,0.8);
		glTexCoord2f(0.5,1);glVertex3f(0, 0, 0);
		for (int k = 0; k <= 360; k += 20) {
			glColor3d(0.8,0.1,0.1);
			if(paire){
					glTexCoord2f(0,0);glVertex3f(n*Cos(k)/1.7, n * 1, n*Sin(k)/1.7);
					paire = true;
				}
				else{
					glTexCoord2f(1,0);glVertex3f(n*Cos(k)/1.7, n * 1, n*Sin(k)/1.7);
					paire = false;
				}
		}
		glEnd();
		glRotatef(-180, 1, 0, 0);
		glTranslatef(0, -1.5, 0);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Reine::DrawReine() {
	
	//Animation
	if(action_reine){
		if(reine_angle_corps<90){reine_angle_corps++;}
	}
	if(fin_phase4_dame){
		if(reine_angle_corps_retour<90) {reine_angle_corps_retour++;}
		if(reine_angle_corps_retour>=90) {fin_action_dame = true;}
	}
	
	glPushMatrix();
	{
		glTranslatef(-0.4, 0.4, -0.6);
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0.65, 0.35, 0);
				glCallList(_piece_reine_jambe1);//Reine_DrawJambre(15);
				glTranslatef(0, 0.55, 0.6);
				glRotatef(90, 0, 1, 0);
					glRotatef(-reine_angle_corps,0,1,0);	//Animation
					glRotatef(reine_angle_corps_retour,0,1,0);
				glCallList(_piece_reine_corps);//Reine_DrawCorps();
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, 2.6, 0.8);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(-0.3, -0.2, 0);
				Reine_DrawBrasGauche();
				
				glTranslatef(0.3, 0.2, 0);
				glRotatef(90, 0, 1, 0);
				glTranslatef(0, -2.6, -0.8);
				glTranslatef(0, 3, 0);
				glCallList(_piece_reine_tete);//Reine_DrawTete();
					glTranslatef(0, -3, 0);
					glCallList(_piece_reine_robe);//Reine_DrawRobe(3.1);
					glTranslatef(0, 3, 0);
				glTranslatef(0, -3, 0);

				//=============Partie symétrique===============
				glTranslatef(0, -1.65, 0.9);		//repositionner cette partie
				glTranslatef(0, 0.3, -0.35);
				glCallList(_piece_reine_jambe2);//Reine_DrawJambre(-15);

				glTranslatef(-0, 0.45, 0.6+0.35);
				glTranslatef(0, 2.6, -0.8 - 1.2);
				glRotatef(90, 0, 1, 0);

				//=========================================
				glTranslatef(0, -0.1, 0);
				
				Reine_DrawBrasDroite();
				
				glTranslatef(0, 0.1, 0);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(0, -2.6, 0.8 + 1.2);
				glRotatef(reine_angle_corps,0,1,0);	//inverse animation
				glRotatef(-reine_angle_corps_retour,0,1,0); //inverse
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

