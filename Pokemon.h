/*
 * Pokemon.h

 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */


#ifndef POKEMON_H_
#define POKEMON_H_



#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include "TypeMap.h"
#include <sstream>
#include <algorithm>
#include "Log.h"

struct winCounterStruct{
  int count = 0;
  std::string pokemon;
};

class Pokemon {

  public:

    short health;
    unsigned short int attack;
    unsigned short int defense;
    unsigned short int speed;
    unsigned long int pos;
    unsigned long int team;
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
    bool canAttack;
    Type typea;
    Type typeb;
    TypeMap* typeMap;
    std::vector<Pokemon*> nearby;
    Pokemon* attacked;

    Pokemon();
    Pokemon(TypeMap*,unsigned long int);
    virtual ~Pokemon();
    std::string print();
    bool attackPokemon(std::vector<winCounterStruct>&);
    void defeatPokemon(Pokemon);
    bool samePokemon(Pokemon);
    bool damagePokemon(Pokemon*,std::vector<winCounterStruct>&);
    int theDamageAlgorithm(Pokemon,std::vector<winCounterStruct>&,bool);
    bool chance(float);
    std::vector<int> getNumbFriends(std::vector<int>);
    bool adjacentToSameSpeed();
    bool adjacentToSameSpeedSpace(short, long);

    bool operator < (const Pokemon& str) const{
      return speed > str.speed;
    };

};



#endif /* POKEMON_H_ */
