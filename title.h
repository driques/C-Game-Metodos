//El siguiente Header nos permite guardar la informacion de los datos que se muestan por pantalla
//se definen los datos correspondientes, y los diferentes cambios de color para la consola.
#ifndef _TITLE
#define _TITLE
#include <stdio.h>
 
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//titulo
void printSpider(){
	printf(ANSI_COLOR_RED);
	printf("                   ,,,, \n");
	printf("             ,;) .';;;;',\n");
	printf(" ;;,,_,-.-.,;;'_,|I\\;;;/),,_\n");
	printf("  `';;/:|:);{ ;;;|| \\;/ /;;;\\__\n");
	printf("      L;/-';/ \\;;\',/;\\/;;;.') \\\n");
	printf("      .:`''` - \\;;'.__/;;;/  . _'-.\n");
	printf("    .'/   \\     \\;;;;;;/.'_7:.  '). \\_\n");
	printf("  .''/     | '._ );}{;//.'    '-:  '.,L\n");
	printf(".'. /       \\  ( |;;;/_/         \\._./;\\   _,\n");
	printf(" . /        |\\ ( /;;/_/             ';;;\\,;;_,\n");
	printf(". /         )__(/;;/_/                (;;'''''\n");
	printf(" /        _;:':;;;;:';-._             );\n");
	printf("/        /   \\  `'`   --.'-._         \\/\n");
	printf("       .'     '.  ,'         '-,\n");
	printf("      /    /   r--,..__       '.\\\n");
	printf("    .'    '  .'        '--._     ]\n");
	printf(ANSI_COLOR_RED"--------VENCIENDO A KINGPIN--------\n"ANSI_COLOR_RED);
	printf("\n\n\n");
	printf(ANSI_COLOR_BLUE"1) RECORRIDO MANUAL\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_BLUE"2) RECORRIDO AUTOMATICO\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_BLUE"3) SELECCIONAR ARCHIVO DE ENTRADA\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_BLUE"4) PARTIDA GUARDADA\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_BLUE"5) EXPORTAR ARCHIVOS\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_BLUE"6) INSTRUCCIONES\n"ANSI_COLOR_BLUE);
	printf(ANSI_COLOR_RED"7) SALIR\n"ANSI_COLOR_RED);
	printf(ANSI_COLOR_BLUE);

	


	return;
}

//Toma un archivo con extensión .art para poder representarlo a través de la terminal
//de esta forma, se ahorra el tener que imprimir varias lineas a la vez, y modificar alguna
//forma ascii
void exitArt (char art[]){
   printf(ANSI_COLOR_CYAN);
   FILE *fichero;
   char c;
   fichero = fopen (art,"rb");
   if (!fichero) {
      fclose (fichero);
      printf ("No se encuentra el fichero .art");
      return;
	  printf(ANSI_COLOR_BLUE);
   }

/* El siguiente bucle lee caracteres uno a uno y los imprime en pantalla. */
   while (!feof (fichero)) {
      c = getc (fichero);
      printf ("%c", c);
   }
	printf("\n");	
   fclose (fichero);
   return ;
   printf(ANSI_COLOR_BLUE);
}

#endif




