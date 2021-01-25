/*
 * =====================================================================================
 *
 *       Filename:  hangman.cpp
 *
 *    Description:  Hangman Game. User guesses needs to guess the letters to a word.
 *                      The user has 10 tries in which to guess the letters.
 *
 *        Version:  0.4.1.3
 *        Created:  8 March 2012
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Bernhard Breytenbach
 *   Organization:  Unforged
 *
 * =====================================================================================
 */

#include <iostream> //Command Prompt Input output
#include <fstream> //Usage of Files
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

string alphabet="a b c d e f g h i j k l m n o p q r s t u v w x y z"; //used for validation
string line, guessed, word, display;
int numlines=0,inttries=0;
ifstream myfile("words.txt"); //File containing all the words


/*******************************
** Create all the Underscores **
*******************************/
void makeDisplay ()
{
    display = "";
    for (int k=0;k<static_cast<int>(string(word).size());k++)
        display=display+"_"; //Add one underscore for every letter in the word
    guessed="_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _";
}

/******************************************************
** ASCII MAN!!! d-_-b One for every number of tries! **
******************************************************/
string makeMan ()
{
    string prefix_normal="\n  ================|\n //               |\n ||               ";
    string out_str = "";
    string b3 = "\n ||             ";
    string b1 = b3 + "  ";
    string b2= b3 + " ";

    switch ( inttries )
    {
        case 10:
            out_str+= prefix_normal + "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]" +
                b3 + "\\___/\n ||" + b1 + "||    - *Snap!!!*"+ b2 + "/||\\"+ b3 +
                "//||\\\\\n ||            // || \\\\\n ||            *  ||  *"+
                b2 + "//\\\\"+ b3 + "//  \\\\\n /\\            //    \\\\\n//\\\\         ***      ***\n/||\\\\\n_||_\\\\\n";
        case 9:
            out_str+= prefix_normal + "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+
                b3 + "\\___/" + b1 + "||"+ b2 + "/||\\"+ b3 + "//||\\\\\n ||            // || \\\\\n ||            *  ||  *"+
                b2 + "//"+ b3 + "//\n ||            //\n /\\          ***\n//\\\\ \n/||\\\\ \n_||_\\\\\n";
        case 8:
            out_str+= prefix_normal +  "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+
                b3 + "\\___/" + b1 + "||"+ b2 + "/||\\"+ b3 +
                "//||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 7:
            out_str+= prefix_normal +  "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+ b3
                + "\\___/" + b1 + "||"+ b2 + "/||"+ b3 + "//||\n ||            // ||\n ||            *  ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 6:
            out_str+= prefix_normal +  "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+ b3
                + "\\___/" + b1 + "||" + b1 + "||" + b1 + "||" + b1 + "||" + b1 + "||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 5:
            out_str+= prefix_normal +  "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+ b3
                + "\\___/" + b1 + "||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 4:
            out_str+= prefix_normal + "|" + b1 + "|"+ b2 + "_^_"+ b3 + "/ ..\\\n ||            [  _  ]"+ b3
                + "\\___/\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 3:
            out_str+= prefix_normal +  "|" + b1 + "|\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 2:
            out_str+= "\n  ================\n //\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 1:
            out_str+= "\n\n\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        case 0:
            out_str+= "\n\n\nCreated By Bernhard Breytenbach for educational purposes. 2008 - 1012\n\nPress * anytime to quit!\n\n\n\n\n\n\n\n\n\n\n\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        default:
            ;
    }
    return out_str;
}

/****************************************
** Check the guessed letter and add it **
****************************************/
void guesslet (char a)
{
    int correct=0,tried=0,validlet=0,k=0;

    for (k = 0; k < 51; k+=2) //Alphabetic Checks
        if (isalpha(a)) //Check if letter is in alphabet
        {
            validlet=1; //Confirm valid entry
            if (guessed[k]!=a) //Check to see if the letter has been tried before
                guessed[k]=a; //Save letter in String
                    else
                        tried=1; //Letter has been tried before
        }

    if ((tried!=1) && (validlet==1)) //Check if letter is valid and hasn't been tried before
    {
        for (k=0;k<static_cast<int>(string(word).size());k++)
            if (word[k]==a) //Check if the letter is in the word
            {
                display[k]=a; //Change the underscore to the letter
                correct=1; //Yes, there is at least one correct letter
            }
        if (correct!=1)
           inttries++; //If the letter isn't in the word, increase tries
    }
}

/************************************************
** Select a random word from the text document **
************************************************/
void selectRandLine ()
{
    try{
        int randline=0, wordlength=0, k=0;
    string newword;
    //Generate random line
    randline = (rand()%numlines)+1;
    //Reset curser to first line
    myfile.clear();
    myfile.seekg(0, ios::beg);
    //Grab line from file
    for (int lineno = 0; getline (myfile,newword) && lineno < randline; lineno++);
    wordlength=string(newword).size();
    word="";
    for (int i = 0; wordlength>i; i++)
    {
        for (k = 0; k < 51; k+=2) //Alphabetic Checks
            if (alphabet[k]==newword[i]) //Check if letter is in alphabet
                word=word+newword[i];
    }
    }
    catch(const std::exception &e){
        cout << "Some fatal exception. File words.txt missing?";
    }
    catch(int j){
        cout << "Error occurred in the selectRandLine";
    }
}

/*******************
** The main class **
*******************/
int main ()
{
    try{
        if(!myfile.is_open()){
            cout << "File not found" << std::endl;
            throw 404;
        }

        char a; //Guessing letter
        srand((unsigned)time(0)); //Seed RNG
        while (std::getline(myfile, line)) ++numlines; //Open the word list and count how many words are present.

        while (a!='*') //Continuous loop with exit number 2.
        {
            selectRandLine (); //Select a random word from the file
            makeDisplay(); //Make the correct number of underscores
            inttries = 0; //Reset number of tries
            while (display!=word) //Exit loop when word is guessed correctly.
            {
                cout << makeMan (); //Draw ASCII Man d-_-b
                cout << "Please guess a letter!\nWord: " << display << "\nGuessed: " << guessed << "\nTries left:" << 10-inttries << "\n";
                cin >> a; //Read user input
                guesslet(a); //Check if letter is valid and in word
                if (a=='*') inttries=10; //Check for quit character
                if (inttries>=10) display=word; //Meet condition to exit loop when tries expire
            }
            cout << makeMan (); //Draw ASCII Man d-_-b
            //Message when user loses.
            if (inttries>=10) cout << "\nYou lost! The word was \"" << word << "\".\nPress any key to play again, or * to quit.\n\n";
            //Message when user wins!
            if (inttries<10) cout << "\nYou won! The word is \"" << word << "\"!\nPress any key to play again, or * to quit.\n\n";
            cin >> a; //Read user input
        }
    }
    catch(int j){
        if(j==404){
            cout << "File words.txt was not found.";
        }
        else {
            cout << "Error number "<< j << " occurred in main.";
        }
    }
    return 0;
}
