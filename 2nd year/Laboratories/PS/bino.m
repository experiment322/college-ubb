function x = bino(p, n, N)
  x = zeros(1, N);
  for i=1:N
    x(i) = sum(ber(p, n));
  endfor
endfunction
