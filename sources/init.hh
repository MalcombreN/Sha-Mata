#pragma once


#include "actions.hh"

int notre_init(int argc, char** argv, void (*DrawGLScene)());

GLvoid Redimensionne(GLsizei Width, GLsizei Height);

void createMenu();
void menu(int value);
void load_textures();
