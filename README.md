# PokeSim

A C++ implementation of the "Pokemon Simulation" that I first saw on /r/dataisbeautiful in [this post](https://www.reddit.com/r/dataisbeautiful/comments/5tfcym/a_simulation_of_360000_1_pixel_pokemon_fighting/) by /u/Morning_Fresh. I figured that a C++ implementation might run a little faster and be something fun to write. If you're not familiar, it is basically a simulation that gives a certain amount of "Pokemon" specific attributes and two "types" that fight and faint based on a damage formula with winners taking over the losers and gaining ground. The simulation ends when an entire "round" has gone by without a single instance of positive non-zero damage being done. Usually this means that there is one man standing although there are scenarios where there are multiple survivors and the winner goes to whomever holds more of the board.

## What You'll Need

This application has been tested to compile/run with MinGW on Windows and gcc on Linux. You will also need ffmpeg installed and on your path so that it will automatically turn the simulation into a .mp4 file once it finishes. You can find it [here](https://ffmpeg.org/).

## Windows mingw Build

g++ -std=c++11 -mno-ms-bitfields -o PokeSim \*.cpp

## Linux gcc Build

g++ -std=c++11  -o PokeSim \*.cpp

## Run Parameters

-h        Print this output.

-d        Delete round .bmps after the .mp4 render finishes. (Default:No)

-c X      Run simulation with a X * X square. (Default:100)

-x X      Run simulation until round X. (Default:No Limit)

-l X      Run simulation with log level X. (Default:3)(0=quiet,1=error,2=warning,3=notify,4=debug,5=trace)

-g        Create a .gif as well as .mp4 (Default:No)

-f X      Run simulation video with a framerate of X. (Default:30)


## Current Size

~~I have 16 GB of RAM and and 2000^2 is right around the maximum simulation that I can run without running into bad_alloc.~~ Don't worry about this if compiling with gcc or 64bit mingw. I ran a 5000^2 sim without problems.
 The main data type is about 112 B but could probably be smaller. Your mileage may vary.

## Examples

Format health:attack:defense:speed type1-type2

A 100x100 won by a 3:8:5:5 Water-Dragon type

![](https://github.com/alambley/PokeSim/blob/master/preview/a.gif?raw=true)

A 100x100 won by a 1:11:5:4 Ice-Flying type

![](https://github.com/alambley/PokeSim/blob/master/preview/b.gif?raw=true)
