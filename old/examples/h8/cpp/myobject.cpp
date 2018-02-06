/*
 * Author: 2002 Davide Cantini
 * CVS: $Id: myobject.cpp,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "myobject.hpp"

void myobject::print1(void)
{
  EE_lcd_write_num(i++); 
}

void myobject::print2(void)
{
  EE_lcd_write_num(i); 
}
