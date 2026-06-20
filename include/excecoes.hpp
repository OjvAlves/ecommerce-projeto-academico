#ifndef EXCECOES_HPP
#define EXCECOES_HPP

#include <stdexcept>
#include <string>
/**
 * @class LojaException
 * @brief Classe base para todas as exceções customizadas da aplicação.
 *
 * Herda de std::runtime_error e serve para centralizar o tratamento de erros
 * específicos da lógica do sistema da loja.
 */
class LojaException : public std::runtime_error {
public:
    /**
    * @brief Construtor da exceção LojaException.
    * @param msg Mensagem descritiva do erro encontrado.
    */
    explicit LojaException(const std::string& msg) : std::runtime_error(msg) {}
};
/**
 * @class FalhaArquivoException
 * @brief Exceção lançada quando ocorre um erro crítico no acesso ou abertura de arquivos.
 */
class FalhaArquivoException : public LojaException {
public:
/**
* @brief Construtor da exceção FalhaArquivoException.
* @param arquivo Nome ou caminho do arquivo que não pôde ser acessado.
*/
    explicit FalhaArquivoException(const std::string& arquivo)
        : LojaException("Erro critico: Nao foi possivel acessar o arquivo de banco de dados -> " + arquivo) {}
};
/**
 * @class DadosCorrompidosException
 * @brief Exceção lançada quando a leitura do arquivo encontra dados fora do formato esperado.
 */
class DadosCorrompidosException : public LojaException {
public:
    /**
    * @brief Construtor da exceção DadosCorrompidosException.
    * @param detalhe Informação adicional indicando onde ou qual dado está inconsistente.
    */
    explicit DadosCorrompidosException(const std::string& detalhe)
        : LojaException("Erro de leitura: Os dados no arquivo estao em um formato invalido -> " + detalhe) {}
};

#endif
