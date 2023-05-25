Proceso Inventariocel
	// Productos
	Dimension producto[2];
	Definir producto Como Caracter;
	Dimension Precio[2];
	Definir Precio Como Real;
	Dimension Existencias[2];
	Definir Existencias Como Entero;
	Dimension Descripcion[2];
	Definir Descripcion Como Caracter;
	Dimension Entrada[2];
	Definir Entrada Como Entero;
	Dimension Salida[2];
	Definir Salida Como Entero;
	// Usuario
	Definir Usuario Como Caracter;
	Definir Contrasenia Como Caracter;
	// Ejemplo de contrasenia Admin
	Usuario <- 'Admin';
	Contrasenia <- '1234';
	// Funciones basicas producto
	Definir usuarionum Como Caracter;
	Definir contrasenianum Como Caracter;
	Escribir 'Digite el usuario';
	Leer usuarionum;
	Escribir 'Digite la contrasenia';
	Leer contrasenianum;
	Si usuarionum==Usuario Y contrasenianum==Contrasenia Entonces
		Definir opcion Como Entero;
		Escribir 'Menu:';
		Escribir '1. Agregar producto:';
		Escribir '2. Modificar producto: ';
		Escribir '3. Eliminar producto: ';
		Escribir '4. Imprimir inventario: ';
		Escribir '5. Salir: ';
		Escribir 'Opcion: ';
		Leer opcion;
			Mientras opcion<>5 Hacer
			Segun opcion  Hacer
				1:
					Borrar Pantalla;
					Definir i Como Entero;
					Para i<-0 Hasta 1 Hacer
						Escribir 'Nombre del producto: ';
						Leer producto[i];
						Escribir 'Precio: ';
						Leer Precio[i];
						Escribir 'Existencias';
						Leer Existencias[i];
						Escribir 'Descripcion';
						Leer Descripcion[i];
					FinPara
					
				2:
					Borrar Pantalla;
					Para i<-0 Hasta 1 Hacer
						Escribir i,'. ','Producto: ',producto[i];
						Escribir '$',Precio[i];
						Escribir 'Existencias: ',Existencias[i];
						Escribir 'Descripcion: ',Descripcion[i];
						Escribir 'Entrada de producto: ',Entrada[i];
						Escribir 'Salida de producto: ',Salida[i];
						Escribir ' ';
					FinPara
					Definir n Como Entero;
					Escribir 'Cual deseas modificar?: ';
					Leer n;
					Escribir 'Nombre del producto: ';
					Leer producto[n];
					Escribir 'Precio: ';
					Leer Precio[n];
					Escribir 'Existencias';
					Leer Existencias[n];
					Escribir 'Descripcion';
					Leer Descripcion[n];
				3:
					Borrar Pantalla;
					Para i<-0 Hasta 1 Hacer
						Escribir i,'. ','Producto: ',producto[i];
						Escribir '$',Precio[i];
						Escribir 'Existencias: ',Existencias[i];
						Escribir 'Descripcion: ',Descripcion[i];
						Escribir 'Entrada de producto: ',Entrada[i];
						Escribir 'Salida de producto: ',Salida[i];
						Escribir ' ';
					FinPara
					Definir n Como Entero;
					Escribir 'Cual deseas eliminar?: ';
					Leer n;
					producto[n] <- '';
					Precio[n] <- 0;
					Existencias[n] <- 0;
					Descripcion[n] <- '';
					Salida[n] <- Entrada[n];
					Entrada[n] <- 0;
				4:
					Borrar Pantalla;
					Para i<-0 Hasta 1 Hacer
						Escribir i,'. ','Producto: ',producto[i];
						Escribir '$',Precio[i];
						Escribir 'Existencias: ',Existencias[i];
						Escribir 'Descripcion: ',Descripcion[i];
						Escribir 'Entrada de producto: ',Entrada[i];
						Escribir 'Salida de producto: ',Salida[i];
						Escribir ' ';
					FinPara
				5:
			FinSegun
		FinMientras
		
	FinSi
FinProceso
