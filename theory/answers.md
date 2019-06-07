1. `(A ∨ ¬B)` (alternate: `(A || !B)`)

```
A     B     result
-------------------
0     0       1
0     1       0
1     0       1
1     1       1
```

2. `(¬A ∨ B) ∧ ¬(A ∧ ¬B)` (alternate: `(!A-f || B-t) && !(A-f && !B-t)`)

```
A     B     result
-------------------
0     0       0
0     1       1
1     0       0
1     1       0
```

3. `¬(A ∨ B) ∨ ( (A ∨ C) ∧ ¬(B ∨ ¬C) )` (alternate: `!(A-f || B-f) || ( (A || C) && !(B-f || !C-t) )`)

- (Hint: Is it possible to calculate this using code?)

```
A     B     C     result
-------------------------
0     0     0       0
0     0     1       1
0     1     0       0
0     1     1       1
1     0     0       1
1     0     1       1
1     1     0       0
1     1     1       0
```
