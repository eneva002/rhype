# rhype
A command line music player for the [Hype Machine](http://hypem.com/)!

rhype uses a modified version of fzakaria's [HypeScript](https://github.com/fzakaria/HypeScript) to retreive a list of the current front page songs on HypeM. 
After retreiving the tracklist, you can play the tracklist in order.
The songs are played using [mpg123](http://www.mpg123.de/), a popular open source audio player.

##Dependencies
There are a few things you need before you can use rhype:

  * mpg123 (available in apt)
  * python2.7 (available in apt)
  * python-bs4 (available in apt)
  * python-beautifulsoup (available in apt)

##Installing And Using rhype
To install rhype, do the following:

```
$ git clone https://github.com/eneva002/rhype
$ cd rhype
$ make
$ PATH=$PATH:/path/to/your/rhype/bin
$ rhyped 
$ rhype update 
$ rhype play
$ #if you want to stop playing
$ rhype stop
```

####Basic Commands
The basic method of controlling rhype is to use `rhype <command>` where command can be any of the following:

  * `update` fetches the latest tracklist from hypem.
  * `list` lists the current tracklist loaded and indicates the current song. 
  * `play` plays the current tracklist in order from the beginning.
  * `stop` stops the current song.
  * `skip` skips the current song.
  * `pause` pauses the current song. 
  * `resume` resumes playing where the song was paused.
  * `help` lists all available commands.

##The Future Of rhype
This project is work in progress.
If you like the project or want to contribute, I encourage you to submit issues or pull requests.
My repo can be found [here](https://github.com/eneva002/rhype).



