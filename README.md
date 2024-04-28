To Do:
    - Unset PWD con env -i // unset PWD cd .. (en normal)
	*** crear un nodo propio env.key = TRIGGER env.value = NULL, y unos cuantos triggers que sean utils
		- p.e --> is_unsetpwd
				  is env - i
				  camuflar la hardcodeada al imprimir el export
			** poner como cabeza de lista :)









bash-3.2$ export b='" 456'
bash-3.2$ echo $a$b   si el limiter de un heredoc tiene comillas, el line input no debe expandirse
echo '$a' $b ad "ad" 'a' $b "$USER"
echo '$a' $b ad "ad" 'a' $b "$a$HOME'$USER'"
echo $USER'$USER'$USER'$USER''$USER'
echo "'$USER''dwad'aaaaa$HOME"
echo $USER""
echo "aa$USER$DWADAWDWCHOME"
echo "$DWDWADADW$USER""DDWAD"