#include "cgen.h"
#include "ext/io.h"

typedef struct song_s{
    char *name;
    char *singer;
    char *musician;
    char *year;
} *song_t;

song_t song_create(){
    song_t song = malloc(sizeof(struct song_s));
    song->name = song->singer = song->musician = NULL;
    song->year = 0;
    return song;
}

void gtype_free_song(gtype value){
    song_t song = (song_t)(value.v);
    free(song->name);
    free(song->singer);
    free(song->musician);
    free(song);
}

#define parse_attrib(line, sign, attrib)\
    do { \
        char *tmp; \
        if ((tmp = strstr(line, sign)) == NULL) { \
            return NULL; \
        } \
        attrib = line; \
        *tmp = 0; \
        line = tmp + strlen(sign); \
    } while (0)

song_t parse_song(char *line){
    
}

int main(const int agrc, const char* argv[]){

    return 0;
}


