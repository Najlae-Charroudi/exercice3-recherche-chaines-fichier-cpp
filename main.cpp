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
    string mot1;
    string mot2;

    // =========================
    // Nom du fichier
    // =========================

    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    // =========================
    // Ouverture du fichier
    // =========================

    ifstream fichier(nomFichier);

    if (!fichier)
    {
        cout << "Erreur : impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    // =========================
    // Lecture du fichier
    // =========================

    while (getline(fichier, ligne))
    {
        mots.push_back(ligne);
    }

    fichier.close();

    cout << "\nNombre de chaines lues : "
         << mots.size() << endl;

    // =========================
    // Saisie des mots
    // =========================

    cout << "Donner le mot a chercher : ";
    cin >> mot1;

    cout << "Donner le mot de remplacement : ";
    cin >> mot2;

    // =========================
    // Recherche avec find()
    // =========================

    auto debutFind = chrono::high_resolution_clock::now();

    bool trouveFind = false;

    for (int i = 0; i < mots.size(); i++)
    {
        if (contientFind(mots[i], mot1))
        {
            trouveFind = true;

            int position = mots[i].find(mot1);

            mots[i].replace(
                position,
                mot1.length(),
                mot2
            );
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
        if (contientSansFind(mots[i], mot1))
        {
            trouveSansFind = true;
        }
    }

    auto finSansFind = chrono::high_resolution_clock::now();

    auto dureeSansFind =
        chrono::duration_cast<chrono::nanoseconds>(
            finSansFind - debutSansFind
        );

    // =========================
    // Résultats
    // =========================

    if (trouveFind)
    {
        cout << "\n[Avec find] Mot trouve et remplace." << endl;
    }
    else
    {
        cout << "\n[Avec find] Mot non trouve." << endl;
    }

    if (trouveSansFind)
    {
        cout << "[Sans find] Mot trouve." << endl;
    }
    else
    {
        cout << "[Sans find] Mot non trouve." << endl;
    }

    // =========================
    // Affichage du vector modifié
    // =========================

    cout << "\nVector apres remplacement :" << endl;

    for (int i = 0; i < mots.size(); i++)
    {
        cout << mots[i] << endl;
    }

    // =========================
    // Temps
    // =========================

    cout << "\nTemps avec find : "
         << dureeFind.count() << " ns" << endl;

    cout << "Temps sans find : "
         << dureeSansFind.count() << " ns" << endl;

    return 0;
}
