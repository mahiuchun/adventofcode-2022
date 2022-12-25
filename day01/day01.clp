(deffunction main ()
  (open "input.txt" myinput)
  (bind ?most 0)
  (bind ?elf 0)
  (while (neq (bind ?line (readline myinput)) EOF)
    do
    (if (eq ?line "")
      then (progn
             (bind ?most (max ?elf ?most))
             (bind ?elf 0))
      else (bind ?elf (+ ?elf (string-to-field ?line)))))
  (bind ?most (max ?elf ?most))
  (printout t ?most crlf)
  (close))
