
#include <fstream>
#include <regex>


#include "terrain.hh"
#include "piece.hh"
#include "pion.hh"
#include "tour.hh"
#include "fou.hh"
#include "reine.hh"
#include "cavalier.hh"
#include "roi.hh"

extern GLfloat look;
extern GLfloat lookh;
extern GLfloat lookeloi;  
extern GLdouble Coef_screen_size; 
extern int largeur;
extern int hauteur;


class Jeu
{
private:
	unsigned int _etat_jeu;
	bool _joueur;
	Terrain _terrain;
	std::vector<std::unique_ptr<Piece>> _ens_pieces_vivante;
	std::vector<std::unique_ptr<Piece>> _ens_pieces_morte;
	
	bool _couleur_piece_a_placer;
	type_piece _type_piece_a_placer;
	
	std::shared_ptr<Case> _case_locked;
	std::vector<std::shared_ptr<Case>> _ens_deplacement;
	
	bool _action_effectue;
	unsigned int _compteur_tour;
	unsigned int _compteur_exit;
	
	int _piece_a_tuer;
	int _piece_tueuse;
	
	unsigned int _roi_j1;
	unsigned int _roi_j2;
	int _display_roi_screen;
	
	int _roi_rock;
	int _tour_rock;
	bool _rock_done;
	int _pion_changement;
	
	std::array<bool,5> _changement_screen;
	int _piece_a_ressusiter;
	
	int _angle_x;
	int _angle_z;
	int _eloignement;
	
	bool _useclic;

//pour savoir si on a déjà chargé les liste d'affichage
	bool _pose_piece_loader;
	bool _rois_loader;
	bool _pieces_loader;
	bool _winner_loader;
	bool _erreur_loader;
	bool _sauv_loader;
	bool _sauvgarder_oui_non;
	int _echec_sauvgarde;
	
//liste d'affichage
	GLuint _affichage_entering_screen;
	GLuint _couleur_blanche;
	GLuint _couleur_noir;
	GLuint _screen_pion;
	GLuint _screen_roi;
	GLuint _screen_reine;
	GLuint _screen_fou;
	GLuint _screen_tour;
	GLuint _screen_cavalier;
	GLuint _screen_indication;
	GLuint _screen_roi_erreur;	
	GLuint _screen_j1_win;
	GLuint _screen_j2_win;
	GLuint _screen_erreur;
	GLuint _screen_sauv;
	GLuint _screen_sauv_oui;
	GLuint _screen_sauv_non;
	GLuint _screen_sauv_echec;
	
	//chargement des listes d'affichages
	void load_pose_piece_screen();
	void load_pieces();
	void load_erreur_screen();
	void load_rois_screen();
	void load_win_screen();
	void load_sauv_screen();
	
	int inverse(int x);
	void place_piece();
	void action_joueur();
	void kill();
	void rock();
	void changement();
	void validation_changement();
	void ressussite();
	void affiche_piece_screen();	
	void pose_set_pieces(int num_plateau);
	void sauvegarde();
	void restore_sauvegarde();
	
	bool est_occuper(std::shared_ptr<Case> const & ptr)const;
	bool est_occuper_allier(std::shared_ptr<Case> const & ptr)const;
	bool est_occuper_ennemi(std::shared_ptr<Case> const & ptr)const;
	
	bool dans_deplacement(std::vector<std::shared_ptr<Case>> const & deplacements ,std::shared_ptr<Case> const & ptr)const;
	
	void calcul_deplacement(std::shared_ptr<Case> const & ptr);
	void calcul_deplacement_pion(std::shared_ptr<Case> const & ptr , bool a_bouger);
	void calcul_deplacement_tour(std::shared_ptr<Case> const & ptr);
	void calcul_deplacement_fou(std::shared_ptr<Case> const & ptr);
	void calcul_deplacement_reine( std::shared_ptr<Case> const & ptr );
	void calcul_deplacement_cavalier( std::shared_ptr<Case> const & ptr );
	void deplacement_cavalier( int dir , int dir2 , std::shared_ptr<Case> const & ptr );
	void calcul_deplacement_roi(std::shared_ptr<Case> const & ptr, bool a_bouger);
	void deplacement_roi( int dir , int dir2 , std::shared_ptr<Case> const & ptr );
	void trouve_rock (int dir , std::shared_ptr<Case> const & ptr);
	
	void calcul_deplacement_diagonale( int dir , std::shared_ptr<Case> const & ptr);
	void calcul_deplacement_rectiligne( int dir , std::shared_ptr<Case> const & ptr);
	bool effectue_deplacement_diagonale( int dir , std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed );
	bool effectue_deplacement_rectiligne( int dir , std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed );
	
	
	void effectue_deplacement (std::shared_ptr<Case> const & depart,std::shared_ptr<Case> const & arrivee);
	void effectue_deplacement_pion(unsigned int i ,std::shared_ptr<Case> const & arrivee );
	void effectue_deplacement_tour(unsigned int i ,std::shared_ptr<Case> const & arrivee );
	void effectue_deplacement_fou(unsigned int i ,std::shared_ptr<Case> const & arrivee );
	void effectue_deplacement_reine( unsigned int i , std::shared_ptr<Case> const & arrivee );
	void effectue_deplacement_cavalier( unsigned int i , std::shared_ptr<Case> const & arrivee );
	void mouvement_cavalier( int dir , int dir2 , int coin , std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed  );
	void effectue_deplacement_roi( unsigned int i , std::shared_ptr<Case> const & arrivee );
	void mouvement_roi( int dir , int dir2 , int coin, std::shared_ptr<Case> const & ptr , std::shared_ptr<Case> const & arrivee , std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed  );	
	void repere_tour_rock( int dir, std::shared_ptr<Case> const & depart , std::shared_ptr<Case> const & arrivee,std::vector<std::shared_ptr<Case>> & path , std::vector<Point> & intermed);

	
	void change_joueur();
	void pieces_display();
public:
	Jeu();
	~Jeu()=default;

	
	void gere_menu(int value);
	int get_etat_jeu()const;
	void load_entering_screen();
	void clic(int x,int y);
	void select_autre_case(unsigned int x);
	void game_exit();
	void lock_la_case();
	void reset_cam();
	
	void cam_verticale(int val);
	void cam_horizontale(int val);
	
	void cam_eloignement();
	void cam_rapprochement();
	
	void display();
};
