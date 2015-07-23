;Ford Tang
;46564602
;ICS 141
;Homework 4


;Exercise 1
(defun contains(A L)
	;Check if A is the same as the the first element of L, returns true if they are.
	(cond ((eq A (car L)) T)
		;checks if L is empty.
		((null (car L)) nil)
		;checks if L is a list, and if so return true by recursively calling the first
		;element of L and the cdr of L.
		((listp (car L))(or (contains A (car L)) (contains A (cdr L))))
		;else, recurse the cdr of L.
		(T (contains A (cdr L)))))

;Exercise 2
(defun insert-q(O L)
	;Checks if L is empty, if so, cons O onto L.
	(cond ((null (car L)) (cons O L))
		;else, cons a recursive call to the cdr of L.
		(T (cons (car L) (insert-q O (cdr L))))))

;Exercise 3
(defun subhelp(pat str)
	;Checks pattern to be an atom.  If it is, check the pattern against the first character in the string.
	(cond ((atom pat) (eq pat (car str)))
		;else, if the cdr of the pattern is null (last letter of pattern), then check the letter against the
		;string.
		((null (cdr pat)) (eq (car pat) (car str)))
		;else, recursively call subhelp on each letter of pattern to the string respectively.
		(T (and (subhelp (car pat) str) (subhelp (cdr pat) (cdr str))))))

(defun sub-pattern(pat str)
	;if string is null then return nil.
	(cond ((null (car str)) nil)
		;else, call subhelp function to determine if pattern is in string.  If pattern matches,
		;return string.
		((subhelp pat str) str)
		;else, recurse with the cdr of string.
		(T (sub-pattern pat (cdr str)))))

;Exercise 4
(defun mapping (L val)
	;check if L is empty.
	(cond ((null L) nil)
		;If L is an atom then...
		((atom (car L))
			;If the key of L (known to be a value) is less than the value, then return the object of L.
			(cond ((< (car L) val) (car (cdr L)))))
		;If the key value is greater than the value, then recurse through the cdr of L.
		((null (mapping (car L) val)) (mapping (cdr L) val))
		;else construct a list with the object of L and the recurse of cdr L.
		(T (cons (mapping (car L) val) (mapping (cdr L) val)))))

;Exercise 5
(defun first-atom (L)
	;Check to see if L is an Atom, returns L if it is.
	(cond ((atom L) L)
		;else L must be a list so recursively call the car of L until an atom is found and return it. 
		(T (first-atom (car L)))))

;Exercise 6
(defun rest-list (L)
	;Check if L is an atom.
	(cond ((atom (car L)) (cdr L))
		;If L is not an atom, check to see if L is a one element list.  If so return cdr of L.
		((null (rest-list (car L))) (cdr L))
		;Else recursively call the function to the first car and cons with the cdr.
		(T (cons (rest-list (car L)) (cdr L)))))

;Exercise 7
(defun find-all (A L)
	;checks if list is empty
	(cond ((null L) nil)
		;checks if A is the same as first atom, if so, cons the first atom of the rest of the list to a
		;recursive call to the rest of the list.
		((eq A (first-atom L)) (cons (first-atom (rest-list L)) (find-all A (rest-list L))))
		;Else just check the rest of the list.
		(T (find-all A (rest-list L)))))

;Exercise 8
(defun occ (L A)
	;checks if L is empty
	(cond ((null L) 0)
		;Checks if the first atom is equal to A, if so, add 1 to the result of the recursive call.
		((eq (first-atom L) A) (+ 1 (occ (rest-list L) A)))
		;Else check the rest of the list.
		(T (occ (rest-list L) A))))

;Exercise 9
(defun total-reverse (L)
	;checks if L is empty
	(cond ((null L) nil)
		;Check to see if L is a list.  If so reverse the list, then combine it with the reverse of 
		;cdr of L.
		((listp (car L)) (insert-q (total-reverse(car L)) (total-reverse (cdr L))))
		;Else use insert-q to build a new list from L.
		(T (insert-q (car L) (total-reverse (cdr L))))))
