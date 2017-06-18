//
//  main.c
//  Zahrivaci uloha
//
//  Created by Andrey Babushkin on 18/10/15.
//  Copyright (c) 2015 Mannannlegur. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    printf("ml' nob:\n");
    
    double inputFloat;
    int input = 0;
    char newLine;
    
    if (scanf("%lf%c", &inputFloat, &newLine) == 2 && newLine == '\n') {
        
        input = inputFloat;
        if (inputFloat == input &&
            (inputFloat >= 1.0) && (inputFloat <= 5.0)) {
            
            printf("Qapla'\n");
            switch (input) {
                case 1:
                    printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
                    break;
                case 2:
                    printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
                    break;
                case 3:
                    printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
                    break;
                case 4:
                    printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
                    break;
                case 5:
                    printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
                    break;
                default:
                    printf("luj\n");
                    break;
            }
            
        } else {
            printf("luj\n");
        }
        
    } else {
        printf("luj\n");
    }
    
    #ifndef __PROGTEST__
    system ( "pause" ); /* toto progtest "nevidi" */
    #endif /* __PROGTEST__ */

    return 0;
}
