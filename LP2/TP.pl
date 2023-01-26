cabeca([A|_],A).
corpo([_|X],X).

quicksort([X|Xs],Ys) :- partition(Xs,X,Left,Right), quicksort(Left,Ls), quicksort(Right,Rs),append(Ls,[X|Rs],Ys).
quicksort([],[]).

partition([X|Xs],Y,[X|Ls],Rs) :- X =< Y, partition(Xs,Y,Ls,Rs).
partition([X|Xs],Y,Ls,[X|Rs]) :- X > Y, partition(Xs,Y,Ls,Rs).
partition([],_,[],[]).

corteUnidimensional(T,Lista,[T]):- quicksort(Lista,Ord),cabeca(Ord,C), T < C, !.
corteUnidimensional(T,Lista,R):- corteAux(T,Lista,[],R), !.
corteUnidimensional(T,Lista,R):- T1 is (T-1),corteUnidimensional(T1,Lista,R1), cabeca(R1,C), C1 is (C+1),corpo(R1,B), R = [C1|B],!.

corteAux(0,_,Atual,[0|Atual]):-!.
corteAux(T,[C|X],Atual,R):- T >= C, T1 is (T-C), corteAux(T1,[C|X],[C|Atual],R).
corteAux(T,[_|X],Atual,R):- corteAux(T,X,Atual,R).