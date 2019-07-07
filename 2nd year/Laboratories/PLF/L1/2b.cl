(defun is-inside (e l)
  (cond
    ((NULL (car l)) NIL)
    ((eql e (car l)) T)
    (T (or
	 (and (listp (car l)) (is-inside e (car l)))
	 (is-inside e (cdr l))))))
