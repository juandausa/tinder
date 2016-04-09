CREATE TABLE IF NOT EXISTS users
(
    id      	serial PRIMARY KEY,
    data		json
);

CREATE TABLE IF NOT EXISTS interests
(
    id      	serial PRIMARY KEY,
    data		json
);
