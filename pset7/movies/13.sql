SELECT DISTINCT name FROM people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND NOT (people.name = "Kevin Bacon" AND people.birth = 1958)
AND stars.movie_id IN
(
    SELECT DISTINCT movie_id FROM people, stars, movies
    WHERE people.id = stars.person_id
    AND stars.movie_id = movies.id
    AND people.name = "Kevin Bacon"
    AND people.birth = 1958
)
ORDER BY name;