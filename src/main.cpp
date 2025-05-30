#include <iostream>
#include <string.h>
using namespace std;

char strazi[50][100];
int adj[50][100] = {0};
int n, m;
char intersectie[100];

struct Sofer
{
    char nume[100];
    int loc;
    bool online;
    double rating_sum;
    int rides;
    int total_dist;
} soferi[1000];
int nrsoferi = 0;

int findDriver(char key[])
{
    for (int i = 0; i < nrsoferi; i++)
    {
        if (strcmp(soferi[i].nume, key) == 0)
            return i;
    }
    return -1;
}

int index(char key[])
{
    int lo = 0, hi = n - 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        int cmp = strcmp(key, strazi[mid]);
        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return -1; // nu s-a gasit
}

int bfs_dist[1000];
void bfs(int src)
{
    for (int i = 0; i < n; i++)
        bfs_dist[i] = -1;
    int q[1000], head = 0, tail = 0;
    bfs_dist[src] = 0;
    q[tail++] = src;
    while (head < tail)
    {
        int u = q[head++];
        for (int v = 0; v < n; v++)
        {
            if (adj[u][v] && bfs_dist[v] == -1)
            {
                bfs_dist[v] = bfs_dist[u] + 1;
                q[tail++] = v;
            }
        }
    }
}

int bfs_rev_dist[1000];
void bfs_reverse(int dest)
{
    for (int i = 0; i < n; i++)
        bfs_rev_dist[i] = -1;
    int q[1000], head = 0, tail = 0;
    bfs_rev_dist[dest] = 0;
    q[tail++] = dest;
    while (head < tail)
    {
        int v = q[head++];
        for (int u = 0; u < n; u++)
        {
            if (adj[u][v] && bfs_rev_dist[u] == -1)
            {
                bfs_rev_dist[u] = bfs_rev_dist[v] + 1;
                q[tail++] = u;
            }
        }
    }
}

// exista drum de la start la end
int P1(char start[], char end[])
{
    int s = index(start);
    int f = index(end);
    int viz[20] = {0};
    int q[20], st = 0, dr = 0;
    q[dr++] = s;
    viz[s] = 1;
    while (st < dr)
    {
        int nod = q[st++];
        if (nod == f)
        {
            return 1;
        }
        for (int v = 0; v < n; v++)
        {
            if (adj[nod][v] == 1 && !viz[v])
            {
                viz[v] = 1;
                q[dr++] = v;
            }
        }
    }
    return 0;
}
// dist de la start la end
int P2(char start[], char end[])
{
    int viz[20] = {0};
    int q[20], st = 0, dr = 0;
    int dist[100] = {-1};

    int s = index(start);
    int f = index(end);

    viz[s] = 1;
    dist[s] = 0;
    q[dr++] = s;

    while (st < dr)
    {
        int nod = q[st++];
        if (nod == f)
        {
            return dist[f];
        }
        for (int v = 0; v < n; v++)
        {
            if (adj[nod][v] == 1 && !viz[v])
            {
                viz[v] = 1;
                q[dr++] = v;
                dist[v] = dist[nod] + 1;
            }
        }
    }
    return -1;
}

void P3(char ch, char start[], char end[], int caz, char intersectie[])
{
    int u = index(start);
    int v = index(end);
    if (ch == 'c')
    {
        if (caz == 0) // stergere drum de la start la end
        {
            adj[u][v] = 1;
        }

        else if (caz == 1) // blocare drum indiferent de sens
        {
            adj[u][v] = adj[v][u] = 0;
        }
        else if (caz == 2) // adaugare drum bidirectional
        {
            adj[u][v] = adj[v][u] = 1;
        }
        else if (caz == 3) // inversare drum
        {
            if (adj[u][v] == 1 && adj[v][u] == 0)
            {
                adj[u][v] = 0;
                adj[v][u] = 1;
            }
        }
    }
    else if (ch == 'q')
    {

        if (caz == 0)
        {
            if (P1(start, end))
                cout << "y\n"; // folosim functia P1, afisam y daca avem drum, n, altfel.
            else
                cout << "n\n";
        }
        else if (caz == 1)
        {
            cout << P2(start, end) << '\n'; // afisarea drumului minim de la start la end;
        }
        else if (caz == 2)
        {

            // drum minim de la start la end printr-o anumita intersectie.
            int d1 = P2(start, intersectie);
            int d2 = P2(intersectie, end);
            if (d1 != -1 && d2 != -1)
                cout << d1 + d2 << '\n';
            else
                cout << -1 << '\n';
        }
    }
}

void P4()
{
    int q;
    cin >> q;
    char c[10];
    for (int i = 0; i < q; i++)
    {
        cin >> c;
        if (strcmp(c, "d") == 0) // online
        {
            char nume[100], locatie[100];
            cin >> nume >> locatie;
            int poz = findDriver(nume);
            if (poz == -1) // sofer nou
            {
                strcpy(soferi[i].nume, nume);
                soferi[nrsoferi].loc = index(locatie);
                soferi[nrsoferi].online = 1;
                soferi[nrsoferi].rating_sum = 0;
                soferi[nrsoferi].rides = 0;
                soferi[nrsoferi].total_dist = 0;
                nrsoferi++;
            }
            else
            {
                strcpy(soferi[poz].nume, nume);
                soferi[poz].online = 1;
            }
        }
        if (strcmp(c, "b") == 0)
        {
            char nume[100];
            cin >> nume;
            int poz = findDriver(nume);
            if (poz != -1)
                soferi[poz].online = 0;
        }
        else if (strcmp(c, "r") == 0)
        {
            char start[100], end[100], rating[100];
            cin >> start >> end >> rating;
            int s = index(start);
            int f = index(end);
            // alegerea soferului pornind din start;
            // trebuie sa intoarcea muchiile, si cautam soferii care pot veni la start
            bfs(s);
            int destinatie = f;
            if (bfs_dist[f] == -1) // cautam o intersectie vecina, incheiem cursa in k , in loc de destinatia noastra
            {
                bool gasit = 0;
                for (int k = 0; k < n && !gasit; k++)
                    if (adj[f][k] == 1 && bfs_dist[k] != -1)
                        destinatie = k, gasit = 1;

                if (gasit == 0)
                    cout << "Destinatie inaccesibila\n";
            }
            bfs_reverse(s); // distanta de la toate nodurile catre start(client)
            int soferi_disp[1000], nrsd = 0;
            for (int i = 0; i < nrsoferi; i++)
            {
                if (soferi[i].online && bfs_rev_dist[soferi[i].loc] != -1)
                    soferi_disp[nrsd++] = i;
            }
            if (nrsd == 0)
            {
                cout << "Soferi indisponibili\n";
            }
            int best = soferi_disp[0];
            for (int i = 1; i < nrsd; i++)
            {
                int current = soferi_disp[1];
                int dist_best = bfs_rev_dist[soferi[best].loc];
                int dist_current = bfs_rev_dist[soferi[current].loc];
                if (dist_best < dist_current)
                    dist_best = dist_current;
                else if (dist_current == dist_best)
                {
                    //
                }
                
            }
        }
    }
}

void sortare(char strazi[][100])
{
    for (int i = 0; i < n - 1; i++)
    {
        int best = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(strazi[j], strazi[best]) < 0)
                best = j;
        }
        if (best != i)
        {
            char tmp[100];
            strcpy(tmp, strazi[i]);
            strcpy(strazi[i], strazi[best]);
            strcpy(strazi[best], tmp);
        }
    }
}

int main()
{
    
    freopen("date.in", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> strazi[i];

    sortare(strazi);
    for (int i = 0; i < m; i++)
    {
        char s1[100];
        char s2[100];
        cin >> s1 >> s2;
        int u = index(s1); // cautare binara
        int v = index(s2);
        adj[u][v] = 1;
    }
    freopen("P1.out", "w", stdout);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        char ch, start[100], end[100];
        cin >> start >> end;
        if (P1(start, end) == 1)
            cout << "y\n";
        else
            cout << "n\n";
    }
    freopen("P2.out", "w", stdout);
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        char ch, start[100], end[100];
        cin >> start >> end;
        cout << P2(start, end) << '\n';
    }
    freopen("P3.out", "w", stdout);
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        char ch, start[100], end[100];
        int caz;
        cin >> ch >> start >> end >> caz;
        if (ch == 'q' && caz == 2)
            cin >> intersectie;
        P3(ch, start, end, caz, intersectie);
    }

}
