(defun nthelem (l n)
  (cond
    ((< n 0) NIL)
    ((= n 0) (car l))
    (t (nthelem (cdr l) (- n 1)))))
