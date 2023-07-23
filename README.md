# Estimador de fila M/M/1 - Código auxiliar | Trabalho 3 | Modelagem e Avaliação de Desempenho 2023.1

<br>

Esse repositório contém o código de um estimador do $\rho$ de uma fila M/M/1.

<br>

# Dependências

- Cabeçalho de threads POSIX
- Python 3 e Python3-dev
- Matplotlib
- G++

<br>

# Como funciona?

O programa recebe n arquivos texto, cada um contendo o número de pessoas no sistema após a saída de um processo. Cada um desses arquivos serve para a amostra
do programa. Ele calcula a média e variância da probabilidade de ocorrência de um certo número de processos, bem como do rho. São gerados os gráficos da PDF e CDF do número de processos e também o histograma do $\rho$.

<br>

# Como utilizar?

Clone o repositório:

```shell
$ git clone https://github.com/thiagoc01/estimador-mm1.git
```

Compile com:

```shell
$ make 
```

**OBS.: O make está orientado para o Linux apenas.**

Execute o programa:

```shell
$ ./estimador-mm1 <quantidade de arquivos na amostra> [caminho do arquivo] 
```

O programa lê a quantidade de arquivos passada baseado no caminho. Por exemplo, se o caminho for "/tmp/trace", ele irá ler "/tmp/trace1", "/tmp/trace2" e assim segue até a quantidade fornecida. Logo, todos os traces devem estar no caminho dado.

Se o caminho não for especificado, assume-se que todos os arquivos estão no diretório do executável.

Qualquer arquivo que contenha números inteiros representando o número de clientes é utilizável aqui. Caso você queira testar ou utilizar uma simulação base, utilize o simulador em https://github.com/simulador-mm1.

<br>

# Instalação de dependências

Certifique-se de que tenha instalado as dependências:

```bash
$ sudo apt install python3
$ sudo apt install python3-dev
$ sudo apt install pip
$ pip install matplotlib
$ sudo apt install g++
```

Nesse exemplo, o gerenciador de pacotes é o apt.

Em um ambiente Windows, tenha o make instalado via chocolatey, o g++ e o python na pasta padrão. Lembre-se de adicioná-los ao PATH.




