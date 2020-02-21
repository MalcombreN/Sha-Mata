#include "terrain.hh"

Terrain::Terrain():
	_num_plateau(0),
	_case_selected(nullptr)
{}

unsigned int Terrain::get_num_plateau() const {return _num_plateau;}
std::shared_ptr<Case> Terrain::get_case_selected()const{return _case_selected;}
std::vector<std::shared_ptr<Case>> Terrain::get_ens_cases()const {return _ens_cases;}

//Terrains -------------------------------------------------------------
void Terrain::construire_echec()
{
	for(float i = -20; i< 20; i+=5){
		for(float j = -20; j <20; j+=5){
				Point bg(i,0.0,j) ,bd(i+5,0,j), hd(i+5,0,j+5), hg(i,0,j+5);
				Triangle t1(bg,bd,hd), t2(hd,hg,bg);
				_ens_tr.push_back(std::make_shared<Triangle>(t1));
				_ens_tr.push_back(std::make_shared<Triangle>(t2));
		}
	}
}


void Terrain::construire_sphere()
{
	float diametre=15;
	float nb_slice=10;
	float nb_stack=10;
	
	float i_plus=360/nb_slice;
	float j_plus=180/nb_stack;
	
	for (float j=180; j>0 ; j-=j_plus) //tranches horizontales
	{
		for (float i=0 ; i<360 ; i+=i_plus) //tranches verticales
		{
			if (j==180)
			{
				Point 	b(0, round(cos(j*M_PI/180)*diametre*100)/100, 0) ,
						hg(round(sin((j-j_plus)*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
						hd(round(sin((j-j_plus)*M_PI/180)*sin((i-i_plus)*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos((i-i_plus)*M_PI/180)*diametre*100)/100) ;
				
				Triangle t1(b,hd,hg) ;
				_ens_tr.push_back(std::make_shared<Triangle>(t1));
			}
			else
			{
				if (j==j_plus)
				{
					Point 	bg(round(sin(j*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
							bd(round(sin(j*M_PI/180)*sin((i-i_plus)*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos((i-i_plus)*M_PI/180)*diametre*100)/100) ,
							h(0, round(cos((j-j_plus)*M_PI/180)*diametre*100)/100, 0) ;
					Triangle t1(h,bg,bd) ;
					_ens_tr.push_back(std::make_shared<Triangle>(t1));		
				}
				else
				{
					Point 	bg(round(sin(j*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
							bd(round(sin(j*M_PI/180)*sin((i+i_plus)*M_PI/180)*diametre*100)/100,round(cos(j*M_PI/180)*diametre*100)/100,round(sin(j*M_PI/180)*cos((i+i_plus)*M_PI/180)*diametre*100)/100) ,
							
							hg(round(sin((j-j_plus)*M_PI/180)*sin(i*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos(i*M_PI/180)*diametre*100)/100) ,
							hd(round(sin((j-j_plus)*M_PI/180)*sin((i+i_plus)*M_PI/180)*diametre*100)/100,round(cos((j-j_plus)*M_PI/180)*diametre*100)/100,round(sin((j-j_plus)*M_PI/180)*cos((i+i_plus)*M_PI/180)*diametre*100)/100) ;
					
					Triangle t1(hg,bd,bg)  , t2(bd,hg,hd)  ;
					_ens_tr.push_back(std::make_shared<Triangle>(t1));
					_ens_tr.push_back(std::make_shared<Triangle>(t2));		
				}
			}
		}
	}
}

void Terrain::construire_test()
{
	Point p1(0,0,0) , p2(4,0,0) , p3(8,4,-4) , p4(8,4,0), p5(12,0,4), p6(7,0,8) , p6b(8,0,7), p7(4,0,4), p8(0,0,4), p9(-4,0,8), p10(0,0,8), p11(4,0,12);
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p1,p2,p8)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p2,p7,p8)));
	
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p2,p3,p7)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p3,p4,p7)));
	
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p9,p8,p7)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p7,p10,p9)));
	
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p7,p4,p5)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p7,p5,p6b)));
	
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p10,p7,p11)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p11,p7,p6)));
	
	for(float i = 4; i> -16; i-=4){
		for(float j = 4; j>-16; j-=4){
			if (!(j==4 && i==4))
			{
				Point bg(i,0,j) ,bd(i-4,0,j), hd(i-4,0,j-4), hg(i,0,j-4);
				Triangle t1(bg,bd,hd), t2(hd,hg,bg);
				_ens_tr.push_back(std::make_shared<Triangle>(t1));
				_ens_tr.push_back(std::make_shared<Triangle>(t2));
			}
		}
	}
	
	for(float i = 8; i<24; i+=4){
		for(float j = 0; j>-16; j-=4){
				Point bg(i,4,j) ,bd(i+4,4,j), hd(i+4,4,j-4), hg(i,4,j-4);
				Triangle t1(bd,bg,hd), t2(hd,hg,bg);
				_ens_tr.push_back(std::make_shared<Triangle>(t1));
				_ens_tr.push_back(std::make_shared<Triangle>(t2));
		}
	}
	
	Point p12(4,0,-8) , p13(4,0,-12),p14(8,4,-12) , p15(8,4,-16);
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p12,p15,p14)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p12,p13,p15)));
	Point p16(4,0,-4) , p17(4,0,-8),p18(8,4,-8) , p19(8,4,-12);
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p16,p19,p18)));
	_ens_tr.push_back(std::make_shared<Triangle>(Triangle(p16,p17,p19)));
}

void Terrain::construire_montagne()
{
	srand(time(0)); 
	double max = 0;
	double min = 0;
	//hauteur
	std::vector<std::vector<double>> hauteurs;
	for(float i = -32; i<=32; i+=4)
	{
		std::vector<double> tmp;
		for(float j = -32; j <=32; j+=4)
		{
			tmp.push_back(0);
		}
		hauteurs.push_back(tmp);
	}
	
	
	//========================================
	
	double dz, dx;
	double distance;
	double test;
	int x, z;
	double radius;
	double cosVal;

	//Determine number of hills in terrain
	int area = 16 * 16;
	int tempA = area;
	int num = 0;
	
	while (tempA > 100) 
	{
		num += 1;
		tempA -= 100;
	}

	int numCircles = rand() % area + num * (8);
	//int numCircles = rand()%100+50;
	//Adjust height values
	for (int a = 0; a < numCircles; a++)
	{
		//Circle parameters
		x = rand() % 16;
		z = rand() % 16;
		radius = rand() % 20 + 1;  


		//Each terrain point
		for (int i = 0; i <= 16; i++)
		{
			for (int j = 0; j <=16; j++)
			{
				
				//Calculate y of points
				dz = z - i;
				dx = x - j;

				//Calculate distance between point and circle centre
				distance = sqrt((dz*dz) + (dx*dx));
				
				test = distance * 2  / radius;

				if (fabs(test) <= 1.0)
				{
					cosVal = test * 3.14 / 180;
					hauteurs[i][j] += (0.3 / 2.0)  + (cos(cosVal) * 0.3 / 2.0);
					//if (hauteurs[i][j] > maxHeight) maxHeight = hauteurs[i][j];
				}
				
				
			}
		}
	}
	for (int i = 0; i <= 16; i++)
		{
			for (int j = 0; j <= 16; j++)
			{
				if(hauteurs[i][j]>max){max = hauteurs[i][j];}
				if(hauteurs[i][j]<min) {min = hauteurs[i][j];}
			}
		}
		double moyen = (max+min) /2;
	//=============================================
	
	for(float i = -32; i< 32; i+=4){
		for(float j = -32; j <32; j+=4)
		{
				
				Point bg(i,hauteurs[i/4+8][j/4+8] - moyen,j) ,bd(i+4,hauteurs[(i+4)/4+8][j/4+8]- moyen,j), hd(i+4,hauteurs[(i+4)/4+8][(j+4)/4+8]- moyen,j+4), hg(i,hauteurs[i/4+8][(j+4)/4+8]- moyen,j+4);
				Triangle t1(bg,bd,hd), t2(hd,hg,bg);
				_ens_tr.push_back(std::make_shared<Triangle>(t1));
				_ens_tr.push_back(std::make_shared<Triangle>(t2));
		}
	}
}
//----------------------------------------------------------------------

bool Terrain::selection_plateau(unsigned int num_plateau)
{
	_num_plateau=num_plateau;
	
	switch (_num_plateau)
	{
		case 1:
			construire_echec();
			break;
		case 2:
			construire_sphere();
			break;
		case 3:
			construire_test();
			break;
		case 4:
			construire_montagne();
			break;
	}
	
	if (!creer_cases_sat())
	{
		std::cout<<"Le terrain ne peut pas etre creer avec toutes les contraintes classiques ( essai avec le 2ème algorithme )"<<std::endl;
		if (!creer_cases())
		{
			std::cout<<"Le terrain ne peut as etre construit du tout"<<std::endl;
			return false;
		}
	}
	
	do_graph();
	//verification graph 
	/*
	for( std::vector<std::shared_ptr<Case>>::size_type itr(0); itr<_ens_cases.size(); ++itr)
	{
		std::cout<<"case "<<itr<<"[";
		for (int j=0;j<4;++j)
		{
			if (_ens_cases[itr]->get_cases_adjacentes()[j]==nullptr)
				std::cout<<"N,";
			else
				std::cout<<_ens_cases[itr]->get_cases_adjacentes()[j]->get_tr1()->get_num_case()<<",";
		}std::cout<<"]"<<std::endl;
	}*/
	load_preaffichage_case();
	
	_case_selected=_ens_cases[0];
	_case_selected->change_hover();
	return true;
}

void Terrain::clear()
{
	for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_cases.size(); ++i)
	{
		_ens_cases[i]->destroyList();
	}
	_ens_cases.clear();
	_ens_tr.clear();
	_num_plateau=0;
	_case_selected=nullptr;	
}

void Terrain::load_preaffichage_case()
{
	for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_cases.size(); ++i)
	{ 
		_ens_cases[i]->load_preaffichage();
	}
}

void Terrain::select_autre_case(unsigned int x)
{
	if (_case_selected->get_cases_adjacentes()[x]!=nullptr)
	{
		_case_selected->change_hover();
		_case_selected=_case_selected->get_cases_adjacentes()[x];
		_case_selected->change_hover();
	}
}


void Terrain::display(int sens)const
{
	for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_cases.size(); ++i)
	{ 
		_ens_cases[i]->display();
		
		glPushMatrix();
			glColor3f(0.,0.,1.);
			translation(_ens_cases[i]->get_pos_pion().get_coord_x()*0.1,_ens_cases[i]->get_pos_pion().get_coord_y()*0.1,_ens_cases[i]->get_pos_pion().get_coord_z()*0.1);
			translation(_ens_cases[i]->get_centre_bords_cases()[sens].get_coord_x()*0.9,_ens_cases[i]->get_centre_bords_cases()[sens].get_coord_y()*0.9,_ens_cases[i]->get_centre_bords_cases()[sens].get_coord_z()*0.9);
			glutSolidSphere(0.1,20,20);
		glPopMatrix();
	}
}

bool Terrain::est_adjacent(std::shared_ptr<Triangle> const & t1 , std::shared_ptr<Triangle> const & t2)
{
	return ( (t1!=t2) && (
		   ( (t1->get_point_g()==t2->get_point_g() || t1->get_point_g()==t2->get_point_d() || t1->get_point_g()==t2->get_point_h()) &&
			 (t1->get_point_d()==t2->get_point_g() || t1->get_point_d()==t2->get_point_d() || t1->get_point_d()==t2->get_point_h()) ) 
		   ||				 
		   ( (t1->get_point_g()==t2->get_point_g() || t1->get_point_g()==t2->get_point_d() || t1->get_point_g()==t2->get_point_h()) &&
			 (t1->get_point_h()==t2->get_point_g() || t1->get_point_h()==t2->get_point_d() || t1->get_point_h()==t2->get_point_h()) ) 
		   || 				 
		   ( (t1->get_point_d()==t2->get_point_g() || t1->get_point_d()==t2->get_point_d() || t1->get_point_d()==t2->get_point_h()) &&
			 (t1->get_point_h()==t2->get_point_g() || t1->get_point_h()==t2->get_point_d() || t1->get_point_h()==t2->get_point_h()) ) ) );
}

std::vector<unsigned int> Terrain::triangles_adjacents (std::shared_ptr<Triangle> const & t1)
{
	std::vector<unsigned int> res;
	for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
	{
		if ( est_adjacent(t1,_ens_tr[i]) )
		{
			res.push_back(i);
		}
	}
	return res;
}

bool Terrain::verif_association ()
{
	//triangle de départ
	_ens_tr[0]->set_num_case(-1); 
	association(_ens_tr[0]);
	
	//verification de l'association
	for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
	{
		if(_ens_tr[i]->get_num_case()==-2 ) // son code est a -2 il n'est pas associé
		{
			std::cout<<"Une partie des triangles ne peut pas être atteinte"<<std::endl;
			return false;
		}
	}
	return true;
}

void Terrain::association(std::shared_ptr<Triangle> const & t1 )
{
	for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
	{
		if (_ens_tr[i]->get_num_case()!=-1) // en l'occurrence il sera a -2
		{
			if ( est_adjacent(t1,_ens_tr[i]) )
			{
				_ens_tr[i]->set_num_case(-1);
				association(_ens_tr[i]);
			}
		}
	}
} 

bool Terrain::creer_cases_sat()
{
	if (_ens_tr.size()==0)
	{
		std::cout<<"Terrain vide"<<std::endl;
		return false;
	}
	if ( !verif_association() )
	{
		return false;
	}
	
	//tous est ok pour SAT
	using namespace Minisat;
    
	Solver solver;
	//structure pour se rappeler des variables SAT
	std::vector<std::vector<int>> varsat_case;
	int compteur_vars=-1;
	
	//initialisation des 2 structures en une fois
	for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
	{
		//creer les variables de couleur de triangle	
		compteur_vars++;
		solver.newVar();
		
		//creer la matrice pour les numéros des variables de cases
		std::vector<int> tmp;
		for (std::vector<std::shared_ptr<Triangle>>::size_type j(0); j<_ens_tr.size(); ++j)
		{
			tmp.push_back(-1);
		}
		varsat_case.push_back(tmp);
	}
	
	//on declare les clauses pour chaque triangles
	for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
	{
		std::vector<unsigned int> num_tradj=triangles_adjacents (_ens_tr[i]);
		
		//instanciation des variables SAT de case
		for ( std::vector<unsigned int>::size_type j(0); j<num_tradj.size(); ++j)
		{
			if (varsat_case[i][num_tradj[j]]==-1)
			{
				compteur_vars++;
				solver.newVar();
				varsat_case[i][num_tradj[j]]=compteur_vars;
			}
		}
		
		//pour la clause Cij ou Cia ou... 1/3
		vec<Lit> une_valide;
		
		for ( std::vector<unsigned int>::size_type j(0); j<num_tradj.size(); ++j)
		{
			//pour la clause Cij ou Cia ou... 2/3
			une_valide.push(mkLit(varsat_case[i][num_tradj[j]]));
			
						
			//les 2 clauses pour  Cij<=>Cji
			solver.addClause( mkLit(varsat_case[i][num_tradj[j]]) , ~mkLit(varsat_case[num_tradj[j]][i]) );
			solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]) , mkLit(varsat_case[num_tradj[j]][i]) );
			
			//les 2 clauses de couleur
			solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]) , ~mkLit(i) , mkLit(num_tradj[j]) );
			solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]) , ~mkLit(num_tradj[j]) , mkLit(i) );			
			
			for ( std::vector<unsigned int>::size_type a(j+1); a<num_tradj.size(); ++a)
			{
				//clause pour Cij=>~Cia
				solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]) , ~mkLit(varsat_case[i][num_tradj[a]]) );
				
				//clause pour Cij et Ni => ~Na
				solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]), ~mkLit(i) , ~mkLit(num_tradj[a]) );
				solver.addClause( ~mkLit(varsat_case[i][num_tradj[j]]), mkLit(i) , mkLit(num_tradj[a]) );
			}
		}
		//pour la clause Cij ou Cia ou... 3/3
		solver.addClause(une_valide);
		une_valide.clear();
		
	}
	
    auto model = solver.solve();
    if ( model ) 
    {
        std::cout << "SAT" <<std::endl;
        //traitement de la reponse
        for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
		{
			for (std::vector<std::shared_ptr<Triangle>>::size_type j(i+1); j<_ens_tr.size(); ++j)
			{
				if (varsat_case[i][j]!=-1 && (solver.modelValue(varsat_case[i][j])==l_True))
				{
					//std::cout<<"case ["<<i<<","<<j<<"] couleur="<<(solver.modelValue(i)==l_True)<<(solver.modelValue(j)==l_True)<<std::endl;
					_ens_tr[i]->set_num_case(_ens_cases.size());
					_ens_tr[j]->set_num_case(_ens_cases.size());
					_ens_cases.push_back(std::make_shared<Case>(Case(_ens_tr[i],_ens_tr[j],(solver.modelValue(j)==l_True))));
						
				}
			}
		}
				
        return true;
    } 
    else 
    {
        std::cout << "UNSAT" <<std::endl;
        return false;
    }
    
}


bool Terrain::creer_cases()
{
	if (_ens_tr.size()==0)
	{
		std::cout<<"Terrain vide"<<std::endl;
		return false;
	}
	if (!((_ens_tr.size()%2)==0))
	{	
		std::cout<<"Nombre impaire de triangle"<<_ens_tr.size()<<std::endl;
		return false;
	}	
	if ( !verif_association() )
	{
		return false;
	}
	
	//on creer une premiere case qui va creer les autres
	int x=0;
	if(! faire_case(_ens_tr[0],true , x))
	{
		std::cout<<"impossible de créer le terrain"<<std::endl;
		return false;
	}
	return true;
}

bool Terrain::faire_case(std::shared_ptr<Triangle> const & t1 , bool color , int & cpt)
{
	std::vector<unsigned int> num_trs_adj=triangles_adjacents (t1);
	
	//pour chacun des triangles adjacents si il n'est pas dans une case on tentera de l'associer 
	//si cela n'a pas donné un terrain valide on detruira l'association et on essayera avec un autre
	for( std::vector<unsigned int>::size_type itr(0); itr<num_trs_adj.size(); ++itr)
	{ 
		if (cpt>100000)
			return false;
		if (_ens_tr[num_trs_adj[itr]]->get_num_case()==-1)
		{
			//sauvegarde de la taille du vecteur pour le remettre bien si on ne peut pas former les cases
			unsigned int sauv_size=_ens_cases.size();
			
			//creation de la case.
			t1->set_num_case(sauv_size);
			_ens_tr[num_trs_adj[itr]]->set_num_case(sauv_size);
			_ens_cases.push_back( std::make_shared<Case>(Case(t1,_ens_tr[num_trs_adj[itr]],color) ));
			
			//triangles adjacents à la case
			std::vector<unsigned int> num_trs_adj_case=triangles_adjacents(_ens_tr[num_trs_adj[itr]]);
			std::vector<unsigned int> num_trs_adj_case_part2=triangles_adjacents(t1);
			num_trs_adj_case.insert( num_trs_adj_case.end(), num_trs_adj_case_part2.begin(), num_trs_adj_case_part2.end() );


			bool tous_vrai=true;
			//pour chaque triangle adjacent à la case
			for( std::vector<unsigned int>::size_type tradjc(0); tradjc<num_trs_adj_case.size(); ++tradjc)
			{ 
				//si le triangle n'est pas dans une case
				if (_ens_tr[num_trs_adj_case[tradjc]]->get_num_case()==-1)
				{
					cpt++;
					if (!faire_case(_ens_tr[num_trs_adj_case[tradjc]],!color, cpt))
					{
						tous_vrai=false;
						break; //l'un des triangles adjacent ne peut pas former de case on ne continue pas et on detruira la case
					}
				}
			}
	
			if (tous_vrai)
				return true;
			else
			{
				while (_ens_cases.size()>sauv_size)
				{
					_ens_cases.back()->get_tr1()->set_num_case(-1);
					_ens_cases.back()->get_tr2()->set_num_case(-1);
					_ens_cases.pop_back();
				}
			}	
		}	
	}
	return false;	
}

void Terrain::do_graph()
{
	//les 2 triangles qui composent la case 0
	std::shared_ptr<Triangle> t1=_ens_cases[0]->get_tr1();
	std::shared_ptr<Triangle> t2=_ens_cases[0]->get_tr2();

	//recherche du "nord"
	//phase 1 les 4 coins de la case
	Point com1, com2;
	Point dif1, dif2;
	
	if (t1->get_point_g()==t2->get_point_g() || t1->get_point_g()==t2->get_point_d() || t1->get_point_g()==t2->get_point_h() )
	{
		com1=t1->get_point_g();
		if (t1->get_point_d()==t2->get_point_g() || t1->get_point_d()==t2->get_point_d() || t1->get_point_d()==t2->get_point_h() )
		{ com2=t1->get_point_g(); }
		else
		{
			dif1=t1->get_point_d();
			com2=t1->get_point_h();
		} 
	}
	else
	{
		dif1=t1->get_point_g();
		com1=t1->get_point_d();
		com2=t1->get_point_h();
	} 
	if (t2->get_point_g()==com1 || t2->get_point_g()==com2)
	{
		if (t2->get_point_d()==com1 || t2->get_point_d()==com2)
		{ dif2=t2->get_point_h(); }
		else
		{ dif2=t2->get_point_d(); }
	}
	else
	{ dif2=t2->get_point_g(); }
	
	//phase 2 le "nord"
	Point max1, max2, max3;
	
	max1=com1;
	if (com2>max1)
	{
		max2=max1;
		max1=com2;
	}
	else
	{ max2=com2; }

	if (dif1>max1)
	{
		max3=max2;
		max2=max1;
		max1=dif1;
	}
	else
	{
		if (dif1>max2)
		{
			max3=max2;
			max2=dif1;
		}
		else
		{ max3=dif1; }
	}
	
	if (dif2>max1)
	{
		max3=max2;
		max2=max1;
		max1=dif2;
	}
	else
	{
		if (dif2>max2)
		{
			max3=max2;
			max2=dif2;
		}
		else
		{
			if (dif2>max3)
			{ max3=dif2; }
		}
	}
	
	//verification de si max 1 et max 2 sont les 2 points opposées
	if ((com1==max1 && com2==max2)||(com2==max1 && com1==max2)||(dif1==max1 && dif2==max2)||(dif2==max1 && dif1==max2))
	{ max2=max3; }
	
	
	//j'ai le haut d'une case random la case 0
	relie_adj(0,0,max1,max2);
	
}

void Terrain::relie_adj(int num_case,int config , Point const & max1 , Point const & max2)
{
	//la config nous donne si on a max1 et max2 en haut 0 a droite 1 a gauche -1 ou en bas 2

	
	//verif pour ne pas refaire la case inutilement et surtout boucler
	if (_ens_cases[num_case]->get_cases_adjacentes()[0]==nullptr &&
		_ens_cases[num_case]->get_cases_adjacentes()[1]==nullptr &&
		_ens_cases[num_case]->get_cases_adjacentes()[2]==nullptr &&
		_ens_cases[num_case]->get_cases_adjacentes()[3]==nullptr )
	{
		std::shared_ptr<Triangle> t1=_ens_cases[num_case]->get_tr1();
		std::shared_ptr<Triangle> t2=_ens_cases[num_case]->get_tr2();
		//phase 1 les 4 coins de la case
		Point com1, com2;
		Point dif1, dif2;
		
		if (t1->get_point_g()==t2->get_point_g() || t1->get_point_g()==t2->get_point_d() || t1->get_point_g()==t2->get_point_h() )
		{
			com1=t1->get_point_g();
			if (t1->get_point_d()==t2->get_point_g() || t1->get_point_d()==t2->get_point_d() || t1->get_point_d()==t2->get_point_h() )
			{
				com2=t1->get_point_d();
				dif1=t1->get_point_h();
			}
			else
			{
				dif1=t1->get_point_d();
				com2=t1->get_point_h();
			} 
		}
		else
		{
			dif1=t1->get_point_g();
			com1=t1->get_point_d();
			com2=t1->get_point_h();
		} 
		if (t2->get_point_g()==com1 || t2->get_point_g()==com2)
		{
			if (t2->get_point_d()==com1 || t2->get_point_d()==com2)
			{ dif2=t2->get_point_h(); }
			else
			{ dif2=t2->get_point_d(); }
		}
		else
		{ dif2=t2->get_point_g(); }
	
		//on a les 4 coins de la case on les orientes bien 		
		Point hg, hd;
		Point bg, bd;
		
		if (com1==max1)
		{
			hd=com1;
			bg=com2;
		}
		else
		{
			if (com2==max1)
			{
				hd=com2;
				bg=com1;
			}
		}
			
		if (dif1==max1)
		{
			hd=dif1;
			bg=dif2;
		}
		else
		{
			if (dif2==max1)
			{
				hd=dif2;
				bg=dif1;
			}
		}
			
		if (com1==max2)
		{
			hg=com1;
			bd=com2;
		}
		else
		{
			if (com2==max2)
			{
				hg=com2;
				bd=com1;
			}
		}
		
		if (dif1==max2)
		{
			hg=dif1;
			bd=dif2;
		}
		else
		{
			if (dif2==max2)
			{
				hg=dif2;
				bd=dif1;
			}
		}
		
		//si on ne vien pas du haut (config 0) on reoriente la case
		if (config==1)//droite
		{
			Point tmp;
			tmp=hd;
			hd=hg;
			hg=bg;
			bg=bd;
			bd=tmp;
		}
		if (config==-1)//gauche
		{
			Point tmp;
			tmp=hg;
			hg=hd;
			hd=bd;
			bd=bg;
			bg=tmp;
		}
		
		if (config==2)//bas
		{
			Point tmp;
			tmp=hg;
			hg=bd;
			bd=tmp;
			
			tmp=hd;
			hd=bg;
			bg=tmp;
		}
		
		//desormais la case est bien orienté
		_ens_cases[num_case]->set_coin_bords_cases(0,Point(hg.get_coord_x() , hg.get_coord_y() , hg.get_coord_z()));
		_ens_cases[num_case]->set_coin_bords_cases(1,Point(bd.get_coord_x() , bd.get_coord_y() , bd.get_coord_z()));
		_ens_cases[num_case]->set_coin_bords_cases(2,Point(hd.get_coord_x() , hd.get_coord_y() , hd.get_coord_z()));
		_ens_cases[num_case]->set_coin_bords_cases(3,Point(bg.get_coord_x() , bg.get_coord_y() , bg.get_coord_z()));
		
		_ens_cases[num_case]->set_centre_bords_cases(0,Point( (hg.get_coord_x()+hd.get_coord_x()) /2, (hg.get_coord_y()+hd.get_coord_y()) /2, (hg.get_coord_z()+hd.get_coord_z()) /2));
		_ens_cases[num_case]->set_centre_bords_cases(1,Point( (bg.get_coord_x()+bd.get_coord_x()) /2, (bg.get_coord_y()+bd.get_coord_y()) /2, (bg.get_coord_z()+bd.get_coord_z()) /2));
		_ens_cases[num_case]->set_centre_bords_cases(2,Point( (hg.get_coord_x()+bg.get_coord_x()) /2, (hg.get_coord_y()+bg.get_coord_y()) /2, (hg.get_coord_z()+bg.get_coord_z()) /2));
		_ens_cases[num_case]->set_centre_bords_cases(3,Point( (bd.get_coord_x()+hd.get_coord_x()) /2, (bd.get_coord_y()+hd.get_coord_y()) /2, (bd.get_coord_z()+hd.get_coord_z()) /2));
		
		for (std::vector<std::shared_ptr<Triangle>>::size_type i(0); i<_ens_tr.size(); ++i)
		{
			if(_ens_tr[i]!=t1 && _ens_tr[i]!=t2 ) 
			{
				if( (_ens_tr[i]->get_point_d()==hd || _ens_tr[i]->get_point_g()==hd || _ens_tr[i]->get_point_h()==hd) &&
					(_ens_tr[i]->get_point_d()==hg || _ens_tr[i]->get_point_g()==hg || _ens_tr[i]->get_point_h()==hg) )
				{	
					_ens_cases[num_case]->set_cases_adjacentes(0, _ens_cases[_ens_tr[i]->get_num_case()]);
					relie_adj(_ens_tr[i]->get_num_case(),2,hg,hd);
				}
				if( (_ens_tr[i]->get_point_d()==bg || _ens_tr[i]->get_point_g()==bg || _ens_tr[i]->get_point_h()==bg) &&
					(_ens_tr[i]->get_point_d()==bd|| _ens_tr[i]->get_point_g()==bd || _ens_tr[i]->get_point_h()==bd) )
				{
					_ens_cases[num_case]->set_cases_adjacentes(1, _ens_cases[_ens_tr[i]->get_num_case()]);
					relie_adj(_ens_tr[i]->get_num_case(),0,bd,bg);
				}
				if( (_ens_tr[i]->get_point_d()==bg || _ens_tr[i]->get_point_g()==bg || _ens_tr[i]->get_point_h()==bg) &&
					(_ens_tr[i]->get_point_d()==hg || _ens_tr[i]->get_point_g()==hg || _ens_tr[i]->get_point_h()==hg) )
				{
					_ens_cases[num_case]->set_cases_adjacentes(2, _ens_cases[_ens_tr[i]->get_num_case()]);
					relie_adj(_ens_tr[i]->get_num_case(),1,bg,hg);
				}	
				if( (_ens_tr[i]->get_point_d()==hd || _ens_tr[i]->get_point_g()==hd || _ens_tr[i]->get_point_h()==hd) &&
					(_ens_tr[i]->get_point_d()==bd || _ens_tr[i]->get_point_g()==bd || _ens_tr[i]->get_point_h()==bd) )
				{
					_ens_cases[num_case]->set_cases_adjacentes(3,_ens_cases[_ens_tr[i]->get_num_case()]);
					relie_adj(_ens_tr[i]->get_num_case(),-1,hd,bd);
				}		
			}
		}
	}	
}




















