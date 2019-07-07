max([], 0).

max([H|T], R):-
	max(T, R1), H > R1,
	R is H, !.

max([_|T], R):-
	max(T, R).
