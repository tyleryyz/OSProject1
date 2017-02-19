#include "parseMeta.h"

struct Points *parseMeta(char* input_file[])
  {
    fflush(stdout);
    struct Points *meta_data;
    int iterator=0;
    int tmp=0;
    int number_of_lines=0;
    int number_of_delims=0;
    int tempiterator=0;
    int operator_iterator=0;
    char buffer[350];
    const char *line_check;
    char file_letter;
    char *operator;
    char *cycle_time;
    char *sample_proc;
    char *throwaway;
    int *delims_per_line;
    FILE *meta_file;

    meta_file = fopen(input_file[1], "r");
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

          }
      }


    rewind(meta_file);

    delims_per_line = malloc(sizeof(int)*number_of_lines-1);

    // Getting the number of processes per line
    for (iterator = 0; iterator<number_of_lines; iterator++)
      {
        fgets(buffer, 350, meta_file);
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


    rewind(meta_file);



    fgets(buffer, 350, meta_file);
  for (iterator = 1; iterator < number_of_lines-1; iterator++)
      {
        fgets(buffer, 350, meta_file);
        sample_proc = strtok(buffer, ";");
        printf("%s\n", sample_proc);

        for (tmp = 0; tmp < delims_per_line[iterator]-1; tmp++)
          {
            sample_proc = strtok(NULL, ";");
            if (tmp == delims_per_line[iterator]-2)
              {
                sample_proc = strtok(sample_proc, "\n");
              }
            RemoveSpaces(sample_proc);
            printf("%s\n", sample_proc);

          }
      }
      operator = malloc(25*sizeof(char)+1);
      for (tempiterator = 0; tempiterator<strlen(sample_proc); tempiterator++){
        if (sample_proc[tempiterator] == '('){
          file_letter = sample_proc[tempiterator-1];
        }
        while (sample_proc[tempiterator] != ')'){
          printf("here");
          operator[operator_iterator] = sample_proc[tempiterator];

        }
      }

    printf("file_letter: %c", file_letter);
    printf("operator: %s", operator);
    meta_data = malloc(sizeof(struct Points) * number_of_delims+1);

    fclose(meta_file);
    return meta_data;

}

void RemoveSpaces(char* string)
{
  char* temp1 = string;
  char* temp2 = string;
  while(*temp2 != 0)
  {
    *temp1 = *temp2++;
    if(*temp1 != ' ')
      temp1++;
  }
  *temp1 = 0;
}
