#include <stdio.h>
#include "cgen.h"
#include "ext/io.h"
#include <string.h>

#define DELIM "*#*"

typedef struct song_s{
    char *name;
    char *path;
} *song_t;

song_t song_create(){
    song_t song = malloc(sizeof(struct song_s));
    song->name = song->path = NULL;
    return song;
}

void gtype_free_song(gtype value){
    song_t song = (song_t)(value.v);
    free(song->name);
    free(song->path);
    free(song);
}
#define parse_attrib(_line, sign, attrib)\
    do { \
        char *tmp; \
        if ((tmp = strstr(_line, sign)) == NULL) { \
            return NULL; \
        } \
        attrib = _line; \
        *tmp = 0; \
        _line = tmp + strlen(sign); \
    } while (0)

song_t parse_song(char *line){
    char *name, *path;
    parse_attrib(line, DELIM, name);
    path = line;
    song_t song = song_create();
    song->name = strdup(name);
    song->path = strdup(path);
    return song;
}
#undef parse_attrib

gsl_t parse_song_list(const char *fname){
    FILE *inp = fopen(fname, "r");
    if (!inp){
        printf("Không thể mở tệp %s\n", fname);
        return NULL;
    }
    gsl_t song_list = gsl_create(gtype_free_song);
    char *line = NULL;
    song_t tmp;
    while (cgetline(&line, 0, inp)) {
        remove_tail_lf(line);
        if((tmp = parse_song(line))){
            gsl_push_back(song_list, gtype_v(tmp));
        }
    }
    free(line);
    fclose(inp);
    return song_list;
}
void gtype_print_song(gsl_t song_list){
    printf("Danh sách bài hát là:\n");
    gsl_traverse(cur, song_list){
        song_t tmp = (song_t) cur->v;
        printf("%s\n", tmp->name);
    }
}

char *view_path(char *find_name, gsl_t song_list){
    char *path = NULL;
    gsl_traverse(cur, song_list){
        song_t tmp = (song_t) cur->v;
        if (strstr(tmp->name, find_name)) {
            return tmp->path;
        }
    }
    return path;
}

int main(){
    char *fname = "songs.txt";
    gsl_t song_list = parse_song_list(fname);
    gtype_print_song(song_list);
    printf("Nhập tên muốn tìm: ");
    char *find_name = NULL;
    cgetline(&find_name, 0, stdin);
    remove_tail_lf(find_name);
    char *path;
    if ( (path = view_path(find_name, song_list))) {
        printf("Đường dẫn: %s\n", path);
    }else printf("Không tồn tại\n");
    free(find_name);
    gsl_free(song_list);
    return 0;
}

