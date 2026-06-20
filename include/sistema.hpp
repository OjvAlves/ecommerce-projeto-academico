#ifndef SISTEMA_HPP
#define SISTEMA_HPP
#include "cliente.hpp"
#include "administrador.hpp"
#include "produto.hpp"
#include "pedido.hpp"
#include <vector>
#include <string>
/**
 * @class Sistema
 * @brief Classe centralizadora (Fachada) que gerencia as regras de negócio e fluxos da aplicação.
 *
 * Mantém o estado da sessão atual (se há administrador ou cliente logado),
 * o carrinho de compras ativo, e provê a interface operacional unificada
 * para busca, salvamento, remoção e atualização de todas as entidades do software.
 */
class Sistema {
public:
    Cliente clienteLogado;/**< Instância do cliente autenticado na sessão atual. */
    bool clienteLogadoFlag;/**< Indicador de existência de um cliente logado na sessão. */
    Administrador admLogado;/**< Instância do administrador autenticado na sessão atual. */
    bool admLogadoFlag;/**< Indicador de existência de um administrador logado na sessão. */
    Pedido carrinhoAtual;/**< Instância de pedido usada temporariamente como carrinho de compras. */
    bool carrinhoAtivo;/**< Controlador que dita se o carrinho possui compras em andamento. */
    /*** @brief Construtor da classe Sistema, inicializa o estado de sessões e flags zeradas. */
    Sistema();
    /*** @brief Gera incrementalmente um identificador ID inédito para novos cadastros de clientes.
* @return int Novo ID livre gerado. */
    int gerarIdCliente();
    /**
         * @brief Gera incrementalmente um identificador ID inédito para a inserção de novos produtos.
         * @return int Novo ID do produto livre.
         */
    int gerarIdProduto();
    /**
         * @brief Gera incrementalmente um código identificador unívoco para registro de novos pedidos.
         * @return int Novo código de pedido livre.
         */
    int gerarCodigoPedido();
    /**
         * @brief Adiciona um novo cliente e salva a alteração no armazenamento persistente.
         * @param c Instância do cliente montada a ser persistida.
         */
    void salvarCliente(const Cliente& c);
    /**
         * @brief Procura por um cliente registrado avaliando sua chave de username.
         * @param username String contendo o login do usuário procurado.
         * @param resultado Referência de saída onde o objeto encontrado será copiado caso tenha sucesso.
         * @return true Se o usuário for localizado, false caso contrário.
         */
    bool buscarClientePorUsername(const std::string& username, Cliente& resultado);
    /**
         * @brief Valida o login de um cliente associando suas credenciais de acesso.
         *
         * Caso o login seja bem-sucedido, popula internamente a variável clienteLogado e ativa a respectiva flag.
         * @param username Login informado.
         * @param senha Senha informada.
         * @return true Caso as credenciais coincidam com os registros, false caso contrário.
         */
    bool verificarLoginCliente(const std::string& username, const std::string& senha);
    /**
         * @brief Valida o login de um operador administrador associando suas credenciais de acesso.
         *
         * Caso obtenha sucesso, ativa as variáveis de sessão administrativa admLogado e ativa sua flag.
         * @param username Login administrativo informado.
         * @param senha Senha administrativa informada.
         * @return true Se o administrador for autenticado, false se falhar.
         */
    bool verificarLoginAdm(const std::string& username, const std::string& senha);
    /**
         * @brief Atualiza os metadados cadastrais de um cliente pré-existente (substituindo pelo ID correspondente).
         * @param c Objeto contendo os dados modificados a serem gravados.
         */
    void atualizarCliente(const Cliente& c);
    /**
         * @brief Cadastra um novo produto no catálogo geral e salva a lista atualizada.
         * @param p Instância do produto montada.
         */
    void salvarProduto(const Produto& p);
    /**
         * @brief Retorna uma cópia da lista completa de produtos cadastrados na loja.
         * @return std::vector<Produto> Vetor contendo todo o catálogo.
         */
    std::vector<Produto> listarProdutos();
    /**
         * @brief Busca por um produto específico utilizando seu código ID identificador.
         * @param id Identificador numérico do item.
         * @return Produto* Ponteiro apontando para a instância interna do produto, ou nullptr se não encontrado.
         */
    Produto* buscarProduto(int id);
    /**
         * @brief Substitui ou altera os parâmetros de um produto existente baseado em seu ID.
         * @param p Objeto Produto com as alterações integradas.
         */
    void atualizarProduto(const Produto& p);
    /**
         * @brief Exclui em definitivo um produto do catálogo e atualiza a persistência.
         * @param id Identificador numérico do item a remover.
         */
    void removerProduto(int id);
    /**
         * @brief Insere e grava permanentemente um pedido novo fechado no histórico da loja.
         * @param ped Pedido preenchido pronto a ser adicionado.
         */

    void salvarPedido(const Pedido& ped);
    /**
         * @brief Lista todos os pedidos pertencentes a um determinado cliente filtrados por seu estado.
         * @param idCliente ID do cliente dono das compras.
         * @param statusFiltro Código do status para filtragem (-1 lista todos independentemente de status).
         * @return std::vector<Pedido> Coleção de pedidos que atendem aos critérios estipulados.
         */
    std::vector<Pedido> listarPedidosCliente(int idCliente, int statusFiltro);
    /**
         * @brief Coleta e retorna a listagem global de todos os pedidos já feitos por todos os usuários.
         * @return std::vector<Pedido> Lista irrestrita com todos os pedidos gravados na plataforma.
         */
    std::vector<Pedido> listarTodosPedidos();
    /**
         * @brief Atualiza a situação de processamento ou valores de um pedido no arquivo.
         * @param p Pedido com as novas informações associadas ao mesmo código de identificação.
         */
    void atualizarPedido(const Pedido& p);
    /**
         * @brief Cria um relatório em formato humanizado .txt externo discriminando os detalhes de um pedido.
         *
         * Gera um arquivo contendo nomes dos produtos, preços, totais e dados cadastrais do cliente emissor.
         * @param codigoPedido Código do pedido alvo da exportação de registro.
         */
    void gerarRegistroTxt(int codigoPedido);

};

#endif
