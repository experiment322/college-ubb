(defun nary-tree-depth (tree)
  (cond
    ((null tree) 0)
    ((null (cdr tree)) 1)
    (t (+ 1 (apply 'max (mapcar 'nary-tree-depth (cdr tree)))))))
