#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define BUFSIZE 100

struct play{
    int user_id;
    int artist_id; 
    int playcount;
    struct play *next;
};

void print_play(struct play *p);
void print_plays(struct play *p);
struct play *create_play(int id, int artist_id, int playcount);
struct play *parse_play(char *line);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
struct play *filter_user(int user_id, struct play *head);
int count_plays(struct play *head);
void free_plays(struct play *p);
void free_play(struct play *p);

void print_play(struct play *p){
    if(p == NULL){
        printf("NULL\n");
    } else {
        printf("User: %d, Artist: %d, Count: %d\n", p->user_id, p->artist_id, p->playcount);
    };
}

struct play *create_play(int id, int artist_id, int playcount){
    struct play *a =
        (struct play *)malloc(sizeof(struct play));
    if( a != NULL ) {
        a->user_id = id;
        a->artist_id = artist_id;
        a->playcount = playcount;
        a->next = NULL;
    }
    return a; 
}

struct play *parse_play(char *line){  
    printf("Function play *parse_play is not yet defined.\n");
    return NULL;
}

void free_play(struct play *p){
    free(p);
}

struct play *add_play(struct play *head, struct play *newp){  
    if(newp != NULL){
        head->next = newp;
    };
    return head;
}

void print_plays(struct play *p){
    while(p != NULL){
        print_play(p);
        p = p->next;
    };
}


struct play *read_plays(char *file_name){
    int user_id, artist_id, playcount, r;
    FILE *fp = fopen(file_name, "r");
    if(fp != NULL){
        while(r != EOF){
            r = fscanf(fp, "%d %d %d\n", &user_id, &artist_id, &playcount);
            create_play(user_id, artist_id, playcount);
        } else {
            return NULL;
        };
    };
}

int count_plays(struct play *head){
    struct play *p = head;
    int plays = 0;
    while(p != NULL){
        plays = plays + p->playcount;
        p = p->next;
    };
    return plays;
}

struct play *filter_user(int user_id, struct play *head){
    printf("Function play *filter_user is not yet defined.\n");
    return NULL;
}

void free_plays(struct play *p){
    printf("Function free_plays is not yet defined.\n");
}


void exit_usage() {
    printf("USAGE: query_plays file command\n"
            "\n"
            "where command is one of\n"
            "\n"
            "   p <userid>  prints plays, optionally limited to user.\n"
            "   c <userid>  counts plays, optionally limited to user.\n");
    exit(1);
}

void test_task1() {
    printf("\nTest of Task 1:\n");
    struct play *test_play = NULL;
    print_play(test_play);
    test_play = create_play(1,2,3);
    print_play(test_play);
    free_play(test_play);
}

void test_task2() {
    printf("\nTest of Task 2:\n");
    struct play *a = create_play(1,2,3);
    struct play *b = create_play(4,5,6);
    a = add_play(a, NULL);
    a = add_play(a, b);
    print_plays(a);
    printf("There are %d plays in a.\n", count_plays(a));
}

int main(int argc, char **argv) {

    test_task1();
    test_task2();
    //exit_usage();
}
