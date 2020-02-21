#pragma once

//Required class
#include "vecteur.hh"
#include "point.hh"

class Normale : public Vecteur
{
private:
	/* herited from Vecteur
		float _dir_x;
		float _dir_y;
		float _dir_z;
	*/

public:
	//Constructeurs / Destructeurs
	Normale(Point const & p1, Point const & p2, Point const & p3);
	~Normale()=default;
	
	/* herited from Vecteur
		//Accesseurs
		float get_dir_x()const;
		float get_dir_y()const;
		float get_dir_z()const;
		
		//Mutateurs
		void set_dir_x(float const x);
		void set_dir_y(float const y);
		void set_dir_z(float const z);
	*/
};
