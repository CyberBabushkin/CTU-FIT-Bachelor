REM INSERTING into BABUSAND.FAN
SET DEFINE OFF;
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('0','Andrey                        ','Babushkin                     ','Dark Blond','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('3','Gregory                       ','Trubchanin                    ','Black     ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('1','Radek                         ','Storc                         ','Dark Blond','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('2','Tomas                         ','Kasprzik                      ','Dark Blond','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('4','Karel                         ','Halla                         ','Dark Brown','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('5','Angus                         ','Young                         ','Black     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('6','Cliff                         ','Williams                      ','Blond     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('7','Robbie                        ','Williams                      ','Black     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('8','Tomas                         ','Lajsky                        ','Dark      ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('9','Luna                          ','Mure                          ','Blond     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('10','Ifca                          ','Frauendinova                  ','Blond     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('11','Aria                          ','Stark                         ','Black     ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('12','Sansa                         ','Stark                         ','Ginger    ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('13','Abdulla                       ','Khamilli                      ','Black     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('14','Ibragim                       ','Dauleussov                    ','Dark Blond','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('15','Andrej                        ','Malinnikov                    ','Dark Blue ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('16','Mana                          ','Linhartova                    ','Blond     ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('17','Hanna                         ','Isomaki                       ','Purple    ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('18','Martina                       ','Deuringer                     ','Red       ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('19','Alfonso                       ','Barnes                        ','Black     ','0');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('20','The First                     ','King of Metal                 ','Blackest  ','1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('21','Wolfgang Amadeus              ','Mozart                        ',null,null);
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('22','Jeff                          ','Abel                          ',null,'1');
Insert into BABUSAND.FAN (FAN_ID,NAME,FAM_NAME,HAIR_COLOR,TATTOO) values ('23','Eric                          ','Adams                         ','Black     ','1');
REM INSERTING into BABUSAND.MUSICIAN
SET DEFINE OFF;
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Vocals              ','0');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Guitar              ','1');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Drums               ','2');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Guitar              ','3');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Bass                ','4');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Vocals              ','7');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Guitar              ','5');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Bass                ','6');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Vocals, Guitar      ','20');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Harpsichord         ','21');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('DJ                  ','22');
Insert into BABUSAND.MUSICIAN (ROLE,FAN_FAN_ID) values ('Vocals              ','23');
REM INSERTING into BABUSAND.BAND
SET DEFINE OFF;
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('Kings Of Metal                                    ','Heavy Metal                                       ',to_date('23.12.01','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('Robbie Williams                                   ','Pop                                               ',to_date('12.01.90','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('Excision                                          ','Dubstep                                           ',to_date('12.03.04','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('Manowar                                           ','American Power Metal                              ',to_date('16.04.80','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('RAW                                               ','Metal                                             ',to_date('01.09.15','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('AC/DC                                             ','Metal                                             ',to_date('01.11.73','DD.MM.RR'),null);
Insert into BABUSAND.BAND (NAME,STYLE,BIRTHDAY,DEATHDAY) values ('Mozart                                            ','Classical                                         ',to_date('27.01.56','DD.MM.RR'),to_date('05.12.91','DD.MM.RR'));
REM INSERTING into BABUSAND.IN_BAND
SET DEFINE OFF;
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('AC/DC                                             ','5');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('AC/DC                                             ','6');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('Excision                                          ','22');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('Kings Of Metal                                    ','20');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('Manowar                                           ','23');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('Mozart                                            ','21');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('RAW                                               ','0');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('RAW                                               ','1');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('RAW                                               ','2');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('RAW                                               ','3');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('RAW                                               ','4');
Insert into BABUSAND.IN_BAND (BAND_NAME,MUSICIAN_FAN_ID) values ('Robbie Williams                                   ','7');
REM INSERTING into BABUSAND.SONG
SET DEFINE OFF;
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Follow Your Instincts','Recreate And Witness',to_date('10.05.16','DD.MM.RR'),'222','RAW                                               ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Struggle','Recreate And Witness',to_date('14.04.16','DD.MM.RR'),'231','RAW                                               ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Rise','Recreate And Witness',to_date('03.03.16','DD.MM.RR'),'185','RAW                                               ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Feel','Feel',to_date('05.03.09','DD.MM.RR'),'228','Robbie Williams                                   ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Killing Metal','Metal \m/',to_date('06.06.66','DD.MM.RR'),'666','Kings Of Metal                                    ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Robo Kitty','Codename X',to_date('12.10.15','DD.MM.RR'),'250','Excision                                          ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Manowar','Manowar',to_date('14.03.95','DD.MM.RR'),'294','Manowar                                           ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Rock ''n'' Roll Train','Black Ice',to_date('18.08.08','DD.MM.RR'),'284','AC/DC                                             ');
Insert into BABUSAND.SONG (SONG_NAME,ALBUM,YEAR,LENGTH,BAND_NAME) values ('Overture to The Marriage of Figaro','The Marriage of Figaro',to_date('01.01.86','DD.MM.RR'),'240','Mozart                                            ');
REM INSERTING into BABUSAND.IS_FAN
SET DEFINE OFF;
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('0','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('0','Mozart                                            ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('0','Robbie Williams                                   ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('1','Kings Of Metal                                    ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('2','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('3','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('4','Kings Of Metal                                    ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('5','Kings Of Metal                                    ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('7','Mozart                                            ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('8','RAW                                               ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('9','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('9','RAW                                               ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('10','RAW                                               ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('11','Mozart                                            ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('12','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('12','Mozart                                            ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('13','Excision                                          ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('14','Excision                                          ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('15','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('15','Kings Of Metal                                    ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('15','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('15','RAW                                               ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('16','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('17','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('17','Excision                                          ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('17','Robbie Williams                                   ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('18','AC/DC                                             ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('18','RAW                                               ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('19','Excision                                          ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('20','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('22','Kings Of Metal                                    ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('22','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('23','Manowar                                           ');
Insert into BABUSAND.IS_FAN (FAN_FAN_ID,BAND_NAME) values ('23','Mozart                                            ');
REM INSERTING into BABUSAND.PLACE
SET DEFINE OFF;
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Festival Village, Germany                                                                           ','+43 955799568       ','1000000','The Biggest Fest    ');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Broadway 12, NY                                                                                     ','+109887634          ','100','A Club              ');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Slovenska, 1888/88, Praha                                                                           ','+420433953100       ','300','Demolish and Conquer');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Gig St, 54, Guatemala                                                                               ','+23415785445        ','30','Guatemala Club      ');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Sokolovska, 195, Praha                                                                              ','+420 602 695 549    ','200','Exit-US             ');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ','+4827 999 66 999    ','100000','Wacken Open Air     ');
Insert into BABUSAND.PLACE (ADDRESS,PHONE_NUMBER,CAPACITY,NAME) values ('Hofburg Vienna, Heldenplatz, 1010 Wien                                                              ','+43 1 5337570       ','500','Hofburg             ');
REM INSERTING into BABUSAND.CONCERT
SET DEFINE OFF;
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('28.05.16','DD.MM.RR'),to_date('31.05.16','DD.MM.RR'),'MetalFest                                         ','2000','Festival Village, Germany                                                                           ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('04.06.03','DD.MM.RR'),to_date('04.06.03','DD.MM.RR'),'The Nature                                        ','100','Broadway 12, NY                                                                                     ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('07.07.16','DD.MM.RR'),to_date('10.07.16','DD.MM.RR'),'WOA                                               ','3450','Hauptstraße, 47, Wacken, Deutschland                                                                ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('07.07.15','DD.MM.RR'),to_date('10.07.15','DD.MM.RR'),'WOA                                               ','3000','Hauptstraße, 47, Wacken, Deutschland                                                                ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('07.07.14','DD.MM.RR'),to_date('10.07.14','DD.MM.RR'),'WOA                                               ','3450','Hauptstraße, 47, Wacken, Deutschland                                                                ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('04.06.13','DD.MM.RR'),to_date('07.06.13','DD.MM.RR'),'WOA                                               ','2500','Hauptstraße, 47, Wacken, Deutschland                                                                ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('14.05.16','DD.MM.RR'),to_date('15.05.16','DD.MM.RR'),'Recreate And Witness Tour                         ','100','Sokolovska, 195, Praha                                                                              ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('27.01.76','DD.MM.RR'),to_date('27.01.76','DD.MM.RR'),'For the Queen                                     ','10000','Hofburg Vienna, Heldenplatz, 1010 Wien                                                              ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('15.11.13','DD.MM.RR'),to_date('16.11.13','DD.MM.RR'),'The Wind                                          ','500','Broadway 12, NY                                                                                     ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('15.11.13','DD.MM.RR'),to_date('16.11.13','DD.MM.RR'),'The Earth                                         ','500','Slovenska, 1888/88, Praha                                                                           ');
Insert into BABUSAND.CONCERT (DATETIME_START,DATETIME_END,NAME,TICKET_PRICE,PLACE_ADDRESS) values (to_date('14.11.16','DD.MM.RR'),to_date('15.11.16','DD.MM.RR'),'Evmet                                             ','100','Slovenska, 1888/88, Praha                                                                           ');
REM INSERTING into BABUSAND.PERFORMANCE
SET DEFINE OFF;
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Broadway 12, NY                                                                                     ',to_date('04.06.03','DD.MM.RR'),'Excision                                          ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Broadway 12, NY                                                                                     ',to_date('15.11.13','DD.MM.RR'),'Robbie Williams                                   ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'AC/DC                                             ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'Kings Of Metal                                    ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'Kings Of Metal                                    ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'Manowar                                           ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'RAW                                               ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'AC/DC                                             ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'Kings Of Metal                                    ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'AC/DC                                             ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'Kings Of Metal                                    ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'Manowar                                           ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Hofburg Vienna, Heldenplatz, 1010 Wien                                                              ',to_date('27.01.76','DD.MM.RR'),'Mozart                                            ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('15.11.13','DD.MM.RR'),'Excision                                          ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'Kings Of Metal                                    ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'RAW                                               ');
Insert into BABUSAND.PERFORMANCE (CONCERT_ADDRESS,CONCERT_DATETIME_START,BAND_NAME) values ('Sokolovska, 195, Praha                                                                              ',to_date('14.05.16','DD.MM.RR'),'RAW                                               ');
REM INSERTING into BABUSAND.HAVING_FUN
SET DEFINE OFF;
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Broadway 12, NY                                                                                     ',to_date('15.11.13','DD.MM.RR'),'0');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'0');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'0');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'0');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'0');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'1');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'1');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'2');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'3');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'4');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.16','DD.MM.RR'),'4');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'5');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'5');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'8');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'8');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'9');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'9');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'9');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'10');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'10');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'11');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('04.06.13','DD.MM.RR'),'12');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'12');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('15.11.13','DD.MM.RR'),'13');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'13');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('15.11.13','DD.MM.RR'),'14');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Sokolovska, 195, Praha                                                                              ',to_date('14.05.16','DD.MM.RR'),'14');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'15');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.15','DD.MM.RR'),'15');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'16');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Broadway 12, NY                                                                                     ',to_date('04.06.03','DD.MM.RR'),'17');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Broadway 12, NY                                                                                     ',to_date('15.11.13','DD.MM.RR'),'17');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Broadway 12, NY                                                                                     ',to_date('04.06.03','DD.MM.RR'),'18');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'18');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Slovenska, 1888/88, Praha                                                                           ',to_date('14.11.16','DD.MM.RR'),'18');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Sokolovska, 195, Praha                                                                              ',to_date('14.05.16','DD.MM.RR'),'18');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Hauptstraße, 47, Wacken, Deutschland                                                                ',to_date('07.07.14','DD.MM.RR'),'22');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Sokolovska, 195, Praha                                                                              ',to_date('14.05.16','DD.MM.RR'),'22');
Insert into BABUSAND.HAVING_FUN (CONCERT_ADDRESS,CONCERT_DATETIME_START,FAN_FAN_ID) values ('Sokolovska, 195, Praha                                                                              ',to_date('14.05.16','DD.MM.RR'),'23');
REM INSERTING into BABUSAND.MUS_INST
SET DEFINE OFF;
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('24','True DJ''s Synt                ','22','ELECTRONIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('0','Shure SM57                    ','0','MIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('1','Ibanez Black                  ','1','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('2','DrumKit Professional          ','2','PERCUSSION');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('3','Ibanez Solo                   ','3','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('4','Cool Bass Guitar              ','4','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('5','Fender Solo                   ','3','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('6','Fender Guitar                 ','3','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('7','Ibanez Heavy                  ','1','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('8','Fender XCort                  ','0','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('9','Line6                         ','0','OTHER');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('10','Vargan                        ','0','OTHER');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('11','Sennheiser EW 145 G3          ','7','MIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('12','Gibson SG                     ','5','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('13','StingRay                      ','6','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('14','Ibanez Black                  ','20','STRINGED');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('15','Shure SM58                    ','20','MIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('16','The Mozart''s Harpsichord      ','21','KEYBOARD');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('17','Ableton Live                  ','22','ELECTRONIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('18','Cool Metal Mic                ','20','MIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('19','True Metal Saxophone          ','20','WIND');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('20','True Metal Piano              ','20','KEYBOARD');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('21','True Metal Mixer              ','20','ELECTRONIC');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('22','True Metal Drums              ','20','PERCUSSION');
Insert into BABUSAND.MUS_INST (INSTRUMENT_INS_ID,INSTRUMENT_NAME,MUSICIAN_FAN_ID,INST_DESC_ID) values ('23','True Metal 50000W Amplifier   ','20','OTHER');
REM INSERTING into BABUSAND.ELECTRONIC
SET DEFINE OFF;
Insert into BABUSAND.ELECTRONIC (INSTRUMENT_INS_ID,SYNTHESIZER) values ('24','1');
Insert into BABUSAND.ELECTRONIC (INSTRUMENT_INS_ID,SYNTHESIZER) values ('17','0');
Insert into BABUSAND.ELECTRONIC (INSTRUMENT_INS_ID,SYNTHESIZER) values ('21','0');
REM INSERTING into BABUSAND.KEYBOARD
SET DEFINE OFF;
Insert into BABUSAND.KEYBOARD (INSTRUMENT_INS_ID,NUM_OF_OCTAVES) values ('16','7');
Insert into BABUSAND.KEYBOARD (INSTRUMENT_INS_ID,NUM_OF_OCTAVES) values ('20','6');
REM INSERTING into BABUSAND.MIC
SET DEFINE OFF;
Insert into BABUSAND.MIC (INSTRUMENT_INS_ID,TYPE) values ('0','Dynamic');
Insert into BABUSAND.MIC (INSTRUMENT_INS_ID,TYPE) values ('11','Condenser');
Insert into BABUSAND.MIC (INSTRUMENT_INS_ID,TYPE) values ('15','Dynamic');
Insert into BABUSAND.MIC (INSTRUMENT_INS_ID,TYPE) values ('18','Condenser');
REM INSERTING into BABUSAND.OTHER
SET DEFINE OFF;
Insert into BABUSAND.OTHER (INSTRUMENT_INS_ID,INSTRUMENT_NAME) values ('9','Guitar amplifier');
Insert into BABUSAND.OTHER (INSTRUMENT_INS_ID,INSTRUMENT_NAME) values ('10','Jew''s harp');
Insert into BABUSAND.OTHER (INSTRUMENT_INS_ID,INSTRUMENT_NAME) values ('23','Devil''s Amplifier');
REM INSERTING into BABUSAND.PERCUSSION
SET DEFINE OFF;
Insert into BABUSAND.PERCUSSION (INSTRUMENT_INS_ID,NEED_STICKS) values ('2','1');
Insert into BABUSAND.PERCUSSION (INSTRUMENT_INS_ID,NEED_STICKS) values ('22','1');
REM INSERTING into BABUSAND.STRINGED
SET DEFINE OFF;
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('1','7');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('3','7');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('4','5');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('5','6');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('6','6');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('7','6');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('8','6');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('12','6');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('13','4');
Insert into BABUSAND.STRINGED (INSTRUMENT_INS_ID,NUM_OF_STRINGS) values ('14','7');
REM INSERTING into BABUSAND.WIND
SET DEFINE OFF;
Insert into BABUSAND.WIND (INSTRUMENT_INS_ID,RANGE) values ('19','19');

begin
  -- naplníme hodnoty do sloupce NUM_ROWS v pohledu USER_TABLES (metadata v datovém slovníku)
  DBMS_STATS.GATHER_SCHEMA_STATS
    (ownname => user,
     estimate_percent => 100
    );
end;
/
SELECT TABLE_NAME,NUM_ROWS
FROM user_tables;