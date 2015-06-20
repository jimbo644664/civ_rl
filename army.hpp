#ifndef   ARMY_HPP_INCLUDED
#define   ARMY_HPP_INCLUDED

struct ArmyModes
{
    bool zombies;
};

enum class UnitType
{
    Normal,
    Hero
};

struct Dice
{
    int value;
    UnitType type;
    
    friend bool operator<(const Dice& lhs, const Dice& rhs);
};

class Army
{
    public:
        Army() = delete;
        explicit Army(int sz, int cn = 0, ArmyModes am = {false});
        
        ~Army();
    
        int normal; // Size of normal
        int hero; // Size of hero
        
        int size();
        
        ArmyModes type;
};

#endif // ARMY_HPP_INCLUDED
