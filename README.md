# Sistema de Supervisão de Dados em C++ com Qt

Este projeto é um sistema cliente-servidor para aquisição e supervisão de dados em tempo real, desenvolvido como parte de um exercício de programação orientada a objetos com o framework Qt 6.

O sistema é composto por três módulos que comunicam via TCP/IP numa rede local:
1.  **Servidor (`QtServerMultithread`):** Um servidor TCP multithread que escuta na porta 1234, gere as conexões dos clientes e armazena os dados recebidos.
2.  **Cliente Produtor (`QtTcpClientProducer`):** Uma aplicação com interface gráfica que simula um dispositivo a gerar e enviar dados (timestamp e um valor de ponto flutuante) para o servidor em intervalos de tempo configuráveis.
3.  **Cliente Supervisor (`QtTcpClientConsumer`):** Uma aplicação com interface gráfica que se conecta ao servidor para visualizar os dados. Permite listar os produtores de dados ativos, selecionar um deles e exibir os seus dados num gráfico de tempo vs. valor que se atualiza em tempo real.

---

## Funcionalidades Principais

### Servidor
-   Aceita múltiplas conexões de clientes simultaneamente.
-   Interpreta comandos de texto simples (`list`, `get`, `set`).
-   Armazena os dados recebidos dos clientes produtores.

### Cliente Produtor
-   Interface gráfica para configurar o endereço IP do servidor.
-   Controlos para definir a faixa de valores (mínimo e máximo) e o intervalo de tempo (timing) para o envio de dados.
-   Botões para conectar/desconectar do servidor e para iniciar/parar o envio de dados.
-   Área de texto para visualizar os dados que estão a ser enviados.

### Cliente Supervisor (Consumidor)
-   Interface gráfica para conectar a um servidor através do seu IP.
-   Botão "Update" para solicitar e exibir uma lista de todos os clientes produtores que enviaram dados para o servidor.
-   Visualização dos dados de um produtor selecionado num gráfico que se atualiza em tempo real.
-   Possibilidade de definir o intervalo de atualização do gráfico.

---

## Como Compilar e Executar

### Pré-requisitos
-   C++ Compiler (g++)
-   Qt 6 (Framework e Qt Creator)
-   Git

### Passos para Execução
1.  **Clone o repositório:**
    ```bash
    git clone [https://github.com/seu-usuario/seu-repositorio.git](https://github.com/seu-usuario/seu-repositorio.git)
    cd seu-repositorio
    ```
2.  **Abra os projetos no Qt Creator:** Abra os ficheiros `.pro` de cada um dos três módulos (`QtServerMultithread`, `QtTcpClientProducer`, `QtTcpClientConsumer`).
3.  **Compile cada projeto:** Selecione um projeto como ativo e clique em "Build". Repita para os três.
4.  **Execute na seguinte ordem:**
    a. Execute o projeto **`QtServerMultithread`**. Anote o endereço IP que aparece na saída da aplicação.
    b. Execute o projeto **`QtTcpClientProducer`**.
    c. Execute o projeto **`QtTcpClientConsumer`**.

---

## Como Usar o Sistema

1.  Com os três programas em execução, na janela do **Produtor**, insira o IP do servidor, defina os parâmetros (Min, Max, Timing) e clique em `Connect` e depois em `Start`.
2.  Na janela do **Consumidor**, insira o mesmo IP do servidor e clique em `Connect`.
3.  Clique em `Update` para ver o IP do Produtor aparecer na lista.
4.  Selecione o IP na lista, defina um `Timing` para a atualização e clique em `Start` para visualizar o gráfico.

---

## Tecnologias Utilizadas
-   **Linguagem:** C++
-   **Framework:** Qt 6
-   **Comunicação:** TCP/IP Sockets
-   **IDE:** Qt Creator

---

## Autor
* **Deyvid A. N. Macedo** - *Desenvolvimento dos clientes Produtor e Supervisor*
