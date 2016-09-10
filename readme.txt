For all those people who used the first version, look below, you will find there what has changed in version 1.01.

Well, what does this program?

Simply said:
You tell the program (=> in the goal file) what units/buildings/upgrade you want and the program gives you the (in most
cases) fastest build order to reach your goal.
The program is no Einstein but it does its job pretty well as much as I tested.

>>All times that the program tells you are that of a speed 5 game. This is because all times stated in StarEdit are<<
>>that of a speed 5 game, too.<<
To compare this BOs with others, either type them in stratagema or just test the calculated bo in the battle.net!

Well, you should look at it as a tool. It cannot give you exact advices what to do in a certain situation.
You have to play the calculated build order yourself to see where its weaknesses lie and where you could do some fine 
tuning.
The program starts with 50 minerals, 4 workers, a main building (Command Center, Nexus or Hatchery).
It simulates the build order on a standard map with 8 mineral patches and one gas geysire.
But there are of course different maps, different start positions where you have to place your buildings different.
In addition the mineral patches could be further away or there are could be more or less than 8 patches, so there is 
always an uncertainty of the build order.

I *could* add additional parameters to the program but I think it is pretty useless if you have to remember 
an own build order for every map and every race. The most important factor in a game is the enemy, a build order
is only one piece of the game.
But: Why should you waste time and resources already in the beginning of a game? That is way build orders are so 
popular I think. You want to concentrate on the game itself and you do not want to loose because your opponent knows
a way to get his units and upgrades faster.

If you have an other opion, please tell me :).

Setting goals (goal_t.txt, goal_z.txt, goal_p.txt):

- Max Time: (0-45)
Write here the time in minutes the program should need >at maximum<.
A smaller number may fasten up the beginning at the calculation in some cases though I would not recommend it to 
decrease it.
A good rule here is to set it to at least three times the number of minutes the build order will need (approximately).

- Max Generations: (0-999)
The more the more time consumes the calculation but the probability is higher that your results at the end are really 
most optimized.

- Max Vespene: (0-9)
The number of Vespene Geysirs availible near the hatchery/command center/nexus.

- Mutations: (0 - 99)
25 is standard, you could change it to get (perhaps) better results... well... ^^
Try 30 or 35 if you have a complex build order where the program can't even solve the problem at Max Time at all.
Anything above will lead to a pure random search :|

- Mutation Rate: (0 - 99)
50 is standard, same as above (the greater the LESS mutations).

- Detailed Output: (0 - 1)
Tells the program to write the time in front of the orders in the output file (1) or
to squeeze the build order to a short form ("3 SCV" instead of "SCV SCV SCV")

- Attack (0 - 1)
Well, as mentioned above, the program optimizes the build order. So it is very probably that the last unit is just ready 
when the last upgrade is complete.
But a dark templar in your own base is useless if you want to attack, so I added an algorithm that adds the distance
from you to the enemy to the build time of the units (that depends also on their movement speed).
So, for example your weapon upgrade is just ready when you enter the enemy base :)
0: Units stay in base
1: Units run to the enemy

- Time to Enemy (0-999)
Average time in seconds on LT from main to main, maybe less/more on some maps, this also depends on the positions 
(A zero means Air Map, no way to enemy!)
This is ignored when "Attack" is set to "0".

- The unit list: (0 - 99)
The number means how many units you want at least from this type.
I added an algorithm corrects errors in your goals. So if you set Templar Archives to "0" the program will build
one if you set for example Dark Templar to "1".
So you do not have to enter all the tech buildings if you do not care how many the program should build.

(example: the program will build high templars if you tell it to build archons)
If you don't tell the program to build for example a stargate to get scouts it will also try to get a scout without the
stargate :P. Though the program will still find good solutions the calculation may take longer...

FAQ:

- I don't know how to use the program...

Read on! Try to experiment with the goals ("goal_*.txt") and compare the results.
Or, write an email to scc@clawsoftware.de :)

- Why does the generations-counter jump back again and again?

This is no bug. The program counts down the generations when there is no improvement in the fitness (=points) of the 
build order. 

- Why does the program needs several runs to find a good solution?

Well, it happens that the program is stuck in a so called "local minima" where only a change of the whole
build order may result in a better fitness. Running the program 10 times should guarantee that the best build 
order is found.
You may end the program any time pressing a key.

- The program needs soo long to get a result...

Try to reduce the Max Generations. This will really speed up the process though it may lead to worse results :\
The program needs some cpu speed, so try to let it run "at top" or upgrade your cpu ;-).
You can find an article on the ClawSoftware homepage in the "AI" section (http://www.clawsoftware.de/ai.htm)
about the speed problem.

- The program has gone through all 5 runs but it did not come up with any result!

Well, there are two reasons for this:

1. You have given the program not enough time and/or too many goals. You should try to increase the Max Time
(=> Max Time in the goal*.txt files) or reduce the number of goals the program shall calculate.
Remember, any build order above 10 minutes gets more and more useless as the enemy will probably intervene.
So giving the goal to build 99 nukes or something like that (which would be impossible because of the supply by 
the way ;-)) will not work.
A good rule is to keep the amount of goals below 25.

2. If the method above did not work it may be a bug. But try to build only one 'branch' of your goals, reduce the
upgrades or the unit count. If that works it may be a bug in one of the branches or you should increase Max Time.


Program structure:

The Calculator uses Genetic Algorithms starting with a population of random generated build orders.
The best of these "programs" may copy itself over the other programs deleting their build order.
Mutations take place changing the build order of a program which (in most cases) reduce the fitness of it while in a few
cases the build order gets better.
"Fitness" equals points the program get for completing a task or doing all tasks you given in a short time.
Example:
	- your goal: get 5 drones
	- a first approach may be building 5 overlords, then 5 drones
	- due a mutation a program builds only 4 overlords, then 4 drones => faster => less time used => more fitness
	... and so on

Known Bugs:

- SCVs and Probes need time to get to the building place and time to return to the mineral line. As you may (especially with
  protoss) to build multiple buildings with one Probe/SCV there is a little error in the time calculation...
  I used 3 seconds for zerg, 4 seconds for protoss and 5 seconds for terra. Well... this depends where you want your 
  buildings (for a wallin for example). But I don't think this is a big factor.
- There is no option for the build order to wait until a certain amount of minerals are reached (to build for example 
  multiple buildings). This is no bug but may improve some build orders when implemented.
  (Although I noticed, that the program instead of waiting for the minerals build workers. 
  (set "Marines 30" as a goal and read the build order. On of the best builds 3 Barracks just as the minerals hit 450))
- You might have noticed that the program has sometimes well... its own will. As soon as the goals are completed
  it builds random units/buildings. 
- In addition there are in some cases some minerals and/or gas left (depends on the goals you set).
  I will probably add at the end of the calculation a final run, where the program puts additional units/buildings in
  the build order.
- your turn :P Go, find some :)


Version 1.01 Bug Fix/Update:

- Hydralisk now cost 75/25 instead of 75/0
- Zerg no longer can research Dark Swarm or Parasite
- Upgrades and Researches work now properly
- Added a complete tech tree to all races. You do not have to enter all tech buildings, just the units you want.
- All 3 .exe files are now combined into one
- Reduced Runnings from 10 to 5
- better viewable output file
- better viewable input file
- added options "Time to Enemy", "Detailed Output" and "Attack" (see above)
- speed up of calculation (a bit)
- changed Terra harvesting rules
- added some error handling
- Added some lines to the readme.txt
- corrected some errors in the output
- corrected some other minor bugs


Future Options/Features (v1.02)

- Terran: Wallin Defense (You can choose between different types of wallins and when they should be ready)
- Zerg: Hatchery at the entrance of your plateau/area, with sunkens and zerglings after a certain time
- Protoss: 2 cannons, some zealots at the front
- In addition to those scripts you will have the option to set your own early defense or let the program decide what units 
  to build
- Scout Probes/SCVs/Drones (will change the BOs a bit, sorry that this didn't make it in v1.01) 
- Expansions
- Shuttle option for units (that's already implemented for reaver, though not for other units yet)
- Terra: Flying buildings (for scouting, or for a rax or cliff drop)
- In addition to the "Time to Enemy" some units need to wait to get more energy before you can use them effective
- Interceptors, Scarabs 
- (Probably in v1.03) You give the program your own BO and it will try to optimize it
- (Probably in v1.03) After a certain amount of time the BO will split into several branches (depends on what the scouting 
  unit has revealed)
- (Perhaps in v1.04) Something like a damage calculator...
- (Maybe in v8.00) A Bot that plays for your and wins every game, just sit and watch it running. 
  No more clicking needed. ;-)

A word to a WarCraft 3 Calculator:

Well, it would be easy to transfer the data from WarCraft to StarCraft though I think it would be pretty useless.
As far as I know there is not much build order to calculate ^^. Well, let's hope Blizzard do something about that :|.
What do you think? 


You missed something in this file? Please write me an email!
I am working on this program because of you, not of me, I do not get anything from it but your feedback.

	IRC Quakenet: #amb
	scc@clawsoftware.de
Don't hesitate to write your opinion/suggestions/experiences with the program! 
I would also be happy about bug reports or hints to make the program better :)

			Visit www.clawsoftware.de for updates!

This is freeware, you may give it to all your friends if you include all files 
(scc.exe, readme.txt, goal_t.txt, goal_z.txt, goal_p.txt and this file readme.txt) though donations are welcome of course...
		You may not decompile or change the executable without permission.
		You may not sell the program. 
Copyright by clawsoftware.de.
Warcraft, Starcraft, Starcraft:Broodwar, StarEdit are trademarks of "Blizzard".


Thanks for reading!

Oh, one last thing:
Some feedback I got from v1.00:

- "solid piece of programming indeed..." though it is "no miracle maker"
- "You are a newbie, so don't try to re-invent strategies you newbie dork."
- "cool idea"
- "perhaps I should read the readme... mmmmh... no I'll think I just play..."
- "6 Lings and it said "build a greater spire" ^^ crap"
- "I just want to warn other people to download this crap"
- "btw: I know the BO for 6ling rush..."
- "this needs VERY long..."
- "would be cool with a graphic interface!"
- "this sucks..."
- "It's always the same... I try to optimize my 2rax bunker rush vs zerg and I get exactly that what I already knew..."
- "... a good successor of stratagema..."
- "... this is too confusing for me, although I've read that it works fine..."