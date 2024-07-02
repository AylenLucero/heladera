#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#define ValoresCuentasAdmin "cuentaAdmin.dat"
#define ValoresCuentasCajero "cuentasCajeros.dat"
#define ProductosHeladeria "productos.txt"
#define HistorialVentas "histoVentas.txt"

TProductos productos;
THistorialVentas histoVentas;

void menuPrincipal(TDatosCuentaAdminYCajero *datos)
{
    crearArchivoTxt(ProductosHeladeria);
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
            }
            else
            {
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

void crearArchivoTxt(char *nombreArchivoTxt)
{
    FILE *archivo = fopen(nombreArchivoTxt, "at");
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
        printf("Elija una de las opciones:\n1)Agregar nuevo cajero\n2)Agregar nuevo administrador\n3)Revisar stock y precios\n4)Realizar compra\n5)Volver al menu principal\n6)Eliminar admin\n7)Eliminar cajero\n");
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
            if(archivoEstaVacio(ProductosHeladeria)!=0)
            {
                printf("Administrador, inicia por primera vez. Es su responsabilidad cargar el stock con el que comienza su heladeria\n");
                pedirDatosProcutosInicio();
                guardarDatosTxtProductos();
            }
            else
            {
                system("cls");
                listarDatos();
                system("pause");
                menuAdmin(&datos);
            }
            break;
        case 4:
            printf("ARME SU PEDIDO\n");
            realizarPedido();
            break;
        case 5:
            menuPrincipal(&datos);
            break;
        case 6:
            printf("Indique dni del Admin a eliminar\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            eliminar_admin_O_Cajero(ValoresCuentasAdmin,dni_input);
            menuAdmin(&datos);
            break;
        case 7:
            printf("Indique dni del Cajero a eliminar\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            eliminar_admin_O_Cajero(ValoresCuentasCajero,dni_input);
            menuAdmin(&datos);
            break;
        default:
            break;
        }
    }
    while (op<1 || op>6);
}

void guardar_admin(char *nomArchivo, int dni_input, char *texto)
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
                        if(strcmp(ValoresCuentasCajero,nomArchivo))
                        {
                            fclose(archivo);
                            menuAdmin(&admin);
                        }
                        else
                        {
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

void eliminar_admin_O_Cajero(char *nomArchivo,int dni_input)
{
    TDatosCuentaAdminYCajero cuenta;
    FILE *archivo = fopen(nomArchivo, "rb");
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
                printf("%d",strcmp(nomArchivo,ValoresCuentasAdmin));
                if(strcmp(nomArchivo,ValoresCuentasAdmin)==0)   //unicamente se pide contraseña para eliminar otro admin
                {
                    printf("Ingrese password del admin '%d' a eliminar\n",cuenta.dni);
                    fflush(stdin);
                    gets(contrasena_input);

                    if(strcmp(cuenta.contrasena,contrasena_input)==0)
                    {
                        //en caso de que el herr.id coincida con el id por borrar..
                        encontrado=1;
                    }
                    else
                    {
                        printf("Password incorrecta\n");
                        system("pause");
                        menuAdmin(&cuenta);
                    }
                }
                else
                {
                    encontrado=1;
                }

            }
        }
        fclose(archivo);
        fclose(temp);

        if(encontrado==1)
        {
            if(remove(nomArchivo)==0)
            {
                rename("temp.dat", nomArchivo);
            }
            else
            {
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
void menuCajero()
{
    int op;
    system("cls");
    printf("Bienvenido al menu del Cajero. Que desea hacer?\n1)Cargar nueva venta\n2)Volver al menu principal\n");
    fflush(stdin);
    scanf("%d",&op);
    switch(op)
    {
    case 1:
        obtenerPedido();
        break;
    default:
        break;
    }
}

void pedirDatosProcutosInicio()
{
    printf("Ingrese la cantidad de tortas heladas: ");
    scanf("%d", &productos.tortas_heladas);

    printf("Ingrese el precio de las tortas heladas: ");
    scanf("%f", &productos.precio_tortas_heladas);

    printf("Ingrese la cantidad de postres helados: ");
    scanf("%d", &productos.postres_helados);

    printf("Ingrese el precio de los postres helados: ");
    scanf("%f", &productos.precio_postres_helados);

    printf("Ingrese los KG de los siguientes sabores:\n");
    printf("Dulce de leche: ");
    scanf("%f", &productos.saboresKGramos[0]);

    printf("Frutilla: ");
    scanf("%f", &productos.saboresKGramos[1]);

    printf("Crema americana: ");
    scanf("%f", &productos.saboresKGramos[2]);

    printf("Chocolate: ");
    scanf("%f", &productos.saboresKGramos[3]);

    printf("Menta granizada: ");
    scanf("%f", &productos.saboresKGramos[4]);

    printf("Ingrese los precios por cantidad:\n");
    printf("Una bocha: ");
    scanf("%f", &productos.preciosPorCantidad[0]);

    printf("Dos bochas: ");
    scanf("%f", &productos.preciosPorCantidad[1]);

    printf("Tres bochas: ");
    scanf("%f", &productos.preciosPorCantidad[2]);

    printf("Cuarto: ");
    scanf("%f", &productos.preciosPorCantidad[3]);

    printf("Medio: ");
    scanf("%f", &productos.preciosPorCantidad[4]);

    printf("Kilo: ");
    scanf("%f", &productos.preciosPorCantidad[5]);
}

void guardarDatosTxtProductos()
{
    FILE* archivo = fopen("productos.txt", "w");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "tortas_heladas,precio_tortas_heladas,postres_helados,precio_postres_helados,"
            "dulce_de_leche_gramos,frutilla_gramos,crema_americana_gramos,chocolate_gramos,menta_granizada_gramos,"
            "una_bocha,dos_bochas,tres_bochas,cuarto,medio,kilo\n");

    fprintf(archivo, "%d,%.2f,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            productos.tortas_heladas,
            productos.precio_tortas_heladas,
            productos.postres_helados,
            productos.precio_postres_helados,
            productos.saboresKGramos[0],
            productos.saboresKGramos[1],
            productos.saboresKGramos[2],
            productos.saboresKGramos[3],
            productos.saboresKGramos[4],
            productos.preciosPorCantidad[0],
            productos.preciosPorCantidad[1],
            productos.preciosPorCantidad[2],
            productos.preciosPorCantidad[3],
            productos.preciosPorCantidad[4],
            productos.preciosPorCantidad[5]);

    fclose(archivo);
    printf("Datos guardados en productos.txt\n");
}

void listarDatos()
{
    FILE* archivo = fopen(ProductosHeladeria, "rt");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera

    while (fscanf(archivo, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &productos.tortas_heladas,
                  &productos.precio_tortas_heladas,
                  &productos.postres_helados,
                  &productos.precio_postres_helados,
                  &productos.saboresKGramos[0],
                  &productos.saboresKGramos[1],
                  &productos.saboresKGramos[2],
                  &productos.saboresKGramos[3],
                  &productos.saboresKGramos[4],
                  &productos.preciosPorCantidad[0],
                  &productos.preciosPorCantidad[1],
                  &productos.preciosPorCantidad[2],
                  &productos.preciosPorCantidad[3],
                  &productos.preciosPorCantidad[4],
                  &productos.preciosPorCantidad[5]) != EOF)
    {
        printf("1)Tortas Heladas: %d\n", productos.tortas_heladas);
        printf("2)Precio Tortas Heladas: %.2f\n", productos.precio_tortas_heladas);
        printf("3)Postres Helados: %d\n", productos.postres_helados);
        printf("4)Precio Postres Helados: %.2f\n", productos.precio_postres_helados);
        printf("Sabores Gramos:\n");
        printf("5)  Dulce de leche: %.2f\n", productos.saboresKGramos[0]);
        printf("6)  Frutilla: %.2f\n", productos.saboresKGramos[1]);
        printf("7)  Crema americana: %.2f\n", productos.saboresKGramos[2]);
        printf("8)  Chocolate: %.2f\n", productos.saboresKGramos[3]);
        printf("9)  Menta granizada: %.2f\n", productos.saboresKGramos[4]);
        printf("Precios por Cantidad:\n");
        printf("10)  Una bocha: %.2f\n", productos.preciosPorCantidad[0]);
        printf("11)  Dos bochas: %.2f\n", productos.preciosPorCantidad[1]);
        printf("12)  Tres bochas: %.2f\n", productos.preciosPorCantidad[2]);
        printf("13)  Cuarto: %.2f\n", productos.preciosPorCantidad[3]);
        printf("14)  Medio: %.2f\n", productos.preciosPorCantidad[4]);
        printf("15)  Kilo: %.2f\n", productos.preciosPorCantidad[5]);
    }

    fclose(archivo);
}
void realizarPedido()
{

    int producto, cantidad;
    float nuevo_precio, cantidad_suelto;
    char continuar;
    TDatosCuentaAdminYCajero datos;
    listarDatos(); // Llama a la función listarDatosProductos para mostrar los productos y sus precios actuales

    do
    {
        printf("Seleccione el número del producto que desea incrementar o el precio que desea cambiar (Tener en cuenta cual corresponde a cada caso):\n");
        fflush(stdin);
        scanf("%d", &producto);

        switch (producto)
        {
        case 1:
            printf("Cantidad a agregar de Tortas Heladas: ");
            fflush(stdin);
            scanf("%d", &cantidad);
            productos.tortas_heladas += cantidad;
            break;
        case 2:
            printf("Nuevo precio de cada Torta Helada: ");
            fflush(stdin);
            scanf("%f",&nuevo_precio);
            productos.precio_tortas_heladas = nuevo_precio;
            break;
        case 3:
            printf("Cantidad a agregar de Postres Helados: ");
            fflush(stdin);
            scanf("%d", &cantidad);
            productos.postres_helados += cantidad;
            break;
        case 4:
            printf("Nuevo precio de cada Postre Helado: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.precio_postres_helados = nuevo_precio;
            break;
        case 5:
            printf("Cantidad a agregar de Dulce de leche (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidad_suelto);
            productos.saboresKGramos[0] += cantidad_suelto;
            break;
        case 6:
            printf("Cantidad a agregar de Frutilla (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidad_suelto);
            productos.saboresKGramos[1] += cantidad_suelto;
            break;
        case 7:
            printf("Cantidad a agregar de Crema americana (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidad_suelto);
            productos.saboresKGramos[2] += cantidad_suelto;
            break;
        case 8:
            printf("Cantidad a agregar de Chocolate (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidad_suelto);
            productos.saboresKGramos[3] += cantidad_suelto;
            break;
        case 9:
            printf("Cantidad a agregar de Menta granizada (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidad_suelto);
            productos.saboresKGramos[4] += cantidad_suelto;
            break;
        case 10:
            printf("Nuevo precio de Producto 10: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[0] = nuevo_precio;
            break;
        case 11:
            printf("Nuevo precio de Producto 11: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[1] = nuevo_precio;
            break;
        case 12:
            printf("Nuevo precio de Producto 12: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[2] = nuevo_precio;
            break;
        case 13:
            printf("Nuevo precio de Producto 13: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[3] = nuevo_precio;
            break;
        case 14:
            printf("Nuevo precio de Producto 14: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[4] = nuevo_precio;
            break;
        case 15:
            printf("Nuevo precio de Producto 15: ");
            fflush(stdin);
            scanf("%f", &nuevo_precio);
            productos.preciosPorCantidad[5] = nuevo_precio;
            break;
        default:
            printf("Opción no válida.\n");
            break;
        }

        printf("¿Desea actualizar otro producto? (S/N): ");
        fflush(stdin);
        scanf(" %c", &continuar);
        continuar = toupper(continuar);
    }
    while (continuar == 'S');

    // Guardar los nuevos datos en el archivo
    guardarDatosTxtProductos();
    printf("Pedido realizado y datos actualizados.\n");
    menuAdmin(&datos);
}
void leerDatosProductos()
{
    FILE* archivo = fopen(ProductosHeladeria, "rt");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(archivo, "%d,%f,%*d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
           &productos.precio_tortas_heladas,
           &productos.precio_postres_helados,
           &productos.saboresKGramos[0],
           &productos.saboresKGramos[1],
           &productos.saboresKGramos[2],
           &productos.saboresKGramos[3],
           &productos.saboresKGramos[4],
           &productos.preciosPorCantidad[0],
           &productos.preciosPorCantidad[1],
           &productos.preciosPorCantidad[2],
           &productos.preciosPorCantidad[3],
           &productos.preciosPorCantidad[4],
           &productos.preciosPorCantidad[5]);

    fclose(archivo);
}
void mostrarInformacionProductosVentas()
{
    FILE* archivo = fopen(ProductosHeladeria, "rt");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera y descartarla

    float precios[6];
    fscanf(archivo, "%*d,%*f,%*d,%*f,%*f,%*f,%*f,%*f,%*f,%f,%f,%f,%f,%f,%f",
           &precios[0], &precios[1], &precios[2], &precios[3], &precios[4], &precios[5]);

    fclose(archivo);

    printf("1) Tortas Heladas\n");
    printf("2) Postres Helados\n");
    printf("Precios por cantidad:\n");
    printf("3) Una bocha: %.2f\n", precios[0]);
    printf("4) Dos bochas: %.2f\n", precios[1]);
    printf("5) Tres bochas: %.2f\n", precios[2]);
    printf("6) Cuarto: %.2f\n", precios[3]);
    printf("7) Medio kg: %.2f\n", precios[4]);
    printf("8) Kilo: %.2f\n", precios[5]);
}

void obtenerPedido()
{
    int producto, cantidad;
    float totalGastado = 0, bocha = 0.020, cuarto= 0.250;
    char continuar;
    int aux =0;
    mostrarInformacionProductosVentas(); // Mostrar productos y precios
    /*********/
    FILE* archivo = fopen(ProductosHeladeria, "rt");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera

    while (fscanf(archivo, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &productos.tortas_heladas,
                  &productos.precio_tortas_heladas,
                  &productos.postres_helados,
                  &productos.precio_postres_helados,
                  &productos.saboresKGramos[0],
                  &productos.saboresKGramos[1],
                  &productos.saboresKGramos[2],
                  &productos.saboresKGramos[3],
                  &productos.saboresKGramos[4],
                  &productos.preciosPorCantidad[0],
                  &productos.preciosPorCantidad[1],
                  &productos.preciosPorCantidad[2],
                  &productos.preciosPorCantidad[3],
                  &productos.preciosPorCantidad[4],
                  &productos.preciosPorCantidad[5]) != EOF)
    {
        do
        {

            printf("Seleccione el n mero del producto que desea incluir a su pedido:\n");
            scanf("%d", &producto);

            switch (producto)
            {
            // Casos para los productos
            case 1:
                printf("Ingrese la cantidad de Tortas Heladas que desea comprar:");
                fflush(stdin);
                scanf("%d",&cantidad);
                printf("%d",productos.tortas_heladas);
                if (productos.tortas_heladas >= cantidad)
                {
                    productos.tortas_heladas -= cantidad; // Actualizar inventario
                    totalGastado += cantidad * productos.precio_tortas_heladas;
                    printf("Producto agregado al pedido.\n");
                    strcpy(histoVentas.productosVendidos[aux],'Torta Helada');
                    histoVentas.cantProdVendidos[aux] += cantidad;
                    histoVentas.preciosProductos[aux] = productos.precio_tortas_heladas;
                    histoVentas.totalPrev[aux] = totalGastado;
                }
                else
                {
                    totalGastado += productos.tortas_heladas * productos.precio_tortas_heladas;
                    productos.tortas_heladas = 0;
                    printf("Se agot  el stock de Tortas Heladas. Se agregaron %d a su pedido\n",productos.tortas_heladas);
                }
                break;
            case 2:
                if (productos.precio_postres_helados >= cantidad)
                {
                    productos.precio_postres_helados -= cantidad; // Actualizar inventario
                    totalGastado += cantidad * productos.precio_postres_helados;
                    printf("Producto agregado al pedido.\n");
                }
                else
                {
                    totalGastado += productos.precio_postres_helados;
                    productos.postres_helados = 0;
                    printf("Se agot  el stock de postres Helados.\n");
                }
                break;
            case 3:
                printf("Selecciono un helado de una bocha: Elija un sabor\n");
                eleccion_sabor(bocha);
                totalGastado+=productos.preciosPorCantidad[0];
                break;
            case 4:
                printf("Selecciono un helado de dos bochas: Elija uno o dos sabor\n");

                eleccion_sabor(bocha*2);
                totalGastado+=productos.preciosPorCantidad[1];
                break;
            case 5:
                printf("Selecciono un helado de tres bochas: Elija un sabor\n");
                eleccion_sabor(bocha*3);
                totalGastado+=productos.preciosPorCantidad[2];
                break;
            case 6:
                printf("Selecciono un cuarto de helado: Elija un sabor\n");
                eleccion_sabor(cuarto);
                totalGastado+=productos.preciosPorCantidad[3];
                break;
            case 7:
                printf("Selecciono medio de helado: Elija un sabor\n");
                eleccion_sabor(cuarto*2);
                totalGastado+=productos.preciosPorCantidad[3];
                break;
            case 8:
                printf("Selecciono 1kg de helado: Elija un sabor\n");
                eleccion_sabor(cuarto*4);
                totalGastado+=productos.preciosPorCantidad[4];
                break;
            default:
                printf("Opcion no valida.\n");
                break;
            }
            guardarDatosTxtProductos();
            printf("Desea agregar otro producto al pedido? (S/N): ");
            scanf(" %c", &continuar);
            continuar = toupper(continuar);
            if('S'==continuar) {
                aux += 1;
            }
        }
        while (continuar == 'S');
        guardarVentas(continuar,aux);
    }
    fclose(archivo);
    printf("Total gastado en el pedido: %.2f\n", totalGastado);
}

void eleccion_sabor(double peso_a_restar)
{
    int opSabor;
    int veces_a_elegir;
    double peso_restante;
    peso_a_restar = round(peso_a_restar*1000)/1000;
    peso_restante =peso_a_restar;

    FILE* archivo = fopen(ProductosHeladeria, "rt");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera

    while (fscanf(archivo, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &productos.tortas_heladas,
                  &productos.precio_tortas_heladas,
                  &productos.postres_helados,
                  &productos.precio_postres_helados,
                  &productos.saboresKGramos[0],
                  &productos.saboresKGramos[1],
                  &productos.saboresKGramos[2],
                  &productos.saboresKGramos[3],
                  &productos.saboresKGramos[4],
                  &productos.preciosPorCantidad[0],
                  &productos.preciosPorCantidad[1],
                  &productos.preciosPorCantidad[2],
                  &productos.preciosPorCantidad[3],
                  &productos.preciosPorCantidad[4],
                  &productos.preciosPorCantidad[5]) != EOF)
    {

        // Calcular cuntas veces se puede elegir el sabor
        printf("PESO A RESTAR: %lf ",peso_a_restar);

        if (peso_a_restar == 0.020)
        {
            veces_a_elegir = 1;
        }
        else if (peso_a_restar == 0.040)
        {
            veces_a_elegir = 2;
        }
        else if (peso_a_restar == 0.060)
        {
            veces_a_elegir = 3;
        }
        else if (peso_a_restar == 0.250)
        {
            veces_a_elegir = 2;
        }
        else if (peso_a_restar == 0.500)
        {
            veces_a_elegir = 3;
        }
        else if (peso_a_restar == 1.000)
        {
            veces_a_elegir = 4;
        }
        else
        {
            printf("Peso no vlido\n");
            return;
        }
        int aux = veces_a_elegir;
        do
        {
            printf("1) Dulce de leche\n2) Frutilla\n3) Crema americana\n4) Chocolate\n5) Menta granizada\n");
            fflush(stdin);
            scanf("%d", &opSabor);

            switch (opSabor)
            {
            case 1:
                if(productos.saboresKGramos[0]>=peso_restante)
                {
                    productos.saboresKGramos[0] -= (peso_restante / aux);
                }
                else
                {
                    mostrar_mensaje_intermitente("No hay stock, redirigiendo...",1);
                    system("cls");
                    obtenerPedido();
                }

                break;
            case 2:
                if(productos.saboresKGramos[0]>=peso_restante)
                {
                    productos.saboresKGramos[0] -= (peso_restante / aux);
                }
                else
                {
                    mostrar_mensaje_intermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                productos.saboresKGramos[1] -= (peso_restante / aux);
                break;
            case 3:
                if(productos.saboresKGramos[0]>=peso_restante)
                {
                    productos.saboresKGramos[0] -= (peso_restante / aux);
                }
                else
                {
                    mostrar_mensaje_intermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            case 4:
                if(productos.saboresKGramos[0]>=peso_restante)
                {
                    productos.saboresKGramos[0] -= (peso_restante / aux);
                }
                else
                {
                    mostrar_mensaje_intermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            case 5:
                if(productos.saboresKGramos[0]>=peso_restante)
                {
                    productos.saboresKGramos[0] -= (peso_restante / aux);
                }
                else
                {
                    mostrar_mensaje_intermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            default:
                mostrar_mensaje_intermitente("Esta opcion no existe, redirigiendo...",2);
                system("cls");
                obtenerPedido();
                break;
            }

            veces_a_elegir--;
        }
        while (veces_a_elegir > 0);
    }
    fclose(archivo);
}


void mostrar_mensaje_intermitente(const char *mensaje, int duracion)
{
    int i;
    for (i = 0; i < duracion; i++)
    {
        printf("%s\r", mensaje);
        fflush(stdout);
        usleep(1000000); // Retraso de 1 segundos
    }
    printf("\n");
}

void guardarVentas(char continuar, int aux) {
    FILE *archivo = fopen(HistorialVentas, "at");
    if(!archivo)
        printf("Archivo no encontrado");
    for(int i = 0; i<aux; i++) {
    fprintf(archivo,"%d %s %d %f %f", histoVentas.id, histoVentas.productosVendidos[i],histoVentas.cantProdVendidos[i],histoVentas.preciosProductos[i], histoVentas.totalPrev[i]);
    }
    if('N'==continuar) {
        histoVentas.id += 1;
    }
    fclose(archivo);
}
