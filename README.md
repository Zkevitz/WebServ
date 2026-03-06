# 🌐 WebServ — Serveur HTTP en C++

> Projet réalisé dans le cadre du cursus de l'école 42

---


## 📋 Description

**WebServ** est une implémentation d'un serveur HTTP écrit en **C++98**, inspiré du fonctionnement de [NGINX](https://nginx.org/). L'objectif du projet est de comprendre en profondeur le protocole HTTP, la gestion des sockets, le multiplexage I/O et l'architecture d'un serveur web réel.

Le serveur est capable de gérer plusieurs connexions clientes simultanément, de servir des fichiers statiques, et d'exécuter des scripts via l'interface **CGI**.

---

## 🗂️ Structure du projet

```
WebServ/
├── src/            # Sources C++ (logique du serveur)
├── include/        # Headers (.hpp)
├── config/         # Fichiers de configuration
├── Www/            # Fichiers web servis (HTML, CSS, assets)
└── Makefile
```

---

## ⚙️ Compilation

```bash
make
```

Cela produit l'exécutable `webserv` à la racine du projet.

Pour nettoyer :

```bash
make clean    # supprime les objets
make fclean   # supprime les objets + l'exécutable
make re       # recompile tout
```

---

## 🚀 Utilisation

```bash
./webserv [fichier_de_config]
```

Si aucun fichier n'est précisé, le serveur cherche une configuration par défaut.

**Exemple :**

```bash
./webserv config/default.conf
```

Ouvrez ensuite votre navigateur à l'adresse indiquée dans la config (ex : `http://localhost:8080`).

---

## 🔧 Fichier de configuration

Le fichier de configuration est inspiré de la syntaxe NGINX. Il permet de définir un ou plusieurs blocs `server`, chacun avec ses propres directives.

**Exemple de configuration :**

```nginx
server {
    listen          8080;
    server_name     localhost;
    root            ./Www;
    index           index.html;
    client_max_body_size  10M;

    error_page 404  ./Www/errors/404.html;

    location / {
        methods     GET POST DELETE;
        autoindex   on;
    }

    location /upload {
        methods     POST;
        root        ./Www/uploads;
    }

    location *.py {
        cgi_pass    /usr/bin/python3;
    }
}
```

### Directives supportées

| Directive              | Description                                          |
|------------------------|------------------------------------------------------|
| `listen`               | Port d'écoute                                        |
| `server_name`          | Nom(s) de domaine associé(s)                         |
| `root`                 | Répertoire racine servi                              |
| `index`                | Fichier index par défaut                             |
| `client_max_body_size` | Taille maximale du corps d'une requête               |
| `error_page`           | Pages d'erreur personnalisées                        |
| `methods`              | Méthodes HTTP autorisées (GET, POST, DELETE)         |
| `autoindex`            | Activation du listing de répertoire                  |
| `return`               | Redirection HTTP                                     |
| `cgi_pass`             | Interpréteur pour l'exécution CGI                    |

---

## 📡 Fonctionnalités

- **Méthodes HTTP** : `GET`, `POST`, `DELETE`
- **Fichiers statiques** : HTML, CSS, JS, images, etc.
- **Listing de répertoire** : via la directive `autoindex`
- **Upload de fichiers** : via requêtes POST
- **Redirections HTTP** : via la directive `return`
- **CGI** : exécution de scripts Python, PHP, etc.
- **Multi-serveurs** : plusieurs blocs `server` dans un même fichier de config
- **I/O non-bloquant** : gestion concurrente des connexions via `select()` / `poll()`
- **Pages d'erreur personnalisées** : 400, 403, 404, 405, 413, 500...

---

## 🧠 Concepts techniques clés

### Multiplexage I/O

Le serveur utilise un appel système (`select()` ou `poll()`) pour surveiller simultanément plusieurs descripteurs de fichiers (sockets clients, sockets d'écoute) sans bloquer le programme.

### Gestion des sockets

Le cycle de vie d'une connexion suit les étapes classiques :

```
socket() → bind() → listen() → accept() → recv/send() → close()
```

### Parsing HTTP

Le serveur parse manuellement les requêtes HTTP entrantes (méthode, URI, headers, body) et construit les réponses en respectant le protocole HTTP/1.1.

### CGI (Common Gateway Interface)

Pour les routes configurées avec `cgi_pass`, le serveur `fork()` un processus fils, transmet les données de la requête via les variables d'environnement et `stdin`, puis lit la réponse sur `stdout`.

---

## 🌍 Langages & Technologies

| Technologie | Usage                     |
|-------------|---------------------------|
| C++98       | Langage principal          |
| HTML/CSS    | Pages web servies          |
| Python      | Scripts CGI                |
| Makefile    | Compilation                |

---

## 📚 Ressources utiles

- [RFC 7230 — HTTP/1.1 Message Syntax](https://tools.ietf.org/html/rfc7230)
- [Documentation NGINX — directives](https://nginx.org/en/docs/dirindex.html)
- [MDN — HTTP](https://developer.mozilla.org/fr/docs/Web/HTTP)

---

## 👤 Auteur

**Zkevitz** — École 42

> *"Le but du projet WebServ est de comprendre comment fonctionne un serveur HTTP en l'implémentant soi-même, de la socket à la réponse."*