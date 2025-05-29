
<img src="https://cdn.jsdelivr.net/npm/simple-icons@v7/icons/amazon.svg" alt="Amazon Icon" width="24" height="24" /> Learn & Be Curious by Amazon


##Problema propusa
O hartă rutieră a unui oraș, definită prin intersecții și străzi între aceste intersecții, poate fi
reprezentată sub forma unui graf orientat în care nodurile reprezintă intersecțiile, iar
muchiile reprezintă străzile (vom considera străzile că fiind unidirecționale). O astfel de
reprezentare a unei hărți rutiere este foarte eficientă pentru a determina diferite proprietăți
ale acesteia (conectivitatea între diferite intersecții, care sunt cele mai frecventate rute, cel
mai scurt drum între două puncte de interes etc.).


## Rulare

Datele de intrare se citesc din fișierul `date.in`. Pentru a rula și salva output în fișierele P1.out, P2.out, P3.out, P4.out și P5.out:


## Exemplu `date.in`

```8 11
Pacurari Nicolina TudorVladimirescu Copou Tatarasi PoduRos Palas Unirii
Nicolina Pacurari
Pacurari Palas
Nicolina Palas
TudorVladimirescu Nicolina
TudorVladimirescu Copou
Tatarasi Palas
Palas Tatarasi
PoduRos Palas
Tatarasi PoduRos
Copou Tatarasi
Tatarasi Copou
3
Pacurari TudorVladimirescu
PoduRos Copou
Nicolina PoduRos
3
Nicolina PoduRos
Palas TudorVladimirescu
Pacurari Copou
10
c Palas Tatarasi 1
q Palas Copou 0
c TudorVladimirescu Copou 3
q Tatarasi TudorVladimirescu 1
q TudorVladimirescu Palas 2 Pacurari
c TudorVladimirescu Palas 0
c PoduRos Palas 2
q TudorVladimirescu PoduRos 1
c PoduRos Tatarasi 2
c TudorVladimirescu Copou 3
16
d Andrei Pacurari
d Bogdan Palas
r PoduRos Copou 4
r PoduRos Tatarasi 4
top_dist 6
d Mihaita Pacurari
r Pacurari PoduRos 3
b Bogdan
top_rating 2
info Mihaita
r Palas TudorVladimirescu 5
r Pacurari Unirii 4
r TudorVladimirescu Palas 2
d Bogdan TudorVladimirescu
r TudorVladimirescu Tatarasi 5
info Bogdan
1 Bogdan
6 PoduRos Tatarasi PoduRos Palas Copou Nicolina 
```

## Output

Se generează cinci fișiere:

- `P1.out`: răspunsuri y/n pentru P1
- `P2.out`: distanțele (sau -1)
- `P3.out`: rezultate interogări și modificări graf
- `P4.out`: informații despre șoferi și topuri
- `P5.out`: intersecții ordonate după combustibil


