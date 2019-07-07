(defun find-sublists (l)
  (cond
    ((null l) nil)
    ((listp (car l)) (append
		       (list (car l))
		       (find-sublists (car l))
		       (find-sublists (cdr l))))
    (t (find-sublists (cdr l)))))

(defun find-sublists-inc (l)
  (find-sublists (list l)))
