# Pedido

| **Classe** | `Pedido` |
|:---|:---|

## Responsabilidades e Colaboradores

| # | Responsabilidade | Colaboradores |
|:--|:---              |           :---|
| 1 | Registrar metadados consolidados do ato de compra (ID único do pedido, data/hora da transação, status do fluxo de pagamento). | Nenhum |
| 2 | Armazenar de forma imutável a lista de ItemProduto adquiridos. | `ItemProduto` |
| 3 | Computar o valor total bruto da transação somando todos os subtotais dos itens contidos. | Nenhum |
| 4 | Vincular e validar a operação em relação ao Cliente originador da compra. | `Cliente` |