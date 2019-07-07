maxNumber([H|T], M) :- maxNumber(T, M1), number(H), H > M1, M = H, !.
maxNumber([_|T], M) :- maxNumber(T, M1), M = M1, !.
maxNumber([], -inf).
