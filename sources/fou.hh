#include "piece.hh"



class Fou : public Piece
{
private:
	bool action_fou;
	GLboolean fin_phase1_fou;
	GLboolean fin_phase2_fou;
	GLboolean fin_phase3_fou;
	GLboolean fin_phase4_fou;
	GLboolean fin_phase5_fou;
	GLboolean fin_phase6_fou;
	GLboolean fin_phase7_fou;
	GLboolean fin_action_fou;
	GLfloat fou_angle_epaule;
	GLfloat fou_angle_epaule_bis;
	GLfloat fou_angle_epaule_retour;
	GLfloat fou_angle_epaule_bis_retour;

	GLfloat fou_angle_avantbras;
	GLfloat fou_angle_avantbras_retour;
	GLfloat fou_angle_main1;
	GLfloat fou_angle_main1_retour;
	GLfloat fou_angle_poignet;
	GLfloat fou_angle_poignet_retour;
	GLfloat fou_angle_main2;
	GLfloat fou_angle_main2_retour;

	GLfloat fou_angle_assassiner_epaule;
	GLfloat fou_angle_assassiner_avantbras;
	GLfloat fou_angle_assassiner_avantbras_bis;
	GLfloat fou_angle_assassiner_avantbras_bis_retour;

	GLfloat fou_angle_assassiner_retour_avantbras;
	GLfloat fou_angle_assassiner_retour_epaule;
	GLfloat fou_distance_corps;
	GLfloat fou_distance_corps_retour;
	GLfloat fou_angle_corps;
	GLfloat fou_angle_corps_retour;

	GLfloat fou_distance_jambre;
	GLfloat fou_distance_jambre_retour;
	GLfloat fou_distance_avancer;
	GLfloat fou_distance_avancer_retour;
	GLfloat fou_angle_genoux;
	GLfloat fou_angle_genoux_retour;
	GLfloat fou_angle_cuisse;
	GLfloat fou_angle_cuisse_retour;

	GLfloat fou_monte_bras;
	GLfloat fou_monte_bras_retour;
	
	void affiche_piece()override;	
	void animation() override;
	
	static void Fou_DrawDague();
	static void Fou_DrawPied() ;
	static void Fou_DrawJambre(float degree) ;
	void Fou_DrawJambre_action(float degree);
	static void Fou_DrawCorps();
	static void Fou_DrawFouChapeau();
	static void Fou_DrawTete(); 
	void Fou_DrawBrasGauche();
	void Fou_DrawBrasDroite();
	void DrawFou();
	
	static GLuint _piece_fou_dague;
	static GLuint _piece_fou_pied;
	static GLuint _piece_fou_jambe;
	static GLuint _piece_fou_corps;
	static GLuint _piece_fou_chapeau;
	static GLuint _piece_fou_tete;
	
public:
	Fou(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Fou()=default;
	static void load_piece();
	
};
