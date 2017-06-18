male(abraham).
male(clancy).
male(herb).
male(homer).
male(bart).

female(mona).
female(jackie).
female(marge).
female(patty).
female(selma).
female(maggie).
female(ling).

parent(bart, homer).
parent(bart, marge).
parent(lisa, homer).
parent(lisa, marge).
parent(maggie, homer).
parent(maggie, marge).
parent(ling, selma).
parent(herb, abraham).
parent(homer, abraham).
parent(homer, mona).
parent(marge, clancy).
parent(marge, jackie).
parent(patty, clancy).
parent(patty, jackie).
parent(selma, clancy).
parent(selma, jackie).

mother(X,Y) :- parent(X, Y), female(Y).
father(X,Y) :- parent(X, Y), male(Y).
brother(X,Y) :- parent(X, Z), parent(Y, Z), male(Y), X \= Y.
sister(X,Y) :- parent(X, Z), parent(Y, Z), female(Y), X \= Y.
sibling(X,Y) :- parent(X, Z), parent(Y, Z), X \= Y.
cousin(X,Y) :- parent(X, Z), sibling(Z, F), parent(Y, F), X \= Y.
grandfather(X,Y) :- parent(X, Z), parent(Z, Y), male(Y).
grandmother(X,Y) :- parent(X, Z), parent(Z, Y), female(Y).
uncle(X,Y) :- parent(X, Z), brother(Z, Y).
aunt(X,Y) :- parent(X, Z), sister(Z, Y).

move(1, X, Y, _) :-
	write('Move top disk from '), 
    write(X), 
    write(' to '), 
    write(Y), 
    nl.
 move(N, X, Y, Z) :-
 	N > 1,
 	M is N - 1,
 	move(M,X,Z,Y), 
    move(1,X,Y,_), 
    move(M,Z,Y,X). 