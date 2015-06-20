#include "test.hpp"

int main(int argc, char** argv)
{
    int max_size = 15;
    int num_trials = 1000000;
    
    bool same_lines = true;
    bool one_battle = false;
    
    int num_hero_1 = 1;
    int num_hero_2 = 1;
    
    std::ostream* data = &std::cout;
    std::ostream* prog = &std::cerr;
    
    for (int i = 1; i <= max_size; i++) // Army 1 sizes
    {
        for (int j = 1; j <= i; j++) // Army 2 sizes
        {
            (*data) << "----------------------------------------"
                      << "----------------------------------------"
                      << std::endl;
            (*data) << "Army 1 size: " << i << std::endl;
            (*data) << "Army 2 size: " << j << std::endl;
            
            (*prog) << "Army 1 size: " << i << "\n";
            (*prog) << "Army 2 size: " << j << "\n";
            
            int army1_victories = 0;
            int army2_victories = 0;
            
            int army1_survivors = 0;
            int army2_survivors = 0;
            
            int army1_survivors_n = 0;
            int army2_survivors_n = 0;
            
            int army1_survivors_h = 0;
            int army2_survivors_h = 0;
            
            StdRandomManager rm;
            for (int trial = 1; trial <= num_trials; trial++)
            {
                Army army1((i-num_hero_1 > 0) ? i-num_hero_1 : 0, num_hero_1);
                Army army2((j-num_hero_2 > 0) ? j-num_hero_2 : 0, num_hero_2);
                
                int result = lets_battle(army1, army2, rm,
                                         {same_lines, one_battle});
                if (one_battle)
                {
                    army1_survivors += army1.size();
                    army2_survivors += army2.size();
                    
                    if (num_hero_1 || num_hero_2)
                    {
                        army1_survivors_n += army1.normal;
                        army2_survivors_n += army2.normal;
                        
                        army1_survivors_h += army1.hero;
                        army2_survivors_h += army2.hero;
                    }
                }
                else // if (!one_battle)
                {
                    if (result == 1)
                    {
                        army1_victories += 1;
                        army1_survivors += army1.size();
                        if (num_hero_1 || num_hero_2)
                        {
                            army1_survivors_n += army1.normal;
                            army1_survivors_h += army1.hero;
                        }
                    }
                    else if (result == -1)
                    {
                        army2_victories += 1;
                        army2_survivors += army2.size();
                        if (num_hero_1 || num_hero_2)
                        {
                            army2_survivors_n += army2.normal;
                            army2_survivors_h += army2.hero;
                        }
                    }
                }
                
                if ((trial % (num_trials/40)) == 0)
                {
                    (*prog) << ".";
                }
            }
            
            (*prog) << "\n";
            
            (*data) << "........................................" << std::endl;
            
            if (one_battle)
            {
                (*data) << "Average survivors of Army 1: "
                          << static_cast<float>(army1_survivors) /
                             static_cast<float>(num_trials)
                          << std::endl;
                (*data) << "Average survivors of Army 2: "
                          << static_cast<float>(army2_survivors) /
                             static_cast<float>(num_trials)
                          << std::endl;
                if (num_hero_1 || num_hero_2)
                {
                    (*data) << "Average hero survivors of Army 1: "
                              << static_cast<float>(army1_survivors_h) /
                                 static_cast<float>(num_trials)
                              << std::endl;
                    (*data) << "Average hero survivors of Army 2: "
                              << static_cast<float>(army2_survivors_h) /
                                 static_cast<float>(num_trials)
                              << std::endl;
                    
                    (*data) << "Average normal survivors of Army 1: "
                              << static_cast<float>(army1_survivors_n) /
                                 static_cast<float>(num_trials)
                              << std::endl;
                    (*data) << "Average normal survivors of Army 2: "
                              << static_cast<float>(army2_survivors_n) /
                                 static_cast<float>(num_trials)
                              << std::endl;
                }
            }            
            else // if (!one_test)
            {
                (*data) << "Probability Army 1 will win: "
                          << static_cast<float>(army1_victories) /
                             static_cast<float>(num_trials)
                          << std::endl;
                (*data) << "Probability Army 2 will win: "
                          << static_cast<float>(army2_victories) /
                             static_cast<float>(num_trials)
                          << std::endl;
                      
                (*data) << "Average survivors when Army 1 wins: "
                          << static_cast<float>(army1_survivors) /
                             static_cast<float>(army1_victories)
                          << std::endl;
                (*data) << "Average survivors when Army 2 wins: "
                          << static_cast<float>(army2_survivors) /
                             static_cast<float>(army2_victories)
                          << std::endl;
                if (num_hero_1 || num_hero_2)
                {
                    (*data) << "Average hero survivors when Army 1 wins: "
                              << static_cast<float>(army1_survivors_h) /
                                 static_cast<float>(army1_victories)
                              << std::endl;
                    (*data) << "Average hero survivors when Army 2 wins: "
                              << static_cast<float>(army2_survivors_h) /
                                 static_cast<float>(army2_victories)
                              << std::endl;
                    
                    (*data) << "Average normal survivors when Army 1 wins: "
                              << static_cast<float>(army1_survivors_n) /
                                 static_cast<float>(army1_victories)
                              << std::endl;
                    (*data) << "Average normal survivors when Army 2 wins: "
                              << static_cast<float>(army2_survivors_n) /
                                 static_cast<float>(army2_victories)
                              << std::endl;
                }
            }
        }
    }
}
