getenv --> getenv(char * del nombre de la variable de entorno) p.e -> getenv("PATH") devuelve la el valor de la variable en un char *
chdir --> chdir(char * de la ruta donde quieres cambiar el working directory) p.e -> chdir("..") y cambia al directorio que tienes antes
getcwd --> getcwd(char * de la ruta actual, size del length de la ruta absoluta) p.e -> devuelve NULL si no se encutra el path o en cwd se almacena la ruta
