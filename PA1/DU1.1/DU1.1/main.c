

#include <stdio.h>
#include <math.h>

/**
* Checks if two doubles are equal.
* @param d1 and d2 - two doubles.
* @return Returns 1 if d1 == d2. Otherwise, returns 0.
*
**/
int areEqual (double d1, double d2) {
    double diff = d1 - d2;
    double eps = 10e-15;
    if (diff < 0) diff *= -1;
    if (diff < eps) return 1; else return 0;
}

double * reseni1 (double hm1, double ko1, double hm2, double ko2, double hmV, double koV) {
    static double arr[2];
    double cast1, cast2;
    
    arr[0] = -1.0;
    arr[1] = -1.0;
    
    if (areEqual(0.0, hmV)) {
        arr[0] = 0.0;
        arr[1] = 0.0;
        return arr;
    }

    if (areEqual(ko1, ko2) && !areEqual(koV, ko1)) {
        return arr;
    }

    if (areEqual(ko1, ko2)) {
        if (hm2 + hm1 >= hmV) {
            arr[0] = hmV - hm1 >= 0.0 ? hm1 : hmV;
            arr[1] = hmV - arr[0] >= 0.0 ? hmV - arr[0] : 0.0;
            return arr;
        } else {
            return arr;
        }
    }

    cast2 = (koV-ko1) / (ko2-ko1);
    cast1 = 1 - cast2;

    if (cast1 < 0.0 || cast2 < 0.0) {
        return arr;
    }

    arr[0] = cast1 * hmV;
    arr[1] = cast2 * hmV;

    if ((arr[0] > hm1 && !areEqual(arr[0], hm1))
            || (arr[1] > hm2 && !areEqual(arr[1], hm2))) {
        return arr;
    }

    return arr;
}

void reseni2(void) {
    double hm1, hm2, hm3, ko1, ko2, ko3, hmV, koV, rozt1, rozt2, rozt3, tempMass;
    double *p;
    unsigned long long i;
    
    printf("Hmotnost a koncentrace #1:\n");
    if (scanf("%lf %lf", &hm1, &ko1) != 2 || ko1 < 0.0 || ko1 > 1.0 || hm1 < 0.0) {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Hmotnost a koncentrace #2:\n");
    if (scanf("%lf %lf", &hm2, &ko2) != 2 || ko2 < 0.0 || ko2 > 1.0 || hm2 < 0.0) {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Hmotnost a koncentrace #3:\n");
    if (scanf("%lf %lf", &hm3, &ko3) != 2 || ko3 < 0.0 || ko3 > 1.0 || hm3 < 0.0) {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Hmotnost a koncentrace vysledku:\n");
    if (scanf("%lf %lf", &hmV, &koV) != 2 || koV < 0.0 || koV > 1.0 || hmV < 0.0) {
        printf("Nespravny vstup.\n");
        return;
    }
    
    {
    if (areEqual(0.0, hmV)) {
        rozt1 = 0.0;
        rozt2 = 0.0;
        rozt3 = 0.0;
        printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
        return;
    }
    
    if (areEqual(0.0, hm1)) {
        p = reseni1(hm2,ko2,hm3,ko3,hmV,koV);
        rozt1 = 0.0;
        if (*(p) < 0 || *(p+1) < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        rozt2 = *(p);
        rozt3 = *(p+1);
        printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
        return;
    } else
    
    if (areEqual(0.0, hm2)) {
        p = reseni1(hm1,ko1,hm3,ko3,hmV,koV);
        rozt2 = 0.0;
        if (*(p) < 0 || *(p+1) < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        rozt1 = *(p);
        rozt3 = *(p+1);
        printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
        return;
    } else
    
    if (areEqual(0.0, hm3)) {
        p = reseni1(hm1,ko1,hm2,ko2,hmV,koV);
        rozt3 = 0.0;
        if (*(p) < 0 || *(p+1) < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        rozt1 = *(p);
        rozt2 = *(p+1);
        printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
        return;
    }
    } /* checks 0's */
    
    if (areEqual(ko1, ko2) && areEqual(ko2, ko3) && !areEqual(koV, ko1)) {
        printf("Nelze dosahnout.\n");
        return;
    }
    
    if (areEqual(ko1, ko2) && areEqual(ko2, ko3)) {
        if (hm2 + hm1 + hm3 >= hmV) {
            rozt1 = hmV - hm1 >= 0.0 ? hm1 : hmV;
            rozt2 = hmV - rozt1 - hm2 >= 0.0 ? hm2 : hm2 - rozt1;
            rozt3 = hmV - rozt1 - rozt2 >= 0.0 ? hmV - rozt1 - rozt2 : 0.0;
            printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
            return;
        } else {
            printf("Nelze dosahnout.\n");
            return;
        }
    }
    
    /*
     
     m3 = m - m1 - m2
     
          (p-p3)m - (p1-p3)m1
     m2 = --------------------
                p2 - p3
     
     1) Check if p2==p3 !!! V
     
     */
    
    /* We had to do that. We did it.*/
    if (areEqual(ko2, ko3)) {
        p = reseni1(hm1, ko1, hm2 + hm3, ko2, hmV, koV);
        if (*(p) < 0 || *(p+1) < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        rozt1 = *(p);
        tempMass = *(p+1);
        rozt2 = tempMass - hm2 >= 0.0 ? hm2 : tempMass - hm2;
        rozt3 = tempMass - rozt2 >= 0.0 ? hm3 : 0.0;
        printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
        return;
    }
    
    
    
    for (i = 0; i < hm1 * 10e7; i++) {
        rozt1 = i / 10e7;
        rozt2 = ((koV - ko3) * hmV - (ko1 - ko3)) / (ko2 - ko3);
        rozt3 = hmV - rozt1 - rozt2;
        if (rozt1 < 0 || rozt2 < 0 || rozt3 < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        if ((rozt3 < hm3 || areEqual(rozt3, hm3))
            && (rozt1 < hm1 || areEqual(rozt1, hm1))
            && (rozt2 < hm2 || areEqual(rozt2, hm2))) {
            printf("%.6f x #1 + %.6f x #2 + %.6f x #3\n", rozt1, rozt2, rozt3);
            return;
        }
    }
    
    /*{
        
        cast2 = (koV-ko1) / (ko2-ko1);
        cast1 = 1 - cast2;
        
        if (cast1 < 0 || cast2 < 0) {
            printf("Nelze dosahnout.\n");
            return;
        }
        
        rozt1 = cast1 * hmV;
        rozt2 = cast2 * hmV;
        
        if ((rozt1 > hm1 && !areEqual(rozt1, hm1))
            || (rozt2 > hm2 && !areEqual(rozt2, hm2))) {
            printf("Nelze dosahnout.\n");
            return;
        }
        
        printf("%.6f x #1 + %.6f x #2\n", rozt1, rozt2);

    } * old code for 2 */
    
    
    
}

int main(int argc, const char * argv[]) {
    //reseni2();
    
    int a = 0, b = 19;
    
    if (a = !b) {
        printf("%d", 16+a);
    }
    
    return 0;
}
