#include "operation_base.hh"

void translation (GLfloat x,GLfloat y,GLfloat z)
{
	GLfloat transalt[16]={	1,0,0,0,
							0,1,0,0,
							0,0,1,0,
							x,y,z,1};
						
	glMultMatrixf(transalt);					
}

void aggrandissement (GLfloat ax,GLfloat ay,GLfloat az)
{
	GLfloat agr[16]={	ax,0,0,0,
						0,ay,0,0,
						0,0,az,0,
						0,0,0,1};
						
	glMultMatrixf(agr);					
}

void rotation (GLfloat angx,GLfloat angy,GLfloat angz)
{
	angx = angx / 180.0 * M_PI;
	angy = angy / 180.0 * M_PI;
	angz = angz / 180.0 * M_PI;
	
	GLfloat surx[16]={	1,0,0,0,
						0,(GLfloat)cos(angx),(GLfloat)sin(angx),0,
						0,(GLfloat)-sin(angx),(GLfloat)cos(angx),0,
						0,0,0,1};
						
	GLfloat sury[16]={	(GLfloat)cos(angy),0,(GLfloat)-sin(angy),0,
						0,1,0,0,
						(GLfloat)sin(angy),0,(GLfloat)cos(angy),0,
						0,0,0,1};
						
	GLfloat surz[16]={	(GLfloat)cos(angz),(GLfloat)sin(angz),0,0,
						(GLfloat)-sin(angz),(GLfloat)cos(angz),0,0,
						0,0,1,0,
						0,0,0,1};
						
	glMultMatrixf(surx);
	glMultMatrixf(sury);
	glMultMatrixf(surz);					
}

void cisallementsur_yz (GLfloat y,GLfloat z)
{						
	GLfloat ciyz[16]={	1,y,z,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,1};
						
	glMultMatrixf(ciyz);			
}

void cisallementsur_xz (GLfloat x,GLfloat z)
{						
	GLfloat cixz[16]={	1,0,0,0,
						x,1,z,0,
						0,0,1,0,
						0,0,0,1};
						
	glMultMatrixf(cixz);			
}

void cisallementsur_xy (GLfloat x,GLfloat y)
{						
	GLfloat cixy[16]={	1,0,0,0,
						0,1,0,0,
						x,y,1,0,
						0,0,0,1};
						
	glMultMatrixf(cixy);			
}

void eloignement (GLfloat t)
{
	GLfloat el[16]={	1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						0,0,0,t};
						
	glMultMatrixf(el);					
	
}

// NOTES
/*GLfloat nom[16]={	aggrandissement sur x,0,0,0,
							0,aggrandissement sur z,0,0,
							0,0,aggrandissement sur t,0,
							0,0,0,(observateur)t};*/
							
							
	 /*GLfloat nom[16]={	x,0,0,0,
							0,y,0,0,
							0,0,z,0,
							translation sur x,translation sur y,translation sur z,(observateur)t};*/
							
							
	/*GLfloat nom[16]={		x,0,0,0,
							0,y,0,0,
							0,0,z,0,
							0,0,0,t};*/

void translationTR (GLfloat taille_base , GLfloat largeurx  , GLfloat longueury, GLfloat hauteurz  )
{
	translation(taille_base*largeurx,taille_base*longueury,taille_base*hauteurz);
}


bool activer_perspective=false;

GLvoid perspective() 
{
	if (activer_perspective)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool activer_blend=true;

GLvoid blend() 
{
	if (activer_blend) {
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST); 
	}
	else 
	{
		glEnable(GL_BLEND);	
		glDisable(GL_DEPTH_TEST);
	}
}

bool activer_axes=false;
GLvoid aff_axes()
{
	if (activer_axes) 
	{
		axes();
	}
}

