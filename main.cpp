/*
 * main.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: Alex Lambley
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Pokemon.h"
#include <Windows.h>
#include <algorithm>
#include <memory>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <string>

template <typename T>
  std::string NumberToString ( T Number )
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
    // 0x4D = M 0×42 = B storing in reverse order to match with endian
    bfh.bfType = 0x4D42;
    //bfh.bfType = 'B'+('M' << 8);

    // <<8 used to shift ‘M’ to end  */

    // Offset to the RGBQUAD
    bfh.bfOffBits = headers_size;

    // Total size of image including size of headers
    bfh.bfSize =  headers_size + pixel_data_size;

    // Create the file in disk to write
    HANDLE hFile = CreateFile( lpszFileName.c_str(),
                                GENERIC_WRITE,
                                0,
                                NULL,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL );

    // Return if error opening file
    if( !hFile ) return;

    DWORD dwWritten = 0;

    // Write the File header
    WriteFile( hFile,
                &bfh,
                sizeof(bfh),
                &dwWritten ,
                NULL );

    // Write the bitmap info header
    WriteFile( hFile,
                &bmpInfoHeader,
                sizeof(bmpInfoHeader),
                &dwWritten,
                NULL );

    // Write the RGB Data
    WriteFile( hFile,
                pBitmapBits,
                bmpInfoHeader.biSizeImage,
                &dwWritten,
                NULL );

    // Close the file handle
    CloseHandle( hFile );
}

void drawPicture(std::vector<Pokemon>& battlefield, int counter, int square){
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
                  NumberToString(counter) + ".bmp" );
  delete [] buf;
}

void debugPrint(std::vector<Pokemon> a){
  std::cout << "\n";
  for(unsigned int counter = 0; counter < a.size(); counter++){
    std::cout << a[counter].print() << "\n";
  }
  std::cout << "\n";
}

struct winCounterStruct{
  Pokemon pokemon;
  int count = 0;
};

struct speedEngine{
  int pos;
  int speed;
};

int main(int argc, char* argv[]){

  int square = 100;
  bool deleteSourceImages = false;
  int maxRounds = -1;

  for(int argcounter = 1; argcounter < argc; argcounter++){
    if(argv[argcounter] == std::string("-d")){
      deleteSourceImages = true;
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
    else if(argv[argcounter] == std::string("-h")){
      std::cout << "Help:\n";
      std::cout << "-d = Delete round .bmps after the .mp4 render finishes. (Default:No)\n";
      std::cout << "-c X = Run simulation with a X * X square. (Default:100)\n";
      std::cout << "-x X = Run simulation until round X. (Default:No Limit)\n";
      return 0;
    }
    else{
      std::cout << "\"" << std::string(argv[argcounter]) << "\" is not a recognized command. Use the -h parameter for help.\n";
      return 1;
    }
  }

  srand (time(NULL));
  TypeMap types;
  std::vector<Pokemon> battleField;
  int pos = 0;
  if(square >= 100){
    std::cout << "Loading...\n";
  }
  try{
    for(int counterY = 0; counterY < square; counterY++){
      for(int counterX = 0; counterX < square; counterX++){
        battleField.push_back(Pokemon(&types,pos));
        pos++;
      }
    }
  }
  catch(std::bad_alloc){
    std::cout << "You did not have enough memory to load the entire simulation. Try again with a smaller simulation.\n";
    return 1;
  }
  if(square >= 100){
    std::cout << "Done.\n";
    std::cout << "Linking...\n";
  }
  for(int countera = 0; countera < square * square; countera++){
    std::vector<int> temp = getNearby(battleField[countera].pos, square);
    for(unsigned int counterb = 0; counterb <temp.size(); counterb++){
      battleField[countera].nearby.push_back(& battleField[temp[counterb]]);
    }
  }
  if(square >= 100){
    std::cout << "Done.\n";
  }
  bool keepgoing = true;
  int counter = 1;
  while(keepgoing){
    std::vector<speedEngine> howFast;
    for(int counter = 0; counter < battleField.size(); counter++){
      speedEngine temp;
      temp.pos = counter;
      temp.speed = battleField[counter].speed;
      howFast.push_back(temp);
    }
    std::sort(howFast.begin(), howFast.end(),
                    [](speedEngine const & a, speedEngine const & b) -> bool
                    { return a.speed > b.speed; } );
    keepgoing = false;
    for(int maincounter = 0; maincounter < square * square; maincounter++){
      if(battleField[howFast[maincounter].pos].attackPokemon()){
        keepgoing = true;
      }
    }
    drawPicture(battleField,counter,square);
    for(unsigned int refresh = 0; refresh < battleField.size(); refresh++){
      battleField[refresh].canAttack = true;
    }
    std::cout << "-----" << counter << "-----\n";
    if(counter == maxRounds){
      keepgoing = false;
    }else{
      counter++;
    }
  }
  bool found;
  std::vector<winCounterStruct> winCount;
  for(unsigned int winCounter = 0; winCounter < battleField.size(); winCounter++){
    found = false;
    for(unsigned int winCounter2 = 0; winCounter2 < winCount.size(); winCounter2++){
      if(battleField[winCounter].samePokemon(winCount[winCounter2].pokemon)){
        winCount[winCounter2].count++;
        found = true;
        break;
      }
    }
    if(!found){
      winCounterStruct temp;
      temp.pokemon = battleField[winCounter];
      temp.count = 1;
      winCount.push_back(temp);
    }
  }
  std::sort(winCount.begin(), winCount.end(),
                [](winCounterStruct const & a, winCounterStruct const & b) -> bool
                { return a.count > b.count; } );
  time_t now = time(0);
  tm *ltm = localtime(&now);
  std::ostringstream oss;
  oss << ltm->tm_year + 1900 << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_mon + 1 << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_mday << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_hour << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_min << "-" <<
  std::setw(2) << std::setfill('0') << ltm->tm_sec ;
  std::string cmd = "ffmpeg -framerate 30 -f image2 -i %d.bmp -b 5000k " + oss.str() + ".avi";
  system(cmd.c_str());
  if(deleteSourceImages){
    system("del *.bmp");
  }
  std::cout << "Battle is over after " << counter << " rounds.\n";
  if(winCount.size() < 3){
    for(unsigned int counter2 = 0; counter2 < winCount.size(); counter2++){
      std::cout << "[" << counter2 << "]" << winCount[counter2].pokemon.print() << " (" << ((float)winCount[counter2].count / (square * square)) * 100 << " %)\n";
    }
  }else{
    for(unsigned int counter2 = 0; counter2 < 3; counter2++){
      std::cout << "[" << counter2 << "]" << winCount[counter2].pokemon.print() << " (" << ((float)winCount[counter2].count / (float)(square * square)) * 100.0 << " %)\n";
    }
  }

}



