#ifndef __RANDOM_GENERATOR__
#define __RANDOM_GENERATOR__

class RandomGenerator {
public:
    static RandomGenerator *Instance() {
        if( s_pInstance == 0 ) {
            s_pInstance = new RandomGenerator();
        }
        return s_pInstance;
    }
    unsigned int Generate( int offset, int range ); // Returns [offset, offset + range)
    unsigned char GenerateUChar(); // Returns [0, 255]
    float GenerateFloat(); // Returns [0.0f, 1.0f]
    unsigned char *GenerateGridUChar( int size );
    float *GenerateGridFloat( int size );

private:
    RandomGenerator();
    ~RandomGenerator();

    static RandomGenerator *s_pInstance;
};

typedef RandomGenerator TheRandomGenerator;

#endif

