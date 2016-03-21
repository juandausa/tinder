CREATE TABLE IF NOT EXISTS users
(
    id      	serial PRIMARY KEY,
    data		json
);

GRANT USAGE, SELECT ON SEQUENCE users_id_seq TO root;
GRANT ALL PRIVILEGES ON users TO root;