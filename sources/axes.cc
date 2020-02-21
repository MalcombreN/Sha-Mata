// gcc axes.c -c 

#include "axes.hh"

void axes() 
{
	glPushMatrix();
	{
		GLfloat epaisseur_segment = 0.05f;
		GLfloat taille_fleche = 1.0f;
		GLfloat taille_cone = 0.2f;
		GLfloat taille_reelle_segment = (taille_fleche+(epaisseur_segment/2)) - taille_cone;
		GLfloat position_segment = (taille_fleche - taille_cone) - taille_reelle_segment/2;
		GLfloat position_cone = taille_fleche - taille_cone;
		// Axe des X
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(position_segment, 0.0f, 0.0f); 
		glScalef(taille_reelle_segment, epaisseur_segment, epaisseur_segment); 
		glutSolidCube(1.0);
		glPopMatrix();

		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(position_cone, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		//    glScalef(0.1f, 0.1f, 0.1f);
		glutSolidCone(0.1f, taille_cone, 50, 5);
		glPopMatrix();

		// Axe des Y
		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0f, position_segment, 0.0f);
		glScalef(epaisseur_segment, taille_reelle_segment, epaisseur_segment);
		glutSolidCube(1.0);
		glPopMatrix();

		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0f, position_cone, 0.0f); 
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		//    glScalef(0.1f, 0.1f, 0.1f);
		glutSolidCone(0.1, taille_cone, 50, 5);
		glPopMatrix();

		// Axe des Z
		glColor3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, position_segment);
		glScalef(epaisseur_segment, epaisseur_segment, taille_reelle_segment);
		glutSolidCube(1.0);
		glPopMatrix();

		glColor3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, position_cone);
		//    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
		//    glScalef(0.1f, 0.1f, 0.1f);
		glutSolidCone(0.1, taille_cone, 50, 5);
		glPopMatrix();
	}
    glPopMatrix();
}
