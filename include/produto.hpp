#ifndef PRODUTO_HPP
#define PRODUTO_HPP
#include <string>
/**
 * @class Produto
 * @brief Representa um item comercializável contido no estoque da loja.
 *
 * Gerencia as propriedades de precificação, nome descritivo, controle de
 * quantidades em estoque e conversão para persistência.
 */
class Produto {
    private:
     int id; /**< Identificador numérico do produto. */
     std::string nome; /**< Nome comercial do produto. */
     double valor; /**< Valor/Preço unitário em Reais. */
     int qtdEstoque; /**< Quantidade de unidades disponíveis em estoque. */

    public:
/**
* @brief Construtor padrão e parametrizado da classe Produto.
* @param id Identificador único do produto (padrão: 0).
* @param nome Nome do produto (padrão: vazio).
* @param valor Preço em double (padrão: 0.0).
* @param qtd Unidades iniciais físicas em estoque (padrão: 0).
*/
        Produto(int id = 0, const std::string& nome = "", double valor = 0.0, int qtd = 0);
 /**
* @brief Formata as variáveis de estado do produto em padrão textual separado por pipe.
* @return std::string String serializada.
*/
        std::string toFormato() const;
/**
* @brief Instancia um novo Produto mapeando os termos extraídos de uma linha lida.
* @param linha Linha de registro oriunda do arquivo de banco de dados.
* @return Produto Objeto montado.
*/
        static Produto fromFormato(const std::string& linha);
        /**
                 * @brief Retorna o identificador numérico do produto.
                 * @return int ID do produto.
                 */
        int getId() const;
        /**
                 * @brief Retorna o nome atribuído ao produto.
                 * @return const std::string& Referência para a string do nome.
                 */
        const std::string& getNome() const;
        /**
                 * @brief Retorna o valor monetário unitário do produto.
                 * @return double Preço unitário.
                 */
        double getValor() const;
        /**
                 * @brief Informa o saldo disponível em estoque para venda deste item.
                 * @return int Quantidade estocada.
                 */
        int getQtdEstoque() const;
        /**
                 * @brief Atualiza a quantidade física do produto em estoque.
                 * @param novaQtd Nova quantidade disponível absoluta.
                 */
        void setQtdEstoque(int novaQtd) {
            qtdEstoque = novaQtd;
        }
        /**
                 * @brief Altera a descrição/nome comercial atribuída ao item.
                 * @param n Novo nome da mercadoria.
                 */
        void setNome(const std::string& n);
        /**
                 * @brief Altera a precificação unitária associada ao produto.
                 * @param v Novo valor unitário em double.
                 */
        void setValor(double v);
};

#endif
