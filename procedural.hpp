#pragma once

///Procedural generation class
/**
*Coordinate dependant procedural generation class that doesn't use rand() or srand(), because those are a buggy mess
*
*Most of the code is shamelessly stolen from this video: https://www.youtube.com/watch?v=ZZY9YE7rZJw
*/

class Procedural
{
    unsigned int globalSeed;
    const int x,y;
    unsigned int generate(unsigned int seed)
    {
        seed += (x * 0x1f1f1f1f) ^ y;
        seed += 0xe120fc15;
        unsigned long long tmp;
        tmp = (unsigned long long)seed * 0x4a39b70d;
        unsigned int m1 = (tmp >> 32) ^ tmp;
        tmp = (unsigned long long)m1 * 0x12fad5c9;
        return (tmp >> 32) ^ tmp;
    }
public:
    ///Default constructor.
    /**Uses seed 0 at coordinates 0,0*/
    Procedural() : globalSeed(0), x(0), y(0) {};
    ///Uses seed 0 with set coordinates.
    /** **Parameters**:\n
        int x: x coordinate\n
        int y: y coordinate*/
    Procedural(int x, int y) : globalSeed(0), x(x), y(y) {};
    ///Uses set seed.
    /** **Parameters**\n
        unsigned int seed: starting seed\n
        int x: x coordinate\n
        int y: y coordinate*/
    Procedural(unsigned int seed, int x, int y) : globalSeed(seed), x(x), y(y) {};

    ///Generates a number, using previous number as seed.
    /** **Returns** a random number*/
    int rand() {return globalSeed = generate(globalSeed);}
    ///Generates consistent number based on the current seed.
    /** **Returns** a constant random number*/
    int proc() {return generate(globalSeed);}
};
