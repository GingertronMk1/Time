
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "sort.h"
#include "ascrobbler.h"

int main(int argc, char **argv) {

  int pc = 0;
  int prev_id = -1;
  int artist_id = 0;
  int n = 0;
  int i = 0;
  int j = 0;
  
  struct list *curr = NULL;
  struct list *artists = NULL;
  struct list *plays = NULL;
  struct artist **index = NULL;

  struct play *p = NULL;
  struct artist *a = NULL;
  struct artist *b = NULL;
  struct artist *a2 = NULL;
  
  if( argc != 3 ) {
    printf("USAGE: recommend artists_file plays_file\n");
    exit(1);
  }

  fprintf(stderr, "Initialising data structures...\n");
  fprintf(stderr, " - reading artists\t(step 1/7)\n");
  artists = read_list(argv[1], parse_artist);

  fprintf(stderr, " - reading plays\t(step 2/7)\n");
  plays = read_list(argv[2], parse_play);
    
  fprintf(stderr, " - counting artists\t(step 3/7)\n");
  n = length(artists);

  fprintf(stderr, " - sorting plays\t(step 4/7)\n");
  plays = sort(plays, p_leq_uid_geq_count);
  
  fprintf(stderr, " - sorting artists\t(step 5/7)\n");
  artists = sort(artists, a_leq_id);

  fprintf(stderr, " - indexing artists\t(step 6/7)\n");
  index = create_index(artists, n);
  
  fprintf(stderr, " - registering fans\t(step 7/7)\n");
  register_fans(index, n, plays);
  fprintf(stderr, "done\n\n\n");

  // TODO: Complete this program.

  printf("Incomplete\n");

  free_list(artists, free);
  free_list(plays, free);
  free_index(index);

}
