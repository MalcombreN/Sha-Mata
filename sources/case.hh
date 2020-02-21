#pragma once

//Required class
#include "triangle.hh"

//Required libraries
#include <algorithm>
#include <array>
#include <memory>
#include <math.h>

class Case
{
private:
	std::shared_ptr<Triangle> _tr1; 
	std::shared_ptr<Triangle> _tr2;
	bool _couleur;
	Vecteur _norm;
	std::array<std::shared_ptr<Case>,4> _cases_adjacentes;
	std::array<Point,4> _centre_bords_cases;
	std::array<Point,4> _coin_bords_cases;
	Point _pos_pion;
	bool _is_hover;
	bool _is_locked;
	bool _is_target;
		
	GLuint _tour_case;
	GLuint _triangles_cases;	
		
public:
	//Constructeurs / Destructeurs
	Case(std::shared_ptr<Triangle> t1, std::shared_ptr<Triangle> t2, bool couleur );
	Case(Case const & C);
	~Case()=default;

	//Accesseur
	std::shared_ptr<Triangle> get_tr1();
	std::shared_ptr<Triangle> get_tr2();
	bool get_couleur()const;
	Vecteur get_norm()const;
	std::array<std::shared_ptr<Case>,4> get_cases_adjacentes();
	std::array<Point,4> get_centre_bords_cases();
	std::array<Point,4> get_coin_bords_cases();
	Point get_pos_pion()const;
	
	//Mutateurs
	void set_cases_adjacentes(int pos, std::shared_ptr<Case> const & ptr  );
	void set_centre_bords_cases(int pos, Point const & P );
	void set_coin_bords_cases(int pos, Point const & P );
	void change_hover();
	void change_lock();
	void change_target();
	
	//Affichage
	void load_preaffichage();
	void destroyList();
	void display()const;
};
