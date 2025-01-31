
#include "stats.h"



Stats::Stats() {}

    // Méthode pour ajouter un log dans la map
    void Stats::ajouter(const Log& nouveau_log)
    {
        // Ajouter l'URL et ses informations associées dans la map
        url_map.insert({nouveau_log.Request.url, make_tuple(nouveau_log.Date_time, nouveau_log.referer,nouveau_log.Request.extension)});

    /*    for (const auto& entry : url_map) {
       std::cout << "Clé: " << entry.first
                 << " -> Description: " << std::get<1>(entry.second)
                 << " -> Autre info: " << std::get<2>(entry.second)
                 << endl;
    }test */
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
        //remplir le graph
        for (const auto& entry : url_map) {
            const string& log_cible = entry.first;
            const string& log_ref = get<1>(entry.second);

            int nb = 0;

            for (const auto& entry_2 : url_map) {
                if (entry_2.first == log_cible && get<1>(entry_2.second)== log_ref) {
                    nb++;
                }
            }

            graph_vec.push_back(make_pair(log_cible, make_pair(nb, log_ref)));
        }

        // Générer le début du fichier GraphViz
        fichier << "digraph G {\n";

        for (int i = 0; i < graph_vec.size(); i++) {
            fichier << "node" + to_string(i) << " [label=\"" << graph_vec[i].first << "\"];\n";
            fichier << "node" + to_string(i) << "->" << graph_vec[i].second.second << " [label=\"" << graph_vec[i].second.first << "\"];\n";
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
