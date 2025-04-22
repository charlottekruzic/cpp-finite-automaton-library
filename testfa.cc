#include "gtest/gtest.h"

#include "Automaton.h"

/**
* isValid
*/
TEST(AutomatonConstructorIsValidTest, Valid) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(1);
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonConstructorIsValidTest, NoState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonConstructorIsValidTest, NoSymbol) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isValid());
}

TEST(AutomatonConstructorIsValidTest, NoStateNoSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/**
* addSymbol
*/
TEST(AutomatonAddTest, OneSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}

TEST(AutomatonAddTest, TwoSymbol) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
}

TEST(AutomatonAddTest, NoGraphicRepresentation) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\n'));
  EXPECT_FALSE(fa.hasSymbol('\n'));
}

TEST(AutomatonAddTest, Epsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

TEST(AutomatonAddTest, AlreadyPresent) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}


/**
* removeSymbol
*/
TEST(AutomatonRemoveSymbolTest, Present) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}

TEST(AutomatonRemoveSymbolTest, NotPresent) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeSymbol('b'));
}

TEST(AutomatonRemoveSymbolTest, NoSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

TEST(AutomatonRemoveSymbolTest, Unknown) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('\n'));
}

TEST(AutomatonRemoveSymbolTest, PresentInTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',1);
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',1));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',1));
}

/**
* hasSymbol
*/

TEST(AutomatonHasSymbolTest, Present) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.hasSymbol('a'));
}

TEST(AutomatonHasSymbolTest, NotPresent) {
  fa::Automaton fa;
  fa.addSymbol('b');
  EXPECT_FALSE(fa.hasSymbol('a'));
}

TEST(AutomatonHasSymbolTest, NoSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

TEST(AutomatonHasSymbolTest, Unknown) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('\n'));
}

/**
* countSymbols
*/

TEST(AutomatonCountSymbolsTest, Zero) {
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countSymbols());
}

TEST(AutomatonCountSymbolsTest, Several) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addSymbol('d');
  fa.addSymbol('e');
  EXPECT_EQ(5u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('c'));
  EXPECT_TRUE(fa.hasSymbol('d'));
  EXPECT_TRUE(fa.hasSymbol('e'));
}

/**
* addState
*/

TEST(AutomatonAddStateTest, Positive) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonAddStateTest, Zero) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.hasState(0));
}

TEST(AutomatonAddStateTest, Negative) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
  EXPECT_FALSE(fa.hasState(-1));
}

TEST(AutomatonAddStateTest, AlreadyPresent) {
  fa::Automaton fa;
  fa.addState(2);
  EXPECT_FALSE(fa.addState(2));
  EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonAddStateTest, TwoState) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
}

TEST(AutomatonAddStateTest, AddAfterRemove) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}


/**
* removeState
*/

TEST(AutomatonRemoveStateTest, Present) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}

TEST(AutomatonRemoveStateTest, NotPresent) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));
}

TEST(AutomatonRemoveStateTest, OriginTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',3);
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',3));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',3));
}

TEST(AutomatonRemoveStateTest, DestinationTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',3);
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',3));
  EXPECT_TRUE(fa.removeState(3));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(2,'a',3));
}

TEST(AutomatonRemoveStateTest, AllStates) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_TRUE(fa.removeState(2));
  EXPECT_TRUE(fa.removeState(3));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
}


TEST(AutomatonRemoveStateTest, OriginAndDestinationInTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'c',2);

  EXPECT_TRUE(fa.removeState(0));
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasTransition(0,'a',0));
  EXPECT_FALSE(fa.hasTransition(0,'b',1));
  EXPECT_TRUE(fa.hasTransition(1,'c',2));
}


/**
* hasState
*/

TEST(AutomatonHasStateTest, Present) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonHasStateTest, NotPresent) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(1));
}

/**
* countStates
*/

TEST(AutomatonCountStatesTest, Zero) {
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countStates());
}

TEST(AutomatonCountStatesTest, Several) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  EXPECT_EQ(4u, fa.countStates());
}


/**
* setStateInitial / isStateInitial
*/

TEST(AutomatonSetStateInitialTest, OneInitial) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitialTest, TwoInitial) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitialTest, NotInitial) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitialTest, DoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonSetStateInitialTest, ReadEmptyString) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateInitial(3);
  fa.setStateFinal(4);

  fa.addSymbol('a');

  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'a',4);
  fa.addTransition(3,'a',4);
  fa.addTransition(4,'a',2);

  std::set<int> set_test = {1,2,3};
  EXPECT_EQ(set_test, fa.readString(""));

}


/**
* setStateFinal / isStateFinal
*/
TEST(AutomatonSetStateFinalTest, Final) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(AutomatonSetStateFinalTest, NotFinal) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonSetStateFinalTest, DoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonSetStateFinalTest, TwoFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.setStateFinal(3);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(1,'c',3);

  EXPECT_FALSE(fa.isStateFinal(1));
  EXPECT_TRUE(fa.isStateFinal(2));
  EXPECT_TRUE(fa.isStateFinal(3));

  EXPECT_FALSE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("aab"));
  EXPECT_TRUE(fa.match("c"));
  EXPECT_TRUE(fa.match("aac"));
}

/**
* addTransition
*/

TEST(AutomatonAddTransitionTest, NotPresent) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonAddTransitionTest, EpsilonTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_TRUE(fa.addTransition(1,fa::Epsilon,2));
  EXPECT_TRUE(fa.hasTransition(1,fa::Epsilon,2));
}

TEST(AutomatonAddTransitionTest, AlreadyPresent) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonAddTransitionTest, NoSymbol) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_FALSE(fa.addTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonAddTransitionTest, NoFromState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(2);
  EXPECT_FALSE(fa.addTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonAddTransitionTest, NoToState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonAddTransitionTest, SameOriginAndLetter) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'a',3));
  EXPECT_TRUE(fa.hasTransition(1,'a',3));
}

TEST(AutomatonAddTransitionTest, SameOriginAndDestination) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
}

TEST(AutomatonAddTransitionTest, SameLetterAndDestination) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(3,'a',1));
  EXPECT_TRUE(fa.hasTransition(3,'a',1));
}

/**
* removeTransition
*/

TEST(AutomatonRemoveTransitionTest, Present) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_TRUE(fa.removeTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonRemoveTransitionTest, NotPresent) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1,'a',2));
}

TEST(AutomatonRemoveTransitionTest, ReverseTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(2,'a',1);
  EXPECT_FALSE(fa.removeTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
}

TEST(AutomatonRemoveTransitionTest, UnknownOrigin) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.removeTransition(3,'a',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonRemoveTransitionTest, UnknownTarget) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.removeTransition(1,'a',3));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonRemoveTransitionTest, UnknownLetter) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.removeTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonRemoveTransitionTest, EpsilonTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,fa::Epsilon,2);
  EXPECT_TRUE(fa.hasTransition(1,fa::Epsilon,2));
  EXPECT_TRUE(fa.removeTransition(1,fa::Epsilon,2));
  EXPECT_FALSE(fa.hasTransition(1,fa::Epsilon,2));
}


/**
* hasTransition
*/
TEST(AutomatonHasTransitionTest, Present) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonHasTransitionTest, NotPresent) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

TEST(AutomatonHasTransitionTest, ReverseTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(2,'a',1);
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}


/**
* countTransitions
*/
TEST(AutomatonCountTransitionTest, Zero) {
  fa::Automaton fa;
  EXPECT_EQ(0u, fa.countTransitions());
}

TEST(AutomatonCountTransitionTest, Several) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',1);
  fa.addTransition(2,'a',3);
  fa.addTransition(3,'c',1);
  EXPECT_EQ(4u, fa.countTransitions());
}

/**
* prettyPrint                 
*/
TEST(AutomatonPrettyPrintTest, Default) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);

  fa.setStateInitial(0);
  fa.setStateInitial(1);

  fa.setStateFinal(1);
  fa.setStateFinal(4);
  
  fa.addSymbol('a');
  fa.addSymbol('b');
  
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'a',3);
  
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',4);
  
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',4);

  fa.addTransition(4,'a',4);

  fa.prettyPrint(std::cout);
}

/**
* hasEpsilonTransition 
*/
TEST(AutomatonHasEpsilonTransitionTest, EpsilonTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,fa::Epsilon,2);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransitionTest, NoEpsilonTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransitionTest, NoTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransitionTest, Twice) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,fa::Epsilon,2);
  fa.addTransition(2,fa::Epsilon,1);
  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.hasTransition(1,fa::Epsilon,2));
  EXPECT_TRUE(fa.hasTransition(2,fa::Epsilon,1));
}

TEST(AutomatonHasEpsilonTransitionTest, AddAndRemove) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,fa::Epsilon,2);
  EXPECT_TRUE(fa.hasTransition(1,fa::Epsilon,2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.removeTransition(1,fa::Epsilon,2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/**
* isDeterministic 
*/

TEST(AutomatonIsDeterministicTest, Deterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, SeveralInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, NoInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, TwoInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.isStateInitial(0);
  fa.isStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, NoFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, SeveralFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(0,'b',2);
  fa.addTransition(2,'a',2);
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, NoTransition1) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, NoTransition2) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, TwoTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(1,'b',2);
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, NotComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addSymbol('d');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(3,'d',3);
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, ThreeTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addSymbol('d');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'a',3);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(3,'d',3);
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministicTest, TransitionInverse) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',0);
  EXPECT_TRUE(fa.isDeterministic());
}

/**
* isComplete 
*/
TEST(AutomatonIsCompleteTest, Complete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'b',0);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',1);
  EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, NotComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'b',0);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',1);
  EXPECT_FALSE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, TwoTransitions) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'b',0);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',1);
  EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonIsCompleteTest, ZeroTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isComplete());

}

TEST(AutomatonIsCompleteTest, AddedRemovedTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'b',0);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',1);
  EXPECT_TRUE(fa.isComplete());
  fa.removeTransition(0,'a',1);
  EXPECT_FALSE(fa.isComplete());
  fa.addTransition(0,'a',2);
  EXPECT_TRUE(fa.isComplete());
}


/**
* createComplete 
*/
TEST(AutomatonCreateCompleteTest, DeterministicAlreadyComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',1);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',3);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("babb"));
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("babb"));
}

TEST(AutomatonCreateCompleteTest, NotDeterministicAlreadyComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(0,'b',3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',1);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',3);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("babb"));
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("babb"));
}

TEST(AutomatonCreateCompleteTest, DeterministicNotComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(3,'a',3);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaaaa"));
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaaaa"));
}

TEST(AutomatonCreateCompleteTest, NotDeterministicNotComplete) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(3,'a',3);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaa"));
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaa"));
}

TEST(AutomatonCreateCompleteTest, Garbage) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',1);
  EXPECT_FALSE(fa.isComplete());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaa"));
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('c'));
  EXPECT_EQ(3u, fa.countSymbols());
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaa"));
}

TEST(AutomatonCreateCompleteTest, StateAlone) {
fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',1);
  EXPECT_FALSE(fa.isComplete());
  fa=fa.createComplete(fa);
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_EQ(1u, fa.countSymbols());
}

/**
* createComplement                    
*/

TEST(AutomatonCreateComplementTest, DeterministicComplete) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);
  
  fa::Automaton fa_complement;
  EXPECT_FALSE(fa.match(""));
  fa_complement=fa.createComplement(fa);
  EXPECT_FALSE(fa.match(""));
  EXPECT_EQ(2u, fa_complement.countSymbols());

}

TEST(AutomatonCreateComplementTest, NotDeterministicComplete) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',5);
  fa.addTransition(1,'c',5);
  
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',3);
  fa.addTransition(2,'c',5);
  
  fa.addTransition(3,'a',5);
  fa.addTransition(3,'c',4);
  fa.addTransition(3,'b',5);
  
  fa.addTransition(4,'a',5);
  fa.addTransition(4,'b',5);
  fa.addTransition(4,'c',4);
  fa.addTransition(4,'c',3);

  fa.addTransition(5,'a',5);
  fa.addTransition(5,'b',5);
  fa.addTransition(5,'c',4);
  
  EXPECT_TRUE(fa.match("abcccccc"));
  EXPECT_TRUE(fa.match("abc"));
  EXPECT_TRUE(fa.match("abcccccccccccccc"));
  EXPECT_FALSE(fa.match(""));

  fa=fa.createComplement(fa);

  EXPECT_EQ(fa.countSymbols(),3u);
  EXPECT_FALSE(fa.match("abcccccc"));
  EXPECT_FALSE(fa.match("abc"));
  EXPECT_FALSE(fa.match("abcccccccccccccc"));
  EXPECT_TRUE(fa.match(""));

}

TEST(AutomatonCreateComplementTest, DeterministicNotComplete) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(1);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'c',4);
  fa.addTransition(4,'c',4);

  EXPECT_TRUE(fa.match("abcccccc"));
  EXPECT_TRUE(fa.match("abc"));
  EXPECT_TRUE(fa.match("abcccccccccccccc"));
  EXPECT_FALSE(fa.match(""));

  fa=fa.createComplement(fa);

  EXPECT_EQ(fa.countSymbols(),3u);
  EXPECT_FALSE(fa.match("abcccccc"));
  EXPECT_FALSE(fa.match("abc"));
  EXPECT_FALSE(fa.match("abcccccccccccccc"));
  EXPECT_TRUE(fa.match(""));
}

TEST(AutomatonCreateComplementTest, NotDeterministicNotComplete) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(1);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(1,'a',2);
  
  fa.addTransition(2,'b',3);
  
  fa.addTransition(3,'c',4);
  fa.addTransition(3,'b',5);
  
  fa.addTransition(4,'c',4);
  fa.addTransition(4,'c',3);
  
  EXPECT_TRUE(fa.match("abcccccc"));
  EXPECT_TRUE(fa.match("abc"));
  EXPECT_TRUE(fa.match("abcccccccccccccc"));
  EXPECT_FALSE(fa.match(""));

  fa=fa.createComplement(fa);

  EXPECT_EQ(fa.countSymbols(),3u);
  EXPECT_FALSE(fa.match("abcccccc"));
  EXPECT_FALSE(fa.match("abc"));
  EXPECT_FALSE(fa.match("abcccccccccccccc"));
  EXPECT_TRUE(fa.match(""));
}

TEST(AutomatonCreateComplementTest, UselessState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',1);
  
  EXPECT_TRUE(fa.match("ababababa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("abababa"));
  EXPECT_FALSE(fa.match(""));

  fa=fa.createComplement(fa);

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_FALSE(fa.match("ababababa"));
  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("abababa"));
  EXPECT_TRUE(fa.match(""));
 
}

TEST(AutomatonCreateComplementTest, Empty) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  
  EXPECT_TRUE(fa.match(""));
  fa=fa.createComplement(fa);
  EXPECT_FALSE(fa.match(""));
 
}

TEST(AutomatonCreateComplementTest, Full) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateInitial(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');

  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',1);
  fa.addTransition(2,'a',2);
  
  EXPECT_TRUE(fa.match("aaaaaaaaaaaaaaa"));
  EXPECT_TRUE(fa.match(""));

  fa=fa.createComplement(fa);

  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aaaaaaaaaaaaaaa"));
 
}


/**
* createMirror 
*/
TEST(AutomatonCreateMirrorTest, Empty) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  
  EXPECT_TRUE(fa.match(""));

  fa=fa.createMirror(fa);

  EXPECT_EQ(1u, fa.countStates());
  EXPECT_EQ(1u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_EQ(0u, fa.countTransitions());
  EXPECT_TRUE(fa.match(""));

}

TEST(AutomatonCreateMirrorTest, OneStateInitialOneStateFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'b',3);
  fa.addTransition(3,'b',1);

  EXPECT_TRUE(fa.match("abbabbab"));
  EXPECT_FALSE(fa.match("babbabba"));
  EXPECT_TRUE(fa.match("a"));

  fa=fa.createMirror(fa);

  EXPECT_FALSE(fa.match("abbabbab"));
  EXPECT_TRUE(fa.match("babbabba"));
  EXPECT_TRUE(fa.match("a"));

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_EQ(fa.countTransitions(),5u);
}

TEST(AutomatonCreateMirrorTest, OneStateInitialAndFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(1);

  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'b',3);
  fa.addTransition(3,'b',1);


  EXPECT_TRUE(fa.match("abbbbbbbbb"));
  EXPECT_FALSE(fa.match("bbbbbbbbba"));

  fa=fa.createMirror(fa);

  EXPECT_FALSE(fa.match("abbbbbbbbb"));
  EXPECT_TRUE(fa.match("bbbbbbbbba"));

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),3u);
  EXPECT_EQ(fa.countTransitions(),5u);

}

/**
* match 
*/
TEST(AutomatonMatchTest, FinisseA) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);

  fa.setStateInitial(0);
  fa.setStateFinal(1);

  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'b',0);
  fa.addTransition(0,'a',1);
  
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aab"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("bbaba"));
  EXPECT_TRUE(fa.match("abbaba"));
  EXPECT_FALSE(fa.match("c"));
}

TEST(AutomatonMatchTest, NbImpairB) {
  fa::Automaton fa;
  
  fa.addState(0);
  fa.addState(1);

  fa.setStateInitial(0);
  fa.setStateFinal(1);

  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',0);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbaba"));
  EXPECT_TRUE(fa.match("abbaba"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("aab"));
  EXPECT_FALSE(fa.match(""));

}

TEST(AutomatonMatchTest, ManyInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'a',2);
  fa.addTransition(1,'a',0);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',0);
  fa.addTransition(2,'a',1);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',2);

  EXPECT_TRUE(fa.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  EXPECT_TRUE(fa.match("aaaaaaaaaaaa"));
  EXPECT_TRUE(fa.match("aaaaaaaaaaaaaaaa"));
  EXPECT_TRUE(fa.match("aaaaaaaaaaaaaaaaaaaab"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("aab"));
}

TEST(AutomatonMatchTest, Exponential) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);

  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',0);
  fa.addTransition(1,'b',2);

  EXPECT_FALSE(fa.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  EXPECT_TRUE(fa.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));

}

/**
* isLanguageEmpty                    
*/

TEST(AutomatonIsLanguageEmptyTest, NoEmpty) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoFinalState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoInitialState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, NoPathInitialToFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(2,'b',2);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmptyTest, InitialAndFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}

/**
* removeNonAccessibleStates                    
*/

TEST(AutomatonRemoveNonAccessibleStatesTest, AllAccessible) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonAccessibleStates();

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),2u);
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_EQ(fa.countTransitions(),4u);
  EXPECT_TRUE(fa.hasTransition(1,'a',1));  
  EXPECT_TRUE(fa.hasTransition(1,'b',2));  
  EXPECT_TRUE(fa.hasTransition(2,'b',2));  
  EXPECT_TRUE(fa.hasTransition(2,'a',1));  
}

TEST(AutomatonRemoveNonAccessibleStatesTest, NoInitialState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonAccessibleStates();

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),1u);  
}


TEST(AutomatonRemoveNonAccessibleStatesTest, StateAlone) {  
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);


  fa.removeNonAccessibleStates();

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),2u);
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_EQ(fa.countTransitions(),4u);
  EXPECT_TRUE(fa.hasTransition(1,'a',1));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));

}

TEST(AutomatonRemoveNonAccessibleStatesTest, StateWithTransitionNoAccessible) { 
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);
  fa.addTransition(3,'a',1);

  fa.removeNonAccessibleStates();

  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(fa.countStates(),2u);
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_EQ(fa.countTransitions(),4u);
  EXPECT_TRUE(fa.hasTransition(1,'a',1));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
  EXPECT_FALSE(fa.hasTransition(3,'a',1));

}

/**
* removeNonCoAccessibleStates                    
*/

TEST(AutomatonRemoveNonCoAccessibleStatesTest, AllCoAccessible) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonCoAccessibleStates();

  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countStates());
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_EQ(4u, fa.countTransitions());
  EXPECT_TRUE(fa.hasTransition(1,'a',1));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, NoFinalState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonCoAccessibleStates();

  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_EQ(0u, fa.countTransitions());
  EXPECT_FALSE(fa.hasTransition(1,'a',1));
  EXPECT_FALSE(fa.hasTransition(1,'b',2));
  EXPECT_FALSE(fa.hasTransition(2,'b',2));
  EXPECT_FALSE(fa.hasTransition(2,'a',1));

}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, StateAlone) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonCoAccessibleStates();

  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countStates());
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_EQ(4u, fa.countTransitions());
  EXPECT_TRUE(fa.hasTransition(1,'a',1));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
}

TEST(AutomatonRemoveNonCoAccessibleStatesTest, NoInitialState) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);

  fa.removeNonCoAccessibleStates();

  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(2u, fa.countStates());
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_EQ(4u, fa.countTransitions());
  EXPECT_TRUE(fa.hasTransition(1,'a',1));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',2));
  EXPECT_TRUE(fa.hasTransition(2,'a',1));
}

/**
* createProduct
*/
TEST(AutomatonCreateProductTest, Different) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.addState(3);
  fa1.setStateInitial(1);
  fa1.setStateInitial(3);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'a',3);
  fa1.addTransition(3,'b',3);
  fa1.addTransition(3,'b',2);
  EXPECT_TRUE(fa1.match("aab"));
  EXPECT_TRUE(fa1.match("aabb"));

  fa::Automaton fa2;
  fa2.addState(4);
  fa2.addState(5);
  fa2.setStateInitial(4);
  fa2.setStateFinal(5);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(4,'a',4);
  fa2.addTransition(4,'b',5);
  fa2.addTransition(5,'a',4);
  EXPECT_TRUE(fa2.match("aab"));
  EXPECT_FALSE(fa2.match("aabb"));

  fa::Automaton fa_product = fa_product.createProduct(fa1,fa2);  
  EXPECT_TRUE(fa_product.match("aab"));
  EXPECT_FALSE(fa_product.match("aabb"));
}

TEST(AutomatonCreateProductTest, Same) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'b',1);
  EXPECT_TRUE(fa1.match("a"));
  EXPECT_TRUE(fa1.match("abababa"));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.addState(2);
  fa2.setStateInitial(1);
  fa2.setStateFinal(2);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(1,'a',2);
  fa2.addTransition(2,'b',1);
  EXPECT_TRUE(fa2.match("a"));
  EXPECT_TRUE(fa2.match("abababa"));

  fa::Automaton fa_product = fa_product.createProduct(fa1,fa2);
  EXPECT_TRUE(fa_product.match("a"));
  EXPECT_TRUE(fa_product.match("abababa")); 
}

TEST(AutomatonCreateProductTest, WithEmpty) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'b',1);
  EXPECT_TRUE(fa1.match("a"));
  EXPECT_TRUE(fa1.match("abababa"));
  EXPECT_FALSE(fa1.match(""));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.setStateInitial(1);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  EXPECT_TRUE(fa2.match(""));
  EXPECT_FALSE(fa2.match("a"));
  EXPECT_FALSE(fa2.match("abababa"));


  fa::Automaton fa_product = fa_product.createProduct(fa1,fa2);
  EXPECT_FALSE(fa_product.match(""));
  EXPECT_FALSE(fa_product.match("a"));
  EXPECT_FALSE(fa_product.match("abababa"));

}

TEST(AutomatonCreateProductTest, DifferentSymbols) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'a',2);

  EXPECT_TRUE(fa1.match("aaa"));
  EXPECT_TRUE(fa1.match("a"));
  EXPECT_FALSE(fa1.match("bbb"));
  EXPECT_FALSE(fa1.match("bbb"));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.addState(2);
  fa2.setStateInitial(1);
  fa2.setStateFinal(2);
  fa2.addSymbol('b');
  fa2.addTransition(1,'b',2);
  fa2.addTransition(2,'b',2);

  EXPECT_TRUE(fa2.match("bbb"));
  EXPECT_TRUE(fa2.match("b"));
  EXPECT_FALSE(fa2.match("aaa"));
  EXPECT_FALSE(fa2.match("a"));

  fa::Automaton fa_product = fa_product.createProduct(fa1,fa2);
  EXPECT_FALSE(fa_product.match("bbb"));
  EXPECT_FALSE(fa_product.match("b"));
  EXPECT_FALSE(fa_product.match("aaa"));
  EXPECT_FALSE(fa_product.match("a"));
}

/**
* hasEmptyIntersectionWith
*/
TEST(AutomatonHasEmptyIntersectionWithTest, NotEmpty) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(1,'b',2);
  fa1.addTransition(2,'a',2);

  EXPECT_FALSE(fa1.match("bbb"));
  EXPECT_TRUE(fa1.match("b"));
  EXPECT_TRUE(fa1.match("aaa"));
  EXPECT_TRUE(fa1.match("a"));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.addState(2);
  fa2.setStateInitial(1);
  fa2.setStateFinal(2);
  fa2.addSymbol('b');
  fa2.addTransition(1,'b',2);
  fa2.addTransition(2,'b',2);

  EXPECT_TRUE(fa2.match("bbb"));
  EXPECT_TRUE(fa2.match("b"));
  EXPECT_FALSE(fa2.match("aaa"));
  EXPECT_FALSE(fa2.match("a"));
  
  EXPECT_FALSE(fa1.hasEmptyIntersectionWith(fa2));

}

TEST(AutomatonHasEmptyIntersectionWithTest, WithEmpty) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'b',1);
  EXPECT_TRUE(fa1.match("a"));
  EXPECT_TRUE(fa1.match("abababa"));
  EXPECT_FALSE(fa1.match(""));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.setStateInitial(1);
  fa2.setStateFinal(1);
  fa2.addSymbol('a');
  EXPECT_TRUE(fa2.match(""));
  EXPECT_FALSE(fa2.match("a"));
  EXPECT_FALSE(fa2.match("abababa"));

  fa1.hasEmptyIntersectionWith(fa2);

}

TEST(AutomatonHasEmptyIntersectionWithTest, DifferentSymbols) {
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.setStateInitial(1);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addTransition(1,'a',2);
  fa1.addTransition(2,'a',2);

  EXPECT_TRUE(fa1.match("aaa"));
  EXPECT_TRUE(fa1.match("a"));
  EXPECT_FALSE(fa1.match("bbb"));
  EXPECT_FALSE(fa1.match("bbb"));

  fa::Automaton fa2;
  fa2.addState(1);
  fa2.addState(2);
  fa2.setStateInitial(1);
  fa2.setStateFinal(2);
  fa2.addSymbol('b');
  fa2.addTransition(1,'b',2);
  fa2.addTransition(2,'b',2);

  EXPECT_TRUE(fa2.match("bbb"));
  EXPECT_TRUE(fa2.match("b"));
  EXPECT_FALSE(fa2.match("aaa"));
  EXPECT_FALSE(fa2.match("a"));

  EXPECT_TRUE(fa1.hasEmptyIntersectionWith(fa2));
}

/**
* readString
*/
TEST(AutomatonReadStringTest, Default) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(0,'a',2);

  std::set<int> set1 = {0};
  EXPECT_EQ(set1, fa.readString(""));
  std::set<int> set2 = {1,2};
  EXPECT_EQ(set2, fa.readString("a"));
  std::set<int> set3 = {2};
  EXPECT_EQ(set3, fa.readString("aa"));
  std::set<int> set4 = {};
  EXPECT_EQ(set4, fa.readString("b"));
}

TEST(AutomatonReadStringTest, ManyInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(0,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(3,'a',2);

  std::set<int> set1 = {0,1};
  EXPECT_EQ(set1, fa.readString(""));
  std::set<int> set2 = {1,2,3};
  EXPECT_EQ(set2, fa.readString("a"));
  std::set<int> set3 = {2,3};
  EXPECT_EQ(set3, fa.readString("aa"));
  std::set<int> set4 = {1};
  EXPECT_EQ(set4, fa.readString("b"));
}

TEST(AutomatonReadStringTest, UnknownSymbol) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',0);

  std::set<int> set1 = {};
  EXPECT_EQ(set1, fa.readString("c"));
  std::set<int> set2 = {};
  EXPECT_EQ(set2, fa.readString("aaac"));
  std::set<int> set3 = {};
  EXPECT_EQ(set3, fa.readString("aaacaa"));
  std::set<int> set4 = {};
  EXPECT_EQ(set4, fa.readString("caaaa"));
}

TEST(AutomatonReadStringTest, InvalidString) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',0);

  std::set<int> set1 = {};
  EXPECT_EQ(set1, fa.readString("aaaaa\n"));
  std::set<int> set2 = {};
  EXPECT_EQ(set2, fa.readString("a\taa"));
  std::set<int> set3 = {};
  EXPECT_EQ(set3, fa.readString("\raaaaa"));
}

/**
* createDeterministic
*/

TEST(AutomatonCreateDeterministicTest, AlreadyDeterministic) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.setStateInitial(0);
  fa.setStateFinal(0);

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);
  fa.addTransition(1,'b',0);

  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aababab"));
  fa = fa.createDeterministic(fa);
  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aababab"));
}

TEST(AutomatonCreateDeterministicTest, SameLetterTransition1) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',1);
  fa.addTransition(1,'b',2);

  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aaabbbabaab"));
  fa = fa.createDeterministic(fa);
  EXPECT_EQ(fa.countSymbols(), 2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aaabbbabaab"));
}

TEST(AutomatonCreateDeterministicTest, SameLetterTransition2) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(0);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',0);
  fa.addTransition(0,'b',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'a',4);
  fa.addTransition(3,'b',4);

  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("abaabba"));
  fa = fa.createDeterministic(fa);
  EXPECT_EQ(fa.countSymbols(), 2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("abaabba"));
}

TEST(AutomatonCreateDeterministicTest, SameLetterTransition3) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'b',0);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'a',1);


  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aaababbb"));
  fa = fa.createDeterministic(fa);
  EXPECT_EQ(fa.countSymbols(),2u);
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("aaababbb"));
}

TEST(AutomatonCreateDeterministicTest, TwoFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',4);
  fa.addTransition(0,'a',5);

  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',3);

  fa.addTransition(3,'b',0);

  fa.addTransition(4,'a',3);
  fa.addTransition(4,'a',4);

  fa.addTransition(5,'b',4);
  fa.addTransition(5,'a',5);
  
  EXPECT_TRUE(fa.match("abbbbbbaaaabababba"));
  EXPECT_TRUE(fa.match("babb"));


  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("abbbbbbaaaabababba"));
  EXPECT_TRUE(fa.match("babb"));
}

TEST(AutomatonCreateDeterministicTest, TwoInitialStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateInitial(4);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',4);
  fa.addTransition(0,'a',5);

  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',3);

  fa.addTransition(3,'b',0);

  fa.addTransition(4,'a',3);
  fa.addTransition(4,'a',4);

  fa.addTransition(5,'b',4);
  fa.addTransition(5,'a',5);
  EXPECT_TRUE(fa.match("abbbbbbaaaabababba"));
  EXPECT_TRUE(fa.match("aaaaaaaabbaa"));

  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("abbbbbbaaaabababba"));
}

TEST(AutomatonCreateDeterministicTest, Empty) {
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
}


TEST(AutomatonCreateDeterministicTest, NoInitialState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',4);
  fa.addTransition(0,'a',5);

  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',3);

  fa.addTransition(3,'b',0);

  fa.addTransition(4,'a',3);
  fa.addTransition(4,'a',4);

  fa.addTransition(5,'b',4);
  fa.addTransition(5,'a',5);
  
  EXPECT_FALSE(fa.match(""));
  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_FALSE(fa.match(""));
  
}

TEST(AutomatonCreateDeterministicTest, NoFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',4);
  fa.addTransition(0,'a',5);

  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',3);

  fa.addTransition(3,'b',0);

  fa.addTransition(4,'a',3);
  fa.addTransition(4,'a',4);

  fa.addTransition(5,'b',4);
  fa.addTransition(5,'a',5);

  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
  
}

TEST(AutomatonCreateDeterministicTest, InitialFinal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.addSymbol('b');

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',4);
  fa.addTransition(0,'a',5);

  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',3);

  fa.addTransition(3,'b',0);

  fa.addTransition(4,'a',3);
  fa.addTransition(4,'a',4);

  fa.addTransition(5,'b',4);
  fa.addTransition(5,'a',5);
  
  EXPECT_TRUE(fa.match("abbabbaabb"));
  EXPECT_TRUE(fa.match(""));
  fa = fa.createDeterministic(fa);
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("abbabbaabb"));
  EXPECT_TRUE(fa.match(""));
}

/**
 * isIncludedIn
*/
TEST(AutomatonIsIncludedInTest, Default) {
  fa::Automaton automaton_a;
  automaton_a.addState(0);
  automaton_a.addState(1);
  automaton_a.setStateInitial(0);
  automaton_a.setStateFinal(1);
  automaton_a.addSymbol('a');
  automaton_a.addTransition(0,'a',1);
  automaton_a.addTransition(1,'a',1);
  
  EXPECT_TRUE(automaton_a.match("aaaaaaaa"));
  EXPECT_FALSE(automaton_a.match("bbbbbbbbbbbb"));

  fa::Automaton automaton_a_et_b;
  automaton_a_et_b.addState(0);
  automaton_a_et_b.addState(1);
  automaton_a_et_b.setStateInitial(0);
  automaton_a_et_b.setStateFinal(1);
  automaton_a_et_b.addSymbol('a');
  automaton_a_et_b.addSymbol('b');
  automaton_a_et_b.addTransition(0,'a',1);
  automaton_a_et_b.addTransition(1,'a',1);
  automaton_a_et_b.addTransition(0,'b',1);
  automaton_a_et_b.addTransition(1,'b',1);
  EXPECT_TRUE(automaton_a_et_b.match("aaaaaaaa"));
  EXPECT_TRUE(automaton_a_et_b.match("bbbbbbbbbbbb"));
  
  EXPECT_TRUE(automaton_a.isIncludedIn(automaton_a_et_b));
  EXPECT_FALSE(automaton_a_et_b.isIncludedIn(automaton_a));
}

TEST(AutomatonIsIncludedInTest, Same) {
  fa::Automaton automaton_a1;
  automaton_a1.addState(0);
  automaton_a1.addState(1);
  automaton_a1.setStateInitial(0);
  automaton_a1.setStateFinal(1);
  automaton_a1.addSymbol('a');
  automaton_a1.addTransition(0,'a',1);
  automaton_a1.addTransition(1,'a',1);
  
  EXPECT_TRUE(automaton_a1.match("aaaaaaaa"));

  fa::Automaton automaton_a2;
  automaton_a2.addState(0);
  automaton_a2.addState(1);
  automaton_a2.setStateInitial(0);
  automaton_a2.setStateFinal(1);
  automaton_a2.addSymbol('a');
  automaton_a2.addTransition(0,'a',1);
  automaton_a2.addTransition(1,'a',1);
  
  EXPECT_TRUE(automaton_a2.match("aaaaaaaa"));
  
  EXPECT_TRUE(automaton_a1.isIncludedIn(automaton_a2));
  EXPECT_TRUE(automaton_a2.isIncludedIn(automaton_a1));
}

TEST(AutomatonIsIncludedInTest, EmptyInEmpty) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.setStateInitial(0);
  fa1.setStateFinal(0);
  fa1.addSymbol('a');
  EXPECT_TRUE(fa1.match(""));

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.setStateInitial(0);
  fa2.setStateFinal(0);
  fa2.addSymbol('a');
  EXPECT_TRUE(fa2.match(""));
  
  EXPECT_TRUE(fa2.isIncludedIn(fa1));
  EXPECT_TRUE(fa1.isIncludedIn(fa2));
}

TEST(AutomatonIsIncludedInTest, EmptyInEmpty2) {
  fa::Automaton fa1;
  fa1.addState(0);
  fa1.setStateInitial(0);
  fa1.setStateFinal(0);
  fa1.addSymbol('a');
  EXPECT_TRUE(fa1.match(""));

  fa::Automaton fa2;
  fa2.addState(0);
  fa2.addState(1);
  fa2.setStateInitial(0);
  fa2.setStateFinal(0);
  fa2.addSymbol('b');
  fa2.addTransition(0,'b',1);
  fa2.addTransition(1,'b',1);
  EXPECT_TRUE(fa2.match(""));
  
  EXPECT_TRUE(fa2.isIncludedIn(fa1));
  EXPECT_TRUE(fa1.isIncludedIn(fa2));
}

TEST(AutomatonIsIncludedInTest, DifferentSymbols) {
  fa::Automaton automaton_a1;
  automaton_a1.addState(0);
  automaton_a1.addState(1);
  automaton_a1.setStateInitial(0);
  automaton_a1.setStateFinal(1);
  automaton_a1.addSymbol('b');
  automaton_a1.addTransition(0,'b',1);
  automaton_a1.addTransition(1,'b',1);
  
  EXPECT_TRUE(automaton_a1.match("bbbbbbbb"));
  EXPECT_FALSE(automaton_a1.match("aaaaaaaa"));

  fa::Automaton automaton_a2;
  automaton_a2.addState(0);
  automaton_a2.addState(1);
  automaton_a2.setStateInitial(0);
  automaton_a2.setStateFinal(1);
  automaton_a2.addSymbol('a');
  automaton_a2.addTransition(0,'a',1);
  automaton_a2.addTransition(1,'a',1);
  
  EXPECT_TRUE(automaton_a2.match("aaaaaaaa"));
  EXPECT_FALSE(automaton_a2.match("bbbbbbbb"));
  
  EXPECT_FALSE(automaton_a1.isIncludedIn(automaton_a2));
  EXPECT_FALSE(automaton_a2.isIncludedIn(automaton_a1));
}

/**
 * createMinimalMoore
*/
TEST(AutomatonCreateMinimalMooreTest, AlreadyMinimal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'b',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',0);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbbba"));
  EXPECT_TRUE(fa.match("abbbaabbabaaabbba"));
  fa = fa.createMinimalMoore(fa);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbbba"));
  EXPECT_TRUE(fa.match("abbbaabbabaaabbba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(3u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}


TEST(AutomatonCreateMinimalMooreTest, DifferentSymbols) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'c',3);
  fa.addTransition(2,'c',3);
  
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("bc"));

  fa = fa.createMinimalMoore(fa);
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("bc"));
  EXPECT_EQ(3u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('c'));
  EXPECT_EQ(4u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());

}

TEST(AutomatonCreateMinimalMooreTest, TwoFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',1);
  fa.addTransition(3,'b',5);
  fa.addTransition(3,'a',4);
  fa.addTransition(4,'a',3);
  fa.addTransition(4,'b',5);
  fa.addTransition(5,'a',5);
  fa.addTransition(5,'b',5);

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("baaaabaaa"));
  EXPECT_TRUE(fa.match("baaaaaaba"));

  fa = fa.createMinimalMoore(fa);
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("baaaabaaa"));
  EXPECT_TRUE(fa.match("baaaaaaba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(4u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonCreateMinimalMooreTest, InitialAndFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateFinal(5);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',5);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'a',4);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',5);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',0);
  fa.addTransition(4,'b',2);
  fa.addTransition(4,'a',1);
  fa.addTransition(5,'a',5);
  fa.addTransition(5,'b',4);

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aaabaaabba"));
  fa = fa.createMinimalMoore(fa);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aaabaaabba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(3u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}



/**
 * createMinimalBrzozowski
*/

TEST(AutomatonCreateMinimalBrzozowskiTest, AlreadyMinimal) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'b',0);
  fa.addTransition(0,'a',1);
  fa.addTransition(1,'b',1);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',0);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbbba"));
  EXPECT_TRUE(fa.match("abbbaabbabaaabbba"));
  fa = fa.createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbbba"));
  EXPECT_TRUE(fa.match("abbbaabbabaaabbba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(3u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}


TEST(AutomatonCreateMinimalBrzozowskiTest, DifferentSymbols) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'c',3);
  fa.addTransition(2,'c',3);
  
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("bc"));

  fa = fa.createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("bc"));
  EXPECT_EQ(3u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('c'));
  EXPECT_EQ(4u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonCreateMinimalBrzozowskiTest, TwoFinalStates) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',2);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',1);
  fa.addTransition(3,'b',5);
  fa.addTransition(3,'a',4);
  fa.addTransition(4,'a',3);
  fa.addTransition(4,'b',5);
  fa.addTransition(5,'a',5);
  fa.addTransition(5,'b',5);

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("baaaabaaa"));
  EXPECT_TRUE(fa.match("baaaaaaba"));

  fa = fa.createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("baaaabaaa"));
  EXPECT_TRUE(fa.match("baaaaaaba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(4u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonCreateMinimalBrzozowskiTest, InitialAndFinalState) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateFinal(5);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0,'a',5);
  fa.addTransition(0,'b',1);
  fa.addTransition(1,'a',4);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'b',5);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',0);
  fa.addTransition(4,'b',2);
  fa.addTransition(4,'a',1);
  fa.addTransition(5,'a',5);
  fa.addTransition(5,'b',4);

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aaabaaabba"));
  fa = fa.createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aaabaaabba"));
  EXPECT_EQ(2u, fa.countSymbols());
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_EQ(3u, fa.countStates());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
