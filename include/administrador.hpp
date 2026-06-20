#ifndef ADMINISTRADOR_HPP
#define ADMINISTRADOR_HPP

#include <string>
/**
 * @class Administrador
 * @brief Representa um usuário administrador do sistema da loja.
 *
 * Esta classe armazena as credenciais de um administrador e fornece
 * métodos para autenticação e serialização de dados.
 */
class Administrador {
private:
    std::string username;
    std::string senha;
public:
    /**
         * @brief Construtor da classe Administrador.
         * @param username Nome de usuário do administrador.
         * @param senha Senha de acesso do administrador.
         */
    Administrador(const std::string& username = "", const std::string& senha = "");
    /**
         * @brief Serializa os dados do administrador para o formato.
         * @return std::string Uma linha formatada com os dados delimitados por '|'.
         */
    std::string toFormato() const;
    static Administrador fromFormato(const std::string& linha);
    /**
         * @brief Reconstrói um objeto Administrador a partir de uma linha de texto.
         * @param linha Linha de texto lida do banco de dados/arquivo.
         * @return Administrador O objeto instanciado com os dados da linha.
         */
    const std::string& getUsername() const;
    /**
         * @brief Obtém o nome de usuário do administrador.
         * @return const std::string& Referência para o username.
         */
    bool verificarSenha(const std::string& _senha) const;
};

#endif
