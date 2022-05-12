# Veni-vidi-vici
CS1021 Lab 5

Introduction:
Since the beginning of time people have sent messages that they only wanted the intended recipient to understand. Sometimes the speaker would tell the message to a trusted courier who would deliver the message to the speaker's counterpart. Sometimes the writer would mail a letter and seal it with a wax stamp to indicate to the reader whether the message had been opened in transit. No matter the mechanism, there have always been people who wanted to keep certain communications secret.

And, for as long as there have been secrets, there have been people dedicated to exposing them. The battle between the coy and the nosy has been fought back and forth throughout the ages. Whether by hiding the truth or using trusted intermediaries, early furtive senders would rely on surreptitiousness to keep a message secret. The technique of "security through obscurity (Links to an external site.)" did not hold up long when exposed to dedicated adversaries.

What the secretive sender needed to communicate with the reluctant reader was a method of communicating that could protect the information whether a spy knew the means for its protection or not. In other words, the sender and receiver had to assume that the spy knew the method by which they were keeping a secret and still be able to communicate privately. The need led to the development of encryption.

Encryption/decryption methods are known as schemes. In an encryption/decryption scheme, there is an algorithm for taking the original message (the plaintext) and transforming it to something that an eavesdropper can't understand (the ciphertext). This process is known as encryption and is performed by the sender. In an encryption/decryption scheme, there is a corresponding algorithm for taking the ciphertext and reversing the encryption -- the process is known as decryption and is performed by the receiver.

Encryption/decryption schemes are publicly known, well documented and standardized (Links to an external site.). If the methods of encryption and decryption are known, why can't the sender's foes use that information to recover the plaintext? Because encryption/decryption schemes usually rely on the sender and the intended recipient sharing some data that is used to configure the encryption/decryption scheme in a particular way. The data shared between communicating parties that can be used to configure the encryption/decryption scheme is called a key.

Untitled drawing(1).png

Using a good encryption/decryption scheme and key to protect a message means that the sunglassed snooper has no way of knowing the contents of the message even if they know the algorithm used to protect the message.

One of the earliest encryption schemes was employed by Julius Caesar (Links to an external site.) to keep his messages safe. A type of substitution cipher, the sender and receiver agree on the key -- a shift number and direction (left or right) -- and, to encrypt, the sender shifts each letter in the plaintext in the chosen direction and by the number of spaces indicated by the shift number to create the ciphertext and, to decrypt, the receiver shifts each letter in the ciphertext in the opposite direction and same amount to restore the plaintext. It is called a substitution cipher because each letter in the plaintext is substituted for a letter in the ciphertext.

Untitled drawing(3).png

Figure 1: Substituting characters in plaintext for ciphertext when using a key with a shift number of 3 and right direction.

An example will help!

Assume that I want to communicate with my parents. We would agree that I would encrypt my messages by shifting each letter 5 (the shift number) characters to the right (the direction). I would encrypt the message "hello" as "mjqqt". Why? Because m is five letters to the right of h in the alphabet, j is five letters to the right of e in the alphabet, and so on. To be able to read the secured message, my parents would shift each letter of the ciphertext to the left by 5 and recover the original plaintext. Hello, indeed.

Implementing the Caesar Cipher is done with modulo arithmetic and by equating each letter with a number according to its position in the alphabet. Assume that we have a function named number_from_letter that turns a letter into its position in the alphabet: a is 0, b is 1, c is 2, etc. For example, if we call number_from_letter with the argument d, the return value is 3.

Assume that we have another function named letter_from_number that turns a number between 0 and 25, inclusive, into a letter from the alphabet: 0 is a, 1 is b, 2 is c, etc. For example, if we call letter_from_number with the argument 1, the value of the expression is b. We can use these functions to come up with the ciphertext given the key and the direction.

What is the general process for encrypting a single character? Let's use a variable, c, to represent the plaintext letter that we are encrypting. Note carefully that we are using c as a variable to represent any character. We will name the result of a call to number_from_letter with the argument c the index of the plaintext letter. If the direction of encryption is right, we will add the shift number from the key to the index of the plaintext letter. That gives us a number that represents the position of the ciphertext character in the alphabet, what we will call the index of the ciphertext character. To get the actual ciphertext letter, we call the letter_from_number function with the index of the ciphertext letter as the argument. Voila, the result of that function call is the enciphered character.

If the direction of the encryption is left, we will subtract the key from the index of the plaintext letter. Otherwise, the process is the same!

That works fine for most cases. However, there are two corner cases that we have to consider.

First, what happens if the index of the ciphertext character is past the end of the alphabet? For example, if we attempt to encrypt z with a shift number of 1 and a direction of right? We know that we want the ciphertext letter to be a. But, how do we calculate it algorithmically? Using the algorithm from above, we would calculate the index of the ciphertext character as 26 in this case. However, we can't call letter_from_number with an argument of 26 because our numbering scheme equates 25 with z! Despair! Wait: we can use our friend the modulus operator! Taking the index of the ciphertext character and "modding it" by 26, the number of characters in the alphabet, will solve the problem. In our example, 26 % 26 is 0 and that becomes the updated index of the ciphertext character. Using the updated index of the ciphertext character as the argument in the call to letter_from_function means, in our working example, that the ciphertext character is a. Just what we wanted!

Second, what happens if we calculate an index of the ciphertext character that is less than 0? For example, if we attempt to encrypt the letter a with a key of 1 and a direction of left? Intuitively, we know that we want the ciphertext character to be z. But, how do we write a process to do it? Using the algorithm from above, we would calculate an index of the ciphertext character of -1 in this case. Uh oh, there is no letter of the alphabet equated with the number -1. To solve the problem, when the index of the ciphertext character is negative, let's overwrite it with an updated index of the ciphertext character calculated by subtracting the old index from the number of letters in the alphabet (26). Therefore, in the working example, the index of the ciphertext character becomes 25 (26 - 1). Using that updated index of the ciphertext character as the argument to letter_from_function means that the ciphertext character is z! Bingo!

In this lab, you will develop an encryption program named 1d3s to read in a key and plaintext message from a file and print the encrypted version which will be safe from
prying eyes (Links to an external site.)
.

As always, read the entire lab document before beginning!

Good luck!

Program Design Task:
As my dad always said, “If you want something done wrong, you have do it yourself.” Before you start writing code, please write the pseudocode or draw a flow chart for your implementation of the 1d3s application.

Program Design Requirements:
Your pseudocode or flow chart must describe the entirety of the solution. You may choose to write the flow chart or the pseudocode at any level of detail but remember that this is a tool for you! Your pseudocode or flow chart must include a description of how you plan to

Read in the encryption key (shift number and direction) and plaintext from a file,
Handle any errors in the formatting of the input file,
For each character in the plaintext
Calculate the index of the plaintext character,
Calculate the index of the ciphertext character,
Handle situations where the index of the ciphertext character is longer than the alphabet,
Handle the situation where the index of the ciphertext character is shorter than the alphabet,
convert the (possibly adjusted) index of the ciphertext character to the actual ciphertext character, and
Print the ciphertext to the screen.
Programming Task:
Your programming task is to implement the 1d3s application. In this lab you will not prompt the user for input. You will read all input from a file named input.txt. Like Lab 4, a skeleton file is provided (below) and you must use the skeleton.

The input file will be formatted like so:

<l or r><shift number (an integer)><first character of plaintext><second character of plaintext>...<last character of plaintext>

The first character is the direction (l for left and r for right) and the number is the shift number. For example, an input file might contain:

l4hello
which would tell 1d3s that the encryption direction is left and that the key is four (4).

Your program will calculate the ciphertext and print it to the screen on a single line. For example, if you run 1d3s with an input file whose contents are

l4hello
the output would be

dahhk
As another example, if you run 1d3s with a file whose contents are

l28goodbye
the output would be

emmbzwc
The 1d3s program must also properly handle input files that are improperly encoded. If there is no direction provided, 1d3s must output

Oops: Could not read the direction from the input file.
If the first character in the file is not an l or an r, 1d3s must output

Oops: Invalid direction in the input file.
If there is no shift number provided, 1d3s must output

Oops: Could not read the shift number from the input file.
You may test your code using these test input files: one  Download one, two  Download two, three  Download three, four  Download four, five  Download five.

To check whether your program is operating correctly, you may want to use one of these online Caesar (Links to an external site.) Cipher (Links to an external site.) implementations (Links to an external site.).

Note: Your program will be tested against other test cases. Your program must compute properly in all cases in order to receive full points! Check the output of the autograder to make sure that your program behaves as expected. Read the autograder's output carefully!

Programming Requirements:
Start with this skeleton  Download skeleton(if you are a Mac user, use this skeleton  Download this skeleton) that provides the functions you will need to use to successfully complete this lab. If you do not use this skeleton code you will not be able to complete this lab. The skeleton code contains two useful functions:

number_from_letter: This function takes a single parameter, a character. The output from the function is an integer according to the equation between number and letters described in the introduction (above).
letter_from_number: This function takes a single parameter, an integer. The output from the function is a character according to the equation between number and letters described in the introduction (above).
You may make the following assumptions:

The file input.txt will always be available and readable.
The plaintext will be entirely lowercase.
The plaintext will only contain valid alphabetic letters.
The plaintext will contain no numbers.
You must use the provided constant anywhere that you need to use 26, the number of letters in the alphabet.

Critical Thinking Task:
We talked in class about an interesting property of the for loop: Every for loop can be rewritten as a while loop. How cool is that? Your Critical Thinking Task is to describe (graphically or textually) a mechanical (algorithmic) process for converting between for loops and while loops. You may use any means you choose to describe the transformation. Bonus points may be awarded for creative presentations. You may use the following terminology to refer to different parts of the for loop when describing the conversion:

for (initialization statement; condition expression; update expression) {
  body
}
Critical Thinking Requirement:
As stated above, you may use any means you choose to describe the transformation between for loops and while loops. You must describe the transformation process generally -- you cannot simply describe how you would translate a particular for loop into a particular while loop. Bonus points may be awarded for creative presentations at the discretion of the professor and TAs.

Deliverables:
The pseudocode describing the algorithm of your 1d3s program in PDF format (named design.pdf).
The C++ source code for your 1d3s application (named 1d3s.cpp).
A written response to the Critical Thinking Task prompt in PDF format (named equivalent.pdf). If you chose to satisfy the Critical Thinking Task using a means that is not easily transmissible as a PDF, please upload an appropriately named PDF with instructions on how to access your masterpiece!

Code is appropriately commented to match the solution's pseudocode and variables are given appropriate/meaningful names.
Related Learning Objectives:
Writing boolean expressions using relational and logical operators
Using if-statements to implement selective program execution
Using algorithmic thinking to design programs
Write syntactically correct for, while and do-while loops
Identify the components of for, while and do-while loops
Understand the difference between pre- and post-test loops
Use each of the three types of loops in the appropriate situation
Use methods on file stream objects to read/write files
Credits
writer by Kamin Ginkaew from the Noun Project

writer by Smashing Stocks from the Noun Project

reader by Komkrit Noenpoempisut from the Noun Project

