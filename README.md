# Discrete Mathematics 2
---

This is the repository used to work in [this] project.

It's a C program that reads a graph both by console input and by file, and runs coloring algorithms on them.

## **Folders:**

#### * **Wahlaan**
This is the main folder and it contains all the files implemented to color the graphs.
Quick review:

**Rii.h**: This is the main file. It includes all the other files in the project. If you want to use our program, you should include this file and use our functions.    
**Build.c**: This file will load the graph with a given input (both files or console input), and return it with a Natural coloring. Build.c also has a "CopiarGrafo" function, that allows you to make a hard copy of your graph into another to make some test.    
**Color.c**: This file has implementations of Greedy and Bipartito coloring algorithms.    
**Grafo.c**: This is a simple file that only has the structure of the graphs.    
**Order.c**: This file has some sorting functions to reorder the vertex in the graph in order to improve the Greedy coloring.    
**Query.c**: This file has all the necessary query functions to work with the graphs.    
**Tree.c**: This file has the implementation of an AVL Tree, using the map file for the tree nodes. It's used to make a dictionary when you're reading a graph from input.    
**Map.c**: This file has the implementation of the nodes used by the AVL Tree.    
**Vector.c**: This file has the implementation of a vector like C++.

#### * **Test**
This folder contains tree tests: Penazzi.c, Memory.c and Performance.c
This will be explained later at the end, after "how to compile".

#### * **Ans**
This folder contains all the answers to the test made by the Python script.
This will also be explained after the tests.

---

#### **Implementation Ideas**
We had to deal with this two main problems:
* The input could be broken: i.e it could have bad-intentional comments in between of the edges, or it could have more or less edges than declared before, etc. So we have to check wether the input is safe or not.
* The input could give us some neighbours of vertex 1, then all neighbours of vertex 1000000, and then again some neighbours of vertex 1. So we couldn't just load the graph in the order it was given to us, we had to use something that tells us if a particular vertex has been loaded before or not, and help us know where to put that vertex.

We will talk about the returns later on, but first let's focus on how we've solved this problems:

To solve the first problem, we have to check every line we read from the files (or from the console input), throwing errors depending on what is wrong with that particular file. For example: if we find an edge that only has one vertex, we don't have to put that in our graph, because that's not a valid edge.    
This was an easy problem to fix, because the only thing we had to do was check that the number of lines that we read is the same as the number of edges the graph says it has, and then, when loading it, check that every edge has the correct format, i.e: it's name is a natural number (checking that every char we read is between the position of the number 0 and number 9 in the ASCII table), and it has two vertices.

To solve the second problem, we had to create some sort of "map" that told us were to put a given vertex.    
If we didn't use a map, there could be a problem:    
If, for n vertices, the file would give us the vertices in order, and named by 1, 2, ..., n - 1, n, we wouldn't have any problem to put that in the graph, but supose that the file gave us neighbours of vertex 1, then neighbours of vertex 2, and finally, some other neighbours of vertex 1, how could we know that we have loaded the vertex 1 before? Well, an easy solution could be: put the vertex 1 in the position 1 of an array, vertex 2 in the position 2 of that array, and so on. But there's a problem with that solution: What if the file gave us just the vertices 1 and 1000000? We would have a huge array, of 1000000 positions, just to load a graph with 2 vertices. So we have to know where to put that vertex, i.e: vertex 1 in position 0, vertex 1000000 in position 1, and the following vertex next to them. This could be solved in many ways: You could use a Hash Table, for example, but we've chosen to implement a Binary Search Tree.

But that Binary Search Tree leads us to another problem:    
What if the input was a list of ordered neighbours from 1 to 1e7?    
i.e: edge 1 2, edge 2 3, edge 3 4, ... , edge 999999 10000000 and edge 10000000 1    

If we implement a simple Binary Search Tree, the querys to know "where do I have to put this vertex?" could be O(n).    
And consider that it not only would be linear, but the querys would also depend over a linked list, and that's much slower than a linear query over an array. So we had to do something about this:

If the tree was balanced, the queries would be O(log(n)). So, an idea is to re-balance the tree everytime we put a vertex on it. And so we did it: We implemented an AVL Tree instead of a normal Binary Search Tree, and that solved the problem.

---

#### **Handling Errors**

The first error we have to worry about, are the problems with the file loading.    
As said before, they could have the wrong format we expect (the format of the graphs will be specified in details later), or they could be incomplete, etc. So we deal with this in build.c    

We know that there may be HUGE graphs, and some of them could cause troubles with the used memory.    
Supose you have a small RAM, and you run the program with a big graph. Supose then that when the graph is loading in the structure, the RAM is full, a malloc fails and the program continues. That wouldn't be acceptable, so for every alloc we do in this project, we check wheter the malloc returned something, or NULL. If it returned NULL, it means that for some reason, it couldn't save memory, so we have to return an error.    

Everytime a malloc fails, we stop the function, free the resourses, and then return NULL.
As you might expect, for some specific problems, we also make a printf showing what caused the error. It could be:

* **Failed in the first line without comment**: When the first line is not a commentary.
* **Failed to read**: When the graph has a syntax error in it.
* **Failed to allocate the memory for GrafoSt**: When the malloc for the Graph fails.
* **Failed to allocate the memory for vector**: When the malloc for the Vector fails.
* **Failed to allocate memory**: When a malloc for the dictionary, color, etc. fails.
* **Failed creating an edge**: When a malloc for some vertex fails.
* **Failed to add node to map**: When a malloc for a node fails.
* **Error reading an edge**: When an edge has the wrong syntax.
* **Number of vertices is not the same as the declared**: When the file has more/less vertices than declared.

---

#### **Functions explained**
We did a quick review of some Wahlaan files before, and we have to review some of them more deeply.

*A file you might need is **order.c**:

It has the implementation of:
* **OrdenNatural**: Reorder the vertex in non-decreasing order by name. This is the predef order we put the vertices when loading the graph.
* **OrdenWelshPowell**: Reorder the vertices in non-decreasing order by it's adjacency.
* **RMBCnormal**: Reorder the vertices in non-decreasing order by it's color (puts all vertices with color 1 first, the all vertices with color 2, and so on).
* **RMBCrevierte**: Reorder the vertices like "RMBCnormal" but in decreasing order (if graph G is colored with r colors, first all with color r, then all with color r - 1, and so on) 
* **RMBCchicogrande**: Reorder the vertices like "RMBCnormal", but depending on how many vertex uses that color in non-decreasing order (for example, if the graph only has 3 colors, 1 vertex colored with color 1, 300 vertex colored with color 2, and 25 vertex colored with color 3, it will reorder all vertex with color 1, then all vertex with color 3, and finally all vertex with color 2).
* **SwitchVertices**: Swaps the position of two given vertices in the graph.
* **SwitchColores**: Swaps the color of two given vertices in the graph.

This sorts are used in order to improve the coloring in the Greedy function.

*Another useful file is **query.c**:

It has the functions:
* **NumeroDeVertices**: Returns number of vertex in the given Graph.
* **NumeroDeLados**: Returns the number of edges in the given Graph.
* **NumeroDeColores**: Returns the number of different colors the given Graph.
* **NombreDelVertice**: Returns the name of the vertex in the given position.
* **ColorDelVertice**: Returns the color of the given vertex. Otherwise -1 (2^32-1 because it's unisgned).
* **GradoDelVertice**: Returns the vertex adjacency in the given position.
* **ColorJotaesimoVecino**: Returns the color of the given neighbour of the given vertex.
* **NombreJotaesimoVecino**: Returns the name of the given neighbour of the given vertex.

This functions are used to work with a graph, and take it's info.

And finally, **color.c**:    
This file has only two functions:    

* **Greedy**: This will run the Greedy coloring algorithm in a given order. You can change the order of the graph by using the functions mentioned above.
* **Bipartito**: This will check if the graph is bipartite or not. If it's bipartite, it will color it, bit if it's not, it will run Greedy, to give the graph a proper coloring, and return 1 to let you know it failed.

And that's all you need to use in order to color graphs. The other files, such as "Vector.c" are aux files to implement the needed structures and let this project working as best as possible.

---

#### **Graphs Syntax**
The syntax of the graphs used by this program is the following:
* All comments must be at the beginning, and start with the char **'c'**.
* The first **non-comentary** line should be **'p edge n m'** (where n = number of vertex, m = number of edges).
* The next following **m lines** should be **'e a b'** (where a = name of 'a' vertex, and b = name of 'b' vertex).

For example:    
> c Hello I'm a comment    
> c I'm a comment too    
> c I will be ignored    
> p edge 3 3    
> e 1 2    
> e 1 3    
> e 2 3    

Will make a triangle graph, with the vertex named '1', '2' and '3'.    
**Note**: All vertex should be named with an integer value.    
Some [examples] of graphs.    

---

#### **Compile**
We made a Python script called "run.py" that choose between two types of tests: "Penazzi test" and "Memory test". You can choose to run the tests in two modes: "Easy mode" and "Hard mode". Hard mode will activate some Make flags that will check that everything is running correctly.

To compile you can call run.py like this:    
```
python run.py [options] [test_name] [graph_name]
```
For example:    
```
python run.py -t penazzi queen10
```
This will run the penazzi test, with the graph called [queen10] in hard difficulty.    
Or you could do something like this:    
```
python run.py -t memory /*
```
This will run the memory test with all the graphs in hard difficulty.    

#### **Usage**

***Flags**:

  * **-t** or **--test**: Activates a hardcore testing flag, it checks everything: order, coloring, and every property (for example: RMBC does not increase the coloring). Warning: It's the slowest test of all.
  * **-v** or **--valgrind**: "Super valgrind", it shows all valgrind results with leaks and context errors.

***Avaible Tests**:
  * **Penazzi**: For each graph you test in this option, we have the answers of the results of Natural, Welsh, Switch, RMBC and Bipartito in the Ans folder. Warning: Natural is deterministic, the others could give you different results.
  * **Performance**: Checks how much time does it takes to run Switches and RMBC's with large graphs.
  * **Memory**: Uses CopiarGrafo, works with the copy, and checks whether there are leaks or not. It has the -v flag activated by default, so you don't have to run it with -v. Warning: Do not run Memory test with the -t flag on, or if you do so, then desactivate the RMBC assert that prevent RMBC to increase colors.

---

#### **Graphs**

There are 3 types of graphs: Penazzi, Performance and Memory.    
You should put the graphs in: "**/samples**/penazzi", "**/samples**/performance" or "**/samples**/memory"    
For Penazzi graphs **we know** what the answer is for the coloring functions.    
So Penazzi graphs **are limited**: Some of them are: [queen10], [queen13], [K100], [K500], [K1000], etc.    
For Performance and Memory test, we're free to create whatever graph we want to test.    
But for those test, we recommend large files, so you can test well the performance of the program. Some of those graphs are: [Graph1], [Graph2], [Graph3], [Graph4], etc.    
You can also test the Bipartito function, giving it large bipartite graphs, like this: [Graph5], [Graph6], [Graph7], etc.    
As said before, some graph examples are [this].    

---

#### **Ans and Test Folders**

**Ans** folder has the results for those 3 types of tests. For Penazzy test we have the answers, but for memory, for example, we use that folder to place the valgrind files when the program is done running.    
**Test** folder contains three .c files: **penazzi.c**, **memory.c** and **performance.c**
Those files are used by the Python script to run those tests.
If you want to add your own tests, feel free to add them to that folder, and to the run.py script, so you can use it.

---

[this]:https://www.famaf.unc.edu.ar/~penazzi/ProyectoDiscreta2019.pdf

[queen10]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/Corrdeotrapagina/q10.corr
[queen13]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/Corrdeotrapagina/q13.corr
[K100]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/KC
[K500]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/KD
[K1000]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/KM
[Graph1]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/Gf12345_12111222_457_15.gz
[Graph2]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/BxB1100_999_54_2017.tar.gz
[Graph3]:https://www.famaf.unc.edu.ar/~penazzi/AlgunosGrafos2019/Octo.txt.tar.gz
[Graph4]:https://www.famaf.unc.edu.ar/~penazzi/AlgunosGrafos2019/CBQsv1000_77_150.txt.tar.gz
[Graph5]:https://www.famaf.unc.edu.ar/~penazzi/Discreta2018/GRD99704280.tar.gz
[Graph6]:https://www.famaf.unc.edu.ar/~penazzi/AlgunosGrafos2019/DG100.txt
[Graph7]:https://www.famaf.unc.edu.ar/~penazzi/Discreta2018/GRD505041100.tar.gz

[examples]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/2019GrafosDeEjemplos2019.html
[this]:https://www.famaf.unc.edu.ar/~penazzi/DisII2016/2019GrafosDeEjemplos2019.html
