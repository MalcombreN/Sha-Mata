#include "point.hh"

//Constructeurs
Point::Point ():
	_coord_x(0),
	_coord_y(0),
	_coord_z(0)
{}

Point::Point (float const coord_x,float const coord_y,float const coord_z):
	_coord_x(coord_x),
	_coord_y(coord_y),
	_coord_z(coord_z)
{}



//Accesseurs
float Point::get_coord_x()const{return _coord_x;}
float Point::get_coord_y()const{return _coord_y;}
float Point::get_coord_z()const{return _coord_z;}


//Operateurs
bool Point::operator == (Point const & p1)const
{
	return ( get_coord_x()==p1.get_coord_x() && get_coord_y()==p1.get_coord_y() && get_coord_z()==p1.get_coord_z() );
}

bool Point::operator > (Point const & p1)const
{
	if ( get_coord_x()>p1.get_coord_x() )
	{ return true; }
	else
	{
		if ( get_coord_x()==p1.get_coord_x() )
		{
			if ( get_coord_y()>p1.get_coord_y() )
			{ return true; }
			else
			{
				if ( get_coord_y()==p1.get_coord_y() )
				{
					if ( get_coord_z()>p1.get_coord_z() )
					{ return true; }
					else
					{ return false; }
				}
				else
				{ return false; }
			}
		}
		else
		{ return false; }
	}
}
