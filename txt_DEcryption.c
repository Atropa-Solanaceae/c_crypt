#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPTION_KEY "key"
void decrypt_file(char* file_path) {
    FILE* file = fopen(file_path, "r+");
    if (file == NULL) {
        printf("Error opening file %s\n", file_path);
        return;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the file content
    char* file_content = (char*) malloc((file_size + 1) * sizeof(char));
    fread(file_content, sizeof(char), file_size, file);

    // Decrypt the file content
    for (int i = 0; i < file_size; i++) {
        file_content[i] ^= ENCRYPTION_KEY[i % strlen(ENCRYPTION_KEY)];
    }

    // Write the decrypted content back to the file
    rewind(file);
    fwrite(file_content, sizeof(char), file_size, file);

    // Close the file and free memory
    fclose(file);
    free(file_content);
}

int main() {
    FILE* fp;
    char path[1035];

    /* Open the command for reading. */
    fp = popen("dir /b *.txt", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        path[strlen(path)-1] = '\0';
        decrypt_file(path);
    }

    /* close */
    pclose(fp);
    return 0;
}
