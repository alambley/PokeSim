/*
 * Pokemon.h

 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

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


#ifndef POKEMON_H_
#define POKEMON_H_

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
    bool attackPokemon();
    void defeatPokemon(Pokemon);
    bool samePokemon(Pokemon);
    bool damagePokemon(Pokemon*);
    int theDamageAlgorithm(Pokemon);

    bool operator < (const Pokemon& str) const{
      return speed > str.speed;
    };

};



#endif /* POKEMON_H_ */
