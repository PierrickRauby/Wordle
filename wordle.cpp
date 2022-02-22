/*
 * Simple Wordle Game.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
std::string const word_list_path("./5_letter_word.txt");

/**
 * @brief Loads the list of file letter words from path
 * @param  {std::vector<std::string>} word_list : the path to the txt file.
 */
void getWords(std::vector<std::string>& word_list){
    std::fstream fs(word_list_path.c_str());
    std::string word;
    while(fs>>word){
        word_list.push_back(word);
    }
    fs.close();
}
/**
 * @brief Selects a  randowm word in the list of words
 * @param  {std::vector<std::string>} word_list : the list of word to select a 
 *      a word form.
 * @return {std::string} : the selected word
 */
std::string selectWord(std::vector<std::string>& word_list){
    int random_index=rand()%word_list.size();
    return word_list[random_index];
}
 
/**
 * @brief Check if one letter is appearing in the word to find in the correct 
 *      position, returns true if yes, false if no.
 * @param  {char} const c :  the char to check.
 * @param  {std::string} const word : the word to find.
 * @param  {int} const index:  the position of the char c in the user's guess.
 * @return {bool} :  if at the specified index the character is c 
 *      in the word to find then return true, else return false.
 */
bool checkForHit(char const& c,std::string const & word, int const index){
    if (c == word[index])
        return true;
    else
        return false;
}
/**
 * @brief Check if the given letter is in the word to guess, return true if yes, 
 *      note that if the letter is also a hit at another position of the user's 
 *      guess then it will appear as a partial hit.
 * @param  {char} const c: the char in the user's guess.
 * @param  {std::string} const word: the word to guess.
 * @return {bool} : return true if c is in word, false otherwise.
 */
bool checkForPartial(char const& c, std::string const & word ){
    int i;
    for(i=0;i<word.size();i++){
        if(word[i]==c){
            return true;
        }
    }
    return false; 
}
/**
 * @brief function that format the output for the user in case of a wrong guess.
 * @param  {std::string} const guessed_word: the user's guess.
 * @param  {std::string} const reponse: the clues for the user (5 letter string)
 *      indicating for each character if it is a hit, a partial hit or a miss.
 */
void formatClues(std::string const& guessed_word, std::string const& response){
        std::cout<<"Sorry, try again: "<<std::endl;
        std::cout<<"\t-----------"<<std::endl<<"\t|";
        int k;
        for(k=0;k<guessed_word.size();k++){
            std::cout<<guessed_word[k]<<"|";
        }
        std::cout<<std::endl<<"\t-----------"<<std::endl<<"\t|";
        for(k=0;k<guessed_word.size();k++){
            std::cout<<response[k]<<"|";
        }
        std::cout<<std::endl<<"\t-----------"<<std::endl;
        std::cout<<"\th-> correct letter,"<<std::endl;
        std::cout<<"\tp-> letter in the word but somewhere else,"<<std::endl;
        std::cout<<"\tx-> letter not in the word."<<std::endl;
        std::cout<<"Enter a new guess:"<<std::endl;
}
/**
 * @brief Main function, select a word from the word list and itterate until the
 *      user finds the correct word. For each attempt some clue are sent to the 
 *      user.
 * @return {int}  :  0
 */
int main(){
    srand(time(0));
    std::vector<std::string> word_list; 
    getWords(word_list);
    std::string guessed_word, response("xxxxx");
    std::string word=selectWord(word_list);
    std::cout<< "I have choosen a 5 letters word "<<std::endl;
    std::cout<< "Can you guess it?(enter a 5 letters word)"<<std::endl;
    while(true) {
    std::cin>>guessed_word;
    guessed_word=guessed_word.substr(0,5);
    int j;
    for(j=0;j<word.size();j++){
       if(checkForHit(guessed_word[j],word,j)){
           response[j]='h';
       }else if(checkForPartial(guessed_word[j],word)){
           response[j]='p';
       }else{
           response[j]='x';
       }
    }
    if(response=="hhhhh"){
        std::cout<<"Congrats you found the word: "<<guessed_word<<"!"<<std::endl;
        break;
    }else{
        formatClues(guessed_word,response);
    }
    }

return 0;
}