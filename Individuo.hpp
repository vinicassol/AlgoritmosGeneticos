//  Individuo.hpp
//  Geneticos
//
//  Created by Vini Cassol on 14/03/21.
//

#include <iostream>
using namespace std;

class Individuo
{
public:
    Individuo();
    void SetupIndividuo(int qtdGenes);
    void CalcularFitness();
    int GetFitness();
    int GetQtdGenes();
    int *genes;
    
private:
    int fitness;
    int qtdGenes;
};
