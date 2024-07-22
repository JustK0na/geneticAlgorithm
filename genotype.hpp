#ifndef GENOTYPE
#define GENOTYPE
#include <vector>


class Pop{
    public:
    std::vector<int> chromosome;
    float fitness;
    Pop();
    ~Pop();

};
std::vector<Pop> createPopulation(int nOfPop, int nOfGens);
void showPopulation(std::vector<Pop> population);
std::vector<Pop> simpleSelection(std::vector<Pop>, float);
std::vector<Pop> rouletteWheelSelection(std::vector<Pop>, float);
std::vector<Pop> onePointCrossover(std::vector<Pop>, int nOfPop);
std::vector<Pop> mutate(std::vector<Pop>&, float);
float fitnessSum(std::vector<Pop>);
#endif 