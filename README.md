# createED_hackathon_simon_game

## Inspiration
I have implemented an online version of the game last Christmas, using basic Javascript, HTML5 and CSS. Whilst brainstorming for ideas, we figured - as a group - that since none of us have experience with hardware we'd try to create a physical version of the game. 

## What it does
The way the game works is that the user is given a series of buttons and a counter. Each time the user inputs a series of button presses correctly, they can see the same series of button presses but with an additional step. There's also a sound associated with each button press. The user is also notified in case they press the wrong button, then they are notified that they have done so, and the game restarts at a new random series of button presses, from stage 1. The user can win the game by getting a series of 9 (we reduce it to 3 in the presentation, for the sake of time) steps correct. Once the game is won, a series of funky lights and sounds play, then the game resets.

## How I built it
After a little research, we came to the decision of implementing the game using an Adruino as we have seen plenty of online support for it. Only two members of the group, including myself, had a little bit of experience with C. So, suffice to say, it was a long process to implement it in the Adruino language (which's very similar to C++). 
We built it using a large breadboard, a switch button, four push buttons, four LEDs, a speaker, an Arduino Uno, and a bunch of jumper wires.

## Challenges I ran into
Our main challenge at the beginning was to understand how the circuit would work. It was helpful going to the electronic workshop, which gave us a head start. It took us quite a lot of time to make the breadboard (and the circuit, overall) look as humane as possible.

Another big challenge for us was the code. We found plenty of online help with that, so we were quite fortunate and didn't get stuck there for too long. 

We also had a bit of trouble running out of pins on the Adruino and, in essence, understanding how the Adruino itself works.

## Accomplishments that I'm proud of
We are very proud to have found a project that is suitable for our level of experiences, and that we have all managed to learn an awful lot. Everyone had something to do, everyone was excited and showed tenaciousness. The statement, "I didn't expect us to get that far" that kept repeating throughout the hack kept us pushing further for more functionalities. 

## What I learned
We learned quite a lot about circuits, electricity, the Adruino as a micro-controller and, most importantly, I think each of us will leave here today knowing how to work better in a team.

## What's next for Simon Game
We're very happy with the functionality of our game. What's next for Simon Game lies in the aesthetics, namely in hiding the wires and making it look more user-friendly.
