Todos los scripts necesarios para compilar y correr los ejemplos se encuentran en la carpeta "scripts"
Para compilar:
- ./compile_compiler.sh (si no tenemos permiso realizar: $ chmod 777 compile_compiler.sh)

Para ejecutarel compilador:
- ./ctds input.ctds (donde input.tds es el archivo que queremos analizar)
- gcc input.s {archivos objeto que queramos incluir, mas todas las opciones que da gcc}
- ./a.out (o el nombre que le hayamos dado al ejecutable).

