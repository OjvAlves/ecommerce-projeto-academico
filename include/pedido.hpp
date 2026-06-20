#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <vector>
#include <string>
#include "itemPedido.hpp"
/**
 * @class Pedido
 * @brief Representa a requisição de compra realizada por um cliente.
 *
 * Reúne uma listagem de itens pedidos, o valor total calculado, o status atual
 * de processamento da transação (carrinho, finalizado, pago, etc.) e os
 * identificadores de controle de faturamento.
 */
class Pedido {
private:
    int codigoPedido;
    int idCliente;
    float valorTotal;
    int status;
    std::vector<ItemPedido> itens;

public:
    /**
         * @brief Construtor padrão e parametrizado da classe Pedido.
         * @param codigoPedido Código identificador do pedido (padrão: 0).
         * @param idCliente ID do cliente associado (padrão: 0).
         * @param status Código de status inicial (padrão: 0).
         * @param valorTotal Valor financeiro computado inicial (padrão: 0.0f).
         */
    Pedido(int codigoPedido = 0, int idCliente = 0, int status = 0, float valorTotal = 0.0f);
    /**
         * @brief Serializa os metadados do pedido e sua lista de itens em uma string única complexa.
         * @return std::string Linha formatada englobando a sintaxe especial de chaves.
         */
    std::string toFormato() const;
    /**
         * @brief Reconstrói um Pedido completo e seus sub-itens por meio de um parser textual complexo.
         * @param linha String estruturada lida a partir do arquivo de registros.
         * @return Pedido Objeto re-hidratado com dados e lista de sub-itens populada.
         */
static Pedido fromFormato(const std::string& linha);
/**
     * @brief Obtém o código numérico identificador do pedido.
     * @return int Código do pedido.
     */
int getCodigoPedido() const;
/**
     * @brief Obtém o identificador do cliente proprietário do pedido.
     * @return int ID do cliente.
     */
    int getIdCliente() const;
    /**
         * @brief Informa o número total de itens distintos adicionados a este pedido.
         * @return int Quantidade de itens no vetor.
         */
    int getNumItens() const;
    /**
         * @brief Obtém o status do ciclo de vida atual do pedido.
         * @return int Código do status.
         */
    int getStatus() const;
    /**
         * @brief Retorna o somatório financeiro computado para o pedido.
         * @return float Preço total em Reais.
         */
    float getValorTotal() const;
    /**
         * @brief Define ou altera o código identificador deste pedido.
         * @param cod Novo código identificador.
         */
    void setCodigoPedido(int cod) {
        codigoPedido = cod;
     }
     /**
          * @brief Associa este pedido a um cliente específico via ID.
          * @param id ID do cliente correspondente.
          */
    void setIdCliente(int id) {
        idCliente = id; }
    /**
         * @brief Altera a situação ou estágio de processamento do pedido.
         * @param st Novo código de status.
         */
    void setStatus(int st) {
        status = st; }
    /**
         * @brief Define manualmente o valor monetário total do pedido.
         * @param v Valor total em float.
         */
    void setValorTotal(float v) {
        valorTotal = v; }
    /**
         * @brief Fornece acesso direto e modificável ao vetor interno de itens do pedido.
         *
         * Utilizado para inclusões, remoções ou edições diretas em nível de aplicação (ex: gerenciamento do carrinho).
         * @return std::vector<ItemPedido>& Referência mutável para a coleção de itens.
         */
     std::vector<ItemPedido>& getItensModificaveis() {
        return itens;  }
};

#endif
