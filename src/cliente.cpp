#include "cliente.hpp"
#include "gestorDados.hpp"

Cliente::Cliente(int id, const std::string& nome, const std::string& email,
                 const std::string& username, const std::string& senha)
    : id(id), nome(nome), email(email), username(username), senha(senha) {}

std::string Cliente::toFormato() const {
    return "|" + std::to_string(id) + "|" + nome + "|" + email + "|" + username + "|" + senha + "|";
}

Cliente Cliente::fromFormato(const std::string& linha) {
    auto p = split(linha, '|');
    // formato: |id|nome|email|username|senha| -> o split gera ["", id, nome, email, username, senha, ""]
    if (p.size() < 6) return Cliente();
    return Cliente(
        std::stoi(p[1]),
        p[2],
        p[3],
        p[4],
        p[5]
    );
}

const std::string& Cliente::getUsername() const {
    return username;
}

const std::string& Cliente::getEmail() const {
    return email;
}

const std::string& Cliente::getNome() const {
    return nome;
}

int Cliente::getId() const {
    return id;
}

bool Cliente::verificarSenha(std::string& _senha) const {
    return _senha == senha;
}

void Cliente::setNome(const std::string& n) { nome = n; }
void Cliente::setEmail(const std::string& e) { email = e; }
void Cliente::setSenha(const std::string& s) { senha = s; }
