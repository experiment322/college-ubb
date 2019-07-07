count([], _, 0).

count([H|T], E, R):-
	count(T, E, R1), E == H,
	R is R1 + 1, !.

count([_|T], E, R):-
	count(T, E, R).
