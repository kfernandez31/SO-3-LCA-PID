## Testy rocznikowe
https://gitlab.com/mimuw-rocznik-2001/so-2022/testy-zad3

## Testy oficjalne
https://github.com/kfernandez31/SO-3-Process-LCA/tree/main/src/test

## Opis wyników i testów

Podczas testowania w tle było budowane drzewo procesów, generowane przez `./fork_tree 7 2`.

Testy były oceniane binarnie – test albo przechodzi, albo nie.

W komentarzach są wypisane identyfikatory testów, których rozwiązanie nie przeszło, wraz z komunikatem błędu.

### Testy poprawnościowe: (warte w sumie 3 pkt.)
- `tree_one_level` (skrót v1, warty 0,8 pkt.) - zapytania o lca procesów na tym samym poziomie w drzewie

- `tree_random_queries` (skrót v2, warty 0,8 pkt.) - losowe zapytania na drzewie procesów

- `query_servers` (skrót v3, warty 0,5 pkt.) - zapytania o lca serwerów jądra

- `parent_killed` (skrót v4, warty 0,4 pkt.) - zapytanie o lca procesu, którego rodzic skończył się wykonywać

- `check_contants` (skrót c, warty 0,5 pkt.) - prosty test sprawdzający zdefiniowane stałe w pliku callnr.h

### Testy sprawdzające errno: (warte w sumie 2 pkt.)
- `invalid_pid` (skrót e1, warty 0,7 pkt.) - zapytania o nieistniejące procesy oraz ujemne pidy

- `invalid_pid_init` (skrót e2, warty 0,3 pkt.) - zapytania o nieistniejący proces i proces init, czyli korzeń drzewa procesów

- `query_init_tree` (skrót e3, warty 0,5 pkt.) - zapytania, w których jeden z argumentów to proces init, a drugi to proces z drzewa procesów

- `query_init_servers` (skrót e4, warty 0,5 pkt.) - zapytania, w których jeden z argumentów to proces init, a drugi to serwer jądra
