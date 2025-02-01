# minishell
![illustration minishell](./picture.png)
Le projet Minishell de l'École 42 consiste à développer un interpréteur de commandes minimaliste, inspiré de bash. Ce projet vise à familiariser les étudiants avec le fonctionnement interne des shells, en mettant l'accent sur le parsing, la gestion des processus, la synchronisation et la gestion des signaux.

🎯 Objectifs du Projet
Compréhension des Shells Unix : Apprendre le fonctionnement des shells, qui fournissent une interface en ligne de commande pour interagir avec le système.

Gestion des Processus : Mettre en œuvre la création, la synchronisation et la terminaison des processus pour exécuter des commandes utilisateur.

Gestion des Signaux : Manipuler les signaux pour gérer les interruptions et les commandes intégrées, telles que Ctrl+C pour interrompre un processus.

Implémentation des Redirections et des Pipes : Gérer les redirections d'entrée/sortie (<, >, >>) et les pipes (|) pour permettre la communication entre processus.

🛠️ Spécifications Techniques
Fonctionnalités à Implémenter :

Affichage d'un Prompt : Afficher un prompt personnalisé en attente des commandes de l'utilisateur.
Historique des Commandes : Maintenir un historique des commandes exécutées pour permettre la navigation et la réexécution.
Exécution des Commandes : Localiser et exécuter les exécutables en se basant sur la variable d'environnement PATH ou via un chemin absolu.
Gestion des Citations Simples et Doubles : Gérer les guillemets simples (') et doubles (") pour empêcher ou permettre l'interprétation des métacaractères.
Redirections :
Entrée (<) : Rediriger l'entrée standard depuis un fichier.
**Sortie (>) : Rediriger la sortie standard vers un fichier, en écrasant le contenu existant.
**Append (>>) : Rediriger la sortie standard vers un fichier, en ajoutant au contenu existant.
**Heredoc (<<) : Lire l'entrée jusqu'à un délimiteur spécifié, sans mettre à jour l'historique.
Pipes (|) : Connecter la sortie d'une commande à l'entrée d'une autre, permettant la création de pipelines.
Variables d'Environnement : Gérer l'expansion des variables d'environnement ($VARIABLE) et de la variable $? pour le statut de sortie de la dernière commande exécutée.
Gestion des Signaux :
Ctrl+C : Afficher un nouveau prompt sur une nouvelle ligne.
Ctrl+D : Quitter le shell.
Ctrl+\ : Ne rien faire.
Built-ins à Implémenter :

echo : Avec l'option -n pour supprimer le saut de ligne final.
cd : Changer le répertoire de travail actuel.
pwd : Afficher le répertoire de travail actuel.
export : Définir des variables d'environnement.
unset : Supprimer des variables d'environnement.
env : Afficher les variables d'environnement actuelles.
exit : Quitter le shell.
🔧 Approche d'Implémentation
Lecture de l'Entrée :

Utiliser la fonction readline pour afficher le prompt et lire l'entrée de l'utilisateur.
Ajouter les commandes saisies à l'historique à l'aide de add_history.
Analyse Lexicale (Lexer) :

Diviser l'entrée en tokens pour identifier les commandes, arguments, opérateurs, etc.
Analyse Syntaxique (Parser) :

Construire une structure de données représentant la commande et ses composants, en tenant compte de la priorité des opérateurs et des parenthèses.
Expansion :

Gérer l'expansion des variables d'environnement et le traitement des guillemets.
Exécution :

Implémenter les built-ins directement dans le shell.
Pour les autres commandes, utiliser fork pour créer un processus enfant et execve pour exécuter la commande.
Gérer les redirections et les pipes en ajustant les descripteurs de fichiers à l'aide de dup2.

Gestion des Signaux :
Configurer des gestionnaires de signaux pour intercepter Ctrl+C, Ctrl+D et Ctrl+\ et appliquer le comportement approprié.

📂 Structure du Projet

Fichiers Principaux :
main.c : Point d'entrée du programme, gère la boucle principale du shell.
lexer.c : Contient les fonctions pour l'analyse lexicale de l'entrée utilisateur.
parser.c : Gère l'analyse syntaxique et la construction de la commande.

Fichiers Principaux (Suite) :
executor.c : Contient les fonctions pour l'exécution des commandes et la gestion des processus.
builtins.c : Implémente les commandes internes (cd, echo, export, etc.).
signals.c : Gestion des signaux (Ctrl+C, Ctrl+D, Ctrl+\).
utils.c : Fonctions utilitaires (gestion de la mémoire, affichage d'erreurs, etc.).

Bibliothèques Utilisées :
readline : Pour la gestion du prompt et de l’historique des commandes.
unistd.h : Pour les appels système (fork, execve, dup2).
signal.h : Pour la gestion des signaux.
stdlib.h et string.h : Pour la manipulation des chaînes et allocation dynamique.

🧪 Tests et Validation
Tests Fonctionnels :

Vérifier que chaque commande interne (cd, pwd, etc.) fonctionne correctement.
Vérifier la gestion des redirections (<, >, >>) et des pipes (|).
Vérifier l’expansion des variables ($USER, $HOME, etc.).
Assurer la bonne gestion des erreurs (commandes inconnues, fichiers inexistants, etc.).
Tests de Robustesse :

Exécuter le shell avec des entrées non valides pour observer le comportement.
Tester la gestion des signaux (Ctrl+C, Ctrl+D) pour éviter les comportements indésirables.
Vérifier la gestion de la mémoire avec valgrind pour éviter les fuites.

Tests de Performance :
Exécuter un grand nombre de commandes en boucle pour évaluer la stabilité.
Tester l’exécution simultanée de plusieurs processus avec des pipes.

📚 Ressources Utiles
📂 Dépôts GitHub :
[mcombeau/minishell : Une implémentation complète avec explications.][https://github.com/mcombeau/minishell]
[tjensen42/42-minishell : Version alternative mettant l’accent sur les processus.][https://github.com/tjensen42/42-minishell]

📖 Articles et Guides :
[Minishell: Building a mini-bash : Explication détaillée du projet.][https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218]
[42Docs - Minishell : Documentation technique avec conseils d’implémentation.][https://harm-smits.github.io/42docs/projects/minishell]
[Minishell Guide 42 Cursus : Guide complet du projet.][https://42-cursus.gitbook.io/guide/rank-03/minishell]
🎥 Tutoriels Vidéo :
[42-Minishell - YouTube Playlist : Série de vidéos sur le développement de Minishell.][https://www.youtube.com/playlist?list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW]
[Shell programming & Process management : Introduction aux shells Unix et gestion des processus.][https://www.youtube.com/watch?v=ZJFIwsL9I1Y]

🚀 Pourquoi ce projet est important ?
Le projet Minishell est un exercice clé pour comprendre comment fonctionne un shell Unix. Il permet d'acquérir des compétences avancées en gestion des processus, redirections d’entrée/sortie, gestion de la mémoire, et synchronisation des tâches. Ces compétences sont essentielles pour les développeurs systèmes, DevOps et ingénieurs en logiciels bas niveau. 🔥