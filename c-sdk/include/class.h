#define MAX_STRING_SIZE 40

typedef struct
{
    char* key;
    char* value;
} payload_struct;
int api_access(char *, char *);
int _send(char*, char[][MAX_STRING_SIZE], payload_struct*);
int _post(char [][MAX_STRING_SIZE], payload_struct*);
