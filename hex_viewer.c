
#include <stdio.h>

#define BUFFER_SIZE 16

int main(int argc, char *argv[])
{
    FILE *file;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        printf("Error: Unable to open the specified file.\n");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        // Display hexadecimal values
        for (size_t i = 0; i < bytesRead; i++)
        {
            printf("%02X ", buffer[i]);
        }

        // Maintain proper column alignment
        for (size_t i = bytesRead; i < BUFFER_SIZE; i++)
        {
            printf("   ");
        }

        printf(" | ");

        // Display printable ASCII characters
        for (size_t i = 0; i < bytesRead; i++)
        {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                printf("%c", buffer[i]);
            else
                printf(".");
        }

        printf("\n");
    }

    if (ferror(file))
    {
        printf("Error: Failed to read the file.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}
