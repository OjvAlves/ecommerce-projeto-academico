#ifndef ITEM_PEDIDO_HPP
#define ITEM_PEDIDO_HPP
#include <string>
/**
 * @class ItemPedido
 * @brief Representa uma unidade de produto vinculada a um pedido de compra.
 *
 * Modela a associação de um produto específico identificado por seu ID
 * e a respectiva quantidade que foi selecionada para aquisição.
 */
class ItemPedido {
private:
    int id; /**< Identificador do produto que compõe este item. */
    int quantidade; /**< Quantidade pedida do produto. */

public:
    /**
       * @brief Construtor padrão e parametrizado da classe ItemPedido.
       * @param id Identificador do produto (padrão: 0).
       * @param quantidade Quantidade selecionada (padrão: 0).
       */
    ItemPedido(int id = 0, int quantidade = 0);
    /**
       * @brief Converte o item de pedido em uma string formatada para salvamento conjunto.
       * @return std::string Texto estruturado no formato "{id|quantidade}".
       */
  std::string toFormato() const;
  /**
     * @brief Cria uma instância de ItemPedido interpretando um bloco de texto formatado.
     * @param linha Bloco textual contendo os dados do item.
     * @return ItemPedido Objeto preenchido com as informações extraídas.
     */
  static ItemPedido fromFormato(const std::string& linha);
  /**
     * @brief Recupera a quantidade de unidades deste item.
     * @return int Quantidade selecionada.
     */
   int getQuantidade() const;
   /**
      * @brief Obtém o identificador do produto associado a este item.
      * @return int ID do produto.
      */
   int getId() const;
   /**
      * @brief Modifica a quantidade selecionada do produto.
      * @param novaQtd Nova quantidade requisitada.
      */
   void setQuantidade(int novaQtd) {
        quantidade = novaQtd;
    }
};

#endif
