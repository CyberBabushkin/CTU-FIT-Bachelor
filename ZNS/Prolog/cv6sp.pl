fam(skoda).
fam(vw).
sport(ferrari).
util(tatra).
offroad(jeep).

price(skoda, cheap).
price(vw, cheap).
price(ferrari, exp).
price(tatra, exp).
price(jeep, exp).


speed(skoda, slow).
speed(vw, slow).
speed(ferrari, fast).
speed(tatra, slow).
speed(jeep, fast).

cons(skoda, low).
cons(vw, low).
cons(ferrari, high).
cons(tatra, high).
cons(jeep, high).

capacity(skoda, low).
capacity(vw, low).
capacity(ferrari, low).
capacity(tatra, high).
capacity(jeep, high).

fam( X ) :- price(X, cheap), speed(X, slow), cons(X, low), capacity(X, low).
sport( X ) :- price(X, exp), speed(X, fast), cons(X, high), capacity(X, low).
util( X ) :- price(X, exp), speed(X, slow), cons(X, high), capacity(X, high).
offroad( X ) :- price(X, exp), speed(X, fast), cons(X, high), capacity(X, high).
