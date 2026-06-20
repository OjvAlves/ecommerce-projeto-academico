#include "itemPedido.hpp"
#include "gestorDados.hpp"

ItemPedido::ItemPedido(int id, int quantidade) : id(id), quantidade(quantidade) {}
std::string ItemPedido::toFormato() const {
  return "{" + std::to_string(id) + "|" + std::to_string(quantidade) + "}";
}
ItemPedido ItemPedido::fromFormato(const std::string& linha) {
    //{id|quantidade}
  if (linha.size() < 3 || linha.front() != '{' || linha.back() != '}') return ItemPedido(); //conferindo se o que chega faz sentido
  std::string inner = linha.substr(1, linha.size() - 2); //coloca em inner o conteúdo entre as chaves
  auto p = split(inner, '|'); //separa o id da quantidade
  if (p.size() < 2) return ItemPedido(); //confere de novo se o resultado até aqui faz sentido
    return ItemPedido(std::stoi(p[0]), std::stoi(p[1]));
}
int ItemPedido::getQuantidade() const{
  return quantidade;
}

int ItemPedido::getId() const{
  return id;
}
