reinou(rhodri, 844, 878).
reinou(anarawd, 878, 916).
reinou(hywel_dda, 916, 950).
reinou(iago_ap_idwal, 950, 979).
reinou(hywal_ap_ieuaf, 979, 985).
reinou(cadwallon, 985, 986).
reinou(maredudd, 986, 999).
principe(X, Y) :- reinou(X, A, B), Y >= A, Y =< B.

populacao(eua, 203).
populacao(india, 548).
populacao(china, 800).
populacao(brasil, 108).
area(eua, 8).
area(india, 3).
area(china, 10).
area(brasil, 8).
densidade(X, Y) :- populacao(X, P), area(X, A), Y is P/A.

pessoa(carlao, 21, masculino).
pessoa(ana, 22, feminino).
pessoa(erasmo, 50, masculino).
pessoa(mariana, 50, feminino).
pessoa(cristiano, 25, masculino).
pessoa(luiz, 5, masculino).
pessoa(maria, 30, feminino).
pessoa(antonio, 55,masculino).
pessoa(roberto, 22, masculino).
pessoa(dalton, 80, masculino).

progenitor(erasmo, carlao).
progenitor(erasmo, cristiano).
progenitor(erasmo, ana).
progenitor(mariana, ana).
progenitor(mariana, carlao).
progenitor(antonio, roberto).
progenitor(cristiano, luiz).
progenitor(dalton, erasmo).
progenitor(dalton, antonio).

irmao(X,Y) :- progenitor(A,X),progenitor(A,Y),pessoa(X,B,masculino), X \= Y.
irma(X,Y) :- progenitor(A,X),progenitor(A,Y),pessoa(X,C,feminino), X \= Y.
pai(X,Y) :- progenitor(X,Y), pessoa(X,A,masculino).
mae(X,Y) :- progenitor(X,Y), pessoa(X,A,feminino).
avo(X,Y) :- progenitor(Pai,Y), progenitor(X,Pai).
tio(X,Y) :- pai(Pai,Y),irmao(X,Pai).
tio(X,Y) :- mae(Pai,Y),irmao(X,Pai).
tia(X,Y) :- pai(Pai,Y),irma(X,Pai).
tia(X,Y) :- mae(Pai,Y),irma(X,Pai).
primo(X,Y) :- tio(Z,X),pai(Z,Y).
primo(X,Y) :- tio(Z,X),mae(Z,Y).
primo(X,Y) :- tia(Z,X),pai(Z,Y).
primo(X,Y) :- tia(Z,X),mae(Z,Y).






