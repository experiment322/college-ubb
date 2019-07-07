(defun count-atoms (l)
  (cond
    ((null l) 0)
    (t (+ (cond
	    ((listp (car l)) (count-atoms (car l)))
	    ((atom (car l)) 1)
	    (t 0))
	  (count-atoms (cdr l))))))

(defun nlcar (nl)
  (cons (car nl) (cadr nl)))

(defun nlcdr (nl)
  (cddr nl))

(defun nlnthcdr (n nl)
  (nthcdr (* 2 n) nl))

(defun nl-to-tree (nl)
  (cond
    ((null nl) nil)
    (t (cond
	 ((= (cdr (nlcar nl)) 1)
	  (list
	    (car (nlcar nl))
	    (nl-to-tree (nlcdr nl))))
	 ((= (cdr (nlcar nl)) 2)
	  (list 
	    (car (nlcar nl))
	    (nl-to-tree (nlcdr nl)) 
	    (nl-to-tree (nlnthcdr (count-atoms ltree) (nlcdr nl)))))
	 (T (list
	      (car (nlcar nl))))))))

(defun lnr-traverse-tree (tree)
  (cond
    ((null (car tree)) nil)
    (t (append
	 (lnr-traverse-tree (cadr tree))
	 (list (car tree))
	 (lnr-traverse-tree (caddr tree))))))

(defun lnr-traverse-nl (nl)
  (lnr-traverse-tree (nl-to-tree nl)))
