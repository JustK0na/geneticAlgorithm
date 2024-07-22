#include "genotype.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>

#define POP_SIZE 10
#define GEN_SIZE 16
#define MUT_RATE 0.01


/*########################################
  Eval fun will be diffren for every case
##########################################*/
float eval(std::vector<Pop> &population){
    float fit =0;
    for(int i=0; i<(int)population.size(); i++){
        fit = 0;        
        for(int j=0; j<(int)population.at(i).chromosome.size(); j++){
            fit = fit+population.at(i).chromosome.at(j);
        }
        population.at(i).fitness = fit;
    }


    return fit;
};

int main(){

    std::vector<Pop> population;
    population = createPopulation(POP_SIZE, GEN_SIZE);
    eval(population);
    std::cout<<"\n\n\n\t\t Pierwsza Generacja: \n\n\n";
    showPopulation(population);
    float overalFitness = fitnessSum(population);
    std::cout<<"Overal fitness: "<<overalFitness<<std::endl;

    //for(int i=0; i<20; i++){
    int i=0;
    while(overalFitness<157){
        std::cout<<"Gen: "<<i+1<<std::endl;
        std::vector<Pop> Parents = rouletteWheelSelection(population, 0.3) ;
        std::cout<<"\n\nGeneration ["<<i+1<<"] Parents:\n";
        showPopulation(Parents);

        population = onePointCrossover(Parents, POP_SIZE);
        mutate(population, MUT_RATE);
        eval(population);
        overalFitness = fitnessSum(population);
        std::cout<<"\nGeneration ["<<i+1<<"]\n";
        showPopulation(population);
        i++;
    }  
        

    //}
    eval(population);
    std::cout<<"\n\n\n\t\tOstatnia generacja: \n\n\n";
    showPopulation(population);
    overalFitness = fitnessSum(population);
    std::cout<<"Overal fitness: "<<overalFitness<<" after "<< i << " generations"<<std::endl;

    return 0;
}