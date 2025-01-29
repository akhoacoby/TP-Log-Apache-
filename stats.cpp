#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Stats {
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
        // Utilisation de url_map au lieu de Url_map
        for (const auto& entry : url_map) {
            const string& log_cible = entry.first;  
            const string& log_ref = entry.second.second;  

            int nb = 0;  

            // Comparaison sur url_map
            for (const auto& entry_2 : url_map) {
                if (entry_2.first == log_cible && entry_2.second.second == log_ref) {
                    nb++;  
                }
            }

            graph_vec.push_back(make_pair(log_cible, make_pair(nb, log_ref)));
        }

        vector<pair<string, int>> top_urls;
        vector<string> already_seen;

        for (const auto& entry : graph_vec) {
            string log_cible = entry.first;

            if (find(already_seen.begin(), already_seen.end(), log_cible) == already_seen.end()) {
                int nb = 0;

                for (const auto& entry_2 : graph_map) {
                    if (entry_2.first == log_cible) {
                        nb += entry_2.second.first;
                    }
                }

                top_urls.push_back(make_pair(log_cible, nb));
                already_seen.push_back(log_cible);
            }
        }

        sort(top_urls.begin(), top_urls.end(), [](auto& a, auto& b) { return a.second > b.second; });

        cout << "Top 10 pages consultées:\n";
        for (size_t i = 0; i < min(top_urls.size(), size_t(10)); i++) {
            cout << top_urls[i].first << "(-> " << top_urls[i].second << " hits)\n";
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

        for (int i = 0; i < graph_vec.size(); i++) {
            fichier << "node" << i << " [label=\"" << graph_vec[i].first << "\"];\n"; 
            fichier << "node" << i << "->" << graph_vec[i].second.second << " [label=\"" << graph_vec[i].second.first << "\"];\n";
        }

        // Générer la fin du fichier GraphViz
        fichier << "}\n";

        // Fermer le fichier après écriture
        fichier.close();
    }

    // Filtrer les extensions des fichiers (ex. .jpg, .css, .js)
    void filtrerExtensions() 
    {
        for (auto it = url_map.begin(); it != url_map.end();) {
            string url = it->first;
            if (url.find(".jpg") != string::npos || 
                url.find(".css") != string::npos || 
                url.find(".js") != string::npos) {
                it = url_map.erase(it);  
            } 
            else {
                ++it;  
            }
        }
    }

    // Filtrer par heure
    void filtrerParHeure(int heure) 
    {
        for (auto it = url_map.begin(); it != url_map.end();) {
            // Calcul de l'heure réelle en prenant en compte les informations du décalage horaire
            int log_heure = it->second.first.hour;
            int log_minute = it->second.first.minute;
            int decalage_signe = it->second.first.zone.signe;
            int decalage_heure = it->second.first.zone.hour; 
            int decalage_minute = it->second.first.zone.minute;

            double heure_reelle = log_heure + log_minute / 60.0 + decalage_signe * (decalage_heure + decalage_minute / 60.0);

            // Comparaison de l'heure réelle
            if (heure_reelle < heure || heure_reelle >= heure + 1) {
                it = url_map.erase(it);
            } 
            else {
                ++it;
            }
        }
    }

private:
    unordered_map<string, pair<Date_time, string>> url_map;  
    vector<pair<string, pair<int, string>>> graph_vec;  
};
