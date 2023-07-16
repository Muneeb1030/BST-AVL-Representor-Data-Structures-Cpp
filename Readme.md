# BST and AVL Tree Visualization

The BST and AVL Tree Visualization is a C++ program that utilizes the SFML library and object-oriented programming (OOP) to represent and visualize Binary Search Trees (BST) and AVL Trees. The program allows users to interactively input values, insert them into the trees, and observe the tree structure and rotations in real-time.

## Features

- BST and AVL tree visualization: The program visually represents the structure of BST and AVL trees using graphical elements.
- Interactive input and insertion: Users can input values and insert them into the trees using a user-friendly interface.
- Real-time tree updates: The program updates the tree structure in real-time after each insertion, allowing users to observe the changes visually.
- Rotation visualization: If an AVL tree becomes imbalanced after an insertion, the program marks the imbalance nodes and shows the rotations required to rebalance the tree.
- Search functionality: Users can search for specific values in both BST and AVL trees.
- Deletion functionality: Users can remove nodes from the trees, and the program updates the tree structure accordingly.

## Getting Started

To run the BST and AVL Tree Visualization program, follow these steps:

1. Clone the repository or download the source code files.
2. Install the SFML library. Refer to the official SFML documentation for installation instructions: [SFML Installation Guide](https://www.sfml-dev.org/download.php)
3. Open the terminal and navigate to the project directory.
4. Compile the source code using a C++ compiler and link with the SFML library:
```sh
g++ main.cpp -o bst_avl_visualization -lsfml-graphics -lsfml-window -lsfml-system
```
5. Run the program:
```sh
./bst_avl_visualization
```
6. Follow the on-screen instructions to interact with the program, insert values, search, and delete nodes in the BST and AVL trees.

## Dependencies

The BST and AVL Tree Visualization program has the following dependencies:

- SFML library: Required for graphical visualization of the trees. Make sure to install the SFML library before compiling the program.

## Customization

The program can be customized to fit specific requirements. Here are a few customization suggestions:

- Modify graphical elements: Explore the code in `Source.cpp` to customize the visual representation of the trees, such as node shapes, colors, and animations.
- Adjust insertion speed: In `Source.cpp`, you can change the delay between tree updates to control the speed at which the trees are visualized.
- Add additional functionality: Extend the program by implementing additional tree operations or visualizations.

Feel free to explore the codebase and experiment with different customizations to suit your needs.

## Contributing

Contributions to the BST and AVL Tree Visualization project are welcome! If you have any ideas, bug fixes, or enhancements, please open an issue or submit a pull request on the project's GitHub repository.

Please adhere to the code style and structure of the existing project when making contributions. Include clear commit messages and provide a detailed explanation of your changes.

## License

The BST and AVL Tree Visualization program is open-source and released under the [MIT License](LICENSE). See the `LICENSE` file for more details.

## Contact

If you have any questions or suggestions regarding the BST and AVL Tree Visualization program, please contact [m.muneeb.ur.rehman.2000@gmail.com](mailto:m.muneeb.ur.rehman.2000@gmail.com). We appreciate your feedback!

---

Thank you for using the BST and AVL Tree Visualization program! We hope it helps you understand and visualize the behavior of Binary Search Trees (BST) and AVL Trees effectively. Happy tree visualization!