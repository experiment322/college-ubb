function I = MC(g, a, b, n)
  X = unifrnd(a, b, 1, n);
  I = mean(g(X) * (b - a));
endfunction
