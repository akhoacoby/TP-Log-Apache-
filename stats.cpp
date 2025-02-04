
#include "stats.h"




Stats::Stats() {}

    // Méthode pour ajouter un log dans la map
    void Stats::ajouter(const SimpleLog& nouveau_log)
    {
        // Ajouter l'URL et ses informations associées dans la map
        url_map.insert({nouveau_log.Request.url, make_tuple(nouveau_log.Date_time, nouveau_log.referer,nouveau_log.Request.extension)});

  }

    // Méthode pour afficher les top 10 des pages consultées
    void Stats::afficherTop10() const
    {
        vector<pair<string, int>> top_urls;
        vector<string> already_seen;

        for (const auto& entry : url_map) {
            const string log_cible = entry.first;

            if (find(already_seen.begin(), already_seen.end(),log_cible) == already_seen.end())
            {
                int nb = 0;

                for (const auto& entry_2 : url_map)
                {

                    if (entry_2.first == log_cible)
                    {
                        nb ++;
                    }


                  }

                top_urls.push_back(make_pair(log_cible, nb));
                already_seen.push_back(log_cible);
            }
        }

        sort(top_urls.begin(), top_urls.end(), [](auto& a, auto& b) { return a.second > b.second; });

        cout << "Top 10 pages consultées :\n";
      size_t limit = min(top_urls.size(), size_t(10));
      for (size_t i = 0; i < limit; i++) {
          cout << top_urls[i].first << "(" << top_urls[i].second << " hits)\n";
      }
      if (limit == 0) {
          cout << "No pages to display." << endl;
      }


    }

    // Méthode pour générer un fichier GraphViz pour les URLs
    void Stats::genererGraphViz(const string& fichier_dot) {
        // Ouvrir ou créer le fichier pour l'écriture
        ofstream fichier(fichier_dot);

        if (!fichier.is_open()) {
            cerr << "Erreur d'ouverture du fichier !" << endl;
            return;
        }

        //construire la map node
        unordered_map<string, string> node_map;
        vector<string> already_seen;
        int i=0;
        for (const auto& entry : url_map) {
            string url_1 = entry.first;
            string url_2 = get<1>(entry.second);

            if (find(already_seen.begin(), already_seen.end(),url_1) == already_seen.end())
            {
                i++;
                node_map.insert({url_1, "node" + to_string(i)});
                already_seen.push_back(url_1);
            }
            if (find(already_seen.begin(), already_seen.end(),url_2) == already_seen.end())
            {
                i++;
                node_map.insert({url_2, "node" + to_string(i)});
                already_seen.push_back(url_2);
            }

        }


        //construire le graph des noeuds
        unordered_map<string, pair<string,int>> graph_map;
        vector<string> node_seen;

        for (const auto& entry : url_map) {
            const string& url_cible = entry.first;
            const string& url_ref = get<1>(entry.second);

            int nb = 0;

            for (const auto& entry_2 : url_map) {

                if (entry_2.first == url_cible && get<1>(entry_2.second)== url_ref
                && find(node_seen.begin(), node_seen.end(),url_cible) == node_seen.end() ) {
                    nb++;

                }
            }

            graph_map.insert({node_map[url_cible],make_pair(node_map[url_ref],nb)});
            node_seen.push_back(url_cible);

        }

        // Générer le début du fichier GraphViz
        fichier << "digraph G {\n";
        for (const auto& entry : node_map)
        {
          fichier << entry.second << " [label=\"" << entry.first << "\"];\n";
        }

        for (const auto& entry : graph_map)
        {
          fichier << entry.first <<" -> "<<entry.second.first<<"  [label=\"" << entry.second.second << "\"];\n";
        }



        // Générer la fin du fichier GraphViz
        fichier << "}\n";

        // Fermer le fichier après écriture
        fichier.close();
    }

    // Filtrer les extensions des fichiers (ex. .jpg, .css, .js)
    void Stats::filtrerExtensions()
    {
        for (auto it = url_map.begin(); it != url_map.end();){
          string extension = get<2>(it->second);
          if (extension =="jpg"|| extension =="css"||extension =="js")
              {
                it=url_map.erase(it);

            }
            else {
                ++it;
            }
        }

    }



    // Filtrer par heure
    void Stats::filtrerParHeure(int heure)
    {

        for (auto it = url_map.begin(); it != url_map.end();)
        {
            // Calcul de l'heure réelle en prenant en compte les informations du décalage horaire
            int log_heure = get<0>(it->second).hour;
            int log_minute = get<0>(it->second).minute;
            int decalage_signe = get<0>(it->second).zone.signe;
            int decalage_heure = get<0>(it->second).zone.hour;
            int decalage_minute = get<0>(it->second).zone.minute;

            double heure_reelle = log_heure + log_minute / 60.0 + decalage_signe * (decalage_heure + decalage_minute / 60.0);

            // Comparaison de l'heure réelle
            if (heure_reelle < heure || heure_reelle >= heure + 1)
            {
                it=url_map.erase(it);
            }
            else
            {
                ++it;
            }

        }

}
