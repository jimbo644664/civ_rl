#ifndef    RANDOM_HPP_INCLUDED
#define    RANDOM_HPP_INCLUDED

#include <random>
#include <chrono>

#define abstract 0

enum class DiceSize
    : int
{
    D6,
    D8
};

class RandomManager
{
    public:
        RandomManager() {};
        
        virtual int operator()(DiceSize dc) = abstract;
        
        ~RandomManager() {};       
};

class StdRandomManager : public RandomManager
{
    public:
        StdRandomManager();
        
        virtual int operator()(DiceSize dc);
        
        ~StdRandomManager();
        
    protected:
        std::mt19937_64 generator; // Mersenne Twister 64-bit PRNG
        std::uniform_int_distribution<int> d6;
        std::uniform_int_distribution<int> d8;
};

#endif // RANDOM_HPP_INCLUDED
