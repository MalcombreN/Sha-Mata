#include "case.hh"

// Constructeurs 
Case::Case(std::shared_ptr<Triangle> t1, std::shared_ptr<Triangle> t2, bool couleur ):
	_tr1(t1),
	_tr2(t2),
	_couleur(couleur),
	_cases_adjacentes({nullptr,nullptr,nullptr,nullptr}),
	_is_hover(false),
	_is_locked(false),
	_is_target(false)
{
	//calcul du vecteur "normal" à la case
	//rendre les deux vecteurs normaux unitaire
	float max1=sqrt( pow(_tr1->get_norm().get_dir_x(),2) + pow(_tr1->get_norm().get_dir_y(),2) + pow(_tr1->get_norm().get_dir_z(),2) );
	float max2=sqrt( pow(_tr2->get_norm().get_dir_x(),2) + pow(_tr2->get_norm().get_dir_y(),2) + pow(_tr2->get_norm().get_dir_z(),2) );
	
	float dir_x=(_tr1->get_norm().get_dir_x()/max1)+(_tr2->get_norm().get_dir_x()/max2);
	float dir_y=(_tr1->get_norm().get_dir_y()/max1)+(_tr2->get_norm().get_dir_y()/max2);
	float dir_z=(_tr1->get_norm().get_dir_z()/max1)+(_tr2->get_norm().get_dir_z()/max2);

	float max3=sqrt( pow(dir_x,2) + pow(dir_y,2) + pow(dir_z,2) );
	_norm=Vecteur(dir_x/max3,dir_y/max3,dir_z/max3);
	
	
	//calcul de la position (le millieu des deux points en commun)
	Point comm1;
	Point comm2;
	if (t1->get_point_d()==t2->get_point_d() || t1->get_point_d()==t2->get_point_g() || t1->get_point_d()==t2->get_point_h())
	{	
		comm1=t1->get_point_d();
		
		if(t1->get_point_g()==t2->get_point_d() || t1->get_point_g()==t2->get_point_g() || t1->get_point_g()==t2->get_point_h())
		{ comm2=t1->get_point_g(); }
		else
		{ comm2=t1->get_point_h(); }
	}
	else
	{
		comm1=t1->get_point_g();
		comm2=t1->get_point_h();
	}
	_pos_pion=Point((comm1.get_coord_x()+comm2.get_coord_x())/2,(comm1.get_coord_y()+comm2.get_coord_y())/2,(comm1.get_coord_z()+comm2.get_coord_z())/2);
	
}

Case::Case(Case const & C):
	_tr1(C._tr1),
	_tr2(C._tr2),
	_couleur(C._couleur),
	_norm(C._norm),
	_cases_adjacentes(C._cases_adjacentes),
	_pos_pion(C._pos_pion),
	_is_hover(C._is_hover),
	_is_locked(C._is_locked),
	_is_target(C._is_target)
{}


//Accesseurs
std::shared_ptr<Triangle> Case::get_tr1(){return _tr1;}
std::shared_ptr<Triangle> Case::get_tr2(){return _tr2;}
bool Case::get_couleur()const{return _couleur;}
Vecteur Case::get_norm()const {return _norm;}
std::array<std::shared_ptr<Case>,4> Case::get_cases_adjacentes(){return _cases_adjacentes;}
std::array<Point,4> Case::get_centre_bords_cases() {return _centre_bords_cases;}
std::array<Point,4> Case::get_coin_bords_cases() {return _coin_bords_cases;}
Point Case::get_pos_pion()const{return _pos_pion;}

//Mutateurs
void Case::set_cases_adjacentes(int pos, std::shared_ptr<Case> const & ptr ){ _cases_adjacentes[pos]=ptr;}
void Case::set_centre_bords_cases(int pos, Point const & P ){_centre_bords_cases[pos]=P;}
void Case::set_coin_bords_cases(int pos, Point const & P ){_coin_bords_cases[pos]=P;}
void Case::change_hover(){ _is_hover= !_is_hover ;}
void Case::change_lock(){ _is_locked= !_is_locked ;}
void Case::change_target(){ _is_target= !_is_target ;}

//Affichage
void Case::destroyList()
{
	glDeleteLists(_tour_case, 1);
	glDeleteLists(_triangles_cases, 1);
}

void Case::load_preaffichage()
{
	_tour_case = glGenLists(1);
	
	glNewList(_tour_case, GL_COMPILE);
	{
		glPushMatrix();
			glColor3f(0.,0.,0.);
			glLineWidth(2.5);
			glBegin(GL_LINES);
				glVertex3f(_coin_bords_cases[0].get_coord_x(),_coin_bords_cases[0].get_coord_y(),_coin_bords_cases[0].get_coord_z());
				glVertex3f(_coin_bords_cases[3].get_coord_x(),_coin_bords_cases[3].get_coord_y(),_coin_bords_cases[3].get_coord_z());
				glVertex3f(_coin_bords_cases[3].get_coord_x(),_coin_bords_cases[3].get_coord_y(),_coin_bords_cases[3].get_coord_z());
				glVertex3f(_coin_bords_cases[1].get_coord_x(),_coin_bords_cases[1].get_coord_y(),_coin_bords_cases[1].get_coord_z());
				glVertex3f(_coin_bords_cases[1].get_coord_x(),_coin_bords_cases[1].get_coord_y(),_coin_bords_cases[1].get_coord_z());
				glVertex3f(_coin_bords_cases[2].get_coord_x(),_coin_bords_cases[2].get_coord_y(),_coin_bords_cases[2].get_coord_z());
				glVertex3f(_coin_bords_cases[2].get_coord_x(),_coin_bords_cases[2].get_coord_y(),_coin_bords_cases[2].get_coord_z());
				glVertex3f(_coin_bords_cases[0].get_coord_x(),_coin_bords_cases[0].get_coord_y(),_coin_bords_cases[0].get_coord_z());
			glEnd();
		glPopMatrix();
	}
	glEndList();
	
	_triangles_cases = glGenLists(1);
	
	glNewList(_triangles_cases, GL_COMPILE);
	{
		glPushMatrix();
			this->_tr1->display();
			this->_tr2->display();
		glPopMatrix();      
	}
	glEndList();
}

void Case::display()const
{
	glPushMatrix();
		glCallList(_tour_case);
		if (_is_target && _is_hover)
			glColor3f(1.,0.5,0.);
		else
		{
			if (_is_target)
				glColor3f(1.,0.,0.);
			else
			{
				if (_is_locked)
					glColor3f(0.,1.,0.);
				else
				{
					if (_is_hover )
						glColor3f(1.,1.,0.);
					else
					{
						if (this->_couleur)
							glColor3f(0.,0.,0.);
						else
							glColor3f(1.,1.,1.);
					}
				}
			}
		}
		glCallList(_triangles_cases);                                                                 
	glPopMatrix();
}
