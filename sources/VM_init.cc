#include "VM_init.hh"
#include "operation_base.hh"

void VM_init()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//camera 
	gluLookAt(0,0,1, 0., 0., 0., 0., 1., 0.); 

}
