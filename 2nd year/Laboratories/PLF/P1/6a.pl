remPlurals([], _, []).

remPlurals([H|T], L, R):-
	count(L, H, O), O == 1,
	remPlurals(T, L, R1),
	R = [H|R1], !.

remPlurals([_|T], L, R):-
	remPlurals(T, L, R).

remPlurals(L, R):-
	remPlurals(L, L, R).
