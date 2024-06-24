#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#define ValoresCuentasAdmin "cuentaAdmin.dat"
#define ValoresCuentasCajero "cuentasCajeros.dat"
#define ProductosHeladeria "productos.txt"


void menuPrincipal(TDatosCuentaAdminYCajero *datos)
{
    crearArchivoBinario(ProductosHeladeria);
    system("cls");
    int opPuesto = 0;
    int dni_input;
    do
    {
        printf("BIENVENIDO A LA HELADERIA ICE!!!\n");
        printf("Indique su puesto para continuar\n1)Cajero\n2)Administrador\n3)Salir\n");
        fflush(stdin);
        scanf("%d",&opPuesto);
        switch(opPuesto)
        {
        case 1:
            if(archivoEstaVacio(ValoresCuentasAdmin)==0)
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                //si el dni existe redirigimos al login
                if(existe_dni(ValoresCuentasCajero,dni_input)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    login_admin(ValoresCuentasCajero,dni_input);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El dni no está registrado en la tabla administadores. Un administrador debe registrar la cuenta.\n");
                    system("pause");
                }
            } else {
                printf("No existen cuentas creadas para cajeros");
            }
            break;
        case 2:
            if(archivoEstaVacio(ValoresCuentasAdmin)==0)
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                //si el dni existe redirigimos al login
                if(existe_dni(ValoresCuentasAdmin,dni_input)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    login_admin(ValoresCuentasAdmin,dni_input);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El dni no está registrado en la tabla administadores\n");
                    system("pause");
                    guardar_admin(ValoresCuentasAdmin, dni_input, "Administrador");
                }
            }
            else
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                system("pause");
                guardar_admin(ValoresCuentasAdmin,dni_input, "Administrador");
            }


            break;
        default:
            break;
        }
    }
    while(opPuesto!=3);
}
void crearArchivoBinario(char *nombreArchivoBinario)
{
    FILE *archivo = fopen(nombreArchivoBinario, "ab");
    if(archivo == NULL)
    {
        printf("No se pudo crear el arcrivo\n");
    }
    else
    {
        printf("Se creo el archivo correctamente\n");
    }
    fclose(archivo);
}

int archivoEstaVacio(char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        perror("No se pudo abrir el archivo");
        return 1; // Consideramos vacío si no se puede abrir
    }

    fseek(archivo, 0, SEEK_END);
    long size = ftell(archivo);
    fclose(archivo);

    return size == 0; // Retorna 1 si el archivo está vacío, 0 si no lo está
}

void menuAdmin(TDatosCuentaAdminYCajero *datos)
{
    int op = 0;
    int dni_input;
    do
    {
        printf("Bienvenido al ADMINISTRADOR\n");
        printf("Elija una de las opciones:\n1)Agregar nuevo cajero\n2)Agregar nuevo administrador\n3)Revisar/Agregar stock\n4)Realizar compra\n5)Volver al menu principal\n6)Eliminar admin\n");
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
                crearArchivoBinario(ValoresCuentasCajero);
                printf("Ingrese el dni del cajero a registrar:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                //si el dni existe redirigimos al login
                if(existe_dni(ValoresCuentasCajero,dni_input)==1)
                {
                    //login..
                    printf("Dni encontrado, este cajero ya posee una cuenta.\n");
                    system("pause");
                    menuAdmin(&datos);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    guardar_admin(ValoresCuentasCajero, dni_input, "Cajero");
                }
            menuAdmin(&datos);
            break;
        case 2:
            printf("Ingrese su dni:\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            system("pause");
            while(existe_dni(ValoresCuentasCajero,dni_input)==1)
            {
                //login..
                printf("Dni encontrado, ingrese dni que no tenga cuenta\n");
                fflush(stdin);
                scanf("%d",&dni_input);
            }
            guardar_admin(ValoresCuentasAdmin,dni_input, "Administrador");
            break;
        case 3:
            if(archivoEstaVacio(ProductosHeladeria)!=0) {
                printf("Administrador, inicia por primera vez. Es su responsabilidad cargar el stock con el que comienza su heladeria\n");
                cargar_stock_inicio();
            } else {
                printf("El stock actual es: \n");

            }
            break;
        case 4:
            break;
        case 5:
            menuPrincipal(&datos);
            break;
        case 6:
            printf("Indique dni a eliminar\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            eliminar_admin(dni_input);
            menuAdmin(&datos);
            break;
        default:
            break;
        }
    }
    while (op<1 || op>6);
}

void guardar_admin(char *nomArchivo, int dni_input, char texto)
{
    if(existe_dni(nomArchivo,dni_input)==0)//si el dni no está registrado, procedemos
    {
        TDatosCuentaAdminYCajero admin;
        FILE * archivo;
        archivo=fopen(nomArchivo,"ab");
        if(archivo!=NULL)
        {
            admin.dni = dni_input;

            //levantamos los demás datos solicitandolos por pantalla
            printf("Password \n");
            fflush(stdin);
            gets(admin.contrasena);

            fwrite(&admin, sizeof(admin), 1, archivo);

            if(fclose(archivo)==0)
            {
                printf("%s cargado!\n", texto);
                printf("\n");
                return;
            }
            else
            {
                printf("No se pudo cargar el %s \n", texto);
            }
        }
        else
        {
            printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
        }
    }
    else
    {
        printf("DNI ya registrado\n");
        login_admin(nomArchivo,dni_input);

    }
}


int existe_dni(char *ValoresCuentasAdmins,int dni_input)
{
    TDatosCuentaAdminYCajero admin;
    FILE * archivo = fopen(ValoresCuentasAdmins,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni==dni_input)
                {
                    fclose(archivo);
                    return 1;//ID encontrado
                }
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
    }
    return 0;//ID no encontrado

}


void login_admin(char *nomArchivo,int dni_admin)
{
    TDatosCuentaAdminYCajero admin;
    char contrasena_input[20];
    FILE *archivo = fopen(nomArchivo, "rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo))//mientras el puntero tenga para leer..
        {

            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni == dni_admin)//coincide?
                {
                    printf("Ingrese su password:\n");
                    fflush(stdin);
                    gets(contrasena_input);

                    //comparamos la contraseña ingresada con la guardada en ese registro
                    if(strcmp(contrasena_input,admin.contrasena)==0)
                    {
                        //si coincide..
                        printf("Redirigiendo..\n");
                        if(strcmp(ValoresCuentasCajero,nomArchivo)){
                        fclose(archivo);
                        menuAdmin(&admin);
                        } else {
                            menuCajero();
                        }
                    }
                    else
                    {
                        printf("Password incorrecta!\n");
                    }

                }
            }

        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
    }
}

void eliminar_admin(int dni_input)
{
    TDatosCuentaAdminYCajero cuenta;
    FILE *archivo = fopen(ValoresCuentasAdmin, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    char contrasena_input[20];
    int encontrado = 0;
    char decision;

    if (!archivo || !temp)
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n", strerror(errno));
        if (archivo) fclose(archivo);
        if (temp) fclose(temp);
        return;
    }

    printf("Esta acción es irreversible. ¿Está seguro de que desea continuar? (S/N): \n");
    scanf(" %c", &decision);
    decision = toupper(decision);

    if(decision=='S')
    {
        //leemos el archivo 'original'
        while(fread(&cuenta,sizeof(cuenta),1,archivo)==1)
        {
            //mientras herr.id sea != del id consultado para eliminar, copiamos esa herramienta en temp.dat
            if(cuenta.dni!=dni_input)
            {
                fwrite(&cuenta,sizeof(cuenta),1,temp);
            }
            else
            {
                printf("Ingrese password del admin '%d' a eliminar\n",cuenta.dni);
                fflush(stdin);
                gets(contrasena_input);
                if(strcmp(cuenta.contrasena,contrasena_input)==0){
                    //en caso de que el herr.id coincida con el id por borrar..
                    encontrado=1;
                }else{
                    printf("Password incorrecta\n");
                    system("pause");
                    menuAdmin(&cuenta);
                }

            }
        }
        fclose(archivo);
        fclose(temp);

        if(encontrado==1)
        {
                    if(remove(ValoresCuentasAdmin)==0){
                        rename("temp.dat", ValoresCuentasAdmin);
                        listar_admins();
                    }else{
                        printf("ERROR: %s\n",strerror(errno));
                    }
        }
        else
        {
            remove("temp.dat");
            printf("\n");
        }

    }
}

void listar_admins()
{
    TDatosCuentaAdminYCajero admin;
    FILE *archivo = fopen(ValoresCuentasAdmin, "rb");
    if(!archivo)
    {
        printf("El archivo no se encontro");
    }
    else
    {
        fread(&admin, sizeof(admin),1,archivo);
        while(!feof(archivo))
        {
            printf("DNI ADMIN:%d\n",admin.dni,admin.contrasena);
            fread(&admin, sizeof(admin),1,archivo);
        }
    }
    fclose(archivo);
}

/**********************SECCION CAJEROS*****************************************/
void menuCajero(){
printf("Probando");
}
void cargar_stock_inicio() {
    TProductos productos;
    TDatosCuentaAdminYCajero dato;
    FILE *archivo = fopen(ProductosHeladeria, "ab");
    if(!archivo) {
        printf("Archivo no encontrado");
    } else {
        printf("Ingrese la cantidad de tortas heladas: ");
        fflush(stdin);
        scanf("%d",&productos.tortas_heladas);
        printf("\nIngrese el precio de cada torta helada: ");
        fflush(stdin);
        scanf("%f",&productos.precio_tortas_heladas);
        printf("\nIngrese la cantidad de postres helados: ");
        fflush(stdin);
        scanf("%d",&productos.postres_helados);
        printf("\nIngrese el precio de cada postre helado: ");
        fflush(stdin);
        scanf("%f",&productos.precio_postres_helados);
        printf("\nAhora vamos a ingresar la cantidad, en gramos, de cada sabor:\n");
        printf("Dulce de leche: ");
        fflush(stdin);
        scanf("%f",&productos.saboresGramos.dulce_de_leche_gramos);
        printf("\nFrutilla: ");
        fflush(stdin);
        scanf("%f",&productos.saboresGramos.frutilla_gramos);
        printf("\nCrema Americana: ");
        fflush(stdin);
        scanf("%f",&productos.saboresGramos.crema_americana_gramos);
        printf("\nChocolate: ");
        fflush(stdin);
        scanf("%f",&productos.saboresGramos.chocolate_gramos);
        printf("\nMenta granizada: ");
        fflush(stdin);
        scanf("%f",&productos.saboresGramos.menta_granizada_gramos);
        // Solicitar datos de precios de venta
        printf("Ingrese los precios de venta:\n");

        printf("Una bocha: ");
        scanf("%f", &productos.preciosVentas.una_bocha);

        printf("Dos bochas: ");
        scanf("%f", &productos.preciosVentas.dos_bochas);

        printf("Tres bochas: ");
        scanf("%f", &productos.preciosVentas.tres_bochas);

        printf("Un cuarto (kilo): ");
        scanf("%f", &productos.preciosVentas.cuarto);

        printf("Medio kilo: ");
        scanf("%f", &productos.preciosVentas.medio);

        printf("Un kilo: ");
        scanf("%f", &productos.preciosVentas.kilo);

        // Escribir todos los datos en el archivo
        fprintf(archivo, "%d %.2f %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",
                productos.tortas_heladas, productos.precio_tortas_heladas,
                productos.postres_helados, productos.precio_postres_helados,
                productos.saboresGramos.dulce_de_leche_gramos,
                productos.saboresGramos.frutilla_gramos,
                productos.saboresGramos.crema_americana_gramos,
                productos.saboresGramos.chocolate_gramos,
                productos.saboresGramos.menta_granizada_gramos,
                productos.preciosVentas.una_bocha, productos.preciosVentas.dos_bochas,
                productos.preciosVentas.tres_bochas, productos.preciosVentas.cuarto,
                productos.preciosVentas.medio, productos.preciosVentas.kilo);

        printf("\nFelicidades, el stock fue cargado con exito\n");
    }
    fclose(archivo);
    menuAdmin(&dato);
}

void listar_stock() {
    FILE *archivo = fopen(ProductosHeladeria, "rb");
}
