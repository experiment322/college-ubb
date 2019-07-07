loop(L, R, N) :- L =< R, N = L.
loop(L, R, N) :- L1 is L + 1, L1 =< R, loop(L1, R, N).

isLast([H|T], E) :- T = [], H = E.
isLast([_|T], E) :- isLast(T, E). 

concat([], L, L).
concat([H|T], L, R) :- concat(T, L, R1), R = [H|R1].

colorMap(0, _, []).
colorMap(N, M, R) :- N > 0, N1 is N - 1, colorMap(N1, M, R1), loop(0, M, C), \+isLast(R1, C), concat(R1, [C], R).
