#ifndef DEF_MENU_HPP
#define DEF_MENU_HPP
#include<C:\library\freeglut\include\GL\freeglut.h>

	void createMenu(void);
	void menuP(int num);
	void gestionmenu(int num);
	void gestionmenu2(int num);	
	
struct menu
{
	
    int value; 
    int nSousmenu1;
    int nSousmenu2;
	int nMenuprincipal;
	int window=0;
};
 extern menu mm;

#endif
