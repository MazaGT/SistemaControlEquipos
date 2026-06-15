//Pedro Pablo Maza

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Equipo{
    int codigo;
    char nombre[50];
    char marca[30];
    char responsable[50];
    char estado[20];
    float precio;
};

void registrarEquipo();
void mostrarEquipos();
void buscarEquipo();
void modificarEquipo();
void eliminarEquipo();

int main(){

    int opcion;

    do{
        printf("\n========== SISTEMA CONTROL EQUIPOS ==========\n");
        printf("1. Registrar equipo\n");
        printf("Bienvenido al sistema\n");
        printf("2. Mostrar equipos\n");
        printf("3. Buscar equipo\n");
        printf("4. Modificar equipo\n");
        printf("5. Eliminar equipo\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d",&opcion);

        switch(opcion){

            case 1:
                registrarEquipo();
                break;

            case 2:
                mostrarEquipos();
                break;

            case 3:
                buscarEquipo();
                break;

            case 4:
                modificarEquipo();
                break;

            case 5:
                eliminarEquipo();
                break;

            case 6:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    }while(opcion != 6);

    return 0;
}

void registrarEquipo(){

    struct Equipo registro;

    FILE *archivo;

    archivo = fopen("equipos.dat","ab");

    if(archivo == NULL){
        printf("Error al abrir archivo.\n");
        return;
    }

    printf("\nCodigo: ");
    scanf("%d",&registro.codigo);
    getchar();

    printf("Nombre del equipo: ");
    fgets(registro.nombre,50,stdin);
    registro.nombre[strlen(registro.nombre)-1]='\0';

    printf("Marca: ");
    fgets(registro.marca,30,stdin);
    registro.marca[strlen(registro.marca)-1]='\0';

    printf("Responsable: ");
    fgets(registro.responsable,50,stdin);
    registro.responsable[strlen(registro.responsable)-1]='\0';

    printf("Estado: ");
    fgets(registro.estado,20,stdin);
    registro.estado[strlen(registro.estado)-1]='\0';

    printf("Precio: ");
    scanf("%f",&registro.precio);

    fwrite(&registro,sizeof(struct Equipo),1,archivo);

    fclose(archivo);

    printf("\nEquipo registrado correctamente.\n");
}

void mostrarEquipos(){

    struct Equipo registro;

    FILE *archivo;

    archivo = fopen("equipos.dat","rb");

    if(archivo == NULL){
        printf("\nNo hay registros.\n");
        return;
    }

    printf("\n===== LISTA DE EQUIPOS =====\n");

    while(fread(&registro,sizeof(struct Equipo),1,archivo)==1){

        printf("\nCodigo: %d\n",registro.codigo);
        printf("Equipo: %s\n",registro.nombre);
        printf("Marca: %s\n",registro.marca);
        printf("Responsable: %s\n",registro.responsable);
        printf("Estado: %s\n",registro.estado);
        printf("Precio: Q%.2f\n",registro.precio);
    }

    fclose(archivo);
}

void buscarEquipo(){

    struct Equipo registro;

    int codigoBuscar;
    int encontrado = 0;

    FILE *archivo;

    archivo = fopen("equipos.dat","rb");

    if(archivo == NULL){
        printf("\nNo hay registros.\n");
        return;
    }

    printf("Ingrese codigo a buscar: ");
    scanf("%d",&codigoBuscar);

    while(fread(&registro,sizeof(struct Equipo),1,archivo)==1){

        if(registro.codigo == codigoBuscar){

            printf("\nEquipo encontrado\n");
            printf("Nombre: %s\n",registro.nombre);
            printf("Marca: %s\n",registro.marca);
            printf("Responsable: %s\n",registro.responsable);
            printf("Estado: %s\n",registro.estado);
            printf("Precio: Q%.2f\n",registro.precio);

            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0){
        printf("\nNo se encontro el equipo.\n");
    }

    fclose(archivo);
}

void modificarEquipo(){

    struct Equipo registro;

    int codigoBuscar;
    int encontrado = 0;

    FILE *archivo;

    archivo = fopen("equipos.dat","rb+");

    if(archivo == NULL){
        printf("\nNo existe el archivo.\n");
        return;
    }

    printf("Codigo del equipo: ");
    scanf("%d",&codigoBuscar);

    while(fread(&registro,sizeof(struct Equipo),1,archivo)==1){

        if(registro.codigo == codigoBuscar){

            printf("Precio actual: %.2f\n",registro.precio);

            printf("Nuevo precio: ");
            scanf("%f",&registro.precio);

            fseek(archivo,-sizeof(struct Equipo),SEEK_CUR);

            fwrite(&registro,sizeof(struct Equipo),1,archivo);

            encontrado = 1;

            printf("\nPrecio actualizado.\n");

            break;
        }
    }

    if(encontrado == 0){
        printf("\nEquipo no encontrado.\n");
    }

    fclose(archivo);
}

void eliminarEquipo(){

    struct Equipo registro;

    int codigoBuscar;
    int encontrado = 0;

    FILE *archivo;
    FILE *temporal;

    archivo = fopen("equipos.dat","rb");
    temporal = fopen("temp.dat","wb");

    if(archivo == NULL){
        printf("\nNo existe el archivo.\n");
        return;
    }

    printf("Codigo a eliminar: ");
    scanf("%d",&codigoBuscar);

    while(fread(&registro,sizeof(struct Equipo),1,archivo)==1){

        if(registro.codigo != codigoBuscar){

            fwrite(&registro,sizeof(struct Equipo),1,temporal);

        }else{

            encontrado = 1;
        }
    }

    fclose(archivo);
    fclose(temporal);

    remove("equipos.dat");
    rename("temp.dat","equipos.dat");

    if(encontrado){
        printf("\nEquipo eliminado correctamente.\n");
    }else{
        printf("\nNo se encontro el equipo.\n");
    }
}