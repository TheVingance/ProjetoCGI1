# Guia de Apresentação e Estudo - Computação Gráfica

Este documento foi criado especificamente para a **apresentação do trabalho ao professor**. Ele contém:
1. **As 4 Frases de Ouro para Decorar Hoje à Noite** (respostas rápidas e certeiras).
2. **Roteiro de Demonstração na Tela** (o que clicar e o que falar).
3. **As 7 Perguntas Clássicas de Arguição** com as respostas prontas e os locais exatos no código.
4. **Colinha Rápida** (botão da interface -> linha do código).

> **Dica de leitura:** Todas as explicações usam linguagem direta e falada (sem fórmulas LaTeX brutas), para você ler com fluidez e responder com naturalidade.

---

## 🎨 Curvas Paramétricas e Splines

### 1. Curva de Bézier (Polinômios de Bernstein)
* **Arquivos e Linhas:** `uPoligono.cpp` (378–394) / `Uprincipal.cpp` (442–470)
* **O que é:** Uma curva suave definida por pontos de controle (geralmente 4 pontos: P1, P2, P3 e P4).
* **Como funciona:**
  * O primeiro (P1) e o último ponto (P4) são os extremos por onde a curva obrigatoriamente passa (interpolação).
  * Os pontos intermediários (P2 e P3) atuam como "imãs", puxando a curva na direção deles, mas a curva geralmente não encosta neles (aproximação).
  * O cálculo varia um parâmetro `t` de 0.0 até 1.0 usando os polinômios de combinação de Bernstein.
* **Pergunta do Professor:** *"A curva de Bézier passa por todos os pontos de controle?"*
  * **Resposta:** *"Não, professor. Ela interpola (passa por dentro) apenas o ponto inicial e o ponto final. Os pontos intermediários servem apenas para definir a curvatura e a inclinação das tangentes."*

---

### 2. Algoritmo de Casteljau (Subdivisão Recursiva)
* **Arquivos e Linhas:** `uPoligono.cpp` (326–349) / `Uprincipal.cpp` (385–410)
* **O que é:** Um método geométrico e recursivo para desenhar a curva de Bézier sem precisar calcular os polinômios diretamente.
* **Como funciona:**
  * Ele pega os pontos de controle e calcula pontos médios (interpolações lineares) entre segmentos adjacentes.
  * Repete essa divisão formando triângulos de pontos até que a distância entre os pontos seja menor que um limite pré-estabelecido (no código, critério de parada <= 1 pixel).
  * Quando a reta é pequena o suficiente, traça-se o segmento na tela.
* **Vantagem:** Muito estável numericamente e fácil de subdividir a curva em pedaços menores.
* **Pergunta do Professor:** *"Qual é o critério de parada do algoritmo de Casteljau no seu código?"*
  * **Resposta:** *"O critério de parada é a distância euclidiana entre os pontos ou o comprimento do segmento. Quando o segmento se torna menor ou igual a 1 pixel, a recursão para e o algoritmo desenha uma reta simples, pois o olho humano não distingue mais curvatura nessa escala."*

---

### 3. Curva de Hermite
* **Arquivos e Linhas:** `uPoligono.cpp` (351–376) / `Uprincipal.cpp` (412–440)
* **O que é:** Uma curva cúbica que é definida por **2 pontos de extremidade** (P1 e P2) e **2 vetores tangentes/velocidades** (R1 e R2).
* **Como funciona:**
  * Em vez de usar pontos intermediários para puxar a curva (como Bézier), o usuário define a direção e a força de inclinação com que a curva "sai" de P1 e com que ela "chega" em P2.
  * Se aumentarmos o tamanho do vetor tangente, a curva faz uma volta mais aberta antes de chegar ao destino.
* **Diferença para Bézier:** Bézier usa 4 pontos de posição no espaço. Hermite usa 2 pontos de posição e 2 vetores de direção.
* **Pergunta do Professor:** *"O que acontece se eu inverter o sentido de um dos vetores tangentes em Hermite?"*
  * **Resposta:** *"A curva muda radicalmente de trajetória: em vez de fazer um arco direto, ela é forçada a dar um laço (looping) ou uma inflexão em 'S' para conseguir chegar ao ponto final na direção oposta exigida pelo vetor."*

---

### 4. B-Splines Uniformes
* **Arquivos e Linhas:** `uPoligono.cpp` (396–425) / `Uprincipal.cpp` (472–500)
* **O que é:** Uma sequência de curvas cúbicas conectadas suavemente, calculada usando matrizes polinomiais (fator 1/6).
* **O grande diferencial (Controle Local):**
  * Em curvas de Bézier com muitos pontos, se você mover um único ponto, **toda a curva** se deforma (controle global).
  * Em B-Splines, a curva possui **controle local**: mover um ponto de controle afeta apenas os segmentos vizinhos mais próximos, mantendo o restante da curva inalterado.
  * Ela não passa necessariamente por nenhum dos pontos de controle (nem o primeiro nem o último), gerando um traçado extremamente suave (continuidade C2).
* **Pergunta do Professor:** *"Por que usamos B-Spline em vez de uma curva de Bézier simples em projetos complexos?"*
  * **Resposta:** *"Porque a B-Spline garante controle local e continuidade de curvatura suave entre segmentos. Se alterarmos a posição de um ponto no meio de um desenho grande, só um trecho pequeno é recalculado, sem desarmar o restante da curva."*

---

### 5. Diferenças Finitas (Forward Differences)
* **Arquivos e Linhas:** `uPoligono.cpp` (427–469) / `Uprincipal.cpp` (502–523)
* **O que é:** Uma técnica de otimização numérica para traçar curvas polinomiais de forma ultra rápida.
* **Como funciona:**
  * Em vez de resolver polinômios com potências cúbicas (multiplicações lentas de t*t*t) para cada ponto da tela, calculam-se as diferenças iniciais (derivadas discretas).
  * Depois disso, os próximos pontos da curva são obtidos apenas com **somas e incrementos** dentro do laço de repetição.
* **Vantagem:** Desempenho computacional bruto (reduz cálculos complexos a adições simples).
* **Pergunta do Professor:** *"Qual é a principal vantagem do Forward Differences sobre o cálculo direto?"*
  * **Resposta:** *"O ganho de performance. O cálculo do polinômio exige várias multiplicações e potências a cada passo do loop; com Diferenças Finitas, após a inicialização, todos os pontos subsequentes são gerados apenas com operações de soma."*

---

## 💎 1. As 4 Frases de Ouro para Decorar

Se o professor te interromper durante a apresentação e fizer perguntas teóricas diretas, tenha estas 4 respostas na ponta da língua:

1. **Por que Bresenham é melhor que DDA?**  
   > *"Porque o Bresenham opera estritamente com números inteiros e cálculo de erro acumulado, sem nenhuma divisão e sem ponto flutuante (float) no laço de repetição."*

2. **Por que a Rotação Homogênea precisa de 3 matrizes?**  
   > *"Porque a rotação pura sempre gira na origem (0,0). Com as 3 matrizes encadeadas, eu translado o centro do objeto para a origem, rotaciono pelo ângulo desejado e depois translado de volta para o lugar dele, fazendo ele girar no próprio centro."*

3. **Como funciona o algoritmo de Cohen-Sutherland (Clipping)?**  
   > *"Ele classifica cada ponto com um código binário de 4 bits (Esquerda, Direita, Abaixo, Acima). Se o OU binário for zero, os dois pontos estão dentro (aceitação trivial). Se o E binário for diferente de zero, os dois compartilham o mesmo lado de fora (rejeição trivial). Se não for nenhum dos dois, a reta cruza a borda e calculamos o ponto de interseção analítico."*

4. **Como funciona a Projeção Perspectiva no 3D?**  
   > *"Eu divido as coordenadas X e Y pela distância focal (D - Z). Quanto maior a distância Z (mais ao fundo da cena), menor o ponto fica projetado na tela, criando a sensação real de profundidade da visão humana."*

---

## 🎬 2. Roteiro Prático de Apresentação (Passo a Passo na Interface)

Siga esta ordem na hora de demonstrar o sistema para o professor. É uma sequência lógica que mostra domínio do pipeline gráfico:

### Passo 1: Sistema de Coordenadas e Desenho Livre
* **O que fazer:** Mova o cursor do mouse sobre a área cinza de desenho e aponte para o rodapé da tela. Em seguida, clique com o **botão esquerdo** várias vezes para criar pontos e clique com o **botão direito** para fechar o polígono.
* **O que falar:** 
  > *"Professor, o sistema já inicia com os eixos cartesianos X e Y e o retângulo delimitador de recorte. Conforme movo o mouse, o sistema converte dinamicamente em tempo real as coordenadas da tela em pixels para as coordenadas contínuas de mundo no rodapé. Com o botão esquerdo insiro os vértices no Display File e com o botão direito finalizo o polígono."*

### Passo 2: Algoritmos de Rasterização (Linhas e Círculo)
* **O que fazer:** No painel de tipo de reta, alterne entre **DDA** e **Bresenham**, desenhe novos segmentos e depois clique no botão de **Círculo** (informando um raio, por exemplo 60).
* **O que falar:**
  > *"O sistema implementa os três métodos clássicos de traçado: a reta padrão do Windows, o algoritmo DDA por interpolação de ponto flutuante e o algoritmo de Bresenham por aritmética inteira. Para circunferências, implementamos o algoritmo do Ponto Médio com simetria nos 8 octantes."*

### Passo 3: Transformações Geométricas 2D
* **O que fazer:** Selecione o polígono na lista à esquerda. Altere os valores e clique em **Transladar**, depois em **Escalonar**. Em seguida, mostre primeiro a **Rotação Simples** (ele orbita a origem) e depois a **Rotação Homogênea** (ele gira no próprio centro).
* **O que falar:**
  > *"Aqui temos as transformações 2D. Na rotação simples, o objeto gira em torno da origem (0,0), então ele orbita e sai da posição. Já na rotação homogênea, usamos a composição de matrizes 3x3 para transladar o centro do objeto para a origem, rotacionar e devolver ao lugar original, permitindo que ele gire sobre o seu próprio eixo."*

### Passo 4: Recorte de Linhas (Cohen-Sutherland)
* **O que fazer:** Desenhe um polígono que comece fora da caixa vermelha e termine dentro (ou que cruze de um lado a outro). Selecione-o na lista e clique no botão **Clipping**.
* **O que falar:**
  > *"Implementamos o algoritmo clássico de Cohen-Sutherland. Ao acionar o clipping, o algoritmo classifica cada segmento usando códigos de 4 bits para aceitação ou rejeição trivial. Os segmentos que cruzam a borda têm seus pontos de interseção calculados analiticamente e um novo polígono recortado é gerado."*

### Passo 5: Câmera Virtual (Pan e Zoom)
* **O que fazer:** Clique nos botões de navegação: **Cima**, **Baixo**, **Esquerda**, **Direita**, e depois no **Zoom +** e **Zoom -**.
* **O que falar:**
  > *"Aqui controlamos a câmera 2D alterando a janela de mundo. O Pan desloca as coordenadas mínimas e máximas da janela de mundo, e o Zoom aproxima ou afasta a visualização recalculando a matriz de mapeamento para a tela."*

### Passo 6: Modelagem e Visualização 3D
* **O que fazer:** Mude para a aba 3D. Clique em **Pirâmide (TXT)** (ou Cubo). Mude a projeção para **Perspectiva** e clique nos botões **Rx +15°**, **Ry +15°** ou **Rz +15°** algumas vezes.
* **O que falar:**
  > *"No módulo tridimensional, implementamos uma estrutura de modelo de arame (wireframe). O botão carrega as faces triangulares da aula prática direto do arquivo texto, deduplicando as arestas repetidas para gerar o modelo de arame com 8 arestas. Na projeção perspectiva, ao rotacionar a pirâmide nos eixos X, Y e Z, conseguimos visualizar a profundidade e a altura do ápice."*

---

## 🧠 3. As 11 Perguntas Clássicas de Arguição do Professor (com Código e Resposta)

Se o professor pedir para abrir o código e explicar, aqui está exatamente o que abrir e o que responder:

---

### Pergunta 1: *"Onde está o Window-to-Viewport e por que o eixo Y precisa ser invertido?"*
* **Onde mostrar no código:**
  * Mundo para Tela: [`Unit1.cpp: linhas 19 a 27`](Unit1.cpp#L19-L27) (`xW2Vp` e `yW2Vp`).
  * Tela para Mundo: [`Uprincipal.cpp: linhas 27 a 33`](Uprincipal.cpp#L27-L33) (`xVp2Mundo` e `yVp2Mundo`).
* **Como responder:**
  > *"Professor, o mundo cartesiano trabalha com coordenadas reais e com o eixo Y crescendo para cima a partir do centro (0,0). Mas o monitor do computador (a viewport) trabalha com pixels inteiros e o eixo Y cresce para baixo a partir do canto superior esquerdo. Na função `yW2Vp`, usamos o termo `(1 - ...)` para inverter a direção vertical, garantindo que o topo do objeto fique no topo da tela."*

---

### Pergunta 2: *"Qual a diferença entre o DDA e o Bresenham? Por que o Bresenham é melhor?"*
* **Onde mostrar no código:**
  * DDA: [`uPoligono.cpp: linhas 19 a 54`](uPoligono.cpp#L19-L54) (`Poligono::desenharDDA`).
  * Bresenham: [`uPoligono.cpp: linhas 60 a 121`](uPoligono.cpp#L60-L121) (`Poligono::desenharBRESENHAM`).
* **Como responder:**
  > *"O DDA calcula o maior lado entre delta X e delta Y, divide para achar passos fracionários em ponto flutuante (float) e precisa arredondar com FLOOR a cada iteração.*
  > 
  > *Já o algoritmo de Bresenham é superior porque opera **estritamente com números inteiros**. Ele usa uma variável de decisão de erro (`erro = 2*deltay - deltax`). A cada passo, avalia apenas o sinal desse erro com somas e subtrações inteiras para saber se mantém ou avança a coordenada do pixel, sem nenhuma divisão ou ponto flutuante durante o laço."*

---

### Pergunta 3: *"Como funciona o traçado de circunferência pelo método dos 8 octantes?"*
* **Onde mostrar no código:**
  * [`uPoligono.cpp: linhas 124 a 160`](uPoligono.cpp#L124-L160) (`DesenhaCircunferencia` e `DesenhaPontoCircunferencia`).
* **Como responder:**
  > *"Em vez de calcular 360 graus com funções trigonométricas pesadas como seno e cosseno, o algoritmo do Ponto Médio calcula incrementalmente apenas um quadrante de 45 graus (enquanto X for menor que Y). A cada ponto calculado, a função `DesenhaPontoCircunferencia` plota imediatamente 8 pontos simétricos espelhados, alternando os sinais positivo e negativo e invertendo as posições de X e Y."*

---

### Pergunta 4: *"Por que a rotação simples tira o objeto do lugar e como a rotação homogênea resolve isso?"*
* **Onde mostrar no código:**
  * Rotação Simples: [`uPoligono.cpp: linhas 243 a 247`](uPoligono.cpp#L243-L247).
  * Cálculo do Centroide: [`uPoligono.cpp: linhas 249 a 263`](uPoligono.cpp#L249-L263) (`pontoMedio`).
  * Rotação Homogênea: [`uPoligono.cpp: linhas 265 a 305`](uPoligono.cpp#L265-L305) (`rotacaoHomogenea`).
* **Como responder:**
  > *"A rotação matemática pura sempre gira os pontos em torno da origem (0,0). Se o objeto estiver desenhado em outra parte da tela, ele vai orbitar a origem e mudar de posição.*
  > 
  > *Para girar o objeto em torno do seu próprio centro, usamos coordenadas homogêneas com 3 matrizes encadeadas: primeiro calculamos o centroide (ponto médio dos vértices) e transladamos o centro para a origem com a matriz T(-centro). Depois aplicamos a rotação com a matriz R(graus). Por fim, transladamos de volta com a matriz T(+centro). A multiplicação dessas três matrizes gera uma única transformação que gira o objeto sobre si mesmo."*

---

### Pergunta 5: *"Como funciona o algoritmo de recorte (Clipping) de Cohen-Sutherland?"*
* **Onde mostrar no código:**
  * Código de Região (Outcode): [`Unit1.cpp: linhas 62 a 75`](Unit1.cpp#L62-L75) (`Ponto::cohen`).
  * Algoritmo de Recorte: [`uPoligono.cpp: linhas 478 a 610`](uPoligono.cpp#L478-L610) (`Poligono::clipping`).
  * Botão na UI: [`Uprincipal.cpp: linhas 525 a 585`](Uprincipal.cpp#L525-L585) (`btClippingClick`).
* **Como responder:**
  > *"Ele divide o espaço em 9 regiões através de uma máscara de 4 bits: bit 0 para Esquerda, bit 1 para Direita, bit 2 para Abaixo e bit 3 para Acima.*
  > 
  > *Para cada segmento de reta entre dois pontos:*
  > * *Se a operação OU binária entre os códigos for zero (`c1 | c2 == 0`), os dois pontos estão dentro da janela (aceitação trivial).*
  > * *Se a operação E binária for diferente de zero (`c1 & c2 != 0`), ambos compartilham a mesma região externa (rejeição trivial).*
  > * *Se não for nenhum dos dois casos, a reta corta a borda: o algoritmo calcula o ponto exato de interseção com a equação da reta e substitui a ponta de fora pelo novo ponto de corte."*

---

### Pergunta 6: *"Qual a diferença entre a Projeção Ortográfica, Perspectiva e Cavaleira no 3D?"*
* **Onde mostrar no código:**
  * Projeções no Ponto 3D: [`uPonto3D.cpp: linhas 146 a 168`](uPonto3D.cpp#L146-L168).
  * Renderizador do Objeto 3D: [`uObjeto3D.cpp: linhas 428 a 521`](uObjeto3D.cpp#L428-L521) (`Objeto3D::desenha`).
* **Como responder:**
  > *"Na projeção **Ortográfica**, simplesmente descartamos o eixo Z, usando direto X e Y no plano 2D.*
  > 
  > *Na projeção em **Perspectiva**, simulamos a visão humana considerando um observador a uma distância focal D. Dividimos as coordenadas X e Y por (D - Z). Quanto maior a distância Z (mais ao fundo), menor o ponto fica projetado na tela, criando profundidade realista.*
  > 
  > *Na projeção **Cavaleira**, mantemos as proporções frontais sem distorção e projetamos a profundidade Z inclinada em um ângulo de 45 graus."*

---

### Pergunta 7: *"Como o arquivo texto da pirâmide (`piramide.txt`) foi carregado e estruturado?"*
* **Onde mostrar no código:**
  * Parser e Deduplicação: [`uObjeto3D.cpp: linhas 216 a 404`](uObjeto3D.cpp#L216-L404) (`carregarDeArquivo`).
  * Botão de Carregar: [`Uprincipal.cpp: linhas 638 a 680`](Uprincipal.cpp#L638-L680) (`btCarregarPiramideTxtClick`).
* **Como responder:**
  > *"O arquivo `piramide.txt` contém as 12 coordenadas das 4 faces triangulares desenhadas no quadro durante a aula prática.*
  > 
  > *Ao carregar, o método `carregarDeArquivo` lê os triângulos e extrai os segmentos de reta de cada face. Em seguida, ele executa um algoritmo de deduplicação que detecta arestas compartilhadas entre triângulos vizinhos e descarta as cópias repetidas. O resultado final são exatamente as 8 arestas do modelo de arame da pirâmide: 4 arestas da base quadrada e 4 arestas que sobem até o ápice."*

---

### Pergunta 8: *"Como funciona a rotação em torno de um eixo arbitrário no 3D (os 7 passos)?"*
* **Onde mostrar no código:**
  * [`uPonto3D.cpp: linhas 101 a 144`](uPonto3D.cpp#L101-L144) (`Ponto3D::rotacaoEixoArbitrario`).
  * Botão na UI: [`Uprincipal.cpp: linhas 818 a 848`](Uprincipal.cpp#L818-L848) (`btRotEixoArbitrarioClick`).
* **Conceito (O que significa):**
  > As rotações comuns (Rx, Ry, Rz) giram o objeto apenas ao redor dos eixos fixos e retos (horizontal, vertical ou frontal). Girar em eixo arbitrário significa fazer o objeto girar ao redor de **qualquer reta inclinada no espaço**, definida por dois pontos quaisquer P1 e P2 (como um espeto de churrasco atravessando o objeto na diagonal).
* **Como responder ao Professor:**
  > *"Professor, a trigonometria de rotação só sabe calcular giros ao redor dos eixos canônicos X, Y ou Z. Para girar ao redor de uma reta inclinada qualquer definida por dois pontos (P1 e P2), usamos o método clássico dos 7 passos de alinhamento:*
  > 
  > 1. *Transladamos o ponto P1 da reta para a origem T(-P1);*
  > 2. *Rotacionamos em X (Rx) para deitar o vetor no plano XY;*
  > 3. *Rotacionamos em Z (Rz) para alinhar a reta perfeitamente sobre o eixo Y;*
  > 4. *Aplicamos a rotação desejada pelo ângulo escolhido Ry(graus);*
  > 5. *Desfazemos a rotação em Z aplicando a inversa Rz(-);*
  > 6. *Desfazemos a rotação em X aplicando a inversa Rx(-);*
  > 7. *Desfazemos a translação aplicando a inversa T(+P1) para retornar à posição original.*
  > 
  > *Assim, o objeto gira exatamente ao redor daquela reta inclinada sem deformar o resto do cenário."*

---

### Pergunta 9: *"Qual a diferença entre Zoom e Escalonamento?"*
* **Onde mostrar no código:**
  * Escalonamento: [`uPoligono.cpp: linhas 237 a 241`](uPoligono.cpp#L237-L241).
  * Zoom: [`Uprincipal.cpp: linhas 196 a 239`](Uprincipal.cpp#L196-L239).
* **Como responder:**
  > *"O **escalonamento** é uma transformação de modelagem que altera diretamente as coordenadas dos vértices do objeto no espaço de mundo (multiplicando X e Y por fatores de escala). O objeto realmente muda de tamanho na memória.*
  > 
  > *Já o **zoom** é uma transformação de visualização da câmera 2D. Ele não altera nenhum vértice de nenhum objeto no mundo. O que o zoom faz é diminuir ou aumentar as dimensões da **Janela de Mundo (Window)**. Ao dar Zoom In, reduzimos a janela de mundo; como uma porção menor do universo é mapeada para os mesmos pixels da tela (Viewport), os objetos aparentam estar maiores, mas a sua geometria continua intacta."*

---

### Pergunta 10: *"Por que precisamos da conversão Tela para Mundo no clique do mouse?"*
* **Onde mostrar no código:**
  * Funções: [`Uprincipal.cpp: linhas 27 a 33`](Uprincipal.cpp#L27-L33) (`xVp2Mundo` e `yVp2Mundo`).
  * Clique de Desenho: [`Uprincipal.cpp: linhas 138 a 161`](Uprincipal.cpp#L138-L161) (`Image1MouseDown`).
* **Como responder:**
  > *"O evento do mouse entrega coordenadas físicas em pixels da tela (com origem no canto superior esquerdo e Y crescendo para baixo). Porém, todos os polígonos e transformações vivem no Sistema de Coordenadas de Mundo (com origem no centro e Y crescendo para cima).*
  > 
  > *As funções `xVp2Mundo` e `yVp2Mundo` aplicam a matemática inversa do Window-to-Viewport, desinvertendo o eixo vertical com `(1 - ...)`. Se salvássemos pixels puros, qualquer Zoom ou Pan futuro não moveria o desenho feito pelo mouse, quebrando a consistência do mundo virtual."*

---

### Pergunta 11: *"O que é o Display File e por que não desenhamos direto na tela?"*
* **Onde mostrar no código:**
  * [`uDisplay.cpp: linhas 15 a 60`](uDisplay.cpp#L15-L60) (`DisplayFile`).
* **Como responder:**
  > *"O **Display File** é a estrutura de dados central (uma lista de polígonos e objetos 3D) que armazena a descrição geométrica de toda a cena em coordenadas reais de mundo.*
  > 
  > *Não podemos desenhar diretamente no Canvas sem salvar porque qualquer evento do sistema — como minimizar a janela, sobrepor outra tela, ou aplicar Pan e Zoom — apagaria o desenho dos pixels. Com o Display File, sempre que a cena precisa ser atualizada, o sistema limpa o Canvas e varre a lista, reprojetando cada objeto na Viewport de forma consistente."*

---

## ⚡ 4. Colinha de Emergência (Botão -> Arquivo e Linha)

Se o professor apontar para a tela ou seguir a planilha de avaliação, as linhas abaixo estão na **ordem exata de avaliação (1 a 18)**:

| Botão na Tela | O que ele faz | Onde está o clique (UI) | Onde está o cálculo (Modelo) |
| :--- | :--- | :--- | :--- |
| **1. Transformadas** | Mundo para Viewport (Tela) | Desenho contínuo no Canvas | [`Unit1.cpp: 19–27`](Unit1.cpp#L19-L27) |
| **2. Movimentação** | Pan e Zoom (Câmera 2D) | [`Uprincipal.cpp: 196`](Uprincipal.cpp#L196) | [`Uprincipal.cpp: 163`](Uprincipal.cpp#L163) |
| **3. Mundo** | Tela para Mundo (Mouse) | [`Uprincipal.cpp: 82`](Uprincipal.cpp#L82) / [`138`](Uprincipal.cpp#L138) | [`Uprincipal.cpp: 27–33`](Uprincipal.cpp#L27-L33) |
| **4. Reta DDA** | Traçado DDA (RadioGroup = 1) | [`Uprincipal.cpp: 167`](Uprincipal.cpp#L167) | [`uPoligono.cpp: 19`](uPoligono.cpp#L19) |
| **5. Bresenham** | Traçado Bresenham (RadioGroup = 2) | [`Uprincipal.cpp: 167`](Uprincipal.cpp#L167) | [`uPoligono.cpp: 60`](uPoligono.cpp#L60) |
| **6. Circunferência** | Traça círculo por raio | [`Uprincipal.cpp: 270`](Uprincipal.cpp#L270) | [`uPoligono.cpp: 124`](uPoligono.cpp#L124) |
| **7. Translação** | Move objeto em X e Y | [`Uprincipal.cpp: 250`](Uprincipal.cpp#L250) | [`uPoligono.cpp: 231`](uPoligono.cpp#L231) |
| **8. Rotação Simples (rot)** | Gira em torno de (0,0) | [`Uprincipal.cpp: 316`](Uprincipal.cpp#L316) | [`uPoligono.cpp: 243`](uPoligono.cpp#L243) |
| **9. Escalonamento (esc)** | Aumenta/diminui tamanho | [`Uprincipal.cpp: 297`](Uprincipal.cpp#L297) | [`uPoligono.cpp: 237`](uPoligono.cpp#L237) |
| **10. Reflexão (reflexao)** | Espelha nos eixos X, Y e XY | [`Uprincipal.cpp: 351`](Uprincipal.cpp#L351) | [`uPoligono.cpp: 307`](uPoligono.cpp#L307) |
| **11. Rot. Homogênea (Homog)** | Gira no próprio centro | [`Uprincipal.cpp: 334`](Uprincipal.cpp#L334) | [`uPoligono.cpp: 265`](uPoligono.cpp#L265) |
| **12. Clipping** | Corta polígono na caixa | [`Uprincipal.cpp: 525`](Uprincipal.cpp#L525) | [`uPoligono.cpp: 478`](uPoligono.cpp#L478) |
| **13. Curva Casteljau** | Bézier recursivo | [`Uprincipal.cpp: 385`](Uprincipal.cpp#L385) | [`uPoligono.cpp: 326`](uPoligono.cpp#L326) |
| **14. Curva Hermite** | Cúbica com tangentes | [`Uprincipal.cpp: 412`](Uprincipal.cpp#L412) | [`uPoligono.cpp: 351`](uPoligono.cpp#L351) |
| **15. Curva Bézier** | Polinômios de Bernstein | [`Uprincipal.cpp: 442`](Uprincipal.cpp#L442) | [`uPoligono.cpp: 378`](uPoligono.cpp#L378) |
| **16. B-Spline** | B-Spline Uniforme matricial | [`Uprincipal.cpp: 472`](Uprincipal.cpp#L472) | [`uPoligono.cpp: 396`](uPoligono.cpp#L396) |
| **17. Forward Diff.** | Diferenças progressivas | [`Uprincipal.cpp: 502`](Uprincipal.cpp#L502) | [`uPoligono.cpp: 427`](uPoligono.cpp#L427) |
| **18. 3D** | Cubo, Pirâmide, Rotações e Projeções | [`Uprincipal.cpp: 614`](Uprincipal.cpp#L614) | [`uObjeto3D.cpp: 59`](uObjeto3D.cpp#L59) / [`uPonto3D.cpp: 28`](uPonto3D.cpp#L28) |



