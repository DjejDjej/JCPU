#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc > 0) {
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
      return 1;
    }

    fseek(file, 0L, SEEK_END);

    long int res = ftell(file);
    char *buffer = malloc(res + 1);
    rewind(file);

    while (fgets(buffer, res + 1, file)) {
      printf("%s", buffer);
    }



    return 0;
  }
}
