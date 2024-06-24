#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
typedef struct DatosCuentaAdmin { //Estructura datos de cuenta de administradores
    int dni;
    char contrasena[20];
} TDatosCuentaAdmin;

typedef struct DatosCuentaCajeros { //Estructura datos de cuenta de cajeros
    int codUnico;
    char contrasena[20];
} TDatosCuentaCajeros;

void menuPrincipal();
void crearArchivoBinario(char *nombreArchivoBinario);
int archivoEstaVacio(char *nombreArchivo);

void leerArchivoBinarioInicioSesion(char *nombreArchivoBinario, char *puesto);
void menuAdmin(TDatosCuentaAdmin *datos);
void guardarDatos();
int existe_dni(char ValoresCuentasAdmin,int dni_input);
void login_admin(char ValoresCuentasAdmin,int dni_admin);
void guardar_admin(char *nomArchivo, int dni_input);
void eliminar_admin(int dni_input);
void listar_admins();

#endif // LIB_H_INCLUDED
