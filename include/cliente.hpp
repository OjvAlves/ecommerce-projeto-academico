#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <string>
/**
 * @class Cliente
 * @brief Representa um cliente cadastrado na plataforma.
 *
 * Esta classe armazena as informações cadastrais e credenciais de um cliente,
 * além de prover os métodos de acesso (getters), modificação (setters) e
 * suporte à persistência de dados.
 */
class Cliente {
    private:
        int id; /**< Identificador único do cliente. */
        std::string nome; /**< Nome completo do cliente. */
        std::string email; /**< Endereço de e-mail do cliente. */
        std::string username; /**< Nome de usuário para login. */
        std::string senha; /**< Senha do cliente. */

    public:
        /**
        * @brief Construtor padrão e parametrizado da classe Cliente.
        * @param id Identificador único (padrão: 0).
        * @param nome Nome completo do cliente (padrão: vazio).
        * @param email E-mail do cliente (padrão: vazio).
        * @param username Nome de usuário para acesso (padrão: vazio).
        * @param senha Senha de acesso (padrão: vazio).
        */
        Cliente(int id = 0, const std::string& nome = "", const std::string& email = "",
                const std::string& username = "", const std::string& senha = "");
        /**
        * @brief Serializa os dados do cliente para armazenamento em arquivo texto.
        * @return std::string Linha formatada com os atributos separados por '|'.
        */
        std::string toFormato() const;
        /**
        * @brief Instancia um objeto Cliente a partir de uma linha de registro textual.
        * @param linha Linha de texto recuperada da base de dados.
        * @return Cliente Objeto populado com as informações da linha.
        */
        static Cliente fromFormato(const std::string& linha);
        /**
        * @brief Valida se a senha digitada corresponde à senha da conta.
        * @param _senha String contendo a senha informada para teste.
        * @return true Se as senhas coincidirem, false caso contrário.
         */
        bool verificarSenha(std::string& _senha) const;
        /**
        * @brief Recupera o nome de usuário (login) do cliente.
        * @return const std::string& Referência para o username.
        */
        const std::string& getUsername() const;
        /**
        * @brief Recupera o e-mail cadastrado do cliente.
        * @return const std::string& Referência para o e-mail.
        */
        const std::string& getEmail() const;
        /**
        * @brief Recupera o nome completo do cliente.
        * @return const std::string& Referência para o nome.
        */
        const std::string& getNome() const;
        /**
        * @brief Obtém o identificador numérico único do cliente.
        * @return int ID do cliente.
        */
        int getId() const;
        /**
        * @brief Atualiza o nome do cliente.
        * @param n Novo nome completo.
        */
    void setNome(const std::string& n);
    /**
    * @brief Atualiza o e-mail cadastrado do cliente.
    * @param e Novo endereço de e-mail.
    */
    void setEmail(const std::string& e);
    /**
    * @brief Atualiza a senha de acesso do cliente.
    * @param s Nova senha.
    */
    void setSenha(const std::string& s);

};

#endif
