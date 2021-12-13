/*
Diego Abraham Riquelme
20.595.397-3
L-10
diego.riquelme.s@usach.cl
*/


/*Se importan las librerias necesarias para el funcionamiento del programa, por otro lado
se importan los headers previamente hechos.*/
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include"title.h"
#include"scrClean.h"

//Se crea el tipo de dato ubicacion como ubicacion.
typedef struct ubicacion ubicacion;



// estado mantiene posicion en el laberinto, además de la matriz que se genera.
struct ubicacion{
	int x;  // posicion x
	int y;  // posicion y
	int **matriz; //matrizGenerada
    // datos auxiliares
	int idEstado;
	int estadoAnterior;
	char * transicion; // nombre de la transicion
};

//Se crean las variables necesarias.
int correlativo;


// verificar si se puede hacer una transicion
int verificarN(ubicacion estado, int** m );
int verificarS(ubicacion estado, int** m, int sizeM);
int verificarE(ubicacion estado, int** m  );
int verificarO(ubicacion estado, int** m, int sizeM );

// efectuar transicion para crear estado
ubicacion norte(ubicacion estado,int tamanio);
ubicacion sur(ubicacion estado,int tamanio);
ubicacion este(ubicacion estado, int tamanio);
ubicacion oeste(ubicacion estado, int tamanio);

// verificar si es estado final
int esFinal(ubicacion b, int** m,int tamanio);

// funciones de cola

ubicacion * agregarEstado(ubicacion * lista, int * elementos, ubicacion estado);
ubicacion * sacarElemento(ubicacion * lista, int * elementos);
int estaEstado(ubicacion * lista, int elementos, ubicacion b, int tamanio);

// funciones utilitarias 
void imprimirEstado(ubicacion b);

// implementaciones

//La funcion crearEstado tiene como entrada x, e y, tambien el estado anterior, y la trnasicion, además de la matriz que
//se esta generando. Retorna el nuevo estado generado a partir de los datos ingresados.
ubicacion crearEstado(int x, int y, int anterior, char * t, int tamanio, int **nuevaMatriz){

	ubicacion nuevoEstado;

	nuevoEstado.y = y;
	nuevoEstado.x = x;

	nuevoEstado.matriz=(int**)malloc(sizeof(int*)*tamanio);


	for (int i = 0; i < tamanio; i++){
		nuevoEstado.matriz[i]=(int*)malloc(sizeof(int)*tamanio);
		for (int j = 0; j < tamanio; j++){
			
			nuevoEstado.matriz[i][j]=nuevaMatriz[i][j];
		}
		
	}
	
    // lo siguiente es generico con respecto a BEE.
	nuevoEstado.idEstado = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;


	return nuevoEstado;
}

// agrega estado a la lista de estados segun corresponde a abiertos o cerrados, retorna la lista nueva.
ubicacion * agregarEstado(ubicacion * lista, int * elementos, ubicacion estado){
	ubicacion * nuevaLista = (ubicacion *)malloc(sizeof(ubicacion)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

// Funciones propias de BEE

// verificar si se puede ir al este, lo mismo para las proximas funciones oeste, norte y sur.
// m es el mapa entregado
int verificarE(ubicacion e, int** m){
	if(e.y > 0 && (m[e.x][e.y-1])>e.matriz[e.x][e.y-1] && m[e.x][e.y-1]!=0 ) {
		return 1;
	}
	return 0;
}
//Se crea el estado este, y luego se avanza, lo mismo para las proximas funciones oeste, norte y sur.
ubicacion este(ubicacion estado, int tamanio){

	ubicacion nuevoEstado = crearEstado(estado.x,estado.y-1, estado.idEstado, "este",tamanio,estado.matriz);
	nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]=nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]+1;
	return nuevoEstado;
}


int verificarO(ubicacion e, int** m,int sizeM){
	
	if(e.y < sizeM-1 && (m[e.x][e.y+1])>e.matriz[e.x][e.y+1]  && m[e.x][e.y+1]!=0){
		return 1;
	}return 0;
}

ubicacion oeste(ubicacion estado,int tamanio){
	ubicacion nuevoEstado = crearEstado(estado.x,estado.y+1, estado.idEstado, "oeste",tamanio,estado.matriz);
	nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]=nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]+1;
	return nuevoEstado;
}

int verificarS(ubicacion e, int** m,int sizeM){
	
	if(e.x < sizeM-1 && (m[e.x+1][e.y])>e.matriz[e.x+1][e.y]&& m[e.x+1][e.y]!=0){
		return 1;
	}return 0;
}

ubicacion sur(ubicacion estado, int tamanio){
	ubicacion nuevoEstado = crearEstado(estado.x+1,estado.y, estado.idEstado, "sur",tamanio,estado.matriz);
	nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]=nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]+1;
	return nuevoEstado;
}

int verificarN(ubicacion e, int** m){
	
	if(e.x > 0 && (m[e.x-1][e.y])>e.matriz[e.x-1][e.y] && m[e.x-1][e.y]!=0 ){
		return 1;
	}return 0;
}

ubicacion norte(ubicacion estado, int tamanio){
	ubicacion nuevoEstado = crearEstado(estado.x-1,estado.y, estado.idEstado, "norte",tamanio,estado.matriz);
	nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]=nuevoEstado.matriz[nuevoEstado.x][nuevoEstado.y]+1;
	return nuevoEstado;
}





////////////////////////////////////////////////////////////////////////////////////////////////
// generica para BEE, salvo el tipo de datos.

//la funcion sacarElemento, nos permite sacar un elemento de la lista de abiertos, de esta forma, pasar los necesarios
//a los cerrados. Nos retorna la lista nueva.
ubicacion * sacarElemento(ubicacion * lista, int * elementos){
	ubicacion * nuevaLista = (ubicacion *)malloc(sizeof(ubicacion)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

// revisa si corresponde al estado final
int esFinal(ubicacion b, int** m,int tamanio){
	for (int i = 0; i < tamanio; i++)
	{	for (int j = 0; j < tamanio; j++){
			if(b.matriz[i][j] != m[i][j]){
				
				return 0;
			}
			
		}
	}
	return 1;
}


//La funcion isInMatrix nos permite saber si un elemento ya esta en la matriz o no.
//Nos retorna un 1 si es que si, o un 0 si es que no.
int isInMatrix(ubicacion lista, ubicacion b, int tamanio){
	int sumaTotal = tamanio*tamanio;
	int sumaFound = 0 ;
	for (int i = 0; i < tamanio; i++){
		for (int j = 0; j < tamanio; j++){
			if (lista.matriz[i][j] == b.matriz[i][j]){
				sumaFound++;
			}	
		}
	}

	if(sumaFound==sumaTotal) return 1;
	else return 0;

}

//Funcion que verifica que el estado generado no haya sido visitado.
int estaEstado(ubicacion * lista, int elementos, ubicacion b,int tamanio){

	for (int i = 0; i < elementos; ++i){
		if(isInMatrix(lista[i],b,tamanio)==1) return 1;
	}return 0;
}



/*Funcion que imprime la matriz a partir de cada cambio. Tiene como entrada la matriz, el tamanio de esta
y la seleccion del eje x e y*/
void imprimeMatriz(int **matriz, int tamanMatriz, int x, int y){
	
	//recorrido filas
	for (int j = 0; j < tamanMatriz; ++j){

		//recorrido columnas
		for (int i = 0; i < tamanMatriz; ++i){
			//seleccion del elemento que busca el usuario
			if (x==j && y==i){
					printf("[%d]", matriz[j][i]);
				}
			else printf(" %d ", matriz[j][i]);

		}


		printf("\n");
	}
}
/*la funcion verificaMatriz nos permite saber si es que la matriz esta en su estado final o no, es decir,
si esta esta conformada solo de 0s, si aun esta incompleta, retorna 0, si la matriz ya esta lista, retorna 1*/
int verificaMatriz(int **matriz,int tamanMatriz){
	int matrizLista=0;
	for (int i = 0; i < tamanMatriz; ++i){

		for (int j = 0; j < tamanMatriz; ++j){
			if (matriz[i][j]!=0){
				matrizLista=1;
			}
		}
	}
	return matrizLista;
}

//funcion LOGs permite llevar un registro de los eventos sucedidos, se invoca por cada evento.
void LOGs(char log[]){
    FILE *datosLogs;
    datosLogs= fopen("LOGS.out","a");
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char fechaHora[70];
    char *formato = "%Y-%m-%d %H:%M:%S";
    int escribeHora = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    strcat(fechaHora,"\t");
    strcat(fechaHora,log);
    strcat(fechaHora,"\n");
    fputs(fechaHora,datosLogs);
	
    fclose(datosLogs);

}
/*La funcion salidaOut nos permite guardar un string dentro de un archivo .out en este caso, tiene como entrada
el puntero del string, y no retorna nada al ser una funcion void*/

void salidaOut(char *buffer){
	FILE * salida;
	salida=fopen("Salida2.out","wt");
	fputs(buffer,salida);
	fclose(salida);
	printf("Guardado con exito!\n");
	char log[]="Guardado con exito!";
	LOGs(log);
}
/*Funcion que toma el ultimo digito de la primera posicion del array,
para saber desde donde partir en la funcion del recorrido. de esta forma, obtiene la posicion
del edificio que esta en la posicion mas superior derecha, tiene como entrada la matriz a trabajar, y retorna 
el indicie*/
int posicionFinal(int **matriz, int tamanMatriz){
	int indiceFinal=0;
	int i = tamanMatriz;
	while(i>0){
		if(matriz[0][i]!=0){
			if (indiceFinal==0)
			{
				indiceFinal=i;
			}
		}
		i=i-1;
	}
	return indiceFinal;
}


/*La funcion recorrido automatico tiene como entrada la matriz a trabajar, su tamanio, un char puntero con las direcciones que debe tomar, y el largo
de estas, tal y como lo dice su nombre, esta funcion nos permite visualizar el recorrido automatico entregado por BEE, tiene similitud fuerte con respecto
a la funcion recorridoMan, ya que en el fondo son la misma función pero con la adaptacion para el recorrido automatico. */

void recorridoAuto(int **matriz, int tamanMatriz, char * direcciones, int largoDirecciones){
	//creamos las posiciones iniciales para el eje x e y.
	int y=posicionFinal(matriz, tamanMatriz-1), x=0;
	//Primera posicion, hace referencia a si es la primera jugada en el tablero o no.
	int primeraPosicion=0;


	//verifica si es correcta la matriz.
	int verificacionMatriz;
	//creamos 2 char que nos permitan obtener y guardar las direcciones
	//N S E O
	char *direccion;
	char *buffer;
	
	//Se inicializa el buffer para poder obtener los datos de posicion.

	int i=largoDirecciones-1;
	//hacer calloc de 4024, para luego concatenar la direccion que me de el user.
	buffer=calloc(4024,sizeof(char));
	int exit=0;
	for (int i=largoDirecciones; i >=0; i--){
		printf("GENERANDO RECORRIDO AUTOMATICO . . .\n");
		imprimeMatriz(matriz,tamanMatriz,x,y);
		
		if (primeraPosicion==0)
		{
			matriz[x][y]=matriz[x][y]-1;
			primeraPosicion=primeraPosicion+1;
		}
		printf("DIRECCION -> [%c]\n",direcciones[i]);
		
		waitSec();
		scrClean();
				
		
		//Luego, dependiendo de la entrada del user, se selecciona la posicion, se verifica si es valida
		//de serlo, se guarda en el buffer, se elimina una pasada por la posicion, se cambia a la posicion siguiente
		//y se vuelve a preguntar por la seleccion.
		if (direcciones[i]=='w'){	
			x=x-1;
			y=y;
			matriz[x][y]=matriz[x][y]-1;
			direccion="N ";
			char log[]="direccion=N";
			LOGs(log);
			strcat(buffer,direccion);
			
			verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
			if (verificacionMatriz==0){
				printf("COMPLETADO!\n");
				char log[]="COMPLETADO!";
				LOGs(log);
				salidaOut(buffer);
				free(buffer);
				exit=1;
			}
		}
					
		if (direcciones[i]=='a'){	
			x=x;
			y=y-1;			
			matriz[x][y]=matriz[x][y]-1;
			direccion="E ";
			char log[]="direccion=E";
			LOGs(log);
			strcat(buffer,direccion);
			
			
			verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
			
			if (verificacionMatriz==0)
			{
				printf("COMPLETADO!\n");
				char log[]="COMPLETADO!";
				LOGs(log);
				salidaOut(buffer);
				free(buffer);
				exit=1;
			}
		}
				
		if (direcciones[i]=='s'){	
			x=x+1;
			y=y;
			matriz[x][y]=matriz[x][y]-1;
			direccion="S ";
			char log[]="direccion=S";
			LOGs(log);
			strcat(buffer,direccion);
			
			verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
			if (verificacionMatriz==0)
			{
				printf("COMPLETADO!\n");
				char log[]="COMPLETADO!";
				LOGs(log);
				salidaOut(buffer);
				free(buffer);
				exit=1;
			}
		}
			
		if (direcciones[i]=='d'){	
			x=x;
			y=y+1;
			matriz[x][y]=matriz[x][y]-1;
			direccion="O ";
			char log[]="direccion=O";
			LOGs(log);
			
			strcat(buffer,direccion);
			
			verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
			if (verificacionMatriz==0){
				printf("COMPLETADO!\n");
				char log[]="COMPLETADO!";
				LOGs(log);
				salidaOut(buffer);
				free(buffer);
				exit=1;
			}
		}
	
	}
}

// es generica salvo tipo, da paso a mostrar la solucion obtenida por BEE, no retorna nada.
void mostrarSolucion(ubicacion * lista, int ultimo, int ** matrizInicial, int tamanMatrizInicial){
	char * transiciones;
	char * continuar;
	transiciones = (char *)malloc(sizeof(char)*ultimo);
	
	int indice=0;
	printf("Direcciones a seguir: \n");
	while(lista[ultimo].idEstado != 0){
		if (strcmp(lista[ultimo].transicion,"norte")==0){
			transiciones[indice] ='w';
			
		}
		if (strcmp(lista[ultimo].transicion,"sur")==0){
			transiciones[indice] ='s';
		}
		if (strcmp(lista[ultimo].transicion,"este")==0){
			transiciones[indice] ='a';
		}
		if (strcmp(lista[ultimo].transicion,"oeste")==0){
			transiciones[indice] ='d';
		}
		
		indice++;
		ultimo = lista[ultimo].estadoAnterior;
	}
	
	recorridoAuto(matrizInicial,tamanMatrizInicial,transiciones,indice);
	printf("Las direcciones a seguir son: \n");

	for (int i = indice-1; i >=0; i--){
		if (transiciones[i]=='w'){
			printf("NORTE\n");
		}
		if (transiciones[i]=='s'){
			printf("SUR\n");
		}
	
		if (transiciones[i]=='d'){
			printf("ESTE\n");
		}
		if (transiciones[i]=='a'){
			printf("OESTE\n");
		}
	}
	printf("presione una tecla y enter para continuar. . . ");
	scanf("%s",continuar);
	scrClean();
	free(transiciones);
	
}





//funcion que captura la matriz del formato 2 de entrada, la trabaja sobre 
// un doble puntero para crear una matriz bidimensional, retorna la matriz.	
int **matrizObt(int **matriz, int tamanio, char nombreArchivo[]){
	int num;
	char dato;
	char charNum[255];
	FILE *dataFile;
	dataFile = fopen(nombreArchivo,"r");

	matriz=(int **)calloc(tamanio,sizeof(int *));
	for (int i = 0; i < tamanio; ++i){
		matriz[i]=(int *)calloc(tamanio,sizeof(int));}

	int i=0;
	int j=0,k=0;
	while (i<=tamanio) {
	 	fgets(charNum,100,dataFile);
 		if (i>0){
	 		j=0;
	 		for (int i = 0; i < tamanio*2; ++i){	
	 			dato=charNum[i];
	 			
	 			if (dato!=' '){
	 				num = (int) charNum[i]-48;
	 				if (num>=0){
	 					matriz[k][j]=num;
	 					j=j+1;}
	 				
	 				}	
	 			
	 		}
	 			k=k+1;}
	 	i=i+1;}
 	    return matriz;




}




/*La funcion atrapado permite buscar en cada posicion nueva si es que se quedara atrapado dentro de 0s
o no, tiene como entrada la matriz, la posicion (x,y), y el tamanio de la matriz, nos retorna 1 si no esta atrapado
y 0 si lo esta, lo que hace es por cada posicion que entra en X e Y, es preguntar hacia sus alrededores.*/
int atrapado(int **matriz,int x,int y, int tamanMatriz){

	int salida=1;

	if (x==0){

		if (y==0){
			if (matriz[x+1][y]==0 && matriz[x][y+1]==0){
				salida = 0;
				return salida;
				}
			}
		else{

			if (matriz[x+1][y]==0 && matriz[x][y+1]==0 && matriz[x][y-1]==0){
				salida=0;
				return salida;

			}
			
		}

		return salida;
	}


	if (x==(tamanMatriz-1)){
		if (y==(tamanMatriz-1)){
			if (matriz[x-1][y]==0 && matriz[x][y-1]==0){
				salida=0;
				return salida;
				}
			else return salida;
		}
		else{
			if (matriz[x-1][y]==0 && matriz[x][y-1]==0 && matriz[x][y+1]==0){
				salida=0;
				return salida;
			}
			else return salida;
		}
	}


	if (y==0){
		if (x==0){
			if (matriz[x+1][y]==0 && matriz[x][y+1]==0){
				salida=0;
				return salida;
				}
			else return salida;
			}
		else{
			if (matriz[x+1][y]==0 && matriz[x][y+1]==0 && matriz[x-1][y]==0){
				salida=0;
				return salida;
			}
			else return salida;
		}
	}


	if (y==(tamanMatriz-1)){
		if (x==(tamanMatriz-1)){
			if (matriz[x-1][y]==0 && matriz[x][y-1]==0){
				salida=0;
				return salida;
				}
			else return salida;
		}
		else{
			if (matriz[x-1][y]==0 && matriz[x][y-1]==0 && matriz[x+1][y]==0){
				salida=0;
				return salida;
			}
			else return salida;
		}
	}


	
	if (matriz[x+1][y]==0 && matriz[x-1][y]==0 && matriz[x][y+1]==0 && matriz[x][y-1]==0)
	{
		salida=0;
		return salida;
	}
	
	else {

		return salida;}

}



//La funcion randomPass tiene como entrada un puntero char, su funcion es generar una contrasenia
//aleatoria con el fin de utilizarla en el guardado del archivo. Nos retorna la contrasenia creada.

char* randomPass(char * password){
    //Generamos los arrays donde se obtendran los datos
    int i = 0;
    int randomizer = 0;
    char randomData[] = "0123456789abcdefghijklmnoqprstuvwyzxABCDEFGHIJKLMNOQPRSTUYWVZX";
  
    password = calloc(5,sizeof(char));
  
    // Se genera la semilla para la contraseña, a partir del tiempo.
    srand((unsigned int)(time(NULL)));
    //Se genera la contraseña.
    while (i <5){
		
        password[i]=randomData[rand() %61];
		i++;
        
    }
    return password;
}



/*La funcion saveMatrixData tiene como entrada un doble puntero matriz, el tamanio de esta, la ultima posicion en x e y, y un puntero char con 
el buffer creado, esta funcion nos permite generar el guardado de la partida "encriptado" bajo una contrasenia aleatoria, con el fin de que otros
jugadores no puedan jugar en el avance de la partida del user.*/
void saveMatrixData(int ** matriz,int tamanio,int x, int y, char * buffer){
	char *pass;
	FILE *saveFile = fopen("avance.sv","w");

    pass=randomPass(pass);
    
    fprintf(saveFile,"%d\n",tamanio);
    for (int i = 0; i < tamanio; i++)
    {
       for (int j = 0; j < tamanio; j++){
           if(j==(tamanio-1))fprintf(saveFile,"%d",matriz[i][j]);
           else fprintf(saveFile,"%d ",matriz[i][j]);
       }
       fprintf(saveFile,"\n");
       
    }
	fprintf(saveFile,"-\n");
    fprintf(saveFile,"%d\n",x);
    fprintf(saveFile,"%d\n",y);
    fprintf(saveFile,"%s\n",buffer);
	fprintf(saveFile,"#\n");
	fprintf(saveFile,"%s",pass);
	printf("Tu password para la proxima partida es:%s\nNO OLVIDES ANOTARLA!\n",pass);
	fclose(saveFile);
	
}


/*La funcion obtBuffer, nos permite obtener el buffer guardado en el archivo .sv, nos retorna
el puntero con el buffer, además pasamos por referencia las variables x e y, para poder obtener la posicion en 
que quedo el usuario*/
char * obtBuffer(char nombreArchivo[], int *x,int *y){
    int num;
	char dato;
	char charNum[255];
    char *buffer;
	FILE *dataFile;
	dataFile = fopen(nombreArchivo,"r");
    buffer=(char *)malloc(sizeof(buffer)*1024);
	int i=0;
    int ingresaBuffer=0;
    fgets(charNum,100,dataFile);
	while (charNum[0]!='#'){
 		fgets(charNum,100,dataFile);
 		if (charNum[0]=='-'){
             ingresaBuffer=1;
        }
        if (ingresaBuffer==1 && charNum[0]!='-'){
           if (i==0){
               num = charNum[0]-'0';
               *x=num;   
           }
           if (i==1){
                num = charNum[0]-'0';
                *y=num;
           }
           if (i==2){
               int j=0;
               while (charNum[j]!='\n'){
                   buffer[j]=charNum[j];
                   j++;
               }
           }
           i++;
        }
    }

    return buffer;

}
/*Funcion que nos entrega la contrasenia guardada en el archivo .sv para luego, saber si el user 
la conoce, retorna la contrasenia guardada.*/
char *passwordSave(char nombreArchivo[]){
	
	FILE *dataFile;
	char *password;
    password = (char *)malloc(sizeof(char)*6);
	dataFile = fopen(nombreArchivo,"r");
    int isPass=0;
    fgets(password,6,dataFile);
	
    while (feof(dataFile) == 0){
        fgets(password,6,dataFile);
		
        //if(strcmp(password,"#\n")==0){
		if(password[0]=='#'){
            isPass=1;
        }
        //if(isPass==1 && strcmp(password,"#\n")!=0){
		if(isPass==1 && password[0]!='#'){
			
			return password;}
    }
}



/*La funcion recorridoMan es una de las funciones principales, la cual funciona como eje central del recorrido manual, tiene
como entrada la matriz a recorrer, el tamanio de esta, y si se jugara una partida guardada o no, al ser void, no retorna nada.*/
void recorridoMan(int **matriz, int tamanMatriz,int lastGame){


	//creamos 2 char que nos permitan obtener y guardar las direcciones
	//N S E O
	char *direccion;
	char *buffer;
	int x;
	int y;
	int primeraPosicion=0;
	
	buffer=calloc(4024,sizeof(char));
	//Si es una partida nueva...
	if(lastGame==0){
		
		//creamos las posiciones iniciales para el eje x e y.
		y=posicionFinal(matriz, tamanMatriz-1);
		x=0;
		//Primera posicion, hace referencia a si es la primera jugada en el tablero o no.
		
		//Se inicializa el buffer para poder obtener los datos de posicion.
		//hacer calloc de 4024, para luego concatenar la direccion que me de el user.
		

	}
	//Si no es una partida nueva...
	else{
		
		char nombreArchivo[]="avance.sv";
		primeraPosicion=1;
		buffer=obtBuffer(nombreArchivo,&x,&y);

	}

	//Se crea un char array en entrada, para que en caso de que ocurran errores, poder recuperarlos.
	char entrada[255];
	//verifica la salida.
	int sinSalida;
	//verifica si es correcta la matriz.
	int verificacionMatriz;
	
	
	int i=0;
	int exit=0;

	while(exit!=1){

		imprimeMatriz(matriz,tamanMatriz,x,y);
		
		printf("-muevete con las teclas WASD- selecciona una dirección y luego enter\n(proTip con R puedes rendirte o con G guardar la partida):");
		
		scanf(" %s",entrada);
		while (strcmp(entrada,"w")!=0 &&strcmp(entrada,"d")!=0 &&strcmp(entrada,"s")!=0 &&strcmp(entrada,"a")!=0 &&strcmp(entrada,"r")!=0 &&strcmp(entrada,"g")!=0 )
		{	char log[]="INGRESA UNA ENTRADA VALIDA";
			LOGs(log);
			printf("INGRESA UNA ENTRADA VALIDA\n");
			printf("-muevete con las teclas WASD- selecciona una dirección y luego enter:");
			scanf(" %s",entrada);
		}

		if (primeraPosicion==0)
		{
			matriz[x][y]=matriz[x][y]-1;
			primeraPosicion=primeraPosicion+1;
		}

		scrClean();		
		
		//Luego, dependiendo de la entrada del user, se selecciona la posicion, se verifica si es valida
		//de serlo, se guarda en el buffer, se elimina una pasada por la posicion, se cambia a la posicion siguiente
		//y se vuelve a preguntar por la seleccion.
		if (strcmp(entrada,"r")==0){
			char waitForExit[255];
			free(buffer);
			printf("TE RENDISTE!!\n");
			char log[]="TE RENDISTE!!";
			LOGs(log);
			exit=1;
		}
		if (strcmp(entrada,"g")==0){
			char waitForExit[255];
			saveMatrixData(matriz,tamanMatriz,x,y,buffer);
			free(buffer);
			printf("Guardado con exito!\n");
			char log[]="Guardado con exito!";
			LOGs(log);
			exit=1;
			
		}




		if (strcmp(entrada,"w")==0){	
			x=x-1;
			y=y;
			if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
				if (matriz[x][y]==0){
					printf("HAY UN 0!\n");
					char log[]="HAY UN 0!";
					LOGs(log);
					x=x+1;
					y=y;
				}
				else{
					matriz[x][y]=matriz[x][y]-1;
					direccion="N ";
					char log[]="direccion=N";
					LOGs(log);
					strcat(buffer,direccion);
					i=i+1;
					verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
					if (verificacionMatriz==0)
					{
						printf("GANASTE!\n");
						char log[]="GANASTE!";
						LOGs(log);
						salidaOut(buffer);
						free(buffer);
						exit=1;
					}
					else{
						sinSalida=atrapado(matriz,x,y,tamanMatriz);
						if (sinSalida==0)
						{
							exit=1;
						}
					}
					
					
					
					}
				}
			else{	
				printf("FUERA DE LA MATRIZ! INTENTA NUEVAMENTE\n");
				char log[]="FUERA DE LA MATRIZ! INTENTA NUEVAMENTE";
				LOGs(log);
				x=x+1;
				y=y;
			}

		}



		if (strcmp(entrada,"a")==0){
			int test;	
			x=x;
			y=y-1;			
			if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
				if (matriz[x][y]==0){
					printf("HAY UN 0!\n");
					char log[]="HAY UN 0!";
					LOGs(log);
					x=x;
					y=y+1;
				}
				else{
				
				matriz[x][y]=matriz[x][y]-1;
				direccion="E ";
				char log[]="direccion=E";
				LOGs(log);
				strcat(buffer,direccion);
				i=i+1;
				
				verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
				
				if (verificacionMatriz==0)
				{
					printf("GANASTE!\n");
					char log[]="GANASTE!";
					LOGs(log);
					salidaOut(buffer);
					free(buffer);
					exit=1;
				}
				else{
					
					sinSalida=atrapado(matriz,x,y,tamanMatriz);
					if (sinSalida==0)
					{
						exit=1;
					}
				}	
				
				}
				}
			else{
				
				printf("FUERA DE LA MATRIZ! INTENTA NUEVAMENTE\n");
				char log[]="FUERA DE LA MATRIZ! INTENTA NUEVAMENTE";
				LOGs(log);
				x=x;
				y=y+1;
			}
			
			
		}
		if (strcmp(entrada,"s")==0){	
			x=x+1;
			y=y;

			if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
				if (matriz[x][y]==0){
					printf("HAY UN 0!\n");
					char log[]="HAY UN 0!";
					LOGs(log);
					x=x-1;
					y=y;
				}
				else{
					matriz[x][y]=matriz[x][y]-1;
					direccion="S ";
					char log[]="direccion=S";
					LOGs(log);
					strcat(buffer,direccion);
					i=i+1;
					verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
					if (verificacionMatriz==0)
					{
						printf("GANASTE!\n");
						char log[]="GANASTE!";
						LOGs(log);
						salidaOut(buffer);
						free(buffer);
						exit=1;
					}
					else{
						sinSalida=atrapado(matriz,x,y,tamanMatriz);
						if (sinSalida==0){
							exit=1;
						}}
					}
					}
			else{
				printf("FUERA DE LA MATRIZ! INTENTA NUEVAMENTE\n");
				char log[]="FUERA DE LA MATRIZ! INTENTA NUEVAMENTE";
				LOGs(log);
				x=x-1;
				y=y;
			}
			
		}
		if (strcmp(entrada,"d")==0){	
			x=x;
			y=y+1;
			if(x>=0 && y>=0 && x<tamanMatriz && y<tamanMatriz){
				if (matriz[x][y]==0){
					printf("HAY UN 0!\n");
					char log[]="HAY UN 0!";
					LOGs(log);
					x=x;
					y=y-1;
				}
				else{
					matriz[x][y]=matriz[x][y]-1;
					direccion="O ";
					char log[]="direccion=O";
					LOGs(log);
					
					strcat(buffer,direccion);
					i=i+1;
					verificacionMatriz=verificaMatriz(matriz,tamanMatriz);
					if (verificacionMatriz==0){
						printf("GANASTE!\n");
						char log[]="GANASTE!";
						LOGs(log);
						salidaOut(buffer);
						free(buffer);
						exit=1;
					}
					else{
						sinSalida=atrapado(matriz,x,y,tamanMatriz);
						if (sinSalida==0){
							exit=1;
						}}
				
			}}
			else{
				printf("FUERA DE LA MATRIZ! INTENTA NUEVAMENTE\n");
				char log[]="FUERA DE LA MATRIZ! INTENTA NUEVAMENTE";
				LOGs(log);
				x=x;
				y=y-1;
			}}
		


	}
	if (sinSalida==0){	
		free(buffer);
		printf("PERDISTE!!\n");
		char log[]="PERDISTE!!";
		LOGs(log);
	}

	
}



//funcion que nos entrega el tamanio de la matriz, retorna el tamanio, tiene como entrada un 
//array con el nombre del archivo a revisar, nos retorna el tamanio.
int matrixSize(char nombreArchivo[]){
	FILE *dataFile;
	char numero[3];
	dataFile = fopen(nombreArchivo,"r");
	fgets(numero,3,dataFile);
	int numeroInicial=atoi(numero);
	return numeroInicial;
}


/*Funcion driver de BEE, tiene como entrada el tamanio de la matriz, y un doble puntero de esta, nos permite generar la BEE en si,
de esta forma resolver la matriz, y de tener solucion, animarla. */
int BEE(int sizeM, int ** laberinto){
	//Doble puntero para la nueva Matriz.
	int **matrizEntrada;

	//
    //Genericas de BEE.
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	int **nuevaMatriz;
	///////////////////////
	//Nos permite obtener el primer numero desde donde parte.
	int masDerSup=posicionFinal(laberinto, sizeM-1);
	//Se crea la matriz donde se trabajara.
	nuevaMatriz=(int**)malloc(sizeof(int*)*sizeM);
	for (int i = 0; i < sizeM; i++) {	
		nuevaMatriz[i]=(int*)malloc(sizeof(int)*sizeM);
		for(int j = 0; j <sizeM; j++){
			if (i==0 && j==masDerSup){
				nuevaMatriz[i][j]=1;
			}
			else nuevaMatriz[i][j]=0;
		}
	}
	//Se imprime la matriz a trabajar.
	for (int x = 0; x <sizeM; x++)
	{
		for (int y = 0; y <sizeM; y++)
		{
			if (y==masDerSup && x==0)
			{
				printf("[%d]",laberinto[x][y]);
			}
			else printf(" %d ",laberinto[x][y]);
			
		}
		printf("\n");
		
	}
	
	


	///////////////////////////
	//Generacion de estados con los que se trabajara adelante.
	
	ubicacion bActual, bSiguiente;
	ubicacion * abiertos = (ubicacion *)malloc(sizeof(ubicacion)*canAbiertos);
	ubicacion * cerrados = (ubicacion *)malloc(sizeof(ubicacion)*canCerrados);
    // generar estado inicial
	
	ubicacion inicial = crearEstado(0,masDerSup, correlativo, "INICIO",sizeM,nuevaMatriz); // x=3,y=0
    
    //Se agrega el primer estado abierto.
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial);
	int encuentraSolucion = 0;
	while(canAbiertos > 0){ // mientras existan estado por revisar
		
		bActual = abiertos[0]; // obtengo el primer elemento de la cola
		
	
		//				
		abiertos = sacarElemento(abiertos, &canAbiertos); // elimino el primero
		cerrados = agregarEstado(cerrados, &canCerrados, bActual); // se deja en los visitados

		// ¿corresponde a un estado final?

		if(esFinal(bActual,laberinto,sizeM) == 1){
			mostrarSolucion(cerrados,canCerrados-1,laberinto,sizeM);
			encuentraSolucion = 1;
			return 0;

		}
		else{
			//De no serlo, se empiezan a verificar las opciones de la forma NOES como explica el pdf.
			if(verificarN(bActual,laberinto) == 1){ // puedo caminar al norte?
				
				bSiguiente = norte(bActual,sizeM); // entonces genero estado al norte
				
				// este estado no fue visitado?
				if((estaEstado(abiertos,canAbiertos,bSiguiente,sizeM) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente,sizeM) == 0)){ 
					
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
				else{
					//Si es que fue visitado, se libera la matriz generada, y su respectivo correlativo.

					correlativo = correlativo - 1;
					for (int i = 0; i < sizeM; i++){
						free(bSiguiente.matriz[i]);
					}
					free(bSiguiente.matriz);

				}
			}
			//Lo siguiente es generico con respecto a lo anteriormente explicado.
			//oeste
			if(verificarO(bActual,laberinto,sizeM) == 1){
			
				bSiguiente = oeste(bActual,sizeM);
				if((estaEstado(abiertos,canAbiertos,bSiguiente,sizeM) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente,sizeM) == 0)){
				
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
				else{
					correlativo = correlativo - 1;
					for (int i = 0; i < sizeM; i++){
						free(bSiguiente.matriz[i]);
					}
					free(bSiguiente.matriz);
				}
			}
			//este
			if(verificarE(bActual,laberinto) == 1){
				
			
				bSiguiente = este(bActual,sizeM);
				if((estaEstado(abiertos,canAbiertos,bSiguiente,sizeM) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente,sizeM) == 0)){
				
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
				else{
					correlativo = correlativo - 1;
					for (int i = 0; i < sizeM; i++){
						free(bSiguiente.matriz[i]);
					}
					free(bSiguiente.matriz);
				}
			} 
			//sur
			if(verificarS(bActual,laberinto,sizeM) == 1){
				
				bSiguiente = sur(bActual,sizeM);
				if((estaEstado(abiertos,canAbiertos,bSiguiente,sizeM) == 0) && (estaEstado(cerrados,canCerrados,bSiguiente,sizeM) == 0)){
					
					abiertos = agregarEstado(abiertos,&canAbiertos,bSiguiente);
				}
				else{
					correlativo = correlativo - 1;
					for (int i = 0; i < sizeM; i++){
						free(bSiguiente.matriz[i]);
					}
					free(bSiguiente.matriz);
				}
			}
		
		
			
		}
	

	}
	//Si no se encuentra solucion...
	if (encuentraSolucion==0){	
		printf("No se encontro una solucion para el mapa ingresado...\npresiona una tecla y enter para continuar");
		scanf("%d",&encuentraSolucion);
		scrClean();
	}
	return 0;
	
}


/*La funcion writeRowsCols tiene como entrada la matriz a trabajar, y su tamanio, al ser void no retorna nada, pero si escribe
un archivo de salida1.out, esta funcion nos permite obtener la forma de la Entrada1.*/
void writeRowsCols(int **matrizEntrada, int tamanio){
	
    FILE *datos;
    datos=fopen("Salida1.out","w");
    //Contador de cantidad de datos en las filas
    int contador[255];//* contador;
    for (int i = 0; i <tamanio; i++){
        int contadorInterno=0;
        for (int j = 0; j < tamanio; j++){
            if(matrizEntrada[i][j]!=0) contadorInterno++;
        }
        contador[i]=contadorInterno;
    }
    
    
    //////////////////////////////
    //Captura los numeros de las filas
    char numerosRows[2040]="";
    int k=0;
	char *numCharRow;
    for (int i = 0; i <tamanio; i++){
		k=0;
        numCharRow=calloc(255,sizeof(char));
        int esPrimero=0;
        for (int j = 0; j < tamanio; j++){
			
            if(matrizEntrada[i][j]!=0){
                char numConcat=matrizEntrada[i][j]+'0';
                if(esPrimero==0){
                    esPrimero = 1; 
                    numCharRow[k]=numConcat;
                    k++;
					}
                else{
                    numCharRow[k]=' ';
					k++;
                    numCharRow[k]=numConcat;
                    k++;}
            }
        }
        strcat(numerosRows,numCharRow);
        strcat(numerosRows,"\n");
        k++;
        
    }
    //////////////////////////////////////
    //Captura la informacion de las columnas
	
    char columnasInfo[255]="";    
    fprintf(datos,"%d\n",tamanio);
    int q=0;
	
    for (int i = 0; i < tamanio; i++){
        fprintf(datos,"%d ",contador[i]);
        while (numerosRows[q]!='\n'){
			
            fprintf(datos,"%c",numerosRows[q]);
            q++;
        }
        q++;
        fprintf(datos,"\n");
         
    }
	
   char *numCol;
    int contadorFinal=0;
    for(int i=0; i<tamanio;i++){
		int q=0;
        numCol=calloc(255,sizeof(char));
        int contadorCeros = 0;
        int primeraPosicion = 0;
        for (int j = 0; j < tamanio; j++){
            if (matrizEntrada[j][i]==0){
                contadorCeros++;
            }
            if (matrizEntrada[j][i]!=0){
                int iteradorInterior=0;
                int contadorInterno=0;
                iteradorInterior=j;
                
                while(matrizEntrada[iteradorInterior][i]!=0){
                   contadorInterno++;
                    if (iteradorInterior<tamanio-1){
                        iteradorInterior++;
                    }
                    else break;
                    
                }
               
                char numConcat=contadorInterno+'0';

                if(primeraPosicion!=0){
					
					numCol[q]='-';
					q++;
				}
                primeraPosicion=1;
			
                numCol[q]=numConcat;
				q++;
                
                j=iteradorInterior;
            
            }
        }
        
        
        if(contadorCeros==tamanio){
            strcat(columnasInfo,"0");
            strcat(columnasInfo,"\n");
            
        }
        else{
            strcat(columnasInfo,numCol);
            strcat(columnasInfo,"\n");
        } 
        
        
   }
	
    //Captura los numeros de las columnas
    char numerosCol[255]="";
	
   	char *numChar;
	int i=0;
    while (i <tamanio ){
		 k=0;
		
		
        numChar=calloc(255,sizeof(char));
        int esPrimero=0;
        for (int j = 0; j < tamanio; j++){
			
			
            if(matrizEntrada[j][i]!=0){
                char numConcat=matrizEntrada[j][i]+'0';
				int win=0;
				//En casos crossplataform, en caso de trabajar en Unix, se utiliza strok para
				//remover el salto de linea.
				#ifdef _WIN32
					win=0;
				#else
					win=1;
				#endif
				if(win==1)strtok(&numConcat,"\n");
                
			
				numChar[k]=numConcat;
				k++;
				numChar[k]=' ';
				k++;
            }
        }
        strcat(numerosCol," ");
        strcat(numerosCol,numChar);
        strcat(numerosCol,"\n");
        k++;
		i++;
        
    }
    q=0;
    int iter2=0;
    for (int i = 0; i < tamanio; i++){
        while (columnasInfo[q]!='\n'){
            fprintf(datos,"%c",columnasInfo[q]);
            q++;
        }
       
        while (numerosCol[iter2]!='\n'){
            fprintf(datos,"%c",numerosCol[iter2]);
            iter2++;
        }

        iter2++;
        q++;
        fprintf(datos,"\n");
         
    }
    fclose(datos);
}






//Funcion main, driver principal, empezamos a capturar datos, e invocamos las funciones necesarias.

int main(){

	//creacion de los archivos a trabajar.
	char nombreArchivo[255];
	int tamMatriz;
	int **matriz, i;
	int **matrizSalida;
	int salir=0;

	//limpiamos la consola antes de empezar.
	scrClean();
	char opt[255];
	int existeArch=0;
	while (salir==0){		
		
		
		//al seleccionar la OPT1 se despliega la funcion que 
		//abre los archivos
		int i=0;
		do{
			if (i>0){
				scrClean();
				char log[]="OPCION INCORRECTA!";
				LOGs(log);
				printf("OPCION INCORRECTA!\n");}
			//invocación desde title.h
			printSpider();
			printf("Elige una opcion: ");
			char log[]="Elige una opcion: ";
			LOGs(log);
			
			scanf("%s",opt);
			i++;
		} while (strcmp(opt,"1")!=0 && strcmp(opt,"2")!=0&&strcmp(opt,"3")!=0&&strcmp(opt,"4")!=0&&strcmp(opt,"5")!=0&&strcmp(opt,"6")!=0&&strcmp(opt,"7")!=0);
		i=0;
		scrClean();
		if (strcmp(opt,"1")==0 ){
			//Si es que no existe el archivo, o se abrio el archivo de guardado...
			if (existeArch==0 || strcmp(nombreArchivo,"avance.sv")==0)
			{	
				printf("Primero especifique archivo .in!\n");
				char log[]="Primero especifique archivo .in!";
				LOGs(log);
			}
			else{
				char log[]="OPCION 1";
				LOGs(log);
				
				//invocacion de tamanio matriz y la matriz obtenida.
				tamMatriz=matrixSize(nombreArchivo);
				matrizSalida=matrizObt(matriz,tamMatriz,nombreArchivo);

				
			
				//Se invoca la funcion de recorrido manual.
				recorridoMan(matrizSalida,tamMatriz,0);
			}

			
		}
		if(strcmp(opt,"2")==0){
			if (existeArch==0 || strcmp(nombreArchivo,"avance.sv")==0)
			{	
				printf("Primero especifique archivo .in!\n");
				char log[]="Primero especifique archivo .in!";
				LOGs(log);
			}
			else{
			printf("CARGANDO . . .\n");
			tamMatriz=matrixSize(nombreArchivo);
			matrizSalida=matrizObt(matriz,tamMatriz,nombreArchivo);
			char log[]="OPCION 2";
			LOGs(log);
			//Se invoca BEE.
			BEE(tamMatriz,matrizSalida);}


		}
		if (strcmp(opt,"3")==0 ){
			char log[]="OPCION 3";
			LOGs(log);
			FILE *file;
			printf("Ingrese nombre del archivo: ");
			scanf("%s",nombreArchivo);
			//Se pregunta por la existencia del archivo.
			if (file = fopen(nombreArchivo, "r")){
				fclose(file);
				printf("Archivo leido con exito!\n");
				char log[]="Archivo leido con exito!";
				LOGs(log);
				existeArch=1;
			}
			else
			{
				printf("El archivo no existe!\n");
				char log[]="El archivo no existe!";
				LOGs(log);
				existeArch=0;
			}
			

		}
		if (strcmp(opt,"4")==0 ){
			FILE *fileSV;
			char nombreArchivoGuard[]="avance.sv";
			//Se pregunta por la existencia del archivo.
			//Si existe, se proceden a invocar las funciones correspondientes del guardado.
			if (fileSV = fopen(nombreArchivoGuard, "r")){
				char log[]="OPCION 4";
				LOGs(log);
				char *passwordCmp;
				char passwordObt[255];
				passwordCmp = passwordSave(nombreArchivoGuard);
				printf("Ingresa la contrasenia: ");
				char log2[]="Ingresa la contrasenia: \n";
				LOGs(log2);
				scanf("%s",passwordObt);
				
				if (strcmp(passwordCmp,passwordObt)==0){
					
					//invocacion de tamanio matriz y la matriz obtenida.
					tamMatriz=matrixSize(nombreArchivoGuard);
					
					matrizSalida=matrizObt(matriz,tamMatriz,nombreArchivoGuard);
	
					
					//Se invoca la funcion de recorrido manual.
					recorridoMan(matrizSalida,tamMatriz,1);
					
				}
				else {
					printf("CONTRASENIA INCORRECTA!\n");
					char log[]="CONTRASENIA INCORRECTA!\n";
					LOGs(log);
				}
			}
			else {
				char log[]="NO HAY NINGUNA PARTIDA GUARDADA ANTERIORMENTE!\n";
				LOGs(log);
				printf("NO HAY NINGUNA PARTIDA GUARDADA ANTERIORMENTE!\n");}
	
	

			
		}
		/*Se exporta la entrada2 con la forma de la entrada1*/
		if(strcmp(opt,"5")==0){
			if (existeArch==0 || strcmp(nombreArchivo,"avance.sv")==0)
			{	
				printf("Primero especifique archivo .in!\n");
				char log[]="Primero especifique archivo .in!";
				LOGs(log);
			}
			else{
			tamMatriz=matrixSize(nombreArchivo);
			matrizSalida=matrizObt(matriz,tamMatriz,nombreArchivo);	
			
			writeRowsCols(matrizSalida,tamMatriz);
			char log[]="MATRIZ EXPORTADA AL FORMATO 1 CON EXITO!\n";
			LOGs(log);
				
			printf("MATRIZ EXPORTADA AL FORMATO 1 CON EXITO!\n");
			}


		}
		if (strcmp(opt,"6")==0 ){
			scrClean();
			char inputStop[255];
			char log[]="Acerca de";
			LOGs(log);
			char instruction[]="inst.art";
			exitArt(instruction);
			printf("Presiona una tecla y enter para continuar...");
			scanf("%s",inputStop);
			scrClean();
			
		}
		
		if (strcmp(opt,"7")==0 ){
			char log[]="FIN DEL PROGRAMA";
			LOGs(log);
			char exit[]="exitArt.art";
			exitArt(exit);
			salir=1;
		}
		

	}
	
	return 0;
}