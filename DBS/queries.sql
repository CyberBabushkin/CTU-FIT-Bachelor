set linesize 2000;
SET SQLFORMAT html;

SELECT DISTINCT band_name
FROM
  (SELECT DISTINCT *
   FROM
     (SELECT DISTINCT band_name,
                      fan_id
      FROM
        (SELECT DISTINCT *
         FROM in_band
         JOIN fan ON musician_fan_id = fan_id))
   JOIN musician ON fan_id = fan_fan_id)
WHERE role = 'Guitar';

SELECT name, fam_name 
FROM 
(SELECT 
  name, 
  fam_name, 
  (SELECT count(*)
  FROM IS_FAN
  WHERE fan_fan_id = fan_id) as Bands
FROM FAN)
WHERE Bands >= 2;

SELECT DISTINCT name
FROM BAND
WHERE DEATHDAY IS NOT NULL;

SELECT name, address, COALESCE(Bands, 0) as Bands
FROM PLACE
LEFT OUTER JOIN
  (SELECT concert_address, COUNT(*) as Bands
  FROM
    (SELECT DISTINCT concert_address, band_name
    FROM PERFORMANCE)
  GROUP BY concert_address)
ON PLACE.ADDRESS = concert_address;

SELECT DISTINCT band_name AS "Name"
FROM IN_BAND
INNER JOIN MUS_INST
ON MUS_INST.MUSICIAN_FAN_ID = IN_BAND.MUSICIAN_FAN_ID
INNER JOIN KEYBOARD
ON MUS_INST.INSTRUMENT_INS_ID = KEYBOARD.INSTRUMENT_INS_ID
WHERE KEYBOARD.NUM_OF_OCTAVES > 5;

SELECT DISTINCT MUS_INST.INSTRUMENT_NAME AS "Name", MUS_INST.INST_DESC_ID AS "Type" 
FROM IN_BAND
INNER JOIN MUS_INST
ON MUS_INST.MUSICIAN_FAN_ID = IN_BAND.MUSICIAN_FAN_ID
WHERE IN_BAND.BAND_NAME = 'RAW';

SELECT DISTINCT name
FROM
(SELECT name, PERFORMANCE.CONCERT_DATETIME_START
FROM BAND
LEFT OUTER JOIN PERFORMANCE
ON PERFORMANCE.BAND_NAME = BAND.NAME)
WHERE CONCERT_DATETIME_START IS NOT NULL;

SELECT DISTINCT band_name 
FROM PERFORMANCE
WHERE
  (to_date(to_char(concert_datetime_start, 'DD.MM') || '.2016', 'DD.MM.YYYY') >= to_date('1.6.2016', 'DD.MM.YYYY'))
  AND
  (to_date(to_char(concert_datetime_start, 'DD.MM') || '.2016', 'DD.MM.YYYY') <= to_date('31.8.2016', 'DD.MM.YYYY'));
  
SELECT name, fam_name
FROM FAN 
NATURAL JOIN
  ((SELECT fan_fan_id AS fan_id
    FROM IS_FAN
    WHERE band_name = 'AC/DC')
  MINUS
    (SELECT fan_fan_id AS fan_id
    FROM IS_FAN
    WHERE band_name != 'AC/DC'));

(SELECT DISTINCT *
   FROM
     (SELECT DISTINCT name,
                      fam_name
      FROM FAN)) MINUS
  (SELECT DISTINCT *
   FROM
     (SELECT DISTINCT name, fam_name
      FROM (
              (SELECT DISTINCT *
               FROM
                 (SELECT DISTINCT *
                  FROM
                    (SELECT DISTINCT fan_id, name, fam_name
                     FROM FAN)
                  CROSS JOIN
                    (SELECT DISTINCT inst_desc_id
                     FROM MUS_INST))) MINUS
              (SELECT DISTINCT *
               FROM
                 (SELECT DISTINCT fan_id, name, fam_name, inst_desc_id
                  FROM
                    (SELECT DISTINCT *
                     FROM FAN
                     JOIN MUS_INST ON fan_id = musician_fan_id))))));

SELECT DISTINCT NAME, FAM_NAME
FROM FAN JOIN MUSICIAN ON (FAN_ID = FAN_FAN_ID);

SELECT DISTINCT name,
                fam_name
FROM
  (SELECT DISTINCT *
   FROM fan MINUS
     (SELECT DISTINCT *
      FROM
        (SELECT DISTINCT *
         FROM fan
         WHERE EXISTS
             (SELECT 1
              FROM is_fan
              WHERE fan_id = fan_fan_id))));
              
SELECT  name, address
FROM PLACE
WHERE PLACE.address NOT IN (SELECT concert_address AS address
                      FROM PERFORMANCE);
                      
(SELECT DISTINCT *
   FROM ((((((
                (SELECT DISTINCT *
                 FROM
                   (SELECT DISTINCT musician_fan_id
                    FROM MUS_INST
                    WHERE inst_desc_id = 'MIC')) INTERSECT
                (SELECT DISTINCT *
                 FROM
                   (SELECT DISTINCT musician_fan_id
                    FROM MUS_INST
                    WHERE inst_desc_id = 'ELECTRONIC'))) INTERSECT
               (SELECT DISTINCT *
                FROM
                  (SELECT DISTINCT musician_fan_id
                   FROM MUS_INST
                   WHERE inst_desc_id = 'KEYBOARD'))) INTERSECT
              (SELECT DISTINCT *
               FROM
                 (SELECT DISTINCT musician_fan_id
                  FROM MUS_INST
                  WHERE inst_desc_id = 'OTHER'))) INTERSECT
             (SELECT DISTINCT *
              FROM
                (SELECT DISTINCT musician_fan_id
                 FROM MUS_INST
                 WHERE inst_desc_id = 'PERCUSSION'))) INTERSECT
            (SELECT DISTINCT *
             FROM
               (SELECT DISTINCT musician_fan_id
                FROM MUS_INST
                WHERE inst_desc_id = 'STRINGED'))) INTERSECT
           (SELECT DISTINCT *
            FROM
              (SELECT DISTINCT musician_fan_id
               FROM MUS_INST
               WHERE inst_desc_id = 'WIND')))) MINUS
  (SELECT DISTINCT *
   FROM (
           (SELECT DISTINCT *
            FROM
              (SELECT DISTINCT fan_id
               FROM FAN)) MINUS
           (SELECT DISTINCT *
            FROM
              (SELECT DISTINCT fan_id
               FROM (
                       (SELECT DISTINCT *
                        FROM
                          (SELECT DISTINCT *
                           FROM
                             (SELECT DISTINCT fan_id
                              FROM FAN)
                           CROSS JOIN
                             (SELECT DISTINCT inst_desc_id
                              FROM MUS_INST))) MINUS
                       (SELECT DISTINCT *
                        FROM
                          (SELECT DISTINCT fan_id, inst_desc_id
                           FROM
                             (SELECT DISTINCT *
                              FROM FAN
                              JOIN MUS_INST ON fan_id = musician_fan_id))))))));
                              
SELECT BAND.name, COUNT(*) AS num
FROM PERFORMANCE
LEFT OUTER JOIN BAND
ON BAND.name = PERFORMANCE.band_name
GROUP BY BAND.name;

SELECT FAN.name, PERFORMANCE.band_name, COUNT(*) AS NumberOfConcerts
FROM ((PERFORMANCE
INNER JOIN HAVING_FUN
ON PERFORMANCE.CONCERT_ADDRESS = HAVING_FUN.CONCERT_ADDRESS
  AND PERFORMANCE.CONCERT_DATETIME_START = HAVING_FUN.CONCERT_DATETIME_START)
INNER JOIN FAN
ON FAN.fan_id = HAVING_FUN.fan_fan_id)
WHERE PERFORMANCE.band_name != 'AC/DC'
GROUP BY FAN.name, PERFORMANCE.band_name
HAVING COUNT(*) > 0
ORDER BY FAN.name, PERFORMANCE.band_name;

CREATE OR REPLACE VIEW Tattoo_View AS 
SELECT name, fam_name
FROM FAN
WHERE TATTOO = '1'
ORDER BY name, fam_name;

UPDATE CONCERT
SET ticket_price = ticket_price * 1.15
WHERE 
    (SELECT count(*)  
    FROM PERFORMANCE
    WHERE datetime_start = concert_datetime_start
      AND
    place_address = concert_address) > 2
  AND
    NAME = 'WOA';
COMMIT;

DELETE FROM PERFORMANCE
WHERE band_name IN
    (SELECT name  
    FROM BAND
    INNER JOIN PERFORMANCE
    ON PERFORMANCE.BAND_NAME = BAND.NAME
    WHERE deathday is not null
      AND
      deathday < PERFORMANCE.CONCERT_DATETIME_START);
COMMIT;

SELECT *
FROM
(SELECT 
  name, 
  (SELECT COUNT(*)
  FROM SONG
  WHERE name = band_name) as Songs
FROM BAND)
WHERE Songs = 1
UNION
SELECT *
FROM
(SELECT 
  name, 
  (SELECT COUNT(*)
  FROM SONG
  WHERE name = band_name) as Songs
FROM BAND)
WHERE Songs = 3;

SELECT *
FROM
(
  SELECT DISTINCT band_name, COUNT(*) AS Songs
  FROM SONG
  LEFT OUTER JOIN BAND
  ON BAND.name = SONG.band_name
  GROUP BY band_name
)
WHERE Songs = 1 OR Songs = 3;

SELECT *
FROM
(SELECT 
  name, 
  (SELECT COUNT(*)
  FROM SONG
  WHERE name = band_name) as Songs
FROM BAND)
WHERE Songs in (1,3);

CREATE OR REPLACE VIEW ALL_FANS
AS
SELECT name, fam_name, band_name
FROM FAN
FULL OUTER JOIN IS_FAN
ON FAN.FAN_ID = IS_FAN.FAN_FAN_ID;

SELECT name as "Name", fam_name as "Family name"
FROM ALL_FANS
WHERE BAND_NAME = 'RAW'
ORDER BY name, fam_name;

DELETE FROM PERFORMANCE
WHERE CONCERT_ADDRESS = 'Festival Village, Germany'
      AND CONCERT_DATETIME_START = '28.05.2016'
      AND band_name IN
        (SELECT name  
        FROM BAND
        WHERE STYLE LIKE '%Metal%');
COMMIT;

INSERT INTO PERFORMANCE( CONCERT_ADDRESS, CONCERT_DATETIME_START, BAND_NAME )
SELECT 'Festival Village, Germany', '28.05.2016', name
FROM BAND
WHERE BAND.STYLE LIKE '%Metal%';
COMMIT;

SELECT name, fam_name
FROM FAN
INNER JOIN MUS_INST
ON MUS_INST.MUSICIAN_FAN_ID = FAN.FAN_ID
INNER JOIN ELECTRONIC
ON MUS_INST.INSTRUMENT_INS_ID = ELECTRONIC.INSTRUMENT_INS_ID 
WHERE synthesizer = '1';