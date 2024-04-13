Execution path:
				-Se ordena todo ✅
				-Se eliminan los redirects abriendo los archivos y almacenando los fds en estos ✅
				-Se crea un doble char pointer con los builtins para hacer las comprobaciones ✅
				-Se checkea si el comando a ejecutar es builtin o no
					-Si es builtin:
									-Se llama a la funcion del builtin en concreto
					-Si no es builtin:
									-Se llama a execve con el path completo y la lst->flags

Builtins To Do:
				- echo ✅
				- cd
				- pwd
				- export
				- unset ✅
				- env ✅ *check el comment
				- exit