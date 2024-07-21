#include "genotype.hpp"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>

#define POP_SIZE 10
#define GEN_SIZE 16
#define MUT_RATE 0.1


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
/*###################################
Z jakiegoś powodu mutacja kompletnie
nie działa. Gdy MUT_RATE dąży do 0
(w szczególności mniejsze niż 0.1)
jakość populacji spada do PRAWIE całkiem
losowej. Dodatkowo MUT_RATE = 0 działa
jak gdyby mutacje zachodziły zawsze.
Dla tego prostego przykładu MUT_RATE = 0
powinien oznaczać, że znajdziemy idealną
odpowiedź, a tak nie jest.
Może to być też wina onePointCrossover.
Co.
stop.
jednak działa poprawnie?
dla innego seed'a losowego niż 420
Nie ważne wszystko ok, ale szkoda
mi takiego długiego i ładnego
komentarza.
#####################################*/
int main(){

    std::vector<Pop> population;
    population = createPopulation(POP_SIZE, GEN_SIZE);
    eval(population);
    std::cout<<"\n\n\n\t\t Pierwsza Generacja: \n\n\n";
    showPopulation(population);
    float overalFitness = fitnessSum(population);
    std::cout<<"Overal fitness: "<<overalFitness<<std::endl;

    for(int i=0; i<100; i++){
        //std::cout<<"Gen: "<<i<<std::endl;
        eval(population);
        std::vector<Pop> Parents = selectParents(population, 0.3);
        population = onePointCrossover(Parents, POP_SIZE);
        mutate(population, MUT_RATE);

    }
    eval(population);
    std::cout<<"\n\n\n\t\tOstatnia generacja: \n\n\n";
    showPopulation(population);
    overalFitness = fitnessSum(population);
    std::cout<<"Overal fitness: "<<overalFitness<<std::endl;

    return 0;
}