/*
 * Log.cpp
 *
 *  Created on: May 28, 2017
 *      Author: Alex Lambley
 */

#include "Log.h"
Log d(3);



template <typename T>
std::string toString ( T Number )
{
   std::ostringstream ss;
   ss.clear();
   ss << Number;
   return ss.str();
}

Log::Log() {
  logLevel = 3;
}

Log::Log(int initLogLevel) {
  logLevel = initLogLevel;
}

void Log::error(std::string allocator) {
  if(logLevel >= 1){
    std::cout << allocator << "\n";
  }
  exit(1);
}

void Log::warning(std::string allocator) {
  if(logLevel >= 2){
    std::cout << allocator << "\n";
  }
}

void Log::notify(std::string allocator) {
  if(logLevel >= 3){
    std::cout << allocator << "\n";
  }
}

void Log::debug(std::string allocator) {
  if(logLevel >= 4){
    std::cout << allocator << "\n";
  }
}

void Log::trace(std::string allocator) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  if(logLevel >= 5){
    std::cout << allocator << "\n";
  }
}

void Log::error(std::string allocator, int int1) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point then;
  int foundPos = -1;
  bool found = false;
  for(int counter = 0; counter < timeVector.size(); counter++){
    if(timeVector[counter].key == int1){
      found = true;
      then = timeVector[counter].value;
      foundPos = counter;
      break;
    }
  }
  if(found){
    if(logLevel >= 1){
      std::cout << allocator << " " << prettyTime(std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()) <<"\n";
    }
    timeVector.erase(timeVector.begin() + foundPos);
  }else{
    timeStruct temp;
    temp.key = int1;
    temp.value = now;
    timeVector.push_back(temp);
    if(logLevel >= 1){
      std::cout << allocator << "\n";
    }
  }
  exit(1);
}

void Log::warning(std::string allocator, int int1) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point then;
  int foundPos = -1;
  bool found = false;
  for(int counter = 0; counter < timeVector.size(); counter++){
    if(timeVector[counter].key == int1){
      found = true;
      then = timeVector[counter].value;
      foundPos = counter;
      break;
    }
  }
  if(found){
    if(logLevel >= 2){
      std::cout << allocator << " " << prettyTime(std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()) <<"\n";
    }
    timeVector.erase(timeVector.begin() + foundPos);
  }else{
    timeStruct temp;
    temp.key = int1;
    temp.value = now;
    timeVector.push_back(temp);
    if(logLevel >= 2){
      std::cout << allocator << "\n";
    }
  }
}

void Log::notify(std::string allocator, int int1) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point then;
  int foundPos = -1;
  bool found = false;
  for(int counter = 0; counter < timeVector.size(); counter++){
    if(timeVector[counter].key == int1){
      found = true;
      then = timeVector[counter].value;
      foundPos = counter;
      break;
    }
  }
  if(found){
    if(logLevel >= 3){
      std::cout << allocator << " " << prettyTime(std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()) <<"\n";
    }
    timeVector.erase(timeVector.begin() + foundPos);
  }else{
    timeStruct temp;
    temp.key = int1;
    temp.value = now;
    timeVector.push_back(temp);
    if(logLevel >= 3){
      std::cout << allocator << "\n";
    }
  }
}

void Log::debug(std::string allocator, int int1) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point then;
  int foundPos = -1;
  bool found = false;
  for(int counter = 0; counter < timeVector.size(); counter++){
    if(timeVector[counter].key == int1){
      found = true;
      then = timeVector[counter].value;
      foundPos = counter;
      break;
    }
  }
  if(found){
    if(logLevel >= 4){
      std::cout << allocator << " " << prettyTime(std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()) <<"\n";
    }
    timeVector.erase(timeVector.begin() + foundPos);
  }else{
    timeStruct temp;
    temp.key = int1;
    temp.value = now;
    timeVector.push_back(temp);
    if(logLevel >= 4){
      std::cout << allocator << "\n";
    }
  }
}

void Log::trace(std::string allocator, int int1) {
  std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point then;
  int foundPos = -1;
  bool found = false;
  for(int counter = 0; counter < timeVector.size(); counter++){
    if(timeVector[counter].key == int1){
      found = true;
      then = timeVector[counter].value;
      foundPos = counter;
      break;
    }
  }
  if(found){
    if(logLevel >= 5){
      std::cout << allocator << " " << prettyTime(std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count()) <<"\n";
    }
    timeVector.erase(timeVector.begin() + foundPos);
  }else{
    timeStruct temp;
    temp.key = int1;
    temp.value = now;
    timeVector.push_back(temp);
    if(logLevel >= 5){
      std::cout << allocator << "\n";
    }
  }
}

void Log::changeLogLevel(int int1) {
  logLevel = int1;
}

std::string Log::prettyTime(int time) {
  if(time < 1000){
    return toString(time) + "ms";
  }else if(time < 60000){
    return toString(time/1000) + "." + toString(time%1000/100) + "s";
  }else if(time < 3600000){
    return toString(time/60000) + "m " + toString(time%60000/1000) + "s" ;
  }else{
    return toString(time/3600000) + "h " + toString(time%3600000/60000) + "m " + toString(time%3600000%60000/1000) + "s";
  }
}
