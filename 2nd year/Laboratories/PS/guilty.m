function X = guilty (a, n)
  for i = 1:n
    T = 0; % timpul acumulat
    k = 0; % nr de apeluri
    while T < 1
      T = T + wtime(a, 1);
      k++;
    endwhile
    X(i) = k - 1;
  endfor
endfunction
