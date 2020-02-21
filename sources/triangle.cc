#include "triangle.hh"

//Constructeurs
//Note : Il est impératif de donner les points en respectant le sens anti-horaire pour le calcul de la normale
Triangle::Triangle(Point const & point_g,Point const & point_d,Point const & point_h):
	_point_g(point_g),
	_point_d(point_d),
	_point_h(point_h),
	_norm(Normale(point_g,point_d,point_h)),
	_num_case(-2) // -2=isoler -1=relier au reste x=dans la case x
{}

//Accesseurs
Point Triangle::get_point_g()const{return _point_g;}
Point Triangle::get_point_d()const{return _point_d;}
Point Triangle::get_point_h()const{return _point_h;}

Normale Triangle::get_norm()const{return _norm;}

int Triangle::get_num_case()const{return _num_case;}

//Mutateurs
void Triangle::set_num_case(int num_case){_num_case=num_case;}

//Affichage
void Triangle::display()const
{
	glPushMatrix();
		glNormal3f(_norm.get_dir_x(),_norm.get_dir_y(),_norm.get_dir_z());
		glBegin(GL_TRIANGLES);
				glVertex3f(get_point_g().get_coord_x(),get_point_g().get_coord_y(),get_point_g().get_coord_z());
				glVertex3f(get_point_d().get_coord_x(),get_point_d().get_coord_y(),get_point_d().get_coord_z());
				glVertex3f(get_point_h().get_coord_x(),get_point_h().get_coord_y(),get_point_h().get_coord_z());
		glEnd();
	glPopMatrix();
}
