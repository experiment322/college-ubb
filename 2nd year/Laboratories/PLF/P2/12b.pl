replaceMaxInSublists_([H|T], M, R) :-
	replaceMaxInSublists_(T, M, R1), is_list(H), maxNumber(H, MH), replace(M, MH, H, RH), R = [RH|R1], !.
replaceMaxInSublists_([H|T], M, R) :-
	replaceMaxInSublists_(T, M, R1), R = [H|R1], !.
replaceMaxInSublists_([], _, []).

replaceMaxInSublists(L, R) :- maxNumber(L, M), replaceMaxInSublists_(L, M, R).

