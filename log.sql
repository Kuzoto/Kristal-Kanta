-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get the crime scene description from the theft on July 28, 2020 on Chamberlein Street
SELECT description FROM crime_scene_reports WHERE year = 2020 and month = 7 and day = 28 and street = "Chamberlin Street";
-- Get the names and transcripts of the witnesses interviewed that mentioned the courthouse
SELECT name, transcript FROM interviews WHERE year = 2020 and month = 7 and day = 28 and transcript LIKE "%courthouse%";
-- Get the license plate of cars that left the parking lot
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute BETWEEN 15 and 25 and activity = "exit";
-- Get the account number and amount for atm transactions that occured that day at Fifer Street
SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street";
-- Get people_id based on account_number
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street");
-- Get earliest flight_id and its destination from Fiftyville
SELECT id, destination_airport_id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1;
-- Get the accomplice and thief phone numbers
SELECT receiver, caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60;
-- Get the passport number of the thief and his accomplice
SELECT name, passport_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1));
-- Get the name of the thief
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street")) 
and phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration <= 60) 
and passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1))
and license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and activity = "exit" and minute BETWEEN 15 and 25);
-- Get Accomplice's phone number
SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street")) 
and phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration <= 60) 
and passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1))
and license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and activity = "exit" and minute BETWEEN 15 and 25)) and year = 2020 and month = 7 and day = 28 and duration <= 60;
-- Get Accomplice's name
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street")) 
and phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration <= 60) 
and passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1))
and license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and activity = "exit" and minute BETWEEN 15 and 25)) and year = 2020 and month = 7 and day = 28 and duration <= 60);
-- Get thief destination
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour ASC LIMIT 1);