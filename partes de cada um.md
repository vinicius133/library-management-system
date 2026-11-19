*jose:* livro.c/.h e vetor.c/.h: struct, cadastro, validação de ID, vetor dinâmico, remoção, listagem, buscas, ordenação (incluindo merge sort recursivo), relatórios e agrupamento de categorias.

*vini:* main.c, arquivo.c/.h, utils.c/.h, Makefile e README: menu, entrada de dados, limpeza de espaços, arquivos txt/binário, carregamento, login e exportação CSV.

*git:* criar uma main e uma branch pra cada um. Cada um trabalha nos arquivos combinados, faz commits frequentes e integra as mudanças aos poucos, sempre testando a compilação.

*ordem:* estrutura e interfaces → cadastro/listagem/remoção → arquivos e buscas/ordenação → relatórios e bônus → testes finais.







# 📚 Checklist & Arquitetura — Parte do Vini

> **Escopo:** `utils.c/.h`, `arquivo.c/.h`, `main.c`, `Makefile`, `README.txt` e arquivos de dados (`livros.txt` / `usuarios.txt`).  
> **Bônus sob sua responsabilidade:** 🌟 *Higienização de espaços*, 🔐 *Sistema de login* e 📊 *Exportação de relatório em `.csv`*.

---

## 🛠️ 1. Módulo `utils.h` & `utils.c`
*Blindagem de entrada (`stdin`) e limpeza de texto para evitar que o programa trave ou pule leituras.*

| Função | Tipo | O que faz |
| :--- | :---: | :--- |
| `void limpar_buffer(void)` | Core | Descarta caracteres residuais do `stdin` até encontrar `\n` ou `EOF`. |
| `void ler_string(char *destino, int tamanho)` | Core | Lê strings com espaços via `fgets`, remove o `\n` final, chama `limpar_espacos()` e limpa o buffer se o texto passar do limite. |
| `void limpar_espacos(char *str)` | 🌟 Bônus | Remove espaços sobrando no início, no fim e espaços duplos no meio (ex.: `"  O   Hobbit  "` $\rightarrow$ `"O Hobbit"`). |
| `int ler_inteiro(const char *prompt)` | Core | Valida a leitura de inteiros (ID, ano, opção de menu) e repete o pedido se o usuário digitar letras, evitando loops infinitos. |
| `void pausar_tela(void)` / `limpar_tela(void)` | Core | Padroniza a navegação entre telas (`"Pressione Enter para continuar..."`). |

---

## 💾 2. Módulo `arquivo.h` & `arquivo.c`
*Concentra os **20 pontos de persistência** da rubrica + **2 bônus**. Depende de `vetor.h` (módulo do José).*

### 📄 Persistência em Texto (`livros.txt`)
* **`int salvar_texto(const char *nome_arquivo, const VetorLivros *v)`**
  * Abre em modo `"w"` e grava linha a linha com `fprintf` no formato: `ID;Titulo;Autor;Ano;Categoria\n`.
  * Retorna `1` (sucesso) ou `0` (erro ao abrir).
* **`int carregar_texto(const char *nome_arquivo, VetorLivros *v)`**
  * Abre em modo `"r"` (se não existir na 1ª execução, apenas retorna `0` sem quebrar).
  * Lê cada linha com `fgets`, quebra os campos pelo `;` (`strtok` ou `sscanf`) e insere no vetor dinâmico do José.

### 💽 Persistência em Binário (`livros.dat`)
* **`int salvar_binario(const char *nome_arquivo, const VetorLivros *v)`**
  * Abre em modo `"wb"`.
  * Grava primeiro a quantidade (`fwrite(&v->tamanho, sizeof(int), 1, fp)`) e depois o bloco inteiro do vetor (`fwrite(v->dados, sizeof(Livro), v->tamanho, fp)`).
* **`int carregar_binario(const char *nome_arquivo, VetorLivros *v)`**
  * Abre em modo `"rb"`.
  * Lê a quantidade com `fread`, garante a capacidade no vetor dinâmico do José e carrega todos os structs de uma vez com `fread`.

### 🌟 Funcionalidades Bônus
* **🔐 `int autenticar_usuario(const char *arquivo_usuarios)`**
  * Lê `usuarios.txt` (formato `usuario;senha`). Se não existir, cria um padrão automaticamente (`admin;1234`).
  * Bloqueia o acesso ao menu principal até o usuário acertar login e senha (máx. 3 tentativas).
* **📊 `int exportar_relatorio_csv(const char *nome_arquivo, const VetorLivros *v)`**
  * Gera `relatorio.csv` (modo `"w"`) separado por `;` (abre direto no Excel em PT-BR).
  * Escreve o cabeçalho, lista todos os livros e adiciona ao final as métricas resumidas (total geral, total por categoria, mais antigo e mais recente).

---

## 🎮 3. `main.c` — Orquestração e Fluxo
*Costura a interface do usuário com as funções de negócio do José.*

### 🔄 Ordem de Execução
1. **Inicialização:**
   * Chama `autenticar_usuario("usuarios.txt")` $\rightarrow$ se falhar, encerra o programa.
   * Inicializa o vetor dinâmico (função do José).
   * Carrega automaticamente (ou pergunta se deseja carregar) `livros.dat` / `livros.txt`.
2. **Loop Principal (`do { ... } while (opcao != 0)`):**
   * Mantém uma flag `int alterado = 0;` (vira `1` sempre que houver cadastro ou remoção).
   * **1.** Cadastrar livro *(usa `ler_string` / `ler_inteiro` + função do José)*
   * **2.** Listar todos os livros *(submenu: `a)` Ordenar por título, `b)` Ordenar por ano)*
   * **3.** Buscar livros *(submenu: por título, autor ou categoria)*
   * **4.** Remover livro por ID
   * **5.** Salvar em texto (`livros.txt`) $\rightarrow$ zera `alterado`
   * **6.** Salvar em binário (`livros.dat`) $\rightarrow$ zera `alterado`
   * **7.** Gerar relatórios *(exibe na tela via módulo do José + oferece exportar `.csv`)*
   * **0.** Sair
3. **Encerramento Seguro:**
   * Se `alterado == 1`, pergunta: `"Deseja salvar antes de encerrar? (S/N)"`.
   * Libera a memória do vetor dinâmico (`free`) antes do `return 0`.

---

## 📦 4. Entregáveis Obrigatórios

- [ ] **`Makefile`**:
  * Compilação limpa com `-Wall -Wextra -std=c11 -Iinclude` (garante o ponto de *zero warnings*).
  * Regras `all` (gera o executável `biblioteca`) e `clean` (remove `.o` e executáveis).
- [ ] **`README.txt`**:
  * Estrutura das pastas (`src/`, `include/`, `data/`).
  * Comandos para compilar via `make` e via `gcc` manual.
  * Credenciais padrão de login (`admin` / `1234`) e formato dos arquivos de entrada.
- [ ] **Arquivos de Teste Prontos**:
  * `livros.txt` populado com **pelo menos 5 livros** válidos.
  * `usuarios.txt` com a conta padrão configurada.

---

> ⚠️ **Sincronização Imediata com o José (GitHub)**  
> Antes de codar a integração, confirmem juntos os nomes exatos no `vetor.h` e `livro.h`:
> 1. **Struct do vetor:** `VetorLivros` (campos `Livro *dados`, `int tamanho`, `int capacidade`).
> 2. **Função de inserção:** `int vetor_inserir(VetorLivros *v, Livro l)` — indispensável para você popular o vetor dentro de `carregar_texto()` e `carregar_binario()`.