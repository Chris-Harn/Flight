#include "RandomGenerator.h"

#include <iostream> // time
#include <cstdlib> // srand

RandomGenerator::RandomGenerator() {
    // Seed generator
    srand( ( unsigned ) time( nullptr ) );
}

RandomGenerator::~RandomGenerator() {

}

unsigned int RandomGenerator::Generate( int offset, int range ) {
    // Generates a number for a range...
    // offset - starting point for random number
    // range - the number of values between first 
    // and last possible random number
    // i.e. (1, 10) will generate a number between 1 and 10.
    // (0, 10) will generate a number between 0 and 9.
    return ( offset + ( rand() % range ) );
}

unsigned char RandomGenerator::GenerateHeight() {
    return ( rand() % 256 );
}