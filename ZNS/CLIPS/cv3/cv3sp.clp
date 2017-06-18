(defrule pizza
=>
        (printout t "Sugo Di Pomodori jako zaklad?" crlf)
        (bind ?ans (read))

        (if (eq ?ans ne)
        then 
                (printout t "Syr?" crlf)
                (bind ?ans (read))

                (if (eq ?ans ne)
                then
                        (printout t "Quattro formagi" crlf)
                else
                        (printout t "Kari?" crlf)
                        (bind ?ans (read))

                        (if (eq ?ans ne)
                        then
                                (printout t "Pro tebe pizzu nemam" crlf)
                        else
                                (printout t "Bombay" crlf)
                        )
                )
        else
                (printout t "Syr?" crlf)
                (bind ?ans (read))

                (if (eq ?ans ne)
                then
                        (printout t "Marinara" crlf)
                else
                        (printout t "Sunka?" crlf)
                        (bind ?ans (read))

                        (if (eq ?ans ne)
                        then
                                (printout t "Margherita" crlf)
                        else
                                (printout t "Zampiony?" crlf)
                                (bind ?ans (read))

                                (if (eq ?ans ne)
                                then
                                        (printout t "Ananas?" crlf)
                                        (bind ?ans (read))

                                        (if (eq ?ans ne)
                                        then
                                                (printout t "Prosciutto" crlf)
                                        else
                                                (printout t "Hawai" crlf)
                                        )
                                else
                                        (printout t "Artycoky?" crlf)
                                        (bind ?ans (read))

                                        (if (eq ?ans ne)
                                        then
                                                (printout t "Funghi" crlf)
                                        else
                                                (printout t "Capricciosa" crlf)
                                        )
                                )
                        )
                )
        )
)