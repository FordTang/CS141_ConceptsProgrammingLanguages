%Ford Tang
%46564602
%CS 141
%Homework 5

compute-change(Money, Q, D, N, P) :- Money >= 25,
	NewMoney is Money - 25,
	compute-change(NewMoney, NewQ, D, N, P),
	Q is NewQ + 1.
compute-change(Money, Q, D, N, P) :- Money >= 10,
	NewMoney is Money - 10,
	compute-change(NewMoney, Q, NewD, N, P),
	D is NewD + 1.
compute-change(Money, Q, D, N, P) :- Money >= 5,
	NewMoney is Money - 5,
	compute-change(NewMoney, Q, D, NewN, P),
	N is NewN + 1.
compute-change(Money, Q, D, N, P) :- Money >= 1,
	NewMoney is Money - 1,
	compute-change(NewMoney, Q, D, N, NewP),
	P is NewP + 1.
compute-change(X, X, X, X, X).


palindrome(B, R) :- append(B, NewR, R), reverse(B, NewR).
