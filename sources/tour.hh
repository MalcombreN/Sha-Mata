#include "piece.hh"

class Tour : public Piece
{
private:
	GLboolean action_tour; 
	GLboolean fin_phase1_tour;
	GLboolean fin_phase2_tour;
	GLboolean fin_phase3_tour;
	GLboolean fin_phase4_tour;
	GLboolean fin_action_tour;
	GLfloat tour_angle_canon1;
	GLfloat tour_angle_canon_retour;
	GLdouble tour_recul_canon;
	GLdouble tour_recul_canon_retour;
	GLdouble tour_distance_anneau;
	GLdouble tour_epaisseur_anneau;
	GLfloat tour_compt;

	
	void affiche_piece()override;	
	void animation() override;
	
	static void Tour_DrawAnneau(float rc, int numc, float rt, int numt);
	static void Tour_DrawTourCorps();
	void DrawTour();
	
	static GLuint _piece_tour_corps;
	
	
public:
	Tour(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Tour()=default;
	
	static void load_piece();
};
