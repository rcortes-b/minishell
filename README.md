Estructura actual del proyecto:
								-Un unico prompt que pide un input
								-Se hace un split del input
								-Se hace el check de que ni el primer ni el ultimo struct sea operator y de que no hayan dos seguidos
								-Se ordena el input para ser ejecutado de forma correcta (order flags)
								-Se pasa el input a estructura distinguiendo entre operador y comando / flags
								-Se tokenizan las estructuras para saber que tipo de simbolo o si es comando


			EL INFILE PUEDE PILLAR DESPUES DE UNA PIPE EN CUALQUIERE MOEMNTO