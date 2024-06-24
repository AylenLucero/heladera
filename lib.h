#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
typedef struct DatosCuentaAdmin { //Estructura datos de cuenta de administradores
    int dni;
    char contrasena[20];
} TDatosCuentaAdminYCajero;
/**************************/
typedef struct PreciosVenta {
    float una_bocha;
    float dos_bochas;
    float tres_bochas;
    float cuarto;
    float medio;
    float kilo;
}TPreciosVentas;
typedef struct SaboresPorKilo {
    float dulce_de_leche_gramos;
    float frutilla_gramos;
    float crema_americana_gramos;
    float chocolate_gramos;
    float menta_granizada_gramos;
}TSaboresPorKilo;
typedef struct Productos {
    int tortas_heladas;
    float precio_tortas_heladas;
    int postres_helados;
    float precio_postres_helados;
    /*TSaboresPalitosHelados palitos_helados;*/
    TSaboresPorKilo saboresGramos;
    TPreciosVentas preciosVentas;
}TProductos;
/**************************/

void menuPrincipal();
void crearArchivoBinario(char *nombreArchivoBinario);
int archivoEstaVacio(char *nombreArchivo);

void leerArchivoBinarioInicioSesion(char *nombreArchivoBinario, char *puesto);
void menuAdmin(TDatosCuentaAdminYCajero *datos);
void menuCajero();
void guardarDatos();
int existe_dni(char *ValoresCuentasAdmin,int dni_input);
void login_admin(char *ValoresCuentasAdmin,int dni_admin);
void guardar_admin(char *nomArchivo, int dni_input, char texto);
void eliminar_admin(int dni_input);
void listar_admins();

void cargar_stock_inicio();

#endif // LIB_H_INCLUDED
