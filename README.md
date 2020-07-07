# reploid

Projeto dedicado ao aprendizado de Robótica através do uso da plataforma [ROS](https://www.ros.org/).

**Aluno**: Victor Lima.

**Linguagem utilizada**: C++14.

## Entregavel 1: Planejamento de Caminho do Turtlebot

> Descrição da Pontuação:
> 1. Criar um mapa (occupancy grid) nas dimensões máximas de 9 m de largura x 12 metros de comprimento com paredes externas e internas, ou seja, obstáculos fixos (2 pontos).
> 2. Gerar um caminho que ande por todo o mapa gerado, desviando de obstáculos (6 pontos).
> 3. O caminho gerado deve ser apresentado ao menos 1 figura em forma de mapa com o caminho traçado (2 pontos). 

Algoritmo utilizado para roteamento: A*

### Implementação

Foi desenvolvido um sistema simples para carregamendo de imagens PNG, que, com base na cor de cada pixel, realiza a construção do occupancy grid e dos extremos do trajeto:
- pontos pretos representam obstáculos fixos;
- pontos brancos representam espaços vagos;
- a cor vermelha pura (#FF0000) representa o ponto de partida;
- a cor verde pura (#00FF00) representa o destino;

Com base nas informações obtidas na etapa anterior, o algoritmo A* é aplicado para encontrar o caminho ótimo entre o ponto de partida e o ponto de destino.

O trajeto obtido é, por sua vez, representado no mapa de entrada. Retornado pelo arquivo `saida.png` criado no diretório atual.

### Dependências

    sudo apt install git build-essential cmake

### Instalação e Execução

    git clone https://github.com/vtfr/reploid.git
    cd reploid
    cmake .
    make -j 3
    ./build/megaman
    
### Demonstração

https://www.youtube.com/watch?v=aC-tetMdQJY&feature=youtu.be    
