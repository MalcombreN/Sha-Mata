#include "piece.hh"

class Roi : public Piece
{
private:
	GLfloat roi_angle_doigt;  
	GLfloat roi_angle_doigt_retour;
	GLfloat roi_angle_avantbras;
	GLfloat roi_angle_avantbras_retour;
	GLfloat roi_angle_fix;
	GLfloat roi_angle_lever_epee;
	GLfloat roi_angle_lever_epee_retour;
	GLfloat roi_lever_bras;
	GLfloat roi_lever_bras_retour;
	GLfloat roi_attaquer_avantbras_v;
	GLfloat roi_attaquer_avantbras_v_retour;
	GLfloat roi_attaquer_bras;
	GLfloat roi_attaquer_bras_retour;
	GLboolean action_roi;
	GLboolean fin_phase1_roi;
	GLboolean fin_phase2_roi;
	GLboolean fin_phase3_roi;
	GLboolean fin_phase4_roi;
	GLboolean fin_phase5_roi;
	GLboolean fin_phase6_roi;
	GLboolean fin_phase7_roi;
	GLboolean fin_phase8_roi;
	GLboolean fin_phase9_roi;
	GLboolean fin_action_roi;
	
	static GLuint	_piece_roi_epee;
	static GLuint	_piece_roi_cape;
	static GLuint	_piece_roi_couronne;
	static GLuint	_piece_roi_tete;
	static GLuint	_piece_roi_epaule;
	static GLuint	_piece_roi_jambe1;
	static GLuint	_piece_roi_jambe2;
	static GLuint	_piece_roi_corps;
	static GLuint	_piece_roi_bras;
	
	
	static void	Roi_DrawEpee();
	static void	Roi_DrawCape();
	static void	Roi_DrawCouronne_roi(float a,float b);
	static void	Roi_DrawTete(); 
	static void	Roi_DrawEpaule();
	static void	Roi_DrawJambre(float a);
	static void	Roi_DrawCorps();	
	static void	Roi_DrawBras();	
	
	void	Roi_DrawBras_action();
	void 	DrawRoi();	
	
	void affiche_piece()override;	
	void animation() override;
public:
	Roi(std::shared_ptr<Case> const & case_support ,bool joueur);
	~Roi()=default;
	static void load_piece();
	
};
