% min(i, o); în M se va afla elementul minim din lista dată la input
min([H|T], M) :- min(T, M1), H < M1, M = H, !.
min([_|T], M) :- min(T, M), !. 
min([], inf).

% elemSwitchList(i, i, i, o); în R se va afla lista dată la input având toate aparițiile elementului E înlocuite cu elementele listei L
elemSwitchList(E, L, [H|T], R) :- elemSwitchList(E, L, T, R1), E = H, append(L, R1, R), !.
elemSwitchList(E, L, [H|T], R) :- elemSwitchList(E, L, T, R1), append([H], R1, R), !.
elemSwitchList(_, _, [], []).

% minSwitchList(i, i, o); în R se va afla lista L având toate aparițiile elementului minim înlocuite cu elementele listei L1
minSwitchList(L, L1, R) :- min(L, M), elemSwitchList(M, L1, L, R).
