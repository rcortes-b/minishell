- Expansion:
	* Respetar espacios. ej: echo ".   $USER", "    $USER"
	* Quotes finales
	* diferentes limitadores de iteracion segun el caracter puesto. ej: $USERdwad -> "", $1dawd -> dawd
- PWD (recibirlo por el env menos cuando es NULL, recibir por getcwd)
- Export tiene que hacer todo aunque falle
- sin expansion heredoc. ej: << '$USER' cat > out (no expande nada dentro del heredoc)



bash-3.2$ export b='" 456'
bash-3.2$ echo $a$b   si el limiter de un heredoc tiene comillas, el line input no debe expandirse
echo '$a' $b ad "ad" 'a' $b "$USER"
echo '$a' $b ad "ad" 'a' $b "$a$HOME'$USER'"
echo $USER'$USER'$USER'$USER''$USER'
echo "'$USER''dwad'aaaaa$HOME"
echo $USER""
echo "aa$USER$DWADAWDWCHOME"
echo "$DWDWADADW$USER""DDWAD"