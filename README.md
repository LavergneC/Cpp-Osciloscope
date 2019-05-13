# Oscilloscope via Qt

Petit projet académique visant à réaliser la simulation d'un oscilloscope d'un signal fourni par un GBF sur un GUI développé avec Qt en C++.

## Utilisation

La partie microcontrôleur s'est développée sur une STM32F4Discovery, avec l'ADC, un timer et un UART pour transmettre les données en communication série vers l'ordinateur faisant tourner le GUI. 
On a en sortie l'affichage personnalisable de la courbe générée sur le GBF, ici une sinusoïde. Il est tout à fait possible d'afficher des signaux rampes ou des signaux triangles, par exemple.

![Signal Sinusoïdal](https://raw.githubusercontent.com/Guilyx/Cpp-Osciloscope/blob/master/docs/oscillo.png?raw=True)

## License

[MIT License](https://github.com/Guilyx/Cpp-Osciloscope/blob/master/LICENSE.md)
