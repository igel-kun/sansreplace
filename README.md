# Random choice algorithm

This generates k distinct natural numbers less than n, in sorted order, fairly
among all the ways of doing so.

The obvious way to do it: generate a candidate, reject if it's already been
generated, repeat until you have k. However that's not linear time; if you're
asked for (n=20, k=19) you will reject a lot of samples.

What I like about this way: you don't have to store the samples generated so far
in anything more complex than a list, and you don't have to crawl over them all
for a new sample either.

Intuition: supposing you have (n=7, k=3). So you have three red balls out of
seven balls total; let's say the other four balls are white. Start with the four
white balls in a row

     O O O O

We want to add a red ball; there are five places it can go

     O O O O
    0 1 2 3 4

Supposing we pick 1, then we get

     O x O O O

Now there are six places the next ball can go, which we could number

     O x O O O
    0 1 2 3 4 5

But instead we number them like this:

     O x O O O
    0 1 5 2 3 4

Also, we don't care about the final ordering among the red balls, so we just
keep track of which white balls they're between. Now add another red ball:

     O x O O x O
    0 1 5 2 3 6 4

And another:

     O x x O O x O
    0 1 5 7 2 3 6 4

It helps me to imagine that instead of white balls we have solid white marble
blocks, and instead of red balls we have thin red cards. Initially there's just
one place to drop a card between two marble blocks, but once we drop a card in
there, there are now two places to drop a second card, and so on.
