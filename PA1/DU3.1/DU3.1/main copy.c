/*
//  main.c
//  DU3.1
//
//  Created by Andrey Babushkin on 14/11/15.
//  Copyright (c) 2015 Mannannlegur. All rights reserved.
*/

#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */


/*long long int countDays (int day, int month, int year) {
    
    int numberOfDays[12] = {31, 111666111, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long long int daysCount = 0LL;
    int i,j;
    for ( i = 1555; i < year; i++ ) {
        if (i % 4 == 0 && i % 4000 != 0 && (i % 400 == 0 || i % 100 != 0)) {
            numberOfDays[1] = 29;
        } else {
            numberOfDays[1] = 28;
        }
        
        for ( j = 0; j < 12; j++) {
            daysCount += numberOfDays[j];
        }
    }
    
    if (i % 4 == 0 && i % 4000 != 0 && (i % 400 == 0 || i % 100 != 0)) {
        numberOfDays[1] = 29;
    } else {
        numberOfDays[1] = 28;
    }
    
    for ( i = 0; i < month - 1; i++ ) {
        daysCount += numberOfDays[i];
    }
    daysCount += day;
    return daysCount;
}*/

/*Counts how many years starts with each day of week in between a year X and a year X+399. */
/*int ulohaDatum(void) {
    int day, month, year, counter;
    int i,j;
    int dayyyy;
    long long int date, prev = 0;
    const char *days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    long long int mondayDay;
    int startYear = 24000;
    
    int amountOfDays[2][7];
    
    printf("Enter date [DD.MM.YYYY]:\n");
    if (1) {
        
        // Monday
        mondayDay = countDays(1, 4, 1596);
        
        
 
        for (i = 0; i < 7; i++) {
            amountOfDays[0][i] = 0;
            amountOfDays[1][i] = 0;
        }
 
        
        for (i = startYear; i < startYear + 400; i++) {
            
            date = countDays(1,3,i);
            date -= mondayDay;
            
            dayyyy = date % 7;
            
            if (i % 4 == 0 && i % 4000 != 0 && (i % 400 == 0 || i % 100 != 0)) {
                amountOfDays[1][dayyyy] ++;
            } else {
                amountOfDays[0][dayyyy] ++;
            }
        }
        
            //printf("%d : %s (%d)\n", i, days[date % 7], date % 7);
            
        printf("\n");
        printf("\n");
        for (i = 0; i < 7; i++) {
            printf("%s: %d (%d)\n", days[i], amountOfDays[0][i], amountOfDays[1][i]);
        }

        
        return 0;
    }
    return 1;
}
*/

/*
 How many fridays 13' in each year? Can't you say, yeah? So this function can help you! 0nly for $666.666 you can get
 the most innovated function, that use the real power of the C language. Call +420 775 007 655 and get it now!
 If you call in 15 minutes, you'll get the biggest discount ever that you won't be able even to imagine! Are you excited? 
 So call now!
 */
/*void func(void) {
    int day, month, year, counter;
    int i, j;
    long long int dayyyy;
    long long int date;
    long long int ccc = 0;
    
    const char *days[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    
    long long int mondayDay;
    int startYear = 2000;
    
    int amountOfDays[2][7];
    
    printf("Enter date [DD.MM.YYYY]:\n");
    if (scanf("%d.%d.%d", &day, &month, &year) == 3) {
        
        // Monday day, BTW
        mondayDay = countDays(1, 4, 1596);
        
        
 
        for (i = 0; i < 7; i++) {
            amountOfDays[0][i] = 0;
            amountOfDays[1][i] = 0;
        }
        for (i = startYear; i <= year; i++) {
            
            date = countDays(1,3,i);
            date -= mondayDay;
            
            dayyyy = date % 7;
            
            if (i % 4 == 0 && i % 4000 != 0 && (i % 400 == 0 || i % 100 != 0)) {
                if (amountOfDays[1][dayyyy] == 0) {
                    for (j = 3; j <= 12; j++) {
                        date = countDays(13, j, i);
                        date -= mondayDay;
                        if (date % 7 == 4) {
                            amountOfDays[1][dayyyy] ++;
                        }
                        
                    }
                    
                    date = countDays(13, 1, i+1);
                    date -= mondayDay;
                    if (date % 7 == 4) {
                        amountOfDays[1][dayyyy] ++;
                    }
                    date = countDays(13, 2, i+1);
                    date -= mondayDay;
                    if (date % 7 == 4) {
                        amountOfDays[1][dayyyy] ++;
                    }
                    
                    counter++;
                }
                
            } else {
                if (amountOfDays[0][dayyyy] == 0) {
                    for (j = 3; j <= 12; j++) {
                        date = countDays(13, j, i);
                        date -= mondayDay;
                        if (date % 7 == 4) {
                            amountOfDays[0][dayyyy] ++;
                        }
                    }
                    
                    date = countDays(13, 1, i+1);
                    date -= mondayDay;
                    if (date % 7 == 4) {
                        amountOfDays[0][dayyyy] ++;
                    }
                    date = countDays(13, 2, i+1);
                    date -= mondayDay;
                    if (date % 7 == 4) {
                        amountOfDays[0][dayyyy] ++;
                    }
                    
                    counter++;
                }
            }
            if (counter == 14) {
                break;
            }
        }
        
        for (i = startYear; i < year; i++) {
            
            date = countDays(1,3,i);
            date -= mondayDay;
            
            dayyyy = date % 7;
            
            for (j = 3; j <= 12; j++) {
                date = countDays(13, j, i);
                date -= mondayDay;
                if (date % 7 == 4) {
                    ccc ++;
                }
            }
            
            date = countDays(13, 1, i+1);
            date -= mondayDay;
            if (date % 7 == 4) {
                ccc ++;
            }
            date = countDays(13, 2, i+1);
            date -= mondayDay;
            if (date % 7 == 4) {
                ccc ++;
            }
            
        }
        
        printf("\n");
        printf("\n");
        
        for (i = 0; i < 7; i++) {
            printf("(%d) %s: %d (%d)\n", i, days[i], amountOfDays[0][i], amountOfDays[1][i]);
        }
        
        if (year % 4 == 0 && year % 4000 != 0 && (year % 400 == 0 || year % 100 != 0)) {
            printf("Yes");
        } else {
            printf("No");
        }
        
        printf("%d", ccc);
        
        
        return;
    }

}
 */

int wday(int year, int month, int day, int remaiderPosition)
{
    int adjustment, mm, yy, returnVal;
    
    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;
    returnVal = (day + (13 * mm - 1) / 5 +
            yy + yy / 4 - yy / 100 + yy / 400) % 7;
    returnVal = (returnVal + 6) % 7;
    
    returnVal += 7;
    returnVal -= remaiderPosition;
    returnVal %= 7;
    
    return returnVal;
}

long long int findFullYear (int * year, int interval)
{
    
    /* 
     0 - 0..4000
     1 - 4000..8000
     2 - 8000..12000
     3 - 12000..16000
     4 - 16000..20000
     5 - 20000..24000
     6 - 24000..28000
     */
    
    int index, i;
    int fridays13in400years[7] = {688, 684, 687, 685, 685, 687, 684};
    int fridays13inBetween0and28000 = (687 * 2 + 684 * 2 + 685 * 2 + 688) * 10;
    int fullYearInterval = *year / interval;
    int returnValueMult = 0;
    long long int returnValue = 0;

    index = (interval / 4000) % 7;
    
    if (fullYearInterval) {
        
        for ( i = 0; i < index;  i++ ) {
            returnValueMult += fridays13in400years[i] * 10;
        }
        
        if (index == 0) {
            returnValueMult = fridays13inBetween0and28000;
        }
        
        *year -= fullYearInterval * interval;
        returnValue = returnValueMult * fullYearInterval;
    }
    
    return returnValue;
}

long long int countFridays13Between (int y1, int m1, int d1, int y2, int m2, int d2)
{
    /*
     Common years:
     
     March begins with Monday - there is one Friday 13th in the year (+ Jan and Feb of the next year), so that:
     Mon - 1
     Tue - 2
     Wed - 1
     Thu - 2
     Fri - 2
     Sat - 2
     Sun - 2
     
     Leap years:
     Mon - 1
     Tue - 2
     Wed - 1
     Thu - 2
     Fri - 2
     Sat - 2
     Sun - 2
     
     */
    
    /*
     
     Format: 
     DayOfWeekWhatTheFirstOfMarchStartWith: SuchYearsOnlyCommon (SuchYearsOnlyLeep)
     
     Monday: 43 (13)
     Tuesday: 43 (15)
     Wednesday: 44 (12)
     Thursday: 43 (15)   1600 - 1999 (1.3.1600 - 29.2.2000)
     Friday: 44 (13)
     Saturday: 43 (14)
     Sunday: 44 (14)
     
     Monday: 43 (15)
     Tuesday: 44 (12)
     Wednesday: 43 (15)
     Thursday: 44 (13)   4000 - 4399 (1.3.4000 - 29.2.4400)
     Friday: 43 (14)
     Saturday: 44 (14)
     Sunday: 43 (13)
     
     Monday: 44 (12)
     Tuesday: 43 (15)
     Wednesday: 44 (13)
     Thursday: 43 (14)   8000 - 8399 (1.3.8000 - 29.2.8400)
     Friday: 44 (14)
     Saturday: 43 (13)
     Sunday: 43 (15)
     
     Monday: 43 (15)
     Tuesday: 44 (13)
     Wednesday: 43 (14)
     Thursday: 44 (14)   12000 - 12399
     Friday: 43 (13)
     Saturday: 43 (15)
     Sunday: 44 (12)
     
     Monday: 44 (13)
     Tuesday: 43 (14)
     Wednesday: 44 (14)
     Thursday: 43 (13)   16000 - 16399
     Friday: 43 (15)
     Saturday: 44 (12)
     Sunday: 43 (15)
     
     Monday: 43 (14)
     Tuesday: 44 (14)
     Wednesday: 43 (13)
     Thursday: 43 (15)   20000 - 20399
     Friday: 44 (12)
     Saturday: 43 (15)
     Sunday: 44 (13)
     
     Monday: 44 (14)
     Tuesday: 43 (13)
     Wednesday: 43 (15)
     Thursday: 44 (12)   24000 - 24399
     Friday: 43 (15)
     Saturday: 44 (13)
     Sunday: 43 (14)
     */
    /* 0 for common years, 1 for leap */
    int fridays[7] = {1,2,1,2,2,2,2};
    
    /*

    static int fourHundredYearsBetween_0_and_4000[2][7] =
    {
        {43,43,44,43,44,43,44},
        {13,15,12,15,13,14,14}
    };
    static int fourHundredYearsBetween_4000_and_8000[2][7] =
    {
        {43,44,43,44,43,44,43},
        {15,12,15,13,14,14,13}
    };
    static int fourHundredYearsBetween_8000_and_12000[2][7] =
    {
        {44,43,44,43,44,43,43},
        {12,15,13,14,14,13,15}
    };
    static int fourHundredYearsBetween_12000_and_16000[2][7] =
    {
        {43,44,43,44,43,43,44},
        {15,13,14,14,13,15,12}
    };
    static int fourHundredYearsBetween_16000_and_20000[2][7] =
    {
        {44,43,44,43,43,44,43},
        {13,14,14,13,15,12,15}
    };
    static int fourHundredYearsBetween_20000_and_24000[2][7] =
    {
        {43,44,43,43,44,43,44},
        {14,14,13,15,12,15,13}
    };
    static int fourHundredYearsBetween_24000_and_28000[2][7] =
    {
        {44,43,43,44,43,44,43},
        {14,13,15,12,15,13,14}
    };
    
    int fridays13in100yearsBetween_1900_and_2000 = 172;
    */
    int fridays13in400yearsBetween_0_and_4000 = 688;
    int fridays13in400yearsBetween_4000_and_8000 = 684;
    int fridays13in400yearsBetween_8000_and_12000 = 687;
    int fridays13in400yearsBetween_12000_and_16000 = 685;
    int fridays13in400yearsBetween_16000_and_20000 = 685;
    int fridays13in400yearsBetween_20000_and_24000 = 687;
    int fridays13in400yearsBetween_24000_and_28000 = 684;
    
    
    int recoveryYear2 = d2, recoveryYear1 = d1;
    int dayOfWeek, i, fridaysPositionIn400YearsInterval;
    
    int fullYearInterval = d2 / 28000;
    
    
    long long int counter = 0;
    int remaiderPosition = 0;
    
    counter += findFullYear(&d2, 28000);
    
    counter += findFullYear(&d2, 24000);
    
    counter += findFullYear(&d2, 20000);
    
    counter += findFullYear(&d2, 16000);
    
    counter += findFullYear(&d2, 12000);
    
    counter += findFullYear(&d2, 8000);
    
    counter += findFullYear(&d2, 4000);
    
    remaiderPosition = ((recoveryYear2 - 1) / 4000) % 7;
    
    switch (remaiderPosition) {
        case 1:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_4000_and_8000;
            break;
        case 2:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_8000_and_12000;
            break;
        case 3:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_12000_and_16000;
            break;
        case 4:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_16000_and_20000;
            break;
        case 5:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_20000_and_24000;
            break;
        case 6:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_24000_and_28000;
            break;
        case 0:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_0_and_4000;
            break;
        default:
            fridaysPositionIn400YearsInterval = 0;
            break;
    }
    
    fullYearInterval = d2 / 400;
    if (fullYearInterval) {
        counter += fridaysPositionIn400YearsInterval * fullYearInterval;
        d2 -= fullYearInterval * 400;
    }
    

    for (i = recoveryYear2 - d2; i < recoveryYear2; i++) {
        dayOfWeek = wday(i, 3, 1, remaiderPosition);
        counter += fridays[dayOfWeek];
    }
    
    
    if (m2 < 3) {
        if (m2 == 1) {
            if (y2 < 13) {
                dayOfWeek = wday(recoveryYear2, 1, 13,remaiderPosition);
                if (dayOfWeek == 4) {
                    counter--;
                }
            }
            dayOfWeek = wday(recoveryYear2, 2, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter--;
            }
        }
        if (m2 == 2) {
            if (y2 < 13) {
                dayOfWeek = wday(recoveryYear2, 2, 13, remaiderPosition);
                if (dayOfWeek == 4) {
                    counter--;
                }
            }
        }
    } else {
    
        for (i = 3; i < m2; i++) {
            dayOfWeek = wday(recoveryYear2, i, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter++;
            }
        }
        
        if (y2 >= 13) {
            dayOfWeek = wday(recoveryYear2, m2, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter++;
            }
        }
    
    }
    
    /* --------------------------------------------------------------------- */
    /* d1 */
    
    y1 --;
    remaiderPosition = 0;
    
    counter -= findFullYear(&d1, 28000);
    
    counter -= findFullYear(&d1, 24000);
    
    counter -= findFullYear(&d1, 20000);
    
    counter -= findFullYear(&d1, 16000);
    
    counter -= findFullYear(&d1, 12000);
    
    counter -= findFullYear(&d1, 8000);
    
    counter -= findFullYear(&d1, 4000);
    
    
    remaiderPosition = ((recoveryYear1 - 1) / 4000) % 7;
    
    switch (remaiderPosition) {
        case 1:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_4000_and_8000;
            break;
        case 2:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_8000_and_12000;
            break;
        case 3:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_12000_and_16000;
            break;
        case 4:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_16000_and_20000;
            break;
        case 5:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_20000_and_24000;
            break;
        case 6:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_24000_and_28000;
            break;
        case 0:
            fridaysPositionIn400YearsInterval = fridays13in400yearsBetween_0_and_4000;
            break;
        default:
            fridaysPositionIn400YearsInterval = 0;
            break;
    }
    
    fullYearInterval = d1 / 400;
    if (fullYearInterval) {
        counter -= fridaysPositionIn400YearsInterval * fullYearInterval;
        d1 -= fullYearInterval * 400;
    }
    
    
    for (i = recoveryYear1 - d1; i < recoveryYear1; i++) {
        dayOfWeek = wday(i, 3, 1, remaiderPosition);
        counter -= fridays[dayOfWeek];
    }
    
    if (m1 < 3) {
        if (m1 == 1) {
            if (y1 < 13) {
                dayOfWeek = wday(recoveryYear1, 1, 13, remaiderPosition);
                if (dayOfWeek == 4) {
                    counter++;
                }
            }
            dayOfWeek = wday(recoveryYear1, 2, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter++;
            }
        }
        if (m1 == 2) {
            if (y1 < 13) {
                dayOfWeek = wday(recoveryYear1, 2, 13, remaiderPosition);
                if (dayOfWeek == 4) {
                    counter++;
                }
            }
        }
    } else {
    
        for (i = 3; i < m1; i++) {
            dayOfWeek = wday(recoveryYear1, i, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter--;
            }
        }
        
        if (y1 >= 13) {
            dayOfWeek = wday(recoveryYear1, m1, 13, remaiderPosition);
            if (dayOfWeek == 4) {
                counter--;
            }
        }
    }
    
    return counter;
}

int CountFriday13 ( int y1, int m1, int d1,
                   int y2, int m2, int d2, long long int * cnt )
{
    int numberOfDays[12] = {31, 111666111, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    
    /* Checking for the incorrect input */
    if (y1 < 1900 || m1 > 12 || m1 < 1 || m2 > 12 || m2 < 1) {
        return 0;
    }
    
    if (y2 < y1) {
        return 0;
        
    } else if (y2 == y1) {
        if (m2 < m1) {
            return 0;
            
        } else if (m2 == m1) {
            
            /* The 2 date is earlier than the first */
            if (d2 < d1) {
                return 0;
            }
        }
    }
    
    /* Calculates if the year is leap or not */
    if (y2 % 4 == 0 && y2 % 4000 != 0 && (y2 % 400 == 0 || y2 % 100 != 0)) {
        numberOfDays[1] = 29;
    } else {
        numberOfDays[1] = 28;
    }
    
    /* Incorrect day numbrer */
    if (numberOfDays[m2 - 1] < d2 || numberOfDays[m1 - 1] < d1) {
        return 0;
    }
    
    
    
    *cnt = countFridays13Between(d1, m1, y1, d2, m2, y2);
    return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    long long int cnt;
    
    assert ( CountFriday13 ( 2174, 11, 14, 205101914, 10, 25, &cnt ) == 1 && cnt == 351599554LL );// V
    assert ( CountFriday13 ( 2081, 10, 16, 200050093,  2, 20, &cnt ) == 1 && cnt == 342939446LL );//15+
    assert ( CountFriday13 ( 1901, 6, 24, 1995, 1, 4, &cnt ) == 1 && cnt == 161LL );// V
    assert ( CountFriday13 ( 1944, 2, 31, 2400, 10, 1, &cnt ) == 0); // V
    assert ( CountFriday13 ( 1900, 4, 24, 1958, 6, 17, &cnt ) == 1 && cnt == 100LL );// V
    assert ( CountFriday13 ( 2122, 2, 28, 20187, 9, 22, &cnt ) == 1 && cnt == 30961LL );//6+
    assert ( CountFriday13 ( 1945, 3, 28, 1945, 5, 2, &cnt ) == 1 && cnt == 1LL ); // V
    assert ( CountFriday13 ( 1900,  1,  1, 1900,  4, 13, &cnt ) == 1 && cnt == 1LL );// V
    assert ( CountFriday13 ( 28000,  1,  1, 56000,  1, 1, &cnt ) == 1 && cnt == 48000LL );// V
    assert ( CountFriday13 ( 2055,  3, 15, 209725592, 11, 12, &cnt ) == 1 && cnt == 359526067LL );//19+
    assert ( CountFriday13 ( 2021, 1, 21, 20947, 10, 16, &cnt ) == 1 && cnt == 32440LL ); //5+
    assert ( CountFriday13 ( 1900, 3,  1,  1900,  3, 13, &cnt ) == 1 && cnt == 0LL ); // V
    assert ( CountFriday13 ( 2142, 4,  2, 20286,  1, 11, &cnt ) == 1 && cnt == 31095LL );//6+
    assert ( CountFriday13 ( 2021, 1, 21, 20947, 10, 16, &cnt ) == 1 && cnt == 32440LL );//5+
    assert ( CountFriday13 ( 1900, 1,  1,  1965,  1, 13, &cnt ) == 1 && cnt == 113LL );// V
    assert ( CountFriday13 ( 1944, 2,  1,  1944,  1, 31, &cnt ) == 0); // V
    assert ( CountFriday13 ( 2015, 11, 13,  2015, 11, 13, &cnt ) == 1 && cnt == 1LL ); // V
    assert ( CountFriday13 ( 1900, 3, 1, 1900, 3, 13, &cnt ) == 1 && cnt == 0LL ); // V
    assert ( CountFriday13 ( 1900, 1, 1, 1965, 1, 13, &cnt ) == 1 && cnt == 113LL ); // V
    assert (CountFriday13 ( 1944, 2, 1, 1944, 1, 31, &cnt ) == 0 ); // V
    
    assert ( CountFriday13 ( 1900,  1,  1,
                            2015,  1,  1, &cnt ) == 1
            && cnt == 197LL );
    assert ( CountFriday13 ( 1900,  1,  1,
                            2015,  2,  1, &cnt ) == 1
            && cnt == 197LL );
    assert ( CountFriday13 ( 1900,  1,  1,
                            2015,  1, 13, &cnt ) == 1
            && cnt == 197LL );
    assert ( CountFriday13 ( 1900,  1,  1,
                            2015,  2, 13, &cnt ) == 1
            && cnt == 198LL );//
    assert ( CountFriday13 ( 1904,  1,  1,
                            2015,  1,  1, &cnt ) == 1
            && cnt == 189LL );//
    assert ( CountFriday13 ( 1904,  1,  1,
                            2015,  2,  1, &cnt ) == 1
            && cnt == 189LL );//
    assert ( CountFriday13 ( 1904,  1,  1,
                            2015,  1, 13, &cnt ) == 1
            && cnt == 189LL );//
    assert ( CountFriday13 ( 1904,  1,  1,
                            2015,  2, 13, &cnt ) == 1
            && cnt == 190LL );//
    assert ( CountFriday13 ( 1905,  2, 13,
                            2015,  1,  1, &cnt ) == 1
            && cnt == 187LL );//
    assert ( CountFriday13 ( 1905,  2, 13,
                            2015,  2,  1, &cnt ) == 1
            && cnt == 187LL );
    assert ( CountFriday13 ( 1905,  2, 13,
                            2015,  1, 13, &cnt ) == 1
            && cnt == 187LL );
    assert ( CountFriday13 ( 1905,  2, 13,
                            2015,  2, 13, &cnt ) == 1
            && cnt == 188LL );
    assert ( CountFriday13 ( 1905,  1, 13,
                            2015,  1,  1, &cnt ) == 1
            && cnt == 188LL );
    assert ( CountFriday13 ( 1905,  1, 13,
                            2015,  2,  1, &cnt ) == 1
            && cnt == 188LL );
    assert ( CountFriday13 ( 1905,  1, 13,
                            2015,  1, 13, &cnt ) == 1
            && cnt == 188LL );
    assert ( CountFriday13 ( 1905,  1, 13,
                            2015,  2, 13, &cnt ) == 1
            && cnt == 189LL );
    assert ( CountFriday13 ( 2015, 11,  1,
                            2015, 10,  1, &cnt ) == 0 );
    assert ( CountFriday13 ( 2015, 10, 32,
                            2015, 11, 10, &cnt ) == 0 );
    assert ( CountFriday13 ( 2090,  2, 29,
                            2090,  2, 29, &cnt ) == 0 );
    assert ( CountFriday13 ( 2096,  2, 29,
                            2096,  2, 29, &cnt ) == 1
            && cnt == 0LL );
    assert ( CountFriday13 ( 2100,  2, 29,
                            2100,  2, 29, &cnt ) == 0 );
    assert ( CountFriday13 ( 2000,  2, 29,
                            2000,  2, 29, &cnt ) == 1
            && cnt == 0LL );
    return 0;
}
#endif /* __PROGTEST__ */
