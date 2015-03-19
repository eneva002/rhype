# rHype
A desktop music player for the [Hype Machine](www.hypem.com)!

##How It Works
rHype uses a modified version of fzakaria's [HypeScript](https://github.com/fzakaria/HypeScript) to retreive a list of the current front page songs on HypeM. 
After retreiving the tracklist, you can play whichever song you like as many times as you like.
The songs are played using [mpg123](http://www.mpg123.de/), a popular open source audio player.

##How To Get rHype Running
There are a few things you need before you can build rHype.

  * mpg123 (available in apt)
  * python2.7 (available in apt)
  * beautiful soup (available in apt)

Once you have all the dependencies taken care of, cd to your rHype folder and type `make`.
Let everything compile and then cd into the bin folder with `cd bin`.
Spawn the rhype daemon (rhyped) with `./rhyped`.
Add the bin folder to your path.

####Basic Commands
The basic method of controlling rhype is to use `rhype <command>` where command can be any of the following:

  * `update` fetches the latest tracklist from hypem. (working)
  * `list` lists the current tracklist loaded and indicates the current song.
  * `play` plays the current tracklist in order.
  * `stop` stops the current song.
  * `pause` pauses the current song. 
  * `resume` resumes playing where the song was paused.
  * `help` lists all available commands.

