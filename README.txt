Vous trouverez 1 dossier et un fichier dans ce répertoire :
-------------------------------------------------------------
		
	* Dossier UpParser_COO_Al-Natour_Mazen : Ce dossier contient le projet Visual Studio comprenant la bibliothèque, les tests et une app avec le main.

Comment fonctionne mon Parser ? 
------------------------------

	1- Commande (Command) :

		C'est une classe abstraite pour représenter une commande quelconque. Elle garde des informations telles que le nom, les alias, le nombre d'arguments, et si elle est requise ou immédiate. Pour l'utiliser, il faudra la dériver en commandes plus précises afin de définir plus précisément le comportement de celle-ci avec différentes configurations.

	2- Parser (parsing) :

		C'est le chef d'orchestre. Il gère tout le processus de compréhension des commandes et de les exécuter. On a une liste de commandes, et on les exécute dans un ordre particulier. Si une commande est nécessaire mais manquante, ou si quelque chose ne va pas, on lance une erreur précise avec une descritpion de ce qui va pas.

		--> Déroulement de l'Analyse :

			D'abord, on regarde les commandes immédiates. On les sépare du reste. Ensuite, on analyse le reste des commandes. Si tout est en ordre, on exécute celles qui ne sont pas immédiates. On s'assure que les cibles nécessaires sont présentes. Si quelque chose manque, on lance une erreur précise avec une descritpion de ce qui va pas.

	Pour plus de détails, je vous invite à regarder mon code et l'UML.


	Afin de tester mon parser, un exemple de ligne de commande est inclus dans le main, pour le tester il daudra aller dans les options d'arguments de Visual Studio du projet et le mettre. Après configuration, il suffira de le lancer. Concernant les tests, il faut avoir la bibliothèque de tests de Google au préalable. Ils ne sont pas fournis dans le livrable, sinon il ferait au moins 200 Mo, ce qui n'est pas demandé. D'autre part, il y a les tests qui sont donnés par le sujet et quelques-uns en plus.


Bon Parsing ;)






















