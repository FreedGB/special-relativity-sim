# Spacetime Globe Simulation

A graphical simulation built with Raylib and Raygui to visualize fundamental concepts of Special Relativity: Lorentz transformations, time dilation, and length contraction in a 1D space and 1D time (1+1D) spacetime diagram.

## Description

This project is an interactive spacetime diagram where you can observe how events and objects (rods) appear differently to observers moving at various relativistic velocities. It illustrates the core principles of special relativity, allowing users to:

- Visualize two frames of reference: the "Lab Frame" (your initial, stationary frame) and the "Observer Frame" (a frame moving at a velocity relative to the Lab Frame).
- Understand Lorentz transformations by seeing how coordinates of events change between these frames.
- Demonstrate relativistic effects like time dilation and length contraction through interactive elements.

This visual tool is highly inspired by the spacetime globe shown in minutephysics special relativity video series.

## Getting Started (Installation)

This project uses `Raylib` and `Raygui`, great librairies to make video games using C/C++.

### For Windows users ⊞

1.  **Download Raylib:**

    - Go to [Raylib website](https://www.raylib.com/) and click on "Download Now" to downlaod the installer. The installer comes with MinGW compiler, so no need to download it.

    - Once downloaded, run the installer with admin rights to install Raylib.

    - Navigate to the folder where you installed Raylib, and copy the path to `src` folder somewhere, you'll need it to run the simulation.

2. **Download Raygui:**

    Raygui is typically included as a header-only library.
    
    - Go to [Raygui repository](https://github.com/raysan5/raygui), move to `src` and download `raygui.h`.

    - Go to the `src` folder in the folder where you installed Raylib, and paste the `raygui.h` file there.


3.  **Compile the project:**

    - Download this project with `git clone` or downloading the zip version (don't forget to extract it if you downloaded the zip version).

    - Open the project with Visual Studio Code, or your prefered IDE.

    - Go to `build_windows.bash` file and replace `path/to/raylib/src` with the path you copied.

    - Open the terminal and run the build file:
    ```bash
    bash build_windows.bash
    ```


### For Ubuntu users 🐧

1.  **Install Build Essentials:**

    This will help install `g++`, the C++ compiler. Open your terminal, and enter these commands:
    ```bash
    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get install build-essential
    ```

2.  **Install Raylib (from source, recommended for Linux):**

    Then, enter these commands:
    ```bash
    # Install Raylib dependencies
    sudo apt install libglfw3-dev libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglu1-mesa-dev

    # Install Raylib from source
    git clone https://github.com/raysan5/raylib.git raylib
    cd raylib/src
    make PLATFORM=PLATFORM_DESKTOP
    sudo make install
    ```

3. **Download Raygui:**

    It is just like for Windows.
    
    - Go to [Raygui repository](https://github.com/raysan5/raygui), move to `src` and download `raygui.h`.

    - Go to the `src` folder in the folder where you installed Raylib, and paste the `raygui.h` file there.

4.  **Compile the project:**

    - Download this project with `git clone` or downloading the zip version (don't forget to extract it if you downloaded the zip version).

    - Open the project with Visual Studio Code, or your prefered IDE.

    - Open the terminal and run the Makefile file:
    ```bash
    make main
    ```

Whatever your system is, you can run the simulation by using:
```bash
./spacetime_globe
```



## Features

![Spacetime Globe Simulation](images/spacetime_globe_simulation.png)

The simulation displays a 2D spacetime diagram with a spatial axis (horizontal) and a temporal axis (vertical). One unit on the x-axis represents $3\times 10^8$ meters (the distance light travel in one second) and one unit on the y-axis represents $1$ second.

Two frames are used in this simulation:

  - **Lab Frame (Secondary Grid):** This is the "rest" frame. This frame's grid lines appear to "shear" or deform when viewed from the Observer Frame, demonstrating how space and time mix under relativistic speeds.

  - **Observer Frame (Primary Grid):** This is *your* current frame of reference, which can be set to move at any velocity relative to the Lab Frame using the velocity slider. The grid lines of this frame always remain orthogonal and regular on the screen, as you are observing everything from this perspective.

The simulation applies the **Lorentz transformation** dynamically to all elements in the Lab Frame, showing their appearance in your chosen Observer Frame.

This tool allows you to:

- Visualize the two frames, making clear distinctions between the fixed-on-screen Observer frame and the transforming Lab frame.

- Change your observer's velocity ($v$) relative to the Lab Frame using a slider. As $v$ approaches the speed of light ($c$), you'll observe the relativistic effects.

> [!NOTE]
> $c$ (speed of light) is normalized to `1.0` in this simulation. So, the observer's speed $v$ is mesured as a fraction of $c$.

- Place individual "events" (spacetime points) in the Lab frame and see how their coordinates change in the Observer frame.

- Place "rods" (representing extended objects) in the Lab frame and witness their length contraction when viewed from a moving Observer frame.

The interface is clear and user-friendly, so you're highly encouraged to poke around to understand how it works.


## Two consequences of special relativity

In this section, we will use this simulation to vizualize two popular effects of special relativity: **time dilation** and **length contraction**.

### 1 - Time Dilation

Add multiple events at the **same spatial coordinate** but at **different times**. The example below can represent a stationary clock that ticks every 2 seconds.

![Time dilation step 1](images/time_dilation_step_1.png)

As you increase the `observer_velocity`, the vertical line (worldline) formed by these events in the Lab Frame will tilt. The time difference between these events will appear *longer* in the Observer frame: time dilation. For example, for ann observer moving at half the speed of light, the clock ticks every 2.3 seconds.

![Time dilation step 2](images/time_dilation_step_2.png)

> [!NOTE]
> Note that the events doesn't happen at the same place anymore from that point of view. 

### Length Contraction

This one is a little bit more complicated. But we'll get into it.

First, add a rod (or multiple ones if you want to). Next, add two events: one at the tip of the rod, and the other at the tail (you will understand why soon).

![Length contraction 1](images/length_contraction_step_1.png)

Now, increase the `observer_velocity`. You will notice that the "distance" between the two events is now longer. But wait, why aren't we saying length dilation then?

![Length contraction 2](images/length_contraction_step_2.png)

Well, what is **length**? In the context of special realtivity, **length** can be define as the spacial distance between two events happening at the same time. If something has move between the moment you measured its tip and the moment you measure its tail, you are no longer measured its length!

That's exactly what is happening here. To get the rod's real length, the tip and the tail must be at the same time coordinate.

If we consider the version of the tail happening at the time coordinate as the tip, we will notice that the distance in indeed *shorter*. And we can clearly see on the globe that the rod object is shorter along the x-axis when viewed in the Observer frame: length contraction.

![Length contraction 3](images/length_contraction_step_3.png)

To implement the rod, I had to use a special formula to place the tail of the rod correctly:
$$
    x'_{tail} =  - v \times t'_{tip} + \frac{x_{tail}}{\gamma} 
$$
- $x'_{tail}$ is the space coordinate of the tail in the Observer frame
- $v$ is the Observer velocity relative to the Lab frame
- $t'_{tip}$ is the time coordinate of the tip in the Observer frame
- $x_{tail}$ is the space coordinate of the tail in the Lab frame
- $\gamma$ is gamma

I had to derive that formula by myself. I'll update the README later to write it down.


## Final thoughts
This spacetime globe project was a really challenging one! Even if I almost gave up sometimes, I came back to finish it, because it is better to finish a project, even imperfect, than trying to make it perfect and never finish it. Even if it's not perfect, I'm really proud of it. I gained so much knowledge on special relativity, C++ programming and game development.

I hope this tool would be useful to someone.