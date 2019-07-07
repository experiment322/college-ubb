replace(S, E, [H|T], R) :- H == S, replace(S, E, T, R1), R = [E|R1], !.
replace(S, E, [H|T], R) :- replace(S, E, T, R1), R = [H|R1], !.
replace(_, _, [], []).
