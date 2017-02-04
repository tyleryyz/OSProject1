#include <string.h>
#include <stdlib.h>
#include "parseConfig.h"

int main(int argc, char *argv[])
  {
    char** parsed_config_data;
    if (argc < 2)
      {
        fprintf(stderr, "ERROR: must include config file\n");
        return(1);
      }
    else if (argc > 2)
      {
        fprintf(stderr, "ERROR: too many arguments passed\n");
        return(1);
      }
    parsed_config_data = parseConfig(argv);

    if (parsed_config_data[0] == NULL)
      {
        fprintf(stderr, "ERROR: no data parsed, bad config file\n");
        return(1);
      }

    else if (!strcmp(parsed_config_data[0], "ERROR[0]"))
      {
        fprintf(stderr, "ERROR: Incorrect config file type\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[0], "ERROR[0]"))
      {
        fprintf(stderr, "ERROR: Version number too high/incorrect data\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[1], "ERROR[0]"))
      {
        fprintf(stderr, "ERROR: Incorrect file type in file\n");
        return(1);
      }
    else if (!strcmp(parsed_config_data[2], "ERROR[0]"))
      {
        fprintf(stderr, "ERROR: Incorrect schedule code\n");
        return(1);
      }
    printf("%s", parsed_config_data[2]);
    return(0);
  }
