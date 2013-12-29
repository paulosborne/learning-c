#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.");
}
/**
 * Database_open
 *
 * @struct Connection
 * @param {char} *filename
 * @param {char} mode
 */
struct Connection *Database_open(const char *filename, char mode)
{
    // malloc - returns either a pointer to the beginning of newly allocated
    // memory or NULL if an error occured.
    struct Connection *conn = malloc(sizeof(struct Connection));
    // if conn == NULL
    if(!conn) die("Memory error");
    // request a piece of memory the size of the database struct and then
    // reference it to conn->db
    conn->db = malloc(sizeof(struct Database));
    // again, if NULL is returned by malloc handle the error
    if(!conn->db) die("Memory error");

    if(mode == 'c') {
        // create a new file ready for writing, erases existing files.
        conn->file = fopen(filename, "w");
    } else {
        // Open a fie for update both reading and writing, file must exist.
        conn->file = fopen(filename, "r+");
        // fopen returns a file pointer or NULL if an error occured.
        if(conn->file) {
            Database_load(conn);
        }
    }
    // if there was a problem opening the file, handle the error here.
    if (!conn->file) die("Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) {
         // fclose accepts a pointer to the FILE stream to be closed. Returns
         // 0 if the file was successfully closed or EOF if not.
        if(conn->file) fclose(conn->file);
        // deallocate memory from conn->db
        if(conn->db) free(conn->db);
        // deallocate memory from conn
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    // sets the file position to the beginning of the file stream.
    rewind(conn->file);

    // writes data from conn->db to conn->file, returns the total number of
    // elements successfully written as a size_t object which is an integral
    // data type. If this number differs from nmemb (in this case 1) it will
    // show an error.
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    // handle any errors encountered when writing database.
    if(rc != 1) die("Failed to write database.");

    // flushes the output buffer of a stream. Returns 0 on success, EOF on error
    rc = fflush(conn->file);
    // handle errors thrown when flushing output buffer.
    if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    // create a pointer to the address of rows[id]
    struct Address *addr = &conn->db->rows[id];

    addr->set = 1;
    // WARNING: bug
    // strncpy - copies up to 512 characters from addr->name to name
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demo bug
    if(!res) die("Name copy failed");

    // copies upto 512 characters from addr->name to name
    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    // create a pointer to the address of rows[id]
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
    // create a pointer to the first argument (dbfile)
    char *filename = argv[1];
    // assign the first character value to action
    char action = argv[2][0];
    // create a new Connection passing in filename and action
    struct Connection *conn = Database_open(filename, action);

    int id = 0;
    // atoi converts a string to an integer
    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;
        
        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;

    
}
