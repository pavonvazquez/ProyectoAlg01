//Proyecto en C, es un inventario de una tienda departamental para su administración.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct articulos{
	char nombre[30];
	float precio;
	int inventario;
}articulo;
struct deptos{
	articulo *a;
	char *nombreD;
	int tamanio;
	int tamanioD;
};

struct deptos * nombreDeptos(struct deptos *d);
void muestraDeptos(struct deptos *d,int N);
struct deptos * datosArticulos(struct deptos *d,int N);
void muestraArticulos(struct deptos *d,int nDep);
struct deptos * agregarDeptos(struct deptos*d);
struct deptos * removerArticulo(struct deptos *d,int nd,int na);
struct deptos * comprarArticulo(struct deptos *d,int nd,int na);



int main()
{
	int N=5,bytes,opcion,nDep,nArt;
	struct deptos *d=(struct deptos*)malloc(sizeof(struct deptos)*N);
	d=nombreDeptos(d);
	d=datosArticulos(d,5);
	do{
		printf("\nQue desea hacer:\n1)Agregar Departamento\n2)Mostrar elementos departamento\n3)Modificar articulos\n4)Eliminar elementos\n5)Comprar articulos\n6)Vender articulos\n7)Importar productos de archivo\n8)Agregar Articulos\n9)Salir\n");
		scanf("%d",&opcion);
		getchar();
		switch(opcion){
			case 1:
				d=agregarDeptos(d);
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
			case 6:
			case 8:	
			case 9:
				opcion=9;
				break;
			default:
			 	printf("\nOpcion incorrecta");
			 	break;
		}
	}while(opcion!=9);
	free(d->a);
	free(d);
	return 0;
}
struct deptos * nombreDeptos(struct deptos *d)
{
	int i;
	char *aux=(char*)malloc(sizeof(char)*30);
	d=(struct deptos *)malloc(sizeof(struct deptos)*5);
	for(i=0;i<5;i++){
		printf("\nDepartamento %d:  ",i+1);
		//fgets(aux,30,stdin);
		scanf("%[^\n]",aux);
		getchar();
		d[i].nombreD=(char*)malloc(strlen(aux));
		memcpy(d[i].nombreD,aux,strlen(aux));
		d[0].tamanioD++;
	}
	free(aux);
	return d;
}
void muestraDeptos(struct deptos *d,int N)
{
	int i;
	for(i=0;i<N;i++){
		printf("\nDepartamento %d ->  %s",i+1,d[i].nombreD);
	}	
	printf("\n");
}
struct deptos * datosArticulos(struct deptos *d,int N)
{
	int i,j, M=0;
	int respuesta;
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
			scanf("%[^\n]",d[i].a[j].nombre);
			getchar();
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
	return d;
}
void muestraArticulos(struct deptos *d,int nDep)
{
	int i;
	printf("\n  Articulo\tPrecio\tInventario");
	for(i=0;i<d[nDep-1].tamanio;i++){
		printf("\n%d)  %s\t%f\t%d\n",i+1,d[nDep-1].a[i].nombre,d[nDep-1].a[i].precio,d[nDep-1].a[i].inventario);
	}
}
struct deptos * agregarDeptos(struct deptos*d)
{
	int respuesta,M=0,j=0,i;
	d[0].tamanioD=d[0].tamanioD+1;
	i=d[0].tamanioD;
	d=(struct deptos* )realloc(d,sizeof(struct deptos)*i);
	d[i-1].nombreD=(char*)malloc(sizeof(char)*30);
	printf("\nNombre departamento %d:  ",i);
	//fgets(d[i-1].nombreD,30,stdin);
	scanf("%[^\n]",d[i-1].nombreD);
	getchar();	
	printf("Elementos departamento %s",d[i-1].nombreD);
	d[i-1].a=(articulo *)malloc(sizeof(articulo));
	while(respuesta!=1){
		d[i-1].tamanio++;
		M++;
		d[i-1].a=(articulo*)realloc(d[i-1].a,sizeof(articulo)*M);
		printf("\nArticulo %d:   ",j+1);
		//fgets(d[i-1].a[j].nombre,30,stdin);
		scanf("%[^\n]",d[i-1].a[j].nombre);
		getchar();	
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
	return d;
}
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