/*
 * TypeMapTemp.h
 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

#include <string>
#include <iostream>
#include <stdio.h>


#ifndef TYPE_H_
#define TYPE_H_

class Type {
public:
  Type();
  Type(unsigned short,std::string);
  virtual ~Type();
  unsigned short rank;
  std::string type;

  bool operator== (const Type &other)
  {
    return this->rank == other.rank;
  }

  bool operator!= (const Type &other)
  {
    return !(this->rank == other.rank);
  }

};

#endif /* TYPEMAPTEMP_H_ */
