/*
 * Author: 2002 Davide Cantini
 * CVS: $Id: code.cpp,v 1.3 2006/01/05 14:38:25 pj Exp $
 */

/*
 * C++ test
 * this test simply compiles a C++ class and calls its methods
 */

#include "code.h"
#include "myobject.hpp"

void wait(void)
{    
    while (!EE_button_pressed(VIEW_BUTTON));
    while (EE_button_pressed(VIEW_BUTTON));
}

void thread0(void) {} 
void thread1(void) {}
void thread2(void) {}

void main(void)
{
  myobject test(10);

  /* initialization */
  EE_init();     

  test.print1();
  wait();
  test.print2();
  wait();

  for (;;) {}  	    
}
