#include "gestorDados.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

std::string trim(const std::string& s) {
  size_t start = 0;
  while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;
  size_t end = s.size();
  while (end > start && std::isspace(static_cast<unsigned char>(s[end-1]))) end--;
  return s.substr(start, end - start);
}

std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> res;
  std::string cur;
   for (char c : s) {
     if (c == delim) {
     res.push_back(trim(cur));
     cur.clear();
    } else {
      cur += c;
      }
    }
    res.push_back(trim(cur));
    return res;
}

std::string doubleToString(double v) {
  std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << v;
  std::string s = oss.str();
    while (!s.empty() && s.back() == '0') s.pop_back();
    if (!s.empty() && s.back() == '.') s += '0';
    return s;
}

double stringToDouble(const std::string& s) {
    try { return std::stod(s); } catch (...) { return 0.0; }
}

std::string lerStringProibida(const std::string& prompt) {
  std::string s;
   while (true) {
      std::cout << prompt;
      std::getline(std::cin, s);
        if (s.find('|') != std::string::npos) {
            std::cout << "Erro: o caractere '|' nao e permitido. Digite novamente.\n";
        } else {
            break;
        }
    }
    return s;


}
