#ifndef __RANDOM_GENERATOR__
#define __RANDOM_GENERATOR__

class RandomGenerator {
public:
    RandomGenerator();
    ~RandomGenerator();
    unsigned int Generate( int offset, int range ); // Returns [offset, offset + range)
    unsigned char GenerateUChar(); // Returns [0, 255]
    float GenerateFloat(); // Returns [0.0f, 1.0f]
    unsigned char *GenerateGridUChar( int size );
    float *GenerateGridFloat( int size );
};

#endif

