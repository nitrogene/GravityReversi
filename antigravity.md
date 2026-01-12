# 🪐 Projet Antigravity: Reversi Multi-Agent System

> **Statut du Système :** 🟢 NOMINAL
> **Niveau de Gravité Actuel :** 1 (Mise en place Physique)
> **Dernière mise à jour :** 2026-01-12

## 1. Architecture Manifeste
* **Langage :** C++17 / Qt6 / CMake (pas Ninja)
* **Approche :** Bitboard (unsigned long long)
* **Architecture :** MVC Asynchrone (Core / Controller / Workers / GUI)
* **Dépendances :** Qt Core, Qt Gui, Qt Widgets
* **Délivrable :** Programme dans le répertoire "bin" avec toutes ses dépendances.

## 2. Roadmap & Progression
Cochez les cases au fur et à mesure (`[x]`).

### Phase I: La Physique (The Core)
- [x] Structure de projet CMake/QMake initialisée
- [x] Squelette d'architecture MVC (gui, agents, controller, tests)
- [x] Classe `BitBoard` implémentée (Opérations binaires)
- [x] Règles du Reversi (Coups légaux, Flips)
- [x] Tests Unitaires Core (QTest)

### Phase II: L'Interface (The View)
- [x] Fenêtre principale Qt
- [x] Widget Plateau (Rendu graphique des bitboards)
- [x] Boucle d'événements (Human vs Human)
- [x] Avoir un bouton pour commencer une nouvelle partie
- [x] Avoir sur la droite de l'écran un historique des coups joués
- [ ] Avoir un bouton rewind pour revenir à un coup précédent
- [ ] On doit aussi pouvoir sélectionner un coup dans l'historique pour revenir à ce coup

### Phase III: Les Agents (The Intelligence)
- [x] Interface `IPlayer` (Squelette initial créé)
- [x] Agent `Random` (Le Singe)
- [x] Agent `Greedy` (Le Glouton)
- [x] Agent `Minimax` (Le Calculateur)
- [x] Agent `Minimax` avec une profondeur de recherche variable (Le Calculateur configurable)
- [x] Agent `Minimax` avec élagage Alpha-Bêta (Le Calculateur intelligent) 
- [x] Agent `Minimax` avec élagage Alpha-Bêta et heuristique de positionnement (Le Calculateur encore plus intelligent)
- [ ] Agent `AlphaZero` (Le Calculateur parfait)

## 3. Journal de Bord (Log)
* *Initialisation du protocole Antigravity.*
* **2026-01-11 :** Session majeure.
    * 🏗️ **Infrastructure :** Structure MVC finalisée, configuration CMake réparée (Qt 6.10.1 / MinGW).
    * 🧠 **Core :** `BitBoard` fonctionnel avec gestion des flips et coups légaux.
    * 🎨 **GUI :** Fenêtre principale et rendu du plateau opérationnels (Human vs Human OK).
    * 🧪 **Qualité :** Framework `QTest` intégré. Tests unitaires automatisés validés pour le Core et les Agents.
    * 🤖 **Intelligence :** Premier agent IA (`RandomAgent`) implémenté et testé.
* **2026-01-12 :** Session de debug et finalisation de l'IA + Améliorations GUI.
    * 🛠️ **Infrastructure :** Résolution des problèmes de build (Ninja + MinGW). Le binaire `bin/GravityReversi.exe` est pleinement opérationnel.
    * 🧠 **Core :** Correction d'un bug critique dans `BitBoard::getPossibleMoves` (placement interdit sur cases occupées).
    * 🤖 **Intelligence :** `MinimaxAgent` implémenté avec succès (Alpha-Bêta, Heuristique de poids/position, profondeur ajustable).
    * 🎨 **GUI :** Implémentation du bouton "Nouvelle Partie" et du panneau "Historique des coups".
* **État Actuel au 12/01 au soir :** 🟢 NOMINAL. Le moteur de jeu est solide, les IA de base sont performantes, et l'interface utilisateur commence à être riche.
* **Prochaine étape prioritaire pour la reprise :** Implémentation de la fonction **Rewind** (annulation de coup) pour permettre l'analyse de jeu et la navigation dans l'historique.

## 4. Directives Opérationnelles (AI RULES)
⚠️ **RÈGLES CRITIQUES POUR L'AGENT IA** ⚠️

1.  **GESTION GIT :**
    * ✅ **AUTORISÉ :** Créer des commits locaux (`git commit`) fréquemment pour sauvegarder la progression.
    * ⛔ **INTERDIT :** Exécuter `git push` vers le serveur distant.
    * **PROCÉDURE :** Demander explicitement la validation de l'utilisateur ("Architecte") avant tout push.
    * **OBLIGATOIRE :** Faire un `git pull` avant chaque session de travail.
    * **OBLIGATOIRE :** Faire un `git commit en fin de session de travail.
    
2.  **MODIFICATION DU CODE :**
    * Toujours vérifier que le projet compile après une modification majeure.
    * Ne jamais supprimer de fichiers existants sans confirmation.

3.  **MAINTENANCE DU CONTEXTE :**
    * Avant de terminer une session, mettre à jour la section "Journal de Bord" de ce fichier.
    * Cocher les cases de la Roadmap au fur et à mesure.
	
---
CurrentVersion: 0.0.1
Branch: main
AutoCommit: true