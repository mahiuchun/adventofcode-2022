(deffunction priority (?letter)
  (bind ?ch (string-to-field ?letter))
  (switch ?ch
    (case a then 1)
    (case b then 2)
    (case c then 3)
    (case d then 4)
    (case e then 5)
    (case f then 6)
    (case g then 7)
    (case h then 8)
    (case i then 9)
    (case j then 10)
    (case k then 11)
    (case l then 12)
    (case m then 13)
    (case n then 14)
    (case o then 15)
    (case p then 16)
    (case q then 17)
    (case r then 18)
    (case s then 19)
    (case t then 20)
    (case u then 21)
    (case v then 22)
    (case w then 23)
    (case x then 24)
    (case y then 25)
    (case z then 26)
    (case A then 27)
    (case B then 28)
    (case C then 29)
    (case D then 30)
    (case E then 31)
    (case F then 32)
    (case G then 33)
    (case H then 34)
    (case I then 35)
    (case J then 36)
    (case K then 37)
    (case L then 38)
    (case M then 39)
    (case N then 40)
    (case O then 41)
    (case P then 42)
    (case Q then 43)
    (case R then 44)
    (case S then 45)
    (case T then 46)
    (case U then 47)
    (case V then 48)
    (case W then 49)
    (case X then 50)
    (case Y then 51)
    (case Z then 52)
    (default FALSE)))

(deffunction common (?s1 ?s2)
  (bind ?res (create$))
  (bind ?len (str-length ?s1))
  (loop-for-count (?i 1 ?len)
    (bind ?ch (sub-string ?i ?i ?s1))
    (if (bind ?idx (str-index ?ch ?s2))
      then (bind ?res (insert$ ?res 999 (string-to-field ?ch)))))
  (implode$ ?res))

(deffunction main ()
  (close)
  (open "input.txt" myinput)
  (bind ?tot 0)
  (while TRUE do
    (bind ?r1 (read myinput))
    (if (eq ?r1 EOF)
      then (break))
    (bind ?r2 (read myinput))
    (bind ?r3 (read myinput))
    (bind ?ch (common (common ?r1 ?r2) ?r3))
    (bind ?tot (+ (priority ?ch) ?tot)))
  (printout t ?tot crlf)
  (close myinput))
