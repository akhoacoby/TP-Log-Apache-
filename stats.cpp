#include "Stats.h"


class Stats 
{
    public:

    // Constructeur par défaut
    Stats() {}

    // Méthode pour ajouter un log dans la map
    void ajouter(const Log& nouveau_log) 
    {
        // Ajouter l'URL et ses informations associées dans la map
        url_map[nouveau_log.getRequest().url] = 
            make_pair(nouveau_log.getDate_time(), nouveau_log.getReferer());
    }

    // Méthode pour afficher les top 10 des pages consultées
    void afficherTop10() const 
    {
        // Créer un vecteur à partir de la map pour trier par nombre de visites
        vector<pair<string, int>> top_urls;

        for (const auto& entry : url_map) 
        {
            // On ajoute l'URL et le nombre de visites (le second élément de la paire)
            top_urls.push_back(make_pair(entry.first, entry.second.second));
        }

        // Trier les URLs par nombre de visites décroissant
        sort(top_urls.begin(), top_urls.end(), [](auto& a, auto& b) { return a.second > b.second; });

        // Afficher les top 10
        cout << "Top 10 pages consultées:\n";
        for (size_t i = 0; i < min(top_urls.size(), size_t(10)); i++) 
        {
            cout << top_urls[i].first << " -> " << top_urls[i].second << " fois\n";
        }
    }

    // Méthode pour générer un fichier GraphViz pour les URLs
    void genererGraphViz(const string& fichier_dot) const {
        // Ouvrir ou créer le fichier pour l'écriture
        ofstream fichier(fichier_dot);

        if (!fichier.is_open()) {
            cerr << "Erreur d'ouverture du fichier !" << endl;
            return;
        }

        // Générer le début du fichier GraphViz
        fichier << "digraph G {\n";

        // Pour chaque URL, générer un nœud dans le graphe
        for (const auto& entry : url_map) {
            fichier << "    \"" << entry.first << "\" [label=\"" << entry.first << " (" << entry.second.second << ")\"];\n";
        }

        // Générer la fin du fichier GraphViz
        fichier << "}\n";

        // Fermer le fichier après écriture
        fichier.close();
    }
    void filtrerExtensions() 
    {
    for (auto it = url_map.begin(); it != url_map.end();) 
    {
    string extension = it->first.request.extention;
    if (it->first.find(".jpg") != string::npos || 
    it->first.find(".css") != string::npos || 
    it->first.find(".js") != string::npos) 
    {
        it = url_map.erase(it);  
    } 
    else 
    {
        ++it;  
    }
    }

    }

void filtrerParHeure(int heure) 
{
    for (auto it = url_map.begin(); it != url_map.end();) 
    {

        int log_heure =it->second.first.hour;
        int log_minute=it->second.first.minute;
        int decalage_signe=it->second.first.zone.signe;
        int decalage_heure=it->second.first.zone.hour; 
        int decalage_minute=it->second.first.zone.minute;
        double heure_reelle= log_heure+ log_minute/60 + decalage_signe*(decalage_heure+ decalage_minute/60)
        if (heure_log < heure|| heure_log >= heure+1) {
            it = url_map.erase(it);
        } 
        else 
        {
            ++it;
        }
    }
}

private:
     unordered_map<string, pair<Date_time, string>> url_map;  
    // La map qui stocke les informations des URLs
};
