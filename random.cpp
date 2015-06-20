#include "random.hpp"

StdRandomManager::StdRandomManager()
    : d6(1, 6), d8(1, 8)
{
    using namespace std::chrono;
    
    high_resolution_clock::time_point beginning = high_resolution_clock::now();
    
    high_resolution_clock::time_point end = high_resolution_clock::now();
    high_resolution_clock::duration d = end - beginning;
    
    high_resolution_clock::time_point now = high_resolution_clock::now();
    now += d;
    
    int seed1 = now.time_since_epoch().count();
    generator.seed(seed1);
}

int StdRandomManager::operator()(DiceSize dc)
{
    switch (dc)
    {
        case DiceSize::D6:
            return d6(generator);
        case DiceSize::D8:
            return d8(generator);
        default:
            return -1;
    }
}

StdRandomManager::~StdRandomManager()
{

}
