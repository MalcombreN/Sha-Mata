#include "jeu.hh"

Jeu::Jeu():
	_etat_jeu(0),	
	_joueur(true),
	_couleur_piece_a_placer(true),
	_type_piece_a_placer(type_piece::pion),
	_case_locked(nullptr),
	_action_effectue(false),
	_compteur_tour(0),
	_compteur_exit(0),
	_piece_a_tuer(-1),
	_piece_tueuse(-1),
	_roi_j1(0),
	_roi_j2(0),
	_display_roi_screen(-1),
	_roi_rock(-1),
	_tour_rock(-1),
	_rock_done(false),
	_pion_changement(-1),
	_changement_screen({false,false,false,false,false}),
	_piece_a_ressusiter(-1),
	_angle_x(0),
	_angle_z(0),
	_eloignement(50),
	_useclic(true),
	_pose_piece_loader(false),
	_rois_loader(false),
	_pieces_loader(false),
	_winner_loader(false),
	_erreur_loader(false),
	_sauv_loader(false),
	_sauvgarder_oui_non(false),
	_echec_sauvgarde(0)
{}

int Jeu::get_etat_jeu()const {return _etat_jeu;}

void Jeu::sauvegarde()
{
	auto file=fopen("./sauv/sauv.txt","w");
	if (file && !_action_effectue)
	{
		std::string text="terrain - ";
		text+=std::to_string(_terrain.get_num_plateau());
		text+="\njoueur - ";
		text+=std::to_string(_joueur);
		text+="\nvivante :";
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
		{
			text+="\ncase - "+std::to_string(_ens_pieces_vivante[i]->get_case_support()->get_tr1()->get_num_case());
			text+="\tjoueur - "+std::to_string(_ens_pieces_vivante[i]->get_joueur())+"\t";
			text+="move - "+std::to_string(_ens_pieces_vivante[i]->get_a_bouger())+"\t";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::roi)
				text+="roi";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::fou)
				text+="fou";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::reine)
				text+="reine";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::cavalier)
				text+="cavalier";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::tour)
				text+="tour";
			if (_ens_pieces_vivante[i]->get_type()==type_piece::pion)
				text+="pion";
								
		}
		text+="\nmorte :";
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			text+="\ncase - "+std::to_string(_ens_pieces_morte[i]->get_case_support()->get_tr1()->get_num_case());
			text+="\tjoueur - "+std::to_string(_ens_pieces_morte[i]->get_joueur())+"\t";
			if (_ens_pieces_morte[i]->get_type()==type_piece::roi)
				text+="roi";
			if (_ens_pieces_morte[i]->get_type()==type_piece::fou)
				text+="fou";
			if (_ens_pieces_morte[i]->get_type()==type_piece::reine)
				text+="reine";
			if (_ens_pieces_morte[i]->get_type()==type_piece::cavalier)
				text+="cavalier";
			if (_ens_pieces_morte[i]->get_type()==type_piece::tour)
				text+="tour";
			if (_ens_pieces_morte[i]->get_type()==type_piece::pion)
				text+="pion";
		}
		
		
		fputs((text.c_str()),file);
		fclose(file);
	}	
	else
	{
		_echec_sauvgarde=120;
	}
}

void Jeu::restore_sauvegarde()
{
	auto file=fopen("./sauv/sauv.txt","r");
	char line [100];
	
	if (file)
	{
		bool terrain_selected=false;
		bool vivante=true;
		while (fgets(line,100,file)!=NULL)
		{
			if (!terrain_selected)
			{
				std::cmatch matchs; 
				std::regex e ("terrain - ([0-9]+)\n");

				if (std::regex_match (line,matchs,e))
				{
					if (_terrain.selection_plateau(std::stoi(matchs[1])))
					{
						std::cout<<"terrain n° "<<matchs[1]<< " -";
						glutAttachMenu(GLUT_RIGHT_BUTTON);
						load_pose_piece_screen();
						load_rois_screen();
						load_win_screen();
						load_pieces();
						load_sauv_screen();
					}
					else
					{
						_etat_jeu=5;
						load_erreur_screen();
						break;
					}
					terrain_selected=true;
				}
			}
			else
			{
				std::cmatch matchs; 
				std::regex e1 ("joueur - ([0-1])\n");
				std::regex e2 ("case - ([0-9]+)\tjoueur - ([0-1])\tmove - ([0-1])\t(.*)(\n)?");
				std::regex e3 ("morte :\n");
				
				if (std::regex_match (line,matchs,e1))
				{
					_joueur=std::stoi(matchs[1]);
					reset_cam();				
				}
				if (std::regex_match (line,matchs,e2))
				{					
					std::unique_ptr<Piece> piece;
					
					if (matchs[4]=="pion")
					{
						piece=std::make_unique<Pion> (Pion(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					if (matchs[4]=="cavalier")
					{
						piece=std::make_unique<Cavalier> (Cavalier(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					if (matchs[4]=="reine")
					{
						piece=std::make_unique<Reine> (Reine(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					if (matchs[4]=="roi")
					{
						piece=std::make_unique<Roi> (Roi(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					if (matchs[4]=="fou")
					{
						piece=std::make_unique<Fou> (Fou(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					if (matchs[4]=="tour")
					{
						piece=std::make_unique<Tour> (Tour(_terrain.get_ens_cases()[std::stoi(matchs[1])],std::stoi(matchs[2])));
					}
					
					if (std::stoi(matchs[3]))
					{
						piece->set_a_bouger();
					}
					
					if (vivante)
					{
						if (matchs[4]=="roi")
						{
							if (std::stoi(matchs[2]))
								_roi_j1++;
							else
								_roi_j2++;
						}
						_ens_pieces_vivante.push_back(std::move(piece));
					}	
					else
					{
						_ens_pieces_morte.push_back(std::move(piece));
						_ens_pieces_morte.back()->disparait();
					}
				}
				if (std::regex_match (line,e3))
				{
					vivante=false;
					std::cout<<"swap mouru";
				}
			}
		}
		if (terrain_selected && _roi_j1>0 && _roi_j2>0)
			_etat_jeu=2;
		else
		{
		_etat_jeu=5;
		load_erreur_screen();
		}
	}	
	else
	{
		_etat_jeu=5;
		load_erreur_screen();
	}
}

void Jeu::gere_menu(int value)
{
	//pieces
	if (value==2) 
	{
		_type_piece_a_placer=type_piece::pion;
	}
	if (value==3) 
	{
		_type_piece_a_placer=type_piece::tour;
	}
	if (value==4) 
	{
		_type_piece_a_placer=type_piece::cavalier;
	}
	if (value==5)
	{
		_type_piece_a_placer=type_piece::fou;
	}
	if (value==6)
	{
		_type_piece_a_placer=type_piece::reine;
	}
	if (value==7) 
	{
		_type_piece_a_placer=type_piece::roi;
	}
	
	if (_etat_jeu==1)
	{
		//couleur
		if (value==0)
		{
			_couleur_piece_a_placer=true;
		}
		if (value==1)
		{
			_couleur_piece_a_placer=false;
		}
		if (value==8)
		{
			if (_ens_pieces_vivante.size()>0)
			{
				if (_ens_pieces_vivante.back()->get_type()==type_piece::roi)
				{
					if (_ens_pieces_vivante.back()->get_joueur())
						_roi_j1--;
					else
						_roi_j2--;
				}
				_ens_pieces_vivante.pop_back();
			}
			
		}
		//pour enlever la dernière pièce
		if (value==9) 
		{
			_ens_pieces_vivante.clear();
			_roi_j1=0;
			_roi_j2=0;
		}
		//pour tout reset
		if (value==10) 
		{
			pose_set_pieces(_terrain.get_num_plateau());
		}
		// si on clique sur le "bouton" commencer
		if (value==11)
		{ 
			if (_roi_j1>0 && _roi_j2>0) 
			{
				_type_piece_a_placer=type_piece::pion;
				_etat_jeu=2;
			}
			else
			{
				_display_roi_screen=300;
			} 
		}
		if (value==12)
		{
			_useclic=false;
			_etat_jeu=0;
			_terrain.clear();
			_roi_j1=0;
			_roi_j2=0;
			_ens_pieces_vivante.clear();
			_ens_pieces_morte.clear();
		}	
	}
}

void Jeu::pose_set_pieces(int num_plateau)
{
	if (num_plateau==1)
	{
		_ens_pieces_vivante.clear();
		_roi_j1=0;
		_roi_j2=0;
		
		for (int i=0 ; i<8 ; i++ )
		{
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[i+8],true)));	
		}
		
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[0],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[7],true )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[1],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[6],true )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[2],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[5],true )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[3],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[4],true )));
		
		for (int i=0 ; i<8 ; i++ )
		{
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[i+48],false)));	
		}
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[56],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[63],false )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[57],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[62],false )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[58],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[61],false )));
		
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[60],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[59],false )));
		
		_roi_j1++;
		_roi_j2++;
	}
	
	if(num_plateau == 4){
		_ens_pieces_vivante.clear();
		_roi_j1=0;
		_roi_j2=0;
		
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[0+32],true)));	
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[3+32],true)));
			
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[7+32],true)));
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[8+32],true)));
			
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[12+32],true)));
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[15+32],true)));
		
		
	
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[0],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[15],true )));
		
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[6+16*1],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[9+16*1],true )));
		
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[4+16*1],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[11+16*1],true )));
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[3],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[5],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[7],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[8],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[10],true )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[12],true )));
		
		//joueur 2
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[0+16*13],false)));	
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[3+16*13],false)));
			
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[7+16*13],false)));
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[8+16*13],false)));
			
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[12+16*13],false)));
			
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_ens_cases()[15+16*13],false)));
		
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[0+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_ens_cases()[15+16*15],false )));
		
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[6+16*14],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_ens_cases()[9+16*14],false )));
		
		
		
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[4+16*14],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_ens_cases()[11+16*14],false )));
	
		
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[3+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[5+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[7+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_ens_cases()[8+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[10+16*15],false )));
		_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_ens_cases()[12+16*15],false )));
	
	
	
		_roi_j1=2;
		_roi_j2=2;
	}
}

void Jeu::reset_cam()
{
	if (_joueur)
	{
		if (_terrain.get_num_plateau()==1 || _terrain.get_num_plateau()==3 )
		{
			_angle_x=45;
		}
		if (_terrain.get_num_plateau()==2)
		{
			_angle_x=0;
		}
		if (_terrain.get_num_plateau()==4)
		{
			_angle_x=45;
			_eloignement=75;
		}
		_angle_z=90;
	}
	else
	{
		if (_terrain.get_num_plateau()==1 || _terrain.get_num_plateau()==3 )
		{
			_angle_x=45;
		}
		if (_terrain.get_num_plateau()==2)
		{
			_angle_x=0;
		}
		if (_terrain.get_num_plateau()==4)
		{
			_angle_x=45;
			_eloignement=75;
		}
		_angle_z=-90;
	}
}

void Jeu::load_entering_screen()
{
	float taille_char;
	std::string str ;
	const char *cstr;

	_affichage_entering_screen = glGenLists(1);
	
	glNewList(_affichage_entering_screen, GL_COMPILE);
	{
	
	
		//liste affichage ecran selection plateau
		glPushMatrix();
			translation(0,0.05,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
			
			
		
			//echecs
			glPushMatrix();
				//BOX
				glColor3f(0,0,1);
				translation(0,5,0);
				glPushMatrix();
					translation(-25/2,0,0);
					
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "echecs";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
			//sphere
			glPushMatrix();
				translation(0,-5,0);
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "sphere";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
			//demo
			glPushMatrix();
				translation(0,-15,0);
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "demo";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
			
			//montagne
			glPushMatrix();
				translation(0,-25,0);
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "montagne";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.04;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.04, 0.04, 0.04);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
			
			//sāh māta
			glPushMatrix();
				translation(0,20,0);
				glScalef(1.2,1.2,1.2);
				//BOX
				glPushMatrix();
					translation(-35/2,0,0);
					
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(35.,5.5,0.);
						glVertex3f(35.,5.5,0.);
						glVertex3f(35.,-2.,0.);
						glVertex3f(35.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "sah mata";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(1,0,0.5);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();	
				translation(5,-40,0);
				//pour le logo
				glColor3f(0.67, 0.84, 0.90);
				translation(-38,5,0);
				glBindTexture (GL_TEXTURE_2D, textures[26]);
				glEnable(GL_TEXTURE_2D);
				glBegin(GL_QUADS);
					glTexCoord2f(1,1);glVertex3f(5,-5,0);
					glTexCoord2f(0,1);glVertex3f(-5,-5,0);
					glTexCoord2f(0,0);glVertex3f(-5,5,0);
					glTexCoord2f(1,0);glVertex3f(5,5,0);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				translation(38,-3,0);
				//====================
				str = "creer par MA Tianning et MALCOMBRE Nicolas";
				cstr = str.c_str();
				taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.02;
					translation(-taille_char/2,0,0);
				glColor3f(0,0,1);
				glScalef(0.02, 0.02, 0.02);
				for (unsigned int i=0 ; i<str.length() ; i++)
					glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
			glPopMatrix();
			
			//reprise game
			glPushMatrix();
				translation(-30,30,0);
				glScalef(0.5,0.5,0.5);
				glColor3f(0,0.5,0.1);
				//BOX
				glPushMatrix();
					glScalef(0.80,1,1);
					translation(-35/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(35.,5.5,0.);
						glVertex3f(35.,5.5,0.);
						glVertex3f(35.,-2.,0.);
						glVertex3f(35.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "continue";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
					
		glPopMatrix();
	}
	glEndList();
}

void Jeu::load_pose_piece_screen()
{
	if (!_pose_piece_loader)
	{
		_pose_piece_loader=true;
		float taille_char;
		std::string str ;
		const char *cstr;
	
	//liste couleur blanc
	_couleur_blanche = glGenLists(1);
	glNewList(_couleur_blanche, GL_COMPILE);
	{
	
	

		glPushMatrix();
			translation(0.1,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					glColor3f(1,1,1);
					translation(-25*0.75/2,0,0);
					glScalef(0.75, 1, 1);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "blanc";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,0);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
	
	//liste couleur noir
	_couleur_noir = glGenLists(1);
	glNewList(_couleur_noir, GL_COMPILE);
	{
		glPushMatrix();
			translation(0.1,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					glColor3f(0,0,0);
					translation(-25*0.75/2,0,0);
					glScalef(0.75, 1, 1);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "noir";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(1,1,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
	
	//liste pion
	_screen_pion = glGenLists(1);
	glNewList(_screen_pion, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "pion";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
	
	
	//liste roi
	_screen_roi = glGenLists(1);
	glNewList(_screen_roi, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "roi";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
	
	//liste reine
	_screen_reine = glGenLists(1);
	glNewList(_screen_reine, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "reine";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
		
	//liste cavalier
	_screen_cavalier = glGenLists(1);
	glNewList(_screen_cavalier, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "cavalier";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
	
	//liste fou
	_screen_fou = glGenLists(1);
	glNewList(_screen_fou, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "fou";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
		
	//liste tour
	_screen_tour = glGenLists(1);
	glNewList(_screen_tour, GL_COMPILE);
	{
		glPushMatrix();
			translation(-0.3,0.4,0);
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
		
			glPushMatrix();
				//BOX
				glPushMatrix();
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "tour";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();
		
		
	//liste indication
	_screen_indication = glGenLists(1);
	glNewList(_screen_indication, GL_COMPILE);
	{
		glPushMatrix();
			glScalef(0.015, 0.015,0.015);
			glLineWidth(2.5);
			translation(-15,-30,0);
			
			//TEXT
			glPushMatrix();	
				str = "   clic droit = menu";
				cstr = str.c_str();
				glColor3f(0,0,1);
				glScalef(0.025, 0.025, 0.025);
				for (unsigned int i=0 ; i<str.length() ; i++)
					glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
			glPopMatrix();
			glPushMatrix();
			{
				translation(-8,0,0);
				glPushMatrix();
				{
					translation(0,-4,0);
					//BOX
					glPushMatrix();
						translation(-7,0,0);
						glBegin(GL_LINES);
							glVertex3f(0,-1,0.);
							glVertex3f(0,2.5,0.);
							glVertex3f(0,2.5,0.);
							glVertex3f(14.,2.5,0.);
							glVertex3f(14.,2.5,0.);
							glVertex3f(14.,-1,0.);
							glVertex3f(14.,-1,0.);
							glVertex3f(0,-1,0.);
						glEnd();
					glPopMatrix();
					
					//TEXT
					glPushMatrix();	
						str = "espace";
						cstr = str.c_str();
						taille_char=0;
						for (unsigned int i=0 ; i<str.length() ; i++)
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.025;
						translation(-taille_char/2,0,0);
						
						glScalef(0.025, 0.025, 0.025);
						for (unsigned int i=0 ; i<str.length() ; i++)
							glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
					glPopMatrix();
				}
				glPopMatrix();
				//zqsd
				glPushMatrix();
				{
					//q
					glPushMatrix();
					{
						translation(-5,0,0);
						//BOX
						glPushMatrix();
							translation(-2,0,0);
							glBegin(GL_LINES);
								glVertex3f(0,-1,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(0,-1,0.);
							glEnd();
						glPopMatrix();
						
						//TEXT
						glPushMatrix();	
							str = "q";
							cstr = str.c_str();
							taille_char=0;
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,'q')*0.025;
							translation(-taille_char/2,0,0);
							
							glScalef(0.025, 0.025, 0.025);
							for (unsigned int i=0 ; i<str.length() ; i++)
								glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
						glPopMatrix();
					}
					glPopMatrix();
					//s
					glPushMatrix();
					{
						//BOX
						glPushMatrix();
							translation(-2,0,0);
							glBegin(GL_LINES);
								glVertex3f(0,-1,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(0,-1,0.);
							glEnd();
						glPopMatrix();
						
						//TEXT
						glPushMatrix();	
							str = "s";
							cstr = str.c_str();
							taille_char=0;
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,'s')*0.025;
							translation(-taille_char/2,0,0);
							
							glScalef(0.025, 0.025, 0.025);
							for (unsigned int i=0 ; i<str.length() ; i++)
								glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
						glPopMatrix();
					}
					glPopMatrix();
					//d
					glPushMatrix();
					{
						translation(5,0,0);
						//BOX
						glPushMatrix();
							translation(-2,0,0);
							glBegin(GL_LINES);
								glVertex3f(0,-1,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(0,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,2.5,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(4.,-1,0.);
								glVertex3f(0,-1,0.);
							glEnd();
						glPopMatrix();
						
						//TEXT
						glPushMatrix();	
							str = "d";
							cstr = str.c_str();
							taille_char=0;
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,'d')*0.025;
							translation(-taille_char/2,0,0);
							
							glScalef(0.025, 0.025, 0.025);
							for (unsigned int i=0 ; i<str.length() ; i++)
								glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
						glPopMatrix();
					}
					glPopMatrix();
					//z
					{
						translation(0,4,0);
						glPushMatrix();
							//BOX
							glPushMatrix();
								translation(-2,0,0);
								glBegin(GL_LINES);
									glVertex3f(0,-1,0.);
									glVertex3f(0,2.5,0.);
									glVertex3f(0,2.5,0.);
									glVertex3f(4.,2.5,0.);
									glVertex3f(4.,2.5,0.);
									glVertex3f(4.,-1,0.);
									glVertex3f(4.,-1,0.);
									glVertex3f(0,-1,0.);
								glEnd();
							glPopMatrix();
							
							//TEXT
							glPushMatrix();	
								str = "z";
								cstr = str.c_str();
								taille_char=0;
								taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,'z')*0.025;
								translation(-taille_char/2,0,0);
								
								glScalef(0.025, 0.025, 0.025);
								for (unsigned int i=0 ; i<str.length() ; i++)
									glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
							glPopMatrix();
					glPopMatrix();
				}
				}
				glPopMatrix();
			}
			glPopMatrix();
		glPopMatrix();
	}
	glEndList();	
		
	}
}

void Jeu::load_pieces()
{
	//liste affichage ecran selection piece à poser
	if (!_pieces_loader)
	{
		_pieces_loader=true;
		Piece::load_piece();
		Pion::load_piece();
		glDisable(GL_TEXTURE_2D);
		Roi::load_piece();
		Fou::load_piece();
		Reine::load_piece();
		Cavalier::load_piece();
		Tour::load_piece();
	}
}

void Jeu::load_erreur_screen()
{
	if (!_erreur_loader)
	{
		_erreur_loader=true;
		
		float taille_char;
		std::string str ;
		const char *cstr;

		_screen_erreur = glGenLists(1);
		glNewList(_screen_erreur, GL_COMPILE);
		{
			glPushMatrix();
				glScalef(0.015, 0.015,0.015);
				glLineWidth(2.5);
				translation(0,5,0);
				glColor3ub(187,11,11);
				//TEXT
				glPushMatrix();	
					str = "erreur lors de"; 
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
				
				//TEXT
				translation(0,-10,0);
				glPushMatrix();	
					str ="la creation de la partie";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();

			glPopMatrix();
		}
		glEndList();
	}
}

void Jeu::load_rois_screen()
{
	if (!_rois_loader)
	{
		_rois_loader=true;
		
		float taille_char;
		std::string str ;
		const char *cstr;

		_screen_roi_erreur = glGenLists(1);
		glNewList(_screen_roi_erreur, GL_COMPILE);
		{
			glPushMatrix();
				translation(0,0,0);
				glScalef(0.015, 0.015,0.015);
				glLineWidth(2.5);
				translation(0,20,0);
				glColor3ub(187,11,11);
				glPushMatrix();	
					//TEXT
					glPushMatrix();	
						str = "il faut un roi dans chaque equipe";
						cstr = str.c_str();
						taille_char=0;
						for (unsigned int i=0 ; i<str.length() ; i++)
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.025;
						translation(-taille_char/2,0,0);
						
						glScalef(0.025, 0.025, 0.025);
						for (unsigned int i=0 ; i<str.length() ; i++)
							glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
					glPopMatrix();
					
					translation(0,-4,0);
					glPushMatrix();	
						str = "pour commencer la partie";
						cstr = str.c_str();
						taille_char=0;
						for (unsigned int i=0 ; i<str.length() ; i++)
							taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.025;
						translation(-taille_char/2,0,0);
	
						glScalef(0.025, 0.025, 0.025);
						for (unsigned int i=0 ; i<str.length() ; i++)
							glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		}
		glEndList();	
	}
}

void Jeu::load_win_screen()
{
	if (!_winner_loader)
	{
		_rois_loader=true;
		
		float taille_char;
		std::string str ;
		const char *cstr;

		_screen_j1_win = glGenLists(1);
		glNewList(_screen_j1_win, GL_COMPILE);
		{
			glPushMatrix();
				glScalef(0.015, 0.015,0.015);
				glLineWidth(2.5);
				translation(0,25,0);
				glColor3ub(187,11,11);
				//TEXT
				glPushMatrix();	
					str = "Le joueur 1 gagne !";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();

			glPopMatrix();
		}
		glEndList();	
		
		_screen_j2_win = glGenLists(1);
		glNewList(_screen_j2_win, GL_COMPILE);
		{
			glPushMatrix();
				glScalef(0.015, 0.015,0.015);
				glLineWidth(2.5);
				translation(0,25,0);
				glColor3ub(187,11,11);
				//TEXT
				glPushMatrix();	
					str = "Le joueur 2 gagne !";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();

			glPopMatrix();
		}
		glEndList();	
	}
}

void Jeu::load_sauv_screen()
{
	if(!_sauv_loader)
	{
		_sauv_loader=true;
		
		float taille_char;
		std::string str ;
		const char *cstr;
		
		_screen_sauv_echec=glGenLists(1);
		
		glNewList(_screen_sauv_echec, GL_COMPILE);
		{
			//sphere
			glPushMatrix();
			
				glScalef(0.005, 0.0075,0.0075);
				glLineWidth(2.5);
				translation(-35,-60,0);
				glColor3ub(187,11,11);
				//TEXT
				glPushMatrix();	
					
					str = "erreur";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		}
		glEndList();
		
		_screen_sauv=glGenLists(1);
		
		glNewList(_screen_sauv, GL_COMPILE);
		{
			//sphere
			glPushMatrix();
				glColor3f(1,1,1);
				glScalef(0.0075, 0.0075,0.0075);
				glLineWidth(2.5);
				translation(-60,-60,0);
				//BOX
				glPushMatrix();
					glScalef(1.25,1,1);
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "sauvgarde";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		}
		glEndList();
		
		_screen_sauv_oui=glGenLists(1);
		
		glNewList(_screen_sauv_oui, GL_COMPILE);
		{
			//sphere
			glPushMatrix();
				
				glScalef(0.0075, 0.0075,0.0075);
				glLineWidth(2.5);
				translation(-35,-60,0);
				//BOX
				glPushMatrix();
					glScalef(0.5,1,1);
					translation(-25/2,0,0);
					glColor3f(0,0,1);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "oui";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		}
		glEndList();
		
		_screen_sauv_non=glGenLists(1);
		
		glNewList(_screen_sauv_non, GL_COMPILE);
		{
			//sphere
			glPushMatrix();
				glColor3f(0,0,1);
				glScalef(0.005, 0.0075,0.0075);
				glLineWidth(2.5);
				translation(-30,-60,0);
				//BOX
				glPushMatrix();
					glScalef(0.75,1,1);
					translation(-25/2,0,0);
					glBegin(GL_LINES);
						glVertex3f(-0.5,-2.,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(-0.5,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,5.5,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(25.,-2.,0.);
						glVertex3f(-0.5,-2.,0.);
					glEnd();
				glPopMatrix();
				
				//TEXT
				glPushMatrix();	
					str = "non";
					cstr = str.c_str();
					taille_char=0;
					for (unsigned int i=0 ; i<str.length() ; i++)
						taille_char+=glutStrokeWidth(GLUT_STROKE_ROMAN,cstr[i])*0.05;
					translation(-taille_char/2,0,0);
					
					glColor3f(0,0,1);
					glScalef(0.05, 0.05, 0.05);
					for (unsigned int i=0 ; i<str.length() ; i++)
						glutStrokeCharacter(GLUT_STROKE_ROMAN, cstr[i]);
				glPopMatrix();
			glPopMatrix();
		}
		glEndList();
	}	
}

void Jeu::cam_verticale(int val)
{
	_angle_x+=val;
}

void Jeu::cam_horizontale(int val)
{
	_angle_z+=val;
}


void Jeu::cam_eloignement()
{
	if(_terrain.get_num_plateau()==4){
		if (_eloignement<68)
			_eloignement+=1;
	}
	else{
		if (_eloignement<48)
			_eloignement+=1;
	}
}

void Jeu::cam_rapprochement()
{
	if (_eloignement>1)
		_eloignement-=1;
}

void Jeu::clic(int x,int y)
{
	//std::cout<<x<<" - "<<y<<std::endl;
	if (_etat_jeu==0 ) //on est en phase de selection du terrain
	{
		if (_useclic)
		{
			int jeu=-1;
			
			if (x>(largeur/2-((hauteur*100)/600) )&& x<(largeur/2+((hauteur*100)/600) ) && y>=((190*hauteur)/600) && y<=((250*hauteur)/600) )
				jeu=1;
			if (x>(largeur/2-((hauteur*100)/600) )&& x<(largeur/2+((hauteur*100)/600) ) && y>=((270*hauteur)/600) && y<=((330*hauteur)/600) )
				jeu=2;
			if (x>(largeur/2-((hauteur*100)/600) )&& x<(largeur/2+((hauteur*100)/600) ) && y>=((350*hauteur)/600) && y<=((410*hauteur)/600) )
				jeu=3;
			if (x>(largeur/2-((hauteur*100)/600) )&& x<(largeur/2+((hauteur*100)/600) ) && y>=((430*hauteur)/600) && y<=((485*hauteur)/600) )
				jeu=4;
			if (x>(largeur/2-((hauteur*290)/600) )&& x<(largeur/2+((hauteur*175)/600) ) && y>=((20*hauteur)/600) && y<=((50*hauteur)/600) )
				restore_sauvegarde();
			
			if (jeu!=-1 && _terrain.selection_plateau(jeu))
			{
				reset_cam();
				glutAttachMenu(GLUT_RIGHT_BUTTON);
				_etat_jeu=1;
				load_pose_piece_screen();
				load_rois_screen();
				load_win_screen();
				load_pieces();
				load_sauv_screen();
			}
			else
			{
				if (jeu!=-1)
				{
					_etat_jeu=5;
					load_erreur_screen();
				}
			}
		}
		else
		{_useclic=true; }
	}
	if ( _etat_jeu==2 ) //on est en phase de promotion
	{
		int nbtrue=0;
		for (unsigned int i=0 ; i<_changement_screen.size() ; i++)
		{
			if (_changement_screen[i])
				nbtrue++;
		}
		int num_case=-1;
		if (x>(largeur/2-((hauteur*85)/600) )&& x<(largeur/2+((hauteur*65)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue==1 )
		{
			num_case=0;
		}
		if (x>(largeur/2-((hauteur*140)/600) )&& x<(largeur/2+((hauteur*10)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue==2 )
		{
			num_case=0;
		}
		if (x>(largeur/2+((hauteur*20)/600) )&& x<(largeur/2+((hauteur*170)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue==2 )
		{
			num_case=1;
		}
		if (x>(largeur/2-((hauteur*240)/600) )&& x<(largeur/2-((hauteur*90)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue>=3)
		{
			num_case=0;
		}
		if (x>(largeur/2-((hauteur*85)/600) )&& x<(largeur/2+((hauteur*65)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue>=3)
		{
			num_case=1;
		}
		if (x>(largeur/2+((hauteur*70)/600) )&& x<(largeur/2+((hauteur*220)/600) ) && y>=((35*hauteur)/600) && y<=((80*hauteur)/600) && nbtrue>=3)
		{
			num_case=2;
		}
		if (x>(largeur/2-((hauteur*85)/600) )&& x<(largeur/2+((hauteur*65)/600) ) && y>=((95*hauteur)/600) && y<=((140*hauteur)/600) && nbtrue==4)
		{
			num_case=3;
		}
		if (x>(largeur/2-((hauteur*165)/600) )&& x<(largeur/2+((hauteur*15)/600) ) && y>=((95*hauteur)/600) && y<=((140*hauteur)/600) && nbtrue==5)
		{
			num_case=3;
		}
		if (x>(largeur/2-((hauteur*5)/600) )&& x<(largeur/2+((hauteur*140)/600) ) && y>=((95*hauteur)/600) && y<=((140*hauteur)/600) && nbtrue==5)
		{
			num_case=4;
		}
		
		for (unsigned int i=0 ; i<_changement_screen.size() ; i++)
		{
			if (num_case==0 && _changement_screen[i]==true)
			{
				if (i==0)
					_type_piece_a_placer=type_piece::cavalier;
				if (i==1)
					_type_piece_a_placer=type_piece::roi;
				if (i==2)
					_type_piece_a_placer=type_piece::reine;
				if (i==3)
					_type_piece_a_placer=type_piece::tour;
				if (i==4)
					_type_piece_a_placer=type_piece::fou;
				break;
			}
			else
			{
				if (num_case>0 && _changement_screen[i]==true)
					num_case--;
			}
		}
		
		if (x>(largeur/2-((hauteur*290)/600) )&& x<(largeur/2-((hauteur*170)/600) ) && y>=((515*hauteur)/600) && y<=((545*hauteur)/600) )
		{
			_sauvgarder_oui_non=true;
			_echec_sauvgarde=0;
		}
		if (x>(largeur/2-((hauteur*160)/600) )&& x<(largeur/2-((hauteur*110)/600) ) && y>=((515*hauteur)/600) && y<=((545*hauteur)/600) )
		{
			sauvegarde();
			_sauvgarder_oui_non=false;
		}
		if (x>(largeur/2-((hauteur*100)/600) )&& x<(largeur/2-((hauteur*50)/600) ) && y>=((515*hauteur)/600) && y<=((545*hauteur)/600) )
		{
			_sauvgarder_oui_non=false;
		}
	}
}

void Jeu::affiche_piece_screen()
{
	if(_couleur_piece_a_placer)
	{
		glCallList(_couleur_blanche);
	}
	else
	{
		glCallList(_couleur_noir);
	}
	glPushMatrix();
		glColor3f(0,0,1);
		if (_type_piece_a_placer==type_piece::pion)
			glCallList(_screen_pion);
		if (_type_piece_a_placer==type_piece::cavalier)
			glCallList(_screen_cavalier);
		if (_type_piece_a_placer==type_piece::fou)
			glCallList(_screen_fou);
		if (_type_piece_a_placer==type_piece::reine)
			glCallList(_screen_reine);
		if (_type_piece_a_placer==type_piece::tour)
			glCallList(_screen_tour);
		if (_type_piece_a_placer==type_piece::roi)
			glCallList(_screen_roi);
	glPopMatrix();
}


void Jeu::display()
{
	if (_etat_jeu==0)
	{
		glutDetachMenu(GLUT_RIGHT_BUTTON);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();	
			translation(0,0,0);
			glCallList(_affichage_entering_screen);
		glPopMatrix();
		
	}
	else
	{
		if (_etat_jeu==1)
		{
			affiche_piece_screen();
			glCallList(_screen_indication);
			
			if (_display_roi_screen>0)
			{
				glCallList(_screen_roi_erreur);
				_display_roi_screen-=1;	
			}

			translation(0,0,(-_eloignement));
			rotation(_angle_x,_angle_z,0);
			
			//affichage plateau
			_terrain.display(inverse(0));
			//affichage des pièces
			pieces_display();
		}
		else
		{
			if (_etat_jeu==2)
			{
				glutDetachMenu(GLUT_RIGHT_BUTTON);
				if (_piece_a_tuer!=-1 && _piece_a_ressusiter==-1 )
				{
					kill();
				}
				if (_piece_a_ressusiter!=-1 )
				{
					ressussite();
				}
				if (_roi_rock!=-1)
				{
					rock();
				}
				if (_pion_changement!=-1)
				{
					changement();
				}
				change_joueur();
				
				if (_sauvgarder_oui_non)
				{
					glCallList(_screen_sauv_oui);
					glCallList(_screen_sauv_non);
				}
				else
				{
					_echec_sauvgarde--;
					if (_echec_sauvgarde>0)
					{
						glCallList(_screen_sauv_echec);
					}
				}
				
				glCallList(_screen_sauv);
				translation(0,0,(-_eloignement));
				rotation(_angle_x,_angle_z,0);
				//affichage plateau
				_terrain.display(inverse(0));
				//affichage des pièces
				pieces_display();
			}
			else
			{	
				if (_etat_jeu==3)
				{
					if (_roi_j1>0)
					{
						glCallList(_screen_j1_win);
					}	
					else
					{
						glCallList(_screen_j2_win);
					}	
					
					translation(0,0,(-_eloignement));
					rotation(_angle_x,_angle_z,0);
					
					_terrain.display(inverse(0));
					pieces_display();
						
					_compteur_exit+=1;
					if (_compteur_exit>600)
					{
						exit(1);
					}
				}		
				if (_etat_jeu==5)
				{
					_compteur_exit+=1;
					if (_compteur_exit>600)
					{
						exit(1);
					}
					glCallList(_screen_erreur);
				}
			}
		}
	}
}

void Jeu::changement()
{
	if (!_changement_screen[0] && !_changement_screen[1] && !_changement_screen[2] && !_changement_screen[3] && !_changement_screen[4] )
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur)
			{
				if (_ens_pieces_morte[i]->get_type()==type_piece::cavalier)
					_changement_screen[0]=true;
				if (_ens_pieces_morte[i]->get_type()==type_piece::roi)
					_changement_screen[1]=true;
				if (_ens_pieces_morte[i]->get_type()==type_piece::reine)
					_changement_screen[2]=true;
				if (_ens_pieces_morte[i]->get_type()==type_piece::tour)
					_changement_screen[3]=true;
				if (_ens_pieces_morte[i]->get_type()==type_piece::fou)
					_changement_screen[4]=true;
			}
		}
		if(!_changement_screen[0] && !_changement_screen[1] && !_changement_screen[2] && !_changement_screen[3] && !_changement_screen[4] ){
			_pion_changement = -1;
		}
	}
	else
	{
		int nbtrue=0;
		for (unsigned int i=0 ; i<_changement_screen.size() ; i++)
		{
			if (_changement_screen[i])
				nbtrue++;
		}
		
		int i=0;
		glPushMatrix();
			
			if (nbtrue>=3)
				translation(-0.4,0.15,0);
			if (nbtrue==1)
				translation(-0.1,0.15,0);
			if (nbtrue==2)
				translation(-0.2,0.15,0);
				
			glScalef(0.75,0.75,0.75);
			if (_changement_screen[0])
			{	
				translation(0.4,0,0);
				i+=1;
				glPushMatrix();
					if (_type_piece_a_placer==type_piece::cavalier)
						glColor3f(0,1,0);
					else
					glColor3ub(187,11,11);
					glCallList(_screen_cavalier);	
				glPopMatrix();
			}
			if (_changement_screen[1])
			{
				translation(0.4,0,0);
				i+=1;
				glPushMatrix();
					if (_type_piece_a_placer==type_piece::roi)
						glColor3f(0,1,0);
					else
					glColor3ub(187,11,11);
					glCallList(_screen_roi);
				glPopMatrix();
			}
			if (_changement_screen[2])
			{
				translation(0.4,0,0);
				i+=1;
				glPushMatrix();
					if (_type_piece_a_placer==type_piece::reine)
						glColor3f(0,1,0);
					else
					glColor3ub(187,11,11);
					glCallList(_screen_reine);
				glPopMatrix();
			}
			if (_changement_screen[3])
			{
				if (i!=3)
					translation(0.4,0,0);
				else
					if (!_changement_screen[4])
						translation(-0.4,-0.15,0);
					else
						translation(-0.6,-0.15,0);
				i+=1;
				glPushMatrix();
					if (_type_piece_a_placer==type_piece::tour)
						glColor3f(0,1,0);
					else
					glColor3ub(187,11,11);
					glCallList(_screen_tour);
				glPopMatrix();
				
			}
			if (_changement_screen[4])
			{
				
				if (i!=3)
					translation(0.4,0,0);
				else
					translation(-0.4,-0.15,0);
				i+=1;
				glPushMatrix();
					if (_type_piece_a_placer==type_piece::fou)
						glColor3f(0,1,0);
					else
					glColor3ub(187,11,11);
					glCallList(_screen_fou);
				glPopMatrix();
			}
		glPopMatrix();
	}
}


void Jeu::rock()
{
	if (_ens_pieces_vivante[_roi_rock]->ready())
	{
		if (!_rock_done)
		{
			_ens_pieces_vivante[_tour_rock]->tuer();
			_rock_done=true;
		}
		else
		{
			if (_ens_pieces_vivante[_tour_rock]->disparue())
			{
				if (_ens_pieces_vivante[_tour_rock]->get_case_support()->get_cases_adjacentes()[0]==_ens_pieces_vivante[_roi_rock]->get_case_support())
				{
					_ens_pieces_vivante[_tour_rock]->set_case_support(_ens_pieces_vivante[_roi_rock]->get_case_support()->get_cases_adjacentes()[0]);
					_ens_pieces_vivante[_tour_rock]->ressussiter();
				}
				else
				{
					if (_ens_pieces_vivante[_tour_rock]->get_case_support()->get_cases_adjacentes()[1]==_ens_pieces_vivante[_roi_rock]->get_case_support())
					{
						_ens_pieces_vivante[_tour_rock]->set_case_support(_ens_pieces_vivante[_roi_rock]->get_case_support()->get_cases_adjacentes()[1]);
						_ens_pieces_vivante[_tour_rock]->ressussiter();
					}
					else
					{
						if (_ens_pieces_vivante[_tour_rock]->get_case_support()->get_cases_adjacentes()[2]==_ens_pieces_vivante[_roi_rock]->get_case_support())
						{
							_ens_pieces_vivante[_tour_rock]->set_case_support(_ens_pieces_vivante[_roi_rock]->get_case_support()->get_cases_adjacentes()[2]);
							_ens_pieces_vivante[_tour_rock]->ressussiter();
						}
						else
						{
							_ens_pieces_vivante[_tour_rock]->set_case_support(_ens_pieces_vivante[_roi_rock]->get_case_support()->get_cases_adjacentes()[3]);
							_ens_pieces_vivante[_tour_rock]->ressussiter();

						}
					}
				}	
				_roi_rock=-1;
				_tour_rock=-1;
				_rock_done=false;
			}
		}
	}
}

void Jeu::kill()
{
	if (_ens_pieces_vivante[_piece_a_tuer]->disparue() )
	{				
		_ens_pieces_vivante[_piece_tueuse]->termine_deplacement();
		_piece_tueuse=-1;
		if (_ens_pieces_vivante[_piece_a_tuer]->get_type()==type_piece::roi)
		{
			if (_ens_pieces_vivante[_piece_a_tuer]->get_joueur())
				_roi_j1--;
			else
				_roi_j2--;
		}
		if (_ens_pieces_vivante[_piece_a_tuer]->get_type()!=type_piece::pion)
			_ens_pieces_morte.push_back(std::move(_ens_pieces_vivante[_piece_a_tuer]));
		_ens_pieces_vivante.erase(_ens_pieces_vivante.begin()+_piece_a_tuer);
		_piece_a_tuer=-1;						
	}
	else
	{
		if (_ens_pieces_vivante[_piece_tueuse]->get_a_attaquer())
			_ens_pieces_vivante[_piece_a_tuer]->tuer();
	}	
}

void Jeu::ressussite()
{
	if (_ens_pieces_vivante[_piece_a_tuer]->ready())
		_ens_pieces_vivante[_piece_a_tuer]->tuer();
	if (_ens_pieces_vivante[_piece_a_tuer]->disparue() && _ens_pieces_morte[_piece_a_ressusiter]->disparue())
	{
		_ens_pieces_morte[_piece_a_ressusiter]->set_case_support(_ens_pieces_vivante[_piece_a_tuer]->get_case_support());
		
		_ens_pieces_vivante.push_back(std::move(_ens_pieces_morte[_piece_a_ressusiter]));
		
		_ens_pieces_vivante.erase(_ens_pieces_vivante.begin()+_piece_a_tuer);
		_ens_pieces_morte.erase(_ens_pieces_morte.begin()+_piece_a_ressusiter);
		
		_ens_pieces_vivante.back()->ressussiter();
		
		_piece_a_ressusiter=-1;
		_piece_a_tuer=-1;		
	}
}

void Jeu::change_joueur()
{
	if (_action_effectue && _pion_changement==-1)
	{
		bool tous_fini=true;
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
		{
			if (!_ens_pieces_vivante[i]->ready())
			{
				tous_fini=false;
			}
		}
		if (tous_fini && (_roi_j1==0 || _roi_j2==0))
		{
			glutDetachMenu(GLUT_RIGHT_BUTTON);
			_etat_jeu=3;
			_ens_pieces_morte.back()->get_case_support()->change_target();
		}
		else
		{
			if (tous_fini)
			{
				_compteur_tour++;
				if (_compteur_tour>=60)
				{
					_joueur=!_joueur;
					_compteur_tour=0;
					_action_effectue=false;
					reset_cam();
				}			
			}
		}		
	}
}

void Jeu::select_autre_case(unsigned int x)
{
	_terrain.select_autre_case(inverse(x));
}

int Jeu::inverse(int x)
{
	if (_joueur)
	{ return x; }
	else
	{
		if (x%2==0)
			return x+1;
		else
			return x-1;
	}
}

void Jeu::lock_la_case()
{
	if (_etat_jeu==1)
	{
		//placement de la pièce
		place_piece();
	}
	else
	{
		if (_etat_jeu==2 && _pion_changement==-1)
		{
			if (!_action_effectue)
				action_joueur();
		}
		else
		{
			if (_etat_jeu==2 && _pion_changement!=-1)
			{
				validation_changement();
			}
		}		
	}
}

void Jeu::validation_changement()
{	
	if (_type_piece_a_placer==type_piece::cavalier)
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur && _ens_pieces_morte[i]->get_type()==type_piece::cavalier)
			{
				_piece_a_ressusiter=i;
				_piece_a_tuer=_pion_changement;
				_pion_changement=-1;
				break;
			}
		} 
	}
	if (_type_piece_a_placer==type_piece::fou)
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur && _ens_pieces_morte[i]->get_type()==type_piece::fou)
			{
				_piece_a_ressusiter=i;
				_piece_a_tuer=_pion_changement;
				_pion_changement=-1;
				break;
			}
		} 
	}
	if (_type_piece_a_placer==type_piece::reine)
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur && _ens_pieces_morte[i]->get_type()==type_piece::reine)
			{
				_piece_a_ressusiter=i;
				_piece_a_tuer=_pion_changement;
				_pion_changement=-1;
				break;
			}
		} 
	}
	if (_type_piece_a_placer==type_piece::roi)
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur && _ens_pieces_morte[i]->get_type()==type_piece::roi)
			{
				_piece_a_ressusiter=i;
				_piece_a_tuer=_pion_changement;
				_pion_changement=-1;
				if (_joueur)
					_roi_j1++;
				else
					_roi_j2++;
				break;
			}
		} 
	}
	if (_type_piece_a_placer==type_piece::tour)
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_morte.size(); ++i)
		{
			if (_ens_pieces_morte[i]->get_joueur()==_joueur && _ens_pieces_morte[i]->get_type()==type_piece::tour)
			{
				_piece_a_ressusiter=i;
				_piece_a_tuer=_pion_changement;
				_pion_changement=-1;
				break;
			}
		} 
	}
	
	if (_piece_a_tuer!=-1)
	{
		_type_piece_a_placer=type_piece::pion;
		_changement_screen={false,false,false,false,false};
	}
}

void Jeu::action_joueur()
{
	if (_case_locked==nullptr)
	{
		if(est_occuper_allier(_terrain.get_case_selected()))
		{
			_case_locked=_terrain.get_case_selected();
			_case_locked->change_lock();
			calcul_deplacement(_case_locked);
		}
	}
	else
	{
		if(est_occuper_allier(_terrain.get_case_selected()))
		{
			if (_case_locked==_terrain.get_case_selected())
			{
				_case_locked->change_lock();
				_case_locked=nullptr;
				for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
				{
					_ens_deplacement[i]->change_target();
				}
				_ens_deplacement.clear();
			}
			else
			{
				_case_locked->change_lock();
				for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
				{
					_ens_deplacement[i]->change_target();
				}
				_ens_deplacement.clear();
				_case_locked=_terrain.get_case_selected();
				_case_locked->change_lock();
				calcul_deplacement(_case_locked);
			}
		}
		else
		{
			if(est_occuper_ennemi(_terrain.get_case_selected()))
			{
				for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
				{
					if (_terrain.get_case_selected()==_ens_deplacement[i])
					{
						for (std::vector<std::unique_ptr<Piece>>::size_type j(0); j<_ens_pieces_vivante.size(); ++j)
						{
							if (_ens_pieces_vivante[j]->get_case_support()==_terrain.get_case_selected())
							{
								_piece_a_tuer=j;
							}
							if (_ens_pieces_vivante[j]->get_case_support()==_case_locked)
							{
								_piece_tueuse=j;
							}
						}
						
						effectue_deplacement( _case_locked , _ens_deplacement[i] );
						_action_effectue=true;
						_case_locked->change_lock();
						_case_locked=nullptr;
						for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
						{
							_ens_deplacement[i]->change_target();
						}
						_ens_deplacement.clear();
					}
				}
			}
			else
			{
				for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
				{
					if (_terrain.get_case_selected()==_ens_deplacement[i])
					{
						
						effectue_deplacement( _case_locked , _ens_deplacement[i] );
						_action_effectue=true;
						_case_locked->change_lock();
						_case_locked=nullptr;
						for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
						{
							_ens_deplacement[i]->change_target();
						}
						_ens_deplacement.clear();
					}
				}
			}
		}
		
	}
}

void Jeu::effectue_deplacement (std::shared_ptr<Case> const & depart,std::shared_ptr<Case> const & arrivee)
{
	for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		if (_ens_pieces_vivante[i]->get_case_support()==depart)
		{ 
			if (_ens_pieces_vivante[i]->get_type()==type_piece::pion)
			{
				effectue_deplacement_pion( i , arrivee );
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::tour)
			{
				effectue_deplacement_tour(i , arrivee );
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::fou)
			{
				effectue_deplacement_fou(i , arrivee );
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::reine)
			{
				effectue_deplacement_reine(i , arrivee );
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::cavalier)
			{
				effectue_deplacement_cavalier(i , arrivee );
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::roi)
			{
				effectue_deplacement_roi(i , arrivee );
			}
		}
	}
}

void Jeu::calcul_deplacement (std::shared_ptr<Case> const & ptr)
{ 
	for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		if (_ens_pieces_vivante[i]->get_case_support()==ptr)
		{ 
			if (_ens_pieces_vivante[i]->get_type()==type_piece::pion)
			{
				calcul_deplacement_pion(ptr , _ens_pieces_vivante[i]->get_a_bouger());
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::tour)
			{
				calcul_deplacement_tour(ptr);
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::fou)
			{
				calcul_deplacement_fou(ptr);
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::reine)
			{
				calcul_deplacement_reine(ptr);
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::cavalier)
			{
				calcul_deplacement_cavalier(ptr);
			}
			if (_ens_pieces_vivante[i]->get_type()==type_piece::roi)
			{
				calcul_deplacement_roi(ptr ,_ens_pieces_vivante[i]->get_a_bouger());
			}
		}
	}
	
	for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<_ens_deplacement.size(); ++i)
	{
		_ens_deplacement[i]->change_target();
	}	
}


void Jeu::place_piece()
{
	if (!est_occuper(_terrain.get_case_selected()))
	{
		if (_type_piece_a_placer==type_piece::pion)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Pion>(Pion(_terrain.get_case_selected(),_couleur_piece_a_placer )));
		}
		if (_type_piece_a_placer==type_piece::tour)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Tour>(Tour(_terrain.get_case_selected(),_couleur_piece_a_placer )));
		}
		if (_type_piece_a_placer==type_piece::fou)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Fou>(Fou(_terrain.get_case_selected(),_couleur_piece_a_placer )));
		}
		if (_type_piece_a_placer==type_piece::reine)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Reine>(Reine(_terrain.get_case_selected(),_couleur_piece_a_placer )));
		}
		if (_type_piece_a_placer==type_piece::cavalier)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Cavalier>(Cavalier(_terrain.get_case_selected(),_couleur_piece_a_placer )));
		}
		if (_type_piece_a_placer==type_piece::roi)
		{
			_ens_pieces_vivante.push_back(std::make_unique<Roi>(Roi(_terrain.get_case_selected(),_couleur_piece_a_placer )));
			if (_couleur_piece_a_placer)
				_roi_j1++;
			else
				_roi_j2++;
		}
	}
}

bool Jeu::est_occuper(std::shared_ptr<Case> const & ptr)const
{
	for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		if (_ens_pieces_vivante[i]->get_case_support()==ptr)
		{ return true; }
	}
	return false;
}

bool Jeu::est_occuper_allier(std::shared_ptr<Case> const & ptr)const
{
	for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		if (_ens_pieces_vivante[i]->get_case_support()==ptr && _ens_pieces_vivante[i]->get_joueur()==_joueur)
		{ return true; }
	}
	return false;
}

bool Jeu::est_occuper_ennemi(std::shared_ptr<Case> const & ptr)const
{
	for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		if (_ens_pieces_vivante[i]->get_case_support()==ptr && _ens_pieces_vivante[i]->get_joueur()!=_joueur)
		{ return true; }
	}
	return false;
}

void Jeu::game_exit()
{
	_etat_jeu=5;
	_compteur_exit=2000;
}

void Jeu::pieces_display()
{
	for (std::vector<std::shared_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
	{ 
		_ens_pieces_vivante[i]->display();
		

	}
}

bool Jeu::dans_deplacement(std::vector<std::shared_ptr<Case>> const & deplacements , std::shared_ptr<Case> const & ptr)const
{
	for (std::vector<std::shared_ptr<Case>>::size_type i(0); i<deplacements.size(); ++i)
	{ 
		if (deplacements[i]==ptr)
			return true;
	}	
	return false;
}

//calcul des deplacements
void Jeu::calcul_deplacement_pion( std::shared_ptr<Case> const & ptr , bool a_bouger)
{
	if (ptr->get_cases_adjacentes()[inverse(0)]!=nullptr && !est_occuper(ptr->get_cases_adjacentes()[inverse(0)]))
	{
		_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(0)]);
		if ( !a_bouger && ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]!=nullptr && !est_occuper(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]))
		{
			_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]);
		}
	}
		
	//diagonale 1
	if (ptr->get_cases_adjacentes()[inverse(0)]!=nullptr)
		if (ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]!=nullptr)
			if (est_occuper_ennemi(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]))
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]);
				
	if (ptr->get_cases_adjacentes()[inverse(0)]!=nullptr)
		if (ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]!=nullptr)
			if (est_occuper_ennemi(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]))
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]);
				
	//diagonale 2
	if (ptr->get_cases_adjacentes()[inverse(2)]!=nullptr)
		if (ptr->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]!=nullptr && !dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]))
			if (est_occuper_ennemi(ptr->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]))
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]);
				
	if (ptr->get_cases_adjacentes()[inverse(3)]!=nullptr)
		if (ptr->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]!=nullptr && !dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]))
			if (est_occuper_ennemi(ptr->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]))
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]);
}

void Jeu::effectue_deplacement_pion( unsigned int i , std::shared_ptr<Case> const & arrivee )
{	
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	
	if (est_occuper_ennemi(arrivee))
	{
		//attaque
		if (depart->get_cases_adjacentes()[inverse(0)]!=nullptr && 
			depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]==arrivee)
		{
			path.push_back(depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]);
			intermed.push_back(depart->get_coin_bords_cases()[inverse(0)]);
			
			if (depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]==nullptr)
					_pion_changement=i;
			
			_ens_pieces_vivante[i]->attaque(path , intermed);
		}
		else
		{//diagonal1
			if (depart->get_cases_adjacentes()[inverse(2)]!=nullptr &&
				depart->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]==arrivee)
			{
				path.push_back(depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(2)]);
				intermed.push_back(depart->get_coin_bords_cases()[inverse(0)]);
				
				if (depart->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(2)]->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]==nullptr)
					_pion_changement=i;
					
				_ens_pieces_vivante[i]->attaque(path , intermed);
			}
		}
		if (depart->get_cases_adjacentes()[inverse(0)]!=nullptr &&
			depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]==arrivee)
		{
			path.push_back(depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]);
			intermed.push_back(depart->get_coin_bords_cases()[inverse(2)]);
			
			if (depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]==nullptr)
				_pion_changement=i;
			
			_ens_pieces_vivante[i]->attaque(path , intermed);
		}
		else
		{//diagonal2
			if (depart->get_cases_adjacentes()[inverse(3)]!=nullptr &&_ens_pieces_vivante[i]->get_case_support()->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]==arrivee)
			{
				path.push_back(depart->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]);
				intermed.push_back(depart->get_coin_bords_cases()[inverse(2)]);
				
				if (depart->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(3)]->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]==nullptr)
					_pion_changement=i;
				
				_ens_pieces_vivante[i]->attaque(path , intermed);
			}
		}
	}
	else
	{
		//deplacement 
		
		if (_ens_pieces_vivante[i]->get_case_support()->get_cases_adjacentes()[inverse(0)]==arrivee)
		{
			path.push_back(depart->get_cases_adjacentes()[inverse(0)]);
			intermed.push_back(_ens_pieces_vivante[i]->get_case_support()->get_centre_bords_cases()[inverse(0)]);
			
			if (depart->get_cases_adjacentes()[inverse(0)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]==nullptr)
				_pion_changement=i;
			
			_ens_pieces_vivante[i]->deplacement(path , intermed);
		}
		if (depart->get_cases_adjacentes()[inverse(0)]!=nullptr && _ens_pieces_vivante[i]->get_case_support()->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]==arrivee)
		{
			path.push_back(depart->get_cases_adjacentes()[inverse(0)]);
			intermed.push_back(depart->get_centre_bords_cases()[inverse(0)]);
			path.push_back(depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]);
			intermed.push_back(depart->get_cases_adjacentes()[inverse(0)]->get_centre_bords_cases()[inverse(0)]);
			
			if (depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)] != nullptr &&
				depart->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]->get_cases_adjacentes()[inverse(0)]==nullptr)
				_pion_changement=i;
			_ens_pieces_vivante[i]->deplacement(path ,intermed);
		}
	}
	
	std::cout<<"pion changement ="<<_pion_changement<<std::endl;
}


void Jeu::calcul_deplacement_tour( std::shared_ptr<Case> const & ptr )
{
	calcul_deplacement_rectiligne (0 , ptr );
	calcul_deplacement_rectiligne (1 , ptr );
	calcul_deplacement_rectiligne (2 , ptr );
	calcul_deplacement_rectiligne (3 , ptr );
}

void Jeu::effectue_deplacement_tour( unsigned int i , std::shared_ptr<Case> const & arrivee )
{	
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	
	effectue_deplacement_rectiligne(0,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(1,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(2,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(3,depart,arrivee,path,intermed);

	if (est_occuper_ennemi(arrivee))
		_ens_pieces_vivante[i]->attaque(path,intermed);
	else
		_ens_pieces_vivante[i]->deplacement(path,intermed);
}

void Jeu::effectue_deplacement_fou( unsigned int i , std::shared_ptr<Case> const & arrivee )
{	
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	
	effectue_deplacement_diagonale(0,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_diagonale(1,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_diagonale(2,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_diagonale(3,depart,arrivee,path,intermed);
	
	if (est_occuper_ennemi(arrivee))
		_ens_pieces_vivante[i]->attaque(path,intermed);
	else
		_ens_pieces_vivante[i]->deplacement(path,intermed);
}


void Jeu::calcul_deplacement_fou( std::shared_ptr<Case> const & ptr )
{
	calcul_deplacement_diagonale(0 , ptr );
	calcul_deplacement_diagonale(1 , ptr );
	calcul_deplacement_diagonale(2 , ptr );
	calcul_deplacement_diagonale(3 , ptr );
}


void Jeu::calcul_deplacement_diagonale( int dir , std::shared_ptr<Case> const & ptr)
{
	switch (dir)
	{
		case 0 :
			if (ptr->get_cases_adjacentes()[0]!=nullptr &&
				ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]) &&
				!dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]))
					calcul_deplacement_diagonale(0, ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2] );
			}
			if (ptr->get_cases_adjacentes()[2]!=nullptr &&
				ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]) &&
				!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]))
					calcul_deplacement_diagonale(0, ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0] );
			}
		break;
		case 1 :
			if (ptr->get_cases_adjacentes()[1]!=nullptr &&
				ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]) &&
				!dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]))
					calcul_deplacement_diagonale(1, ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2] );
			}
			if (ptr->get_cases_adjacentes()[2]!=nullptr &&
				ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]) &&
				!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]))
					calcul_deplacement_diagonale(1, ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1] );
			}
		break;
		case 2 :
		{
			if (ptr->get_cases_adjacentes()[0]!=nullptr &&
				ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]) &&
				!dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]))
					calcul_deplacement_diagonale(2, ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3] );
			}
			if (ptr->get_cases_adjacentes()[3]!=nullptr &&
				ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]) &&
				!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]))
					calcul_deplacement_diagonale(2, ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0] );
			}
		}
		break;
		case 3 :
			if (ptr->get_cases_adjacentes()[1]!=nullptr &&
				ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]) &&
				!dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]))
					calcul_deplacement_diagonale(3, ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3] );
			}
			if (ptr->get_cases_adjacentes()[3]!=nullptr &&
				ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]!=nullptr &&
				!est_occuper_allier(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]) &&
				!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]))
			{
				_ens_deplacement.push_back(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]);
				
				if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]))
					calcul_deplacement_diagonale(3, ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1] );
			}
		break;		
	}
}

void Jeu::calcul_deplacement_rectiligne( int dir , std::shared_ptr<Case> const & ptr)
{
	
	if (ptr->get_cases_adjacentes()[dir]!=nullptr &&
		!est_occuper_allier(ptr->get_cases_adjacentes()[dir]) &&
		!dans_deplacement(_ens_deplacement,ptr->get_cases_adjacentes()[dir]))
	{
		_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir]);
		
		if (!est_occuper_ennemi(ptr->get_cases_adjacentes()[dir]))
			calcul_deplacement_rectiligne(dir, ptr->get_cases_adjacentes()[dir] );
	}
}


bool Jeu::effectue_deplacement_diagonale( int dir , std::shared_ptr<Case> const & ptr ,  std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed )
{
	switch (dir)
	{
		case 0 :
		{
			if (ptr->get_cases_adjacentes()[0]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]) )
				{
					if (ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]==arrivee)
					{ 
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[0]);
						return true;
					}
					else
					{
						path.push_back(ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]);
						if (effectue_deplacement_diagonale(0,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[2]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[0]);
							return true;				
						}
						path.pop_back();
					}
				}
			}	
			
			if (ptr->get_cases_adjacentes()[2]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]))
				{
					if (ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[0]);
						return true;
					}
					else
					{
						path.push_back(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]);
						if (effectue_deplacement_diagonale(0,ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[0]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[0]);
							return true;				
						}
						path.pop_back();
					}
				}
			}
			
			return false;	
		}
		break;
		case 1 :
		{
			if (ptr->get_cases_adjacentes()[1]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]))
				{
					if (ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[3]);
						return true;
					}
					else
					{
						path.push_back(ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]);
						if (effectue_deplacement_diagonale(1,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[2]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[3]);
							return true;				
						}
						path.pop_back();
					}
				}
			}	
			
			if (ptr->get_cases_adjacentes()[2]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]))
				{
					if (ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[3]);
						return true;
					}
					else
					{
						path.push_back(ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]);
						if (effectue_deplacement_diagonale(1,ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[2]->get_cases_adjacentes()[1]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[3]);
							return true;				
						}
						path.pop_back();
					}
				}
			}
			
			return false;	
		}
		break;
		case 2 :
		{
			if (ptr->get_cases_adjacentes()[0]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]))
				{
					if (ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[2]);
						return true;
					}
					else
					{
						path.insert(path.begin(),ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]);
						if (effectue_deplacement_diagonale(2,ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[0]->get_cases_adjacentes()[3]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[2]);
							return true;				
						}
						path.pop_back();
					}
				}
			}	
			
			if (ptr->get_cases_adjacentes()[3]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]))
				{
					if (ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[2]);
						return true;
					}
					else
					{
						path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]);
						if (effectue_deplacement_diagonale(2,ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[0]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[2]);
							return true;				
						}
						path.pop_back();
					}
				}
			}
			
			return false;	
		}
		break;
		case 3 :
		{
			if (ptr->get_cases_adjacentes()[1]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]))
				{
					if (ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[1]);
						return true;
					}
					else
					{
						path.insert(path.begin(),ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]);
						if (effectue_deplacement_diagonale(3,ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[1]->get_cases_adjacentes()[3]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[1]);
							return true;				
						}
						path.pop_back();
					}
				}
			}	
			
			if (ptr->get_cases_adjacentes()[3]!=nullptr)
			{
				if (ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]!=nullptr && !dans_deplacement(path,ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]))
				{
					if (ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]==arrivee)
					{
						path.clear();
						path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]);
						intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[1]);
						return true;
					}
					else
					{
						path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]);
						if (effectue_deplacement_diagonale(3,ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1] , arrivee , path , intermed))
						{
							path.insert(path.begin(),ptr->get_cases_adjacentes()[3]->get_cases_adjacentes()[1]);
							intermed.insert(intermed.begin(),ptr->get_coin_bords_cases()[1]);
							return true;				
						}
						path.pop_back();
					}
				}
			}
						
			return false;	
		}
		break;	
	}
	return false;
}

bool Jeu::effectue_deplacement_rectiligne( int dir , std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed )
{
	if (ptr->get_cases_adjacentes()[dir]==nullptr || dans_deplacement(path,ptr->get_cases_adjacentes()[dir]) )
	{
		path.clear();
	 	return false;
	}
	if (ptr->get_cases_adjacentes()[dir]==arrivee)
	{
		path.clear();
		path.insert(path.begin(),ptr->get_cases_adjacentes()[dir]);
		intermed.insert(intermed.begin(),ptr->get_centre_bords_cases()[dir]);
		return true;
	}
	path.push_back(ptr->get_cases_adjacentes()[dir]);
	if (effectue_deplacement_rectiligne(dir,ptr->get_cases_adjacentes()[dir] , arrivee , path, intermed))
	{
		path.insert(path.begin(),ptr->get_cases_adjacentes()[dir]);
		intermed.insert(intermed.begin(),ptr->get_centre_bords_cases()[dir]);
		return true;				
	}
	else
	{
		return false;	
	}
}


void Jeu::calcul_deplacement_reine( std::shared_ptr<Case> const & ptr )
{
	calcul_deplacement_rectiligne (0 , ptr );
	calcul_deplacement_rectiligne (1 , ptr );
	calcul_deplacement_rectiligne (2 , ptr );
	calcul_deplacement_rectiligne (3 , ptr );
	calcul_deplacement_diagonale ( 0 , ptr );
	calcul_deplacement_diagonale ( 1 , ptr );
	calcul_deplacement_diagonale ( 2 , ptr );
	calcul_deplacement_diagonale ( 3 , ptr );
}


void Jeu::effectue_deplacement_reine( unsigned int i , std::shared_ptr<Case> const & arrivee )
{	
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	
	effectue_deplacement_diagonale(0,depart,arrivee,path,intermed);
	
	effectue_deplacement_diagonale(1,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_diagonale(2,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_diagonale(3,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(0,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(1,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(2,depart,arrivee,path,intermed);
	if (path.size()==0)
		effectue_deplacement_rectiligne(3,depart,arrivee,path,intermed);
	
	if (est_occuper_ennemi(arrivee))
		_ens_pieces_vivante[i]->attaque(path,intermed);
	else
		_ens_pieces_vivante[i]->deplacement(path,intermed);
}

void Jeu::calcul_deplacement_cavalier( std::shared_ptr<Case> const & ptr )
{
	deplacement_cavalier ( 0 , 2 , ptr);
	deplacement_cavalier ( 2 , 0 , ptr);
	
	deplacement_cavalier ( 0 , 3 , ptr);
	deplacement_cavalier ( 3 , 0 , ptr);
	
	deplacement_cavalier ( 1 , 2 , ptr);
	deplacement_cavalier ( 2 , 1 , ptr);
	
	deplacement_cavalier ( 1 , 3 , ptr);
	deplacement_cavalier ( 3 , 1 , ptr);			
}

void Jeu::effectue_deplacement_cavalier( unsigned int i , std::shared_ptr<Case> const & arrivee )
{
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	
	mouvement_cavalier ( 0 , 2 , 0, depart, arrivee, path , intermed);
	mouvement_cavalier ( 2 , 0 , 0, depart, arrivee, path , intermed);
	
	mouvement_cavalier ( 0 , 3 , 2, depart, arrivee, path , intermed);
	mouvement_cavalier ( 3 , 0 , 2, depart, arrivee, path , intermed);
	
	mouvement_cavalier ( 1 , 2 , 3, depart, arrivee, path , intermed);
	mouvement_cavalier ( 2 , 1 , 3, depart, arrivee, path , intermed);
	
	mouvement_cavalier ( 1 , 3 , 1, depart, arrivee, path , intermed);
	mouvement_cavalier ( 3 , 1 , 1, depart, arrivee, path , intermed);
	
	if (est_occuper_ennemi(arrivee))
		_ens_pieces_vivante[i]->attaque(path,intermed);
	else
		_ens_pieces_vivante[i]->deplacement(path,intermed);
}	

void Jeu::mouvement_cavalier( int dir , int dir2 , int coin , std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed  )
{
	if (ptr->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]==arrivee)
	{
		path.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]);
		intermed.push_back(ptr->get_coin_bords_cases()[coin]);
		path.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]);
		intermed.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_centre_bords_cases()[dir]);
	}
	else
	{
		if (ptr->get_cases_adjacentes()[dir2]!=nullptr &&
			ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]!=nullptr &&
			ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]!=nullptr &&
			ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]==arrivee)
		{
			path.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]);
			intermed.push_back(ptr->get_coin_bords_cases()[coin]);
			path.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]);
			intermed.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_centre_bords_cases()[dir]);
		}
	}
}

void Jeu::deplacement_cavalier( int dir , int dir2 , std::shared_ptr<Case> const & ptr )
{
	if (ptr->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]!=nullptr &&
		!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]) &&
		!est_occuper_allier(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]) )
	_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]);
	
	if (ptr->get_cases_adjacentes()[dir2]!=nullptr &&
		ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]!=nullptr &&
		!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]) &&
		!est_occuper_allier(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]) )
	_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir]);
	
}

void Jeu::calcul_deplacement_roi(std::shared_ptr<Case> const & ptr , bool a_bouger)
{
	deplacement_roi(0,2,ptr);
	deplacement_roi(2,1,ptr);
	deplacement_roi(1,3,ptr);
	deplacement_roi(3,0,ptr);
	if (!a_bouger)
	{
		trouve_rock(0,ptr);
		trouve_rock(1,ptr);
		trouve_rock(2,ptr);
		trouve_rock(3,ptr);
	}		
}


void Jeu::deplacement_roi( int dir , int dir2 , std::shared_ptr<Case> const & ptr )
{
	if (ptr->get_cases_adjacentes()[dir]!=nullptr && !est_occuper_allier(ptr->get_cases_adjacentes()[dir]) && !dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[dir]))
		_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir]);
	
	if (ptr->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]!=nullptr &&
		!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]) &&
		!est_occuper_allier(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]) )
	_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]);
	
	if (ptr->get_cases_adjacentes()[dir2]!=nullptr &&
		ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]!=nullptr &&
		!dans_deplacement(_ens_deplacement , ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]) &&
		!est_occuper_allier(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]) )
	_ens_deplacement.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]);
	
}

void Jeu::trouve_rock (int dir , std::shared_ptr<Case> const & ptr)
{
	std::vector<std::shared_ptr<Case>> record;
	std::shared_ptr<Case> sauv_ptr=ptr;
	
	while (sauv_ptr->get_cases_adjacentes()[dir]!=nullptr &&
			!est_occuper(sauv_ptr->get_cases_adjacentes()[dir])&&
			!dans_deplacement(record,sauv_ptr->get_cases_adjacentes()[dir]) )
	{
		record.push_back(sauv_ptr->get_cases_adjacentes()[dir]);
		sauv_ptr=sauv_ptr->get_cases_adjacentes()[dir];
	}
	std::cout<<est_occuper_allier(sauv_ptr->get_cases_adjacentes()[dir])<<std::endl;
	if (est_occuper_allier(sauv_ptr->get_cases_adjacentes()[dir]) && !dans_deplacement(_ens_deplacement , sauv_ptr))		
	{
		for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
		{
			if (_ens_pieces_vivante[i]->get_case_support()==sauv_ptr->get_cases_adjacentes()[dir] && _ens_pieces_vivante[i]->get_type()==type_piece::tour && !_ens_pieces_vivante[i]->get_a_bouger() )
			{
				_ens_deplacement.push_back(sauv_ptr);
			}
		}
	}
	
}


void Jeu::effectue_deplacement_roi( unsigned int i , std::shared_ptr<Case> const & arrivee )
{	
	std::shared_ptr<Case> depart=_ens_pieces_vivante[i]->get_case_support();
	std::vector<std::shared_ptr<Case>> path;
	std::vector<Point> intermed;
	
	mouvement_roi(0,2,0,depart ,arrivee, path, intermed);
	mouvement_roi(2,1,3,depart ,arrivee, path, intermed);
	mouvement_roi(1,3,1,depart ,arrivee, path, intermed);
	mouvement_roi(3,0,2,depart ,arrivee, path, intermed);	
		
	if (path.size()>0)
	{
		if (est_occuper_ennemi(arrivee))
			_ens_pieces_vivante[i]->attaque(path,intermed);
		else
			_ens_pieces_vivante[i]->deplacement(path,intermed);
	}
	else
	{
		_roi_rock=i;
		repere_tour_rock(0,depart,arrivee, path , intermed);
		repere_tour_rock(1,depart,arrivee, path , intermed);	
		repere_tour_rock(2,depart,arrivee, path , intermed);	
		repere_tour_rock(3,depart,arrivee, path , intermed);
		
		_ens_pieces_vivante[i]->deplacement(path,intermed);	
	}	
}

void Jeu::repere_tour_rock( int dir, std::shared_ptr<Case> const & depart , std::shared_ptr<Case> const & arrivee ,std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed)
{
	std::vector<std::shared_ptr<Case>> record;
	if (path.size()==0)
	{
		std::shared_ptr<Case> sauv_ptr=depart;

		while (sauv_ptr->get_cases_adjacentes()[dir]!=nullptr &&
				!est_occuper(sauv_ptr->get_cases_adjacentes()[dir]) &&
				!dans_deplacement(record,sauv_ptr->get_cases_adjacentes()[dir]))
		{
			path.push_back(sauv_ptr->get_cases_adjacentes()[dir]);
			record.push_back(sauv_ptr->get_cases_adjacentes()[dir]);
			intermed.push_back(sauv_ptr->get_centre_bords_cases()[dir]);
			sauv_ptr=sauv_ptr->get_cases_adjacentes()[dir];
		}
		
		if (est_occuper_allier(sauv_ptr->get_cases_adjacentes()[dir]) && sauv_ptr==arrivee)		
		{
			for (std::vector<std::unique_ptr<Piece>>::size_type i(0); i<_ens_pieces_vivante.size(); ++i)
			{
				if (_ens_pieces_vivante[i]->get_case_support()==sauv_ptr->get_cases_adjacentes()[dir] && _ens_pieces_vivante[i]->get_type()==type_piece::tour && !_ens_pieces_vivante[i]->get_a_bouger() )
				{
					_tour_rock=i;
				}
				
			}
		}
		if (_tour_rock==-1)
		{
			path.clear();
			intermed.clear();
		}
	}
}

void Jeu::mouvement_roi( int dir , int dir2 , int coin, std::shared_ptr<Case> const & ptr, std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed  )
{
	if (ptr->get_cases_adjacentes()[dir]!=nullptr && !est_occuper_allier(ptr->get_cases_adjacentes()[dir]) && ptr->get_cases_adjacentes()[dir]==arrivee)
	{
		path.push_back(ptr->get_cases_adjacentes()[dir]);
		intermed.push_back(ptr->get_centre_bords_cases()[dir]);
	}
	
	if (ptr->get_cases_adjacentes()[dir]!=nullptr &&
		ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]==arrivee &&
		!dans_deplacement(path,ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]))
	{
		path.push_back(ptr->get_cases_adjacentes()[dir]->get_cases_adjacentes()[dir2]);
		intermed.push_back(ptr->get_coin_bords_cases()[coin]);
	}
	
	if (ptr->get_cases_adjacentes()[dir2]!=nullptr &&
		ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]==arrivee &&
		!dans_deplacement(path,ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]))
	{
		path.push_back(ptr->get_cases_adjacentes()[dir2]->get_cases_adjacentes()[dir]);
		intermed.push_back(ptr->get_coin_bords_cases()[coin]);
	}
}
