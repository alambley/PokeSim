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

template <typename T>
std::string toString ( T Number )
{
   std::ostringstream ss;
   ss.clear();
   ss << Number;
   return ss.str();
}

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
  int originalHealth = 20 - attack - defense - speed;
  std::ostringstream oss;
  std::vector<int> a;
  oss << "["<< pos << "]" <<originalHealth << ":" << attack << ":" << defense << ":" << speed << ":" << typea.type << "-" << typeb.type;
  return oss.str();
}

bool Pokemon::attackPokemon(std::vector<winCounterStruct> &score){
  if(!canAttack){
    return false;
  }
  if(attacked != NULL){
    Pokemon temp = *attacked;
    return damagePokemon(attacked,score);
  }else{
    std::vector<PokeDamage> findMostDmg;
    for(unsigned int counter = 0; counter < nearby.size(); counter++){
      if(samePokemon(*nearby[counter])){
        //do nothing
      }else{
        Pokemon defender = *nearby[counter];
        PokeDamage temp;
        temp.pointer = nearby[counter];
        temp.damage = theDamageAlgorithm(defender,score,false);
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
      return damagePokemon(findMostDmg[getRandInt(0, findMostDmg.size()-1)].pointer,score);
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

bool Pokemon::damagePokemon(Pokemon* other,std::vector<winCounterStruct> &score){
  Pokemon defender = *other;

  int damage = theDamageAlgorithm(defender,score,true);
  if(damage > 0){
    attacked = other;
    defender.attacked = this;
    canAttack = false;
    defender.health -= damage;
    if(defender.health <= 0){

      health += 1;

      score[team].count += 1;
      score[defender.team].count -= 1;

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

int Pokemon::theDamageAlgorithm(Pokemon defender,std::vector<winCounterStruct> &score, bool canCrit){
  TypeMap temp = *typeMap;
  int critMult = 1;
  if(canCrit){
    if(chance((double)score[team].count/score.size())){
      critMult = 2;
    }
  }
  return attack * temp.getDmgMult(typea, defender.typea) * temp.getDmgMult(typea, defender.typeb) * critMult - (float)defender.defense / 2;
}

bool Pokemon::chance(float prob){
  float r = ((double) rand() / (RAND_MAX));
  if(r < prob){
    return true;
  }
  return false;
}

bool Pokemon::adjacentToSameSpeed(){
  Pokemon temp;
  for(unsigned int counter = 0; counter < nearby.size(); counter++){
    temp = *nearby[counter];
    if (temp.speed == speed){
      return true;
    }
  }
  return false;
}

//this function is OBE, slowed down sim too much
std::vector<int> Pokemon::getNumbFriends(std::vector<int> friends){
  for(int counter = 0; counter < nearby.size(); counter++){
    Pokemon temp = *nearby[counter];
    if(temp.team == team){
      if(std::find(friends.begin(), friends.end(), temp.pos) != friends.end()){

      }else{
        friends.push_back(temp.pos);
        friends = temp.getNumbFriends(friends);
      }
    }
  }
  return friends;
}

