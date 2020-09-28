Para compilar:

- ./script (si no tenemos permiso realizar: $ chmod 777 script)

Para ejecutar:
- ./a.out input.txt (donde input.txt es el archivo que queremos analizar)


//Casos de test positivos

1- extern integer inc(integer x);
	
2- integer prod(){
    integer x;
    integer y;
    {x = 4;     
    y = 5;
    x * 3 * y; }
   } 

3- integer suma(integer a, integer b) {
  return a + b;
  } 
 
4- extern void print(integer i);

5- integer main(){
  integer y;
  y = 1;
  {
  integer x;
  x = 2;
  y = x + 1;
  } 
  return x;
  }

6- integer x;
   integer u;
   bool z

7- integer func() {{{{{{}}}}}}

8 - //Comment!
integer a;
/*Comment!

*/
integer b
 

//Casos de test negativos

1- integer prod(){
    integer x;
    integer y;
    {x = 4;
    y = 5
    x * 3 * y; }
   }

2-extern integer prod(){
    integer x;
    integer y;
    {x = 4;
    y = 5;
    x * 3 * y; }
   }

3- integer func() {{{{{}}}}}}

4- #include<stdio.h>
int main(int argc, char[]* argv) {
	printf("Hello World!\n\0");
}

5- //Comment!
integer a;
/*Comment!

/
integer b

6- /Comment!
integer a;
/*Comment!

*/
integer b

