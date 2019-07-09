#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    // the file we want to read from
    char filename[] = "matriz10x100.txt";

    // open the file for reading
    FILE *file = fopen(filename, "r");

    // make sure the file opened properly
    if(NULL == file)
    {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return 1;
    }

    // set up the buffer to read the line into. Don't worry too much
    // if some of the lines are longer than 80 characters - the buffer
    // will be made bigger if need be.
    size_t buffer_size = 5;
    char *buffer = malloc(buffer_size * sizeof(char));

    // read each line and print it to the screen
    int line_number = 0;
    while(-1 != getline(&buffer, &buffer_size, file))
    {
        printf("%d: %s", ++line_number, buffer);
    }
    fflush(stdout);

    // make sure we close the file and clean up the buffer when we're
    // finished
    fclose(file);
    free(buffer);

    return 0;
}


// #include <stdio.h>
// #include <string.h>

// int main ()
// {
//   char str[] ="This:a:sample:string:!";
//   char * pch;
//   printf ("Splitting string \"%s\" into tokens:\n",str);
//   pch = strtok (str,":");
//   while (pch != NULL)
//   {
//     printf ("%s\n",pch);
//     pch = strtok (NULL, ":");
//   }
//   return 0;
// }