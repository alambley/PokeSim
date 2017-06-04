/*
 * TypeMap.h


 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

#ifndef TYPEMAP_H_
#define TYPEMAP_H_

#include <vector>
#include <string>
#include "Type.h"
#include <iostream>
#include <stdlib.h>


class TypeMap {
public:
  std::vector<Type> typeList;
  std::vector<std::vector<float> > typeStr;
  TypeMap();
  Type getRandomType();
  float getDmgMult(Type,Type);
};

#endif /* TYPEMAP_H_ */
