# rhype
A desktop music player for hypem.com!

####The current state of things.

As it is, the song URLs are hidden away in the depths of HTML. There are two ways that I can go about this: parse the HTML or use a modified version of [HypeScript](https://github.com/fzakaria/HypeScript).

I think a modified version of HypeScript is the easier choice, since I get to skip handling the entire issue of internet data handling.

The modifications I need to make are twofold. The first mod I need to make is to have change the download functionality so it is optional. The second mod I need to make is to save the URLs into either a temporary file or into a variable within my program.

Once I have the URLs from HypeScript, I simply need to figure out a way to play said audio via a music player.

After I have the html acquisition working, I will transition to the daemonization of the program.



####C++ Audio

To play the music I retrieve, I plan to implement the [LIVE555](http://www.live555.com/liveMedia/) set of libraries.

Or possibly something else, I'm still doing my research on it.
