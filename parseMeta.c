#include "parseMeta.h"

struct Points *parseMeta(char* input_file[])
  {
    fflush(stdout);
    struct Points *meta_data;
    int iterator;
    int tmp;
    int number_of_lines;
    int number_of_delims;
    char buffer[100];
    const char *line_check;
    int file_letter;
    char *operator;
    char *cycle_time;
    char *sample_proc;
    int *delims_per_line;


    FILE* meta_file = fopen(input_file[1], "r");
    if (meta_file == NULL){
      exit(1);
    }


    // getting number of lines in file
    while(!feof(meta_file))
      {
        tmp = fgetc(meta_file);
        if (tmp == '\n')
          {
            number_of_lines+=1;
            printf("%d\n", number_of_lines);
          }
      }

    printf("%d\n", number_of_lines);
    rewind(meta_file);
    printf("here!\n");
    delims_per_line = malloc(sizeof(int)*number_of_lines-1);

    // Getting the number of processes per line
    for (iterator = 0; iterator<number_of_lines; iterator++)
      {
        fgets(buffer, 100, meta_file);
        line_check = buffer;
        while ((line_check = strstr(line_check, ";")))
          {
            number_of_delims++;
            line_check++;
          }
        delims_per_line[iterator] = number_of_delims;
        if(iterator == number_of_lines -2)
          {
            number_of_delims++;
            delims_per_line[iterator] = number_of_delims;
          }
        number_of_delims = 0;
      }
    printf("here!3\n");
    rewind(meta_file);
    for (iterator = 0; iterator < number_of_lines; iterator++){
      printf("line: %d delims per line: %d\n", iterator, delims_per_line[iterator]);
    }




    meta_data = malloc(sizeof(struct Points) * number_of_delims+1);

    fclose(meta_file);
    return meta_data;

  }
