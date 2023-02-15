#NatSel

NatSel is a natural selection simulator (NSS).  This game will make a large population of of lifeforms with various attributes (strength, speed, intelligence, etc...). These lifeforms will be competeing with one another for the chance to live on, reproduce, and spread their genes.

###How the genes work in NatSel

At the beginning of the game, there will be some initial batch of different species lifeforms. There will be many lifeforms of each species (so that they have a chance to reproduce). Lifeforms cannot mate with lifeforms that are not in their species. When a couple mate, there is a random chance than their offspring will have some mutation. This mutation will be minor so they can still mate with their own species. However, after recurring mutations to the same line of offspring, this will become so genetically different from the original species that it will become incompatible and the two species will no longer have the ability to mate.

However, due to practical problems, a lifeform's genetic code and genes will be seperate data types. 

The individual will have both a genetic string (64 character long string of alpha-numeric-underscore-dash characters) that will only serve as a genetic "tag" or "marker" or "stamp". It will serve no purpose other than to distinguish species once they become significantly different from one another. The actual genetic attributes will be stored in other variables (like strength, speed, intelligence, etc...)

Through this, new species will have the ability to develop and possibly surpass the old ones.

That is the goal.

###Platform

This simulator engine should be fairly cross-platform. I am going to try to use the lease amount of proprietary Windows API code as possible. Ideally, I would like to use none at all. However, This might not be possible. We will have to see.


###License

Creative Commons Attribution Non-Commercial Share Alike U.S.S 3.0 (CC-BY-NC-SA U.S. 3.0)

###Contact

If you have any questions, comments, or concerns, feel free to email me!


Ryan Jensen

JensenR30@gmail.com
