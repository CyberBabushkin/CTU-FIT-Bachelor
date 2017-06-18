(clear)

(deffunction reverse (?word)
        (bind ?rev "")
        (loop-for-count (?i (length ?word))
                (bind ?rev (str-cat (sub-string ?i ?i ?word) ?rev))
        )
       ?rev
)

(deffunction isPalindrome (?word)
        (bind ?rev (reverse ?word))
        (if (= (str-compare ?rev ?word) 0) 
        then 1
        else 0
        )
)      

(defrule readInput
        (declare (salience 10))
=>
        (printout t "Enter your string: " crlf)
        (bind ?str (read))
        (assert (word ?str))
)

(defrule printReverse
        (declare (salience 9))
        (word ?word)
=>
        (bind ?rev (reverse ?word))
        (printout t "Reversed form of " ?word " is " ?rev crlf)
)

(defrule je-palindrom
        (declare (salience 8))
        (word ?word)
=>
        (if (= 1 (isPalindrome ?word))
        then
                (printout t "Your word " ?word " is a palindrome" crlf)
        else
                (printout t "Your word " ?word " is not a palindrome" crlf)
        )
)

