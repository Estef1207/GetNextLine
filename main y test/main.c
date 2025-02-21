#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int line_count = 0;

    // Si no hay argumentos, leer desde stdin
    if (argc == 1)
    {
        printf("Leyendo desde la entrada estándar (stdin):\n");
        while ((line = get_next_line(0)) != NULL) // fd = 0 para stdin
        {
            printf("Línea %d: %s", ++line_count, line);
            free(line);

            // Opción de seguridad para evitar bucles infinitos
            if (line_count > 1000)
            {
                printf("Posible bucle infinito detectado\n");
                break;
            }
        }

        if (line_count == 0)
            printf("No se ingresaron líneas o hubo un error en la lectura\n");
        else
            printf("Total de líneas leídas desde stdin: %d\n", line_count);

        return 0;
    }

    // Si se proporciona un archivo como argumento
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    line_count = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Línea %d: %s", ++line_count, line);
        free(line);

        // Opción de seguridad para evitar bucles infinitos
        if (line_count > 1000)
        {
            printf("Posible bucle infinito detectado\n");
            break;
        }
    }

    if (line_count == 0)
        printf("El archivo está vacío o hubo un error en la lectura\n");
    else
        printf("Total de líneas leídas: %d\n", line_count);

    close(fd);

    return 0;
}
