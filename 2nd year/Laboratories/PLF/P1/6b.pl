remMax([], _, []).

remMax([H|T], M, R):-
	H \= M, remMax(T, M, R1),
	R = [H|R1], !.

remMax([_|T], M, R):-
	remMax(T, M, R).

remMax(L, R):-
	max(L, M),
	remMax(L, M, R).
