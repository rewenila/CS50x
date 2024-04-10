-- Write a SQL query to determine the average rating of all movies released in 2012.
-- Your query should output a table with a single column and a single row (not counting the header) containing the average rating.

SELECT AVG(rating)
FROM ratings
WHERE movie_id IN
(
    SELECT id
    FROM movies
    WHERE year = 2012
);

-- SELECT AVG(ratings.rating)
-- FROM movies
-- JOIN ratings ON movies.id = ratings.movie_id
-- WHERE movies.year = 2012;
