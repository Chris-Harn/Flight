#ifndef __RANDOM_GENERATOR__
#define __RANDOM_GENERATOR__

class RandomGenerator {
public:
    RandomGenerator();
    ~RandomGenerator();
    unsigned int Generate( int offset, int range ); // Returns [offset, offset + range)
    unsigned char GenerateHeight(); // Returns [0, 255]
};

#endif

