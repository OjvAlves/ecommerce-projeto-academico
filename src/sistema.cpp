#include "sistema.hpp"
#include "persistencia.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

Sistema::Sistema() : clienteLogadoFlag(false), admLogadoFlag(false), carrinhoAtivo(false) {}

int Sistema::gerarIdCliente() {
    auto v = Persistencia::carregarClientes();
    int maxId = 0;
    for (int i = 0; i < (int)v.size(); i++) {
      if (v[i].getId() > maxId) {
        maxId = v[i].getId();
      }
    }
  return maxId + 1;
}

int Sistema::gerarIdProduto() {
  auto v = Persistencia::carregarProdutos();
   int maxId = 0;
   for (const auto& p : v) if (p.getId() > maxId) maxId = p.getId();
  return maxId + 1;
}

/*
int Sistema::gerarCodigoPedido() {
    auto v = Persistencia::carregarPedidos();
    return 1000 + static_cast<int>(v.size());
    } */

int Sistema::gerarCodigoPedido() {
    auto v = Persistencia::carregarPedidos();
    int maxCod = 999;
    for (const auto& p : v) if (p.getCodigoPedido() > maxCod) maxCod = p.getCodigoPedido();
    return maxCod + 1;
}


void Sistema::salvarCliente(const Cliente& c) {
    auto v = Persistencia::carregarClientes();
    v.push_back(c);
    Persistencia::salvarClientes(v);
}

bool Sistema::buscarClientePorUsername(const std::string& username, Cliente& resultado) {
    auto v = Persistencia::carregarClientes();
    for (const auto& c : v) {
        if (c.getUsername() == username) {
            resultado = c;
            return true;
        }
    }
    return false;
}

bool Sistema::verificarLoginCliente(const std::string& username, const std::string& senha) {
    Cliente c;
    if (buscarClientePorUsername(username, c)) {
        std::string senhaCopy = senha;
        if (c.verificarSenha(senhaCopy)) {
            clienteLogado = c;
            clienteLogadoFlag = true;
            return true;
        }
    }
    return false;
}

bool Sistema::verificarLoginAdm(const std::string& username, const std::string& senha) {
    auto v = Persistencia::carregarAdmins();
    for (const auto& a : v) {
        if (a.getUsername() == username && a.verificarSenha(senha)) {
            admLogado = a;
            admLogadoFlag = true;
            return true;
        }
    }
    return false;
}

void Sistema::atualizarCliente(const Cliente& c) {
    auto v = Persistencia::carregarClientes();
    for (auto& cliente : v) {
        if (cliente.getId() == c.getId()) {
            cliente = c;
            break;
        }
    }
    Persistencia::salvarClientes(v); }



void Sistema::salvarProduto(const Produto& p) {
    auto v = Persistencia::carregarProdutos();
    v.push_back(p);
    Persistencia::salvarProdutos(v);
}

std::vector<Produto> Sistema::listarProdutos() {
    return Persistencia::carregarProdutos();
}

Produto* Sistema::buscarProduto(int id) {
    auto v = Persistencia::carregarProdutos();
    for (const auto& p : v) {
        if (p.getId() == id) return new Produto(p);
    }
    return nullptr;
}

void Sistema::atualizarProduto(const Produto& p) {
    auto v = Persistencia::carregarProdutos();
    for (auto& prod : v) {
        if (prod.getId() == p.getId()) {
            prod = p;
            break;
        }
    }
    Persistencia::salvarProdutos(v);
}

void Sistema::removerProduto(int id) {
    auto v = Persistencia::carregarProdutos();
    std::vector<Produto> novo;
    for (const auto& p : v) {
        if (p.getId() != id) novo.push_back(p);
    }
    Persistencia::salvarProdutos(novo);
}

void Sistema::salvarPedido(const Pedido& ped) {
    auto v = Persistencia::carregarPedidos();
    v.push_back(ped);
    Persistencia::salvarPedidos(v);
}

std::vector<Pedido> Sistema::listarPedidosCliente(int idCliente, int statusFiltro) {
    auto v = Persistencia::carregarPedidos();
    std::vector<Pedido> res;
    for (const auto& p : v) {
        if (p.getIdCliente() == idCliente && (statusFiltro == -1 || p.getStatus() == statusFiltro))
            res.push_back(p);
    }
    return res;
}

std::vector<Pedido> Sistema::listarTodosPedidos() {
    return Persistencia::carregarPedidos();
}

void Sistema::atualizarPedido(const Pedido& p) {
    auto v = Persistencia::carregarPedidos();
    for (auto& ped : v) {
        if (ped.getCodigoPedido() == p.getCodigoPedido()) {
            ped = p;
            break;
        }
    }
    Persistencia::salvarPedidos(v);
}

void Sistema::gerarRegistroTxt(int codigoPedido) {
    auto pedidos = Persistencia::carregarPedidos();
    auto produtos = listarProdutos();

 for (int i = 0; i < (int)pedidos.size(); i++) {
  if (pedidos[i].getCodigoPedido() == codigoPedido && pedidos[i].getStatus() == 2) {
   std::string nomeArq = "pedido_" + std::to_string(codigoPedido) + ".txt";
   std::ofstream out(nomeArq);
  if (!out.is_open()) {
   std::cout << "Erro ao criar arquivo.\n";
  return; }
            out << "=== REGISTRO DE PEDIDO ===\n";
            out << "Codigo: " << pedidos[i].getCodigoPedido() << "\n";
            out << "Cliente ID: " << pedidos[i].getIdCliente() << "\n";
            out << "Status: Confirmado\n";
            out << "----------------------------\n";
            out << "Itens:\n";
auto itensPedido = pedidos[i].getItensModificaveis();
  for (int j = 0; j < (int)itensPedido.size(); j++) {
   std::string nomeProduto = "???";
   double valorProduto = 0.0;
   bool achei = false;
    for (int k = 0; k < (int)produtos.size(); k++) {
      if (produtos[k].getId() == itensPedido[j].getId()) {
       nomeProduto = produtos[k].getNome();
       valorProduto = produtos[k].getValor();
       achei = true;
   break;
    }
   }
    if (achei) {
      out << " - " << nomeProduto << " x" << itensPedido[j].getQuantidade() << " = R$ " << valorProduto * itensPedido[j].getQuantidade() << "\n";
       } else {
         out << " - PRODUTO NAO ENCONTRADO (ID: " << itensPedido[j].getId() << ")\n";
        }

            out << "----------------------------\n";
            out << "TOTAL: R$ " << pedidos[i].getValorTotal() << "\n";
            out.close();
   std::cout << "Registro gerado: " << nomeArq << "\n";
      return;
   }
  }
    std::cout << "Pedido nao encontrado ou nao confirmado.\n";
}
}
