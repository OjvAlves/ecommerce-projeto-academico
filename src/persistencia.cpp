#include "persistencia.hpp"
#include "excecoes.hpp"
#include <fstream>
#include <iostream>

std::vector<std::string> Persistencia::lerLinhas(const std::string& nome) {
std::vector<std::string> linhas;
std::ifstream f(nome);
 if (!f.is_open()){
  throw FalhaArquivoException("Falha na leitura: " + nome);
    }
std::string linha;
  while (std::getline(f, linha)) {
    if (!linha.empty()) linhas.push_back(linha); }
    return linhas;
}

void Persistencia::escreverLinhas(const std::string& nome, const std::vector<std::string>& linhas) {
 std::ofstream f(nome);
 if (!f.is_open()) {
  throw FalhaArquivoException("Falha na escrita: " + nome);
 }
 for(const auto& l : linhas) {
   f << l << "\n"; }
}
std::vector<Cliente> Persistencia::carregarClientes() {
 std::vector<Cliente> res;
 for (const auto& l : lerLinhas("clientes.txt"))
   res.push_back(Cliente::fromFormato(l));
  return res;
}

void Persistencia::salvarClientes(const std::vector<Cliente>& dados) {
 std::vector<std::string> linhas;
 for (const auto& c : dados) linhas.push_back(c.toFormato());
 escreverLinhas("clientes.txt", linhas);
}
std::vector<Administrador> Persistencia::carregarAdmins() {
 std::vector<Administrador> res;
  for (const auto& l : lerLinhas("adm.txt"))
   res.push_back(Administrador::fromFormato(l));
 return res;
}

void Persistencia::salvarAdmins(const std::vector<Administrador>& dados) {
 std::vector<std::string> linhas;
  for (const auto& a : dados) linhas.push_back(a.toFormato());
 escreverLinhas("adm.txt", linhas);
}
std::vector<Produto> Persistencia::carregarProdutos() {
 std::vector<Produto> resultado;
  for (const auto& l : lerLinhas("produtos.txt"))
   resultado.push_back(Produto::fromFormato(l));
 return resultado;
}

void Persistencia::salvarProdutos(const std::vector<Produto>& dados) {
 std::vector<std::string> linhas;
  for (const auto& p : dados) linhas.push_back(p.toFormato());
    escreverLinhas("produtos.txt", linhas);
}
std::vector<Pedido> Persistencia::carregarPedidos() {
 std::vector<Pedido> resultado;
  for (const auto& l : lerLinhas("pedidos.txt"))
   resultado.push_back(Pedido::fromFormato(l));
 return resultado;
}

void Persistencia::salvarPedidos(const std::vector<Pedido>& dados) {
 std::vector<std::string> linhas;
  for (const auto& p : dados) linhas.push_back(p.toFormato());
    escreverLinhas("pedidos.txt", linhas); }
