#include "genotype.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
/*
#define POP_SIZE 10
#define GEN_SIZE 16
#define MUT_RATE 0.01*/


//00000011 11111100 00010011
/*########################################
  Eval fun will be diffren for every case
##########################################*/
float eval(std::vector<Pop> &population){
    std::vector<int> green={0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,1};
    float fit=0;
    for(int i=0; i<(int)population.size(); i++){
        fit =0;        
        for(int j=0; j<(int)population.at(i).chromosome.size(); j++){
            if(population.at(i).chromosome.at(j)==green.at(j)){
                fit++;
            }
            else{
                fit--;
            }
            
        }
        population.at(i).fitness = fit;
    }


    return fit;
};

int main(int argc, char **argv){

    int POP_SIZE = atof(argv[1]);
    //std::cout<<"POP_SIZE: "<<POP_SIZE<<"\n";
    int GEN_SIZE = atof(argv[2]);
    //std::cout<<"GEN_SIZE: "<<GEN_SIZE<<"\n";
    float MUT_RATE = atof(argv[3]);
    //std::cout<<"MUT_SIZE: "<<MUT_RATE<<"\n";


    std::vector<Pop> population;
    population = createPopulation(POP_SIZE, GEN_SIZE);
    eval(population);
    //std::cout<<"\n\n\n\t\t Pierwsza Generacja: \n\n\n";
    //showPopulation(population);
    float overalFitness = fitnessSum(population);
    //std::cout<<"Overal fitness: "<<overalFitness<<std::endl;

    //for(int i=0; i<20; i++){
    int i=0;
    int targetedFit = (GEN_SIZE * POP_SIZE*1);
    while(overalFitness<targetedFit){
        //std::cout<<"Gen: "<<i+1<<std::endl;
        //std::vector<Pop> Parents = rouletteWheelSelection(population, 0.3);
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<Pop> Parents = simpleSelection(population, 0.1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = end - start;
        //std::cout<<"Generating parents time: "<<dur.count()<<" ms\n";
        //std::cout<<"\n\nGeneration ["<<i+1<<"] Parents:\n";
        //showPopulation(Parents);

        population = onePointCrossover(Parents, POP_SIZE);
        mutate(population, MUT_RATE);
        eval(population);
        overalFitness = fitnessSum(population);
        //std::cout<<"\nGeneration ["<<i+1<<"]\n";
        //showPopulation(population);
        std::cout<<"Overal pop fit: "<<overalFitness<<"\t target pop fit: "<<POP_SIZE*GEN_SIZE<<" rate: "<<overalFitness/(POP_SIZE*GEN_SIZE)*100<<"%\n";
        i++;
        int bestID = bestIndividual(population);
        std::cout<<"Best individual from ["<<i<<"] generation:\t fit: "<<population.at(bestID).fitness<<"\n";
        for(int g=0; g<(int)population.at(bestID).chromosome.size();g++){
            std::cout<<population.at(bestID).chromosome.at(g)<<",";
        }
        std::cout<<std::endl;
        std::cout<<"How many best? ";
        float howManyBest=0;
        for(int g=0; g<(int)population.size();g++){
            if(population.at(g).fitness == 24)
                howManyBest++;
        }
        std::cout<<howManyBest/(float)population.size()*100<<"%\n";
    }  
        

    //}
    eval(population);
    //std::cout<<"\n\n\n\t\tOstatnia generacja: \n\n\n";
    //showPopulation(population);
    //overalFitness = fitnessSum(population);
    std::cout<</*"Overal fitness: "<<overalFitness<<" after "<< */i /*<< " generations"*/<<std::endl;

    return 0;
}