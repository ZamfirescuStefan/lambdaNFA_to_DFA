# lambdaNFA to DFA

  This program transform a given lambda_NFA(lambda nedeterministic finite automata) to a DFA (deterministic finite automata) 
  and check a list of words if it is accepted by the automata.
  
#### The automata is read from ```config_automat``` file in this from: 
 - the number of states 
 - the number of characters in the alphabet
 - the list of characters of the alphabet
 - initial state 
 - the number of final states
 - the list of final states 
 - the number of transitions
 - the list of transitions 
  - list of transitions with ``` node evaluation node``` structure
#### The list of words is read form ```lista_cuvinte``` in this form: 
 - the number of words
 - the list of words
 
  <br/>
 
 <i> 
 This program was developed as a homework for the Formal Languages And Automata Theory Class at the University of Bucharest,
 Faculty of Mathematics and Computer Science, 2019-2020.
 </i>
