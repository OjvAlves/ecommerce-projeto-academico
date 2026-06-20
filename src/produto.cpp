#include "produto.hpp"
#include "gestorDados.hpp"

Produto::Produto(int id, const std::string& nome, double valor, int qtd)
    : id(id), nome(nome), valor(valor), qtdEstoque(qtd) {}

std::string Produto::toFormato() const {
    return "|" + std::to_string(id) + "|" + nome + "|" + doubleToString(valor) + "|" + std::to_string(qtdEstoque) + "|";
}

Produto Produto::fromFormato(const std::string& linha) {
    auto p = split(linha, '|');
    if (p.size() < 5) return Produto();
    return Produto(
     std::stoi(p[1]),
     p[2],
     stringToDouble(p[3]),
     std::stoi(p[4])
    );
}

int Produto::getId() const {
    return id;}

const std::string& Produto::getNome() const {
    return nome;}

double Produto::getValor() const {
    return valor;}

int Produto::getQtdEstoque() const {
    return qtdEstoque;}

void Produto::setNome(const std::string& n) { nome = n; }
void Produto::setValor(double v) { valor = v; }
