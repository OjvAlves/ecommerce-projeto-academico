#include "pedido.hpp"
#include "gestorDados.hpp"

Pedido::Pedido(int codigoPedido, int idCliente, int status, float valorTotal)
    : codigoPedido(codigoPedido),
      idCliente(idCliente),
      valorTotal(valorTotal),
      status(status) {}

std::string Pedido::toFormato() const {
    std::string itensString;
    for (const auto& item : itens) {
        itensString += item.toFormato();
    }
    return "{" + std::to_string(codigoPedido) + "|" +
           std::to_string(idCliente) + "|" +
           doubleToString(valorTotal) + "|" +
           std::to_string(status) + "|" +
           itensString + "}";
}

Pedido Pedido::fromFormato(const std::string& linha) {
    if (linha.size() < 3 || linha.front() != '{' || linha.back() != '}')
        return Pedido();
    std::string inner = linha.substr(1, linha.size() - 2);
    Pedido p;
    size_t splitPos = 0;
    for (int i = 0; i < 4; ++i) {
        splitPos = inner.find('|', splitPos + 1);
        if (splitPos == std::string::npos)
            return Pedido();
    }
    std::string prefix = inner.substr(0, splitPos);
    std::string suffix = inner.substr(splitPos + 1);
    auto camposVec = split(prefix, '|');
    if (camposVec.size() < 4)
        return Pedido();
    p.codigoPedido = std::stoi(camposVec[0]);
    p.idCliente = std::stoi(camposVec[1]);
    p.valorTotal = static_cast<float>(stringToDouble(camposVec[2]));
    p.status = std::stoi(camposVec[3]);
    size_t i = 0;
    while (i < suffix.size()) {
        if (suffix[i] == '{') {
            size_t fim = suffix.find('}', i);
            if (fim == std::string::npos)
                break;
            std::string itemStr = suffix.substr(i, fim - i + 1);
            p.itens.push_back(ItemPedido::fromFormato(itemStr));
            i = fim + 1;
        } else {
            ++i;
        }
    }
    return p;
}

int Pedido::getCodigoPedido() const {
    return codigoPedido;
}

int Pedido::getIdCliente() const {
    return idCliente;
}

int Pedido::getNumItens() const {
    return static_cast<int>(itens.size());
}

int Pedido::getStatus() const {
    return status;
}

float Pedido::getValorTotal() const {
    return valorTotal;
}
