#ifndef PERSISTENCIA_HPP
#define PERSISTENCIA_HPP
#include <vector>
#include <string>
#include "cliente.hpp"
#include "administrador.hpp"
#include "produto.hpp"
#include "pedido.hpp"
/**
 * @class Persistencia
 * @brief Classe estática de infraestrutura responsável pelo I/O de arquivos de dados.
 *
 * Centraliza os métodos de carga e descarga de vetores de entidades da aplicação
 * de/para arquivos texto persistidos em disco.
 */
class Persistencia {
public:
    /**
         * @brief Lê o arquivo de clientes e converte os registros em um vetor de objetos Cliente.
         * @return std::vector<Cliente> Lista de clientes carregada.
         */
    static std::vector<Cliente> carregarClientes();
    /**
         * @brief Sobrescreve o arquivo de clientes salvando a coleção atualizada de dados.
         * @param dados Vetor com todos os clientes em memória a serem gravados.
         */
    static void salvarClientes(const std::vector<Cliente>& dados);
    /**
         * @brief Lê o arquivo de administradores convertendo as linhas para objetos Administrador.
         * @return std::vector<Administrador> Lista de administradores cadastrados.
         */
    static std::vector<Administrador> carregarAdmins();
    /**
         * @brief Persiste a lista de administradores fornecida de volta no respectivo arquivo.
         * @param dados Vetor de administradores a salvar.
         */
    static void salvarAdmins(const std::vector<Administrador>& dados);
    /**
         * @brief Lê o arquivo de catálogo e popula um vetor de entidades Produto.
         * @return std::vector<Produto> Catálogo de produtos carregado.
         */
    static std::vector<Produto> carregarProdutos();
    /**
         * @brief Salva a lista consolidada do catálogo de produtos no arquivo de persistência.
         * @param dados Coleção contendo os produtos.
         */
    static void salvarProdutos(const std::vector<Produto>& dados);
    /**
         * @brief Lê e decodifica o histórico/estado geral de pedidos armazenados em disco.
         * @return std::vector<Pedido> Vetor contendo a totalidade dos pedidos indexados.
         */
    static std::vector<Pedido> carregarPedidos();
    /**
         * @brief Salva a totalidade das movimentações de pedidos de volta no banco texto.
         * @param dados Vetor com os pedidos atualizados.
         */
    static void salvarPedidos(const std::vector<Pedido>& dados);

private:
    /**
         * @brief Abre um arquivo para leitura e coleta todas as linhas válidas preenchidas.
         * @param nome Caminho ou nome do arquivo em disco.
         * @return std::vector<std::string> Vetor onde cada entrada é uma linha crua lida.
         */
    static std::vector<std::string> lerLinhas(const std::string& nome);
    /**
         * @brief Abre um arquivo em modo de escrita, descarregando um lote de linhas de texto.
         * @param nome Caminho ou nome do arquivo destino.
         * @param linhas Lote de strings prontas a serem gravadas uma por linha.
         */
    static void escreverLinhas(const std::string& nome, const std::vector<std::string>& linhas);
};

#endif
