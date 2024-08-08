#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    char matricula[20];
} Alumno;

void agregarAlumno(Alumno **alumnos, int *cantidad);
void guardarEnDisco(Alumno *alumnos, int cantidad);
void leerDeDisco(Alumno **alumnos, int *cantidad);
void imprimirAlumnos(Alumno *alumnos, int cantidad);
void liberarMemoria(Alumno *alumnos);

int main() {
    Alumno *alumnos = NULL;
    int cantidad = 0;
    int opcion;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Salir\n");
        printf("2. Leer disco\n");
        printf("3. Grabar dato\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                liberarMemoria(alumnos);
                return 0;
            case 2:
                leerDeDisco(&alumnos, &cantidad);
                imprimirAlumnos(alumnos, cantidad);
                break;
            case 3:
                agregarAlumno(&alumnos, &cantidad);
                guardarEnDisco(alumnos, cantidad);
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
}

void agregarAlumno(Alumno **alumnos, int *cantidad) {
    Alumno nuevoAlumno;
    char continuar;

    do {
        printf("Ingrese nombre: ");
        scanf("%s", nuevoAlumno.nombre);
        printf("Ingrese edad: ");
        scanf("%d", &nuevoAlumno.edad);
        printf("Ingrese matricula: ");
        scanf("%s", nuevoAlumno.matricula);

        *alumnos = (Alumno *)realloc(*alumnos, (*cantidad + 1) * sizeof(Alumno));
        if (*alumnos == NULL) {
            printf("Error al asignar memoria.\n");
            exit(1);
        }

        (*alumnos)[*cantidad] = nuevoAlumno;
        (*cantidad)++;

        printf("Desea agregar otro registro? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');
}

void guardarEnDisco(Alumno *alumnos, int cantidad) {
    FILE *file = fopen("alumnos.dat", "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&cantidad, sizeof(int), 1, file);
    fwrite(alumnos, sizeof(Alumno), cantidad, file);

    fclose(file);
    printf("Datos guardados correctamente.\n");
}

void leerDeDisco(Alumno **alumnos, int *cantidad) {
    FILE *file = fopen("alumnos.dat", "rb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fread(cantidad, sizeof(int), 1, file);
    *alumnos = (Alumno *)realloc(*alumnos, (*cantidad) * sizeof(Alumno));
    if (*alumnos == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    fread(*alumnos, sizeof(Alumno), *cantidad, file);

    fclose(file);
    printf("Datos leidos correctamente.\n");
}

void imprimirAlumnos(Alumno *alumnos, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("Alumno %d:\n", i + 1);
        printf("Nombre: %s\n", alumnos[i].nombre);
        printf("Edad: %d\n", alumnos[i].edad);
        printf("Matricula: %s\n", alumnos[i].matricula);
    }
}

void liberarMemoria(Alumno *alumnos) {
    free(alumnos);
}
