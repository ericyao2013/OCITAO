/* -*- C++ -*- $Id$ */

// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO and the TAO IDL Compiler have been developed by the Center for
// Distributed Object Computing at Washington University, St. Louis.
//
// Information about TAO is available at:
//                 http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef AMH_INNER_I_H_
#define AMH_INNER_I_H_

#include "innerS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  Inner_i : public virtual POA_Inner
{
public:
  // ctor takes a 1 to delay and return string, a 0 to crash
  Inner_i (int d);

  // will either return a string after a brief delay, or crash
  virtual char * answer (const char *question);

private:
  int divisor_;
};


#endif /* AMH_INNER_H_  */
