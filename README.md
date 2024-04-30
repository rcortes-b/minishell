To Do:
    - Unset PWD con env -i // unset PWD cd .. (en normal)
	*** crear un nodo propio env.key = TRIGGER env.value = NULL, y unos cuantos triggers que sean utils
		- p.e --> is_unsetpwd
				  is env - i camuflar la hardcodeada al imprimir el export
			** poner como cabeza de lista :)
	- Unset PWD cnd no hay env funciona bien (?wtf)  "Lol, siempre miraba el next y no me importaba si un unset era la cabeza del nodo (en ell env -i, la cabeza de nodo es PWD xdd) , hacer test de UNSET

	cosas que he cambiado: 
						- nueva funcion en unset para eliminar los head nodes if required (aunque si voy a crear un head node quizas no es ni necesario)
						- He añadido la condicion de strcmp para el env "_" ya que aunque hagas unset de este, no hay que llevarlo a cabo (revisar si puede dar lugar a error)
						- builtins_utils.c line 35: he añadido un printf, ya que cuando se hace "cd -" se imprime el oldpwd (revisar si puede dar lugar a error)

						Por implementar ahora:
												- Cabeza de nodo de env, en caso de que sea env -i el PATH y el HOME hardcoded nunca se imprimiran
												- Un trigger que almacene el estado de PWD y OLDPWD (si se ha hecho unset no tiene que imprimirse / actualizarse)

												unset PWD OLDPWD
												echo $PWD $OLDPWD (no aparece)
												cd srcs/ cd ..
												echo $PWD $OLDPWD (aparece) , pero en env y export ni rastro







bash-3.2$ export b='" 456'
bash-3.2$ echo $a$b   si el limiter de un heredoc tiene comillas, el line input no debe expandirse
echo '$a' $b ad "ad" 'a' $b "$USER"
echo '$a' $b ad "ad" 'a' $b "$a$HOME'$USER'"
echo $USER'$USER'$USER'$USER''$USER'
echo "'$USER''dwad'aaaaa$HOME"
echo $USER""
echo "aa$USER$DWADAWDWCHOME"
echo "$DWDWADADW$USER""DDWAD"