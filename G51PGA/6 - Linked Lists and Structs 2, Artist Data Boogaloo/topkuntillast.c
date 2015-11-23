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
    if(p != NULL){
        printf("User: %d\t Artist: %d\t Count: %d\n", p->user_id, p->artist_id, p->playcount); //prints all the information about a struct provided its not NULL
    } else {
        printf("NULL\n");
    };
}

struct play *create_play(int id, int artist_id, int playcount){
    struct play *a =
        (struct play *)malloc(sizeof(struct play)); //allocates the right amount of memory for a new struct
    if( a != NULL ) {
        a->user_id = id;            //sets user id
        a->artist_id = artist_id;   //sets artist id
        a->playcount = playcount;   //sets playcount
        a->next = NULL;             //sets next to NULL by default
    }
    return a;                       //returns our nice new struct
}

struct play *parse_play(char *line){    //honestly no idea what this is meant to do
    printf("Function play *parse_play is not yet defined.\n");
    return NULL;
}

void free_play(struct play *p){
    free(p);        //frees memory allocated to the struct p
}

struct play *add_play(struct play *head, struct play *newp){
    if(newp != NULL){           //provided newp's not nothing
        newp->next = head;      //set its next to be the current head
        return newp;
    } else {
        return head;
    }
}

void print_plays(struct play *p){
    while(p != NULL){
        print_play(p);          //prints everything about p
        p = p->next;            //steps to the next struct in the list until that struct is NULL
    };
}

struct play *read_plays(char *file_name){
    int user_id, artist_id, playcount;      //declaring variables for storage of these things
    FILE *playdata = fopen(file_name, "r"); //opening textfile read-only
    struct play *root = create_play(0,0,0);     //creating an empty struct to act as the head of the list
    struct play *walker = root;     //creating a struct that will walk through the list, creating each new struct as the loop loops
    if(playdata != NULL){                   //assuming the file isn't just NULL
        while(fscanf(playdata, "%d %d %d\n", &user_id, &artist_id, &playcount) != EOF){     //while not at end of file
            struct play *new = create_play(user_id, artist_id, playcount);      //creating new struct
            walker = add_play(new, walker);
            walker = new;           //walking through list
        }
        fclose(playdata);   //Close the file
        walker->next = NULL;      //so we have a NULL pointer at the end of the list for our other functions
        root = root->next;  //so the head doesn't just point to an all-zero struct
        return root;
    } else {
        fclose(playdata);
        printf("File error\n");
        exit(1);
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

struct play *filter_user(int user_id, struct play *head){       //creating a new linked list, so this will be largely similar to read_plays
    struct play *root = create_play(0,0,0);     //creating an empty struct to act as the head of the list
    struct play *walker = root;     //creating a struct that will walk through the list, creating each new struct as the loop loops
    if(head != NULL){                   //assuming the file isn't just NULL
        struct play *p = head;
        while(p != NULL){     //while not on a NULL pointer
            if(p->user_id == user_id){
                struct play *new = create_play(p->user_id, p->artist_id, p->playcount);      //creating new struct
                walker = add_play(new, walker); //adding new struct to new linked list
                walker = new;           //walking through list
            }
            p = p->next;
        }
        walker->next = NULL;      //so we have a NULL pointer at the end of the list for our other functions
        root = root->next;  //so the head doesn't just point to an all-zero struct
        return root;
    } else {
        printf("Error: Empty list provided for filtering\n");
        exit(1);
    };
}

void free_plays(struct play *p){
    while(p != NULL){
        free_play(p);
        p = p->next;
    }
}

void exit_usage() {
    printf("\nUSAGE: query_plays file command\n"
            "\n"
            "where command is one of\n"
            "\n"
            "    p <userid>  prints plays, optionally limited to user.\n"
            "    c <userid>  counts plays, optionally limited to user.\n\n");
    exit(1);
}

/**
 *
 *
 *
 *  HERE BEGINS THE CODE WRITTEN FOR CW-B2
 *
 *
 *
 */

#define PLAYCOUNT 0
#define ARTISTID 1

struct artist {                 //TASK 1)a)
    int artist_id;
    char artist_name[NAMELEN];
    int playcount;
    int alt_artist_id;
    struct artist *next;
};

struct artist *create_artist(int artist_id, char artist_name[NAMELEN], int playcount){
    struct artist *a = (struct artist *)malloc(sizeof(struct artist)); //allocates the right amount of memory for a new struct
    if( a != NULL ) {
        a->artist_id = artist_id;   //sets artist id
        strcpy(a->artist_name, artist_name);
        a->playcount = playcount;   //sets playcount
        a->next = NULL;             //sets next to NULL by default
    }
    return a;                       //returns our nice new struct
}

struct artist *read_artists(char *fname){       //TASK 1)b)
    int artist_id, playcount;      //declaring variables for storage of these things
    char artist_name[NAMELEN];
    FILE *playdata = fopen(fname, "r"); //opening textfile read-only
    struct artist *root = create_artist(0," ",0);     //creating an empty struct to act as the head of the list
    struct artist *walker = root;     //creating a struct that will walk through the list, creating each new struct as the loop loops
    if(playdata != NULL){                   //assuming the file isn't just NULL
        while(fscanf(playdata, "%d\t%65[^\t\n]\n", &artist_id, artist_name) != EOF){     //while not at end of file
            struct artist *new = create_artist(artist_id, artist_name, 0);      //creating new struct
            walker->next = new;
            walker = new;           //walking through list
        }
        fclose(playdata);   //Close the file
        walker->next = NULL;      //so we have a NULL pointer at the end of the list for our other functions
        root = root->next;  //so the head doesn't just point to an all-zero struct
        return root;
    } else {
        fclose(playdata);
        printf("File error\n");
        exit(1);
    };
}

void print_artist(struct artist *a){        //TASK 1)c)
    if(a != NULL){
        printf("%s (%d) [%d]\n", a->artist_name, a->artist_id, a->playcount);
    } else {
        printf("NULL\n");
    }
}

void print_artists(struct artist *a){       //TASK 1)d)
    while(a != NULL){
        print_artist(a);
        a = a->next;
    }
}

void free_artists(struct artist *a){        //TASK 1)e)
    while(a != NULL){
        free(a);
        a = a->next;
    }
}

struct play *find_middle_play(struct play *head){
    struct play *slow = head;
    struct play *fast = head;
    while(fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    };
    return slow;
}

struct play *merge_plays(struct play *x, struct play *y){
    struct play *tmp = NULL;
    struct play *head = NULL;
    struct play *curr = NULL;
    if(x == NULL){
        return y;
    } else if(y == NULL){
        return x;
    };
    while(x != NULL && y!= NULL){
        if(x->artist_id > y->artist_id){
            tmp = x;
            x = y;
            y = tmp;
        }
        if(head == NULL){
            head = x;
            curr = x;
        } else {
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if(x == NULL){
        curr->next = y;
    } else {
        curr->next = x;
    }
    return head;
}

struct play *sort_plays(struct play *head){         //TASK 2)a)
    struct play *m = NULL;
    struct play *x = NULL;
    struct play *y = NULL;
    if(head == NULL || head->next == NULL){
        return head;
    }
    x = head;
    m = find_middle_play(head);
    y = m->next;
    m->next = NULL;
    return merge_plays(sort_plays(x), sort_plays(y));
}

struct artist *find_middle_artist(struct artist *head){
    struct artist *slow = head;
    struct artist *fast = head;
    while(fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    };
    return slow;
}

struct artist *merge_artists(struct artist *x, struct artist *y, int criterion){
    struct artist *tmp = NULL;
    struct artist *head = NULL;
    struct artist *curr = NULL;
    if(x == NULL){
        return y;
    } else if(y == NULL){
        return x;
    };
    while(x != NULL && y!= NULL){
        if(criterion == PLAYCOUNT){             //Sort By Playcount
            if(x->playcount < y->playcount){
                tmp = x;
                x = y;
                y = tmp;
            }
        } else if(criterion == ARTISTID){
            if(x->artist_id > y->artist_id){
                tmp = x;
                x = y;
                y = tmp;
            }
        }
        if(head == NULL){
            head = x;
            curr = x;
        } else {
            curr->next = x;
            curr = curr->next;
        }
        x = x->next;
    }
    if(x == NULL){
        curr->next = y;
    } else {
        curr->next = x;
    }
    return head;
}

struct artist *sort_artists(struct artist *artists, int criterion){     //TASK 2)b)
    if(criterion != PLAYCOUNT && criterion != ARTISTID){
        printf("Error: invalid comparison criteria\n");
        return artists;
    };
    struct artist *m = NULL;
    struct artist *x = NULL;
    struct artist *y = NULL;
    if(artists == NULL || artists->next == NULL){
        return artists;
    }
    x = artists;
    m = find_middle_artist(artists);
    y = m->next;
    m->next = NULL;
    return merge_artists(sort_artists(x, criterion), sort_artists(y, criterion), criterion);
}

struct artist *update_counts(struct artist *a, struct play *p){         //TASK 2)c)
    if(a != NULL && p != NULL){
        struct artist *sorted_artists = sort_artists(a, ARTISTID);
        struct play *sorted_plays = sort_plays(p);
        struct artist *head = create_artist(0," ",0);
        head->next = sorted_artists;
        while(sorted_artists != NULL && sorted_plays != NULL){
        } if(sorted_artists->artist_id > sorted_plays->artist_id){
            sorted_plays = sorted_plays->next;
        } else if(sorted_artists->artist_id < sorted_plays->artist_id){
            sorted_artists = sorted_artists->next;
        } else {
            sorted_artists->playcount = sorted_artists->playcount + sorted_plays->playcount;
            sorted_plays = sorted_plays->next;
        }
    };
    head = head->next;
    return head;
} else {
    return NULL;
}
}

struct artist *shorten_list(struct artist *list, int howmany){
    struct artist *head = create_artist(0," ",0);
    head->next = list;
    for(int i = 1; i < howmany; i++){
        list = list->next;
    }
    list->next = NULL;
    return head->next;
}

void test_sorting_and_printing(){
    struct artist *test_artists = read_artists("test_artists.txt");
    struct play *test_plays = read_plays("test_plays.txt");
    struct artist *id_artists = sort_artists(test_artists,ARTISTID);
    struct play *plays_by_count = sort_plays(test_plays);
    printf("Artists By Artist ID\n");
    print_artists(id_artists);
    printf("\nPlays By Artist ID\n");
    print_plays(plays_by_count);
    printf("\n");
    free_artists(id_artists);
    free_plays(plays_by_count);
}

void test_updating_counts(){
    struct artist *test_artists = read_artists("test_artists.txt");
    struct play *test_plays = read_plays("test_plays.txt");
    struct artist *test_updated = update_counts(test_artists, test_plays);
    print_artists(test_updated);
    free_artists(test_updated);
}

void update_counts_actual(){
    struct artist *test_artists = read_artists("artist_data.txt");
    struct play *test_plays = read_plays("user_artist_data.txt");
    struct artist *test_updated = update_counts(test_artists, test_plays);
    print_artists(sort_artists(test_updated, PLAYCOUNT));
    free_artists(test_updated);
}

int main(int argc, char **argv){
    //test_sorting_and_printing();
    //test_updating_counts();
    //update_counts_actual();
}
