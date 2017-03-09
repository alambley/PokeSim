/*
 * TypeMap.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

#include "TypeMap.h"
#include "Pokemon.h"

int getRandIntTypeMap(int min, int max){
  return min + (rand() % (int)(max - min + 1));
}

TypeMap::TypeMap() {
  typeList.push_back(Type(0, "Normal"));
  typeList.push_back(Type(1, "Fire"));
  typeList.push_back(Type(2, "Water"));
  typeList.push_back(Type(3, "Electric"));
  typeList.push_back(Type(4, "Grass"));
  typeList.push_back(Type(5, "Ice"));
  typeList.push_back(Type(6, "Fighting"));
  typeList.push_back(Type(7, "Poison"));
  typeList.push_back(Type(8, "Ground"));
  typeList.push_back(Type(9, "Flying"));
  typeList.push_back(Type(10, "Psychic"));
  typeList.push_back(Type(11, "Bug"));
  typeList.push_back(Type(12, "Rock"));
  typeList.push_back(Type(13, "Ghost"));
  typeList.push_back(Type(14, "Dragon"));
  typeList.push_back(Type(15, "Dark"));
  typeList.push_back(Type(16, "Steel"));
  typeList.push_back(Type(17, "Fairy"));

  typeStr={
     //nm,fr,wt,el,gr,ic,fg,po,gd,fl,py,bg,rk,gh,dr,dk,st,fa
/*nm*/{01,01,01,01,01,01,01,01,01,01,01,01,.5,00,01,01,.5,01},
/*fr*/{01,.5,.5,01,02,02,01,01,01,01,01,02,.5,01,.5,01,02,01},
/*wt*/{01,02,.5,01,.5,01,01,01,02,01,01,01,02,01,.5,01,01,01},
/*el*/{01,01,02,.5,.5,01,01,01,00,02,01,01,01,01,.5,01,01,01},
/*gr*/{01,.5,02,01,.5,01,01,.5,02,.5,01,.5,02,01,.5,01,.5,01},
/*ic*/{01,.5,.5,01,02,.5,01,01,02,02,01,01,01,01,02,01,.5,01},
/*fg*/{02,01,01,01,01,02,01,.5,01,.5,.5,.5,02,00,01,02,02,.5},
/*po*/{01,01,01,01,02,01,01,.5,.5,01,01,01,.5,.5,01,01,00,02},
/*gd*/{01,02,01,02,.5,01,01,02,01,00,01,.5,02,01,01,01,02,01},
/*fl*/{01,01,01,.5,02,01,02,01,01,01,01,02,.5,01,01,01,.5,01},
/*py*/{01,01,01,01,01,01,02,02,01,01,.5,01,01,01,01,00,.5,01},
/*bg*/{01,.5,01,01,02,01,.5,.5,01,.5,02,01,01,.5,01,02,.5,.5},
/*rk*/{01,02,01,01,01,02,.5,01,.5,02,01,02,01,01,01,01,.5,01},
/*gh*/{00,01,01,01,01,01,01,01,01,01,02,01,01,02,01,.5,01,01},
/*dr*/{01,01,01,01,01,01,01,01,01,01,01,01,01,01,02,01,.5,00},
/*dk*/{01,01,01,01,01,01,.5,01,01,01,02,01,01,02,01,.5,01,.5},
/*st*/{01,.5,.5,.5,01,02,01,01,01,01,01,01,02,01,01,01,.5,02},
/*fa*/{01,.5,01,01,01,01,02,.5,01,01,01,01,01,01,02,02,.5,01},
  };
}

Type TypeMap::getRandomType(){
  Type temp = typeList[getRandIntTypeMap(0, 14)];
  return temp;
}

float TypeMap::getDmgMult(Type attacker, Type defender){
  return typeStr[attacker.rank][defender.rank];
}

