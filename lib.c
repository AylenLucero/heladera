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

//menu que dirige a las diferentes pantallas
void menuPrincipal(TDatosCuentaAdminYCajero *datos)
{
    crearArchivoTxt(ProductosHeladeria);
    system("cls");
    int opPuesto = 0;
    int dniInput;
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
                printf("Ingrese su DNI:\n");
                fflush(stdin);
                scanf("%d",&dniInput);
                //si el dni existe redirigimos al login
                if(existeDni(ValoresCuentasCajero,dniInput)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    loginAdmin(ValoresCuentasCajero,dniInput);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El DNI no está registrado en la tabla administadores. Un administrador debe registrar la cuenta.\n");
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
                printf("Ingrese su DNI:\n");
                fflush(stdin);
                scanf("%d",&dniInput);
                //si el dni existe redirigimos al login
                if(existeDni(ValoresCuentasAdmin,dniInput)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    loginAdmin(ValoresCuentasAdmin,dniInput);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El dni no está registrado en la tabla administadores\n");
                    system("pause");
                    guardarAdmin(ValoresCuentasAdmin, dniInput, "Administrador");
                }
            }
            else
            {
                printf("Ingrese su DNI:\n");
                fflush(stdin);
                scanf("%d",&dniInput);
                system("pause");
                guardarAdmin(ValoresCuentasAdmin,dniInput, "Administrador");
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
    int dniInput;
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
            scanf("%d",&dniInput);
            //si el dni existe redirigimos al login
            if(existeDni(ValoresCuentasCajero,dniInput)==1)
            {
                //login..
                printf("Dni encontrado, este cajero ya posee una cuenta.\n");
                system("pause");
                menuAdmin(&datos);
            }
            else
            {
                //si no existe en la tabla lo llevamos al registro
                guardarAdmin(ValoresCuentasCajero, dniInput, "Cajero");
            }
            menuAdmin(&datos);
            break;
        case 2:
            printf("Ingrese su dni:\n");
            fflush(stdin);
            scanf("%d",&dniInput);
            system("pause");
            while(existeDni(ValoresCuentasCajero,dniInput)==1)
            {
                //login..
                printf("Dni encontrado, ingrese dni que no tenga cuenta\n");
                fflush(stdin);
                scanf("%d",&dniInput);
            }
            guardarAdmin(ValoresCuentasAdmin,dniInput, "Administrador");
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
            scanf("%d",&dniInput);
            eliminarAdminOCajero(ValoresCuentasAdmin,dniInput);
            menuAdmin(&datos);
            break;
        case 7:
            printf("Indique dni del Cajero a eliminar\n");
            fflush(stdin);
            scanf("%d",&dniInput);
            eliminarAdminOCajero(ValoresCuentasCajero,dniInput);
            menuAdmin(&datos);
            break;
        default:
            break;
        }
    }
    while (op<1 || op>6);
}
//Guardar los datos del Admin para el login
void guardarAdmin(char *nomArchivo, int dniInput, char *texto)
{
    if(existeDni(nomArchivo,dniInput)==0)//si el dni no está registrado, procedemos
    {
        TDatosCuentaAdminYCajero admin;
        FILE * archivo;
        archivo=fopen(nomArchivo,"ab");
        if(archivo!=NULL)
        {
            admin.dni = dniInput;

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
        loginAdmin(nomArchivo,dniInput);

    }
}

//evalua si existe, o no, un dni
int existeDni(char *ValoresCuentasAdmins,int dniInput)
{
    TDatosCuentaAdminYCajero admin;
    FILE * archivo = fopen(ValoresCuentasAdmins,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni==dniInput)
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

//funcion para el login
void loginAdmin(char *nomArchivo,int dniAdmin)
{
    TDatosCuentaAdminYCajero admin;
    char contrasenaInput[20];
    FILE *archivo = fopen(nomArchivo, "rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo))//mientras el puntero tenga para leer..
        {

            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni == dniAdmin)//coincide?
                {
                    printf("Ingrese su password:\n");
                    fflush(stdin);
                    gets(contrasenaInput);

                    //comparamos la contraseña ingresada con la guardada en ese registro
                    if(strcmp(contrasenaInput,admin.contrasena)==0)
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
//Funcion para eliminar un admin o un cajero. Se utiliza para ambos, comparten estructura
void eliminarAdminOCajero(char *nomArchivo,int dniInput)
{
    TDatosCuentaAdminYCajero cuenta;
    FILE *archivo = fopen(nomArchivo, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    char contrasenaInput[20];
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
            if(cuenta.dni!=dniInput)
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
                    gets(contrasenaInput);

                    if(strcmp(cuenta.contrasena,contrasenaInput)==0)
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
//Se utiliza solo al iniciar el sistema por primera vez
void pedirDatosProcutosInicio()
{
    printf("Ingrese la cantidad de tortas heladas: ");
    scanf("%d", &productos.tortasHeladas);

    printf("Ingrese el precio de las tortas heladas: ");
    scanf("%f", &productos.precioTortasHeladas);

    printf("Ingrese la cantidad de postres helados: ");
    scanf("%d", &productos.postresHelados);

    printf("Ingrese el precio de los postres helados: ");
    scanf("%f", &productos.precioPostresHelados);

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
//Guardar datos de los productos que hay en stock
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
            productos.tortasHeladas,
            productos.precioTortasHeladas,
            productos.postresHelados,
            productos.precioPostresHelados,
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
//Listar los datos de los productos, toda la estructura
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
                  &productos.tortasHeladas,
                  &productos.precioTortasHeladas,
                  &productos.postresHelados,
                  &productos.precioPostresHelados,
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
        printf("1)Tortas Heladas: %d\n", productos.tortasHeladas);
        printf("2)Precio Tortas Heladas: %.2f\n", productos.precioTortasHeladas);
        printf("3)Postres Helados: %d\n", productos.postresHelados);
        printf("4)Precio Postres Helados: %.2f\n", productos.precioPostresHelados);
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
//El Admin hace una compra y realiza este pedido
void realizarPedido()
{

    int producto, cantidad;
    float nuevoPrecio, cantidadSuelto;
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
            productos.tortasHeladas += cantidad;
            break;
        case 2:
            printf("Nuevo precio de cada Torta Helada: ");
            fflush(stdin);
            scanf("%f",&nuevoPrecio);
            productos.precioTortasHeladas = nuevoPrecio;
            break;
        case 3:
            printf("Cantidad a agregar de Postres Helados: ");
            fflush(stdin);
            scanf("%d", &cantidad);
            productos.postresHelados += cantidad;
            break;
        case 4:
            printf("Nuevo precio de cada Postre Helado: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.precioPostresHelados = nuevoPrecio;
            break;
        case 5:
            printf("Cantidad a agregar de Dulce de leche (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidadSuelto);
            productos.saboresKGramos[0] += cantidadSuelto;
            break;
        case 6:
            printf("Cantidad a agregar de Frutilla (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidadSuelto);
            productos.saboresKGramos[1] += cantidadSuelto;
            break;
        case 7:
            printf("Cantidad a agregar de Crema americana (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidadSuelto);
            productos.saboresKGramos[2] += cantidadSuelto;
            break;
        case 8:
            printf("Cantidad a agregar de Chocolate (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidadSuelto);
            productos.saboresKGramos[3] += cantidadSuelto;
            break;
        case 9:
            printf("Cantidad a agregar de Menta granizada (unicamente por KG): ");
            fflush(stdin);
            scanf("%f", &cantidadSuelto);
            productos.saboresKGramos[4] += cantidadSuelto;
            break;
        case 10:
            printf("Nuevo precio de Producto 10: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[0] = nuevoPrecio;
            break;
        case 11:
            printf("Nuevo precio de Producto 11: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[1] = nuevoPrecio;
            break;
        case 12:
            printf("Nuevo precio de Producto 12: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[2] = nuevoPrecio;
            break;
        case 13:
            printf("Nuevo precio de Producto 13: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[3] = nuevoPrecio;
            break;
        case 14:
            printf("Nuevo precio de Producto 14: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[4] = nuevoPrecio;
            break;
        case 15:
            printf("Nuevo precio de Producto 15: ");
            fflush(stdin);
            scanf("%f", &nuevoPrecio);
            productos.preciosPorCantidad[5] = nuevoPrecio;
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
//Lee los productos
void leerDatosProductos()
{
    FILE* archivo = fopen(ProductosHeladeria, "rt");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(archivo, "%d,%f,%*d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
           &productos.precioTortasHeladas,
           &productos.precioPostresHelados,
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
//Funcion realizada para mostrar los productos en un formato para que el cajero pueda usarlo para crear la venta
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
    THistorialVentas histoVentas;
    int producto, cantidad;
    float totalGastado = 0, bocha = 0.020, cuarto= 0.250;
    char continuar='S';
    int aux=0;
    char extension[3][40];
    extension[0][40]="precio_tortas_heladas";
    extension[1][40]="precio_postres_helados";
    extension[2][40]="preciosPorCantidad";

    mostrarInformacionProductosVentas(); // Mostrar productos y precios
    /***/
    FILE* archivo = fopen(ProductosHeladeria, "rt");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera

    while (fscanf(archivo, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &productos.tortasHeladas,
                  &productos.precioTortasHeladas,
                  &productos.postresHelados,
                  &productos.precioPostresHelados,
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

            printf("Seleccione el numero del producto que desea incluir a su pedido:\n");
            scanf("%d", &producto);
            cantidad=0;
            switch (producto)
            {
            // Casos para los productos
            case 1:
                printf("Ingrese la cantidad de Tortas Heladas que desea comprar:");
                fflush(stdin);
                scanf("%d",&cantidad);



                if (productos.tortasHeladas >= cantidad)
                {
                    productos.tortasHeladas -= cantidad; // Actualizar inventario

                    // printf("Producto agregado al pedido.\n");
                    // printf("AUX: %d\n",aux);
                    // strcpy(histoVentas.productosVendidos[aux],"Torta Helada");
                    // histoVentas.cantProdVendidos[aux] = cantidad;
                    // printf("CANT PROD ...:%d\n",histoVentas.cantProdVendidos[aux]);
                    // //precio por producto
                    // histoVentas.preciosProductos[aux] = productos.precio_tortas_heladas;

                    // histoVentas.totalPrev[aux] = histoVentas.cantProdVendidos[aux] * histoVentas.preciosProductos[aux];
                    // histoVentas.total+=histoVentas.totalPrev[aux];
                    levantarDatos(cantidad,&histoVentas, productos.precioTortasHeladas,aux,"TORTA HELADA");


                }
                else
                {
                    totalGastado += productos.tortasHeladas * productos.precioTortasHeladas;
                    productos.tortasHeladas = 0;
                    printf("Se agoto  el stock de Tortas Heladas. Se agregaron %d a su pedido\n",productos.tortasHeladas);
                }
                break;
            case 2:
                printf("Ingrese la cantidad de Postres Helados que desea comprar:");
                fflush(stdin);
                scanf("%d",&cantidad);
                if (productos.postresHelados >= cantidad)
                {
                    productos.precioPostresHelados -= cantidad; // Actualizar inventario
                    //totalGastado += cantidad * productos.precio_postres_helados;
                    levantarDatos(cantidad,&histoVentas, productos.precioPostresHelados,aux,"POSTRES HELADOS");
                    printf("Producto agregado al pedido.\n");
                }
                else
                {
                    totalGastado += productos.precioPostresHelados;
                    productos.postresHelados = 0;
                    printf("Se agoto  el stock de postres Helados.\n");
                }
                break;
            case 3:
                printf("Selecciono un helado de una bocha: Elija un sabor\n");
                eleccionSabor(bocha);
                totalGastado+=productos.preciosPorCantidad[0];
                break;
            case 4:
                printf("Selecciono un helado de dos bochas: Elija uno o dos sabor\n");

                eleccionSabor(bocha*2);
                totalGastado+=productos.preciosPorCantidad[1];
                break;
            case 5:
                printf("Selecciono un helado de tres bochas: Elija un sabor\n");
                eleccionSabor(bocha*3);
                totalGastado+=productos.preciosPorCantidad[2];
                break;
            case 6:
                printf("Selecciono un cuarto de helado: Elija un sabor\n");
                eleccionSabor(cuarto);
                totalGastado+=productos.preciosPorCantidad[3];
                break;
            case 7:
                printf("Selecciono medio de helado: Elija un sabor\n");
                eleccionSabor(cuarto*2);
                totalGastado+=productos.preciosPorCantidad[3];
                break;
            case 8:
                printf("Selecciono 1kg de helado: Elija un sabor\n");
                eleccionSabor(cuarto*4);
                totalGastado+=productos.preciosPorCantidad[4];
                break;

            default:
                printf("Opcion no valida.\n");
                break;
            }

            if(histoVentas.total!=0 && continuar=='S'){
                int idLeido;
                FILE *pointer = fopen("ventasId.txt", "rt");
                if(pointer){
                    if(fscanf(pointer, "%d", &idLeido)==1){
                        guardarVentas(idLeido+1, aux, histoVentas);
                        fclose(pointer);
                    }
                }
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

        //terminó la orden de compra
        if (histoVentas.total != 0) {
        int idLeido,ultimoId;
        FILE *pointer = fopen("ventasId.txt", "rt+");

        if (pointer != NULL) {
            // Leer el último ID y actualizar el archivo
            if (fscanf(pointer, "%d", &idLeido) == 1) {
                fseek(pointer, 0, SEEK_SET); // Moverse al principio del archivo
                fprintf(pointer, "%d\n", idLeido + 1); // Escribir el nuevo ID incrementado
                ultimoId=idLeido+1;
            } else {
                // Manejar el caso donde no se pudo leer el ID correctamente
                printf("Error al leer el ID desde ventasId.txt\n");
            }

            fclose(pointer);
        } else {
            // Manejar el caso donde no se pudo abrir el archivo
            perror("Error al abrir ventasId.txt");
        }
    }


    }
    fclose(archivo);
    printf("Total gastado en el pedido: %.2f\n", totalGastado);
}

void levantarDatos(int cantidad, THistorialVentas *histoVentas, float precios, int aux, char *nomProducto){
                        printf("Producto agregado al pedido.\n");
                        strcpy(histoVentas->productosVendidos[aux],nomProducto);
                        histoVentas->cantProdVendidos[aux] = cantidad;
                        printf("CANT PROD ...:%d\n",histoVentas->cantProdVendidos[aux]);
                        //precio por producto
                        histoVentas->preciosProductos[aux] = precios;
                        histoVentas->totalPrev[aux] = histoVentas->cantProdVendidos[aux] * histoVentas->preciosProductos[aux];
                        histoVentas->total+=histoVentas->totalPrev[aux];

                    }


void eleccionSabor(double pesoARestar)
{
    int opSabor;
    int vecesAElegir;
    double pesoRestante;
    pesoARestar = round(pesoARestar*1000)/1000;
    pesoRestante =pesoARestar;

    FILE* archivo = fopen(ProductosHeladeria, "rt");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    char cabecera[256];
    fgets(cabecera, sizeof(cabecera), archivo); // Leer la cabecera

    while (fscanf(archivo, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                  &productos.tortasHeladas,
                  &productos.precioTortasHeladas,
                  &productos.postresHelados,
                  &productos.precioPostresHelados,
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
        printf("PESO A RESTAR: %lf ",pesoARestar);

        if (pesoARestar == 0.020)
        {
            vecesAElegir = 1;
        }
        else if (pesoARestar == 0.040)
        {
            vecesAElegir = 2;
        }
        else if (pesoARestar == 0.060)
        {
            vecesAElegir = 3;
        }
        else if (pesoARestar == 0.250)
        {
            vecesAElegir = 2;
        }
        else if (pesoARestar == 0.500)
        {
            vecesAElegir = 3;
        }
        else if (pesoARestar == 1.000)
        {
            vecesAElegir = 4;
        }
        else
        {
            printf("Peso no vlido\n");
            return;
        }
        int aux = vecesAElegir;
        do
        {
            printf("1) Dulce de leche\n2) Frutilla\n3) Crema americana\n4) Chocolate\n5) Menta granizada\n");
            fflush(stdin);
            scanf("%d", &opSabor);

            switch (opSabor)
            {
            case 1:
                if(productos.saboresKGramos[0]>=pesoRestante)
                {
                    productos.saboresKGramos[0] -= (pesoRestante / aux);
                }
                else
                {
                    mostrarMensajeIntermitente("No hay stock, redirigiendo...",1);
                    system("cls");
                    obtenerPedido();
                }

                break;
            case 2:
                if(productos.saboresKGramos[0]>=pesoRestante)
                {
                    productos.saboresKGramos[0] -= (pesoRestante / aux);
                }
                else
                {
                    mostrarMensajeIntermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                productos.saboresKGramos[1] -= (pesoRestante / aux);
                break;
            case 3:
                if(productos.saboresKGramos[0]>=pesoRestante)
                {
                    productos.saboresKGramos[0] -= (pesoRestante / aux);
                }
                else
                {
                    mostrarMensajeIntermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            case 4:
                if(productos.saboresKGramos[0]>=pesoRestante)
                {
                    productos.saboresKGramos[0] -= (pesoRestante / aux);
                }
                else
                {
                    mostrarMensajeIntermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            case 5:
                if(productos.saboresKGramos[0]>=pesoRestante)
                {
                    productos.saboresKGramos[0] -= (pesoRestante / aux);
                }
                else
                {
                    mostrarMensajeIntermitente("No hay stock, redirigiendo...",2);
                    system("cls");
                    obtenerPedido();
                }
                break;
            default:
                mostrarMensajeIntermitente("Esta opcion no existe, redirigiendo...",2);
                system("cls");
                obtenerPedido();
                break;
            }

            vecesAElegir--;
        }
        while (vecesAElegir > 0);
    }
    fclose(archivo);
}


void mostrarMensajeIntermitente(const char *mensaje, int duracion)
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



void guardarVentas(int ultimoId, int aux, THistorialVentas histoVentas)
{
    printf("%d\n",histoVentas.cantProdVendidos[aux]);
    FILE *archivo = fopen(HistorialVentas, "at");
    histoVentas.id=ultimoId;
    if (archivo)
    {
        fprintf(archivo, "%d %s %d %.2f %.2f %.2f\n", histoVentas.id, histoVentas.productosVendidos[aux], histoVentas.cantProdVendidos[aux], histoVentas.preciosProductos[aux], histoVentas.totalPrev[aux], histoVentas.total);

        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo %s\n",HistorialVentas);
    }
}


