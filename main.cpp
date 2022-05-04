#include <iostream>
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<vector>


using namespace std;

struct Lists
{
    vector<vector<int>> next;
    vector<vector<int>> prev;
    vector<vector<int>> lackOfIncidence;
};


//stack<int,vector<int>> stos;


void DFS_msasiedztwa(int **macierzSasiedztwa,int vertex,int sv,bool* visited);
void DFS_mgrafu(int V, int **macierzGrafu, int sv, bool* visited);
Lists createList(int V, int E, vector<vector<int>> next, vector<vector<int>> prev, vector<vector<int>> lackOfIncidence);
Lists createListF(int V, int E, vector<vector<int>> next, vector<vector<int>> prev, vector<vector<int>> lackOfIncidence);
bool findCycle(int **macierzSasiedztwa, int vertex);
bool findCurrentCycle(bool *visited, bool *rec, list<int> *listaSasiedztwa, int currentVertex);
bool findCycleG(int **macierzGrafu, int V);
bool findCurrentCycleG(bool *visited, bool *rec, list<int> *listaSasiedztwa, int currentV);
void DEL_msasiedztwa(int **macierzSasiedztwa, int vertex, int edge);
void DEL_mgrafu(int **macierzGrafu, int V, int E);
int cinV(int V);
int cinInt();

void DFS2_msasiedztwa(int v, int V, int **macierzSasiedztwa, bool *visited, vector<int> stos);
int next_dfs(int v, int V, int **macierzSasiedztwa, bool *visited);


int main()
{
    char c;
    int **macierzSasiedztwa = nullptr;
    int **macierzGrafu = nullptr;
    bool *visited = nullptr;
    bool *visitedg = nullptr;
    int V, E, Vin, Vout;
    fstream file;

    vector<int> stos;


    while(1)
    {
        cout << "Wybierz operacje: \n";
        cout << "1 - macierz sasiedztwa z klawiatury\t2 - macierz sasiedztwa z pliku\n3 - macierz grafu z klawiatury\t\t4 - macierz grafu z pliku\n";
        cout << "5 - DFS macierzy sasiedztwa\t\t6 - DFS macierzy grafu\n7 - DEL macierzy sasiedztwa\t\t8 - DEL macierzy grafu\n";
        cout << "x - zakoncz dzialanie programu\n\n";

        cin.clear();
        cin.sync();
        cin >> c;
        switch(c)
        {
        case '1': /// jest git
            cout<<"Podaj liczbe wierzcholkow i krawedzi:\n";
            //cin >> V >> E;
            V = cinInt();
            E = cinInt();

            macierzSasiedztwa = new int* [V];

            for(int i=0; i<V; i++)
            {
                macierzSasiedztwa[i] = new int[V];
                for(int j=0; j<V; j++)
                {
                    macierzSasiedztwa[i][j] = 0;
                }
            }

            for(int i=0; i<E; i++)
            {
                Vout = cinV(V);
                //cin >> Vout;
                Vin = cinV(V);
                //cin >> Vin;
                macierzSasiedztwa[Vout-1][Vin-1] = 1;
            }
            visited = new bool[V];
            for(int i=0; i<V; i++)
            {
                visited[i] = false;
            }

            cout<<"Macierz sasiedztwa:\n    ";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"|";
            }
            cout<<"\n   ";
            for(int i=0; i<V*2; i++)
            {
                cout<<"_";
            }
            cout<<"\n";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"  |";
                for(int j=0; j<V; j++)
                {
                    cout << macierzSasiedztwa[i][j] <<" ";
                }
                cout<<"\n";
            }
            cout<<"\n\n\n";
            break;

        case '2': /// jest git
            cout << "Dane wczytane z pliku dane.txt\n";
            file.open("dane.txt", ios::in);

            file >> V;
            file >> E;

            macierzSasiedztwa = new int* [V];

            for(int i=0; i<V; i++)
            {
                macierzSasiedztwa[i] = new int[V];
                for(int j=0; j<V; j++)
                {
                    macierzSasiedztwa[i][j] = 0;
                }
            }

            while(1)
            {
                file >> Vout;
                file >> Vin;
                macierzSasiedztwa[Vout-1][Vin-1] = 1;
                if(file.eof())
                {
                    break;
                }
            }
            visited = new bool[V];

            for(int i=0; i<V; i++)
            {
                visited[i] = false;
            }

            file.close();
            cout<<"Macierz sasiedztwa:\n    ";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"|";
            }
            cout<<"\n   ";
            for(int i=0; i<V*2; i++)
            {
                cout<<"_";
            }
            cout<<"\n";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"  |";
                for(int j=0; j<V; j++)
                {
                    cout << macierzSasiedztwa[i][j] <<" ";
                }
                cout<<"\n";
            }
            cout<<"\n\n\n";
            break;

        case '3': /// jest git
        {
            cout << "Podaj liczbe wierzcholkow i krawedzi: " << endl;
            //cin >> V >> E;
            V = cinInt();
            E = cinInt();
            vector<vector<int>> next(V+1);
            vector<vector<int>> prev(V+1);
            vector<vector<int>> lackOfIncidence(V+1, vector<int> (V));
            for(int i=1; i<=V; i++)
            {
                for(int j=0; j<V; j++)
                {
                    lackOfIncidence[i][j] = j+1;
                }
            }

            Lists lista = createList(V, E, next, prev, lackOfIncidence);

            //int **macierzGrafu;///
            macierzGrafu = new int* [V+1];/// XDD

            for(int i=1; i<=V; i++)
            {
                macierzGrafu[i] = new int [V+4];/// :(
                for(int j=0; j<=V+3; j++)
                {
                    macierzGrafu[i][j] = 0;
                }
            }


            for(int i=1; i<=V; i++)
            {
                if(!lista.next[i].empty())
                    macierzGrafu[i][V+1] = lista.next[i].front(); ///6
                if(!lista.prev[i].empty())
                    macierzGrafu[i][V+2] = lista.prev[i].front(); ///7
                if(!lista.lackOfIncidence[i].empty())
                    macierzGrafu[i][V+3] = lista.lackOfIncidence[i].front(); ///8

                for(int j=0; j<lista.next[i].size(); j++)
                {
                    macierzGrafu[i][lista.next[i][j]] = lista.next[i].back();
                }
                for(int j=0; j<lista.prev[i].size(); j++)
                {
                    macierzGrafu[i][lista.prev[i][j]] = lista.prev[i].back()+V;
                }
                for(int j=0; j<lista.lackOfIncidence[i].size(); j++)
                {
                    macierzGrafu[i][lista.lackOfIncidence[i][j]] = -lista.lackOfIncidence[i].back();
                }
            }
            ///wyswietlanie
            cout << "Macierz grafu:\n";
            for(int i=1; i<=V; i++)
            {
                for(int j=1; j<=V+3; j++)
                {
                    cout << macierzGrafu[i][j] << "\t";
                }
                cout << endl;
            }
            break;
        }
        case '4': /// chyba jest git
        {
            cout << "Dane wczytane z pliku:\n";
            file.open("dane.txt", ios::in);
            file >> V >> E;

            vector<vector<int>> next(V+1);
            vector<vector<int>> prev(V+1);
            vector<vector<int>> lackOfIncidence(V+1, vector<int> (V));
            for(int i=1; i<=V; i++)
            {
                for(int j=0; j<V; j++)
                {
                    lackOfIncidence[i][j] = j+1;
                }
            }

            file.close();

            Lists lista = createListF(V, E, next, prev, lackOfIncidence);

            macierzGrafu = new int* [V+1];/// XDD

            for(int i=1; i<=V; i++)
            {
                macierzGrafu[i] = new int [V+4];/// jebane gowno
                for(int j=0; j<=V+3; j++)
                {
                    macierzGrafu[i][j] = 0;
                }
            }

            for(int i=1; i<=V; i++)
            {
                if(!lista.next[i].empty())
                    macierzGrafu[i][V+1] = lista.next[i].front(); ///6
                if(!lista.prev[i].empty())
                    macierzGrafu[i][V+2] = lista.prev[i].front(); ///7
                if(!lista.lackOfIncidence[i].empty())
                    macierzGrafu[i][V+3] = lista.lackOfIncidence[i].front(); ///8

                for(int j=0; j<lista.next[i].size(); j++)
                {
                    macierzGrafu[i][lista.next[i][j]] = lista.next[i].back();
                }
                for(int j=0; j<lista.prev[i].size(); j++)
                {
                    macierzGrafu[i][lista.prev[i][j]] = lista.prev[i].back()+V;
                }
                for(int j=0; j<lista.lackOfIncidence[i].size(); j++)
                {
                    macierzGrafu[i][lista.lackOfIncidence[i][j]] = -lista.lackOfIncidence[i].back();
                }
            }
            ///wyswietlanie
            cout << "Macierz grafu:\n";
            for(int i=1; i<=V; i++)
            {
                for(int j=1; j<=V+3; j++)
                {
                    cout << macierzGrafu[i][j] << "\t";
                }
                cout << endl;
            }
            break;
        }
        case '5': /// gitówa
            for(int i=0; i<V; i++)///
            {
                visited[i] = false;
            }
            if(macierzSasiedztwa == nullptr)
            {
                cout << "przed wykonaniem tego algorytmu musisz stworzyc macierz sasiedztwa\n";
                break;
            }
            if(findCycle(macierzSasiedztwa, V))
            {
                cout << "Graf zawiera cykl\n\n";
            }
            else
            {
                int *inDegrees = new int[V];
                for(int i=0; i<V; i++)
                {
                    inDegrees[i]=0;
                    for(int j=0; j<V; j++)
                    {
                        if(macierzSasiedztwa[j][i]==1)
                            inDegrees[i]++;
                    }
                }
                for(int i=0; i<V; i++)
                {
                    if(inDegrees[i]==0)
                        DFS2_msasiedztwa(i, V, macierzSasiedztwa, visited, stos);
                }
                //DFS_msasiedztwa(macierzSasiedztwa, V, 0, visited);
                //DFS2_msasiedztwa(4, V, macierzSasiedztwa, visited, stos);
                cout << "\n\n\n";
            }
            break;

        case '6': /// chyba gitówson
            if(macierzGrafu == nullptr)
            {
                cout << "Przed wykonaniem tego algorytmu musisz stworzyc macierz grafu\n";
                break;
            }
            visitedg = new bool [V+1];
            for(int i=1; i<=V; i++)
            {
                visitedg[i] = false;
            }
            if(findCycleG(macierzGrafu, V))
            {
                cout << "Graf zawiera cykl\n\n";
            }
            else
            {
                int *inDegrees = new int[V+1];
                for(int i=1; i<=V; i++)
                {
                    inDegrees[i]=0;
                    for(int j=1; j<=V; j++)
                    {
                        if(macierzGrafu[j][i] > 0 && macierzGrafu[j][i] <=V)
                            inDegrees[i]++;
                    }
                }
                for(int i=1; i<=V; i++)
                {
                    if(inDegrees[i]==0)
                        DFS_mgrafu(V, macierzGrafu, i, visitedg);
                }
                //DFS_mgrafu(V, macierzGrafu, 1, visitedg);
                cout << "\n\n\n";
            }
            break;

        case '7':
            DEL_msasiedztwa(macierzSasiedztwa, V, E);
            cout << "\n\n\n";
            break;

        case '8':
            DEL_mgrafu(macierzGrafu, V, E);
            cout << "\n\n\n";
            break;

        case 'x':
            break;

        default:
            cout << "Program nie obsluguje podanej operacji\n";
            break;
        }
        if(c == 'x')
        {
            cout << "Program zakonczony.\n";
            break;
        }
    }



    return 0;
}


void DFS_msasiedztwa(int **macierzSasiedztwa,int vertex,int sv,bool* visited)
{
    cout << sv+1 << "-->";
    visited[sv] = true;
    for(int i=0; i<vertex; i++)
    {
        if(i == sv)
        {
            continue;
        }
        if(macierzSasiedztwa[sv][i] == 1)
        {
            if(visited[i])
            {
                continue;
            }
            DFS_msasiedztwa(macierzSasiedztwa,vertex,i,visited);
        }
    }
}

void DFS_mgrafu(int V, int **macierzGrafu, int sv, bool* visited)/// /////
{
    cout << sv << "-->";
    visited[sv] = true;
    for(int i=1; i<=V; i++)
    {
        if(i == sv)
        {
            continue;
        }
        if(macierzGrafu[sv][i] > 0 && macierzGrafu[sv][i] <= V)
        {
            if(visited[i])
            {
                continue;
            }
            DFS_mgrafu(V, macierzGrafu, i, visited);
        }
    }
}

Lists createList(int V, int E, vector<vector<int>> next, vector<vector<int>> prev, vector<vector<int>> lackOfIncidence)
{
    int a, b;
    for(int i=1; i<=E; i++)
    {
        //cin >> a >> b;
        a = cinV(V);
        b = cinV(V);
        next[a].push_back(b);
        prev[b].push_back(a);

        int j = 0;
        while(lackOfIncidence[a].size() != j)
        {
            if(lackOfIncidence[a][j] == b)
            {
                lackOfIncidence[a][j] = lackOfIncidence[a].back();
                lackOfIncidence[a].pop_back();
                break;
            }
            j++;
        }

        j = 0;
        while(lackOfIncidence[b].size() != j)
        {
            if(lackOfIncidence[b][j] == a)
            {
                lackOfIncidence[b][j] = lackOfIncidence[b].back();
                lackOfIncidence[b].pop_back();
                break;
            }
            j++;
        }
    }

    return {next, prev, lackOfIncidence};
}

bool findCycle(int **macierzSasiedztwa, int vertex)
{
    bool *visited = new bool[vertex];
    bool *rec = new bool[vertex];

    list<int> *listaSasiedztwa;
    listaSasiedztwa = new list<int>[vertex];
    for(int i=0; i<vertex; i++)
    {
        for(int j=0; j<vertex; j++)
        {
            if(macierzSasiedztwa[i][j]==1)
            {
                listaSasiedztwa[i].push_back(j);
            }
        }
    }

    for(int i=0; i<vertex; i++)
    {
        visited[i]=false;
        rec[i]=false;
    }

    for(int i=0; i<vertex; i++)
    {
        if( !visited[i] && findCurrentCycle(visited,rec,listaSasiedztwa,i))
            return true;
    }
    return false;
}

bool findCurrentCycle(bool *visited, bool *rec, list<int> *listaSasiedztwa,int currentVertex)
{
    if(visited[currentVertex] == false)
    {
        visited[currentVertex] = true;
        rec[currentVertex] = true;

        list<int>::iterator i;
        for(i = listaSasiedztwa[currentVertex].begin(); i!=listaSasiedztwa[currentVertex].end(); ++i)
        {
            if( !visited[*i] && findCurrentCycle(visited,rec,listaSasiedztwa,*i))
                return true;
            else if(rec[*i])
                return true;
        }
    }
    rec[currentVertex] = false;
    return false;
}

Lists createListF(int V, int E, vector<vector<int>> next, vector<vector<int>> prev, vector<vector<int>> lackOfIncidence)
{
    fstream file;
    file.open("dane.txt",ios::in);
    int temp;
    file>>temp;
    file>>temp;
    int a, b;
    for(int i=1; i<=E; i++)
    {
        file >> a;
        file >> b;

        if(file.eof())
        {
            break;
        }

        next[a].push_back(b);
        prev[b].push_back(a);

        int j = 0;
        while(lackOfIncidence[a].size() != j)
        {
            if(lackOfIncidence[a][j] == b)
            {
                lackOfIncidence[a][j] = lackOfIncidence[a].back();
                lackOfIncidence[a].pop_back();
                break;
            }
            j++;
        }

        j = 0;
        while(lackOfIncidence[b].size() != j)
        {
            if(lackOfIncidence[b][j] == a)
            {
                lackOfIncidence[b][j] = lackOfIncidence[b].back();
                lackOfIncidence[b].pop_back();
                break;
            }
            j++;
        }
    }
    file.close();

    return {next, prev, lackOfIncidence};
}

bool findCycleG(int **macierzGrafu, int V)
{
    bool *visited = new bool[V+1];
    bool *rec = new bool[V+1];

    list<int> *listaSasiedztwa;
    listaSasiedztwa = new list<int>[V+1];
    for(int i=1; i<=V; i++)
    {
        for(int j=1; j<=V; j++)
        {
            if(macierzGrafu[i][j] > 0 && macierzGrafu[i][j] <= V)
            {
                listaSasiedztwa[i].push_back(j);
            }
        }
    }

    for(int i=1; i<=V; i++)
    {
        visited[i]=false;
        rec[i]=false;
    }

    for(int i=1; i<=V; i++)
    {
        if( !visited[i] && findCurrentCycle(visited, rec, listaSasiedztwa, i))
            return true;
    }
    return false;
}

bool findCurrentCycleG(bool *visited, bool *rec, list<int> *listaSasiedztwa, int currentV)
{
    if(visited[currentV] == false)
    {
        visited[currentV] = true;
        rec[currentV] = true;

        list<int>::iterator i;
        for(i = listaSasiedztwa[currentV].begin(); i != listaSasiedztwa[currentV].end(); ++i)
        {
            if( !visited[*i] && findCurrentCycle(visited, rec, listaSasiedztwa, *i))
                return true;
            else if(rec[*i])
                return true;
        }
    }
    rec[currentV] = false;
    return false;
}

void DEL_msasiedztwa(int **macierzSasiedztwa, int vertex, int edge)
{
    int *outDegrees = new int[vertex];
    int *inDegrees = new int[vertex];
    for(int i=0; i<vertex; i++)
    {
        inDegrees[i]=0;
        outDegrees[i]=0;
        for(int j=0; j<vertex; j++)
        {
            if(macierzSasiedztwa[j][i]==1)
            {
                inDegrees[i]++;
            }
            if(macierzSasiedztwa[i][j]==1)
            {
                outDegrees[i]++;
            }
        }
    }

    queue<int> q;
    for(int i=0; i<vertex; i++)
    {
        if(inDegrees[i]==0)
        {
            q.push(i);
        }
    }

    int counter = 0;
    int top;

    while(!q.empty())
    {
        top = q.front();
        q.pop();
        cout<<top+1<<"-->";
        for(int i=0; i<vertex; i++)
        {
            if(macierzSasiedztwa[top][i]==1)
            {
                if(--inDegrees[i] == 0)
                {
                    q.push(i);

                }
            }
        }
        counter++;
    }

    if(counter != vertex)
    {
        cout<<"istnieje cykl\n";
    }
}

void DEL_mgrafu(int **macierzGrafu, int V, int E)
{
    int *outDegrees = new int[V+1];
    int *inDegrees = new int[V+1];
    for(int i=1; i<=V; i++)
    {
        inDegrees[i]=0;
        outDegrees[i]=0;
        for(int j=1; j<=V; j++)
        {
            if(macierzGrafu[j][i] > 0 && macierzGrafu[j][i] <= V)
            {
                inDegrees[i]++;
            }
            if(macierzGrafu[i][j] > 0 && macierzGrafu[i][j] <= V)
            {
                outDegrees[i]++;
            }
        }
    }

    queue<int> q;
    for(int i=1; i<=V; i++)
    {
        if(inDegrees[i]==0)
        {
            q.push(i);
        }
    }

    int counter = 0;
    int top;

    while(!q.empty())
    {
        top = q.front();
        q.pop();
        cout << top << "-->";
        for(int i=1; i<=V; i++)
        {
            if(macierzGrafu[top][i] > 0 && macierzGrafu[top][i] <= V)
            {
                if(--inDegrees[i] == 0)
                {
                    q.push(i);
                }
            }
        }
        counter++;
    }

    if(counter != V)
    {
        cout<<"istnieje cykl\n";
    }
}

int cinV(int V)
{
    int x;
    while(!(cin >> x) && x <= V)
    {
        cin.clear();
        cin.sync();
        cout << "Podales nie istniejacy wierzcholek. Podaj liczbe mniejsza lub rowna V: \n";
    }
    return x;
}

int cinInt()
{
    int x;
    while(!(cin >> x))
    {
        cin.clear();
        cin.sync();
        cout << "Podaj liczbe: \n";
    }
    return x;
}

void DFS2_msasiedztwa(int v, int V, int **macierzSasiedztwa, bool *visited, vector<int> stos)
{
    int u;
    int next;
    cout << v+1 << "->";
    visited[v] = 1;
    next = next_dfs(v, V, macierzSasiedztwa, visited);
    while(next != -1)
    {
        stos.push_back(next);
        next = next_dfs(v, V, macierzSasiedztwa, visited);
    }
    if(!stos.empty())
    {
        //cout << " -" << stos.back() << "- ";
        u = stos.back();
        stos.pop_back();
        DFS2_msasiedztwa(u, V, macierzSasiedztwa, visited, stos);
    }
}

int next_dfs(int v, int V, int **macierzSasiedztwa, bool *visited)
{
    int i;

    for(i=V-1; i>=0; i--)
    {
        if((macierzSasiedztwa[v][i] == 1) && (visited[i] == 0))
        {
            visited[i] = 1;
            return i;
        }
    }
    return -1;
}
