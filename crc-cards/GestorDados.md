# Gestor de Dados

| **Classe** | `GestorDados` |
|:---|:---|

## Responsabilidades e Colaboradores

| # | Responsabilidade | Colaboradores |
|:--|:---              |           :---|
| 1 | Atuar como o controlador central da lógica de negócios e camada de persistência de dados. | Nenhum |
| 2 | Gerenciar as coleções em memória viva (std::vector ou estruturas correlatas) de Produtos, Clientes e Pedidos | `Produtos` `Clientes` `Pedidos` |
| 3 | Abstrair a camada de conectividade de banco de dados para leitura, atualização e escrita persistente. | Nenhum |
| 4 | Abstrair a camada de conectividade de banco de dados para leitura, atualização e escrita persistente. | `Administrador` `Clientes` | 
| 5 | Garantir a integridade operacional lançando exceções estruturadas quando inconsistências forem detectadas. | Nenhum |