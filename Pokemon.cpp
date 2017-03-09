/*
 * Pokemon.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

#include "Pokemon.h"

int getRandInt(int min, int max){
  return min + (rand() % (int)(max - min + 1));
}

Pokemon::Pokemon(){

}

struct PokeDamage{
  Pokemon * pointer;
  int damage;
};

Pokemon::Pokemon(TypeMap *initTypeMap, unsigned long int initPos){
  attacked = NULL;
  pos = initPos;
  team = initPos;
  health = 1;
  attack = 1;
  defense = 1;
  speed = 1;
  canAttack = true;
  r= getRandInt(0,255);
  g= getRandInt(0,255);
  b= getRandInt(0,255);
  typeMap = initTypeMap;
  TypeMap temp = *initTypeMap;
  typea = temp.getRandomType();
  do{
    typeb = temp.getRandomType();
  }while(typea == typeb);
  for(int counter0 = 0; counter0 < 16; counter0++){
    int temp = getRandInt(0, 3);
    switch(temp){
      case 0:
        health++;
        break;
      case 1:
        attack++;
        break;
      case 2:
        defense++;
        break;
      case 3:
        speed++;
        break;
    }
  }
}

Pokemon::~Pokemon(){

}

std::string Pokemon::print(){
  std::ostringstream oss;
  oss << health << ":" << attack << ":" << defense << ":" << speed << ":" << typea.type << "-" << typeb.type;
  return oss.str();
}

bool Pokemon::attackPokemon(){
  if(!canAttack){
    return false;
  }
  if(attacked != NULL){
    Pokemon temp = *attacked;
    return damagePokemon(attacked);
  }else{
    std::vector<PokeDamage> findMostDmg;
    for(unsigned int counter = 0; counter < nearby.size(); counter++){
      if(samePokemon(*nearby[counter])){
        //do nothing
      }else{
        Pokemon defender = *nearby[counter];
        PokeDamage temp;
        temp.pointer = nearby[counter];
        temp.damage = theDamageAlgorithm(defender);
        findMostDmg.push_back(temp);
      }
    }
    std::sort(findMostDmg.begin(), findMostDmg.end(),
                       [](PokeDamage const & a, PokeDamage const & b) -> bool
                       { return a.damage > b.damage; } );
    int highestdamage;
    if(findMostDmg.size() > 0){
      highestdamage = findMostDmg[0].damage;
      for(int temp = 0; temp < findMostDmg.size(); temp++){
        if(findMostDmg[temp].damage < highestdamage){
          findMostDmg.erase(findMostDmg.begin() + temp);
        }
      }
      return damagePokemon(findMostDmg[getRandInt(0, findMostDmg.size()-1)].pointer);
    }
  }
  return false;
}

bool Pokemon::samePokemon(Pokemon other){
  if(team == other.team){
    return true;
  }
  return false;
}

bool Pokemon::damagePokemon(Pokemon* other){
  Pokemon defender = *other;
  int damage = theDamageAlgorithm(defender);
  if(damage > 0){
    attacked = other;
    defender.attacked = this;
    canAttack = false;
    defender.health -= damage;
    if(defender.health <= 0){

      health += 1;

      defender.canAttack = false;
      defender.r = r;
      defender.g = g;
      defender.b = b;
      attacked = NULL;
      defender.attacked = NULL;
      defender.attack = attack;
      defender.defense = defense;
      defender.speed = speed;
      defender.health = health;
      defender.typea = typea;
      defender.typeb = typeb;
      defender.team = team;
    }else{
    }
    *other = defender;
    return true;
  }else{
    return false;
  }
}

int Pokemon::theDamageAlgorithm(Pokemon defender){
  TypeMap temp = *typeMap;
  //std::cout << "debug " << print() << " attacked " << defender.print() << " for " << attack * temp.getDmgMult(typea, defender.typea) * temp.getDmgMult(typea, defender.typeb) - (float)defender.defense / 2 << " damage.\n";
  //std::cout << attack << " * " << temp.getDmgMult(typea, defender.typea) << " * " << temp.getDmgMult(typea, defender.typeb) << " - " << (float)defender.defense / 2 << "\n";
  return attack * temp.getDmgMult(typea, defender.typea) * temp.getDmgMult(typea, defender.typeb) - (float)defender.defense / 2;
}

