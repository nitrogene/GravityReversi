import os
import subprocess
import sys

# Force l'encodage UTF-8 pour la console Windows (pour afficher les émojis)
sys.stdout.reconfigure(encoding='utf-8')

# Configuration
MD_FILE = "antigravity.md"

def run_command(command):
    try:
        # shell=True est nécessaire sous Windows pour certaines commandes
        result = subprocess.run(command, shell=True, check=True, text=True, capture_output=True, encoding='utf-8')
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        # On capture aussi l'erreur en utf-8
        print(f"❌ Erreur: {e.stderr}")
        sys.exit(1)

def read_status():
    if not os.path.exists(MD_FILE):
        print(f"❌ {MD_FILE} introuvable.")
        sys.exit(1)
    print(f"✅ {MD_FILE} détecté. Système Antigravity prêt.")

def git_status():
    print("\n🔍 Analyse des changements...")
    # Vérification si git est installé et accessible
    try:
        status = run_command("git status -s")
    except Exception:
        print("❌ Git n'est pas détecté. Assure-toi que Git est installé et dans le PATH.")
        sys.exit(1)

    if not status:
        print("Rien à commiter. L'univers est stable.")
        sys.exit(0)
    print(status)
    return status

def interactive_commit():
    print("\n🚀 Initialisation de la séquence de commit...")
    
    types = ["feat", "fix", "refactor", "docs", "test", "chore"]
    print("Type de changement :")
    for i, t in enumerate(types):
        print(f" [{i}] {t}")
    
    try:
        val = input("Sélection (0-5) : ")
        choice = int(val) if val.isdigit() else 5
        commit_type = types[choice] if 0 <= choice < len(types) else "chore"
    except (ValueError, IndexError):
        commit_type = "chore"

    scope = input("Portée (ex: core, gui) [facultatif] : ").strip()
    message = input("Message de commit : ").strip()
    
    if scope:
        full_msg = f"{commit_type}({scope}): {message}"
    else:
        full_msg = f"{commit_type}: {message}"

    print(f"\nMessage généré : '{full_msg}'")
    confirm = input("Confirmer le tir ? (o/n) : ")
    
    if confirm.lower() == 'o':
        run_command("git add .")
        # Les guillemets sont gérés différemment, on passe une liste si shell=False, 
        # mais avec shell=True on formate la string.
        run_command(f'git commit -m "{full_msg}"')
        print("✅ Code commit dans la capsule.")
        
        push = input("Pousser vers l'origine (git push) ? (o/n) : ")
        if push.lower() == 'o':
            print("🛸 Propulsion vers le remote...")
            run_command("git push")
            print("✨ Terminé.")
    else:
        print("🚫 Annulation.")

if __name__ == "__main__":
    try:
        read_status()
        git_status()
        interactive_commit()
    except KeyboardInterrupt:
        print("\n🚫 Interruption par l'utilisateur.")