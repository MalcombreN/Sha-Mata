#pragma once

class Point
{
private :
	float _coord_x;
	float _coord_y;
	float _coord_z;

public:
	//Constructeurs / Destructeur
	Point();
	Point(float const coord_x,float const coord_y,float const coord_z);
	~Point()=default;

	//Accesseurs
	float get_coord_x()const;
	float get_coord_y()const;
	float get_coord_z()const;
	
	//Operateurs
	bool operator == (Point const & p1)const;
	bool operator > (Point const & p1)const;
};
