# [WORKSHOP PROG/ALGO]

Rapport semaine de worshop sur le codage d'effets sur des images.

## 1. Ne garder que le vert

[*pas de problèmes rencontrés*]

![exo1](./output/pouet1.png)


## 2. Échanger les canaux

[*pas de problèmes rencontrés*]

![exo2](./output/pouet2.png)

## 3. Noir & Blanc

[*pas de problèmes rencontrés*]

![exo3](./output/pouet3.png)

## 4. Négatif

[*pas de problèmes rencontrés*]

![exo4](./output/pouet4.png)


## 5. Dégradé

*j'avais divisé x / image.width() sans convertir en float (float(x)), ce qui faisait une division entière donnant 0 et donc une image complètement noire au lieu d'un dégradé.*

![exo5](./output/pouet5.png)

## 6. Miroir

*J'avais fait parcourir la boucle x jusqu'à image.width() au lieu de image.width() / 2 ; l'image était donc inversée deux fois de suite et revenait exactement à l'image d'origine.*

![exo6](./output/pouet6.png)

## 7. Image bruitée

*J'avais mis srand(time(NULL)) à l'intérieur de la fonction et affecté la même valeur aléatoire aux trois canaux r, g et b, ce qui générait uniquement un grain gris/noir et blanc au lieu d'un bruit coloré.*

![exo7](./output/pouet7.png)

## 8. Rotation

[*pas de problèmes rencontrés*]

![exo8](./output/pouet8.png)

## 9. RGB SPLIT

[*pas de problèmes rencontrés*]


![exo9](./output/pouet9.png)

## 10. Luminosité

[*J'avais inversé le sens de l'exposant dans std::pow(valeur, exposant) en mettant un exposant supérieur à 1 pour éclaircir, ce qui aassombrit l'image*]


![exo10](./output/pouet10.1.png)

![exo10](./output/pouet10.2.png)

## 11. Disque

*J'avais oublié de centrer les coordonnées en soustrayant centre_x et centre_y dans l'équation x * x + y * y <= radius * radius, ce qui dessinait seulement un quart de disque blanc dans le coin en haut à gauche de l'image.*

![exo11](./output/pouet11.png)

## 12. Cercle

*J'avais mis uniquement une condition supérieure au rayon intérieur sans limiter au rayon extérieur,ce qui coloriait tout l'extérieur de l'image en blanc et laissait un trou noir au centre.*

![exo11](./output/pouet12.png)

## 13. Animation

![alt text](ezgif.com-gif-maker.gif)

*J'avais déclaré sil::Image en dehors de la boucle for des frames, ce qui empêchait d'effacer les positions précédentes et laissait une longue traînée blanche continue au lieu d'un disque qui se déplace.*

## 14. Rosace

![exo14](./output/pouet14.1.png)


## 15. Miroir

![exo15](./output/pouet15.png)


## 16. Miroir miroir

*J'avais utilisé le modulo % 2 sur la coordonnée du pixel au lieu du numéro de la rep, ce qui inversait un pixel sur deux au lieu d'inverser une image sur deux.*

![exo15](./output/pouet17.png)

## 17. glitch


![exo18](./output/pouet18.png)

## 18. Tri de pixels


![exo19](./output/pouet19.1.png)

*Pour le tri par ligne, j'avais oublié de multiplier l'indice de ligne y par image.width() dans image.pixels().begin() + y * image.width(), ce qui ne triait que les premiers pixels du haut de l'image au lieu de chaque ligne.*

![exo19](./output/pouet19.2.png)
![exo19](./output/pouet19.3.png)

## 19. Fractale de Mandelbrot

![exo19](./output/pouet20.png)
















