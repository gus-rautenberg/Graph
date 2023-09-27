// "---------------------------------------\n";
// "             Grafos
//  Gustavo Portela e Augusto Barella
// "---------------------------------------\n";

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstdlib>
using namespace std;

const int MAX_V = 100; 
const int INF = 1e9;


class Graph {
public:
  

  int nV; 

  struct {
    int fleury[MAX_V][MAX_V];
    int E[MAX_V][MAX_V];
    int custo[MAX_V][MAX_V];
    string aresta[MAX_V][MAX_V];
    string vertice[MAX_V];
  } Vetores;

  // Função para criar grafo
  void CreateGraph(int nv) {
    nV = nv;
    for (int i = 0; i < nv; i++) {
      for (int j = 0; j < nv; j++) {
        Vetores.E[i][j] = 0;
        Vetores.custo[i][j] = 0;
      }
      Vetores.E[i][i] = 0;
      Vetores.custo[i][i] = 0;
    }
  }

  // Função para printar matriz adjacência
  void PrintE() {
    for (int i = 0; i < nV; i++) {
      for (int j = 0; j < nV; j++) {
        cout << Vetores.E[i][j] << " ";
      }
      cout << endl;
    }
  }
  // Função para printar matriz de custo
  void PrintCusto() {
    cout << "|-";
    for (int i = 0; i < nV; i++) {
      cout << Vetores.vertice[i] << "-";
    }
    cout << "|";
    cout << endl;
    for (int i = 0; i < nV; i++) {
      cout << Vetores.vertice[i] << " ";
      for (int j = 0; j < nV; j++) {
        cout << "[" << Vetores.custo[i][j] << "]"
             << " ";
      }
      cout << endl;
    }
  }

  // Função para printar a matriz completa
  void PrintAresta() {
    cout << "|-";
    for (int i = 0; i < nV; i++) {
      cout << Vetores.vertice[i] << " ";
    }
    cout << "-|";
    cout << endl;
    for (int i = 0; i < nV; i++) {
      cout << Vetores.vertice[i] << " ";
      for (int j = 0; j < nV; j++) {
        cout << "[" << Vetores.aresta[i][j] << ", " << Vetores.custo[i][j]
             << "]"
             << " ";
      }
      cout << endl;
    }
  }

  // função para inserir aresta entre duas vertices INT
  void InsertEdge(int v, int w, int p, int custo, string nome) {
    if ((v < 0 || v >= nV) || (w < 0 || w >= nV)) {
      cout << "Erro: número de vértice incorreto!" << endl;
    } else {
      Vetores.E[v][w] = p;
      Vetores.E[w][v] = p;
      Vetores.custo[v][w] = custo;
      Vetores.custo[w][v] = custo;
      Vetores.aresta[w][v] = nome;
      Vetores.aresta[v][w] = nome;
      
    }
  }
  // função para inserir aresta entre duas vertices STRING
  void InsertEdgeName(string nome1, string nome2, int p, int custo, string nome) {
     int v = 0;

    while (Vetores.vertice[v] != nome1 && v < nV) {
      v++;
    }

     int w = 0;

    while (Vetores.vertice[w] != nome2 && w < nV) {
      w++;
    }
    if ((v < 0 || v >= nV) || (w < 0 || w >= nV)) {
      cout << "Erro: número de vértice incorreto!" << endl;
    } else {
      Vetores.E[v][w] = p;
      Vetores.E[w][v] = p;
      Vetores.custo[v][w] = custo;
      Vetores.custo[w][v] = custo;
      Vetores.aresta[w][v] = nome;
      Vetores.aresta[v][w] = nome;
      
    }
  }

  // Função para calcular os graus dos vértices
  int Degree(int v) {
    int k = 0;
    for (int i = 0; i < nV; i++) {
      if (Vetores.E[v][i] > 0) {
        k += Vetores.E[v][i];
      }
    }
    return k;
  }

  // Função para checar se o grafo é euleriano
  bool IsEulerian() {
    for (int i = 0; i < nV; i++) {
      if (Degree(i) % 2 == 1) {
        return false;
      }
    }
    return true;
  }

  // função para inserir vertice por nome
  void inserirVertice(string nome) {
    if (nV < MAX_V) {
      nV++;

      for (int i = 0; i < nV; i++) {
        Vetores.E[i][nV - 1] = 0;
        Vetores.E[nV - 1][i] = 0;
        Vetores.custo[i][nV - 1] = 0;
        Vetores.custo[nV - 1][i] = 0;
        Vetores.vertice[nV - 1] = nome;
        Vetores.aresta[i][nV - 1] = "-";
        Vetores.aresta[nV - 1][i] = "-";
      }
    } else {
      cout << "Erro: o número máximo de vértices foi alcançado!" << endl;
    }
  }

  // função para remover vertice por nome
void removerVertice(string nome) {
  int cont = 0;
  while (cont < nV && Vetores.vertice[cont] != nome) {
    cont++;
  }

  if (cont < nV) {
    for (int i = cont; i < nV - 1; i++) {
      for (int j = 0; j < nV; j++) {
        Vetores.E[i][j] = Vetores.E[i + 1][j];
        Vetores.custo[i][j] = Vetores.custo[i + 1][j];
        Vetores.aresta[i][j] = Vetores.aresta[i + 1][j];
      }
      Vetores.vertice[i] = Vetores.vertice[i + 1];
    }
    for (int j = cont; j < nV - 1; j++) {
      for (int i = 0; i < nV; i++) {
        Vetores.E[i][j] = Vetores.E[i][j + 1];
        Vetores.custo[i][j] = Vetores.custo[i][j + 1];
        Vetores.aresta[i][j] = Vetores.aresta[i][j + 1];
      }
    }

    nV--;

  } else {
    cout << "Erro: Não existe um vértice com esse nome: " << nome << endl;
  }
}

  // função para remover aresta por nome
  void removerAresta(string aresta) {
    string achar = "";
    int contI = 0;
    int contJ = 0;
    for (int i = 0; i < nV; i++) {
      for (int j = 0; j < nV; j++) {
        achar = Vetores.aresta[i][j];
        contI = i;
        contJ = j;
        if (achar == aresta) {
          Vetores.E[contI][contJ] = 0;
          Vetores.E[contJ][contI] = 0;
          Vetores.custo[contI][contJ] = 0;
          Vetores.custo[contJ][contI] = 0;
          Vetores.aresta[contI][contJ] = "";
          Vetores.aresta[contJ][contI] = "";
          cout << "Aresta removida" << endl;
          i = nV;
          j = nV;
        }
      }
    }
    if (achar != aresta) {
      cout << "Erro: Não existe uma aresta com esse nome:" << aresta << endl;
    }
  }

  // função para auxiliar o print da busca profundidade
  void printDFSPath(int parent[], int v, int vertice) {
    if (v == vertice) {
      cout << Vetores.vertice[vertice];
      return;
    }
    printDFSPath(parent, parent[v], vertice);
    cout << " -> " << Vetores.aresta[parent[v]][v] << " -> "
         << Vetores.vertice[v];
  }

  // função para busca de profundidade
  void buscaProfundidade(string nome) {
    const int MAX_V = 100; 
    bool visited[MAX_V] = {false};
    int parent[MAX_V] = {-1}; 
    int vertice = 0;
    while(Vetores.vertice[vertice] != nome && vertice < nV){
       vertice++;
     }
    int stack[MAX_V];
    int top = -1;


    stack[++top] = vertice;
    visited[vertice] = true;

    cout << "Busca em profundidade a partir do vértice "
         << Vetores.vertice[vertice] << ": ";

    while (top >= 0) {
      int current = stack[top--];
      cout << Vetores.vertice[current] << " ";
      for (int i = 0; i < nV; i++) {
        if (Vetores.E[current][i] > 0 && !visited[i]) {
          stack[++top] = i;
          visited[i] = true;
          parent[i] = current; 
        }
      }
    }
    cout << endl;

    cout << "Trajeto encontrado a partir do vértice "
         << Vetores.vertice[vertice] << ": ";
    for (int v = 0; v < nV; v++) {
      if (v == vertice)
        continue; 
      if (visited[v]) {
        printDFSPath(parent, v, vertice);
        cout << " ";
      }
    }
    cout << endl;
  }

  // função que retorna quantidade de componentes conexos
  int goodman() {
    int count = 0;                 
    bool visited[MAX_V] = {false}; 

    for (int k = 0; k < nV; k++) {
      for (int i = 0; i < nV; i++) {
        if (!visited[i] && Vetores.E[k][i] > 0) {
          count++;
          int stack[MAX_V]; 
          int top = 0;

          stack[top] = i;
          while (top >= 0) {
            int v = stack[top];
            top--;

            if (!visited[v]) {
              visited[v] = true;
              for (int j = 0; j < nV; j++) {
                if (Vetores.E[v][j] > 0 && !visited[j]) {
                  top++;
                  stack[top] = j;
                }
              }
            }
          }
        }
      }
    }
    return count;
  }

  // função para auxiliar o algoritmo de fleury, copiando o grafo de graus de vertice
  void copyGraphToFleury() {
    for (int i = 0; i < MAX_V; i++) {
      for (int j = 0; j < MAX_V; j++) {
        Vetores.fleury[i][j] = Vetores.E[i][j];
      }
    }
  }

  // função para auxiliar o algoritmo de fleury, verifica se o grafo se divide
  bool splitGraph(int start, int vertex) {
    int grau = 0;
    for (int i = 0; i < MAX_V; i++) {
      if (Vetores.fleury[start][vertex] == 1) {
        grau++;
        if (grau > 1) {
          return false;
        }
      }
    }
    return true;
  }

  // função para auxiliar o algoritmo de fleury, quantos vertices há
  int numberEdge() {
    int count = 0;
    for (int i = 0; i < MAX_V; i++) {
      for (int j = i; j < MAX_V; j++) {
        if (Vetores.fleury[i][j] == 1 || Vetores.fleury[j][i] == 1) {
          count++;
        }
      }
    }
    return count;
  }

  // ciclo euleriano pelo algoritmo de fleury
  void fleuryEulerian(string nome) {
    int vertice = 0;
    while (Vetores.vertice[vertice] != nome && vertice < nV) {
      vertice++;
    }
    if (IsEulerian() == 0) {
      cout << "Não é Euleriano" << endl;
    } else {

      int nE = numberEdge();
      for (int v = 0; v < MAX_V; v++) {
        if (Vetores.fleury[vertice][v] == 1) {
          if (nE <= 1 || splitGraph(vertice, v) == false) {
            cout << Vetores.vertice[vertice] << "-->" << Vetores.vertice[v]
                 << endl;

            Vetores.fleury[vertice][v] = 0;
            Vetores.fleury[v][vertice] = 0;
            nE--;

            fleuryEulerian(Vetores.vertice[v]);
          }
        }
      }
    }
  }

  // função para realizar a busca em largura
  void buscaLargura(string nome) {
    const int MAX_V = 100;
    bool visited[MAX_V] = {false};
    int parent[MAX_V] = {-1};
    int vertice = 0;
    while(Vetores.vertice[vertice] != nome && vertice < nV){
       vertice++;
     }
    queue<int> fila;
    fila.push(vertice);
    visited[vertice] = true;

    cout << "Busca em largura a partir do vértice " << Vetores.vertice[vertice]
         << ": ";

    while (!fila.empty()) {
      int current = fila.front();
      fila.pop();
      cout << Vetores.vertice[current] << " ";

      for (int i = 0; i < nV; i++) {
        if (Vetores.E[current][i] > 0 && !visited[i]) {
          visited[i] = true;
          fila.push(i);
          parent[i] = current;
        }
      }
    }

    cout << endl;

    cout << "Trajeto encontrado a partir do vértice "
         << Vetores.vertice[vertice] << ": ";
    for (int v = 0; v < nV; v++) {
      if (v == vertice)
        continue;
      if (visited[v]) {
        printBFSPath(parent, v, vertice);
        cout << " ";
      }
    }
    cout << endl;
  }
  // função para auxiliar no print da busca em largura
  void printBFSPath(int parent[], int v, int vertice) {
    if (v == vertice) {
      cout << Vetores.vertice[vertice];
      return;
    }
    printBFSPath(parent, parent[v], vertice);
    cout << " -> " << Vetores.aresta[parent[v]][v] << " -> "
         << Vetores.vertice[v];
  }
  // função para auxiliar o algoritmo de dijkstra
  int findMinDistanceVertex(const int distances[], const bool visited[]) {
    int minDistance = INF;
    int minIndex = -1;
    for (int i = 0; i < nV; ++i) {
      if (!visited[i] && distances[i] < minDistance) {
        minDistance = distances[i];
        minIndex = i;
      }
    }
    return minIndex;
  }
  // função para auxiliar no print do algoritmo de dijkstra
  void printPath(const int parents[], int dest) {
    if (parents[dest] == -1) {
      cout << Vetores.vertice[dest];
    } else {
      printPath(parents, parents[dest]);
      cout << " -> " << Vetores.vertice[dest];
    }
  }

  // Dijkstra
  void dijkstra(string origin, string destiny) {
    string acharOrigem = "";
    string acharDestino = "";
    int contOrigemI = 0;

    int contDestinoI = 0;

    for (int i = 0; i < nV; i++) {
                                   
      acharOrigem = Vetores.vertice[i];
      contOrigemI = i;
     
      if (acharOrigem == origin) {
        i = nV;

      }
    }
    for (int i = 0; i < nV; i++) {       
                                         
      acharDestino = Vetores.vertice[i]; 
      contDestinoI = i;

      if (acharDestino == destiny) {
        i = nV;
      }
    }

    int distances[MAX_V]; 
                          
    bool visited[MAX_V];  
    int parents[MAX_V];   
                          

    for (int i = 0; i < nV; ++i) {
      distances[i] = INF;
      visited[i] = false;
      parents[i] = -1;
    }

    distances[contOrigemI] = 0; 

    for (int i = 0; i < nV - 1; ++i) {
      int u = findMinDistanceVertex(distances, visited);
      if (u == -1)
        break;
      visited[u] = true;

      for (int v = 0; v < nV; ++v) {
        if (!visited[v] && Vetores.custo[u][v] && distances[u] != INF &&
            distances[u] + Vetores.custo[u][v] < distances[v]) {
          distances[v] = distances[u] + Vetores.custo[u][v];
          parents[v] = u;
        }
      }
    }

    if (distances[contDestinoI] == INF) {
      cout << "No path exists from " << Vetores.vertice[contOrigemI] << " to "
           << Vetores.vertice[contDestinoI] << endl;
    } else {
      cout << "Shortest path from " << Vetores.vertice[contOrigemI] << " to "
           << Vetores.vertice[contDestinoI] << ": ";
      printPath(parents, contDestinoI);
      cout << " with distance " << distances[contDestinoI] << endl;
    }
  }
  // função para salvar o grafo em um arquivo
  void printGraphArq(FILE *out) {
    for (int i = 0; i < nV; i++) {
      fprintf(out, "%s ", Vetores.vertice[i].c_str());
    }
    fprintf(out, "\n");
    for (int i = 0; i < nV; i++) {
      fprintf(out, "%s ", Vetores.vertice[i].c_str());
      for (int j = 0; j < nV; j++) {
        fprintf(out, "%s | %d ", Vetores.aresta[i][j].c_str(),
                Vetores.custo[i][j]);
      }
      fprintf(out, "\n");
    }
  }
  // função para carregar grafo salvo como exemplo
  void scanGraphArq(FILE *in) {
    int cont = 0;
    int resultado = 0;
    char vertices[50] = "";
    char auxiliar[50] = "";
    char aresta[50] = "";
    int custo = 0;

    while (fscanf(in, "%49[^ \t\n]", vertices) == 1) {
      
      inserirVertice(vertices);
      cont++;
      char proximoCaractere =
          fgetc(in); 
      if (proximoCaractere == '\n' || proximoCaractere == EOF) {
        break; 
               
      }
    }
    for (int j = 0; j < cont; j++) {
      fscanf(in, "%s", auxiliar);
      
      for (int i = 0; i < cont; i++) {
        fscanf(in, "%s | %d", aresta, &custo);
        if (custo == 0) {
          InsertEdge(j, i, 0, custo, aresta);
        } else {
          InsertEdge(j, i, 1, custo, aresta);
        }
      }
    }
  }
};
  // função para o menu
int displayMainMenu() {
    int choice;
    cout << "---------------------------------------\n";
    cout << "             Graph Operations\n";
    cout << "---------------------------------------\n";
    cout << "  [1] Print Graph\n";
    cout << "  [2] Insert Vertex\n";
    cout << "  [3] Remove Vertex\n";
    cout << "  [4] Insert Edge\n";
    cout << "  [5] Remove Edge\n";
    cout << "  [6] Depth-First Search (DFS)\n";
    cout << "  [7] Breadth-First Search (BFS)\n";
    cout << "  [8] Dijkstra's Algorithm\n";
    cout << "  [9] Fleury's Algorithm\n";
    cout << "  [10] Goodman's Algorithm\n";
    cout << "  [11] Eulerian's Algorithm\n";
    cout << "  [12] Save Graph\n";
    cout << "  [0] Exit\n";
    cout << "---------------------------------------\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int main() {
    Graph G;
    FILE *in;
    FILE *out;
    int choice;
    string origin, destiny;
    int escolha;
    cout << "Gostaria de inicializar um Grafo do inicio? Digite 1: " << endl;
    cout << "Para inicializar com um grafo pré-montando (grafo no arquivo entrada.txt), Digite 2: " << endl;

    cin >> escolha; 
    if(escolha == 1) {
        cout << "Escolha a opção Insert Vertex para começar " << endl;
        
    } else {
        cout << "Carregando o grafo que esta no arquivo entrada.txt" << endl;
        in = fopen("entrada.txt", "r");
        if (!in) {
          printf("Erro 1: não foi possível abrir o arquivo entrada.txt.\n");
          exit(1);
        }
        G.scanGraphArq(in);
        fclose(in);
        cout << "Grafo carregado!" << endl;
        cout << "Tecle [ENTER]" << endl;
        cin.ignore(); 
        cin.get();
    }
    while (true) {
        choice = displayMainMenu();

        switch (choice) {
            case 0:
                cout << "Exiting...\n";
                return 0;
            case 1: {
                cout << "Adjacency Matrix of the Graph:\n";
                G.PrintE();
                G.PrintAresta();
                break;
            }
            case 2: {
                string name;
                cout << "Enter the name of the new vertex: ";
                cin >> name;
                G.inserirVertice(name);
                G.PrintAresta();
                break;
            }
            case 3: {
                string name;
                cout << "Enter the name of the vertex to remove: ";
                cin >> name;
                G.removerVertice(name);
                G.PrintAresta();
                break;
            }
            case 4: {
                int cost;
                string name, v, w;
                cout << "Enter the two vertices (v w): ";
                cin >> v >> w;
                cout << "Enter the cost and name of the edge: ";
                cin >> cost >> name;
                G.InsertEdgeName(v, w, 1, cost, name);
                cout << "Aresta inserida" << endl;
                G.PrintAresta();
                break;
            }
            case 5: {
                string name;
                cout << "Enter the name of the edge to remove: ";
                cin >> name;
                G.removerAresta(name);
                G.PrintAresta();
                break;
            }
            
            case 6: {
                string vertex;
                cout << "Enter the starting vertex for DFS: ";
                cin >> vertex;
                G.buscaProfundidade(vertex);
                G.PrintAresta();
                break;
            }
            case 7: {
                string vertex;
                cout << "Enter the starting vertex for BFS: ";
                cin >> vertex;
                G.buscaLargura(vertex);
                G.PrintAresta();
                break;
            }
            case 8: {
                cout << "Enter the origin and destination vertices: ";
                cin >> origin >> destiny;
                G.dijkstra(origin, destiny);
                cout << endl;
                G.PrintAresta();
                cout << endl;
                cout << "Matriz de Custos: " << endl;
                G.PrintCusto();
                cout << endl;

                break;
            }    
            case 9: {
                string name;
                cout << "Enter the starting vertex for Fleury's Algorithm: ";
                cin >> name;
                G.copyGraphToFleury();
                G.fleuryEulerian(name);
                G.PrintAresta();
                break;
            }
            case 10: {
                int count = G.goodman();
                cout << "Number of connected components: " << count << endl;
                break;
            }
            case 11: {
                bool isEulerian = G.IsEulerian();
                cout << (isEulerian ? "The graph is Eulerian." : "The graph is not Eulerian.") << endl;
                break;
            }
            case 12: {
                out = fopen("output.txt", "w");
                if (!out) {
                    printf("Erro 2: não foi possível abrir o arquivo saida.txt.\n");
                    exit(2);
                }
                G.printGraphArq(out);
                fclose(out);
                cout << "Graph printed to 'output.txt' successfully!\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        cout << "Press [ENTER] to continue...";
        cin.ignore();
        cin.get();
    }
    return 0;
}