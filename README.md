<div align = "middle"> <H2> http:/✧/bank.project.c.com </H2> </div> 
<img align = "right" src="https://cdn.pixabay.com/animation/2023/06/13/15/13/15-13-37-55_512.gif" width="50" height = "50" alt="bank">

## ₊˚‧︵‿꒰୨ Sistema de Gestão Bancária

Este projeto é um sistema simples para a gestão de contas bancárias, desenvolvido em C. Ele permite realizar operações básicas como cadastro de clientes, consultas, transações e geração de extratos. O sistema utiliza arquivos binários para armazenar e gerenciar os dados dos clientes.

## Funcionalidades

O programa oferece as seguintes funcionalidades:

1. **Cadastrar Novo Cliente**: Adiciona um cliente ao sistema com dados como nome, CPF, tipo de conta, saldo inicial e senha.
2. **Remover Cliente**: Exclui um cliente com base no CPF.
3. **Débito**: Permite debitar um valor da conta do cliente, considerando o tipo de conta (comum ou plus) e seus limites.
4. **Depósito**: Permite adicionar um valor à conta de um cliente.
5. **Extrato**: Mostra as informações da conta do cliente, como nome, CPF, tipo de conta e saldo atual.
6. **Transferência**: Transfere valores entre contas, verificando saldo disponível e atualizando ambas as contas.
7. **Saldo Total**: Calcula o saldo acumulado de todas as contas cadastradas.
8. **Sair**: Encerra o programa.

## Estrutura do Código

- **Cliente**: Estrutura para armazenar as informações dos clientes, incluindo nome, CPF, tipo de conta, saldo e senha.
- **Funções**:
  - `limparBuffer()`: Limpa o buffer de entrada.
  - `novoCliente()`: Cadastra um novo cliente.
  - `apagarCliente()`: Remove um cliente do arquivo.
  - `debito()`: Realiza operações de débito considerando limites e taxas por tipo de conta.
  - `deposito()`: Permite adicionar fundos à conta de um cliente.
  - `extrato()`: Exibe os detalhes de uma conta específica.
  - `transferencia()`: Realiza transferências entre contas.
  - `totalSaldoContas()`: Calcula e exibe o saldo total armazenado no banco.

## Como Executar

1. Certifique-se de que tem um compilador de C (como GCC) instalado em sua máquina.
2. Compile o programa com o seguinte comando:

   ```bash
   gcc -o sistema_bancario sistema_bancario.c
   ```

3. Execute o programa:

   ```bash
   ./sistema_bancario
   ```

## Estrutura de Dados

Os dados dos clientes são armazenados no arquivo binário `clientes.dat`. O programa acessa e atualiza este arquivo diretamente para refletir as operações realizadas.

## Observações

- **Segurança**: A senha do cliente é armazenada sem criptografia. Para um sistema em produção, é altamente recomendável implementar técnicas de hash para proteger dados sensíveis.
- **Validações**: Algumas entradas não possuem validação robusta (ex.: formato do CPF). Em aplicações reais, mais validações devem ser adicionadas.
- **Limites de Conta**:
  - **Comum**: Saldo negativo permitido até -1000.00 com taxa de 5% sobre débitos.
  - **Plus**: Saldo negativo permitido até -5000.00 com taxa de 3% sobre débitos.

---

Este projeto é ideal para fins educacionais, ajudando no aprendizado de manipulação de arquivos, estruturas de dados e implementação de lógica em C. <br>

<br>
