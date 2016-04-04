#ifndef _UTILS_H_
#define _UTILS_H_

#include "basicIncludes.h"


string intToString(int num) {
  return static_cast<ostringstream*>( &(ostringstream() << num) )->str();
}



#endif
