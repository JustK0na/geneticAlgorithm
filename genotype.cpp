#include "genotype.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>

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

std::vector<Pop> simpleSelection(std::vector<Pop> population, float nOfBest){
    std::vector<Pop> parents;

    std::sort(population.begin(), population.end(), customSort);
    for(int i=0; i<(int)population.size()*nOfBest; i++){
        parents.push_back(population.at(i));

    }
    
    return parents;
}


std::vector<Pop> rouletteWheelSelection(std::vector<Pop> population, float nOfBest){
    std::vector<Pop> parents;
    std::vector<float> chanceVector;
    double sumFitnness = 0;
    

    for(int j=0; j<(int)population.size(); j++){
        sumFitnness += pow(population.at(j).fitness,4);
        chanceVector.push_back(pow(population.at(j).fitness,4));
    }
    std::mt19937 rng(SEED);
    std::uniform_int_distribution<std::mt19937::result_type> rNumPar(0, sumFitnness);
    int i=0;
    int randomNumber = rNumPar(rng);

    while((int)parents.size()<(int)population.size()*nOfBest){
        //std::cout<<std::endl<<randomNumber;
        randomNumber = rNumPar(rng);
        for(int j=0; j<(int)population.size();j++){
            if(randomNumber < chanceVector.at(j)){
                parents.push_back(population.at(j));
                std::cout<<"Parent's choosen fitness: "<<population.at(j).fitness<<", chance: "<<chanceVector.at(j)/sumFitnness*100<<"% \n";                
                break;
            }
            else
                randomNumber = randomNumber - chanceVector.at(i);
        }            
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
        int a=rNumPar(rng);
        Pop parent1 = parents.at(a);
        int b = rNumPar(rng);
        while(b==a){
            b = rNumPar(rng);
        }

        Pop parent2 = parents.at(b);
        int randomPoint = rNumPoi(rng);

        Pop tmpChild;
        tmpChild.chromosome.reserve(parent1.chromosome.size());
        tmpChild.chromosome.insert(tmpChild.chromosome.end(), parent1.chromosome.begin(), parent1.chromosome.begin()+randomPoint);
        tmpChild.chromosome.insert(tmpChild.chromosome.end(), parent2.chromosome.begin()+randomPoint, parent2.chromosome.end());
        children.push_back(tmpChild);

        std::cout<<"Crossover here: "<<randomPoint<<"\n";
        std::cout<<"Parent 1:\n";
        for(int i=0; i<(int)parent1.chromosome.size(); i++)
            std::cout<<"{"<<parent1.chromosome.at(i)<<"}";
        std::cout<<"\t fit: "<<parent1.fitness<<std::endl;
        std::cout<<"Parent 2:\n";
        for(int i=0; i<(int)parent2.chromosome.size(); i++)
            std::cout<<"{"<<parent2.chromosome.at(i)<<"}";
        std::cout<<"\t fit: "<<parent2.fitness<<std::endl;
        std::cout<<"Child:\n";
        for(int i=0; i<(int)parent2.chromosome.size(); i++)
            std::cout<<"{"<<tmpChild.chromosome.at(i)<<"}";
        std::cout<<"\t fit: "<<tmpChild.fitness<<std::endl;
    }

    newGeneration.reserve(children.size()+parents.size());
    newGeneration.insert(newGeneration.end(), parents.begin(), parents.end());
    newGeneration.insert(newGeneration.end(), children.begin(), children.end());
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









