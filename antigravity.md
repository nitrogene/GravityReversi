# 🪐 Projet Antigravity: Reversi Multi-Agent System

> **Statut du Système :** 🟢 NOMINAL
> **Niveau de Gravité Actuel :** 1 (Mise en place Physique)
> **Dernière mise à jour :** 2026-01-11

## 1. Architecture Manifeste
* **Langage :** C++17 / Qt6
* **Approche :** Bitboard (unsigned long long)
* **Architecture :** MVC Asynchrone (Core / Controller / Workers / GUI)
* **Dépendances :** Qt Core, Qt Gui, Qt Widgets

## 2. Roadmap & Progression
Cochez les cases au fur et à mesure (`[x]`).

### Phase I: La Physique (The Core)
- [x] Structure de projet CMake/QMake initialisée
- [x] Squelette d'architecture MVC (gui, agents, controller, tests)
- [ ] Classe `BitBoard` implémentée (Opérations binaires)
- [ ] Règles du Reversi (Coups légaux, Flips)
- [ ] Tests Unitaires Core (GTest ou QTest)

### Phase II: L'Interface (The View)
- [ ] Fenêtre principale Qt
- [ ] Widget Plateau (Rendu graphique des bitboards)
- [ ] Boucle d'événements (Human vs Human)

### Phase III: Les Agents (The Intelligence)
- [x] Interface `IPlayer` (Squelette initial créé)
- [ ] Agent `Random` (Le Singe)
- [ ] Agent `Greedy` (Le Glouton)
- [ ] Agent `Minimax` (Le Calculateur)

## 3. Journal de Bord (Log)
* *Initialisation du protocole Antigravity.*
* **2026-01-11 :** Structure de fichiers générée (`src/gui`, `src/agents`, `src/controller`, `tests`). `CMakeLists.txt` configuré pour l'auto-détection des sources. Interface `IPlayer.h` initialisée.
* **Prochaine étape :** Implémentation de `BitBoard.cpp/h` et gestion des opérations binaires fondamentales pour le Reversi.

---
CurrentVersion: 0.0.1
Branch: main
AutoCommit: true