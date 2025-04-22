
#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iosfwd>
#include<iostream>

#include <string>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <algorithm>


namespace fa {

  constexpr char Epsilon = '\0';

  //Structure d'un état
  struct State {
    bool isInitial;
    bool isFinal;
  };

  //Structure d'une transition
  struct Transition {
    int from;
    char symbol;
    int to;
  };

  //Structure reliant un ensemble d'état à son nouvel état
  struct Correspondance {
    int nouvel_etat;
    std::set<int> ensemble_etats;
  };

  //Structure représentant une ligne de la table de déterminisation
  struct Determinisation{
    std::set<int> etat_depart;
    char symbol;
    std::set<int> etat_arrivee;
  };

  class Automaton {
  public:
    std::set<char> alphabet;//l'ensemble des symboles de l'automate
    std::map<int, struct State> set_of_states; //l'ensemble des états de l'automate  
    std::vector<struct Transition> set_of_transitions; //l'ensemble des transitions de l'automate
    
    /**
     * Build an empty automaton (no state, no transition).
     */
    Automaton();

    /**
     * Tell if an automaton is valid.
     *
     * A valid automaton has a non-empty set of states and a non-empty set of symbols
     */
    bool isValid() const;

    /**
     * Add a symbol to the automaton
     *
     * Epsilon is not a valid symbol.
     * Returns true if the symbol was effectively added
     */
    bool addSymbol(char symbol);

    /**
     * Remove a symbol from the automaton
     *
     * Returns true if the symbol was effectively removed
     */
    bool removeSymbol(char symbol);

    /**
     * Tell if the symbol is present in the automaton
     */
    bool hasSymbol(char symbol) const;

    /**
     * Count the number of symbols
     */
    std::size_t countSymbols() const;

    /**
     * Add a state to the automaton.
     *
     * By default, a newly added state is not initial and not final.
     * Returns true if the state was effectively added and false otherwise.
     */
    bool addState(int state);

    /**
     * Remove a state from the automaton.
     *
     * The transitions involving the state are also removed.
     * Returns true if the state was effectively removed and false otherwise.
     */
    bool removeState(int state);

    /**
     * Tell if the state is present in the automaton.
     */
    bool hasState(int state) const;

    /**
     * Compute the number of states.
     */
    std::size_t countStates() const;

    /**
     * Set the state initial.
     */
    void setStateInitial(int state);

    /**
     * Tell if the state is initial.
     */
    bool isStateInitial(int state) const;

    /**
     * Set the state final.
     */
    void setStateFinal(int state);

    /**
     * Tell if the state is final.
     */
    bool isStateFinal(int state) const;

    /**
     * Add a transition
     *
     * Returns true if the transition was effectively added and false otherwise.
     * If one of the state or the symbol does not exists, the transition is not added.
     */
    bool addTransition(int from, char alpha, int to);

    /**
     * Remove a transition
     *
     * Returns true if the transition was effectively removed and false otherwise.
     */
    bool removeTransition(int from, char alpha, int to);

    /**
     * Tell if a transition is present.
     */
    bool hasTransition(int from, char alpha, int to) const;

    /**
     * Compute the number of transitions.
     */
    std::size_t countTransitions() const;

    /**
     * Print the automaton in a friendly way
     */
    void prettyPrint(std::ostream& os) const;

    /**
     * Print the automaton with respect to the DOT specification
     */
    // void dotPrint(std::ostream& os) const;

    /**
     * Tell if the automaton has one or more epsilon-transition
     */
    bool hasEpsilonTransition() const;

    /**
     * Tell if the automaton is deterministic
     */
    bool isDeterministic() const;

    /**
     * Tell if the automaton is complete
     */
    bool isComplete() const;

    /**
     * Remove non-accessible states
     */
    void removeNonAccessibleStates();
      
    /**
     * Remove non-co-accessible states
     */
    void removeNonCoAccessibleStates();

    /**
     * Check if the language of the automaton is empty
     */
    bool isLanguageEmpty() const;

    /**
     * Tell if the intersection with another automaton is empty
     */
    bool hasEmptyIntersectionWith(const Automaton& other) const;

    /**
     * Read the string and compute the state set after traversing the automaton
     */
    std::set<int> readString(const std::string& word) const;

    /**
     * Tell if the word is in the language accepted by the automaton
     */
    bool match(const std::string& word) const;

    /**
     * Tell if the langage accepted by the automaton is included in the
     * language accepted by the other automaton
     */
    bool isIncludedIn(const Automaton& other) const;

    /**
     * Create a mirror automaton
     */
    static Automaton createMirror(const Automaton& automaton);

    /**
     * Create a complete automaton, if not already complete
     */
    static Automaton createComplete(const Automaton& automaton);

    /**
     * Create a complement automaton
     */
    static Automaton createComplement(const Automaton& automaton);

    /**
     * Create the product of two automata
     *
     * The product of two automata accept the intersection of the two languages.
     */
    static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);

    /**
     * Create a deterministic automaton, if not already deterministic
     */
    static Automaton createDeterministic(const Automaton& other);

    /**
     * Create an equivalent minimal automaton with the Moore algorithm
     */
    static Automaton createMinimalMoore(const Automaton& other);

    /**
     * Create an equivalent minimal automaton with the Brzozowski algorithm
     */
    static Automaton createMinimalBrzozowski(const Automaton& other);


  private:
    /**
     * Permet de savoir si un état est accessible depuis un état initial
    */
    void find_state(std::set<int>& statesBrowseGlobal, std::set<int>& statesBrowseLocal, int state_to_find, int state) const;
    
    /**
    * Permet de savoir si on peut atteindre un état final en partant d'un état donné
    */
    void find_final_state(std::set<int>& statesBrowseGlobal, std::set<int>& statesBrowseLocal, int state, int state_begin) const;
     
    /**
    * Permet de parcourir l'automate pour voir s'il a un langage vide
    */
    void browse_automaton(std::set<int> statesBrowse, int state , int& nb) const;
    
    /**
    * Permet d'obtenir les états accessibles depuis un état grâce à un symbole
    */
    std::set<int> state_after_move(char next_symbol, std::set<int> states) const;
  };

}

#endif // AUTOMATON_H
