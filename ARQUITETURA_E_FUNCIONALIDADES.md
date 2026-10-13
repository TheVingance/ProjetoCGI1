# Documentação do Sistema Gráfico 2D/3D - Computação Gráfica

Este documento descreve a arquitetura, conceitos matemáticos, algoritmos implementados e o **mapeamento exato de arquivos e números de linha** de cada funcionalidade do projeto para facilitar o estudo e consulta rápida.

---

## 📑 Tabela-Resumo: Funcionalidades, Arquivos e Linhas

| Funcionalidade / Etapa | Arquivo Principal | Linhas no Código | Descrição Resumida |
| :--- | :--- | :--- | :--- |
| **Mundo -> Viewport (Tela)** | [`Unit1.cpp`](Unit1.cpp#L19-L27) | 19–27 | Conversão de coordenadas reais de mundo para pixels inteiros |
| **Viewport (Tela) -> Mundo** | [`Uprincipal.cpp`](Uprincipal.cpp#L27-L33) | 27–33 | Inversão dos cliques de mouse em pixels para coordenadas do mundo |
| **Rasterização: Reta Padrão Canvas** | [`uPoligono.cpp`](uPoligono.cpp#L182-L193) | 182–193 | Uso nativo de `MoveTo` e `LineTo` do VCL Canvas |
| **Rasterização: Algoritmo DDA** | [`uPoligono.cpp`](uPoligono.cpp#L19-L54) | 19–54 | Digital Differential Analyzer com incrementos dx, dy fracionários |
| **Rasterização: Reta de Bresenham** | [`uPoligono.cpp`](uPoligono.cpp#L60-L121) | 60–121 | Algoritmo de aritmética inteira com variável de erro acumulado |
| **Rasterização: Círculo Ponto Médio** | [`uPoligono.cpp`](uPoligono.cpp#L124-L160) | 124–160 | Traçado por simetria nos 8 octantes |
| **Translação 2D** | [`uPoligono.cpp`](uPoligono.cpp#L231-L235) / [`Uprincipal.cpp`](Uprincipal.cpp#L250-L268) | 231–235 / 250–268 | Deslocamento por dx e dy |
| **Escalonamento 2D** | [`uPoligono.cpp`](uPoligono.cpp#L237-L241) / [`Uprincipal.cpp`](Uprincipal.cpp#L297-L314) | 237–241 / 297–314 | Multiplicação por Sx e Sy |
| **Rotação 2D Simples** | [`uPoligono.cpp`](uPoligono.cpp#L243-L247) / [`Uprincipal.cpp`](Uprincipal.cpp#L316-L332) | 243–247 / 316–332 | Rotação trigonométrica em torno da origem (0, 0) |
| **Rotação 2D Homogênea** | [`uPoligono.cpp`](uPoligono.cpp#L265-L305) / [`Uprincipal.cpp`](Uprincipal.cpp#L334-L349) | 265–305 / 334–349 | Matrizes 3x3: T(-Pm) * R(theta) * T(Pm) |
| **Reflexões 2D (X, Y, XY)** | [`uPoligono.cpp`](uPoligono.cpp#L307-L324) / [`Uprincipal.cpp`](Uprincipal.cpp#L351-L383) | 307–324 / 351–383 | Inversão de sinais nos eixos |
| **Clipping: Outcode 4 bits** | [`Unit1.cpp`](Unit1.cpp#L62-L75) | 62–75 | Classificação de região Cohen-Sutherland (Left, Right, Bottom, Top) |
| **Clipping: Cohen-Sutherland** | [`uPoligono.cpp`](uPoligono.cpp#L478-L610) / [`Uprincipal.cpp`](Uprincipal.cpp#L525-L585) | 478–610 / 525–585 | Recorte de polígonos contra janela com cálculo de interseções |
| **Câmera 2D: Pan e Zoom** | [`Uprincipal.cpp`](Uprincipal.cpp#L196-L239) | 196–239 | Movimentação da janela de mundo e ampliação/redução |
| **Coordenadas Mouse (Canvas)** | [`Uprincipal.cpp`](Uprincipal.cpp#L82-L90) | 82–90 | Rastreamento dinâmico no evento `Image1MouseMove` |
| **Desenho Interativo com Mouse** | [`Uprincipal.cpp`](Uprincipal.cpp#L138-L161) | 138–161 | Botão esquerdo: vértice / Botão direito: fecha polígono |
| **Curva: de Casteljau** | [`uPoligono.cpp`](uPoligono.cpp#L326-L349) / [`Uprincipal.cpp`](Uprincipal.cpp#L385-L410) | 326–349 / 385–410 | Subdivisão recursiva de curvas com critério de parada <= 1 |
| **Curva: Hermite** | [`uPoligono.cpp`](uPoligono.cpp#L351-L376) / [`Uprincipal.cpp`](Uprincipal.cpp#L412-L440) | 351–376 / 412–440 | Polinômio cúbico com vetores tangentes R1 e R4 |
| **Curva: Bézier (Bernstein)** | [`uPoligono.cpp`](uPoligono.cpp#L378-L394) / [`Uprincipal.cpp`](Uprincipal.cpp#L442-L470) | 378–394 / 442–470 | Avaliação direta dos polinômios de Bernstein |
| **Curva: B-Spline Uniforme** | [`uPoligono.cpp`](uPoligono.cpp#L396-L425) / [`Uprincipal.cpp`](Uprincipal.cpp#L472-L500) | 396–425 / 472–500 | Multiplicação matricial 1/6 * M * G |
| **Curva: Forward Differences** | [`uPoligono.cpp`](uPoligono.cpp#L427-L469) / [`Uprincipal.cpp`](Uprincipal.cpp#L502-L523) | 427–469 / 502–523 | Método incremental por derivadas discretas |
| **Transformações 3D (Ponto3D)** | [`uPonto3D.cpp`](uPonto3D.cpp#L28-L98) | 28–98 | Translação, escala e rotações nos eixos X, Y, Z |
| **Rotação 3D Eixo Arbitrário** | [`uPonto3D.cpp`](uPonto3D.cpp#L101-L144) | 101–144 | Algoritmo clássico dos 7 passos de alinhamento com os eixos |
| **Projeções 3D -> 2D** | [`uPonto3D.cpp`](uPonto3D.cpp#L146-L168) | 146–168 | Ortográfica (146), Perspectiva (152) e Cavaleira (162) |
| **Modelo de Arame (Objeto3D)** | [`uObjeto3D.cpp`](uObjeto3D.cpp#L59-L149) | 59–149 | Gerenciamento de segmentos 3D, centro e transformações |
| **Geração Primitivas 3D (Cubo/Pirâmide)**| [`uObjeto3D.cpp`](uObjeto3D.cpp#L151-L214) | 151–214 | Construção geométrica de cubos e pirâmides em wireframe |
| **Carregamento de Arquivo 3D (TXT/OBJ)** | [`uObjeto3D.cpp`](uObjeto3D.cpp#L216-L404) | 216–404 | Parser de arquivos texto, deduplicação de arestas e reconstrução |
| **Renderização 3D na Viewport** | [`uObjeto3D.cpp`](uObjeto3D.cpp#L428-L521) | 428–521 | Projeção dos vértices, mapeamento de tela e rasterização |
| **Controles Interativos 3D na UI** | [`Uprincipal.cpp`](Uprincipal.cpp#L614-L848) | 614–848 | Botões de rotações Rx, Ry, Rz, escala, translação Z e projeção |
| **Display File da Cena** | [`uDisplay.cpp`](uDisplay.cpp#L15-L60) | 15–60 | Lista de polígonos e objetos 3D com varredura para redesenho |

---

## 1. Mapeamento de Coordenadas (Window-to-Viewport Transformation)

Converte entre o sistema cartesiano do **Mundo** (com origem (0, 0) central e números reais) e o sistema da **Viewport / Tela** (com origem no canto superior esquerdo e números inteiros em pixels).

### A. Mundo -> Viewport (Tela)
* **Arquivo**: [`Unit1.cpp`](Unit1.cpp#L19-L27) (linhas 19–27)
* **Funções**:
  * `int Ponto::xW2Vp(Janela mundo, Janela Vp)` (linhas 19–22):
    `Xvp = ((Xw - XwMin) / (XwMax - XwMin)) * (XvpMax - XvpMin)`
  * `int Ponto::yW2Vp(Janela mundo, Janela Vp)` (linhas 24–27):
    `Yvp = (1 - ((Yw - YwMin) / (YwMax - YwMin))) * (YvpMax - YvpMin)`

### B. Viewport (Tela) -> Mundo
* **Arquivo**: [`Uprincipal.cpp`](Uprincipal.cpp#L27-L33) (linhas 27–33)
* **Funções**:
  * `double xVp2Mundo(int x, Janela mundo, Janela vp)` (linhas 27–29)
  * `double yVp2Mundo(int y, Janela Mundo, Janela vp)` (linhas 31–33)

---

## 2. Algoritmos de Rasterização 2D

### A. Algoritmo DDA (Digital Differential Analyzer)
* **Arquivo**: [`uPoligono.cpp`](uPoligono.cpp#L19-L54) (linhas 19–54)
* **Função**: `void Poligono::desenharDDA(Ponto p1, Ponto p2, Janela mundo, Janela vp, TCanvas *canvas)`
* **Conceito**: Calcula incrementos fracionários dx e dy baseados no maior lado (`length = max(|dx|, |dy|)`) e plota pixels arredondando as coordenadas (`FLOOR(x)`, `FLOOR(y)`).

### B. Algoritmo de Bresenham para Retas
* **Arquivo**: [`uPoligono.cpp`](uPoligono.cpp#L60-L121) (linhas 60–121)
* **Função**: `void Poligono::desenharBRESENHAM(Ponto p1, Ponto p2, Janela mundo, Janela vp, TCanvas *canvas)`
* **Conceito**: Traça retas usando estritamente **aritmética inteira** e erro acumulado (`erro = 2*deltay - deltax`), tratando todos os 8 octantes através de troca de eixos (`interchange`) e sinais de avanço (`signalx`, `signaly`).

### C. Algoritmo de Bresenham / Ponto Médio para Circunferências
* **Arquivo**: [`uPoligono.cpp`](uPoligono.cpp#L124-L160) (linhas 124–160)
* **Funções**:
  * `void Poligono::DesenhaCircunferencia(int xc, int yc, int r)` (linhas 124–146): Cálculo incremental do primeiro octante com variável de decisão p = 1 - r.
  * `void Poligono::DesenhaPontoCircunferencia(int xc, int yc, int x, int y)` (linhas 150–160): Simetria de 8 octantes gerando os pontos simétricos correspondentes.
* **Evento na UI**: [`Uprincipal.cpp`](Uprincipal.cpp#L270-L295) (linhas 270–295, `CirculoClick`).

### D. Seleção de Tipo de Reta e Renderização Geral
* **Arquivo**: [`uPoligono.cpp`](uPoligono.cpp#L163-L211) (linhas 163–211)
* **Função**: `void Poligono::desenha(TCanvas *canvas, Janela mundo, Janela vp, int TipoReta)`
  * `TipoReta == 0`: Reta padrão VCL via `MoveTo` e `LineTo` (linhas 183–192)
  * `TipoReta == 1`: Reta DDA (linhas 194–200)
  * `TipoReta == 2`: Reta Bresenham (linhas 202–208)

---

## 3. Transformações Geométricas 2D

Todas as transformações operam sobre os vértices do polígono selecionado no Display File.

| Transformação | Função no Modelo ([`uPoligono.cpp`](uPoligono.cpp)) | Operação no Ponto ([`Unit1.cpp`](Unit1.cpp)) | Evento do Botão ([`Uprincipal.cpp`](Uprincipal.cpp)) |
| :--- | :--- | :--- | :--- |
| **Translação** | Linhas 231–235 (`translacao`) | Linhas 38–41 (`x += dx; y += dy;`) | Linhas 250–268 (`btTranslornarClick`) |
| **Escalonamento** | Linhas 237–241 (`escalonamento`) | Linhas 43–46 (`x *= dx; y *= dy;`) | Linhas 297–314 (`btEscalonarClick`) |
| **Rotação Simples** | Linhas 243–247 (`rotacao`) | Linhas 48–53 (Rotação na origem) | Linhas 316–332 (`btRotacionarClick`) |
| **Ponto Médio** | Linhas 249–263 (`pontoMedio`) | N/A | Utilizado pela rotação homogênea |
| **Rotação Homogênea** | Linhas 265–305 (`rotacaoHomogenea`) | Linhas 55–60 | Linhas 334–349 (`btHomoRotacaoClick`) |
| **Reflexão Eixo X** | Linhas 307–311 (`reflexaoEixoX`) | `x = -x;` | Linhas 351–360 (`btReflexaoEixoXClick`) |
| **Reflexão Eixo Y** | Linhas 313–317 (`reflexaoEixoY`) | `y = -y;` | Linhas 362–371 (`YClick`) |
| **Reflexão Origem (XY)** | Linhas 319–324 (`reflexaoEixoXY`) | `x = -x; y = -y;` | Linhas 373–383 (`btEixoXYClick`) |

---

## 4. Câmera Virtual 2D (Pan & Zoom)

Gerenciamento dinâmico dos limites da janela de mundo:

* **Atualização do Mundo**: [`Uprincipal.cpp`](Uprincipal.cpp#L163-L184) (linhas 163–184)
* **Pan Cima**: [`Uprincipal.cpp`](Uprincipal.cpp#L196-L200) (linhas 196–200, `btCimaClick`): ymin += 10, ymax += 10
* **Pan Baixo**: [`Uprincipal.cpp`](Uprincipal.cpp#L202-L207) (linhas 202–207, `btBaixoClick`): ymin -= 10, ymax -= 10
* **Pan Esquerda**: [`Uprincipal.cpp`](Uprincipal.cpp#L209-L214) (linhas 209–214, `btEsquerdaClick`): xmin -= 10, xmax -= 10
* **Pan Direita**: [`Uprincipal.cpp`](Uprincipal.cpp#L216-L221) (linhas 216–221, `btDireitaClick`): xmin += 10, xmax += 10
* **Zoom Out (-)**: [`Uprincipal.cpp`](Uprincipal.cpp#L223-L230) (linhas 223–230, `btZoomOutClick`): expande os limites do mundo
* **Zoom In (+)**: [`Uprincipal.cpp`](Uprincipal.cpp#L232-L239) (linhas 232–239, `btZoomInClick`): contrai os limites do mundo

---

## 5. Recorte de Linhas 2D (Algoritmo de Cohen-Sutherland)

Recorte de arestas contra a janela retangular de clipping em coordenadas de mundo ( [-100, -100] a [100, 100] ):

### A. Cálculo do Código de Região (Outcode de 4 bits)
* **Arquivo**: [`Unit1.cpp`](Unit1.cpp#L62-L75) (linhas 62–75)
* **Função**: `int Ponto::cohen(Janela clipping)`
  * Bit 0 (`1`): À esquerda (x < xmin)
  * Bit 1 (`2`): À direita (x > xmax)
  * Bit 2 (`4`): Abaixo (y < ymin)
  * Bit 3 (`8`): Acima (y > ymax)

### B. Algoritmo de Recorte e Interseção
* **Arquivo**: [`uPoligono.cpp`](uPoligono.cpp#L478-L610) (linhas 478–610)
* **Função**: `Poligono Poligono::clipping(Janela clip)`
* **Etapas**:
  * `(c1 | c2) == 0`: Aceitação trivial (linhas 543–547).
  * `(c1 & c2) != 0`: Rejeição trivial.
  * Interseção com as 4 bordas: linhas 497–533 e 553–606 utilizando a inclinação da reta m = (y2 - y1) / (x2 - x1).

### C. Ação na Interface
* **Arquivo**: [`Uprincipal.cpp`](Uprincipal.cpp#L525-L585) (linhas 525–585)
* **Função**: `void __fastcall TForm1::btClippingClick(TObject *Sender)`

---

## 6. Curvas Paramétricas e Splines

Gera novos polígonos aproximando curvas a partir de pontos de controle:

| Tipo de Curva | Implementação Matemática ([`uPoligono.cpp`](uPoligono.cpp)) | Evento na Interface ([`Uprincipal.cpp`](Uprincipal.cpp)) |
| :--- | :--- | :--- |
| **de Casteljau** (Bézier recursivo) | Linhas 326–349 (`casteljau` e `casteljauRecursivo`) | Linhas 385–410 (`btCurvaCasteljauClick`) |
| **Hermite** (Cúbica com tangentes) | Linhas 351–376 (`hermite`) | Linhas 412–440 (`btHermiteClick`) |
| **Bézier Cúbica** (Polinômios Bernstein) | Linhas 378–394 (`bezier`) | Linhas 442–470 (`btBezierClick`) |
| **B-Spline Cúbica Uniforme** | Linhas 396–425 (`bSpline`, matriz base M) | Linhas 472–500 (`btBSsplineClick`) |
| **Diferenças Progressivas (Forward Diff)** | Linhas 427–469 (`fwdDifferences`) | Linhas 502–523 (`btSplineDifferenceClick`) |

---

## 7. Modelagem e Visualização 3D (Wireframe)

### A. Classe `Ponto3D` ([`uPonto3D.cpp`](uPonto3D.cpp) / [`uPonto3D.h`](uPonto3D.h))
* **Translação 3D**: Linhas 28–34 (`translacao(dx, dy, dz)`)
* **Escalonamento 3D**: Linhas 36–45 (`escalonamento(sx, sy, sz)`)
* **Rotação Eixo X**: Linhas 47–62 (`rotacaoX(graus)`)
* **Rotação Eixo Y**: Linhas 64–79 (`rotacaoY(graus)`)
* **Rotação Eixo Z**: Linhas 81–96 (`rotacaoZ(graus)`)
* **Rotação em Torno de Eixo Arbitrário (7 Passos)**: Linhas 101–144 (`rotacaoEixoArbitrario`)
  * T(-P1) -> Rx -> Rz -> Ry(theta) -> Rz_inv -> Rx_inv -> T(+P1)
* **Projeção Ortográfica**: Linhas 146–150 (`projetaOrtografica()`)
* **Projeção Perspectiva**: Linhas 152–160 (`projetaPerspectiva(d)`)
  `X_2D = (x * d) / (d - z),   Y_2D = (y * d) / (d - z)`
* **Projeção Cavaleira**: Linhas 162–168 (`projetaCavaleira(angGraus, fator)`)

### B. Classe `Objeto3D` ([`uObjeto3D.cpp`](uObjeto3D.cpp) / [`uObjeto3D.h`](uObjeto3D.h))
* **Transformações de Objeto**:
  * Translação: Linhas 72–76
  * Escalonamento no centro: Linhas 86–91
  * Rotações nos eixos X, Y, Z: Linhas 94–113
  * Rotação no baricentro: Linhas 115–123 (`rotacaoNoCentro`)
  * Rotação em eixo arbitrário: Linhas 125–130
  * Cálculo do centroide/baricentro: Linhas 132–149 (`centro()`)
* **Geradores Primitivos**:
  * Cubo Wireframe: Linhas 151–186 (`criarCubo`)
  * Pirâmide Wireframe: Linhas 188–214 (`criarPiramide`)
### C. Leitura de Arquivo Texto e Formato da Pirâmide (`piramide.txt`)
O método `Objeto3D::carregarDeArquivo(caminhoArquivo)` ([`uObjeto3D.cpp:L216-404`](uObjeto3D.cpp#L216-L404)) suporta múltiplos formatos e processa nativamente o **formato da aula prática (anotado no quadro)**:
* **Formato de Faces Triangulares (Quadro da Aula 6)**:
  Contém 12 linhas com coordenadas inteiras x, y, z, correspondentes às 4 faces triangulares vistas de cima que convergem no ápice (0, 0, 50):
  ```text
  -50 -50 0    # Face 1 (Vértices 1, 2, 5)
  -50 50 0
  0 0 50
  -50 -50 0    # Face 2 (Vértices 1, 4, 5)
  50 -50 0
  0 0 50
  -50 50 0     # Face 3 (Vértices 2, 3, 5)
  50 50 0
  0 0 50
  50 50 0      # Face 4 (Vértices 3, 4, 5)
  50 -50 0
  0 0 50
  ```
* **Processamento e Deduplicação de Arestas**:
  O método lê as 4 faces triangulares, extrai os segmentos (P0, P1), (P_1, P_2) e (P_2, P_0) e descarta arestas compartilhadas duplicadas (linhas 365–385), gerando com exatidão as **8 arestas do modelo de arame da pirâmide**:
  * 4 arestas da base quadrada: [(-50,-50) -> (-50,50)], [(-50,50) -> (50,50)], [(50,50) -> (50,-50)], [(50,-50) -> (-50,-50)].
  * 4 arestas laterais subindo ao ápice: dos 4 cantos da base até (0, 0, 50).
* **Outros formatos suportados**:
  * Lista de segmentos diretos: linhas com `x1 y1 z1 x2 y2 z2`.
  * Formato com blocos `VERTICES N` e `ARESTAS M`.
  * Formato Wavefront .obj simples (`v` e `l`/`f`).

### D. Pipeline Completo: Do Arquivo TXT à Tela 2D

```
[piramide.txt] 
      │
      ▼
1. Uprincipal.cpp (L638: btCarregarPiramideTxtClick) ──► Localiza o arquivo na pasta e instancia o objeto
      │
      ▼
2. uObjeto3D.cpp (L216: carregarDeArquivo) ───────────► Parse linha a linha (ifstream), extrai vértices e deduplica segmentos
      │
      ▼
3. uDisplay.cpp (L15: DisplayFile::desenha) ──────────► Percorre display.objetos3D chamando desenha()
      │
      ▼
4. uObjeto3D.cpp (L428: Objeto3D::desenha) ───────────► Projeta 3D->2D (Perspectiva/Ortográfica/Cavaleira), mapeia para Viewport e rasteriza no TCanvas
```

### E. Controles 3D na Interface ([`Uprincipal.cpp`](Uprincipal.cpp))
* **Criar Cubo 3D**: Linhas 614–624 (`btCriarCubo3DClick`)
* **Criar Pirâmide 3D**: Linhas 626–636 (`btCriarPiramide3DClick`)
* **Carregar `piramide.txt`**: Linhas 638–680 (`btCarregarPiramideTxtClick`)
* **Limpar 3D**: Linhas 682–687 (`btLimpar3DClick`)
* **Alterar Projeção (Ortográfica / Perspectiva / Cavaleira)**: Linhas 689–693 (`rgProjecao3DClick`)
* **Rotações Interativas (Rx +/- 15 graus)**: Linhas 695–715 (`btRotXMaisClick`, `btRotXMenosClick`)
* **Rotações Interativas (Ry +/- 15 graus)**: Linhas 717–737 (`btRotYMaisClick`, `btRotYMenosClick`)
* **Rotações Interativas (Rz +/- 15 graus)**: Linhas 739–759 (`btRotZMaisClick`, `btRotZMenosClick`)
* **Escala 3D (+ / -)**: Linhas 762–783 (`btEscalaMais3DClick`, `btEscalaMenos3DClick`)
* **Translação em Z (+ / -)**: Linhas 785–806 (`btTransZMaisClick`, `btTransZMenosClick`)
* **Reset 3D**: Linhas 808–816 (`btReset3DClick`)
* **Rotação em Eixo Arbitrário**: Linhas 818–848 (`btRotEixoArbitrarioClick`)

---

## 8. Display File e Gerenciamento da Cena

* **DisplayFile**: [`uDisplay.cpp`](uDisplay.cpp#L15-L60) (linhas 15–60)
  * `DisplayFile::desenha`: limpa tela e desenha polígonos 2D e objetos 3D (linhas 15–46).
* **Inicialização da Cena**: [`Uprincipal.cpp`](Uprincipal.cpp#L38-L78) (linhas 38–78, construtor de `TForm1`, cria eixos cartesianos e retângulo de recorte).
* **Desenho com Mouse no Canvas**: [`Uprincipal.cpp`](Uprincipal.cpp#L138-L161) (linhas 138–161, `Image1MouseDown`).
* **Limpar Viewport**: [`Uprincipal.cpp`](Uprincipal.cpp#L112-L129) (linhas 112–129, `btLimparClick`).
