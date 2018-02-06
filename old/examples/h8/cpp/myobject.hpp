/*
 * Author: 2002 Davide Cantini
 * CVS: $Id: myobject.hpp,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include <ee.h>

#ifndef __MYOBJECT__
#define __MYOBJECT__

class myobject {
  int i;
public:
  myobject(int par) : i(par) {};

  void print1(void);
  virtual void print2(void);
};

#endif
