#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::vector<std::map<int, double>> contagens; // Faz o mapeamento número de processos -> probabilidade de ocorrência
std::vector<double> rhos; // Rho's de cada trace da amostra
std::map<int, double> medias, esperancaQuadrado, variancias; // Estatísticas de cada número de processos
double mediaRho = 0.0, esperancaQuadradoRho = 0.0, varianciaRho = 0.0; // Análogo ao anterior para o rho

void plotaHistogramaRho()
{
    plt::hist(rhos, 10, "darkmagenta", 1.0, false, {{"edgecolor", "black"}});
    
    /* Printa a linha que representa a média */
    
    plt::axvline(mediaRho, 0.0, std::numeric_limits<float>::max(), {{"color", "#74ff74"}, {"linestyle", "--"}, {"label", "Média"}});

    plt::xlabel("$\\rho$");
    plt::ylabel("Probabilidade de ocorrência");

    plt::title("Histograma de $\\rho$");

    plt::legend();

    plt::show();
}

void plotaPDFCDF(const std::vector<double>& numProcessos, const std::vector<double>& densidade)
{
    std::vector<double> funcaoAcumuladaNumeros(densidade.size());

    std::partial_sum(densidade.begin(), densidade.end(), funcaoAcumuladaNumeros.begin());

    plt::plot(numProcessos, densidade, {{"drawstyle", "steps-post"}, {"label" , "PDF simulada"}});

    plt::xlabel("Número de processos na fila");
    plt::ylabel("Probabilidade de ocorrência");

    plt::title("PDF do número de processos na fila");

    plt::legend();

    plt::show();

    plt::plot(numProcessos, funcaoAcumuladaNumeros, {{"drawstyle", "steps-post"}, {"label" , "CDF simulada"}});

    plt::xlabel("Número de processos na fila");
    plt::ylabel("Probabilidade de ocorrência");

    plt::title("CDF do número de processos na fila");

    plt::legend();

    plt::show();
}

void contabilizaAmostras(const int& tamanhoAmostra, const std::string& diretorioArquivos)
{
    for (int i = 1 ; i <= tamanhoAmostra ; i++) // Para cada elemento da amostra, iremos guardar o número de processos e sua probabilidade de ocorrência
    {
        std::string linha;
        std::string nomeArq = diretorioArquivos;
        nomeArq += std::to_string(i);

        std::ifstream arquivo = std::ifstream(nomeArq);
        std::map<int, double> contagem;

        int numProcessos = 0;

        while (std::getline(arquivo, linha))
        {
            contagem[std::stoi(linha)]++;
            numProcessos++;
        }
        
        for (auto& c : contagem)
            contagem[c.first] = c.second / static_cast<double>(numProcessos);

        contagens.push_back(contagem);
        rhos.push_back(1 - contagem.at(0));
        
        arquivo.close();
    }
}

int main(int argc, char** argv)
{
    std::vector<double> numProcessos, densidade;
    std::string caminho = "./trace";

    if (argc >= 3)
        caminho = std::string(argv[2]);

    contabilizaAmostras( std::stoi( std::string(argv[1]) ), caminho );
    
    for (const auto& amostra : contagens) // Calcula E(X) e E(X^2) para cada quantidade de processos
    {
        for (const auto& processos : amostra)
        {
            medias[processos.first] += processos.second;
            esperancaQuadrado[processos.first] += (processos.second * processos.second);
        }        
    }

    for (const auto& rho : rhos) // Análogo ao anterior
    {
        mediaRho += rho;
        esperancaQuadradoRho += (rho * rho);
    }

    mediaRho /= rhos.size();
    esperancaQuadradoRho /= rhos.size();
    varianciaRho = esperancaQuadradoRho - (mediaRho * mediaRho);

    for (const auto& media : medias)
    {
        medias[media.first] /= contagens.size();
        esperancaQuadrado[media.first] /= contagens.size();
        variancias[media.first] = esperancaQuadrado.at(media.first) - (medias.at(media.first) * medias.at(media.first));

        numProcessos.push_back(media.first);
        densidade.push_back(medias.at(media.first));
    }

    std::cout << "Média/variância de rho: " << mediaRho << "/" << varianciaRho << std::endl << std::endl;

    for (const auto& media : medias)
    {
        std::cout << "Média de " << media.first << " processos na fila: " << media.second << std::endl;
        std::cout << "Variância de " << media.first << " processos na fila: " << variancias.at(media.first) << std::endl;
        std::cout << std::endl;
    }

    plotaPDFCDF(numProcessos, densidade);
    plotaHistogramaRho();

    return 0;
}