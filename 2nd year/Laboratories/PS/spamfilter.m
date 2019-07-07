function spamfilter()
  fileid = fopen('keywords_spam.txt', 'r');
  spam = textscan(fileid, '%s');
  fclose(fileid);
  fileid = fopen('keywords_ham.txt', 'r');
  ham = textscan(fileid, '%s');
  fclose(fileid);
  email = textscan('call your friend today it’s urgent thank you', '%s');
  words = unique([spam{1}; ham{1}]);
  ps = numel(spam{1})/(numel(spam{1}) + numel(ham{1}));
  ph = numel(ham{1})/(numel(spam{1}) + numel(ham{1}));
  for i = 1:numel(email{1})
    if ismember(email{1}{i}, words)
      ps = ps * mean(strcmp(email{1}{i}, spam{1}));
      ph = ph * mean(strcmp(email{1}{i}, ham{1}));
    endif
  endfor
  if ps > ph
    'spam'
  else
    'ham'
  endif
endfunction
