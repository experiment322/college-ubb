(defun build-set (l)
  (cond
    ((null l) nil)
    (t (cond
	 ((member (car l) (build-set (cdr l))) (build-set (cdr l)))
	 (t (cons (car l) (build-set (cdr l))))))))
