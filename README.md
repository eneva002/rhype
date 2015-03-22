#rhype
rhype is a command line music player for the [Hype Machine](http://hypem.com/).
A modified version of fzakaria's [HypeScript](https://github.com/fzakaria/HypeScript) to retreive a list of the current front page songs on HypeMachine.
After retreiving the tracklist, you can play the tracklist in order.
Music is played using [mpg123](http://www.mpg123.de/), a popular open source audio player.

The type of music that is played depends entirely on the music that hypem is posting.
Currently, rhype only looks at the [popular](http://hypem.com/popular) section of hypem.
According to hypem, this section contains "The most popular artists, searches and blogs on the internet right now".
If you're curious about how their aggregator works, I encourage you to take a look at their [about](http://hypem.com/about) page.

##Installing rhype
To install rhype, do the following:

```
$ git clone https://github.com/eneva002/rhype
$ cd rhype
$ make
$ PATH=$PATH:`pwd`/bin
```

####Dependencies
There are a few things you need before you can use rhype:

  * mpg123 (available in apt)
  * python2.7 (available in apt)
  * python-bs4 (available in apt)
  * python-beautifulsoup (available in apt)

####Basic Commands
After rhype has been installed, spawn the rhype daemon with

```
$ rhyped
```

Now you're ready to play music!

```
$ rhype update
$ rhype play
```

Note: There will be a slight delay as the track list and songs are downloaded.

rhype is controlled using  `rhype <command>` where command can be any of the following:

  * `update` fetches the latest tracklist from hypem.
  * `list` lists the current tracklist loaded.
  * `play` plays the current tracklist in order from the beginning.
  * `stop` stops the current song.
  * `skip` skips the current song.
  * `pause` pauses the current song. 
  * `resume` resumes playing where the song was paused.
  * `exit` kills the daemon
  * `help` lists all available commands.

##Implementation Details
rhype works by using `HypeScript` to acquire a list of URLs from the hypem playlist.
Once rhype has the list of URLs, they are downloaded temporarily, and played using mpg123.

All working files for rhype are stored in a folder within your home directory called `rhypefiles`.
You can view the rhype file folder using `cd ~/rhypefiles`.

**Warning:** Modifying the contents of `/rhypefiles` will likely break the program and it is not recommended.

####The rhype daemon
The bulk of the processing is handled by `rhyped`, the rhype daemon.
If the daemon hasn't been spawned, the program will not work.

Attempting to run rhype without the daemon present will result in one or both of the following errors: 

  1. `daemon PID not found: No such file or directory`
  2. `could not connect with rhyped: No such file or directory`

####Long Term Use
For long term use, it will become inconvenient to always modify your PATH by hand.
A solution is to modify your `~/.profile` file to permanently append the rhype bin path.
You can do this by opening up `~/.profile` using your favorite text editor and adding the following line of code:

```
export PATH=$PATH:/path/to/rhype/bin
```

After the profile file has been modified, log out and log back in for the changes to take effect.
With the modified profile file in effect, you will never have to manually change your path again!
If you move your rhype folder, your `~/.profile` file should be modified to reflect the changes.

##The Future Of rhype
This project is work in progress.
If you like the project or want to contribute, I encourage you to submit issues or pull requests.
My repo can be found [here](https://github.com/eneva002/rhype).

####Goals

  * Improve portability by using more portable syscalls.
  * Play music without creating a local copy of files.
  * Allow users to play individual songs.
  * Allow users to specify areas to scrape, i.e. `popular` vs `latest`.
  * Improve playback controls
  * Port to Python (maybe?)



