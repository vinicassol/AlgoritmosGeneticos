//
//  main.cpp
//  Geneticos
//
//  Created by Vini Cassol on 14/03/21.
//

#include <time.h>
#include "Populacao.hpp"

void Selecao(Populacao &p, Individuo &primeiro, Individuo &segundo)
{
    //Seleciona o individuo mais fit
    primeiro = p.GetFittest();

    //Seleciona o segundo mais fit
    segundo = p.GetSegundoFittest();
}

void Crossover(Individuo &primeiro, Individuo &segundo)
{
    //Sorteia o ponto de crossover
    int crossOverPoint = rand() % primeiro.GetQtdGenes();

    //Troca os valores dos genes
    for (int i = 0; i < crossOverPoint; i++)
    {
        int temp = primeiro.genes[i];
        primeiro.genes[i] = segundo.genes[i];
        segundo.genes[i] = temp;
    }
}

void Mutacao(Individuo &primeiro, Individuo &segundo)
{
    
    //Sorteia um ponto de mtacao
    int mutationPoint = rand()%primeiro.GetQtdGenes();

    //Inverte o valor naquele ponto
    if (primeiro.genes[mutationPoint] == 0) {
        primeiro.genes[mutationPoint] = 1;
    } else {
        primeiro.genes[mutationPoint] = 0;
    }

    mutationPoint = rand()%primeiro.GetQtdGenes();

    if (segundo.genes[mutationPoint] == 0) {
        segundo.genes[mutationPoint] = 1;
    } else {
        segundo.genes[mutationPoint] = 0;
    }
}


int main()
{
    srand (time(0));
    
   
    Individuo primeiroFit;
    Individuo segundoFit;
    
    //Gerar Populacao Inicial
    int numGenes = 4;
    Populacao populacao(5, numGenes); // 10 individuos, com 5 genes cada
    int contGeracao = 0;
    
    // Calcular Fitness
    populacao.CalcularFitnessIndividuos();
    cout << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << endl;
   
    //Enquanto nao convergir
    while(populacao.GetFittestValue() < numGenes)
    {
        contGeracao++;
        
        //Seleção
        Selecao(populacao, primeiroFit, segundoFit);
        
        //Crossover
        Crossover(primeiroFit, segundoFit);
        
        //Aplica Mutação considerando percentual
        if (rand()%7 < 5)
            Mutacao(primeiroFit, segundoFit);
        
         //Adiciona o mais saudavel na populacao, no lugar do menos fit
        primeiroFit.CalcularFitness();
        segundoFit.CalcularFitness();

        //Verifica o mais fit da nova geracao e insere na populacao
        if (primeiroFit.GetFitness() > segundoFit.GetFitness())
            populacao.individuos[populacao.GetPosMenosFittest()] = primeiroFit;
        else
            populacao.individuos[populacao.GetPosMenosFittest()] = segundoFit;
         
        
        //Calcular fitness
        populacao.CalcularFitnessIndividuos();
        cout << "Geração " << contGeracao << " - Maior Fit: " << populacao.GetFittestValue() << endl;
    }
    
    cout << "Solucionado na geracao " << contGeracao << ", com fitness: " << populacao.GetFittestValue() << endl;
    
    return 0;
}
