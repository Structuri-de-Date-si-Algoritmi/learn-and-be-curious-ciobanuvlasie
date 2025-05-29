#include <iostream>
#include "mylib.h"
#include <string.h>
using namespace std;

char strazi[50][100];
int adj[50][100] = {0};
int n, m;
char intersectie[100];

int index(char key[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(strazi[i], key) == 0)
            return i;
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
    int dist[100]={-1};

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

void P3(char ch, char start[], char end[], int caz,char intersectie[])
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
            if (P1(start, end)) cout<<"y\n"; // folosim functia P1, afisam y daca avem drum, n, altfel.
            else cout<<"n\n";
        }
        else if (caz==1){
            cout<<P2(start,end)<<'\n'; //afisarea drumului minim de la start la end;
        }
        else if (caz==2){

            //drum minim de la start la end printr-o anumita intersectie.
            int d1=P2(start,intersectie);
            int d2=P2(intersectie,end);
            if (d1!=-1 && d2!=-1) cout<<d1+d2<<'\n';
            else cout<<-1<<'\n';
        }
    }
}

int main()
{
    freopen("date.in", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> strazi[i];
    for (int i = 0; i < m; i++)
    {
        char s1[100];
        char s2[100];
        cin >> s1 >> s2;
        int u = index(s1);
        int v = index(s2);
        adj[u][v] = 1;
    }
    freopen("P1.out", "w", stdout);
    int q;
    cin >> q;
    char start[100], end[100];
    for (int i = 0; i < q; i++)
    {
        cin >> start >> end;
        if (P1(start, end)==1) cout<<"y\n";
        else cout<<"n\n";
    }
    freopen("P2.out", "w", stdout);
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        cin >> start >> end;
        cout<<P2(start,end)<<'\n';
    }
    freopen("P3.out", "w", stdout);
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        char ch, start[100], end[100];
        int caz;
        cin >> ch >> start >> end >> caz;
        if (ch=='q' && caz==2) cin>>intersectie;
        P3(ch, start, end, caz,intersectie);
    }
    //cout<<'\n';
    //cout<<P2("TudorVladimirescu","Pacurari")<<'\n';
    //cout<<P2("Pacurari","Palas");
}
