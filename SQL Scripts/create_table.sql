CREATE TABLE IF NOT EXISTS users
(
    id      	serial PRIMARY KEY,
    data		json
);

GRANT USAGE, SELECT ON SEQUENCE users_id_seq TO postgres;
GRANT ALL PRIVILEGES ON users TO postgres;

CREATE TABLE IF NOT EXISTS interests
(
    id      	serial PRIMARY KEY,
    data		json
);

GRANT USAGE, SELECT ON SEQUENCE interests_id_seq TO postgres;
GRANT ALL PRIVILEGES ON interests TO postgres;