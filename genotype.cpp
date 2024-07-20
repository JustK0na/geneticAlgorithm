#include "genotype.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

//#define SEED 13
#define SEED (std::chrono::system_clock::now().time_since_epoch().count())

Pop::Pop():fitness(0){};
Pop::~Pop(){};

/*Can add binary and real values as genes just two cases in that function*/
std::vector<Pop> createPopulation(int nOfPop, int nOfGens){
    std::vector<Pop> population;
    std::mt19937 rng(SEED);
    std::bernoulli_distribution dist(0.5);
    //std::cout<<"TEST1"<<std::endl;
    for(int i=0; i<nOfPop; i++){
        Pop tmpPop;
        population.push_back(tmpPop);
        //std::cout<<"TEST2"<<std::endl;
        std::vector<int> chromosomeLocal;
        for(int j=0; j<nOfGens; j++){
            //std::cout<<"TEST3"<<std::endl;
            int gene = dist(rng);
            chromosomeLocal.push_back(gene);
        }
        population.at(i).chromosome = chromosomeLocal;
        //std::cout<<"TEST4"<<std::endl;
    }    
    
    return population;
};

void showPopulation(std::vector<Pop> population){
    for(int i=0; i<(int)population.size(); i++){
        std::cout<<"individual["<<i<<"]: "<<"\n\t";
        for(int j=0; j<(int)population.at(i).chromosome.size(); j++){
            std::cout<<"{"<<population.at(i).chromosome.at(j)<<"}";
        }
        std::cout<<"\t Fit: "<<population.at(i).fitness;
        std::cout<<"\n";
    }
};

float fitnessSum(std::vector<Pop> population){
    float allFirnes=0;
    for(int i=0; i<(int)population.size(); i++){
        allFirnes += population.at(i).fitness;
    }
    return allFirnes;
}

bool customSort(Pop a, Pop b){
    return a.fitness>b.fitness;
}

std::vector<Pop> selectParents(std::vector<Pop> population, float nOfBest){
    std::vector<Pop> parents;

    std::sort(population.begin(), population.end(), customSort);
    for(int i=0; i<(int)population.size()*nOfBest; i++){
        parents.push_back(population.at(i));
     //   std::cout<<"Osobnik fitnes z rodzicow: "<<population.at(i).fitness<<"\n";
    }

    return parents;
};

std::vector<Pop> onePointCrossover(std::vector<Pop> parents, int nOfPop){
    std::vector<Pop> children;
    std::vector<Pop> newGeneration;
    std::mt19937 rng(SEED);
    std::uniform_int_distribution<std::mt19937::result_type> rNumPar(0, (int)parents.size()-1);
    std::uniform_int_distribution<std::mt19937::result_type> rNumPoi(1, (int)parents.at(0).chromosome.size()-1);
    
    while((int)(children.size()+parents.size()) < nOfPop){
        //std::cout<<"TEST1\n";
        int a=rNumPar(rng);
        Pop parent1 = parents.at(a);
        a = rNumPar(rng);
        Pop parent2 = parents.at(a);
        int randomPoint = rNumPoi(rng);
        //std::cout<<"TEST2: random point:"<<randomPoint<<"\n";

        Pop tmpChild;
        //std::cout<<"TEST3\n";
        tmpChild.chromosome.reserve(parent1.chromosome.size());
        //std::cout<<"TEST4\n";
        tmpChild.chromosome.insert(tmpChild.chromosome.end(), parent1.chromosome.begin(), parent1.chromosome.begin()+randomPoint);
        //std::cout<<"TEST5\n";
        tmpChild.chromosome.insert(tmpChild.chromosome.end(), parent2.chromosome.begin()+randomPoint, parent2.chromosome.end());
        //std::cout<<"TEST6\n";
        children.push_back(tmpChild);
        //std::cout<<"TEST7\n";
              
    }

    newGeneration.reserve(children.size()+parents.size());
    //std::cout<<"TEST8\n";
    newGeneration.insert(newGeneration.end(), parents.begin(), parents.end());
    //std::cout<<"TEST9\n";
    newGeneration.insert(newGeneration.end(), children.begin(), children.end());
    //std::cout<<"TEST10\n";
    return newGeneration;
};

std::vector<Pop> mutate(std::vector<Pop> &population, float mutRate){

    std::mt19937 rng(SEED);
    std::bernoulli_distribution dist(mutRate);

    for(int i=0; i<(int)population.size(); i++){
        for(int j=0; j<(int)population.at(i).chromosome.size(); j++){
            //std::cout<<"Bruh(?) i: "<<i<<",  j: "<<j<<std::endl;
            if(dist(rng)){
                if(population.at(i).chromosome.at(j)){
                    population.at(i).chromosome.at(j)=0;
                }
                else{
                    population.at(i).chromosome.at(j)=1;
                }
            }
        }
    }

    return population;
};









