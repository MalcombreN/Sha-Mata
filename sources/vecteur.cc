#include "vecteur.hh"

//Constructeurs
Vecteur::Vecteur ():
	_dir_x(0),
	_dir_y(0),
	_dir_z(0)
{}

Vecteur::Vecteur (float const dir_x, float const dir_y, const float dir_z):
	_dir_x(dir_x),
	_dir_y(dir_y),
	_dir_z(dir_z)
{}


//Accesseurs
float Vecteur::get_dir_x()const{return _dir_x;}
float Vecteur::get_dir_y()const{return _dir_y;}
float Vecteur::get_dir_z()const{return _dir_z;}

 //Mutateurs
void Vecteur::set_dir_x(float const x)
{_dir_x=x;}
void Vecteur::set_dir_y(float const y)
{_dir_y=y;}
void Vecteur::set_dir_z(float const z)
{_dir_z=z;}

