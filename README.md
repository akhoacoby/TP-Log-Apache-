# TP-Log-Apache

## Classe `lecture`
**Attributs :**
- 'ligne' (istream)
**Constructeurs/Destructeurs :**

**Méthodes :**
- Lire une ligne et appeler le constructeur de `log`

---

## Classe `log`
**Attributs :**
- `IP` (str) : Adresse IP
- `User_logname` (str) : Nom d'utilisateur du log
- `Authenticated_user` (str) : Utilisateur authentifié
- **`Date/heure`** (struct) : Date et heure
- **`Requête`** (struct) : Requête HTTP
- `statut` (int) : Code de statut HTTP
- `taille` (unsigned int) : Taille de la réponse
- **`Referer`** (str) : URL référente
- `Id_Client` (str) : Identifiant du client

**Constructeurs/Destructeurs :**
- Par défaut
- Argument : (str) ligne
- Destructeur

**Méthodes :**
- `Affichage` (surcharge de l'opérateur `<<` pour `cout`)

---

## Classe `stats`
**Attributs :**
- `url_map` (unordered map) : clé : url, valeur : [date/heure, Referer]

**Constructeurs/Destructeurs :**
- Par défaut
- Destructeur

	**Méthodes :**
  - 'Ajouter un log' 
  - 'Statistiques' : compter le top 10 (avec options de séléction -e, -t et d'affichage du graphe -g) 
