#ifndef   COMBAT_HPP_INCLUDED
#define   COMBAT_HPP_INCLUDED

#include <vector>
#include <algorithm>

#include "random.hpp"
#include "army.hpp"

struct BattleModes
{
    bool relined;
    bool oneshot;
};

int lets_battle(Army& army1_size, Army& army2_size,
                RandomManager& dice_pool, BattleModes bm = {false, false});

#endif // COMBAT_HPP_INCLUDED
