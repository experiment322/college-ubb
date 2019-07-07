function R = testA(N)
  S = unifrnd(-1, 1, N, 4);
  n = 0;
  for i = 1:N
    if pdist2(S(i, :), [0 0 0 0]) <= 1
      n = n + 1;
    endif
  endfor
  P = n / N;
  R = P * 16; # 2 is the length of the 4D cube containing the 4D sphere
endfunction
