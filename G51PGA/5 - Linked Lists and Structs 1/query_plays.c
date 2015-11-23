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

void test_task1() {
    printf("Test of Task 1:\n");
    struct play *test_play = NULL;
    print_play(test_play);
    test_play = create_play(1,2,3);
    print_play(test_play);
    free_play(test_play);
}

void test_task2() {
    printf("Test of Task 2:\n");
    struct play *a = create_play(1,2,3);
    struct play *b = create_play(4,5,6);
    a = add_play(NULL, a);
    a = add_play(a, b);
    print_plays(a);
    printf("There are %d plays in a.\n", count_plays(a));
}

int main(int argc, char **argv){
    /*if(argc == 1){          //if you've only been given the instruction, print the tests for 1 and 2
        printf("\n");
        test_task1();
        printf("\n");
        test_task2();
        printf("\n");
    };*/
    if(argc > 2){                //If we've actually been given arguments, then do the printing/counting
        char playdatafile[80];          //Assigning variables for arguments
        strcpy(playdatafile, argv[1]);
        char countorplay = argv[2][0];
        struct play *readplays = read_plays(playdatafile);       //Pronounced 'red plays'
        if(argc == 3){   //if you've been given a filename and a letter, count or print from the file
            if(countorplay == 'c'){
                printf("Total plays: %d\n", count_plays(readplays));
            } else if(countorplay == 'p'){
                print_plays(readplays);
            }
            free_plays(readplays);



        } else if(argc == 4){   //if you've been given a filename, a letter, and c or p, count/print a filtered list
            int user_id_optional = atoi(argv[3]);       //C apparently takes all arguments as strings, so we've to convert them with atoi()
            struct play *filteredplays = filter_user(user_id_optional, readplays);
            if(countorplay == 'c'){
                printf("Plays for that user: %d\n", count_plays(filteredplays));
            } else if(countorplay == 'p'){
                print_plays(filteredplays);
            }
            free_plays(filteredplays);
        }
    } else {
        exit_usage();
    }
}
