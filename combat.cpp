#include "combat.hpp"

// return +1 for army1 victory, -1 for army2 victory and 0 for no victory
// army sizes are updated in place as combat proceeds
int lets_battle(Army& army1, Army& army2,
                RandomManager& dice_roll, BattleModes bm)
{
    // while both armies are still alive
    // otherwise skip to the cleanup step
    while (!(army1.size() == 0 || army2.size() == 0))
    {
        std::vector<Dice> army1_rolls;
        std::vector<Dice> army2_rolls;
        
        // roll the dice for each soldier in each army
        // the dice pool contains an array of pre-generated
        // random numbers which are used up with each call to get_next()
        for (int i = 0; i < army1.hero; i++)
        {
            army1_rolls.push_back(Dice({dice_roll(DiceSize::D8), UnitType::Hero}));
        }
        for (int i = 0; i < army2.hero; i++)
        {
            army2_rolls.push_back(Dice({dice_roll(DiceSize::D8), UnitType::Hero}));
        }
        for (int i = 0; i < army1.normal; i++)
        {
            army1_rolls.push_back(Dice({dice_roll(DiceSize::D6), UnitType::Normal}));
        }
        for (int i = 0; i < army2.normal; i++)
        {
            army2_rolls.push_back(Dice({dice_roll(DiceSize::D6), UnitType::Normal}));
        }
        // line them up, largest array forwards and other backwards
        // then trim the longer of the two
        // we no longer care about the extra soldiers
        if (army1_rolls.size() >= army2_rolls.size())
        {
            std::sort(army1_rolls.rbegin(), army1_rolls.rend()); // {r}everse
            if (bm.relined)
            {
                std::sort(army2_rolls.rbegin(), army2_rolls.rend()); // {r}everse
            }
            else
            {
                std::sort(army2_rolls.begin(), army2_rolls.end()); // forward
            }
            
            // then we trim army1_rolls
            army1_rolls.resize(army2_rolls.size());
        }
        else // if (army2_rolls.size() > army1_rolls.size())
        {
            std::sort(army2_rolls.rbegin(), army2_rolls.rend()); // {r}everse
            if (bm.relined)
            {
                std::sort(army1_rolls.rbegin(), army1_rolls.rend()); // {r}everse
            }
            else
            {
                std::sort(army1_rolls.begin(), army1_rolls.end()); // forward
            }
            
            // then we trim army2_rolls
            army2_rolls.resize(army1_rolls.size());
        }

        // now the soldiers in each position battle off
        // the higher roll wins, and nothing happens on an equal roll
        for (int i = 0; i < army1_rolls.size(); i++)
        {
            if (army1_rolls[i].value > army2_rolls[i].value)
            {
                if (army2_rolls[i].type == UnitType::Hero)
                {
                    army2.hero -= 1;
                    if (army1.type.zombies)
                    {
                        army1.hero += 1;
                    }
                }
                else // (army2_rolls[i].type == UnitType::Normal)
                {
                    army2.normal -= 1;
                    if (army1.type.zombies)
                    {
                        army1.normal += 1;
                    }
                }
            }
            else if (army2_rolls[i].value > army1_rolls[i].value)
            {
                if (army1_rolls[i].type == UnitType::Hero)
                {
                    army1.hero -= 1;
                    if (army2.type.zombies)
                    {
                        army2.hero += 1;
                    }
                }
                else // (army1_rolls[i].type == UnitType::Normal)
                {
                    army1.normal -= 1;
                    if (army2.type.zombies)
                    {
                        army2.normal += 1;
                    }
                }
            }
        }
        
        if (bm.oneshot)
        {
            break;
        }
    }
    
    // work out the victor of the battle
    // and return a value representing that outcome
    int outcome = 0;
    if (army1.size() == 0)
    {
        outcome -= 1; // army2 has won
    }
    if (army2.size() == 0)
    {
        outcome += 1; // army1 has won
    }
   
    return outcome;
}
