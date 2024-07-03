#include <stdio.h>
#include <string.h>
#include "funciones.h"

void ingresarCliente(char clientes[][2][40]) {
    FILE *file;
    char nombre[40];
    char cedula[40];
    int i;

    file = fopen("clientes.txt", "a");
    if (file == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombre);
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula);

    for (i = 0; i < 5; i++) {
        if (strcmp(clientes[i][0], "") == 0) {
            strcpy(clientes[i][0], nombre);
            strcpy(clientes[i][1], cedula);
            break;
        }
    }

    if (i == 5) {
        printf("No hay espacio para más clientes.\n");
        fclose(file);
        return;
    }

    fprintf(file, "Nombre: %s, Cedula: %s\n", nombre, cedula);
    printf( "Nombre: %s, Cedula: %s\n", nombre, cedula);
    fclose(file);

    printf("Cliente ingresado correctamente.\n");
}

void imprimirClientes(char clientes[][2][40]){
    for (int i = 0; i < 5; i++)
    {
        printf("%s\t\t%s\n",clientes[i][0],clientes[i][1]);
    }   
}

void listarPeliculas(char peliculas[][4][40]) {
    FILE *fp = fopen("ListarP.txt", "w");
    if (fp != NULL) {
        printf("Se abrio correctamente el archivo ListarP.txt\n");

        printf("Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        fprintf(fp, "Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        for (int i = 0; i < 10; i++) {
            fprintf(fp, "%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            printf( "%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
        }

        fclose(fp);
    } else {
        printf("No se pudo abrir el archivo ListarP.txt\n");
    }
}

void buscarporNombre(char peliculas[][4][40]) {
    char nombre[40];

    printf("Ingrese el nombre de la película: ");
    scanf("%s", nombre);

    FILE *file = fopen("BuscarPNombre.txt", "w");
    if (file != NULL) {
        printf("Se abrió correctamente BuscarPNombre.txt\n");
        
        fprintf(file, "Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        printf("Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        for (int i = 0; i < 10; i++) {
            if (strcmp(peliculas[i][1], nombre) == 0) {
                fprintf(file, "%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
                printf( "%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            }
        }

        fclose(file);
    } else {
        printf("No se pudo abrir BuscarPNombre.txt\n");
    }
}


void buscarporGenero(char peliculas[][4][40]) {
    
    char genero[40];
    
    printf("Ingrese el género de la película: ");
    scanf("%s", genero);
    FILE *file = fopen("BuscarPGenero.txt", "w");
    
     if (file != NULL) {
        printf("Se abrio correctamente BuscarPGenero.txt\n");
        
        fprintf(file,"Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        printf("Numero\t\tPelicula\t\t\tHora\t\tGenero\n");
        for (int i = 0; i < 10; i++)
        {
            if (strcmp(peliculas[i][3],genero)==0)
            {
                fprintf(file, "%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
                printf("%s\t\t%s\t\t%s\t\t%s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            }
            
        }
        fclose(file);
    }else
    {
        printf("No se pudo abrir BuscarPGenero.txt\n");
    }
}

void comprarTicket(char peliculas[][4][40], double precio[], char clientes[][2][40], int reserva[][4]) {
    char cedula[40];
    int NumPelicula, cantidad, tipoEntrada, totalEntradas = 0;
    int clienteIndex = -1;

    printf("Ingrese su cedula: ");
    scanf("%s", cedula);

    
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cedula no encontrada.\n");
        return;
    }

    printf("Ingrese el numero de la pelicula: ");
    scanf("%d", &NumPelicula);

    if (NumPelicula < 1 || NumPelicula > 10) {
        printf("El numero de la pelicula no es el correcto.\n");
        return;
    }

    double total = 0.0;

    
    FILE *file = fopen("Reservas.txt", "a");
    if (file == NULL) {
        printf("No se pudo abrir el archivo de reservas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        do {
            printf("Ingrese la cantidad de entradas para el tipo %d (0 - Normal 7.00, 1 - Ninos 3.50, 2 - Adulto mayor 3): ", i);
            scanf("%d", &cantidad);
        } while (cantidad < 0);

        if (cantidad > 0) {
            for (int j = 0; j < 10; j++) {
                if (reserva[j][0] == -1) {
                    reserva[j][0] = NumPelicula - 1;
                    reserva[j][1] = clienteIndex;
                    reserva[j][2] = cantidad;
                    reserva[j][3] = i;
                    total += cantidad * precio[i];
                    totalEntradas += cantidad;

                    
                    fprintf(file, "Cliente: %s, Cedula: %s, Pelicula: %s, Hora: %s, Genero: %s, TipoEntrada: %d, Cantidad: %d, Precio: %.2f\n",
                            clientes[clienteIndex][0], clientes[clienteIndex][1],
                            peliculas[NumPelicula - 1][1], peliculas[NumPelicula - 1][2], peliculas[NumPelicula - 1][3],
                            i, cantidad, cantidad * precio[i]);
                    break;
                }
            }
        }
    }

    fclose(file);

    if (totalEntradas == 0) {
        printf("No se ingresaron entradas.\n");
    } else {
        printf("Compra realizada exitosamente. Total: $%.2f\n", total);
    }
}

void verCompras(char peliculas[][4][40], double precio[], char clientes[][2][40], int reserva[][4]) {
    char cedula[40];
    int clienteIndex = -1;

    // Mostrar contenido previo del archivo
    FILE *file = fopen("Ver compras.txt", "r");
    if (file != NULL) {
        char line[256];
        printf("Contenido de Ver_compras.txt:\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("No se pudo abrir 'Ver_compras.txt' para lectura.\n");
    }

    printf("\nIngrese su cedula: ");
    scanf("%s", cedula);

    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][1], cedula) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cedula no encontrada.\n");
        return;
    }

    file = fopen("Ver compras.txt", "a");
    if (file != NULL) {
        printf("Se abrio correctamente 'Ver_compras.txt'\n");
    
        fprintf(file, "Compras realizadas por %s (Cedula: %s):\n", clientes[clienteIndex][0], clientes[clienteIndex][1]);
        printf("Compras realizadas por %s (Cedula: %s):\n", clientes[clienteIndex][0], clientes[clienteIndex][1]);
        double totalPrecio = 0;

        for (int i = 0; i < 10; i++) {
            if (reserva[i][1] == clienteIndex) {
                int peliculaIndex = reserva[i][0];
                int cantidad = reserva[i][2];
                int tipoEntrada = reserva[i][3];
                double precioEntrada = precio[tipoEntrada];
                double precioTotal = cantidad * precioEntrada;

                fprintf(file, "  Pelicula: %s, Hora: %s, Genero: %s, Cantidad: %d, Precio de entrada: $%.2f, Precio Total: $%.2f\n",
                       peliculas[peliculaIndex][1], peliculas[peliculaIndex][2], peliculas[peliculaIndex][3],
                       cantidad, precioEntrada, precioTotal);
                printf("  Pelicula: %s, Hora: %s, Genero: %s, Cantidad: %d, Precio de entrada: $%.2f, Precio Total: $%.2f\n",
                       peliculas[peliculaIndex][1], peliculas[peliculaIndex][2], peliculas[peliculaIndex][3],
                       cantidad, precioEntrada, precioTotal);

                totalPrecio += precioTotal;
            }
        }

        if (totalPrecio == 0) {
            printf("No tiene reservas.\n");
        } else {
            fprintf(file, "Total a pagar: $%.2f\n", totalPrecio);
            printf("Total a pagar: $%.2f\n", totalPrecio);
        }
        fclose(file);
    } else {
        printf("No se pudo abrir 'Ver_compras.txt' para escritura.\n");
    }
}
