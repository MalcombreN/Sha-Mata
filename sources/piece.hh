#pragma once

#include <vector>

#include "case.hh"
#include "operation_base.hh"
#include "ppm.hh"
#include <math.h>

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
#define D 5

extern GLuint textures[30];

enum class type_piece
{
	pion,
	roi,
	reine,
	fou,
	tour,
	cavalier	
};

class Piece
{
protected :
	type_piece _type;
	std::shared_ptr<Case> _case_support;
	bool _joueur;
	int _etat_piece;
	std::vector<std::shared_ptr<Case>> _chemin;
	std::vector<Point> _points_intermediaires;
	unsigned int _nb_deplacement;
	float _avancement_dir;
	float _avancement_dir2;
	float _avancement_rot;
	bool _a_bouger;
	bool _a_attaquer;
	bool _peut_bouger;
	bool _anim_fini;
	
	void orientation(Point const & centre , Point const & haut , Vecteur const & norm );
	virtual void animation()=0;
	virtual void affiche_piece()=0;
	void affichage_standard();
	virtual void affichage_mouvement();
	virtual void affichage_attaque();
	void affichage_mort();
	void affichage_ressussite();
	
	static GLuint _piece_piece_sphere1;
	static GLuint _piece_piece_sphere2;
	static GLuint _piece_piece_sphere3;
	static GLuint _piece_piece_sphere4;
	static GLuint _piece_piece_sphere5;
	static GLuint _piece_piece_baseArgent;
	static GLuint _piece_piece_baseOr;
	static GLuint _piece_piece_phallanges;
	static GLuint _piece_piece_doigt;
	static GLuint _piece_piece_mains1;
	static GLuint _piece_piece_mains2;
	static GLuint _piece_piece_cylindre1;
	static GLuint _piece_piece_cylindre2;
	static GLuint _piece_piece_cylindre3;
	static GLuint _piece_piece_cylindre4;
	static GLuint _piece_piece_cylindre5;
	static GLuint _piece_piece_cylindre6;
	static GLuint _piece_piece_cylindre7;
	static GLuint _piece_piece_cylindre8;
	static GLuint _piece_piece_cylindre9;
	static GLuint _piece_piece_pied;
	
	//fnc pour affichage partie pieces
	static void demi_sphere();
	static void vertex(double th2, double ph2, double p);
	static GLvoid DrawSphere(double p);
	static void DrawCylindre(float n, float n1, float n2);
	static void DrawBase_Argent();
	static void DrawBase_Or();
	static void DrawPhalange();
	static void DrawDoigt(GLfloat a);
	static void DrawMain(GLfloat a);
	static void DrawPied();
	
public:	
	Piece( type_piece const & type , std::shared_ptr<Case> const & case_support ,bool joueur );
	~Piece()=default;
	
	static void load_piece();
	
	
	std::shared_ptr<Case> get_case_support()const;
	bool get_joueur()const;
	type_piece get_type()const;
	
	void set_a_bouger();
	bool get_a_bouger()const;
	bool ready ()const;
	
	void deplacement(std::vector<std::shared_ptr<Case>> const & chemin, std::vector<Point> const & intermediaires);
	void attaque(std::vector<std::shared_ptr<Case>> const & chemin, std::vector<Point> const & intermediaires);
	void termine_deplacement();
	
	void tuer();
	void ressussiter(); 
	bool disparue() const;
	void disparait();
	bool get_a_attaquer()const;
	
	void set_a_attaquer();
	void set_anim_fini();
	void set_case_support(std::shared_ptr<Case> const & ptr);
	
	void display();
	
	
	
};
