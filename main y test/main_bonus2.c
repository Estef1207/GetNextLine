#include "get_next_line_bonus.h"
#include <stdio.h>

#define MAX_FILES 10

void read_from_stdin(void) {
    char *line;
    
    printf("Modo lectura desde stdin (Ctrl+D para terminar en Unix/Linux, Ctrl+Z en Windows)\n");
    printf("Escribe algo y presiona Enter:\n");
    
    while ((line = get_next_line(0)) != NULL) {
        printf("Línea leída: %s", line);
        free(line);
    }
}

void read_files_simultaneously(char **filenames, int num_files) {
    int fds[MAX_FILES];
    int active_files = num_files;
    int has_content[MAX_FILES];
    
    // Abrir todos los archivos
    for (int i = 0; i < num_files; i++) {
        fds[i] = open(filenames[i], O_RDONLY);
        if (fds[i] == -1) {
            printf("Error al abrir el archivo %s\n", filenames[i]);
            active_files--;
            has_content[i] = 0;
        } else {
            has_content[i] = 1;
        }
    }
    
    // Leer alternadamente de cada archivo mientras haya archivos activos
    while (active_files > 0) {
        for (int i = 0; i < num_files; i++) {
            if (has_content[i]) {
                char *line = get_next_line(fds[i]);
                if (line) {
                    printf("Archivo %d: %s", i + 1, line);
                    free(line);
                } else {
                    // No hay más contenido en este archivo
                    has_content[i] = 0;
                    close(fds[i]);
                    active_files--;
                }
            }
        }
        if (active_files > 0)
            printf("\n"); // Separador entre rondas de lectura
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // No hay argumentos, leer de stdin
        read_from_stdin();
        return 0;
    }
    
    // Hay argumentos, leer de archivos
    int num_files = argc - 1;
    if (num_files > MAX_FILES) {
        printf("Demasiados archivos. Máximo: %d\n", MAX_FILES);
        num_files = MAX_FILES;
    }
    
    printf("Leyendo %d archivos simultáneamente:\n", num_files);
    for (int i = 0; i < num_files; i++) {
        printf("Archivo %d: %s\n", i + 1, argv[i + 1]);
    }
    printf("\n--- Inicio de la lectura ---\n\n");
    
    read_files_simultaneously(argv + 1, num_files);
    
    return 0;
}
