# Pile Technique - Reversi Qt6

## Core Stack
* Langage : C++23 (Support MSVC 2026).
* Framework : Qt 6.x (QtWidgets).
* Build System : CMake multi-cibles (App + Plugins).

## Architecture des Plugins (Agents IA)
* App Centrale : Orchestrateur minimal chargeant les plugins.
* Plugin Interface : Definit l'affichage (QtWidgets ou QML).
* Plugins Agents : Definissent l'IA ou le controle humain.
* Configuration : Tout plugin (Vue ou Agent) doit fournir son widget de reglages.

## Architecture Logicielle
* Board : Logique pure C++ bitboard sans dependance Qt.
* Interface : MainWindow gere la grille et le chargement des plugins.
* Decouplage : Le moteur est pret pour une utilisation en mode CLI (Engine Protocol).

## Ressources Externes
* Serveur de test (GGO) : othello.dfk.com:5000
* Documentation Protocole : http://cassio.free.fr/engine-protocol.htm
* Logiciel de référence pour matchs : Cassio (V. 8.4+)