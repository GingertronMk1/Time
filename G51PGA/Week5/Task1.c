#include <stdio.h>
#include <stdlib.h>

struct play {
    int user_id;
    int artist_id;
    int playcount;
    struct play *next;
};

void print_play(struct play *p);

struct play *create_play(int user_id, int artist_id, int count);

void free_play(struct play *p);



int main(int argc, char *argv[]){
    struct play *test_play = NULL;
    print_play(test_play);
    test_play = create_play(1,2,3);
    print_play(test_play);
    free_play(test_play);
};



void print_play(struct play *p){
    if(p == NULL){
        printf("NULL\n");
    } else {
        printf("User: %d, Artist: %d, Count: %d\n", p->user_id, p->artist_id, p->playcount);
    };
};

struct play *create_play(int user_id, int artist_id, int count) {
    struct play *a =
        (struct play *)malloc(sizeof(struct play));
    if( a != NULL ) {
        a->user_id = user_id;
        a->artist_id = artist_id;
        a->playcount = count; 
    }
    return a; 
}

void free_play(struct play *p){
    free(p);
};
