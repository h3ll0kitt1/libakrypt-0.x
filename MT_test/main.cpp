#include <iostream>
#include <random>

int main()
{
    std::cout << "mt19937 from <random> " <<std::endl;
    std::mt19937 generator (5489);
    for (int i = 0; i < 9; i++)
    {
        std::cout <<  generator() << " ";
    }
    std::cout << std::endl;
}
