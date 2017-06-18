//
//  main.c
//  DU 1
//
//  Created by Andrey Babushkin on 02/11/15.
//  Copyright (c) 2015 Mannannlegur. All rights reserved.
//

#include <stdio.h>

void reseni1(void) {
    
    double hm1, hm2, ko1, ko2, hmV, koV, rozt1, rozt2;
    
    printf("Hmotnost a koncentrace #1:\n");
    if (scanf("%lf %lf", &hm1, &ko1) != 2 || ko1 < 0.0 || ko1 > 1.0 || hm1 < 0) {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Hmotnost a koncentrace #2:\n");
    if (scanf("%lf %lf", &hm2, &ko2) != 2 || ko2 < 0.0 || ko2 > 1.0 || hm2 < 0) {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Hmotnost a koncentrace vysledku:\n");
    if (scanf("%lf %lf", &hmV, &koV) != 2 || koV < 0.0 || koV > 1.0 || hmV < 0) {
        printf("Nespravny vstup.\n");
        return;
    }
    
    if (ko1 == ko2 && koV != ko1) {
        printf("Nelze dosahnout.\n");
        return;
    }
    
    if (ko1 == ko2 && hm2 + hm1 < hmV) {
        if (hm2 + hm1 < hmV) {
            rozt1 = hmV - rozt1 >= 0 ? hmV - rozt1 : hmV ;
            rozt2 = hmV - rozt1;
            printf("%.6lf x #1 + %.6lf x #2\n", rozt1, rozt2);
            return;
        } else {
            printf("Nelze dosahnout.\n");
            return;
        }
    }
    
    double cast2 = (koV-ko1) / (ko2-ko1);
    double cast1 = 1 - cast2;
    
    if (cast1 < 0 || cast2 < 0) {
        printf("Nelze dosahnout.\n");
        return;
    }
    
    rozt1 = cast1 * hmV;
    rozt2 = cast2 * hmV;
    
    if (rozt1 > hm1 || rozt2 > hm2) {
        printf("Nelze dosahnout.\n");
        return;
    }
    
    printf("%.6lf x #1 + %.6lf x #2\n", rozt1, rozt2);
}

int main(int argc, const char * argv[]) {
    reseni1();
    return 0;
}
