#pragma once

#include "triangle.hh"
#include "case.hh"
#include "./Solver.h"

#include <iostream>
#include "operation_base.hh"
#include <vector>


class Terrain
{
private:
	//Attribut
	unsigned int _num_plateau;
	std::vector<std::shared_ptr<Triangle>> _ens_tr;
	std::vector<std::shared_ptr<Case>> _ens_cases;
	std::shared_ptr<Case> _case_selected;
	
	//Methodes
		//Les terrains
			void construire_echec();
			void construire_sphere();
			void construire_test();
			void construire_montagne();
	
		//Dit si t2 est adjacent a t1
		bool est_adjacent(std::shared_ptr<Triangle> const & t1 , std::shared_ptr<Triangle> const & t2);
		//Donne la liste des numeros des triangles adjacents à un triangle
		std::vector<unsigned int> triangles_adjacents (std::shared_ptr<Triangle> const & t1);
		
		//Verifi que tous les triangles forme un seul et unique terrain
		bool verif_association();
		void association(std::shared_ptr<Triangle> const & t1 );
		
		//Associe les triangles en case 2 methodes
			//Methode 1 -> algorithme SAT
			bool creer_cases_sat();
			//Methode 2 -> algorithme recursif classique mais qui maximise juste la contraite de couleur
			bool creer_cases();
			bool faire_case(std::shared_ptr<Triangle> const & t1 ,bool color  , int & cpt);
			
			
		//Realise le graphe de de parcours du terrain
		void do_graph();
		void relie_adj(int num_case,int config, Point const & p1 , Point const & p2);
		
		void load_preaffichage_case();
public:
	//Constructeurs / Destructeurs
	Terrain();
	~Terrain()=default;
	
	//Accesseurs
	unsigned int get_num_plateau() const;
	std::shared_ptr<Case> get_case_selected()const;
	std::vector<std::shared_ptr<Case>> get_ens_cases()const;
	
	
	bool selection_plateau(unsigned int num_plateau);
	void clear();
	void select_autre_case(unsigned int x);
	
	//Affichage
	void display(int sens)const;
};
