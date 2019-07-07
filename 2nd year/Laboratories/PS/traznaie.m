function X = traznaie(x, p, n)  
  U = rand(1, n);
  P = cumsum(p);
  [~, ind] = histc(U, [0, P]);
  X = x(ind);
endfunction
