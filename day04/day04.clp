(deffunction split2 (?str ?sep)
  (bind ?n (str-length ?str))
  (bind ?i (str-index ?sep ?str))
  (create$ (sub-string 1 (- ?i 1) ?str) (sub-string (+ ?i 1) ?n ?str)))

(deffunction main ()
  (close)
  (bind ?tot 0)
  (open "input.txt" myinput)
  (while (neq (bind ?line (readline myinput)) EOF) do
    (bind ?pair (split2 ?line ","))
    (bind ?s1 (split2 (nth$ 1 ?pair) "-"))
    (bind ?b1 (string-to-field (nth$ 1 ?s1)))
    (bind ?e1 (string-to-field (nth$ 2 ?s1)))
    (bind ?s2 (split2 (nth$ 2 ?pair) "-"))
    (bind ?b2 (string-to-field (nth$ 1 ?s2)))
    (bind ?e2 (string-to-field (nth$ 2 ?s2)))
    (if (or (and (>= ?b1 ?b2) (<= ?e1 ?e2)) (and (>= ?b2 ?b1) (<= ?e2 ?e1)))
      then (bind ?tot (+ ?tot 1))))
  (printout t ?tot crlf)
  (close myinput))
