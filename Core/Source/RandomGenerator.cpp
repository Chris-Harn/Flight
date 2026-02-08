#include "RandomGenerator.h"

#include <iostream> // time
#include <cstdlib> // srand


RandomGenerator *RandomGenerator::s_pInstance = 0;

RandomGenerator::RandomGenerator() {
    // Seed generator
    srand( (unsigned)time( nullptr ) );
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

unsigned char RandomGenerator::GenerateUChar() {
    return ( rand() % 256 );
}

float RandomGenerator::GenerateFloat() {
    return (float)( rand() / (float)( RAND_MAX ) );
}

unsigned char *RandomGenerator::GenerateGridUChar( int size ) {
    int area = size * size;
    unsigned char *data = new unsigned char[area];

    for( int i = 0; i < area; i++ ) {
        data[i] = GenerateUChar();
    }

    return data;
}

float *RandomGenerator::GenerateGridFloat( int size ) {
    int area = size * size;
    float *data = new float[area];

    for( int i = 0; i < area; i++ ) {
        data[i] = GenerateFloat();
    }

    return data;
}