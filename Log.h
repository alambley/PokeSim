/*
 * Log.h
 *
 *  Created on: May 28, 2017
 *      Author: Alex Lambley
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <vector>

class Log {


  struct timeStruct{
    int key;
    std::chrono::steady_clock::time_point value;
  };

public:
  Log();
  Log(int);
  void error(std::string);
  void warning(std::string);
  void notify(std::string);
  void debug(std::string);
  void trace(std::string);
  void error(std::string,int);
  void warning(std::string,int);
  void notify(std::string,int);
  void debug(std::string,int);
  void trace(std::string,int);
  void changeLogLevel(int);
  std::string prettyTime(int);

private:
  int logLevel;
  std::vector<timeStruct> timeVector;
};

extern class Log d;



#endif /* LOG_H_ */
