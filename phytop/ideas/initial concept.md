# Physics Simulation Controlled by the Behavior of the Processes Currently Running on Your Computer.

Ryan Jensen

2019-10-08

Imagine each process running on your computer appears as a colored circle on your computer screen.
The color indicates how much ram the process has been allocated.
The size indicates how much % CPU the process is consuming.

It would be cool if these circles (that represent processes) obeyed the law of gravity in a 2D space.
When a new process starts, it appears close to the top of the screen.
Perhaps it hangs there at the top of the screen, peacefully, for a few seconds, as if it still retained some kind of purity from having just been spawned into existence.

5 seconds after the new process was created, the 1-pixel-wide digital thread holding it to the ceiling snaps.
The process is allowed to fall, like rain, or manna from heaven, down into the depths of hell below.

all processes have mass (important, because that means they have inertia).
This means it takes time for the circle to react to the behavior of the process.

The global time constant should be adjustable, and adjustable per parameter.
I.e., you must be able to:
- change the speed of everything by some rate.
- change the speed of specific parameters by some rate.
- change the ranges of display parameters (colors, how parameters map to visual features: e.g. CPU % maps to size of process's circle)

each process circle should have the name of the process printed right under it.
I will need to find a tiny font for this.
perhaps I can print the names of the processes in a normal font if the circle is big enough.
I need to think about the scale of things here...
I should make everything double-precision floating point numbers.
I will implement a function for each parameter.
The filter will be a first-order, infinite-impulse-response low-pass filter.

The low-pass filter time constant (double-precision floating point) can be set to any positive number (including zero).

On second thought, the processes need to be spawned near the bottom of the screen.
This is because, with all the processes that are generated, they will mostly fall and form an ocean of idle-processes.
So when a new process is brought into being, I want it to make pop into being at the bottom.
That way, if it starts consuming a ton of CPU % right away, it will grow big, displace the processes (colored circles) around it, causing an explosion of processes.
It would look so cool.  Imagine starting up a very resource-intensive process such as ffmpeg.


The end result of all this madness should be:
1. a computer screen on which is displayed an assortment of balls.
2. the balls have various sizes and colors.
3. the balls exist in different places on the screen.
4. their movements seem to have patterns, and coincide with your activity on the computer.
5. if you start a resource-intensive process, a big circle will grow from the depths and blast all of the other processes out of the ocean.

Actually, the user should have a choice.  There should be an option in the configuration menu:
- at what position does the process enter the screen?  y-coordinate? x-coordinate?  value? options such as random, linear, etc...

I should get the core-concept working first, and then start adding all the options, one by one.

First Steps:
    - I need to find a physics engine, because I don't want to write one if
      an almost-perfect one already exists for free.
    - I need to find a program that will tell me all the processes that are
running on the computer, and give me as much
information about all of those processes as possible.
I need to know how much RAM they are using, CPU %, how much total RAM
the computer has or RAM % alone would work.
   - I need to decide what graphics library I want to use.  SDL?  OpenGL?
  This program seems like the perfect project to learn a bit of OpenGL
  because of the simplicity (2D circle-drawing and text-rendering).
   - I need to decide which programming language I will use that has good
  support for most popular operating systems,
  the graphics library I want, and can be interfaced to the
  process-reporting process I mentioned earlier.



python has an amazing library called `psutil`.

Here is something you can do with it ([source](https://psutil.readthedocs.io/en/latest/#cpu)):

```python
>>> import psutil
>>> for proc in psutil.process_iter():
...     try:
...         pinfo = proc.as_dict(attrs=['pid', 'name', 'username'])
...     except psutil.NoSuchProcess:
...         pass
...     else:
...         print(pinfo)
...
{'name': 'systemd', 'pid': 1, 'username': 'root'}
{'name': 'kthreadd', 'pid': 2, 'username': 'root'}
{'name': 'ksoftirqd/0', 'pid': 3, 'username': 'root'}
...
```

