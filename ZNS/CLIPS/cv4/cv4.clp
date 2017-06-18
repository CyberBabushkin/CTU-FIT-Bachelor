(clear)

(deffunction factorial (?input)
        (bind ?result ?input)
        (bind ?end (- ?input 1))
        (loop-for-count (?i 1 ?end) do 
                (bind ?result (* ?result ?i))
        )
        (printout t ?result crlf)
)

(factorial 5)

(deffunction factorialRec (?input)
        (if (or (not (integerp ?input)) (> 0 ?input))
        then
                (printout t "Error!" crlf)
        )
        (if (= ?input 0)
        then
                1
        else
                (* ?input (factorialRec (- ?input 1)))
        )
)

