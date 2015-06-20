#include "army.hpp"

Army::Army(int sz, int cn, ArmyModes am)
    : normal(sz), hero(cn), type(am)
{

}

int Army::size()
{
    return (normal + hero);
}

Army::~Army()
{

}

bool operator< (const Dice& lhs, const Dice& rhs)
{
    if (lhs.value == rhs.value)
    {
        if (lhs.type == UnitType::Normal && rhs.type == UnitType::Hero)
        {
            return true;
        }
    }
    return lhs.value < rhs.value;
}
