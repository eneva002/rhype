# rhype
A desktop music player for hypem.com!

####URL Retreival

As it is, the song URLs are hidden away in the depths of HTML. There are two main things that have to be implemented. The first is to parse the HTML from [Hype Machine](www.hypem.com) and locate the JSON encoded server URLs. The second is to decode the JSON and retreive the actual server URL. 

Most of the URL retreival portion of my program is based on [HypeScript](https://github.com/fzakaria/HypeScript), a python script to automatically download files from hypem.

####Audio

To play data from the stream, I will use `mpg123`.

To install, use `sudo apt-get mpg123` or refer to their [website](http://www.mpg123.de/)

After I have the html acquisition working with audio, I will transition to the daemonization of the program.


