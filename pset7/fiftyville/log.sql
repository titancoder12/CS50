-- Keep a log of any SQL queries you execute as you solve the mystery.

--Checking discription of the crime
SELECT * FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28;
--found: Interveiw mentions bakery.
--Suspicious: money Laundering after
--Took place at 10:15am

--Checking interveiw transcripts:
SELECT transcript FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

--Rewriting Query
SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;
--theif was using Leggett street ATM in the morning
--theif drove away in car 10 min after theft
--something about a souvenir from the King of Bohemia in return for the case of the Irene Adler papers

--Check phone calls for suspect's call
SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
ORDER BY duration;
--id:261
--caller: 031 555-6622
--reciever: 910 555-3251

--Find out who has that phone number
SELECT * FROM people
WHERE phone_number = "(031) 555-6622"
OR phone_number = "(910) 555-3251";
--|   id   |    name            |  phone_number  | passport_number | license_plate |
--+--------+------------+----------------+-----------------+---------------+
--| 712712 |Jacqueline(reciever)| (910) 555-3251 |           | 43V0R5D   |
--| 907148 |Carina(caller)      | (031) 555-6622 | 9628244268  | Q12B3Z3   |

--Find licence plates in parking lot at the time
SELECT * FROM bakery_security_logs
WHERE license_plate = "43V0R5D"
AND year = 2021;

SELECT * FROM bakery_security_logs
WHERE license_plate = "Q12B3Z3"
AND year = 2021;

--+-----+------+-------+-----+------+--------+----------+---------------+
--| id  | year | month | day | hour | minute | activity | license_plate |
--+-----+------+-------+-----+------+--------+----------+---------------+
--| 382 | 2021 | 7     | 30  | 11   | 44     | entrance | 43V0R5D       |
--| 443 | 2021 | 7     | 30  | 18   | 30     | exit     | 43V0R5D       |
--+-----+------+-------+-----+------+--------+----------+---------------+

--check flights on 30th
SELECT * FROM flights
WHERE year = 2021
AND month = 7
AND day = 30
AND hour > 18;
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 8  | 8                 | 2                      | 2021 | 7     | 30  | 20   | 56     |
--| 31 | 8                 | 3                      | 2021 | 7     | 30  | 20   | 21     |
--+----+-------------------+------------------------+------+-------+-----+------+--------+

--Check airports
SELECT DISTINCT city, year, month, day, hour, minute FROM airports, flights
WHERE airports.id = flights.destination_airport_id
AND year = 2021
AND month = 7
AND day = 30
AND hour > 18;

--check ATMs
SELECT * FROM atm_transactions
WHERE atm_location = "Leggett Street"
AND year = 2021
AND month = 7
AND day = 28;

--get bank account info and names
SELECT * FROM bank_accounts, atm_transactions, people
WHERE bank_accounts.account_number = atm_transactions.account_number
AND bank_accounts.person_id = people.id
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28;
--+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+--------+---------+----------------+-----------------+---------------+
--| account_number | person_id | creation_year | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |   id   |  name   |  phone_number  | passport_number | license_plate |
--+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+--------+---------+----------------+-----------------+---------------+
--| 49610011       | 686048    | 2010          | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 86363979       | 948985    | 2010          | 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     | 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
--| 26013199       | 514354    | 2012          | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 16153065       | 458378    | 2012          | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
--| 28296815       | 395717    | 2014          | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
--| 25506511       | 396669    | 2014          | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 28500762       | 467400    | 2014          | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 76054385       | 449774    | 2015          | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
--| 81061156       | 438727    | 2018          | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
--+----------------+-----------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+--------+---------+----------------+-----------------+---------------+

--check if any of them are in flights
SELECT DISTINCT * FROM flights, passengers, people, airports
WHERE passengers.passport_number = people.passport_number
AND flights.id = passengers.flight_id
AND (airports.id = flights.origin_airport_id
OR airports.id = flights.destination_airport_id)
AND year = 2021
AND month = 7
AND day = 28;

--check phone numbers again
SELECT * FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
ORDER BY duration;

--find who has those numbers
--+-----+----------------+----------------+------+-------+-----+----------+
--| id  |     caller     |    receiver    | year | month | day | duration |
--+-----+----------------+----------------+------+-------+-----+----------+
--| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |

SELECT * FROM people, atm_transactions
WHERE phone_number = "(499) 555-9472"
OR phone_number = "(892) 555-8872";
--+--------+--------+----------------+-----------------+---------------+
--|   id   |  name  |  phone_number  | passport_number | license_plate |
--+--------+--------+----------------+-----------------+---------------+
--| 251693 |(reciever)Larry |(892) 555-8872|2312901747 |O268ZZ0        |
--| 560886 | (caller)Kelsey |(499) 555-9472|8294398571 |0NTHK55        |
--+--------+--------+----------------+-----------------+---------------+

--find info
SELECT * FROM people
WHERE name = "Larry"
OR name = "Kelsey";

--find if liscence plate was at the bakery on the theft date
SELECT * FROM bakery_security_logs, people
WHERE bakery_security_logs.license_plate = people.license_plate
AND (people.name = "Larry" OR people.name = "Kelsey");
--+-----+------+-------+-----+------+--------+----------+---------------+--------+--------+----------------+-----------------+---------------+
--| id  | year | month | day | hour | minute | activity | license_plate |   id   |  name  |  phone_number  | passport_number | license_plate |
--+-----+------+-------+-----+------+--------+----------+---------------+--------+--------+----------------+-----------------+---------------+
--| 243 | 2021 | 7     | 28  | 8    | 42     | entrance | 0NTHK55       | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
--| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
--+-----+------+-------+-----+------+--------+----------+---------------+--------+--------+----------------+-----------------+---------------+
--Larry and Kelsey very suspicious

--check crime scene reports to see when crime happended
SELECT * FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28;
--Thief is Kelsey
--Thief's acompolice is Larry

--check flights with kelsey onboard on 29th of July
SELECT * FROM flights, passengers, people, airports
WHERE flights.id = passengers.flight_id
AND passengers.passport_number = people.passport_number
AND (flights.origin_airport_id = airports.id OR flights.destination_airport_id = airports.id)
AND people.name = "Kelsey";
--Thief escaped to New York

--wrong answer?

--check robert and patrick
SELECT * FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate
AND year = 2021
AND month = 7
AND day = 28;

--Find what fiftyville's id is
SELECT * FROM airports;

--check earliest flights out of fiftyvillle
SELECT DISTINCT * FROM flights, passengers, airports, people
WHERE flights.id = passengers.flight_id
AND (flights.destination_airport_id = airports.id AND flights.origin_airport_id = 8)
AND passengers.passport_number = people.passport_number
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute;

+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+----+--------------+-------------------------------------+---------------+--------+-----------+----------------+-----------------+---------------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat | id | abbreviation |              full_name              |     city      |   id   |   name    |  phone_number  | passport_number | license_plate |
+----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+----+--------------+-------------------------------------+---------------+--------+-----------+----------------+-----------------+---------------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 7214083635      | 2A   | 4  | LGA          | LaGuardia Air

--get all passengers in flight
SELECT * FROM passengers, flights, people
WHERE passengers.flight_id = flights.id
AND passengers.passport_number = people.passport_number
AND flights.id = 36;

--check if any passenger's license plate was at the bakery
SELECT license_plate FROM passengers, flights, people
WHERE passengers.flight_id = flights.id
AND passengers.passport_number = people.passport_number
AND flights.id = 36

INTERSECT

SELECT license_plate FROM bakery_security_logs
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28;

--check names of license plate
SELECT * FROM bakery_security_logs, people
WHERE bakery_security_logs.license_plate = people.license_plate
AND year = 2021
AND month = 7
AND day = 28
AND (bakery_security_logs.license_plate = "ONNTHK55"
OR bakery_security_logs.license_plate = "1106N58"
OR bakery_security_logs.license_plate = "4328GD8"
OR bakery_security_logs.license_plate = "94KL13X"
OR bakery_security_logs.license_plate = "G412CB7");

--check if any called during the day

SELECT name FROM phone_calls, people
WHERE phone_calls.caller = people.phone_number
OR phone_calls.receiver = people.phone_number

INTERSECT

SELECT name FROM bakery_security_logs, people
WHERE bakery_security_logs.license_plate = people.license_plate
AND year = 2021
AND month = 7
AND day = 28
AND (bakery_security_logs.license_plate = "ONNTHK55"
OR bakery_security_logs.license_plate = "1106N58"
OR bakery_security_logs.license_plate = "4328GD8"
OR bakery_security_logs.license_plate = "94KL13X"
OR bakery_security_logs.license_plate = "G412CB7");

--find the call details
SELECT * FROM phone_calls, people
WHERE phone_calls.caller = people.phone_number
OR phone_calls.receiver = people.phone_number)
AND (people.name = "Bruce"
OR people.name = "Luca"
OR people.name = "Sofia"
OR people.name = "Taylor")
AND year = 2021
AND month = 7
AND day = 28;

--find names of recievers
SELECT DISTINCT caller, receiver, name, duration FROM phone_calls, people
WHERE (phone_calls.caller = people.phone_number
OR phone_calls.receiver = people.phone_number)
AND ((phone_calls.caller = "(367) 555-5533" OR phone_calls.receiver = "(367) 555-5533")--bruce
OR (phone_calls.caller = "(389) 555-5198" OR phone_calls.receiver = "(389) 555-5198")--luca
OR (phone_calls.caller = "(130) 555-0289" OR phone_calls.receiver = "(130) 555-0289")--sofia
OR (phone_calls.caller = "(286) 555-6063" OR phone_calls.receiver = "(286) 555-6063"))--taylor
AND year = 2021
AND month = 7
AND day = 28
ORDER BY duration;

--+----------------+----------------+---------+----------+
--|     caller     |    receiver    |  name   | duration |
--+----------------+----------------+---------+----------+
--| (286) 555-6063 | (676) 555-6554 | James   | 43       |<--james and taylor
--| (286) 555-6063 | (676) 555-6554 | Taylor  | 43       |
--| (367) 555-5533 | (375) 555-8161 | Bruce   | 45       |<--bruce and robin
--| (367) 555-5533 | (375) 555-8161 | Robin   | 45       |
--| (130) 555-0289 | (996) 555-8899 | Sofia   | 51       |<--sofia and jack
--| (130) 555-0289 | (996) 555-8899 | Jack    | 51       |
--| (609) 555-5876 | (389) 555-5198 | Luca    | 60       |
--| (609) 555-5876 | (389) 555-5198 | Kathryn | 60       |
--| (367) 555-5533 | (704) 555-5790 | Carl    | 75       |
--| (367) 555-5533 | (704) 555-5790 | Bruce   | 75       |
--| (367) 555-5533 | (344) 555-9601 | Bruce   | 120      |
--| (367) 555-5533 | (344) 555-9601 | Deborah | 120      |
--| (286) 555-6063 | (310) 555-8568 | Taylor  | 235      |
--| (286) 555-6063 | (310) 555-8568 | Angela  | 235      |
--| (367) 555-5533 | (022) 555-4052 | Gregory | 241      |
--| (367) 555-5533 | (022) 555-4052 | Bruce   | 241      |
--| (544) 555-8087 | (389) 555-5198 | Walter  | 595      |
--| (544) 555-8087 | (389) 555-5198 | Luca    | 595      |
--+----------------+----------------+---------+----------+

--check if they were at atm
SELECT * FROM atm_transactions, bank_accounts, people
WHERE atm_transactions.account_number = bank_accounts.account_number
AND bank_accounts.person_id = people.id
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND (people.name = "Taylor"
OR people.name = "Bruce"
OR people.name = "Luca"
OR people.name = "Sofia");

--+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+--------+----------------+-----------------+---------------+
--| id  | account_number | year | month | day |  atm_location  | transaction_type | amount | account_number | person_id | creation_year |   id   |  name  |  phone_number  | passport_number | license_plate |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+--------+----------------+-----------------+---------------+
--| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     | 49610011       | 686048    | 2010          | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     | 28500762       | 467400    | 2014          | 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     | 76054385       | 449774    | 2015          | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
--+-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+--------+----------------+-----------------+---------------+
--check license plates
SELECT * FROM bakery_security_logs, people
WHERE bakery_security_logs.license_plate = people.license_plate
AND (people.name = "Bruce"
OR people.name = "Taylor");

--bruce and robin are the theives