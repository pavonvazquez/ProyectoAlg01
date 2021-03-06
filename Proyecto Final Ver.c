//Proyecto en C, es un inventario de una tienda departamental para su administración.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NARCHIVO "ventas.txt"
#define NCOMPRAS "compras.txt"
#define REPORTED "reporteDeptos.txt"
#define IMPORTAR "articulos.txt"
#define FINAL "reporteFinal.txt"

typedef struct articulos{
	char *nombre;
	float precio;
	int inventario;
}articulo;
struct deptos{
	articulo *a;
	char *nombreD;
	int tamanio;
	int tamanioD;
	float perdida;
	float ganancia;
	char **ArtVend;
	char **ArtCom;
	int *piezasv;
	int *piezasc;
	int conv;
	int conc;
};

struct deptos * nombreDeptos(struct deptos *d);
void muestraDeptos(struct deptos *d,int N);
struct deptos * datosArticulos(struct deptos *d,int N);
void muestraArticulos(struct deptos *d,int nDep);
struct deptos * removerArticulo(struct deptos *d,int nd,int na);
struct deptos * comprarArticulo(struct deptos *d,int nd,int na);
struct deptos * venderArticulo(struct deptos *d,int nd,int na);
struct deptos * modificarArticulo(struct deptos *d ,int nd ,int na);
struct deptos * agregarArticulo(struct deptos *d,int nd);
float gananciasTotales(struct deptos *d);
float perdidasTotales(struct deptos *d);
struct deptos * inicializarArtV(struct deptos *d);
struct deptos * articulosPorDeptoV(struct deptos *d,int nDep,int nArt,int piezasv);
struct deptos * articulosPorDeptoC(struct deptos *d,int nDep,int nArt,int piezasc);
void reporteDeptos(struct deptos *d,FILE * f);
struct deptos * importarArticulosA(struct deptos *d);
void reporteFinal(struct deptos *d,FILE * f,float g,float p);
void libera(struct deptos *d);


int main()
{
	int N=5,opcion,nDep,nArt,i=0,j,piezas,piezasc,con7=0;
	float ganancias,perdidas;
	FILE  *f, *fc,*rd,*l,*rf;
	f=fopen(NARCHIVO,"wt");
	fc=fopen(NCOMPRAS,"wt");
	fprintf(f,"Productos vendidos\tPiezas\n");
	fprintf(fc,"Productos comprados\tPiezas\n");
	struct deptos *d=(struct deptos*)malloc(sizeof(struct deptos)*N);
	d=nombreDeptos(d);
	d=datosArticulos(d,5);
	d=inicializarArtV(d);
	do{
		printf("\nQue desea hacer:\n1)Salir\n2)Mostrar elementos departamento\n3)Modificar articulos\n4)Eliminar elementos\n5)Comprar articulos\n6)Vender articulos\n7)Importar productos de archivo\n8)Agregar Articulos\n");
		scanf("%d",&opcion);
		getchar();
		switch(opcion){
			case 1:
				opcion=1;
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
						{
							fprintf(fc,"%s\t            %d\n",d[nDep-1].a[nArt-1].nombre,piezasc);
							d=articulosPorDeptoC(d,nDep,nArt,piezasc);
						}
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
							fprintf(f,"%s\t             %d\n",d[nDep-1].a[nArt-1].nombre,piezas);
							d=articulosPorDeptoV(d,nDep,nArt,piezas);
						}
					}
					else
						printf("\nArticulo incorrecto");						
				}
				else
					printf("\nDepartamento incorrecto");	
				break;	
			case 7:
				if(con7==0){
					d=importarArticulosA(d);
					con7++;
				}
				else 
				{
					printf("\nYa se ha importado los productos");
				}
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
			default:
			 	printf("\nOpcion incorrecta");
			 	break;
		}
	}while(opcion!=1);
	ganancias=gananciasTotales(d);
	perdidas=perdidasTotales(d);
	fprintf(f,"Ganancias Totales:  %f",ganancias);
	fprintf(fc,"Perdidas totales:  %f",perdidas);
	reporteDeptos(d,rd);
	reporteFinal(d,rf,ganancias,perdidas);
	fclose(f);
	fclose(fc);
	libera(d);
	return 0;
}
struct deptos * nombreDeptos(struct deptos *d)
{
	int i;
	char *aux=(char*)malloc(sizeof(char)*100);
	d=(struct deptos *)malloc(sizeof(struct deptos)*5);
	for(i=0;i<5;i++){
		printf("\nDepartamento %d:  ",i+1);
		scanf("%[^\n]",aux);
		getchar();
		d[i].nombreD=(char*)malloc(strlen(aux)+1);
		memcpy(d[i].nombreD,aux,strlen(aux)+1);
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
	char *aux=(char*)malloc(sizeof(char)*100);
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
void muestraArticulos(struct deptos *d,int nDep)
{
	int i;
	printf("\n  Articulo\tPrecio\tInventario");
	for(i=0;i<d[nDep-1].tamanio;i++){
		printf("\n%d)  %s\t%.2f\t%d\n",i+1,d[nDep-1].a[i].nombre,d[nDep-1].a[i].precio,d[nDep-1].a[i].inventario);
	}
}
struct deptos * removerArticulo(struct deptos *d,int nd,int na)
{
	int i;
	if(d[nd-1].tamanio>0){
		for(i=na-1;i<d[nd-1].tamanio-1;i++)
		{
			strcpy(d[nd-1].a[i].nombre,d[nd-1].a[i+1].nombre);
			d[nd-1].a[i].precio=d[nd-1].a[i+1].precio;
			d[nd-1].a[i].inventario=d[nd-1].a[i+1].inventario;
		}		
		d[nd-1].a=(articulo*)realloc(d[nd-1].a,sizeof(articulo)*(d[nd-1].tamanio-1));
		d[nd-1].tamanio--;	
	}
	else{
		printf("\nEste Departamento esta vacio");
	}
	return d;
}
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
struct deptos * modificarArticulo(struct deptos *d ,int nd ,int na)
{
	char *aux=(char*)malloc(sizeof(char)*100);
	float precio;
	printf("\nNuevo nombre:  ");
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
struct deptos * agregarArticulo(struct deptos *d,int nd)
{
	int respuesta,j;
	char *aux=(char*)malloc(sizeof(char)*100);
	while(respuesta!=1){
		d[nd-1].tamanio++;
		j=d[nd-1].tamanio;
		d[nd-1].a=(articulo*)realloc(d[nd-1].a,sizeof(articulo)*j);
		printf("\nArticulo %d:   ",j);
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
struct deptos * inicializarArtV(struct deptos *d)
{
	int i;
	for(i=0;i<5;i++)
	{
		d[i].ArtVend=(char**)malloc(sizeof(char*));
		d[i].ArtVend[0]=(char*)malloc(sizeof(char)*100);
		d[i].conv=0;
		d[i].ArtCom=(char**)malloc(sizeof(char*));
		d[i].ArtCom[0]=(char*)malloc(sizeof(char)*100);
		d[i].conc=0;
		d[i].piezasv=(int *)malloc(sizeof(int));
		d[i].piezasc=(int *)malloc(sizeof(int));
	}
	return d;
}
struct deptos * articulosPorDeptoV(struct deptos *d,int nDep,int nArt,int piezasv)
{
	d[nDep-1].conv++;
	d[nDep-1].piezasv=(int *)realloc(d[nDep-1].piezasv,sizeof(int)*d[nDep-1].conv);
	d[nDep-1].piezasv[d[nDep-1].conv-1]=piezasv;
	d[nDep-1].ArtVend=(char**)realloc(d[nDep-1].ArtVend,sizeof(char*)*d[nDep-1].conv);
	d[nDep-1].ArtVend[d[nDep-1].conv-1]=(char*)realloc(d[nDep-1].ArtVend[d[nDep-1].conv-1],strlen(d[nDep-1].a[nArt-1].nombre)*100);
	strcpy(d[nDep-1].ArtVend[d[nDep-1].conv-1],d[nDep-1].a[nArt-1].nombre);
	return d;
}
struct deptos * articulosPorDeptoC(struct deptos *d,int nDep,int nArt,int piezasc)
{
	d[nDep-1].conc++;
	d[nDep-1].piezasc=(int *)realloc(d[nDep-1].piezasc,sizeof(int)*d[nDep-1].conc);
	d[nDep-1].piezasc[d[nDep-1].conc-1]=piezasc;
	d[nDep-1].ArtCom=(char**)realloc(d[nDep-1].ArtCom,sizeof(char*)*(d[nDep-1].conc)*100);
	d[nDep-1].ArtCom[d[nDep-1].conc-1]=(char*)realloc(d[nDep-1].ArtCom[d[nDep-1].conc-1],strlen(d[nDep-1].a[nArt-1].nombre)*100);
	strcpy(d[nDep-1].ArtCom[d[nDep-1].conc-1],d[nDep-1].a[nArt-1].nombre);
	return d;
}
void reporteDeptos(struct deptos *d,FILE * f)
{
	int i,j;
	f=fopen(REPORTED,"wt");
	for(i=0;i<d[0].tamanioD;i++)
	{
		fprintf(f,"\nDepartamento %s ventas\n",d[i].nombreD);
		for(j=0;j<d[i].conv;j++)
		{
			fprintf(f,"\nArticulos vendidos: %s\tPiezas vendidas:  %d\n",d[i].ArtVend[j],d[i].piezasv[j]);
		}
		fprintf(f,"\nGanancias %f\n",d[i].ganancia);
	}
	for(i=0;i<d[0].tamanioD;i++)
	{
		fprintf(f,"\nDepartamento %s compras\n",d[i].nombreD);
		for(j=0;j<d[i].conc;j++)
		{
			fprintf(f,"\nArticulos compradas: %s\tPiezas compradas:  %d\n",d[i].ArtCom[j],d[i].piezasc[j]);
		}
		fprintf(f,"\nPerdidas %f\n",d[i].perdida);
	}
	fclose(f);
}
struct deptos * importarArticulosA(struct deptos *d)
{
	FILE *f;
	f=fopen(IMPORTAR,"r");
	char **lineas;
	char *una;
	int i=0,j,nd,k;
	una=(char*)malloc(sizeof(char)*100);
	lineas=(char**)malloc(sizeof(char *));
	lineas[0]=(char*)malloc(sizeof(char));
	if(f==NULL)
	{
		printf("\nError al abrir archivo");
		exit(1);
	}
	while(feof(f)==0)
	{
		if(feof(f)==0){
			fgets(una,100,f);
			if(una[strlen(una)-1]=='\n')
			{
				una[strlen(una)-1]=0;
			}
			lineas=(char**)realloc(lineas,sizeof(char*)*(i+1)*100);
			lineas[i]=(char*)realloc(lineas[i],strlen(una)+1);
			strcpy(lineas[i],una);
			i++;
		}
	}
	for(j=0;j<i;j+=3)
	{
		printf("\nA que departamento pertenece %s",lineas[j]);
		muestraDeptos(d,d[0].tamanioD);
		scanf("%d",&nd);
		getchar();
		if(nd>0 && nd<d[0].tamanioD+1){
			d[nd-1].tamanio++;
			k=d[nd-1].tamanio;
			d[nd-1].a=(articulo*)realloc(d[nd-1].a,sizeof(articulo)*k);
			d[nd-1].a[k-1].precio=atof(lineas[j+1]);
			d[nd-1].a[k-1].inventario=atoi(lineas[j+2]);
			d[nd-1].a[k-1].nombre=realloc(d[nd-1].a[k-1].nombre,strlen(lineas[j])+100);
			strcpy(d[nd-1].a[k-1].nombre,lineas[j]);
		}
		else
		{
			printf("Opcion incorrecta!!");
			j-=3;
		}
	}
	for(j=0;j<i;j++)
	{
		free(lineas[j]);
	}
	free(lineas);
	free(una);
	fclose(f);
	return d;
}
void reporteFinal(struct deptos *d,FILE * f,float g,float p)
{
	int i,j;
	f=fopen(FINAL,"wt");
	fprintf(f,"Ventas\n");
	for(i=0;i<d[0].tamanioD;i++)
	{
		for(j=0;j<d[i].conv;j++)
		{
			fprintf(f,"\nArticulos: %s\tPiezas:  %d\n",d[i].ArtVend[j],d[i].piezasv[j]);
		}
	}
	fprintf(f,"Ganancias: %f",g);
	fprintf(f,"\nCompras\n");
	for(i=0;i<d[0].tamanioD;i++)
	{
		for(j=0;j<d[i].conc;j++)
		{
			fprintf(f,"\nArticulos: %s\tPiezas:  %d\n",d[i].ArtCom[j],d[i].piezasc[j]);
		}
	}
	fprintf(f,"Perdidas: %f\n",p);
	fprintf(f,"Total:  %f",(g-p));
	fclose(f);
}
void libera(struct deptos *d)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<d[i].tamanio;j++)
		{
			free(d[i].a[j].nombre);
		}
	}
	for(i=0;i<d[0].tamanioD;i++)
	{
		free(d[i].nombreD);
		free(d[i].piezasv);
		for(j=0;j<d[i].conv;j++)
		{
			free(d[i].ArtVend[j]);
		}
		free(d[i].ArtVend);
	}
	for(i=0;i<d[0].tamanioD;i++)
	{
		free(d[i].piezasc);
		for(j=0;j<d[i].conc;j++)
		{
			free(d[i].ArtCom[j]);
		}
		free(d[i].ArtCom);
	}
	free(d->a);
	free(d);
}