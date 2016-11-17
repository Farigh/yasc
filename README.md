# yasc
Yet Another Spell-Checker

## Why this project?
I recently had a conversation with someone called Mark and he asked me the following question:
> How would you check if this string "This is a string" is a valid one based on a given dictionnary ?

I answered simply:
> It's quite easy, you make a map from your dictionnary, split the string based on spaces and then match each word using your map !

Mark then said:
> Now imagin your language does not actually have any separator and your string can be split like this :
>   - "Th"
>   - "is a"
>   - " str"
>   - "ing"

I didn't have any working answer. And for each I gave Mark, he would come up with a non-working edge.
We finally closed the discussion with this solution :
> Build a tree from the dictionnary :
>   - each node is word
>   - each child is a word prefixed with its parent
>   - the head is the empty string

This has kept me thinking since and I have many ideas. I basically came out with an entire spell-checking program.

## Objectives
For now on, the prime goal of this project is to put together every idea I have on the subject, experiment and produce a working program.
I do not intend to do any research on the subject as for now, maybe in a second phase, once I'm confortable with what I did on my own.
