import psycopg2

def query(message):
    try:
        conn = psycopg2.connect("dbname='users' user='postgres' host='localhost' password=''")
    except:
        print "I am unable to connect to the database"
        return None

    cur = conn.cursor()
    cur.execute(message)
    value = cur.fetchone()
    conn.commit()
    cur.close()
    conn.close()
    return int(value[0])


def delete_all(table):
    try:
        conn = psycopg2.connect("dbname='users' user='postgres' host='localhost' password=''")
    except:
        print "I am unable to connect to the database"
        return False
    cur = conn.cursor()
    cur.execute("delete from " + table +";")
    conn.commit()
    conn.close()
    return True

