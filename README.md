To Do:
	-signals
	-leaks
	-builtins error aunque no se tenga que ejecutar
	-norminette

HACER FREE en EXIT
HACER EXPORT, UNSET, ENV handle errors y COOKING EXECUTION
DO TODO LA NORMINETTE

TEST:
	ls | ./minishell
	carpeta borrar
	sin env

ERROR CODE NO FILE		*** DONE ***
EXIT MSG     *** DONE ***
cd -     *** DONE ***
UNSET PATH SEGFAULT     *** DONE ***
ls > $test(no existe) *** DONE ***
ls $b (si es onlyexport no hay que expandir)     *** DONE ***
REDIRECT SI FALLAN CMD NO EXEC     *** DONE ***
cat | ls		*** DONE ***
EXIT ERRCODE (cd path que no existe)     *** DONE ***
HEREDOC CON VARIABLE DE ENTORNO COMO LIMITER FUNCIONA MAL		*** DONE ***

Comillas post tokenization quitarlas :)		*** DONE ***
SI HAY UN INF MALO ACABAR ESas redireciones

bash-3.2$ export a='123 "'
bash-3.2$ export b='" 456'
bash-3.2$ echo $a$b

si el limiter de un heredoc tiene comillas, el line input no debe expandirse