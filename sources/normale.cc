#include "normale.hh"

//Constructeurs
Normale::Normale (Point const & p1, Point const & p3, Point const & p2)
{
	float v0x = p3.get_coord_x() - p2.get_coord_x();
	float v0y = p3.get_coord_y() - p2.get_coord_y();
	float v0z = p3.get_coord_z() - p2.get_coord_z();
	float v1x = p1.get_coord_x() - p2.get_coord_x();
	float v1y = p1.get_coord_y() - p2.get_coord_y();
	float v1z = p1.get_coord_z() - p2.get_coord_z();
	
	set_dir_x((v0y * v1z) - (v0z *v1y));
	set_dir_y((v0z * v1x) - (v0x *v1z));
	set_dir_z((v0x * v1y) - (v0y *v1x));
}


