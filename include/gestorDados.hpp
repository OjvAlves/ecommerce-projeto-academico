#ifndef GESTORDADOS_HPP
#define GESTORDADOS_HPP
#include <string>
#include <vector>
/**
 * @brief Divide uma string em múltiplos pedaços com base em um caractere delimitador.
 * @param s A string original a ser dividida.
 * @param delimitador O caractere que servirá como ponto de divisão (ex: '|').
 * @return std::vector<std::string> Vetor contendo os subpedaços da string isolados.
 */
std::vector<std::string> split(const std::string& s, char delimitador);
/**
 * @brief Remove espaços em branco redundantes do início e do fim de uma string.
 * @param s A string original.
 * @return std::string A nova string tratada sem os espaços nas extremidades.
 */
std::string trim(const std::string& s); //remove espaços em branco das extremidades da string
/**
 * @brief Converte um valor do tipo double para o seu equivalente em formato de texto.
 * @param v O número real em precisão dupla.
 * @return std::string Representação textual do número.
 */
std::string doubleToString(double v); //converte double em string e vice-versa
/**
 * @brief Converte uma string de texto em um valor numérico do tipo double.
 * @param s A string contendo o número.
 * @return double O valor numérico extraído.
 */
double stringToDouble(const std::string& s);
/**
 * @brief Realiza a leitura de uma string via teclado impedindo o uso de caracteres proibidos.
 *
 * Bloqueia a inserção de caracteres reservados pela estrutura dos arquivos (como o delimitador '|').
 * @param prompt Mensagem de orientação exibida ao usuário no terminal antes da leitura.
 * @return std::string A string validada digitada pelo usuário.
 */
std::string lerStringProibida(const std::string& prompt);

#endif
