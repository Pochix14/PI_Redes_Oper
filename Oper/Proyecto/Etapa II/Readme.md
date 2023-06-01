# NachOS - CI-0122

## Autor
- [Pablo Rodríguez Navarro - B66060](https://www.github.com/Pochix14)


## Implementación
Para esta entrega se realizaron los siguientes cambios:
- Se modifica la clase addrespace para que sea multihilo.
- Se completan los system calls pertenecientes a la clase exception.
- Se crea la clase tabla para el manejo de la memoria.
- Se modifica el Makefile.common para que compile con los cambios y archivos generados.

Con los cambios realizados es posible correr la mayoría de pruebas de manera exitosa, sin embargo exiten algunas que generan un error.
Otro detalle a mencionar es que al compilar desde la carpeta *code*, se genera un error que a la fecha de presentación de esta entrega, no se ha logrado solucionar.


## Compilación
Suponiendo que se encuentra en la carpeta **code**

1. Dirigirse a la carpeta *userprog*

```bash
  cd userprog
```

2. Realizar el llamado al Makefile para instalar las dependencias
```bash
  make depend
```

3. Realizar la compilación de los archivos
```bash
  make
```

Para poder recompilar, hace falta eliminar los archivos ejecutables, para esto hay que seguir los siguientes pasos (suponiendo que se encuentra en la carpeta *userprog*):
1. Volver a la carpeta *code*
 ```bash
  cd ..  
```

2. Realizar la limpieza correspondiente con el Makefile
```bash
  make clean
```

Para volver a generar los archivos y poder correr, vuelva a realizar los pasos de esta sección.

## Ejecucción
Una vez compilados los archivos, se puede correr nachos, para esto solo faltaría, suponiendo que se está en la carpeta *userprog*, realizar el siguiente comando:
```bash
  ./nachos -x ../test/NOMBRE_DEL_TEST
```

Donde el NOMBRE_DEL_TEST corresponde a la prueba que quiera ejecutarse.


## Pruebas realizadas
Para esta entrega se corrieron las siguientes pruebas que corrieron de manera satisfactoria:
- addrspacetest
- copy
- halt
- matmult
- matmult5
- pingPong
- socket
- todos

### Problemas presentados
Como se ha mencionado, aún para esta entrega se tienen diversos problemas que se encuentran faltos de solución, entre esos se pueden mencionar:
- Al realizar la compilación en la carpeta code, da error.
- Los casos de prueba **matmult20, shell, sort y sort-ok** dan error al ejecutarse.

Posiblemente la causa de los errores sean parte del código implementado o al menos la manera de realizar dicha implementación; quizás la única salvedad sea el caso de matmult20, quien el profe sugirió en clase
que para realizarse, necesita hacer uso de más memoria; pero a fecha de entrega, no se ha visto como.
