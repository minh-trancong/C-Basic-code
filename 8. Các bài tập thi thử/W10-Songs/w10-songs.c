#include "cgen.h"
#include "ext/io.h"
#include "ctype.h"
#define DELIM "#*#"

typedef struct song_s{
    char *name;
    char *singer;
    char *musician;
    int year;
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
    song_t song = song_create();
    char *name, *singer, *musician;
    parse_attrib(line, DELIM, name);
    parse_attrib(line, DELIM, singer);
    parse_attrib(line, DELIM, musician);
    int year;
    sscanf(line, "%d", &year);
    song->name = strdup(name);
    song->singer = strdup(singer);
    song->musician = strdup(musician);
    song->year = year;
    return song;
}

gvec_t parse_songs_list(const char* fname){
    FILE *inp = fopen(fname, "r");
    if (!inp){
        printf("Không thể mở tệp %s\n", fname);
        return NULL;
    }
    gvec_t songs_list = gvec_create(10, gtype_free_song);
    char *line = NULL;
    song_t tmp;
    while (cgetline(&line, 0, inp)) {
        if ((tmp = parse_song(line))) {
            gvec_append(songs_list, gtype_v(tmp));
        }
    }
    free(line);
    fclose(inp);
    return songs_list;
}
int estimate_utf8(const char *s) {
    int cc = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) {
            ++cc;
        }
        ++s;
    }
    return cc;
}
void pprint_utf8(const char *s, int width) {
    int align = width - estimate_utf8(s);
    if (align < 0) {
        align = 0;
    }
    printf("%s%*s", s, align, " ");
}

enum {
    SONG_NULL,
    SONG_NAME,//1
    SONG_SINGER,//2
    SONG_MUSICIAN,//3
    SONG_YEAR,//4
    SONG_END,
};
const char *field_names[] = {"","Bài hát", "Ca sĩ", "Nhạc sĩ", "Năm sáng tác",""};
const int field_width[] = {0,25, 20, 30, 5,0};

void gtype_print_song_list(gvec_t songs_list){
    printf("STT ");
    for (int i = SONG_NAME; i<= SONG_YEAR; i++) {
        pprint_utf8(field_names[i], field_width[i]);
    }
    printf("\n");
    int i=1;
    gvec_traverse(cur, songs_list){
        song_t tmp = (song_t)(cur->v);
        printf("%*d",-4,i);
        pprint_utf8(tmp->name, field_width[SONG_NAME]);
        pprint_utf8(tmp->singer, field_width[SONG_SINGER]);
        pprint_utf8(tmp->musician, field_width[SONG_MUSICIAN]);
        printf("%*d", -field_width[SONG_YEAR], tmp->year);
        printf("\n");
        i++;
    }
}

#define to_song(p) ((song_t)(((const gtype*)p)->v))
static int song_cmp_name(const void *a, const void *b){
    return strcmp(to_song(a)->name, to_song(b)->name);
}

static int song_cmp_singer(const void *a, const void *b){
    return strcmp(to_song(a)->singer, to_song(b)->singer);
}

static int song_cmp_musician(const void*a, const void *b){
    return strcmp(to_song(a)->musician, to_song(b)->musician);
}

static int song_cmp_year(const void *a, const void *b){
    return to_song(a)->year - to_song(b)->year;
}

int (*song_cmp[])(const void *, const void *) = { NULL, song_cmp_name, song_cmp_singer, song_cmp_musician, song_cmp_year};

int field_choice(){
    printf("1. Tên bài hát\n"
           "2. Ca sỹ\n"
           "3. Nhạc sĩ\n"
           "4. Năm sáng tác\n"
           "Lựa chọn của bạn [1-4]: ");
    int c;
    do{
        scanf("%d",&c);
        clear_stdin();
        if(c<1 || c>4){
            printf("Không hợp lệ, mời nhập lại\n");
        }
    } while (c<1 || c>4);
    return c;
}

void song_view(gvec_t songs_list){
    int c = field_choice();
    gvec_qsort(songs_list, song_cmp[c]);
    gtype_print_song_list(songs_list);
}

gvec_t song_filter(gvec_t songs_list){
    printf("Lọc theo thuộc tính:\n");
    int c = field_choice();
    char *search_phrase = NULL;
    int year = 0;
    switch (c) {
        case SONG_NAME:
        case SONG_SINGER:
        case SONG_MUSICIAN:
            printf("Nhập chuỗi cần tìm: ");
            remove_tail_lf(cgetline(&search_phrase, 0, stdin));
            break;
        case SONG_YEAR:
            printf("Nhập năm: ");
            scanf("%d", &year);
            clear_stdin();
            break;
        default:
            break;
    }
    gvec_qsort(songs_list, song_cmp[c]);
    gvec_t song_filtered = gvec_create(10, NULL);
    gvec_traverse(cur, songs_list){
        song_t song = (song_t)(cur->v);
        int ok = 0; //FALSE
        switch (c) {
            case SONG_NAME:
                ok = (strstr(song->name, search_phrase) != NULL);
                break;
            case SONG_SINGER:
                ok = (strstr(song->singer, search_phrase) != NULL);
                break;
            case SONG_MUSICIAN:
                ok = (strstr(song->musician, search_phrase) != NULL);
                break;
            case SONG_YEAR:
                ok = (song->year >= year);
            default:
                break;
        }
        if (ok) {
            gvec_append(song_filtered, gtype_v(cur));//song_filter chứa con trỏ đến cur của songs_list (cur trỏ đến song)
        }
    }
    free(search_phrase);
    return song_filtered;
}
gvec_t gtype_to_song_list(gvec_t gtype_list){
    gvec_t song_filtered_song = gvec_create(gvec_size(gtype_list), NULL);
    gvec_traverse(cur_gtype, gtype_list){
        gtype* cur = (gtype*)(cur_gtype->v);
        song_t tmp = (song_t)(cur->v);
        gvec_append(song_filtered_song, gtype_v(tmp));
    }
    return song_filtered_song;
}
void song_filter_view(gvec_t songs_list){
    gvec_t song_filtered_gtype = song_filter(songs_list);
    gvec_t song_filtered_song = gtype_to_song_list(song_filtered_gtype);
    gtype_print_song_list(song_filtered_song);
    gvec_free(song_filtered_gtype);
    gvec_free(song_filtered_song);
}

#define enter_song(msg, line)\
    printf(msg);\
    remove_tail_lf(cgetline(&(line), 0, stdin));

void song_add(gvec_t songs_list){
    song_t song = song_create();
    enter_song("Nhập tên bài hát: ", song->name);
    enter_song("Nhập tên ca sĩ: ", song->singer);
    enter_song("Nhập tên nhạc sĩ: ", song->musician);
    printf("Nhập năm sáng tác: ");
    scanf("%d",&(song->year));
    clear_stdin();
    gvec_append(songs_list, gtype_v(song));
}

int modify_file(const char *fname, gvec_t songs_list){
    FILE *out = fopen(fname, "w");
    if (!out){
        printf("Không thể mở tệp %s\n", fname);
        return 0;
    }
    gvec_traverse(cur, songs_list){
        song_t tmp = (song_t)(cur->v);
        fprintf(out, "%s%s%s%s%s%s%d\n",tmp->name,DELIM,tmp->singer,DELIM,tmp->musician,DELIM,tmp->year);
    }
    fclose(out);
    return 1;
}

void song_del(gvec_t songs_list){
    printf("XÓA BÀI HÁT\n");
    gvec_t gtype_filtered = song_filter(songs_list);
    gvec_t song_filtered = gtype_to_song_list(gtype_filtered);
    gtype_print_song_list(song_filtered);
    printf("Chọn bài hát muốn xóa [1,2,3...]: ");
    int del_num;
    scanf("%d",&del_num);
    clear_stdin();
    gtype del_song_g = gvec_elem(gtype_filtered, del_num - 1);
    gtype* tmp = del_song_g.v;
    song_t song = (song_t)(tmp->v); // trỏ đến cur (cur trỏ đến song)
    //đang ok, tí làm tiếp
    //Cần phân biệt lại con trỏ chỗ này nhé !!!!!!!!!!!!!!!!!
    long del_idx = gvec_elem_idx(songs_list, tmp);
    printf("Bạn chắc chắn muốn xóa bài ");
    printf("%d. %s?(y/n): ", del_num, song->name);
    char choice = 0;
    scanf("%c", &choice);
    clear_stdin();
    choice = tolower(choice);
    if (choice == 'y') {
        gvec_remove(songs_list, del_idx);
        printf("Xóa thành công.\n");
    } else printf("No -> Không thay đổi.\n");
    gvec_free(gtype_filtered);
    gvec_free(song_filtered);
}

int main(const int argc, const char* argv[]){
    if (argc != 2) {
        printf("Usage: ./prog songlist.txt");
        return 1;
    }
    gvec_t songs_list = parse_songs_list(argv[1]);
    for (; ;) {
        printf("-------\n");
        printf("1. Xem danh sách bài hát\n");
        printf("2. Lọc danh sách bài hát\n");
        printf("3. Thêm bài hát\n");
        printf("4. Xóa bài hát\n");
        printf("5. Thoát\n");
        printf("Lựa chọn của bạn là [1,2,3,4,5]: ");
        int choice;
        scanf("%d", &choice);
        clear_stdin();
        if (choice == 1) {
            song_view(songs_list);
        } else if (choice == 2) {
            song_filter_view(songs_list);
        } else if (choice == 3) {
            song_add(songs_list);
            modify_file(argv[1], songs_list);
        } else if (choice == 4) {
            song_del(songs_list);
            modify_file(argv[1], songs_list);
        } else if (choice == 5) {
            break;
        } else {
            printf("Lựa chọn không hợp lệ.\n");
        }
    }
    gvec_free(songs_list);
    return 0;
}


