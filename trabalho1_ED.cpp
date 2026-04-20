#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Pessoa
{
    std::string nome;
    std::string datas[3];
};

int chaveData(const std::string &d)
{
    const int pivot = 26;
    int dia = std::stoi(d.substr(0, 2));
    int mes = std::stoi(d.substr(2, 2));
    int ano = std::stoi(d.substr(4, 2));
    if (ano <= pivot)
        ano += 2000;
    else
        ano += 1900;
    return ano * 10000 + mes * 100 + dia;
}

int main()
{
    std::ifstream arquivoEntrada("input.txt");
    if (!arquivoEntrada.is_open())
    {
        arquivoEntrada.open("arquivo.txt");
    }

    if (!arquivoEntrada.is_open())
    {
        std::cerr << "Erro ao abrir arquivo de entrada (input.txt ou arquivo.txt)." << std::endl;
        return 1;
    }

    std::vector<Pessoa> listaPessoas;
    std::string linha;

    while (std::getline(arquivoEntrada, linha))
    {
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();

        if (linha.empty())
            continue;

        Pessoa p;
        int tam = static_cast<int>(linha.size());
        p.nome = linha.substr(0, tam - 18);
        p.datas[0] = linha.substr(tam - 18, 6);
        p.datas[1] = linha.substr(tam - 12, 6);
        p.datas[2] = linha.substr(tam - 6, 6);

        std::sort(p.datas, p.datas + 3, [](const std::string &a, const std::string &b)
                  { return chaveData(a) < chaveData(b); });
        listaPessoas.push_back(p);
    }

    arquivoEntrada.close();

    std::sort(listaPessoas.begin(), listaPessoas.end(), [](const Pessoa &a, const Pessoa &b)
              { return a.nome < b.nome; });

    std::ofstream arquivoSaida("resultado.txt");
    if (!arquivoSaida.is_open())
    {
        std::cerr << "Erro ao criar arquivo de saida." << std::endl;
        return 1;
    }

    for (const Pessoa &p : listaPessoas)
    {
        arquivoSaida << p.nome << " "
                     << p.datas[0].substr(0, 2) << "/" << p.datas[0].substr(2, 2) << "/" << p.datas[0].substr(4, 2) << " "
                     << p.datas[1].substr(0, 2) << "/" << p.datas[1].substr(2, 2) << "/" << p.datas[1].substr(4, 2) << " "
                     << p.datas[2].substr(0, 2) << "/" << p.datas[2].substr(2, 2) << "/" << p.datas[2].substr(4, 2) << "\n";
    }

    arquivoSaida.close();
    std::cout << "Processamento concluido. Verifique o arquivo 'resultado.txt'." << std::endl;

    return 0;
}