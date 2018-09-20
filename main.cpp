/*
 * main.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */
#include "Pokemon.h"
#include "Log.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <Windows.h>
#include <algorithm>
#include <memory>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>

#ifdef _WIN32
std::string deleteCommand = "del";
std::string pipeNull = "> NUL 2>&1";
#endif

#ifdef __linux__
std::string deleteCommand = "rm";
std::string pipeNull = "> /dev/null 2>&1";
#endif

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef int LONG;           //int on 64-bit, long on 32-bit
typedef unsigned int DWORD; //int on 64-bit, long on 32-bit

struct BITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
}__attribute__((packed));

struct BITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
}__attribute__((packed));

template <typename T>
  std::string toString ( T Number )
  {
     std::ostringstream ss;
     ss.clear();
     ss << Number;
     return ss.str();
  }

std::vector<int> getNearby(int pos, int square){
  std::vector<int> temp;
  if(pos == 0){
    temp.push_back(square * square - 1);
    temp.push_back(square * square - square);
    temp.push_back(square * square - square + 1);
    temp.push_back(square - 1);
    temp.push_back(square - 1 + square);
    temp.push_back(pos + 1);
    temp.push_back(pos + square);
    temp.push_back(pos + square + 1);
  }else if(pos == square - 1){
    temp.push_back(0);
    temp.push_back(0 + square);
    temp.push_back(square * square - 1);
    temp.push_back(square * square - 1 - 1);
    temp.push_back(square * square - square);
    temp.push_back(pos - 1);
    temp.push_back(pos + square);
    temp.push_back(pos + square - 1);
  }else if(pos == square * square - square){
    temp.push_back(square * square - 1 - square);
    temp.push_back(square * square - 1);
    temp.push_back(square - 1);
    temp.push_back(0);
    temp.push_back(0 + 1);
    temp.push_back(pos + 1);
    temp.push_back(pos - square);
    temp.push_back(pos - square + 1);
  }else if(pos == square * square - 1){
    temp.push_back(square * square - square - square);
    temp.push_back(square * square - square);
    temp.push_back(square - 1 - 1);
    temp.push_back(square - 1);
    temp.push_back(0);
    temp.push_back(pos - 1);
    temp.push_back(pos - square);
    temp.push_back(pos - square - 1);
  }else if(pos > 0 && pos < square - 1){
    temp.push_back(pos - 1);
    temp.push_back(pos + 1);
    temp.push_back(pos + square);
    temp.push_back(pos + square + 1);
    temp.push_back(pos + square - 1);
    temp.push_back(square * square - square + pos);
    temp.push_back(square * square - square + pos + 1);
    temp.push_back(square * square - square + pos - 1);
  }else if(pos > square * square - square && pos < square * square - 1){
    temp.push_back(pos - 1);
    temp.push_back(pos + 1);
    temp.push_back(pos - square);
    temp.push_back(pos - square + 1);
    temp.push_back(pos - square - 1);
    temp.push_back(pos - (square * square - square));
    temp.push_back(pos - (square * square - square) + 1);
    temp.push_back(pos - (square * square - square) - 1);
  }else if(pos % square == 0){
    temp.push_back(pos - square);
    temp.push_back(pos - square + 1);
    temp.push_back(pos + 1);
    temp.push_back(pos + square);
    temp.push_back(pos + square + 1);
    temp.push_back(pos + square - 1);
    temp.push_back(pos + square - 1 + square);
    temp.push_back(pos + square - 1 - square);
  }else if(pos % square == square - 1){
    temp.push_back(pos - square);
    temp.push_back(pos - square - 1);
    temp.push_back(pos - 1);
    temp.push_back(pos + square);
    temp.push_back(pos + square - 1);
    temp.push_back(pos - square + 1);
    temp.push_back(pos - square + 1 + square);
    temp.push_back(pos - square + 1 - square);
  }else{
    temp.push_back(pos + 1);
    temp.push_back(pos - 1);
    temp.push_back(pos + square);
    temp.push_back(pos - square);
    temp.push_back(pos + square + 1);
    temp.push_back(pos + square - 1);
    temp.push_back(pos - square + 1);
    temp.push_back(pos - square - 1);
  }
  std::sort(temp.begin(),temp.end());
  return temp;
}

void SaveBitmapToFile( BYTE* pBitmapBits,
                       LONG lWidth,
                       LONG lHeight,
                       WORD wBitsPerPixel,
                       const unsigned long& padding_size,
                       std::string lpszFileName )
{
    DWORD BI_RGB = 0;

    // Some basic bitmap parameters
    unsigned long headers_size = sizeof( BITMAPFILEHEADER ) +
                                 sizeof( BITMAPINFOHEADER );

    unsigned long pixel_data_size = lHeight * ( ( lWidth * ( wBitsPerPixel / 8 ) ) + padding_size );

    BITMAPINFOHEADER bmpInfoHeader = {0};

    // Set the size
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);

    // Bit count
    bmpInfoHeader.biBitCount = wBitsPerPixel;

    // Use all colors
    bmpInfoHeader.biClrImportant = 0;

    // Use as many colors according to bits per pixel
    bmpInfoHeader.biClrUsed = 0;

    // Store as un Compressed/
    bmpInfoHeader.biCompression = BI_RGB;

    // Set the height in pixels
    bmpInfoHeader.biHeight = lHeight;

    // Width of the Image in pixels
    bmpInfoHeader.biWidth = lWidth;

    // Default number of planes
    bmpInfoHeader.biPlanes = 1;

    // Calculate the image size in bytes
    bmpInfoHeader.biSizeImage = pixel_data_size;

    BITMAPFILEHEADER bfh = {0};

    // This value should be values of BM letters i.e 0x4D42
    // 0x4D = M 0�42 = B storing in reverse order to match with endian
    bfh.bfType = 0x4D42;
    //bfh.bfType = 'B'+('M' << 8);

    // <<8 used to shift �M� to end  */

    // Offset to the RGBQUAD
    bfh.bfOffBits = headers_size;

    // Total size of image including size of headers
    bfh.bfSize =  headers_size + pixel_data_size;

    // Create the file in disk to write
        std::fstream myfile;
    myfile = std::fstream(lpszFileName.c_str(), std::ios::out | std::ios::binary);

    /*HANDLE hFile = CreateFile( lpszFileName.c_str(),
                                GENERIC_WRITE,
                                0,
                                NULL,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL );*/

    // Return if error opening file
    //if( !hFile ) return;

    DWORD dwWritten = 0;

    // Write the File header

    char* byte_bfh = reinterpret_cast<char*>(&bfh);
    myfile.write(byte_bfh,sizeof(bfh));

    /*WriteFile( hFile,
                &bfh,
                sizeof(bfh),
                &dwWritten ,
                NULL );*/

    // Write the bitmap info header

    char* byte_bmpInfoHeader = reinterpret_cast<char*>(&bmpInfoHeader);

    myfile.write(byte_bmpInfoHeader,sizeof(bmpInfoHeader));

    /*WriteFile( hFile,
                &bmpInfoHeader,
                sizeof(bmpInfoHeader),
                &dwWritten,
                NULL );*/

    // Write the RGB Data

    char* byte_pBitmapBits = reinterpret_cast<char*>(pBitmapBits);

    

    myfile.write(byte_pBitmapBits,bmpInfoHeader.biSizeImage);

    /*WriteFile( hFile,
                pBitmapBits,
                bmpInfoHeader.biSizeImage,
                &dwWritten,
                NULL );*/

    // Close the file handle

    myfile.close();
    //CloseHandle( hFile );
}

void drawPicture1(std::vector<Pokemon>& battlefield, int counter, int square){
  int size = square;
  BYTE* buf = new BYTE[ size * 3 * size ];
  int c = 0;
  int pokeCounter = 0;
  for ( int i = 0; i < size; i++ )
      {
          for ( int j = 0; j < size; j++ )
          {
              buf[ c + 0 ] = (BYTE) battlefield[pokeCounter].b;
              buf[ c + 1 ] = (BYTE) battlefield[pokeCounter].g;
              buf[ c + 2 ] = (BYTE) battlefield[pokeCounter].r;

              c += 3;
              pokeCounter += 1;
          }
      }
    c += size * 3 * 3;

  SaveBitmapToFile( (BYTE*) buf,
                  size,
                  size,
                  24,
                  0,
                  toString(counter) + ".bmp" );
  delete [] buf;
}

void drawPicture2(std::vector<Pokemon>& battlefield, int counter, int square){
  int size = square * 2;
  BYTE* buf = new BYTE[ size * 3 * size ];
  int c = 0;
  int pokeCounter = 0;
  for ( int i = 0; i < square; i++ )
  {
    for ( int j = 0; j < square; j++ )
    {
      for(int k = 0; k < 2; k++){
        buf[ c + k * size * 3 + 0 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c + k * size * 3 + 1 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c + k * size * 3 + 2 ] = (BYTE) battlefield[pokeCounter].r;
        buf[ c + k * size * 3 + 3 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c + k * size * 3 + 4 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c + k * size * 3 + 5 ] = (BYTE) battlefield[pokeCounter].r;
      }
      c += 6;
      pokeCounter++;
    }
    c += size * 3;
  }
  SaveBitmapToFile( (BYTE*) buf,
                  size,
                  size,
                  24,
                  0,
                  toString(counter) + ".bmp" );
  delete [] buf;
}

void drawPicture4(std::vector<Pokemon>& battlefield, int counter, int square){
  int size = square * 4;
  BYTE* buf = new BYTE[ size * 3 * size ];
  int c = 0;
  int pokeCounter = 0;
  for ( int i = 0; i < square; i++ )
  {
    for ( int j = 0; j < square; j++ )
    {

      for(int k = 0; k < 4; k++){
        buf[ c+k*size*3 + 0 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c+k*size*3 + 1 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c+k*size*3 + 2 ] = (BYTE) battlefield[pokeCounter].r;
        buf[ c+k*size*3 + 3 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c+k*size*3+ 4 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c+k*size*3+ 5 ] = (BYTE) battlefield[pokeCounter].r;
        buf[ c+k*size*3+ 6 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c+k*size*3+ 7 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c+k*size*3+ 8 ] = (BYTE) battlefield[pokeCounter].r;
        buf[ c+k*size*3+ 9 ] = (BYTE) battlefield[pokeCounter].b;
        buf[ c+k*size*3+ 10 ] = (BYTE) battlefield[pokeCounter].g;
        buf[ c+k*size*3+ 11 ] = (BYTE) battlefield[pokeCounter].r;
      }
      c += 12;
      pokeCounter++;
    }
    c += size * 3 * 3;
  }
  SaveBitmapToFile( (BYTE*) buf,
                  size,
                  size,
                  24,
                  0,
                  toString(counter) + ".bmp" );
  delete [] buf;
}

void debugPrint(std::vector<Pokemon> a){
  std::cout << "\n";
  for(unsigned int counter = 0; counter < a.size(); counter++){
    std::cout << a[counter].print() << "\n";
  }
  std::cout << "\n";
}

struct speedEngine{
  int pos;
  int speed;
};

bool positiveDamageOccurred = true;
std::mutex damMutex;

void threadRoundDamage(std::vector<int> listOfElements, std::vector<Pokemon> &battleField, std::vector<winCounterStruct> &score){
  for(int iter = 0; iter < listOfElements.size(); iter++){
    if(battleField[listOfElements[iter]].attackPokemon(score)){
      damMutex.lock();
      positiveDamageOccurred = true;
      damMutex.unlock();
      d.trace("Pokemon " + battleField[listOfElements[iter]].print() + " has initiated a successful non-zero attack.");
    }
  }
}

int main(int argc, char* argv[]){

  int numbThreads = std::thread::hardware_concurrency();
  int desiredThreads = numbThreads;
  int square = 100;
  bool deleteSourceImages = false;
  bool createGif = false;
  int maxRounds = -1;
  int logLevel = 3;
  int framerate = 30;
  unsigned int seed = 0;
  bool useSeed = false;

  for(int argcounter = 1; argcounter < argc; argcounter++){
    if(argv[argcounter] == std::string("-d")){
      deleteSourceImages = true;
    }
    else if(argv[argcounter] == std::string("-g")){
      createGif = true;
    }
    else if(argv[argcounter] == std::string("-c")){
      if(argcounter + 2 <= argc){
        square = std::atoi(argv[argcounter + 1]);
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-x")){
      if(argcounter + 2 <= argc){
        maxRounds = std::atoi(argv[argcounter + 1]);
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-l")){
      if(argcounter + 2 <= argc){
        logLevel = std::atoi(argv[argcounter + 1]);
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-f")){
      if(argcounter + 2 <= argc){
        framerate = std::atoi(argv[argcounter + 1]);
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-s")){
      if(argcounter + 2 <= argc){
        useSeed = true;
        seed = std::atoi(argv[argcounter + 1]);
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-t")){
      if(argcounter + 2 <= argc){    
        int temp = std::atoi(argv[argcounter + 1]);
        if(0 < temp && temp <= numbThreads){
          desiredThreads = temp;
        }else{
          desiredThreads = numbThreads;
        }
        argcounter++;
      }else{
        std::cout << "Missing parameter, use -h for help.\n";
        return 1;
      }
    }
    else if(argv[argcounter] == std::string("-h")){
      std::cout << "Help:\n";
      std::cout << "-d = Delete round .bmps after the .mp4 render finishes. (Default:No)\n";
      std::cout << "-c X = Run simulation with a X * X square. (Default:100)\n";
      std::cout << "-x X = Run simulation until round X. (Default:No Limit)\n";
      std::cout << "-l X = Run simulation with log level X. (Default:3)(0=quiet,1=error,2=warning,3=notify,4=debug,5=trace)\n";
      std::cout << "-g = Create a .gif as well as .mp4 (Default:No)\n";
      std::cout << "-f X = Run simulation video with a framerate of X. (Default:30)\n";
      std::cout << "-s X = Run simulation with a seed of X. (Default:random)\n";
      std::cout << "-t X = Run simulation with X number of threads. (Default:all available)\n";
      return 0;
    }
    else{
      std::cout << "\"" << std::string(argv[argcounter]) << "\" is not a recognized command. Use the -h parameter for help.\n";
      return 1;
    }
  }
  d.changeLogLevel(logLevel);

  d.debug("Starting sim square=" + toString(square));
  d.debug("Starting sim deleteSourceImages=" + toString(deleteSourceImages));
  d.debug("Starting sim createGif=" + toString(createGif));
  d.debug("Starting sim maxRounds=" + toString(maxRounds));
  d.debug("Starting sim logLevel=" + toString(logLevel));
  d.debug("Starting sim framerate=" + toString(framerate));
  d.debug("Starting sim using seed=" + toString(useSeed));
  if(useSeed){
    d.debug("Starting sim using seed value=" + toString(seed));
  }
  d.debug("Starting sim with threads=" + toString(desiredThreads));

  d.debug("SIZEOF:WORD:" + toString(sizeof(WORD)) + "(Needs to be 2)");
  d.debug("SIZEOF:DWORD:" + toString(sizeof(DWORD)) + "(Needs to be 4)");
  d.debug("SIZEOF:LONG:" + toString(sizeof(LONG)) + "(Needs to be 4)");
  d.debug("SIZEOF:BITMAPFILEHEADER:" + toString(sizeof(BITMAPFILEHEADER)) + "(Needs to be 14)");
  d.debug("SIZEOF:BITMAPINFOHEADER:" + toString(sizeof(BITMAPINFOHEADER)) + "(Needs to be 40)");

  if(useSeed){
    srand (seed);
  }else{
    srand (time(NULL));
  }
  d.notify("Starting " + toString(square * square) + " square sim",10);
  std::thread threadPool[desiredThreads];
  TypeMap types;
  std::vector<Pokemon> battleField;
  std::vector<winCounterStruct> score;
  int pos = 0;
  if(square >= 100){
    d.notify("Loading...");
  }
  try{
    d.debug("Starting Pokemon load into battleField vector...",1);
    for(int counterY = 0; counterY < square; counterY++){
      for(int counterX = 0; counterX < square; counterX++){
        Pokemon tempPoke(&types,pos);
        int tempScore = 1;
        battleField.push_back(tempPoke);
        winCounterStruct tempWinCounterStruct;
        tempWinCounterStruct.count = 1;
        tempWinCounterStruct.pokemon = tempPoke.print();
        score.push_back(tempWinCounterStruct);
        d.trace("Added Pokemon: " + tempPoke.print() + " with initial score " + toString(tempScore) + " to position " + toString(pos));
        pos++;
      }
    }
  }
  catch(std::bad_alloc){
    d.error("You did not have enough memory to load the entire simulation. Try again with a smaller simulation.");
  }
  d.debug("Done with Pokemon load into battleField vector in",1);
  if(square >= 100){
    d.notify("Done!");
    d.notify("Linking...");
  }
  d.debug("Starting populating each Pokemons nearby pointer vector...",1);
  for(int countera = 0; countera < square * square; countera++){
    std::vector<int> temp = getNearby(battleField[countera].pos, square);
    for(unsigned int counterb = 0; counterb <temp.size(); counterb++){
      battleField[countera].nearby.push_back(& battleField[temp[counterb]]);
    }
  }
  d.debug("Done populating each Pokemons nearby pointer vector in",1);
  if(square >= 100){
    d.notify("Done!");
  }
  int counter = 1;
  d.debug("Starting simulation...",0);
  while(positiveDamageOccurred){
    d.debug("Starting turn " + toString(counter) + " ...",1);
    std::vector<speedEngine> howFast;
    d.debug("Calculating speed for battleField...",2);
    for(int counter = 0; counter < battleField.size(); counter++){
      speedEngine temp;
      temp.pos = counter;
      temp.speed = battleField[counter].speed;
      howFast.push_back(temp);
    }
    std::sort(howFast.begin(), howFast.end(),
                    [](speedEngine const & a, speedEngine const & b) -> bool
                    { return a.speed > b.speed; } );
    d.debug("Done calculating speed for battleField.",2);
    d.debug("Starting battle phase...",2);

    std::vector<int> adjacentToSameSpeed;
    std::vector<int> notAdjacentToSameSpeed;
    int lastSpeed = 1000000;

    if(desiredThreads > 1){
      for(int speedDelimCounter = 0; speedDelimCounter < square * square; speedDelimCounter++){
        adjacentToSameSpeed.push_back(howFast[speedDelimCounter].pos);
        if(battleField[howFast[speedDelimCounter].pos].speed < lastSpeed || speedDelimCounter == (square * square) - 1){
          lastSpeed = battleField[howFast[speedDelimCounter].pos].speed;
          if(speedDelimCounter != 0){
            d.debug("start");
            d.debug("begin " + toString(adjacentToSameSpeed.size()));
            positiveDamageOccurred = false;
            int threadPos = 0;
            for(int notAdjacentIter = 0; notAdjacentIter < adjacentToSameSpeed.size(); notAdjacentIter++){
              if(!battleField[adjacentToSameSpeed[notAdjacentIter]].adjacentToSameSpeed()){      
                notAdjacentToSameSpeed.push_back(adjacentToSameSpeed[notAdjacentIter]);
                adjacentToSameSpeed.erase(adjacentToSameSpeed.begin() + notAdjacentIter);
                notAdjacentIter--;
              }
            }    
            threadPool[threadPos++] = std::thread(threadRoundDamage, adjacentToSameSpeed, std::ref(battleField), std::ref(score));
            std::vector<std::vector<int>> temp;
            for(int tempIter = 0; tempIter < desiredThreads - 1; tempIter++){
              temp.push_back(std::vector<int>());
            }
            int addTo = 0;
            for(int tempIter = 0; tempIter < notAdjacentToSameSpeed.size(); tempIter++){
              temp[addTo++].push_back(notAdjacentToSameSpeed[tempIter]);
              if(addTo == desiredThreads - 1){
                addTo = 0;
              }
            }
            threadPool[0].join();
            for(int tempIter = 0; tempIter < desiredThreads - 1; tempIter++){
              // d.debug("starting nonadjacent thread at pos " + toString(threadPos));
              threadPool[threadPos++] = std::thread(threadRoundDamage, temp[tempIter], std::ref(battleField), std::ref(score));
              // d.debug("test " + toString(threadPos));
            }
            for(int tempIter = 1; tempIter < desiredThreads; tempIter++){
              threadPool[tempIter].join();
            }
            d.debug("end " + toString(notAdjacentToSameSpeed.size() + adjacentToSameSpeed.size()));
            adjacentToSameSpeed.clear();
            notAdjacentToSameSpeed.clear();
            d.debug("finish");
          }
        }
      }
    }else{
      for(int speedDelimCounter = 0; speedDelimCounter < square * square; speedDelimCounter++){
        adjacentToSameSpeed.push_back(howFast[speedDelimCounter].pos);
      }
      positiveDamageOccurred = false;
      threadRoundDamage(adjacentToSameSpeed, battleField, score);
      adjacentToSameSpeed.clear();
    }
    


    
    d.debug("Done with battle phase.",2);
    if(square > 0 && square < 500 ){
      d.debug("Starting a 4x picture...",2);
      drawPicture4(battleField,counter,square);
      d.debug("Done with 4x picture.",2);
    }else if(square >= 500 & square < 1000){
      d.debug("Starting a 2x picture...",2);
      drawPicture2(battleField,counter,square);
      d.debug("Done with 2x picture.",2);
    }else if(square >= 1000){
      d.debug("Starting a 1x picture...",2);
      drawPicture1(battleField,counter,square);
      d.debug("Done with 1x picture.",2);
    }
    d.debug("Refreshing battleField for next round...",2);
    for(unsigned int refresh = 0; refresh < battleField.size(); refresh++){
      battleField[refresh].canAttack = true;
    }
    d.debug("Done refreshing battleField for next round.",2);
    d.debug("Done with turn " + toString(counter) + " ...",1);
    // d.notify("-----" + toString(counter) + "-----");

    if(counter == maxRounds){
      positiveDamageOccurred = false;
    }else{
      counter++;
    }
    // exit(0);
  }
  d.debug("Done with simulation. " + toString(counter) + " rounds in" ,0);
  d.debug("Counting to see who won...",0);
  std::sort(score.begin(), score.end(),
                  [](winCounterStruct const & a, winCounterStruct const & b) -> bool
                  { return a.count > b.count; } );
  d.debug("Done counting to see who won.",0);

  time_t now = time(0);
  tm *ltm = localtime(&now);
  std::ostringstream oss;
  oss << ltm->tm_year + 1900 << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_mon + 1 << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_mday << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_hour << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_min << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_sec ;
  std::string cmd = "ffmpeg -r " + toString(framerate) + " -f image2 -s 1920x1080 -i %0d.bmp -vcodec libx264 -crf 25 -pix_fmt yuv420p " + oss.str() + ".mp4 " + pipeNull;
  d.debug("Executing command: " + cmd);
  d.debug("Creating mp4...",0);
  system(cmd.c_str());
  d.debug("Done creating mp4 in ",0);
  if(createGif){
    cmd = "ffmpeg -i " + oss.str() + ".mp4 -vf fps=30 " + oss.str() + ".gif " + pipeNull;
    system(cmd.c_str());
  }
  if(deleteSourceImages){
    cmd = deleteCommand + " *.bmp";
    std::cout << cmd << "\n";
    system(cmd.c_str());
  }
  d.notify("Battle is over after " + toString(counter) + " rounds in ",10);
  if(score.size() < 5){
    for(unsigned int counter2 = 0; counter2 < score.size(); counter2++){
      d.notify("[" + toString(counter2) + "]" + score[counter2].pokemon + " (" + toString(((float)score[counter2].count / (square * square)) * 100) + " %)");
    }
  }else{
    for(unsigned int counter2 = 0; counter2 < 5; counter2++){
      if(score[counter2].count > 0){
        d.notify("[" + toString(counter2) + "]" + score[counter2].pokemon + " (" + toString(((float)score[counter2].count / (square * square)) * 100) + " %)");
      }
    }
  }

}



