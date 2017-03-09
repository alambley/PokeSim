# PokeSim

A C++ implementation of the "Pokemon Simulation" that I first saw on /r/dataisbeautiful in [this post](https://www.reddit.com/r/dataisbeautiful/comments/5tfcym/a_simulation_of_360000_1_pixel_pokemon_fighting/) by /u/Morning_Fresh. I figured that a C++ implementation might run a little faster and be something fun to write. If you're not familiar, it is basically a simulation that gives a certain amount of "Pokemon" specific attributes and two "types" that fight and faint based on a damage formula with winners taking over the losers and gaining ground. The simulation ends when an entire "round" has gone by without a single instance of positive non-zero damage being done. Usually this means that there is one man standing although there are scenarios where there are multiple survivors and the winner goes to whomever holds more of the board.

## What You'll Need

This application currently is compiled in and for Windows using MinGW. I'm pretty sure you can just run the .exe without any DLL's (unlike Cygwin) but I honestly haven't tried. You will also need ffmpeg installed and on your path so that it will automatically turn the simulation into a .avi file once it finishes. You can find it [here](https://ffmpeg.org/).

## Installation

g++ -std=c++11 -o PokeSim main.cpp Pokemon.cpp Type.cpp TypeMap.cpp

## Run Parameters

-h        Print this output.

-d        Delete round .bmps after the .mp4 render finishes. (Default:No)

-c X      Run simulation with a X * X square. (Default:100)

-x X      Run simulation until round X. (Default:No Limit)

## Current Size

I have 16 GB of RAM and and 2000^2 is right around the maximum simulation that I can run without running into bad_alloc. The main data type is about 112 B but could probably be smaller. Your mileage may vary.

## Examples

Format health:attack:defense:speed type1-type2

A 100x100 won by a 4:6:8:2 Dragon-Grass type

![](https://github.com/alambley/PokeSim/blob/master/preview/a.gif?raw=true)

A 100x100 won by a 1:11:5:4 Ice-Flying type

[](https://github.com/alambley/PokeSim/blob/master/preview/b.gif?raw=true)
