#include "Automaton.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace fa {
/**
 * Operateur permettant de savoir si 2 transitions sont similaires
 */
bool operator==(struct Transition a, struct Transition b) {
  if (a.from == b.from && a.symbol == b.symbol && a.to == b.to)
    return true;
  else
    return false;
}

/**
 * Operateur permettant de savoir si 2 set contiennent les même int
 */
bool operator==(std::set<int> set_1, std::set<int> set_2) {
  bool find = false;
  for (int i1 : set_1) {
    find = false;
    for (int i2 : set_2) {
      if (i1 == i2) {
        find = true;
      }
    }
    if (find == false) {
      return false;
    }
  }
  for (int i2 : set_2) {
    find = false;
    for (int i1 : set_1) {
      if (i2 == i1) {
        find = true;
      }
    }
    if (find == false) {
      return false;
    }
  }
  return true;
}

Automaton::Automaton() {}

/**
 * Tell if an automaton is valid .
 *
 * A valid automaton has a non - empty set of states and
 * a non - empty set of symbols
 */
bool Automaton::isValid() const {
  if (set_of_states.size() == 0 || alphabet.size() == 0) {
    return false;
  }
  return true;
}

/**
 * Add a symbol to the automaton
 *
 * Epsilon is not a valid symbol.
 * Returns true if the symbol was effectively added
 */
bool Automaton::addSymbol(char symbol) {
  if (isgraph(symbol) && hasSymbol(symbol) == false) {
    alphabet.insert(symbol);
    return true;
  }
  return false;
}

/**
 * Remove a symbol from the automaton
 *
 * Returns true if the symbol was effectively removed
 */
bool Automaton::removeSymbol(char symbol) {
  if (alphabet.find(symbol) != alphabet.end()) {
    alphabet.erase(symbol);
    // Supprime les transitions contenant le symbole
    for (auto& t : set_of_transitions) {
      if (t.symbol == symbol) {
        removeTransition(t.from, t.symbol, t.to);
      }
    }
    return true;
  }
  return false;
}

/**
 * Tell if the symbol is present in the automaton
 */
bool Automaton::hasSymbol(char symbol) const {
  if (alphabet.find(symbol) != alphabet.end()) {
    return true;
  }
  return false;
}

/**
 * Count the number of symbols
 */
std::size_t Automaton::countSymbols() const { return alphabet.size(); }

/**
 * Add a state to the automaton.
 *
 * By default, a newly added state is not initial and not final.
 * Returns true if the state was effectively added and false otherwise.
 */
bool Automaton::addState(int state) {
  if (state < 0 || hasState(state)) {
    return false;
  }
  struct State s = {false, false};
  set_of_states.insert({state, s});
  return true;
}

/**
 * Remove a state from the automaton.
 *
 * The transitions involving the state are also removed.
 * Returns true if the state was effectively removed and false otherwise.
 */
bool Automaton::removeState(int state) {
  if (hasState(state)) {
    // Supprime l'état
    set_of_states.erase(state);

    std::vector<struct Transition> transition_to_delete;

    // Supprime les transitions contenant l'état supprimé
    for (auto& t : set_of_transitions) {
      if (t.from == state || t.to == state) {
        transition_to_delete.push_back(t);
      }
    }

    // Suppression des transitions concernées
    for (auto& t : transition_to_delete) {
      set_of_transitions.erase(
          std::remove(set_of_transitions.begin(), set_of_transitions.end(), t),
          set_of_transitions.end());
    }

    return true;
  }
  return false;
}

/**
 * Tell if the state is present in the automaton.
 */
bool Automaton::hasState(int state) const {
  if (set_of_states.find(state) != set_of_states.end()) {
    return true;
  }
  return false;
}

/**
 * Compute the number of states.
 */
std::size_t Automaton::countStates() const { return set_of_states.size(); }

/**
 * Set the state initial.
 */
void Automaton::setStateInitial(int state) {
  if (hasState(state)) {
    auto it = set_of_states.find(state);
    it->second.isInitial = true;
  }
}

/**
 * Tell if the state is initial.
 */
bool Automaton::isStateInitial(int state) const {
  if (hasState(state)) {
    auto it = set_of_states.find(state);
    if (it->second.isInitial == true) {
      return true;
    }
  }
  return false;
}

/**
 * Set the state final.
 */
void Automaton::setStateFinal(int state) {
  if (hasState(state)) {
    auto it = set_of_states.find(state);
    it->second.isFinal = true;
  }
}

/**
 * Tell if the state is final.
 */
bool Automaton::isStateFinal(int state) const {
  if (hasState(state)) {
    auto it = set_of_states.find(state);
    if (it->second.isFinal == true) {
      return true;
    }
  }
  return false;
}

/**
 * Add a transition
 *
 * Returns true if the transition was effectively added and false otherwise.
 * If one of the state or the symbol does not exists, the transition is not
 * added.
 */
bool Automaton::addTransition(int from, char alpha, int to) {
  struct Transition t = {from, alpha, to};
  if ((hasSymbol(alpha) || alpha == fa::Epsilon) && hasState(from) &&
      hasState(to) && !hasTransition(from, alpha, to)) {
    set_of_transitions.push_back(t);

    return true;
  }
  return false;
}

/**
 * Remove a transition
 *
 * Returns true if the transition was effectively removed and false otherwise.
 */
bool Automaton::removeTransition(int from, char alpha, int to) {
  struct Transition t = {from, alpha, to};
  if (hasTransition(from, alpha, to)) {
    set_of_transitions.erase(
        std::remove(set_of_transitions.begin(), set_of_transitions.end(), t),
        set_of_transitions.end());
    return true;
  }
  return false;
}

/**
 * Tell if a transition is present.
 */
bool Automaton::hasTransition(int from, char alpha, int to) const {
  struct Transition t = {from, alpha, to};
  auto it = std::find(set_of_transitions.begin(), set_of_transitions.end(), t);

  if (it != set_of_transitions.end()) {
    return true;
  }
  return false;
}

/**
 * Compute the number of transitions.
 */
std::size_t Automaton::countTransitions() const {
  return set_of_transitions.size();
}

/**
 * Print the automaton in a friendly way
 */
void Automaton::prettyPrint(std::ostream& os) const {
  os << "Initial states:\n\t";
  for (auto& s : set_of_states) {
    if (isStateInitial(s.first)) {
      os << s.first << ' ';
    }
  }

  os << "\nFinal states:\n\t";
  for (auto& s : set_of_states) {
    if (isStateFinal(s.first)) {
      os << s.first << ' ';
    }
  }

  os << "\nTransitions:";
  for (auto& s : set_of_states) {
    os << "\n\tFor state " << s.first << " :";
    for (auto& a : alphabet) {
      os << "\n\t\tFor letter " << a << " : ";
      for (auto& t : set_of_transitions) {
        if (t.from == s.first && t.symbol == a) {
          os << t.to << ' ';
        }
      }
    }
  }
  os << '\n';
}

/**
 * Tell if the automaton has one or more epsilon-transition
 */
bool Automaton::hasEpsilonTransition() const {
  for (auto& t : set_of_transitions) {
    if (t.symbol == fa::Epsilon) {
      return true;
    }
  }
  return false;
}

/**
 * Tell if the automaton is deterministic
 */
bool Automaton::isDeterministic() const {
  int nb_initial_states = 0;
  int nb_final_states = 0;
  for (auto& s : set_of_states) {
    if (isStateInitial(s.first)) {
      nb_initial_states += 1;
    }
    if (isStateFinal(s.first)) {
      nb_final_states += 1;
    }
  }

  // Un état initial
  if (nb_initial_states != 1) {
    return false;
  }

  // Gestion des transitions
  for (auto& t1 : set_of_transitions) {
    // Pas de Epsilon transition
    if (t1.symbol == fa::Epsilon) {
      return false;
    }

    // Une transition partant d'un état avec le même symbole au maximum
    for (auto& t2 : set_of_transitions) {
      if (t1.from == t2.from && t1.symbol == t2.symbol && t1.to != t2.to) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Tell if the automaton is complete
 */
bool Automaton::isComplete() const {
  bool find = false;
  // Une transition par symbole à chaque état
  for (auto& s : set_of_states) {
    for (auto& a : alphabet) {
      find = false;
      for (auto& t : set_of_transitions) {
        if (t.from == s.first && t.symbol == a) {
          find = true;
        }
      }
      if (!find) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Permet de savoir si un état est accessible depuis un état initial
 */
void Automaton::find_state(std::set<int>& statesBrowseGlobal,
                           std::set<int>& statesBrowseLocal, int state_to_find,
                           int state) const {
  // Déjà parcouru pour cet état
  if (statesBrowseLocal.find(state) != statesBrowseLocal.end()) {
    return;
  }
  statesBrowseLocal.insert(state);

  // Etat trouvé donc accessible
  if (state_to_find == state) {
    statesBrowseGlobal.insert(state_to_find);
    return;
  }

  // On continue à parcourir
  if (state_to_find != state) {
    for (auto& t : set_of_transitions) {
      if (t.from == state) {
        find_state(statesBrowseGlobal, statesBrowseLocal, state_to_find, t.to);
      }
    }
  }
}

/**
 * Remove non-accessible states
 */
void Automaton::removeNonAccessibleStates() {
  std::set<int> statesBrowseGlobal;
  std::set<int> statesBrowseLocal;

  // Trouver états initiaux
  for (auto& s_initial : set_of_states) {
    if (isStateInitial(s_initial.first)) {
      // Recherche d'accès aux états
      for (auto& s_to_find : set_of_states) {
        statesBrowseLocal.clear();
        if (statesBrowseGlobal.find(s_to_find.first) !=
            statesBrowseGlobal.end()) {
          continue;
        }
        find_state(statesBrowseGlobal, statesBrowseLocal, s_to_find.first,
                   s_initial.first);
      }
    }
  }

  // Si pas d'état inaccessible
  if (statesBrowseGlobal.size() == countStates()) {
    return;
  }

  // Suppprimer transitions avec les états qui n'ont pas été trouvé
  auto it = set_of_transitions.begin();
  while (it != set_of_transitions.end()) {
    if (statesBrowseGlobal.find(it->from) == statesBrowseGlobal.end()) {
      it = set_of_transitions.erase(it);
    } else if (statesBrowseGlobal.find(it->to) == statesBrowseGlobal.end()) {
      it = set_of_transitions.erase(it);
    } else {
      it++;
    }
  }

  // Suppprimer les états qui n'ont pas été trouvé
  for (auto iterator = set_of_states.begin();
       iterator != set_of_states.end();) {
    if (statesBrowseGlobal.find(iterator->first) == statesBrowseGlobal.end()) {
      set_of_states.erase(iterator++);
    } else {
      ++iterator;
    }
  }

  // On renvoie un automate valide
  if (countStates() == 0) {
    addState(0);
    setStateInitial(0);
  }

  if (countSymbols() == 0) {
    addSymbol('a');
  }
}

/**
 * Permet de savoir si on peut atteindre un état final en partant d'un état
 * donné
 */
void Automaton::find_final_state(std::set<int>& statesBrowseGlobal,
                                 std::set<int>& statesBrowseLocal, int state,
                                 int state_begin) const {
  // Déjà parcouru pour cet état
  if (statesBrowseLocal.find(state) != statesBrowseLocal.end()) {
    return;
  }
  statesBrowseLocal.insert(state);

  // Etat final donc co-accessible
  if (isStateFinal(state)) {
    statesBrowseGlobal.insert(state_begin);
    return;
  }

  // On continue à parcourir
  if (!isStateFinal(state)) {
    for (auto& t : set_of_transitions) {
      if (t.from == state) {
        find_final_state(statesBrowseGlobal, statesBrowseLocal, t.to,
                         state_begin);
      }
    }
  }
}

/**
 * Remove non-co-accessible states
 */
void Automaton::removeNonCoAccessibleStates() {
  std::set<int> statesBrowseGlobal;
  std::set<int> statesBrowseLocal;

  // Parcourir tous les états
  for (auto& s : set_of_states) {
    statesBrowseLocal.clear();
    find_final_state(statesBrowseGlobal, statesBrowseLocal, s.first, s.first);
  }

  // Si pas d'état inaccessible
  if (statesBrowseGlobal.size() == countStates()) {
    return;
  }

  // Suppprimer transitions avec les états qui n'ont pas été trouvé
  auto it = set_of_transitions.begin();
  while (it != set_of_transitions.end()) {
    if (statesBrowseGlobal.find(it->from) == statesBrowseGlobal.end()) {
      it = set_of_transitions.erase(it);
    } else if (statesBrowseGlobal.find(it->to) == statesBrowseGlobal.end()) {
      it = set_of_transitions.erase(it);
    } else {
      it++;
    }
  }

  // Suppprimer les états qui n'ont pas été trouvé
  for (auto iterator = set_of_states.begin();
       iterator != set_of_states.end();) {
    if (statesBrowseGlobal.find(iterator->first) == statesBrowseGlobal.end()) {
      set_of_states.erase(iterator++);
    } else {
      ++iterator;
    }
  }

  // On renvoie un automate valide
  if (countStates() == 0) {
    addState(0);
    setStateInitial(0);
  }

  if (countSymbols() == 0) {
    addSymbol('a');
  }
}

/**
 * Permet de parcourir l'automate pour voir s'il a un langage vide
 */
void Automaton::browse_automaton(std::set<int> statesBrowse, int state,
                                 int& nb) const {
  if (statesBrowse.find(state) != statesBrowse.end()) {
    return;
  }

  statesBrowse.insert(state);

  if (isStateFinal(state) == true) {
    nb++;
    return;
  }

  if (isStateFinal(state) == false) {
    for (auto& t : set_of_transitions) {
      if (t.from == state) {
        browse_automaton(statesBrowse, t.to, nb);
      }
    }
  }
}

/**
 * Check if the language of the automaton is empty
 */
bool Automaton::isLanguageEmpty() const {
  int nb_initial_states = 0;
  int nb_final_states = 0;

  std::set<int> empty_set = {};

  for (auto& s : set_of_states) {
    if (isStateInitial(s.first)) {
      nb_initial_states++;
    }
    if (isStateFinal(s.first)) {
      nb_final_states++;
    }
  }
  if (nb_final_states == 0 || nb_initial_states == 0) {
    return true;
  }

  std::set<int> statesBrowse;
  int nb_chemins = 0;
  // Trouver états initiaux
  for (auto& s : set_of_states) {
    if (isStateInitial(s.first)) {
      browse_automaton(statesBrowse, s.first, nb_chemins);
      if (nb_chemins > 0) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Tell if the intersection with another automaton is empty
 */
bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const {
  Automaton automaton_this = *this;
  Automaton automaton_product =
      automaton_product.createProduct(other, automaton_this);
  if (automaton_product.isLanguageEmpty()) {
    return true;
  }
  return false;
}

/**
 * Permet d'obtenir les états accessibles depuis un état grâce à un symbole
 */
std::set<int> Automaton::state_after_move(char next_symbol,
                                          std::set<int> states) const {
  std::set<int> new_states = {};
  for (auto& s : states) {
    for (auto& t : set_of_transitions) {
      if (t.from == s && t.symbol == next_symbol) {
        new_states.insert(t.to);
      }
    }
  }
  return new_states;
}

/**
 * Read the string and compute the state set after traversing the automaton
 */
std::set<int> Automaton::readString(const std::string& word) const {
  std::set<int> states;
  // Trouver états initiaux
  for (auto& s_initial : set_of_states) {
    if (isStateInitial(s_initial.first)) {
      states.insert(s_initial.first);
    }
  }

  // Parcourir les états
  for (std::size_t i = 0; i < word.length(); i++) {
    states = state_after_move(word[i], states);
  }

  return states;
}

/**
 * Tell if the word is in the language accepted by the automaton
 */
bool Automaton::match(const std::string& word) const {
  std::set acccessible_states = readString(word);
  if (acccessible_states.empty()) {
    return false;
  }
  for (auto& state : acccessible_states) {
    if (isStateFinal(state)) {
      return true;
    }
  }

  return false;
}

/**
 * Tell if the langage accepted by the automaton is included in the
 * language accepted by the other automaton
 */
bool Automaton::isIncludedIn(const Automaton& other) const {
  Automaton a = *this;
  Automaton b = createComplement(other);

  if (b.isLanguageEmpty() && !a.isLanguageEmpty()) {
    return false;
  }
  if (a.hasEmptyIntersectionWith(b) == true) {
    return true;
  }
  return false;
}

/**
 * Create a mirror automaton
 */
Automaton Automaton::createMirror(const Automaton& automaton) {
  Automaton automaton_local;

  for (auto& s : automaton.set_of_states) {
    automaton_local.addState(s.first);
    if (automaton.isStateFinal(s.first)) {
      automaton_local.setStateInitial(s.first);
    }
    if (automaton.isStateInitial(s.first)) {
      automaton_local.setStateFinal(s.first);
    }
  }

  for (auto& a : automaton.alphabet) {
    automaton_local.addSymbol(a);
  }

  for (auto& t : automaton.set_of_transitions) {
    automaton_local.addTransition(t.to, t.symbol, t.from);
  }
  return automaton_local;
}

/**
 * Create a complete automaton, if not already complete
 */
Automaton Automaton::createComplete(const Automaton& automaton) {
  if (automaton.isComplete()) {
    return automaton;
  }
  long new_state = 0;

  Automaton automaton_local = automaton;
  while (automaton.hasState(new_state)) {
    new_state += 1;
  }
  automaton_local.addState(new_state);

  bool hasSymbolTransition = false;
  for (auto& a : automaton_local.alphabet) {
    for (auto& s : automaton_local.set_of_states) {
      for (auto& t : automaton_local.set_of_transitions) {
        if (t.from == s.first && t.symbol == a) {
          hasSymbolTransition = true;
          break;
        }
      }
      if (!hasSymbolTransition) {
        automaton_local.addTransition(s.first, a, new_state);
      }
      hasSymbolTransition = false;
    }
  }
  return automaton_local;
}

/**
 * Create a complement automaton
 */
Automaton Automaton::createComplement(const Automaton& automaton) {
  Automaton complete_deterministic_automaton = createComplete(automaton);
  complete_deterministic_automaton =
      complete_deterministic_automaton.createDeterministic(
          complete_deterministic_automaton);

  Automaton automaton_local;
  for (auto& s : complete_deterministic_automaton.set_of_states) {
    automaton_local.addState(s.first);
    if (!complete_deterministic_automaton.isStateFinal(s.first)) {
      automaton_local.setStateFinal(s.first);
    }
    if (complete_deterministic_automaton.isStateInitial(s.first)) {
      automaton_local.setStateInitial(s.first);
    }
  }

  for (auto& a : complete_deterministic_automaton.alphabet) {
    automaton_local.addSymbol(a);
  }

  for (auto& t : complete_deterministic_automaton.set_of_transitions) {
    automaton_local.addTransition(t.from, t.symbol, t.to);
  }

  return automaton_local;
}

/**
 * Create the product of two automata
 *
 * The product of two automata accept the intersection of the two languages.
 */
Automaton Automaton::createProduct(const Automaton& lhs, const Automaton& rhs) {
  Automaton product_automaton;
  std::map<int, std::pair<int, int>> states_product;

  // Création du set regroupant les nouveaux états et leurs états de départ
  int nb_new_state = 0;
  for (auto& s_lhs : lhs.set_of_states) {
    for (auto& s_rhs : rhs.set_of_states) {
      std::pair<int, int> state_lhs_x_rhs = {s_lhs.first, s_rhs.first};
      states_product.insert({nb_new_state, state_lhs_x_rhs});
      nb_new_state++;
    }
  }

  // Ajout des états à l'automate produit, en ajoutant final et initial
  for (auto& s : states_product) {
    int num_etat_lhs = s.second.first;
    int num_etat_rhs = s.second.second;
    product_automaton.addState(s.first);

    if (lhs.isStateInitial(num_etat_lhs) && rhs.isStateInitial(num_etat_rhs)) {
      product_automaton.setStateInitial(s.first);
    }

    if (lhs.isStateFinal(num_etat_lhs) && rhs.isStateFinal(num_etat_rhs)) {
      product_automaton.setStateFinal(s.first);
    }
  }

  // Parcours de chaque états pour ajouter les transitions
  for (auto& s1 : states_product) {
    int num_etat_depart = s1.first;
    int from_lhs1 = s1.second.first;
    int from_rhs1 = s1.second.second;
    // parcours des transitions de lhs
    for (auto& t_lhs : lhs.set_of_transitions) {
      if (from_lhs1 == t_lhs.from) {
        // parcours des transitions de rhs
        for (auto& t_rhs : rhs.set_of_transitions) {
          if (from_rhs1 == t_rhs.from && t_lhs.symbol == t_rhs.symbol) {
            // Trouver le numéro de l'état à relier
            for (auto& s2 : states_product) {
              int num_etat_arriver = s2.first;
              int arriver_lhs2 = s2.second.first;
              int arriver_rhs2 = s2.second.second;
              if (arriver_lhs2 == t_lhs.to && arriver_rhs2 == t_rhs.to) {
                if (!product_automaton.hasSymbol(t_rhs.symbol)) {
                  product_automaton.addSymbol(t_rhs.symbol);
                }
                product_automaton.addTransition(num_etat_depart, t_rhs.symbol,
                                                num_etat_arriver);
              }
            }
          }
        }
      }
    }
  }

  // On renvoie un automate valide
  if (product_automaton.countStates() == 0) {
    product_automaton.addState(0);
    product_automaton.setStateInitial(0);
  }

  if (product_automaton.countSymbols() == 0) {
    product_automaton.addSymbol('a');
  }

  return product_automaton;
}

/**
 * Create a deterministic automaton, if not already deterministic
 */
Automaton Automaton::createDeterministic(const Automaton& other) {
  if (other.isDeterministic()) {
    return other;
  }

  /**
   * Remplissage de la table
   */

  // Trouver les états initiaux
  std::set<int> states;
  int nb_etats_initiaux = 0;
  for (auto& s : other.set_of_states) {
    if (other.isStateInitial(s.first)) {
      states.insert(s.first);
      nb_etats_initiaux++;
    }
  }

  // Regarder si l'ensemble d'états du set appartient déjà à la map
  std::vector<Determinisation> table_determinisme;
  std::vector<Correspondance> table_correspondance;

  // Ajout du set de départ à la table de correspondance
  table_correspondance.push_back({0, states});

  int ligne_en_cours_de_calcul = 0;
  int num_etat = 1;

  while (ligne_en_cours_de_calcul < num_etat) {
    for (auto& t : table_correspondance) {
      if (t.nouvel_etat == ligne_en_cours_de_calcul) {
        std::set<int> etat_en_cours = t.ensemble_etats;
        // Calcul pour toute les lettres de l'alphabet
        std::vector<std::set<int>> elements_ligne_map;

        for (auto& a : other.alphabet) {
          std::set<int> etats_accessible =
              other.state_after_move(a, etat_en_cours);
          table_determinisme.push_back({etat_en_cours, a, etats_accessible});

          // Ajout à la table de correspondance si non présent
          bool isPresent = false;
          for (auto& t : table_correspondance) {
            if (t.ensemble_etats == etats_accessible) {
              isPresent = true;
              break;
            }
          }
          if (!isPresent) {
            table_correspondance.push_back({num_etat, etats_accessible});
            num_etat++;
          }
        }
        ligne_en_cours_de_calcul++;
        break;
      }
    }
  }

  /**
   * Création de l'automate
   */
  Automaton deterministic_automaton;

  // Ajout alphabet
  std::vector<char> alphabet_tab;
  for (auto& a : other.alphabet) {
    deterministic_automaton.addSymbol(a);
    alphabet_tab.push_back(a);
  }

  // Ajout des états
  for (auto& ligne : table_correspondance) {
    deterministic_automaton.addState(ligne.nouvel_etat);
    bool all_initial = true;
    int nb_etat = 0;
    for (auto& etat_other : ligne.ensemble_etats) {
      nb_etat++;
      if (other.isStateFinal(etat_other)) {
        deterministic_automaton.setStateFinal(ligne.nouvel_etat);
      }
      if (!other.isStateInitial(etat_other)) {
        all_initial = false;
      }
    }
    if (all_initial == true && nb_etat == nb_etats_initiaux) {
      deterministic_automaton.setStateInitial(ligne.nouvel_etat);
    }
  }

  // Ajout des transitions
  for (auto& transition : table_determinisme) {
    int state_from = 0;
    int state_to = 0;
    for (auto& state : table_correspondance) {
      if (transition.etat_depart == state.ensemble_etats) {
        state_from = state.nouvel_etat;
      }
      if (transition.etat_arrivee == state.ensemble_etats) {
        state_to = state.nouvel_etat;
      }
    }
    deterministic_automaton.addTransition(state_from, transition.symbol,
                                          state_to);
  }

  return deterministic_automaton;
}

/**
 * Create an equivalent minimal automaton with the Moore algorithm
 */
Automaton Automaton::createMinimalMoore(const Automaton& other) {
  return other;
}

/**
 * Create an equivalent minimal automaton with the Brzozowski algorithm
 */
Automaton Automaton::createMinimalBrzozowski(const Automaton& other) {
  Automaton automaton_minimal = other.createDeterministic(
      other.createMirror(other.createDeterministic(other.createMirror(other))));
  return automaton_minimal;
}

}  // namespace fa
