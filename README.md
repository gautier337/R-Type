# README for R-TYPE Multiplayer Network Game

## Introduction

Welcome to R-TYPE, a thrilling multiplayer network game that takes you into the heart of fast-paced, cooperative space battles. Our project is designed to offer an immersive gaming experience, emphasizing teamwork and strategy within a dynamic environment. This README provides essential information on setting up and starting the game, as well as insight into the technical backbone that makes our game unique.

## Game Engine: The ECS Method

R-TYPE is powered by a robust game engine utilizing the Entity-Component-System (ECS) methodology. This approach separates logic and data, allowing for highly flexible and efficient game design. Entities represent objects in the game world, components hold data, and systems provide the logic to interpret and manipulate this data. This decoupling allows for a modular design, where adding new features and maintaining existing ones becomes streamlined and more manageable.

### Advantages of ECS in R-TYPE:

- **Performance:** Efficient processing of game entities, ideal for the fast-paced nature of R-TYPE.
- **Modularity:** Easy to add and modify features without disrupting the entire system.
- **Flexibility:** Adapts to various gameplay scenarios and is robust against changing game requirements.

## Getting Started

To embark on your R-TYPE adventure, follow these steps to set up the game environment:

### Cloning the Repository

Begin by cloning the R-TYPE repository to your local machine:

```bash
git clone git@github.com:MaxPeix/R-TYPE.git
```

This command copies all the necessary game files to your system.

### Launching the Server

Once the repository is cloned, navigate to the server build directory and compile the server code:

```bash
cd server/build
cmake .. && make
```

After successful compilation, start the R-TYPE server:

```bash
./RTypeServer
```

### Launching the Client

With the server up and running, it's time to start the client-side of the game:

1. Navigate to the client directory:

```bash
cd client
```

2. Compile the client code:

```bash
make
```

3. Launch the R-TYPE client:

```bash
./client_rtype
```

## Gameplay

Upon launching the client, you'll enter the R-TYPE universe, where you can join other players in cooperative missions against various foes. Master your spacecraft, strategize with your team, and enjoy the high-octane combat that R-TYPE offers.

## Conclusion

R-TYPE represents a seamless blend of engaging gameplay and advanced technical design. By choosing the ECS method for our game engine, we've ensured a flexible, performant, and scalable environment that enhances the gaming experience. Whether you're a seasoned gamer or new to the world of multiplayer network games, R-TYPE promises hours of entertainment and camaraderie. Get ready to clone, compile, and conquer the cosmos with R-TYPE!
