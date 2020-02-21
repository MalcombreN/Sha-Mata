#include "piece.hh"
#include <iostream>

GLuint Piece::_piece_piece_sphere1;
GLuint Piece::_piece_piece_sphere2;
GLuint Piece::_piece_piece_sphere3;
GLuint Piece::_piece_piece_sphere4;
GLuint Piece::_piece_piece_sphere5;
GLuint Piece::_piece_piece_baseArgent;
GLuint Piece::_piece_piece_baseOr;
GLuint Piece::_piece_piece_phallanges;
GLuint Piece::_piece_piece_doigt;
GLuint Piece::_piece_piece_mains1;
GLuint Piece::_piece_piece_mains2;

GLuint Piece::_piece_piece_cylindre1;
GLuint Piece::_piece_piece_cylindre2;
GLuint Piece::_piece_piece_cylindre3;
GLuint Piece::_piece_piece_cylindre4;
GLuint Piece::_piece_piece_cylindre5;
GLuint Piece::_piece_piece_cylindre6;
GLuint Piece::_piece_piece_cylindre7;
GLuint Piece::_piece_piece_cylindre8;
GLuint Piece::_piece_piece_cylindre9;
GLuint Piece::_piece_piece_pied;
	
Piece::Piece(type_piece const & type , std::shared_ptr<Case> const & case_support ,bool joueur):
	_type(type),
	_case_support(case_support),
	_joueur(joueur),
	_etat_piece(0),
	_nb_deplacement(0),
	_avancement_dir(0),
	_avancement_dir2(0),
	_avancement_rot(0),
	_a_bouger(false),
	_a_attaquer(false),
	_peut_bouger(true),
	_anim_fini(false)
{}

std::shared_ptr<Case> Piece::get_case_support()const {return _case_support;}
bool Piece::get_joueur()const{ return _joueur;}
type_piece Piece::get_type()const {return _type;}
void Piece::set_a_bouger(){ _a_bouger=true;}
bool Piece::get_a_bouger()const {return _a_bouger;}
bool Piece::ready ()const {return _etat_piece==0;}

void Piece::orientation(Point const & centre , Point const & haut , Vecteur const & norm )
{
	//rotations dans l'espace
	
	if (norm.get_dir_y()>0)
	{
		rotation( (atan(norm.get_dir_z()/norm.get_dir_y())*180/M_PI),0,0);
		rotation(0,0, -(atan(norm.get_dir_x()/norm.get_dir_y())*180/M_PI));
	}
	if (norm.get_dir_y()<0)
	{
		rotation( (atan(norm.get_dir_z()/norm.get_dir_y())*180/M_PI) ,0,0);
		rotation(0,0, 180-(atan(norm.get_dir_x()/norm.get_dir_y())*180/M_PI));
	}
	if (norm.get_dir_y()==0)
	{
		
	}
	
	//rotations sens de la piece su un plan
	if( (haut.get_coord_x()-centre.get_coord_x())==0 &&
		(haut.get_coord_z()-centre.get_coord_z())!=0)
	{
		if ((haut.get_coord_z()-centre.get_coord_z())>0)
		{ rotation(0,90,0);	}
		else
		{ rotation(0,-90,0); }
	}
	if ((haut.get_coord_x()-centre.get_coord_x())<0)
	{
		rotation(0,(-atan((haut.get_coord_z()-centre.get_coord_z())/(haut.get_coord_x()-centre.get_coord_x()))*180/M_PI),0);
	} 
	if ((haut.get_coord_x()-centre.get_coord_x())>0)
	{
		rotation(0,(180-(atan((haut.get_coord_z()-centre.get_coord_z())/(haut.get_coord_x()-centre.get_coord_x()))*180/M_PI)),0);
	}  
}

void Piece::affichage_standard()
{
	glPushMatrix();
			translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
			//rotation
			
			if (_joueur)
				orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[0] , _case_support->get_norm());
			else
				orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[1] , _case_support->get_norm());
			
			affiche_piece();
		glPopMatrix();
}

void Piece::affichage_mouvement()
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
				
			orientation( _case_support->get_pos_pion(),_points_intermediaires[_nb_deplacement],_case_support->get_norm());
				
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
		}
	}
}

void Piece::affichage_attaque()
{
	if ((_nb_deplacement==_chemin.size()-1 && _anim_fini && !_peut_bouger))
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
		if (_nb_deplacement!=_chemin.size()-1 || (_nb_deplacement==_chemin.size()-1 && _anim_fini && _peut_bouger)) //on avance jusque a la case d'attaque
		{
			
			if (_nb_deplacement<_chemin.size()-1)
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
			if (_nb_deplacement==_chemin.size()-1 && !_anim_fini) // on fais l'animation
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

void Piece::affichage_mort()
{
	glPushMatrix();
		
		translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
		//rotation
		if (_joueur)
			orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[0] , _case_support->get_norm() );
		else
			orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[1] , _case_support->get_norm() );	
			
		aggrandissement((1-_avancement_dir),(1-_avancement_dir),(1-_avancement_dir));
		affiche_piece();
	glPopMatrix();
	_avancement_dir+=0.1;
	if (_avancement_dir>=1)
	{
		_avancement_dir=0;
		_etat_piece=5;
	}	
}

void Piece::affichage_ressussite()
{
	glPushMatrix();
		translation( _case_support->get_pos_pion().get_coord_x(),_case_support->get_pos_pion().get_coord_y(),_case_support->get_pos_pion().get_coord_z());
		//rotation
		if (_joueur)
			orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[0] , _case_support->get_norm() );
		else
			orientation(_case_support->get_pos_pion() , _case_support->get_centre_bords_cases()[1] , _case_support->get_norm() );
			
		aggrandissement(_avancement_dir,_avancement_dir,_avancement_dir);
		affiche_piece();
	glPopMatrix();
	_avancement_dir+=0.1;
	if (_avancement_dir>=1)
	{
		_avancement_dir=0;
		_etat_piece=0;
	}
}

void Piece::display()
{	
	if (_etat_piece==0 )
	{
		this->affichage_standard();
	}
	if (_etat_piece==1)
	{ 
		this->affichage_mouvement();
	}
	if (_etat_piece==2)
	{
		this->affichage_attaque();
	}
	if (_etat_piece==3)
	{
		this->affichage_mort();
	}
	if (_etat_piece==4)
	{
		this->affichage_ressussite();
	}
	if (_etat_piece==5)
	{
		//etat cacher
	}
}

void Piece::tuer()
{
	_etat_piece=3;
}

void Piece::ressussiter()
{
	if (this->disparue())
	{
		_etat_piece=4;
	}
}

bool Piece::disparue() const
{
	return (_etat_piece==5);
}

void Piece::disparait()
{
	_etat_piece=5;
}

void Piece::deplacement(std::vector<std::shared_ptr<Case>> const & chemin , std::vector<Point> const & intermediaires)
{
	_a_bouger=true;
	_chemin=chemin;	
	_points_intermediaires=intermediaires;
	_etat_piece=1;
}

void Piece::attaque(std::vector<std::shared_ptr<Case>> const & chemin , std::vector<Point> const & intermediaires)
{
	_a_bouger=true;
	_chemin=chemin;	
	_points_intermediaires=intermediaires;
	_etat_piece=2;
}

bool Piece::get_a_attaquer()const {return _a_attaquer;}

void Piece::termine_deplacement()
{
	_peut_bouger=true;
}



void Piece::set_a_attaquer() {_a_attaquer=true;}
void Piece::set_anim_fini() {_anim_fini=true;}
void Piece::set_case_support(std::shared_ptr<Case> const & ptr) {_case_support=ptr;}



//====================================================================================

void Piece::load_piece()
{
	_piece_piece_sphere1= glGenLists(1);
	glNewList(_piece_piece_sphere1,GL_COMPILE);	DrawSphere(0.55);	glEndList();
	
	_piece_piece_sphere2= glGenLists(1);
	glNewList(_piece_piece_sphere2,GL_COMPILE);	DrawSphere(0.3);	glEndList();
	
	_piece_piece_sphere3= glGenLists(1);
	glNewList(_piece_piece_sphere3,GL_COMPILE);	DrawSphere(0.2);	glEndList();
	
	_piece_piece_sphere4= glGenLists(1);
	glNewList(_piece_piece_sphere4,GL_COMPILE);	DrawSphere(0.65);	glEndList();
	
	_piece_piece_baseArgent= glGenLists(1);
	glNewList(_piece_piece_baseArgent,GL_COMPILE);	DrawBase_Argent();			glEndList();
	
	_piece_piece_baseOr= glGenLists(1);
	glNewList(_piece_piece_baseOr,GL_COMPILE);	DrawBase_Or();			glEndList();
	

	_piece_piece_phallanges= glGenLists(1);
	glNewList(_piece_piece_phallanges,GL_COMPILE);	DrawPhalange();		glEndList();
	
	_piece_piece_doigt= glGenLists(1);
	glNewList(_piece_piece_doigt,GL_COMPILE);	DrawDoigt(30);		glEndList();
	
	_piece_piece_mains1= glGenLists(1);
	glNewList(_piece_piece_mains1,GL_COMPILE);	DrawMain(30);		glEndList();
	
	_piece_piece_mains2= glGenLists(1);
	glNewList(_piece_piece_mains2,GL_COMPILE);   DrawMain(60); 		glEndList();
	
	_piece_piece_cylindre1 = glGenLists(1);
	glNewList(_piece_piece_cylindre1,GL_COMPILE); DrawCylindre(0.125,0.3,0.7); glEndList();
	
	_piece_piece_cylindre2 = glGenLists(1);
	glNewList(_piece_piece_cylindre2,GL_COMPILE); DrawCylindre(0.3,0.4,0.65); glEndList();
	
	_piece_piece_cylindre3 = glGenLists(1);
	glNewList(_piece_piece_cylindre3,GL_COMPILE); DrawCylindre(0.4,0.3,1.2); glEndList();
	
	_piece_piece_cylindre4 = glGenLists(1);
	glNewList(_piece_piece_cylindre4,GL_COMPILE); DrawCylindre(0.3,0.2,0.8); glEndList();

	_piece_piece_pied = glGenLists(1);
	glNewList(_piece_piece_pied,GL_COMPILE); DrawPied(); glEndList();
	
	_piece_piece_cylindre5 = glGenLists(1);
	glNewList(_piece_piece_cylindre5,GL_COMPILE);DrawCylindre(0.125, 0.2, 0.7);glEndList();
	
	_piece_piece_cylindre6 = glGenLists(1);
	glNewList(_piece_piece_cylindre6,GL_COMPILE); DrawCylindre(0.2,0.3,0.65); glEndList();
	
	//pour le canon du tour
	_piece_piece_sphere5= glGenLists(1);
	glNewList(_piece_piece_sphere5,GL_COMPILE);	DrawSphere(0.5);	glEndList();
	
	_piece_piece_cylindre7 = glGenLists(1);
	glNewList(_piece_piece_cylindre7,GL_COMPILE); DrawCylindre(0.3,0.3,1.2); glEndList();
	
	_piece_piece_cylindre8 = glGenLists(1);
	glNewList(_piece_piece_cylindre8,GL_COMPILE); DrawCylindre(0.4,0.4,0.2); glEndList();
	
	_piece_piece_cylindre9 = glGenLists(1);
	glNewList(_piece_piece_cylindre9,GL_COMPILE); DrawCylindre(0.5,0.5,0.3); glEndList();


}

//fnc des list----------

//constantes :
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  D degrees of rotation */
#define D 5

void Piece::demi_sphere()
{
	
	glEnable(GL_TEXTURE_2D);
	float diametre=2;
	float nb_slice=20;
	float nb_stack=20;
	
	float i_plus=360/nb_slice;
	float j_plus=180/nb_stack;
	
	for (float j=90; j>0 ; j-=j_plus) //tranches horizontales
	{
		for (float i=0 ; i<360 ; i+=i_plus) //tranches verticales
		{
			if (j==j_plus)
			{
				Point 	bg(round(sin(j*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
						bd(round(sin(j*M_PI/180)*sin((i-i_plus)*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos((i-i_plus)*M_PI/180)*diametre*100)/100) ,
						h(0, round(cos((j-j_plus)*M_PI/180)*diametre*100)/100, 0) ;
				Triangle t1(h,bg,bd) ;
				glPushMatrix();
					glBegin(GL_TRIANGLES);
							glTexCoord2f(0,0);		glVertex3f(h.get_coord_x(),h.get_coord_y(),h.get_coord_z());
							glTexCoord2f(0.5,1);	glVertex3f(bg.get_coord_x(),bg.get_coord_y(),bg.get_coord_z());
							glTexCoord2f(0,1);		glVertex3f(bd.get_coord_x(),bd.get_coord_y(),bd.get_coord_z());
					glEnd();
				glPopMatrix();
			}
			else
			{
				Point 	bg(round(sin(j*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
						bd(round(sin(j*M_PI/180)*sin((i+i_plus)*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos((i+i_plus)*M_PI/180)*diametre*100)/100) ,
						
						hg(round(sin((j-j_plus)*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
						hd(round(sin((j-j_plus)*M_PI/180)*sin((i+i_plus)*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos((i+i_plus)*M_PI/180)*diametre*100)/100) ;
				
				Triangle t1(hg,bd,bg)  , t2(bd,hg,hd)  ;
				glPushMatrix();
					glBegin(GL_TRIANGLES);
							glTexCoord2f(0,0);glVertex3f(hg.get_coord_x(),hg.get_coord_y(),hg.get_coord_z());
							glTexCoord2f(0.5,1);glVertex3f(bd.get_coord_x(),bd.get_coord_y(),bd.get_coord_z());
							glTexCoord2f(0,1);glVertex3f(bg.get_coord_x(),bg.get_coord_y(),bg.get_coord_z());
					glEnd();
				glPopMatrix();
				glPushMatrix();
					glBegin(GL_TRIANGLES);
							glTexCoord2f(0,0);glVertex3f(bd.get_coord_x(),bd.get_coord_y(),bd.get_coord_z());
							glTexCoord2f(0.5,1);glVertex3f(hg.get_coord_x(),hg.get_coord_y(),hg.get_coord_z());
							glTexCoord2f(0,1);	glVertex3f(hd.get_coord_x(),hd.get_coord_y(),hd.get_coord_z());
					glEnd();
				glPopMatrix();
			}
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void Piece::vertex(double th2, double ph2, double p)
{
	double x = p * Sin(th2)*Cos(ph2);
	double y = p * Cos(th2)*Cos(ph2);
	double z = p * Sin(ph2);
	glVertex3d(x, y, z);
}

GLvoid Piece::DrawSphere(double p) {
	
	for (int i = -90; i < 90; i += D) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 2 * D) {
			vertex(j, i, p);
			vertex(j, i + D, p);
		}
		glEnd();
	}
}

void Piece::DrawCylindre(float n, float n1, float n2) {
	glPushMatrix();
	{
		int compt = 0;
		
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 360; j += 5) {
			if(compt%2==1){
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n1*Cos(j), n2, n1*Sin(j));
				glTexCoord2f(0.5,1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
				
			}
			else{
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n1*Cos(j), n2, n1*Sin(j));
				glTexCoord2f(1.0,0.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			compt++;
		}
		glEnd();
		
	
		compt=0;
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 360; j += 5) {
			if(compt%2==1){
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
				glTexCoord2f(0.5,1.0);
				glVertex3f(n1*Cos(j+5), n2, n1*Sin(j+5));
			}
			else{
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
				glTexCoord2f(1.0,0.0);
				glVertex3f(n1*Cos(j+5), n2, n1*Sin(j+5));
				
			}
			compt++;
		}
		glEnd();
	
		compt=0;
		glBegin(GL_TRIANGLES);
		for (int j = 0; j <= 360; j += 5) {
			if(compt%2==1){
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n1*Cos(j+5), n2, n1*Sin(j+5));
				glTexCoord2f(0.5,1.0);
				glVertex3f(n*Cos(j+5), 0, n*Sin(j+5));
			}
			else{
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n1*Cos(j+5), n2, n1*Sin(j+5));
				glTexCoord2f(1.0,0.0);
				glVertex3f(n*Cos(j+5), 0, n*Sin(j+5));
			}
			compt++;
		}
		glEnd();


		//================="Couvercle"==================
		//================"Couvercle" en bas ==================
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0, 0, 0);
		compt=1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n * Cos(k), 0, n * Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(n * Cos(k), 0, n * Sin(k));
				
			}
			compt++;
		}
		glEnd();
		glTranslatef(0, n2, 0);
		//================en haut==============================
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0, 0, 0);
		compt = 1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n1 * Cos(k), 0, n1 * Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(n1 * Cos(k), 0, n1 * Sin(k));
				compt++;
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void Piece::DrawBase_Argent() {
	glColor3f(1,1,1);
	//=================Cylindre===================
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[0]);
		glEnable(GL_TEXTURE_2D);
		int n = 2;
		int tmp = 1;
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 5) {
			if (tmp % 2 == 0) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n*Cos(j), +0.4, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(n*Cos(j), +0.4, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			tmp++;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	
		//================="Couvercle"==================
		glTranslatef(0, 0.4, 0);
		glBindTexture (GL_TEXTURE_2D, textures[0]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_FAN);
		
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0, 0, 0);
		int compt = 1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(2 * Cos(k), 0, 2 * Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(2 * Cos(k), 0, 2 * Sin(k));
				compt++;
			}
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, -0.4, 0);
	}
	glPopMatrix();
	glRotatef(180,1,0,0);
	
	
	demi_sphere();

	glRotatef(-180,1,0,0);
	
}

void Piece::DrawBase_Or(){
	glColor3f(1,1,1);
	//=================Cylindre===================
	glPushMatrix();
	{
		glBindTexture (GL_TEXTURE_2D, textures[1]);
		glEnable(GL_TEXTURE_2D);
		int n = 2;
		int tmp = 1;
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= 360; j += 5) {
			if (tmp % 2 == 0) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(n*Cos(j), +0.4, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(n*Cos(j), +0.4, n*Sin(j));
				glTexCoord2f(0.5, 1.0);
				glVertex3f(n*Cos(j), 0, n*Sin(j));
			}
			tmp++;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	
		//================="Couvercle"==================
		glTranslatef(0, 0.4, 0);
		glBindTexture (GL_TEXTURE_2D, textures[1]);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_FAN);
		
		glTexCoord2f(0.5, 1.0);
		glVertex3f(0, 0, 0);
		int compt = 1;
		for (int k = 0; k <= 360; k += 5) {
			if (compt % 2 == 1) {
				glTexCoord2f(0.0, 0.0);
				glVertex3f(2 * Cos(k), 0, 2 * Sin(k));
			}
			else {
				glTexCoord2f(1.0, 0.0);
				glVertex3f(2 * Cos(k), 0, 2 * Sin(k));
				compt++;
			}
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, -0.4, 0);
	}
	glPopMatrix();
	glRotatef(180,1,0,0);

	demi_sphere();
	glRotatef(-180,1,0,0);
}

void Piece::DrawPhalange() {
	
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		//======Face devant======
		glVertex3f(0, 0.07, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0.06, 0, 0);
		glVertex3f(0.06, 0.07, 0);
		//======Face droite======
		glVertex3f(0.06, 0.07, 0);
		glVertex3f(0.06, 0, 0);
		glVertex3f(0.06, 0, -0.05);
		glVertex3f(0.06, 0.07, -0.05);
		//======Face derriere=====
		glVertex3f(0.06, 0.07, -0.05);
		glVertex3f(0.06, 0, -0.05);
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
		glVertex3f(0.06, 0.07, 0);
		glVertex3f(0.06, 0.07, -0.05);
		//=======Face bas========
		glVertex3f(0.06, 0, -0.05);
		glVertex3f(0.06, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, -0.05);
		glEnd();
	}
	glPopMatrix();
}

void Piece::DrawDoigt(GLfloat a) {
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

void Piece::DrawMain(GLfloat a) {
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
		DrawPhalange();
		glTranslatef(0.08, 0.09, 0);
		
		glTranslatef(-0.08, -0.04, 0);
		glRotatef(a, 1, 0, 0);
		DrawPhalange();
		glTranslatef(0.08, 0.04, 0);
		
	}
	glPopMatrix();
	
	glColor3ub(255,255,255);
}

void Piece::DrawPied() {
	glPushMatrix();
	{
		//=============Niveau plus bas==================
		glColor3f(0.2,0.2,0.2);
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

