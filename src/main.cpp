#include <iostream>
#include <iomanip>
#include "sistema.hpp"
#include "gestorDados.hpp"
#include "excecoes.hpp"
#include <limits>

void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pausar() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int lerInteiroSeguro(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "Erro: Entrada invalida! Por favor, introduza um numero inteiro.\n";
        std::cin.clear();
        limparBuffer();
    }
}

double lerDoubleSeguro(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "Erro: Entrada invalida! Por favor, introduza um valor numerico.\n";
        std::cin.clear();
        limparBuffer();
    }
}

enum Tela {
    TELA_INICIAL,
    TELA_CATALOGO,
    TELA_CADASTRO,
    TELA_LOGIN,
    TELA_AREA_CLIENTE,
    TELA_FAZER_PEDIDO,
    TELA_CARRINHO,
    TELA_PEDIDO_ENVIADO,
    TELA_CONSULTAR_PEDIDOS,
    TELA_HISTORICO,
    TELA_AREA_ADMIN,
    TELA_ADD_PRODUTO,
    TELA_REM_PRODUTO,
    TELA_ESTOQUE,
    TELA_PEDIDOS_CONFIRMAR,
    TELA_HISTORICO_GERAL,
    TELA_EDITAR_PERFIL,
    TELA_EDITAR_PRODUTO,
    TELA_SAIR
};

Tela telaInicial() {
    std::cout << "\n========== LOJA VIRTUAL ==========\n";
    std::cout << "1. Abrir Catalogo\n";
    std::cout << "2. Fazer Login\n";
    std::cout << "3. Cadastrar\n";
    std::cout << "4. Sair\n";

    int opcao = lerInteiroSeguro("Escolha: ");
    switch(opcao) {
        case 1: return TELA_CATALOGO;
        case 2: return TELA_LOGIN;
        case 3: return TELA_CADASTRO;
        case 4: return TELA_SAIR;
        default: return TELA_INICIAL;
    }
}

Tela telaCatalogo(Sistema& sys) {
    auto produtos = sys.listarProdutos();
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
    } else {
        std::cout << "\n=== CATALOGO ===\n";
        std::cout << "ID\tNome\t\t\tValor\t\tEstoque\n";
        std::cout << "------------------------------------------------\n";
        for (const auto& p : produtos) {
            std::cout << p.getId() << "\t" << std::left << std::setw(20) << p.getNome()
                      << "\tR$ " << std::fixed << std::setprecision(2) << p.getValor()
                      << "\t" << p.getQtdEstoque() << "\n";
        }
    }

    std::cout << "\n";
    if (sys.admLogadoFlag) {
        std::cout << "1. Voltar à Área do Administrador\n";
    } else if (sys.clienteLogadoFlag) {
        std::cout << "1. Voltar à Área do Cliente\n";
    } else {
        std::cout << "1. Fazer Login\n";
    }
    std::cout << "2. Voltar à Tela Inicial\n";

    int opcao = lerInteiroSeguro("Escolha: ");

    if (opcao == 1) {
        if (sys.admLogadoFlag)  return TELA_AREA_ADMIN;
        if (sys.clienteLogadoFlag) return TELA_AREA_CLIENTE;
        return TELA_LOGIN;
    }
    return TELA_INICIAL;
}


Tela telaCadastro(Sistema& sys) {
    std::cout << "\n=== CADASTRO ===\n";
    std::string nome = lerStringProibida("Nome: ");
    std::string email = lerStringProibida("Email: ");
    std::string username = lerStringProibida("Username: ");

    Cliente temp;
    if (sys.buscarClientePorUsername(username, temp)) {
        std::cout << "Erro: username ja existe!\n";
        pausar();
        return TELA_INICIAL;
    }

    std::string senha = lerStringProibida("Senha: ");
    int id = sys.gerarIdCliente();

    Cliente c(id, nome, email, username, senha);
    sys.salvarCliente(c);



    std::cout << "Cadastro realizado com sucesso! Seu ID: " << c.getId() << "\n";
    pausar();
    return TELA_INICIAL;
}

Tela telaLogin(Sistema& sys) {
    std::string username = lerStringProibida("Username: ");
    std::string senha = lerStringProibida("Senha: ");

    if (sys.verificarLoginAdm(username, senha)) {
        std::cout << "Login de administrador bem-sucedido!\n";
        pausar();
        return TELA_AREA_ADMIN;
    }

    if (sys.verificarLoginCliente(username, senha)) {
        std::cout << "Bem-vindo, " << sys.clienteLogado.getNome() << "!\n";
        pausar();
        return TELA_AREA_CLIENTE;
    }

    std::cout << "Usuario ou senha incorretos.\n";
    pausar();
    return TELA_INICIAL;
}

Tela telaAreaCliente(Sistema& sys) {
    if (!sys.clienteLogadoFlag) return TELA_INICIAL;
    std::cout << "\n=== AREA DO CLIENTE ===\n";
    std::cout << "Bem-vindo, " << sys.clienteLogado.getNome() << "\n";
    std::cout << "1. Consultar Catalogo\n";
    std::cout << "2. Fazer Pedido\n";
    std::cout << "3. Consultar Carrinho\n";
    std::cout << "4. Consultar Pedidos\n";
    std::cout << "5. Historico de Pedidos\n";
    std::cout << "6. Editar perfil\n";
    std::cout << "7. Logout\n";

    int opcao = lerInteiroSeguro("Escolha: ");
    switch(opcao) {
        case 1: return TELA_CATALOGO;
        case 2: return TELA_FAZER_PEDIDO;
        case 3: return TELA_CARRINHO;
        case 4: return TELA_CONSULTAR_PEDIDOS;
        case 5: return TELA_HISTORICO;
        case 6: return TELA_EDITAR_PERFIL;
        case 7: sys.clienteLogadoFlag = false; return TELA_INICIAL;
        default: return TELA_AREA_CLIENTE;
    }
}

Tela telaFazerPedido(Sistema& sys) {
    if (!sys.clienteLogadoFlag) return TELA_LOGIN;

    auto produtos = sys.listarProdutos();
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
    } else {
        std::cout << "\n=== CATALOGO ===\n";
        std::cout << "ID\tNome\t\t\tValor\t\tEstoque\n";
        std::cout << "------------------------------------------------\n";
        for (const auto& p : produtos) {
            std::cout << p.getId() << "\t" << std::left << std::setw(20) << p.getNome()
                      << "\tR$ " << std::fixed << std::setprecision(2) << p.getValor()
                      << "\t" << p.getQtdEstoque() << "\n";
        }
    }

    int idProduto = lerInteiroSeguro("\nDigite o Id do produto (0 para ir ao carrinho): ");
    if (idProduto == 0) return TELA_CARRINHO;

    Produto* p = sys.buscarProduto(idProduto);
    if (!p) {
     std::cout << "Produto nao encontrado!\n";
      pausar();
      return TELA_FAZER_PEDIDO;
    }

    int qtd = lerInteiroSeguro("Quantiadde: ");

    if (qtd > p->getQtdEstoque()) {
     std::cout << "Estoque insuficiente! Disponivel: " << p->getQtdEstoque() << "\n";
     delete p;
     pausar();
     return TELA_FAZER_PEDIDO;
    }

    if (!sys.carrinhoAtivo) {
     sys.carrinhoAtivo = true;
     sys.carrinhoAtual = Pedido();
     sys.carrinhoAtual.setIdCliente(sys.clienteLogado.getId());
    }

 bool encontrado = false;
  for (auto& item : sys.carrinhoAtual.getItensModificaveis()) {
  if (item.getId() == idProduto) {
   if (item.getQuantidade() + qtd > p->getQtdEstoque()) {
    std::cout << "Estoque insuficiente para o total no carrinho! " << "Disponivel: " << p->getQtdEstoque()
              << " (ja tem " << item.getQuantidade() << " no carrinho)\n";
     delete p;
     pausar();
     return TELA_FAZER_PEDIDO;
    }
     item.setQuantidade(item.getQuantidade() + qtd);
     encontrado = true;
    break;
     }
   }
    if (!encontrado) {
        sys.carrinhoAtual.getItensModificaveis().push_back(ItemPedido(idProduto, qtd));}
    sys.carrinhoAtual.setValorTotal(sys.carrinhoAtual.getValorTotal() + static_cast<float>(p->getValor() * qtd));
    std::cout << "Item '" << p->getNome() << "' adicionado ao carrinho!\n";
    delete p;

    std::cout << "1. Adicionar mais itens\n";
    std::cout << "2. Ir para o carrinho\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    return opcao == 1 ? TELA_FAZER_PEDIDO : TELA_CARRINHO;
}

Tela telaCarrinho(Sistema& sys) {
    if (!sys.carrinhoAtivo || sys.carrinhoAtual.getNumItens() == 0) {
     std::cout << "\nCarrinho vazio!\n";
      pausar();
    return TELA_AREA_CLIENTE;
  }

    std::cout << "\n=== CARRINHO ===\n";
    std::cout << "Pedido #" << sys.carrinhoAtual.getCodigoPedido() << "\n";

    auto& itens = sys.carrinhoAtual.getItensModificaveis();
    for (size_t i = 0; i < itens.size(); ++i) {
     Produto* p = sys.buscarProduto(itens[i].getId());
     if (p) {
      std::cout << (i+1) << ". " << p->getNome() << " x" << itens[i].getQuantidade() << " = R$ " << std::fixed << std::setprecision(2)
           << p->getValor() * itens[i].getQuantidade() << "\n";
     delete p;
     }
}
    std::cout << "TOTAL: R$ " << std::fixed << std::setprecision(2) << sys.carrinhoAtual.getValorTotal() << "\n";
    std::cout << "\n1. Remover item\n";
    std::cout << "2. Alterar quantidade\n";
    std::cout << "3. Confirmar pedido\n";
    std::cout << "4. Esvaziar carrinho\n";
    std::cout << "5. Voltar ao catalogo\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    switch(opcao) {
    case 1: {
      int idx = lerInteiroSeguro("Numero do item para remover: ");
      if (idx > 0 && idx <= static_cast<int>(itens.size())) {
        Produto* p = sys.buscarProduto(itens[idx-1].getId());
      if (p) {
       float desc = static_cast<float>(p->getValor() * itens[idx-1].getQuantidade());
       sys.carrinhoAtual.setValorTotal(sys.carrinhoAtual.getValorTotal() - desc);
        delete p;}
      itens.erase(itens.begin() + (idx-1));}
     return TELA_CARRINHO;
        }
    case 2: {
     int idx = lerInteiroSeguro("Numero do item: ");
     if (idx > 0 && idx <= static_cast<int>(itens.size())) {
      int novaQtd = lerInteiroSeguro("Nova quantidade: ");
      Produto* p = sys.buscarProduto(itens[idx-1].getId());
       if (p) {
        if (novaQtd <= 0) {
          std::cout << "Quantidade invalida! Deve ser maior que zero.\n";
          delete p;
          pausar();
        return TELA_CARRINHO;}
       if (novaQtd > p->getQtdEstoque()) {
         std::cout << "Estoque insuficiente! Disponivel: " << p->getQtdEstoque() << "\n";
        delete p;
        pausar();
        return TELA_CARRINHO;}

        float valorAntigo = static_cast<float>(p->getValor() * itens[idx-1].getQuantidade());
        float valorNovo   = static_cast<float>(p->getValor() * novaQtd);
        sys.carrinhoAtual.setValorTotal(
        sys.carrinhoAtual.getValorTotal() - valorAntigo + valorNovo);
        itens[idx-1].setQuantidade(novaQtd);
    delete p;
       }
      }
            return TELA_CARRINHO;
        }
    case 3: {
    sys.carrinhoAtual.setCodigoPedido(sys.gerarCodigoPedido());
    sys.carrinhoAtual.setIdCliente(sys.clienteLogado.getId());
    sys.carrinhoAtual.setStatus(1);
    sys.salvarPedido(sys.carrinhoAtual);

    for (const auto& item : itens) {
     Produto* p = sys.buscarProduto(item.getId());
     if (p) {
      p->setQtdEstoque(p->getQtdEstoque() - item.getQuantidade());
      sys.atualizarProduto(*p);
      delete p;
     }
    }
     std::cout << "Pedido #" << sys.carrinhoAtual.getCodigoPedido() << " confirmado!\n";
     sys.carrinhoAtivo = false;
     sys.carrinhoAtual = Pedido();
      pausar();
     return TELA_PEDIDO_ENVIADO;}
  case 4:
    sys.carrinhoAtivo = false;
    sys.carrinhoAtual = Pedido();
     return TELA_AREA_CLIENTE;
 case 5:
     return TELA_FAZER_PEDIDO;
   default:
     return TELA_CARRINHO;
 }
}

Tela telaPedidoEnviado() {
    std::cout << "\n=== PEDIDO ENVIADO ===\n";
    std::cout << "1. Area do Cliente\n";
    std::cout << "2. Catalogo\n";
    std::cout << "3. Sair\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    switch(opcao) {
        case 1: return TELA_AREA_CLIENTE;
        case 2: return TELA_CATALOGO;
        case 3: return TELA_SAIR;
        default: return TELA_AREA_CLIENTE;
    }
}

Tela telaConsultarPedidos(Sistema& sys) {
    auto pedidos = sys.listarPedidosCliente(sys.clienteLogado.getId(), 1);
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido pendente.\n";
    } else {
        std::cout << "\n=== SEUS PEDIDOS ===\n";
        for (const auto& p : pedidos) {
            std::cout << "Pedido #" << p.getCodigoPedido() << " | Status: Pendente | Total: R$ "
                      << std::fixed << std::setprecision(2) << p.getValorTotal() << "\n";
        }
    }
    std::cout << "\n1. Voltar\n";
    pausar();
    return TELA_AREA_CLIENTE;
}

Tela telaHistorico(Sistema& sys) {
    auto pedidos = sys.listarPedidosCliente(sys.clienteLogado.getId(), 2);
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido confirmado no historico.\n";
    } else {
        std::cout << "\n=== HISTORICO ===\n";
        for (const auto& p : pedidos) {
            std::cout << "Pedido #" << p.getCodigoPedido() << " | Status: Confirmado | Total: R$ "
                      << std::fixed << std::setprecision(2) << p.getValorTotal() << "\n";
        }
    }
    std::cout << "\n1. Gerar registro de compra (.txt)\n2. Voltar\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    if(opcao == 1) {
        int cod = lerInteiroSeguro("Digite o codigo do pedido: ");
        sys.gerarRegistroTxt(cod);
        pausar();
    }
    return TELA_AREA_CLIENTE;
}

Tela telaAreaAdmin(Sistema& sys) {
    if (!sys.admLogadoFlag) return TELA_INICIAL;
    std::cout << "\n=== AREA DO ADMINISTRADOR ===\n";
    std::cout << "1. Consultar Catalogo\n";
    std::cout << "2. Adicionar Produtos\n";
    std::cout << "3. Remover Produtos\n";
    std::cout << "4. Editar produto\n";
    std::cout << "5. Pedidos a Confirmar\n";
    std::cout << "6. Historico Geral\n";
    std::cout << "7. Ver Estoque\n";
    std::cout << "8. Logout\n";
    std::cout << "9. Sair\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    switch(opcao) {
     case 1: return TELA_CATALOGO;
     case 2: return TELA_ADD_PRODUTO;
     case 3: return TELA_REM_PRODUTO;
     case 4: return TELA_EDITAR_PRODUTO;
     case 5: return TELA_PEDIDOS_CONFIRMAR;
     case 6: return TELA_HISTORICO_GERAL;
     case 7: return TELA_ESTOQUE;
     case 8: sys.admLogadoFlag = false; return TELA_INICIAL;
     case 9: return TELA_SAIR;
   default: return TELA_AREA_ADMIN;
    }
}

Tela telaAddProduto(Sistema& sys) {
    std::cout << "\n=== ADICIONAR PRODUTO ===\n";
    std::string nome = lerStringProibida("Nome: ");
    double valor = lerDoubleSeguro("Valor: ");
    int qtdEstoque = lerInteiroSeguro("Quantidade em estoque: ");
    int id = sys.gerarIdProduto();

    Produto p(id, nome, valor, qtdEstoque);
    sys.salvarProduto(p);

    std::cout << "Produto '" << p.getNome() << "' adicionado com sucesso! Codigo: " << p.getId() << "\n";
    pausar();
    return TELA_AREA_ADMIN;
}

Tela telaRemProduto(Sistema& sys) {
    std::cout << "\n=== REMOVER PRODUTO ===\n";
    auto produtos = sys.listarProdutos();
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
        pausar();
        return TELA_AREA_ADMIN;
    }
    std::cout << "ID\tNome\t\t\tValor\t\tEstoque\n";
    std::cout << "------------------------------------------------\n";
    for (const auto& p : produtos) {
        std::cout << p.getId() << "\t" << std::left << std::setw(20) << p.getNome()
                  << "\tR$ " << std::fixed << std::setprecision(2) << p.getValor()
                  << "\t" << p.getQtdEstoque() << "\n";
    }
    int id = lerInteiroSeguro("\nCodigo do produto: ");
    Produto* p = sys.buscarProduto(id);
    if (!p) {
        std::cout << "Produto nao encontrado!\n";
        pausar();
        return TELA_AREA_ADMIN;
    }
    std::cout << "Remover '" << p->getNome() << "'? (1=Sim, 0=Nao): ";
    int confirma = lerInteiroSeguro("Escolha: ");
    if (confirma == 1) {
        sys.removerProduto(id);
        std::cout << "Produto removido!\n";
    }
    delete p;
    pausar();
    return TELA_AREA_ADMIN;
}

Tela telaEstoque(Sistema& sys) {
    auto produtos = sys.listarProdutos();
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
        pausar();
        return TELA_AREA_ADMIN;
    }
    std::cout << "\n=== ESTOQUE ===\n";
    std::cout << "Codigo\tProduto\t\t\tQtd\tStatus\n";
    std::cout << "------------------------------------------------\n";
    for (const auto& p : produtos) {
        std::cout << p.getId() << "\t" << std::left << std::setw(20) << p.getNome()
                  << "\t" << p.getQtdEstoque() << "\t"
                  << (p.getQtdEstoque() < 2 ? "ESTOQUE BAIXO!" : "OK") << "\n";
    }
    std::cout << "\n1. Editar estoque\n";
    std::cout << "2. Voltar\n";
    int opcao = lerInteiroSeguro("Escolha: ");
    if (opcao == 1) {
        int id = lerInteiroSeguro("Codigo do produto: ");
        Produto* p = sys.buscarProduto(id);
        if (p) {
            int qtdAdd = lerInteiroSeguro("Quantidade a adicionar: ");
            p->setQtdEstoque(p->getQtdEstoque() + qtdAdd);
            sys.atualizarProduto(*p);
            std::cout << "Estoque atualizado! Novo total: " << p->getQtdEstoque() << "\n";
            delete p;
        } else {
            std::cout << "Produto nao encontrado!\n";
        }
        pausar();
        return TELA_ESTOQUE;
    }
    return TELA_AREA_ADMIN;
}

Tela telaPedidosConfirmar(Sistema& sys) {
    auto pedidos = sys.listarTodosPedidos();
    std::vector<Pedido> pendentes;
    for (const auto& p : pedidos) {
        if (p.getStatus() == 1) pendentes.push_back(p);
    }
    if (pendentes.empty()) {
        std::cout << "Nenhum pedido pendente.\n";
        pausar();
        return TELA_AREA_ADMIN;
    }
    std::cout << "\n=== PEDIDOS PENDENTES ===\n";
    for (const auto& p : pendentes) {
        std::cout << "Pedido #" << p.getCodigoPedido() << " | Cliente: " << p.getIdCliente()
                  << " | Total: R$ " << std::fixed << std::setprecision(2) << p.getValorTotal() << "\n";
    }
    int cod = lerInteiroSeguro("\nDigite o codigo do pedido (0 para voltar): ");
    if (cod == 0) return TELA_AREA_ADMIN;

   int acao = lerInteiroSeguro("[1] Confirmar [2] Cancelar: ");

    for (auto& p : pendentes) {
        if (p.getCodigoPedido() == cod) {
            if (acao == 2) {
            for (const auto& item : p.getItensModificaveis()) {
             Produto* prod = sys.buscarProduto(item.getId());
              if (prod) {
               prod->setQtdEstoque(prod->getQtdEstoque() + item.getQuantidade());
               sys.atualizarProduto(*prod);
            delete prod;
            }
           }
          }
            p.setStatus((acao == 1) ? 2 : 3);
            sys.atualizarPedido(p);
            std::cout << "Pedido #" << cod << " " << (acao == 1 ? "confirmado" : "cancelado") << "!\n";
            break;
        }
    }
    pausar();
    return TELA_PEDIDOS_CONFIRMAR;
}

Tela telaHistoricoGeral(Sistema& sys) {
    auto pedidos = sys.listarTodosPedidos();
    bool tem = false;
    std::cout << "\n=== HISTORICO GERAL ===\n";
    for (const auto& p : pedidos) {
        if (p.getStatus() == 2) {
            std::cout << "Pedido #" << p.getCodigoPedido() << " | Cliente: " << p.getIdCliente()
                      << " | Total: R$ " << std::fixed << std::setprecision(2) << p.getValorTotal() << "\n";
            tem = true;
        }
    }
    if (!tem) std::cout << "Nenhum pedido confirmado no historico.\n";

    std::cout << "\n1. Gerar registro (.txt)\n";
    std::cout << "2. Voltar\n";
    int opcao = lerInteiroSeguro("Escolha:");
    if (opcao == 1) {
        int cod = lerInteiroSeguro("Digite o codigo do pedido: ");
        sys.gerarRegistroTxt(cod);
        pausar();
    }
    return TELA_AREA_ADMIN;
}

Tela telaEditarPerfil(Sistema& sys) {
 std::cout << "\n===== EDITAR PERFIL =====\n";
 std::cout << "1. Alterar nome\n";
 std::cout << "2. Alterar email\n";
 std::cout << "3. Alterar senha\n";
 std::cout << "4. Voltar\n";
int op = lerInteiroSeguro("Opcao: ");
  switch (op) {
    case 1: {
          std::string novo = lerStringProibida("Novo nome: ");
           sys.clienteLogado.setNome(novo);
           sys.atualizarCliente(sys.clienteLogado);
          std::cout << "Nome atualizado!\n";
            break;
        }
   case 2: {
          std::string novo = lerStringProibida("Novo email: ");
            sys.clienteLogado.setEmail(novo);
            sys.atualizarCliente(sys.clienteLogado);
          std::cout << "Email atualizado!\n";
            break;
        }
    case 3: {
         std::string novo = lerStringProibida("Nova senha: ");
         sys.clienteLogado.setSenha(novo);
         sys.atualizarCliente(sys.clienteLogado);
         std::cout << "Senha atualizada!\n";
         break;
        }
    case 4: return TELA_AREA_CLIENTE;
     default: std::cout << "Opcao invalida!\n";
    }
    pausar();
    return TELA_EDITAR_PERFIL;
}

Tela telaEditarProduto(Sistema& sys) {
    std::cout << "\n===== EDITAR PRODUTO =====\n";
    auto produtos = sys.listarProdutos();
    if (produtos.empty()) {
     std::cout << "Nenhum produto cadastrado.\n";
      pausar();
     return TELA_AREA_ADMIN;
    }
    for (const auto& p : produtos)
        std::cout << "[" << p.getId() << "] " << p.getNome() << " - R$ " << p.getValor()
        << " | Estoque: " << p.getQtdEstoque() << "\n";

    int id = lerInteiroSeguro("ID do produto a editar (0 para voltar): ");
    if (id == 0) return TELA_AREA_ADMIN;

    Produto* p = sys.buscarProduto(id);
    if (!p) {
     std::cout << "Produto nao encontrado!\n";
      pausar();
     return TELA_EDITAR_PRODUTO;
    }

    std::cout << "1. Alterar nome\n";
    std::cout << "2. Alterar valor\n";
    std::cout << "3. Voltar\n";
    int op = lerInteiroSeguro("Opcao: ");
    switch (op) {
    case 1: {
     std::string novo = lerStringProibida("Novo nome: ");
      p->setNome(novo);
      sys.atualizarProduto(*p);
    std::cout << "Nome atualizado!\n";
    break;
        }
    case 2: {
     double novo = lerDoubleSeguro("Novo valor: ");
       if (novo < 0) {
         std::cout << "Valor invalido!\n";
         delete p;
        pausar();
     return TELA_EDITAR_PRODUTO; }
       p->setValor(novo);
       sys.atualizarProduto(*p);
       std::cout << "Valor atualizado!\n";
       break;
        }
        case 3:
         delete p;
            return TELA_AREA_ADMIN;
        default:
       std::cout << "Opcao invalida!\n";
    }
    delete p;
    pausar();
    return TELA_EDITAR_PRODUTO;
}

int main() {
    try {
        Sistema sys;
        Tela atual = TELA_INICIAL;

        while (atual != TELA_SAIR) {
            try {
                switch(atual) {
    case TELA_INICIAL: atual = telaInicial();
     break;
    case TELA_CATALOGO: atual = telaCatalogo(sys);
     break;
    case TELA_CADASTRO: atual = telaCadastro(sys);
     break;
    case TELA_LOGIN: atual = telaLogin(sys);
     break;
    case TELA_AREA_CLIENTE: atual = telaAreaCliente(sys);
     break;
    case TELA_FAZER_PEDIDO: atual = telaFazerPedido(sys);
     break;
    case TELA_CARRINHO: atual = telaCarrinho(sys);
     break;
    case TELA_PEDIDO_ENVIADO: atual = telaPedidoEnviado();
     break;
    case TELA_CONSULTAR_PEDIDOS: atual = telaConsultarPedidos(sys);
     break;
    case TELA_HISTORICO: atual = telaHistorico(sys);
     break;
    case TELA_AREA_ADMIN: atual = telaAreaAdmin(sys);
     break;
    case TELA_ADD_PRODUTO: atual = telaAddProduto(sys);
     break;
    case TELA_REM_PRODUTO: atual = telaRemProduto(sys);
     break;
    case TELA_ESTOQUE: atual = telaEstoque(sys);
     break;
    case TELA_PEDIDOS_CONFIRMAR: atual = telaPedidosConfirmar(sys);
     break;
    case TELA_HISTORICO_GERAL: atual = telaHistoricoGeral(sys);
     break;
    case TELA_EDITAR_PERFIL:  atual = telaEditarPerfil(sys);
     break;
    case TELA_EDITAR_PRODUTO: atual = telaEditarProduto(sys);
     break;
       default: atual = TELA_SAIR;
                }
            } catch (const LojaException& e) {
                std::cerr << "\n[ERRO NA OPERACAO] " << e.what() << "\n";
                std::cerr << "Retornando ao menu inicial...\n";
                pausar();
                atual = TELA_INICIAL;
            }
        }
        std::cout << "\nPrograma encerrado.\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\n[ERRO INESPERADO DO SISTEMA OPERATIVO]\n";
        std::cerr << "Detalhes: " << e.what() << "\n";
        pausar();
        return 1;
    }
}
