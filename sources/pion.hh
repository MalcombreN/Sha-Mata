#include "piece.hh"

class Pion : public Piece
{
private:
	GLfloat pion_angle_doigt;
	GLfloat pion_angle_main;
	GLfloat pion_angle_fix ;
	GLfloat pion_angle_bras ;
	GLfloat pion_angle_bras2 ;
	GLfloat pion_angle_bras_retour;
	GLfloat pion_angle_bras_retour_bis ;
	GLfloat pion_angle_bras_retour_fin ;
	GLfloat pion_angle_corps;
	GLfloat pion_angle_corps_retour ;
	GLfloat pion_angle_genoux;
	GLfloat pion_angle_genoux_retour;
	GLfloat pion_distance_corps;
	GLfloat pion_distance_corps_retour;

	GLboolean action_pion;
	GLboolean fin_phase1 ;
	GLboolean fin_phase2 ;
	GLboolean fin_phase3 ;
	GLboolean fin_phase4 ;
	GLboolean fin_phase5 ;
	GLboolean action_pion_fin ;

	static GLuint _piece_pion_lance_tete;
	static GLuint _piece_pion_lance;
	static GLuint _piece_pion_pied;
	static GLuint _piece_pion_jambe1;
	static GLuint _piece_pion_jambe2;
	static GLuint _piece_pion_corps;
	static GLuint _piece_pion_tete;
	static GLuint _piece_pion_epaules;
	static GLuint _piece_pion_main;
	

	void affiche_piece()override;	
	void animation() override;
	
	void Pion_DrawBras();
	void Pion_DrawBras_action();
	void DrawPion();

	static void Pion_DrawLanceTete();
	static void Pion_DrawLance();
	static void Pion_DrawPied();
	static void Pion_DrawJambre(float degree);
	static void Pion_DrawCorps();
	static void Pion_DrawTete();
	static void Pion_DrawEpaule();
	static void Pion_DrawDoigt(GLfloat a);
	static void Pion_DrawMain(GLfloat a);
	
	
	
	
		
public:
	Pion(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Pion()=default;
	
	static void load_piece();
};
