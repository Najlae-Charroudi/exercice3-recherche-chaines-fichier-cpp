#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

// Recherche avec find()
bool contientFind(string chaine, string mot)
{
    return chaine.find(mot) != string::npos;
}

// Recherche sans find()
bool contientSansFind(string chaine, string mot)
{
    int n = chaine.length();
    int m = mot.length();

    if (m > n)
        return false;

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;

        while (j < m && chaine[i + j] == mot[j])
        {
            j++;
        }

        if (j == m)
            return true;
    }

    return false;
}

int main()
{
    vector<string> mots;
    string nomFichier;
    string ligne;
    string mot;

    // Nom du fichier
    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    // Ouverture du fichier
    ifstream fichier(nomFichier);

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    // Lecture du fichier et remplissage du vector
    while (getline(fichier, ligne))
    {
        mots.push_back(ligne);
    }

    fichier.close();

    cout << "\nNombre de chaines lues : "
         << mots.size() << endl;

    // Mot à rechercher
    cout << "Donner le mot a chercher : ";
    cin >> mot;

    // =========================
    // Recherche avec find()
    // =========================

    auto debutFind = chrono::high_resolution_clock::now();

    bool trouveFind = false;

    for (int i = 0; i < mots.size(); i++)
    {
        if (contientFind(mots[i], mot))
        {
            trouveFind = true;
            break;
        }
    }

    auto finFind = chrono::high_resolution_clock::now();

    auto dureeFind =
        chrono::duration_cast<chrono::nanoseconds>(
            finFind - debutFind
        );

    // =========================
    // Recherche sans find()
    // =========================

    auto debutSansFind = chrono::high_resolution_clock::now();

    bool trouveSansFind = false;

    for (int i = 0; i < mots.size(); i++)
    {
        if (contientSansFind(mots[i], mot))
        {
            trouveSansFind = true;
            break;
        }
    }

    auto finSansFind = chrono::high_resolution_clock::now();

    auto dureeSansFind =
        chrono::duration_cast<chrono::nanoseconds>(
            finSansFind - debutSansFind
        );

    // =========================
    // Affichage des résultats
    // =========================

    if (trouveFind)
        cout << "\n[Avec find] Le mot \"" << mot
             << "\" existe dans le fichier." << endl;
    else
        cout << "\n[Avec find] Le mot \"" << mot
             << "\" n'existe pas dans le fichier." << endl;

    if (trouveSansFind)
        cout << "[Sans find] Le mot \"" << mot
             << "\" existe dans le fichier." << endl;
    else
        cout << "[Sans find] Le mot \"" << mot
             << "\" n'existe pas dans le fichier." << endl;

    // Temps
    cout << "\nTemps avec find : "
         << dureeFind.count() << " ns" << endl;

    cout << "Temps sans find : "
         << dureeSansFind.count() << " ns" << endl;

    return 0;
}
