//Proyecto en C, es un inventario de una tienda departamental para su administración.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Para nombres de archivos
#define NARCHIVO "ventas.txt"
#define NCOMPRAS "compras.txt"
//Estructura de articulos.
typedef struct articulos{
	char *nombre;
	float precio;
	int inventario;
}articulo;
//Estructura de departamentos.
struct deptos{
	articulo *a;
	char *nombreD;
	int tamanio;
	int tamanioD;
	float perdida;
	float ganancia;
	char **ArtVend;
	int conv;
};
//Llamadas de las funciones.
struct deptos * nombreDeptos(struct deptos *d);
void muestraDeptos(struct deptos *d,int N);
struct deptos * datosArticulos(struct deptos *d,int N);
void muestraArticulos(struct deptos *d,int nDep);
struct deptos * agregarDeptos(struct deptos*d);
struct deptos * removerArticulo(struct deptos *d,int nd,int na);
struct deptos * comprarArticulo(struct deptos *d,int nd,int na);
struct deptos * venderArticulo(struct deptos *d,int nd,int na);
struct deptos * modificarArticulo(struct deptos *d ,int nd ,int na);
struct deptos * agregarArticulo(struct deptos *d,int nd);
float gananciasTotales(struct deptos *d);
float perdidasTotales(struct deptos *d);

int main()
{
	int N=5,opcion,nDep,nArt,i=0,j,piezas,piezasc;
	float ganancias,perdidas;
	FILE  *f, *fc;
	//Apuntadores de archivo y abriendo archivos.
	f=fopen(NARCHIVO,"wt");
	fc=fopen(NCOMPRAS,"wt");
	fprintf(f,"Productos vendidos\tPiezas\n");
	fprintf(fc,"Productos comprados\tPiezas\n");
	//Memoria para los N dpt
	struct deptos *d=(struct deptos*)malloc(sizeof(struct deptos)*N);
	//Describiendo Dpt y articulos de estos.
	d=nombreDeptos(d);
	d=datosArticulos(d,5);
	//Memoria para art vendidos
	for(i=0;i<5;i++)
	{
		d[i].ArtVend=(char**)malloc(sizeof(char*));
		d[i].ArtVend[0]=(char*)malloc(sizeof(char)*100);
		d[i].conv=0;
	}
	//MENU 
	do{
		printf("\nQue desea hacer:\n1)Agregar Departamento\n2)Mostrar elementos departamento\n3)Modificar articulos\n4)Eliminar elementos\n5)Comprar articulos\n6)Vender articulos\n7)Importar productos de archivo\n8)Agregar Articulos\n9)Salir\n");
		scanf("%d",&opcion);
		getchar();
		switch(opcion){ //switch case para las opciones. Falta añadir la función de los archivos en el caso 7. Hay que hacerlas a prueba de idiotas por si acaso.
			case 1:
				//Agragando mem. par ArtV si se crean mas departamentos
				d=agregarDeptos(d);
				d[d[0].tamanioD-1].conv=0;
				d[d[0].tamanioD-1].ArtVend=(char**)malloc(sizeof(char*));
				d[d[0].tamanioD-1].ArtVend[0]=(char*)malloc(sizeof(char)*100);
				break;
			case 2:
				printf("Que departamento quiere ver:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0){
					muestraArticulos(d,nDep);					
				}
				else
					printf("\nDepartamento incorrecto");
				break;
			case 3:
				printf("De que departamento quiere modificar:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0)
				{
					printf("Qué articulo desea modificar:  ");
					muestraArticulos(d,nDep);
					scanf("%d",&nArt);
					getchar();
					if(nArt<=d[nDep-1].tamanio && nArt>0)
					{
						d=modificarArticulo(d,nDep,nArt);
					}
					else
						printf("\nArticulo incorrecto");						
				}
				else
					printf("\nDepartamento incorrecto");
				break;
			case 4:
				printf("\nDe que departamento quiere eliminar:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0)
				{
					printf("\nQué articulo desea eliminar, si no hay articulos presione 0:  ");
					muestraArticulos(d,nDep);
					scanf("%d",&nArt);
					getchar();
					if(nArt<=d[nDep-1].tamanio && nArt>0)
					{
						d=removerArticulo(d,nDep,nArt);
					}
					else
						printf("\nArticulo incorrecto");						
				}
				else
					printf("\nDepartamento incorrecto");
				break;	
			case 5:
				printf("\nDe que departamento quiere comprar:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0)
				{
					printf("\nQué articulo desea comprar, si no hay articulos presione 0:  ");
					muestraArticulos(d,nDep);
					scanf("%d",&nArt);
					getchar();
					if(nArt<=d[nDep-1].tamanio && nArt>0)
					{
						piezasc=d[nDep-1].a[nArt-1].inventario;
						d=comprarArticulo(d,nDep,nArt);
						piezasc=d[nDep-1].a[nArt-1].inventario-piezasc;
						if(piezasc!=d[nDep-1].a[nArt-1].inventario)
							fprintf(fc,"%s\t   %d\n",d[nDep-1].a[nArt-1].nombre,piezasc);
					}
					else
						printf("\nArticulo incorrecto");						
				}
				else
					printf("\nDepartamento incorrecto");				
				break;
			case 6:

				printf("\nDe que departamento quiere vender:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0)
				{
					printf("\nQué articulo desea vender:  ");
					muestraArticulos(d,nDep);
					scanf("%d",&nArt);
					getchar();
					if(nArt<=d[nDep-1].tamanio && nArt>0)
					{
						piezas=d[nDep-1].a[nArt-1].inventario;
						d=venderArticulo(d,nDep,nArt);
						piezas-=d[nDep-1].a[nArt-1].inventario;
						if(piezas!=0){
							fprintf(f,"%s\t    %d\n",d[nDep-1].a[nArt-1].nombre,piezas);
							d[nDep-1].conv++;
							printf("\nJalando...");
							d[nDep-1].ArtVend=(char**)realloc(d[nDep-1].ArtVend,sizeof(char*)*d[nDep-1].conv);
							d[nDep-1].ArtVend[d[nDep-1].conv-1]=(char*)realloc(d[nDep-1].ArtVend[100],strlen(d[nDep-1].a[nArt-1].nombre));
							strcpy(d[nDep-1].ArtVend[d[nDep-1].conv-1],d[nDep-1].a[nArt-1].nombre);
						}
					}
					else
						printf("\nArticulo incorrecto");						
				}
				else
					printf("\nDepartamento incorrecto");	
				break;	
			case 8:
				printf("\nA que departamento le quiere agregar articulos:  ");
				muestraDeptos(d,d[0].tamanioD);
				scanf("%d",&nDep);
				getchar();
				if(nDep<=d[0].tamanioD && nDep>0){
					d=agregarArticulo(d,nDep);						
				}
				else
					printf("\nDepartamento incorrecto");
				break;		
			case 9:
				opcion=9;
				break;
			default:
			 	printf("\nOpcion incorrecta");
			 	break;
		}
	}while(opcion!=9);
	//Ganancias y perdidas para finalizar despues de todo el proceso
	ganancias=gananciasTotales(d);
	perdidas=perdidasTotales(d);
	//Escribir en archivos
	for(i=0;i<d[0].tamanioD;i++)
	{
		for(j=0;j<d[i].conv;j++)
		{
			printf("\nArticulos vendidos: %s\n",d[i].ArtVend[j]);
		}
	}
	fprintf(f,"Ganancias Totales:  %f",ganancias);
	fprintf(fc,"Perdidas totales:  %f",perdidas);
	fclose(f);
	fclose(fc);
	free(d->a);
	free(d);
	return 0;
}

//Función para nombrar los departamentos.
struct deptos * nombreDeptos(struct deptos *d)
{
	int i;
	char *aux=(char*)malloc(sizeof(char)*100);
	d=(struct deptos *)malloc(sizeof(struct deptos)*5);
	for(i=0;i<5;i++){
		printf("\nDepartamento %d:  ",i+1);
		//fgets(aux,30,stdin);
		scanf("%[^\n]",aux);
		getchar();
		d[i].nombreD=(char*)malloc(strlen(aux)+1);
		memcpy(d[i].nombreD,aux,strlen(aux)+1);
		d[0].tamanioD++;
	}
	free(aux);
	return d;
}
//Funciones que imprimer los departamentos ingresados
void muestraDeptos(struct deptos *d,int N)
{
	int i;
	for(i=0;i<N;i++){
		printf("\nDepartamento %d ->  %s",i+1,d[i].nombreD);
	}	
	printf("\n");
}
//Función que permite íntroducir los datos de los artículos. Se puede cambiar el nombre del artículo, el precio y la cantidad de piezas en el inventario.
struct deptos * datosArticulos(struct deptos *d,int N)
{
	int i,j, M=0;
	int respuesta;
	char *aux=(char*)malloc(sizeof(char)*100); //apuntador auxiliar para el manejo de memoria.
	d->a=(articulo*)malloc(sizeof(articulo)*1);
	for(i=0;i<N;i++){
		printf("\nDepartamento %s",d[i].nombreD);
		respuesta=0;
		j=0;
		M=0;
		while(respuesta!=1){
			d[i].tamanio++;
			M++;
			d[i].a=(articulo*)realloc(d[i].a,sizeof(articulo)*M);
			printf("\nArticulo %d:   ",j+1);
			//fgets(d[i].a[j].nombre,30,stdin);
			scanf("%[^\n]",aux);
			getchar();
			d[i].a[j].nombre=(char*)malloc(strlen(aux)+1);
			memcpy(d[i].a[j].nombre,aux,strlen(aux)+1);
			printf("\nPrecio %s:  ",d[i].a[j].nombre);
			scanf("%f",&d[i].a[j].precio);
			getchar();
			printf("\nNumero en inventario de %s:  ",d[i].a[j].nombre);
			scanf("%d",&d[i].a[j].inventario);
			getchar();
			printf("\nTermino de ingresar articulos 1.-Si\n2.-No :  ");
			scanf("%d",&respuesta);
			getchar();
			j++;
		}
	}
	free(aux);
	return d;
}
//Función que muestra los datos ingresados del artículo deseado.
void muestraArticulos(struct deptos *d,int nDep)
{
	int i;
	printf("\n  Articulo\tPrecio\tInventario");
	for(i=0;i<d[nDep-1].tamanio;i++){
		printf("\n%d)  %s\t%.2f\t%d\n",i+1,d[nDep-1].a[i].nombre,d[nDep-1].a[i].precio,d[nDep-1].a[i].inventario);
	}
}
//Función para añadir nuevos departamentos.
struct deptos * agregarDeptos(struct deptos*d)
{
	int respuesta,M=0,j=0,i;
	char *aux=(char*)malloc(sizeof(char)*100);
	d[0].tamanioD=d[0].tamanioD+1;
	i=d[0].tamanioD;
	d=(struct deptos* )realloc(d,sizeof(struct deptos)*i);
	printf("\nNombre departamento %d:  ",i);
	//fgets(d[i-1].nombreD,30,stdin);
	scanf("%[^\n]",aux);
	getchar();	
	d[i-1].nombreD=(char*)malloc(sizeof(char)*(strlen(aux)+1));
	memcpy(d[i-1].nombreD,aux,strlen(aux)+1);
	printf("Elementos departamento %s",d[i-1].nombreD);
	d[i-1].a=(articulo *)malloc(sizeof(articulo));
	while(respuesta!=1){
		d[i-1].tamanio++;
		M++;
		d[i-1].a=(articulo*)realloc(d[i-1].a,sizeof(articulo)*M);
		printf("\nArticulo %d:   ",j+1);
		//fgets(d[i-1].a[j].nombre,30,stdin);
		scanf("%[^\n]",aux);
		getchar();	
		d[i-1].a[j].nombre=(char*)malloc(strlen(aux)+1);
		memcpy(d[i-1].a[j].nombre,aux,strlen(aux)+1);
		printf("\nPrecio %s:  ",d[i-1].a[j].nombre);
		scanf("%f",&d[i-1].a[j].precio);
		getchar();
		printf("\nNumero en inventario de %s:  ",d[i-1].a[j].nombre);
		scanf("%d",&d[i-1].a[j].inventario);
		getchar();
		printf("\nTermino de ingresar articulos 1.-Si\n2.-No :  ");
		scanf("%d",&respuesta);
		getchar();
		j++;
	}
	free(aux);
	return d;
}
//Función para remover el artículo deseado.
struct deptos * removerArticulo(struct deptos *d,int nd,int na)
{
	int i;
	if(d[nd-1].tamanio>0){
		for(i=na-1;i<d[nd-1].tamanio-1;i++)
		{
			strcpy(d[nd-1].a[na-1].nombre,d[nd-1].a[na].nombre);
			d[nd-1].a[na-1].precio=d[nd-1].a[na].precio;
			d[nd-1].a[na-1].inventario=d[nd-1].a[na].inventario;
		}		
		d[nd-1].a=(articulo*)realloc(d[nd-1].a,sizeof(articulo)*(d[nd-1].tamanio-1));
		d[nd-1].tamanio--;	
	}
	else{
		printf("\nEste Departamento esta vacio");
	}
	return d;
}
//Función para "comprar" artículos. Ajusta el número de piezas en el inventario y las pérdidas en la compra.

struct deptos * comprarArticulo(struct deptos *d,int nd,int na)
{
	int piezas;
	printf("\nCuantas piezas comprara de %s:  ",d[nd-1].a[na-1].nombre);
	scanf("%d",&piezas);
	getchar();
	d[nd-1].perdida+=piezas*d[nd-1].a[na-1].precio;
	d[nd-1].a[na-1].inventario+=piezas;
	printf("\nPerdidas de este depto: %f  e inventario de articulo %d ",d[nd-1].perdida,d[nd-1].a[na-1].inventario);
	return d;
}
//Función para modificar el nombre y el precio de un artículo.
struct deptos * modificarArticulo(struct deptos *d ,int nd ,int na)
{
	char *aux=(char*)malloc(sizeof(char)*100);
	float precio;
	printf("\nNuevo nombre:  ");
	//fgets(nombre,30,stdin);
	scanf("%[^\n]",aux);	
	getchar();
	d[nd-1].a[na-1].nombre=(char*)malloc(strlen(aux)+1);
	memcpy(d[nd-1].a[na-1].nombre,aux,strlen(aux)+1);
	printf("\nNuevo precio:  ");
	scanf("%f",&precio);
	getchar();
	d[nd-1].a[na-1].precio=precio;
	free(aux);
	return d;
}
//Función para "vender" artículos. Ajusta el número de piezas en el inventario y las ganancias de la venta.
struct deptos * venderArticulo(struct deptos *d,int nd,int na)
{
	int piezas;
	printf("\nCuantas piezas vendera de %s:  ",d[nd-1].a[na-1].nombre);
	scanf("%d",&piezas);
	getchar();
	if(d[nd-1].a[na-1].inventario>0)
	{
		if(piezas<=d[nd-1].a[na-1].inventario)
		{
			d[nd-1].ganancia+=piezas*d[nd-1].a[na-1].precio;
			d[nd-1].a[na-1].inventario-=piezas;
		}
		else
			printf("\nNo hay tantas piezas en inventario");
	}
	else
	{
		printf("\nYa no hay %s en inventario",d[nd-1].a[na-1].nombre);
	}
	printf("\nGanancias de este depto: %f  e inventario de articulo %d ",d[nd-1].ganancia,d[nd-1].a[na-1].inventario);
	return d;
}
//Función para agregar artículos junto con sus datos.
struct deptos * agregarArticulo(struct deptos *d,int nd)
{
	int respuesta,j;
	char *aux=(char*)malloc(sizeof(char)*100);
	while(respuesta!=1){
		d[nd-1].tamanio++;
		j=d[nd-1].tamanio;
		d[nd-1].a=(articulo*)realloc(d[nd-1].a,sizeof(articulo)*j);
		printf("\nArticulo %d:   ",j);
		//fgets(d[i-1].a[j].nombre,30,stdin);
		scanf("%[^\n]",aux);
		getchar();	
		d[nd-1].a[j-1].nombre=(char*)malloc(strlen(aux)+1);
		memcpy(d[nd-1].a[j-1].nombre,aux,strlen(aux)+1);
		printf("\nPrecio %s:  ",d[nd-1].a[j-1].nombre);
		scanf("%f",&d[nd-1].a[j-1].precio);
		getchar();
		printf("\nNumero en inventario de %s:  ",d[nd-1].a[j-1].nombre);
		scanf("%d",&d[nd-1].a[j-1].inventario);
		getchar();
		printf("\nTermino de ingresar articulos 1.-Si\n2.-No :  ");
		scanf("%d",&respuesta);
		getchar();
	}
	free(aux);
	return d;
}

//Funcion suma de ganancias totales
float gananciasTotales(struct deptos *d)
{
	float g=0;
	int i;
	for(i=0;i<d[0].tamanioD;i++)
	{
		g+=d[i].ganancia;
	}
	return g;
}
//Funcion suma de perdidas totales
float perdidasTotales(struct deptos *d)
{
	float p=0;
	int i;
	for(i=0;i<d[0].tamanioD;i++)
	{
		p+=d[i].perdida;
	}
	return p;
}