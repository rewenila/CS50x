-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find all crimes for the given date and place
-- SELECT *
-- FROM crime_scene_reports
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28
-- AND street = 'Humphrey Street';

-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | 297 | 2023 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- crime_scene_report.id = 295
-- occurred at 10:15am
-- interviews with three witnesses that mentioned the bakery
-- littering at the same street at 16:36

-- Find interviews of witnesses
-- SELECT id, name, transcript
-- FROM interviews
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28;

-- 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car
--                 in the bakery parking lot and drive away. If you have security footage from
--                 the bakery parking lot, you might want to look for cars that left the parking
--                 lot in that time frame.
-- 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this
--                 morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett
--                 Street and saw the thief there withdrawing some money.
-- 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them
--                 for less than a minute. In the call, I heard the thief say that they were
--                 planning to take the earliest flight out of Fiftyville tomorrow. The thief
--                 then asked the person on the other end of the phone to purchase the flight
--                 ticket.

-- thief car left bakery parking lot within 10 mins after theft (before 10:25am)
-- withdrew money from atm earlier
-- phone call within 10 mins after theft
-- wanted to buy earliest flight next day (29 July 2023)

-- Find info on bakery security logs
-- SELECT id, minute, activity, license_plate
-- FROM bakery_security_logs
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28
-- AND hour = 10
-- AND minute >= 15
-- AND minute <= 25;

-- +-----+--------+----------+---------------+
-- | id  | minute | activity | license_plate |
-- +-----+--------+----------+---------------+
-- | 260 | 16     | exit     | 5P2BI95       | almost impossible
-- | 261 | 18     | exit     | 94KL13X       | low probability
-- | 262 | 18     | exit     | 6P58WS2       | low probability
-- | 263 | 19     | exit     | 4328GD8       |
-- | 264 | 20     | exit     | G412CB7       |
-- | 265 | 21     | exit     | L93JTIZ       |
-- | 266 | 23     | exit     | 322W7JE       |
-- | 267 | 23     | exit     | 0NTHK55       |

-- Find owners of licence plates above
-- SELECT *
-- FROM people
-- WHERE license_plate IN
-- (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2023
--           AND month = 7
--           AND day = 28
--           AND hour = 10
--           AND minute >= 15
--           AND minute <= 25
-- );

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- Find phone calls that occured on the day of the theft and had less than 1 min duration
-- SELECT id, caller, receiver, duration
-- FROM phone_calls
-- WHERE year = 2023
--       AND month = 7
--       AND day = 28
--       AND duration <= 60;

-- +-----+----------------+----------------+----------+
-- | id  |     caller     |    receiver    | duration |
-- +-----+----------------+----------------+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 45       |
-- | 234 | (609) 555-5876 | (389) 555-5198 | 60       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 54       |
-- +-----+----------------+----------------+----------+

-- Find owners of matching licence plates that made <= 60s calls that day
-- SELECT *
-- FROM people
-- WHERE license_plate IN
-- (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND hour = 10
--     AND minute >= 15
--     AND minute <= 25
-- )
-- AND phone_number IN
-- (
--     SELECT caller
--     FROM phone_calls
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND duration <= 60
-- );

-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+--------+----------------+-----------------+---------------+

-- Find withdrawal atm transactions for that day and location
-- SELECT id, account_number, amount
-- FROM atm_transactions
-- WHERE year = 2023
-- AND month = 7
-- AND day = 28
-- AND transaction_type = 'withdraw'
-- AND atm_location = 'Leggett Street';

-- +-----+----------------+--------+
-- | id  | account_number | amount |
-- +-----+----------------+--------+
-- | 246 | 28500762       | 48     |
-- | 264 | 28296815       | 20     |
-- | 266 | 76054385       | 60     |
-- | 267 | 49610011       | 50     |
-- | 269 | 16153065       | 80     |
-- | 288 | 25506511       | 20     |
-- | 313 | 81061156       | 30     |
-- | 336 | 26013199       | 35     |
-- +-----+----------------+--------+

-- Find the ids of the people that made the transaction
-- SELECT person_id, creation_year
-- FROM bank_accounts
-- WHERE account_number IN
-- (
--     SELECT account_number
--     FROM atm_transactions
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND transaction_type = 'withdraw'
--     AND atm_location = 'Leggett Street'
-- );

-- +-----------+---------------+
-- | person_id | creation_year |
-- +-----------+---------------+
-- | 686048    | 2010          |
-- | 514354    | 2012          |
-- | 458378    | 2012          |
-- | 395717    | 2014          |
-- | 396669    | 2014          |
-- | 467400    | 2014          |
-- | 449774    | 2015          |
-- | 438727    | 2018          |
-- +-----------+---------------+

-- Find name of the people that made the transactions
-- SELECT *
-- FROM people
-- WHERE id IN
-- (
--     SELECT person_id
--     FROM bank_accounts
--     WHERE account_number IN
--     (
--         SELECT account_number
--         FROM atm_transactions
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND transaction_type = 'withdraw'
--         AND atm_location = 'Leggett Street'
--     )
-- );

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+

-- Find people that left the bakery, made phone call and withdrew money
-- SELECT *
-- FROM people
-- WHERE id IN
-- (
--     SELECT person_id
--     FROM bank_accounts
--     WHERE account_number IN
--     (
--         SELECT account_number
--         FROM atm_transactions
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND transaction_type = 'withdraw'
--         AND atm_location = 'Leggett Street'
--     )
-- )
-- AND license_plate IN
-- (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND hour = 10
--     AND minute >= 15
--     AND minute <= 25
-- )
-- AND phone_number IN
-- (
--     SELECT caller
--     FROM phone_calls
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND duration <= 60
-- );

-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- Find earliest flight for the next day of the theft
-- SELECT *
-- FROM flights
-- WHERE year = 2023
-- AND month = 7
-- AND day = 29
-- AND origin_airport_id IN
-- (
--     SELECT id
--     FROM airports
--     WHERE city = 'Fiftyville'
-- )
-- ORDER BY hour
-- LIMIT 1;

-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- Find passengers of the flight
-- SELECT passport_number, seat
-- FROM passengers
-- WHERE flight_id IN
-- (
--     SELECT id
--     FROM flights
--     WHERE year = 2023
--     AND month = 7
--     AND day = 29
--     AND origin_airport_id IN
--     (
--         SELECT id
--         FROM airports
--         WHERE city = 'Fiftyville'
--     )
--     ORDER BY hour
--     LIMIT 1
-- );

-- +-----------------+------+
-- | passport_number | seat |
-- +-----------------+------+
-- | 7214083635      | 2A   |
-- | 1695452385      | 3B   |
-- | 5773159633      | 4A   |
-- | 1540955065      | 5C   |
-- | 8294398571      | 6C   |
-- | 1988161715      | 6D   |
-- | 9878712108      | 7A   |
-- | 8496433585      | 7B   |
-- +-----------------+------+

-- Find people that left the bakery, made phone call, withdrew money and
-- were in the earliest flight next day
-- SELECT *
-- FROM people
-- WHERE id IN
-- (
--     SELECT person_id
--     FROM bank_accounts
--     WHERE account_number IN
--     (
--         SELECT account_number
--         FROM atm_transactions
--         WHERE year = 2023
--         AND month = 7
--         AND day = 28
--         AND transaction_type = 'withdraw'
--         AND atm_location = 'Leggett Street'
--     )
-- )
-- AND license_plate IN
-- (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND hour = 10
--     AND minute >= 15
--     AND minute <= 25
-- )
-- AND phone_number IN
-- (
--     SELECT caller
--     FROM phone_calls
--     WHERE year = 2023
--     AND month = 7
--     AND day = 28
--     AND duration <= 60
-- )
-- AND passport_NUMBER IN
-- (
--     SELECT passport_number
--     FROM passengers
--     WHERE flight_id IN
--     (
--         SELECT id
--         FROM flights
--         WHERE year = 2023
--         AND month = 7
--         AND day = 29
--         AND origin_airport_id IN
--         (
--             SELECT id
--             FROM airports
--             WHERE city = 'Fiftyville'
--         )
--         ORDER BY hour
--         LIMIT 1
--     )
-- );

-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- Find city where the thief went
-- SELECT *
-- FROM airports
-- WHERE id IN
-- (
--     SELECT destination_airport_id
--     FROM flights
--     WHERE year = 2023
--     AND month = 7
--     AND day = 29
--     AND origin_airport_id IN
--     (
--         SELECT id
--         FROM airports
--         WHERE city = 'Fiftyville'
--     )
--     ORDER BY hour
--     LIMIT 1
-- );

-- +----+--------------+-------------------+---------------+
-- | id | abbreviation |     full_name     |     city      |
-- +----+--------------+-------------------+---------------+
-- | 4  | LGA          | LaGuardia Airport | New York City |
-- +----+--------------+-------------------+---------------+

-- Find accomplice: person that received the call
SELECT *
FROM people
WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE caller IN
    (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND year = 2023
    AND month = 7
    AND day = 28
    AND duration <= 60
);


