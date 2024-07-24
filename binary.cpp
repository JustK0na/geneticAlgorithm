#include <iostream>
#include <vector>
#include <cmath>

#define INTSIZE 8


int main(){

    std::vector<int> binary={0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1};
    for(int i=0; i<(int)binary.size(); i++){
        std::cout<<binary.at(i)<<" ";
    }
    std::cout<<std::endl;

    int vectSize;
    vectSize = binary.size()/INTSIZE;
    //std::cout<<vectSize<<std::endl;
    std::vector<int> decimal;
    int tmpDec=0;
    std::cout<<"\n\n\n";
    for(int i=0; i<(int)binary.size(); i++){
        
        if(binary.at(binary.size()-i-1))
            tmpDec = tmpDec + pow(2,i%INTSIZE);
            
        if(i%INTSIZE==INTSIZE-1){
            decimal.insert(decimal.begin(), tmpDec);    
            tmpDec=0;
        }
        std::cout<<tmpDec<<" \n";
    }
    std::cout<<"\n\n\n";
    for(int i=0; i<(int)decimal.size(); i++){
        std::cout<<decimal.at(i)<<" ";
    }
    std::cout<<std::endl;
    return 0;
}