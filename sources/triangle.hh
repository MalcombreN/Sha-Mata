#pragma once

#include "normale.hh"

//Required libraries
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


class Triangle
{
private :
	Point _point_g;
	Point _point_d;
	Point _point_h;
	
	Normale _norm; //Vecteur normal au triangle
		
	int _num_case; //Numéro de la case dont fais partie le triangle

public:
	//Constructeurs / Destructeurs
	Triangle(Point const & point_g,Point const & point_d,Point const & point_h); 
	~Triangle()=default;

	//Accesseurs
	Point get_point_g()const;
	Point get_point_d()const;
	Point get_point_h()const;
	Normale get_norm()const;
	int get_num_case()const;
	
	//Mutateurs
	void set_num_case(int num_case);
	
	//Affichage
	void display()const;
};
