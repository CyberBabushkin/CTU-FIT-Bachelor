/*/
//  main.c
//  DU2.2
//
//  Created by Andrey Babushkin on 09/11/15.
//  Copyright (c) 2015 Mannannlegur. All rights reserved.
/*/

#include <stdio.h>
#include <math.h>
#include <limits.h>

int areEqual (double d1, double d2)
{
    double diff = d1 - d2;
    double eps = 10e-15;
    
    if (diff < 0) diff *= -1;
    if (diff < eps) return 1; else return 0;
}

long long int gcd (long long int a, long long int b)
{
    while (a && b)
        if (a >= b)
            a %= b;
        else
            b %= a;
    return a | b;
}

long long int * eea (long long a, long long b, long long c)
{
    long long a1,a2,b1,b2,x,y,a11,a22,b11,b22,q,r,gcdAB,ao,bo,aBack,bBack,tmp;
    long long z;
    int rev = 0;
    long long arr[2];
    
    if (a < b) {
        tmp = a;
        a = b;
        b = tmp;
        rev = 1;
    }
    
    gcdAB = gcd(a, b);
    
    aBack = a;
    bBack = b;
    
    a11 = 0;
    a22 = 1;
    b11 = 1;
    b22 = 0;
    
    q = a / b;
    r = a - b*q;
    a2 = a11;
    a1 = a22 - q*a11;
    b2 = b11;
    b1 = b22 - q*b11;
    
    while ( r > 0 ) {
        ao = a;
        bo = b;
        a11 = a1;
        b11 = b1;
        a22 = a2;
        b22 = b2;
        
        a = bo;
        b = r;
        
        q = a / b;
        r = a - b*q;
        a2 = a11;
        a1 = a22 - q*a11;
        b2 = b11;
        b1 = b22 - q*b11;
        
    }
    
    x = a2;
    y = b2;
    
    
    a = aBack;
    b = bBack;
    
    if (x < 0) {
        z = ceil((double) -x / b * c);
        x = x * c + b * z;
        y = y * c - a * z;
    }else
        if (y < 0) {
            z = ceil((double) -y / a * c);
            x = x * c - b * z;
            y = y * c + a * z;
        }
    
    if (!rev) {
        arr[0] = x;
        arr[1] = y;
    } else {
        
        arr[1] = x;
        arr[0] = y;
    }
    
    return arr;
}

void reseni1(void)
{
    double a, b, c;
    long long int l1, l2, l3, gcdN, counter = 0, x, i, y, j, l11, l22;
    char sign;
    long long int * p;
    
    printf("Delky koleji:\n");
    if (scanf("%lf %lf", &a, &b) != 2) {
        printf("Nespravny vstup.\n");
        return;
    }
    if ( !areEqual(floor(a), a) || !areEqual(floor(b), b) ||
         a < 0 || b < 0 ||
         areEqual(0.0, a) || areEqual(0.0, b) ||
         areEqual(a, b) )
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Vzdalenost:\n");
    if (scanf(" %c %lf", &sign, &c) != 2) {
        printf("Nespravny vstup.\n");
        return;
    }
    
    if ( !areEqual(floor(c), c) ||
        c < 0 ||
        (sign != '-' && sign != '+')) {
        
        printf("Nespravny vstup.\n");
        return;
    }
    
    l1 = a;
    l11 = a;
    l2 = b;
    l22 = b;
    l3 = c;
    
    if (l3 == 0) {
        if (sign == '+') {
            printf("= %lld * 0 + %lld * 0\n", l1, l2);
        }
        printf("Celkem variant: 1\n");
        return;
    }
    
    gcdN = gcd(l1, l2);
    
    if (l3 % gcdN != 0) {
        printf("Reseni neexistuje.\n");
        return;
    }
    
    l1 /= gcdN;
    l2 /= gcdN;
    l3 /= gcdN;
    
    p = eea(l1, l2, l3);
    
    x = *(p);
    y = *(p+1);
    
    if (x < 0 || y < 0) {
        printf("Reseni neexistuje.\n");
        return;
    }
    
    if (sign == '-') {
        printf("Celkem variant: %lld\n", l3 / l2 / l1 + 1);
        return;
    }
    
    i = x;
    j = y;
    
    while (i >= 0) {
        printf("= %lld * %lld + %lld * %lld\n", l11, i, l22, j);
        counter++;
        i -= l2;
        j += l1;
    }
    
    i = x + l2;
    j = y - l1;
    
    while (j >= 0) {
        printf("= %lld * %lld + %lld * %lld\n", l11, i, l22, j);
        i += l2;
        j -= l1;
        counter++;
    }
    printf("Celkem variant: %lld\n", counter);
}

int main(int argc, const char * argv[]) {
    reseni1();
    return 0;
}
