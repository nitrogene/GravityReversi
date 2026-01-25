# Roadmap Reversi

## Phase 1 : Orchestrateur et Interfaces
- Setup du projet multi-plugins.
- Definition de IViewInterface et IAgentInterface.
- Creation du moteur Board (Logique pure).

## Phase 2 : Premieres briques
- Plugin Vue (QtWidgets) : Grille 8x8.
- Plugin Agent (Humain) : Capture les clics souris.
- Plugin Agent (Hasard) : IA simple.

## Phase 3 : Dynamisme
- Gestion des reglages de chaque plugin via l'IHM de la Vue.
- Mode "Headless" (lancement sans plugin Vue).

## Phase 4 : Reseau et IA
- Plugin Agent (Stream Local) : Protocole Engine.
- Plugin Agent (Minimax) : IA avancee.


## Phase 5 : Réseau et IA avancé
- Plugin Agent (Http)
- Plugin Agent Alphago Zero