SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE name = "Chadwick Boseman" ORDER BY (SELECT rating FROM ratings WHERE movies.id = ratings.movie_id) DESC LIMIT 5;