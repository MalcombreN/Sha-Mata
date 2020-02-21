#include "piece.hh"

class Cavalier : public Piece
{
private:
	float _hauteur;
	bool _lock_bouger;
	
	void affiche_piece()override;	
	void animation() override;
	void affichage_attaque() override;
	void affichage_mouvement() override;
	
	GLfloat cavalier_angle_cheval;
	GLfloat cavalier_angle_cheval_retour;
	GLfloat cavalier_angle_corps;
	GLfloat cavalier_angle_corps_retour;
	GLfloat cavalier_attaque;
	GLfloat cavalier_attaque_retour;
	GLfloat cavalier_angle_pied_cheval;
	GLfloat cavalier_angle_pied_cheval_retour; 
	GLboolean action_cavaliers;
	GLboolean fin_phase1_cavaliers;
	GLboolean fin_phase2_cavaliers;
	GLboolean fin_phase3_cavaliers;
	GLboolean fin_phase4_cavaliers;
	GLboolean fin_action_cavaliers;

	void Cavalier_DrawBrasDroite();
	static void Cavalier_DrawBrasGauche();
	void Cavalier_DrawCheval();
	static void Cavalier_DrawChevalCorps();
	static void Cavalier_DrawChevalPied();
	static void Cavalier_DrawChevalTete();
	static void Cavalier_DrawCorps();
	static void Cavalier_DrawEpaule();
	static void Cavalier_DrawJambre(float degree);
	static void Cavalier_DrawLance();
	static void Cavalier_DrawTete();
	void DrawCavaliers();
	
	static GLuint _piece_cavalier_chevalPied;
	static GLuint _piece_cavalier_chevalCorps;
	static GLuint _piece_cavalier_chevalTete;
	static GLuint _piece_cavalier_Jambe1;
	static GLuint _piece_cavalier_Jambe2;
	static GLuint _piece_cavalier_corps;
	static GLuint _piece_cavalier_epaule;
	static GLuint _piece_cavalier_brasGauche;
	static GLuint _piece_cavalier_lance;
	static GLuint _piece_cavalier_tete;
	
	
public:
	Cavalier(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Cavalier()=default;
	static void load_piece();
	
};
