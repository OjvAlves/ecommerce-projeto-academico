#include "administrador.hpp"
#include "gestorDados.hpp"

Administrador::Administrador(const std::string& username, const std::string& senha): username(username), senha(senha) {}
std::string Administrador::toFormato() const {
 return "|" + username + "|" + senha + "|";
  }
Administrador Administrador::fromFormato(const std::string& linha) {
 auto p = split(linha, '|');
 if (p.size() < 3) return Administrador();
  return Administrador(p[1], p[2]);
  }
const std::string& Administrador::getUsername() const {
  return username;
  }
bool Administrador::verificarSenha(const std::string& _senha) const {
    return _senha == senha;
  }
