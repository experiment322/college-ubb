(defun sublist (l s f)
  (cond
    ((null l) nil)
    ((not (= 0 s)) (sublist (cdr l) (- s 1) f))
    ((not (= 1 f)) (append (list (car l)) (sublist (cdr l) s (- f 1))))
    (T (list (car l)))))

(defun len (l)
  (cond
    ((null l) 0)
    (t (+ 1 (len (cdr l))))))

(defun insert (l n e)
  (append
    (sublist l 0 n)
    (list e)
    (sublist l n (len l))))

(defun add (l n e)
  (cond
    ((null l) nil)
    ((< (len l) n) l)
    (T (insert (add l (* 2 n) e) n e))))
