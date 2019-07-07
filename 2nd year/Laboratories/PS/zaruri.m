pkg load statistics;
function zaruri(n, N)
  for i = 1:N
    X = unidrnd(6, 1, n);
    S(i) = sum(X);
  endfor
endfunction
