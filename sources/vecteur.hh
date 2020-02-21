#pragma once

class Vecteur
{
private:
	float _dir_x;
	float _dir_y;
	float _dir_z;
  
public:
	//Constructeurs / Destructeurs
	Vecteur();
	Vecteur(float const dir_x, float const dir_y, float const dir_z);
	~Vecteur ()=default;
  
	//Accesseurs
  	float get_dir_x()const;
	float get_dir_y()const;
	float get_dir_z()const;
	
	//Mutateurs
	void set_dir_x(float const x);
	void set_dir_y(float const y);
	void set_dir_z(float const z);
	
};
