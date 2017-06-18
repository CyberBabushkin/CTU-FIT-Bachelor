male(john).
female(lisa).
male(karl).
parent(john, lisa).
parent(john,karl).

mother(X,Y) :- parent(X, Y), female(Y)
