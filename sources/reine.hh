#include "piece.hh"

class Reine : public Piece
{
private:

	void affiche_piece()override;	
	void animation() override;
	
	GLboolean action_reine;
	bool fin_action_dame;
	GLboolean fin_phase1_dame;
	GLboolean fin_phase2_dame;
	GLboolean fin_phase3_dame;
	GLboolean fin_phase4_dame ;
	GLfloat reine_angle_fix;
	GLfloat reine_angle_avantbras;
	GLfloat reine_angle_avantbras_retour;
	GLfloat reine_angle_bras;
	GLfloat reine_angle_bras_retour;
	GLfloat reine_angle_bras_etendu;
	GLfloat reine_angle_bras_etendu_retour;
	GLfloat reine_angle_bras_lever;
	GLfloat reine_angle_bras_lever_retour;
	GLfloat reine_angle_attraper;
	GLfloat reine_angle_attraper_retour;
	GLfloat reine_angle_tirer;
	GLfloat reine_angle_lacher;
	GLfloat reine_angle_lacher_retour;
	GLfloat reine_angle_avantbras_retour_gauche;
	GLfloat reine_angle_corps;
	GLfloat reine_angle_corps_retour;
	
	static GLuint _piece_reine_couronne;
	static GLuint _piece_reine_tete;
	static GLuint _piece_reine_arc;
	static GLuint _piece_reine_main;
	static GLuint _piece_reine_jambe1;
	static GLuint _piece_reine_jambe2;
	static GLuint _piece_reine_corps;
	static GLuint _piece_reine_robe;

public:
	Reine(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Reine()=default;
	
	void affichage_attaque();

	static void load_piece();	
	static void Reine_DrawArc();
	static void Reine_DrawCorps();
	static void Reine_DrawCouronne_reine(float a, float b);
	static void Reine_DrawJambre(float a);
	static void Reine_DrawRobe(float n);
	static void Reine_DrawTete();
	void Reine_DrawBrasDroite();
	void Reine_DrawBrasGauche();
	void DrawReine();


};
