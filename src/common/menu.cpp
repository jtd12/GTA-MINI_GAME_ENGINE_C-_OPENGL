#include"menu.hpp"


void menuP(int num){

 if(num == 0){
    glutDestroyWindow(mm.window);
    exit(0);
  }else{
    mm.value = num;
  }
  glutPostRedisplay();
  

}

void gestionmenu(int num){
 
  if(num == 0){
    glutDestroyWindow(mm.window);
    exit(0);
  }else{
   mm.value = num;
  }
  glutPostRedisplay();
 
} 

void createMenu(void){    


	mm.nSousmenu1 = glutCreateMenu(gestionmenu);
	glutAddMenuEntry("Entrer dans le véhicule", 1);
	glutAddMenuEntry("Sortir du véhicule", 2);
	
	mm.nMenuprincipal = glutCreateMenu(menuP);

	glutAddSubMenu("Vehicule", mm.nSousmenu1);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	
	


} 
